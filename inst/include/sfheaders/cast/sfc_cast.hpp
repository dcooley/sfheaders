#ifndef R_SFHEADERS_CAST_SFC_H
#define R_SFHEADERS_CAST_SFC_H

//#include "sfheaders/sf/sf_utils.hpp"
#include "sfheaders/df/sf.hpp"
#include "sfheaders/cast/sfg_cast.hpp"
#include "sfheaders/sfc/zm_range.hpp"
#include "sfheaders/sfc/sfc_attributes.hpp"
//#include "sfheaders/df/sfg.hpp"
//#include "sfheaders/df/utils.hpp"

#include <Rcpp.h>

namespace sfheaders {
namespace cast {


  inline Rcpp::IntegerVector count_new_sfc_objects( Rcpp::List& sfc, std::string& cast_to ) {
    R_xlen_t n = sfc.size();
    Rcpp::IntegerVector res( n );
    R_xlen_t i;
    for( i = 0; i < n; ++i ) {
      SEXP sfg = sfc[ i ];
      res[ i ] = sfheaders::cast::count_new_objects( sfg, cast_to );
    }
    return res;
  }

  // returns CAST_UP or CAST_DOWN
  // given the from & to
  // casting to the same geometry will be counted as 'DOWN'
  inline int cast_type( std::string& cast ) {
    if( cast == "POINT" ) {
      return sfheaders::sfg::VECTOR;    // 1
    } else if ( cast == "MULTIPOINT" ) {
      return sfheaders::sfg::MATRIX;    // 2
    } else if ( cast == "LINESTRING" ) {
      return sfheaders::sfg::MATRIX;    // 2
    } else if ( cast == "MULTILINESTRING" ) {
      return sfheaders::sfg::LIST_MATRIX;  // 3
    } else if ( cast == "POLYGON" ) {
      return sfheaders::sfg::LIST_MATRIX;  // 3
    } else if ( cast == "MULTIPOLYGON" ) {
      return sfheaders::sfg::LIST_LIST_MATRIX;  // 4
    } else {
      Rcpp::stop("sfheders - unknown geometry type to cast to");  // #nocov
    }
    return -1;
  }


  // casting list-columns follows similar logic to sfc
  inline Rcpp::List cast_list(
      Rcpp::List& list_column,
      Rcpp::List& sfc,                 // required to know the 'from' type
      Rcpp::IntegerVector& n_results,
      std::string& cast_to
  ) {

    int casting_to = cast_type( cast_to ) - 1; // TODO: why is this -1 needed???
    std::string cast_from;

    R_xlen_t i, j;

    R_xlen_t total_results = Rcpp::sum( n_results );
    Rcpp::List res( total_results );

    R_xlen_t result_counter = 0;  // for indexing into the res( ) list

    R_xlen_t n = sfc.size();

    for( i = 0; i < n; ++i ) {

      Rcpp::Rcout << "i: " << i << std::endl;

      // the value at n_results[ i ] tells us the size of the returning object
      R_xlen_t returned_size = n_results[ i ];

      SEXP sfg = sfc[ i ];
      SEXP list_element = list_column[ i ];

      Rcpp::CharacterVector cls = sfheaders::utils::getSfgClass( sfg );
      cast_from = cls[1];

      int casting_from = cast_type( cast_from );

      //SEXP new_res = sfheaders::cast::cast_to( sfg, cast_from, cast_to, xyzm, close );
      Rcpp::Rcout << "casting_from: " << casting_from << std::endl;
      Rcpp::Rcout << "casting_to: " << casting_to << std::endl;
      Rcpp::Rcout << "input list element size: " << geometries::utils::sexp_length( list_element ) << std::endl;
      //return list_element;

      Rcpp::List new_res = geometries::nest::nest_impl( list_element, casting_to );

      //Rcpp::List lst_res = Rcpp::as< Rcpp::List >( new_res );
      Rcpp::Rcout << "output size: " << new_res.size() << std::endl;
      Rcpp::Rcout << "returned_size: " << returned_size << std::endl;
      //return new_res;
      //Rcpp::stop("stopping");

      if( casting_from <= casting_to ) {
        res[ result_counter ] = new_res;
        ++result_counter;
      } else {
        for( j = 0; j < returned_size; ++j ) {
          Rcpp::List new_lst = Rcpp::as< Rcpp::List >( new_res );
          res[ result_counter ] = new_lst[ j ];
          ++result_counter;
        }
      }

    }

    return res;
  }

  // TODO: keep / calculate the bbox, z_range and m_range
  // these shouldn't change; because the coordinates aren't changing,right?
  inline Rcpp::List cast_sfc(
      Rcpp::List& sfc,
      Rcpp::IntegerVector& n_results,
      std::string& cast_to,
      bool close = true
  ) {

    int casting_to = cast_type( cast_to );

    Rcpp::List crs = sfc.attr("crs");
    sfheaders::sfc::update_crs( crs );

    double precision = sfc.attr("precision");
    Rcpp::NumericVector bbox = sfc.attr("bbox");

    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range(); // = sfc.attr("z_range");
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range(); // = sfc.attr("m_range");

    if( sfc.hasAttribute("z_range") ) {
      z_range = sfc.attr("z_range");
    }

    if( sfc.hasAttribute("m_range") ) {
      m_range = sfc.attr("m_range");
    }

    int n_empty = sfc.attr("n_empty");
    std::unordered_set< std::string > geometry_types{ cast_to };

    std::string cast_from;
    std::string xyzm;

    R_xlen_t i, j;

    R_xlen_t total_results = Rcpp::sum( n_results );
    Rcpp::List res( total_results );

    // loop over reach sfg and convert and fill teh resutl list
    R_xlen_t result_counter = 0;  // for indexing into the res( ) list

    // IFF the input is not a list, this loop won't work
    // so only use this list loop iff the casting_from >= LIST_MATRIX !! done

    R_xlen_t n = sfc.size();

    for( i = 0; i < n; ++i ) {

      // the value at n_results[ i ] tells us the size of the returning object
      R_xlen_t returned_size = n_results[ i ];

      SEXP sfg = sfc[ i ];

      Rcpp::CharacterVector cls = sfheaders::utils::getSfgClass( sfg );
      cast_from = cls[1];
      xyzm = cls[0];

      int casting_from = cast_type( cast_from );

      SEXP new_res = sfheaders::cast::cast_to( sfg, cast_from, cast_to, xyzm, close );

      if( casting_from <= casting_to ) {
        res[ result_counter ] = new_res;
        ++result_counter;
      } else {
        for( j = 0; j < returned_size; ++j ) {
          Rcpp::List new_lst = Rcpp::as< Rcpp::List >( new_res );
          res[ result_counter ] = new_lst[ j ];
          ++result_counter;
        }
      }

    }
    sfheaders::sfc::attach_sfc_attributes(
      res, cast_to, geometry_types, bbox, z_range, m_range, crs, n_empty, precision
      );
    return res;
  }

  inline Rcpp::List cast_sfc(
      Rcpp::List& sfc,
      std::string& cast_to,
      bool close = true
  ) {

    Rcpp::IntegerVector n_results = count_new_sfc_objects( sfc, cast_to );
    return cast_sfc( sfc, n_results, cast_to, close );
  }


} // cast
} // sfheaders


#endif
