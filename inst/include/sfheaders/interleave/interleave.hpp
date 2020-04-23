#ifndef R_SFHEADERS_INTERLEAVE_H
#define R_SFHEADERS_INTERLEAVE_H

#include <Rcpp.h>
#include "sfheaders/df/sfc.hpp"
#include "sfheaders/df/sf.hpp"
#include "sfheaders/utils/lists/list.hpp"

namespace sfheaders {
namespace interleave {

  template < int RTYPE >
  inline SEXP interleave( Rcpp::Matrix< RTYPE >& mat ) {
    R_xlen_t n_col = mat.ncol();
    R_xlen_t n_row = mat.nrow();
    Rcpp::Vector< RTYPE > res( n_col * n_row );
    R_xlen_t i, j;
    R_xlen_t position_counter = 0;
    for( i = 0; i < n_row; ++i ) {
      for( j = 0; j < n_col; ++j ) {
        res[ position_counter ] = mat( i, j );
        position_counter = position_counter + 1;
      }
    }
    return res;
  }

  inline SEXP interleave( SEXP& sfg ) {

    switch( TYPEOF ( sfg ) ) {
    case INTSXP: {
    if( Rf_isMatrix( sfg ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( sfg );
      return interleave( im );
    } else {
      return sfg; // it's already a vector
    }
    }
    case REALSXP: {
    if( Rf_isMatrix( sfg ) ) {
      Rcpp::NumericMatrix im = Rcpp::as< Rcpp::NumericMatrix >( sfg );
      return interleave( im );
    } else {
      return sfg; // it's already a vector
    }
    }
    case VECSXP: {
    if( Rf_isNewList( sfg ) ) {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      R_xlen_t n = lst.size();
      R_xlen_t i;
      Rcpp::List res( n ); // store interleaved vectors in the same nested-list structure

      for( i = 0; i < n; ++i ) {
        SEXP sfg = lst[ i ];
        res[ i ] = interleave( sfg );
      }

      return sfheaders::utils::unlist_list( res );
    }
    }
    default: {
      Rcpp::stop("sfheaders - can not interleave this type of object");
    }
    }
    return Rcpp::List::create();
  }


  // TODO: unlist - to unlist some columns (like 'stroke_colour')
  inline SEXP interleave(
      Rcpp::List& sfc,
      R_xlen_t& total_coordinates
    ) {

    // the input will be a long data.frame
    // or an sf object
    // if it's a data.frame, it needs id columns and geometry columns
    // can probably do this one later?
    // and focus on the 'sf', because it doesn't need any extra headers / thought / logic

    // the STRIDE depends on the dimension being the same for every pair of coordinates
    Rcpp::CharacterVector cls;
    std::string dim_expected;
    std::string dim;

    R_xlen_t n = sfc.length();
    R_xlen_t i;

    //R_xlen_t total_coordinates = 0;
    Rcpp::List res_list( sfc.size() );
    Rcpp::List res_indices( sfc.size() );
    Rcpp::IntegerVector sfg_coordinates( sfc.size() );

    for( i = 0; i < n; ++i ) {

      SEXP sfg = sfc[ i ];

      cls = sfheaders::utils::getSfgClass( sfg );
      if( i == 0 ) {
        dim_expected = cls[0];
      } else {
        dim = cls[0];
        if ( dim != dim_expected ) {
          Rcpp::stop("sfheaders - interleaving only works when all geometries have the same dimension (XY(Z(M)))");
        }
      }

      Rcpp::IntegerMatrix coords = sfheaders::df::sfg_n_coordinates( sfg );

      R_xlen_t n_geometries = coords.nrow();
      R_xlen_t n_coordinates = coords( n_geometries - 1, 1 );

      // n_coordinates is the total number of coordinates for the given sfg
      // this is what the data needs to be expanded by.
      //n_coordinates = n_coordinates + 1;
      sfg_coordinates[ i ] = n_coordinates;

      Rcpp::IntegerVector start_indices = coords( Rcpp::_, 0 );
      start_indices = start_indices + total_coordinates;

      res_indices[ i ] = start_indices;
      res_list[ i ] = sfheaders::interleave::interleave( sfg );

      total_coordinates = total_coordinates + n_coordinates;
    }

    int stride = ( dim_expected == "XYZ" || dim_expected == "XYM" ? 3 : ( dim_expected == "XYZM" ? 4 : 2 ) );

    return Rcpp::List::create(
      Rcpp::_["coordinates"] = sfheaders::utils::unlist_list( res_list ),
      Rcpp::_["start_indices"] = sfheaders::utils::unlist_list( res_indices ),
      Rcpp::_["n_coordinates"] = sfg_coordinates,
      Rcpp::_["total_coordinates"] = total_coordinates,
      Rcpp::_["stride"] = stride
    );
  }

  inline SEXP interleave( Rcpp::List& sfc ) {
    R_xlen_t total_coordinates = 0;
    return interleave( sfc, total_coordinates );
  }


  // interleaves an `sf` object
  inline Rcpp::List interleave( Rcpp::DataFrame& sf ) {
    // and expand rows
    std::string geom_column = sf.attr("sf_column");
    Rcpp::CharacterVector sf_names = sf.names();
    Rcpp::List sfc = sf[ geom_column ];
    R_xlen_t n_col = sf.ncol();
    R_xlen_t n_geometries = sf.nrow();
    R_xlen_t i;
    R_xlen_t j;

    R_xlen_t total_coordinates = 0;
    Rcpp::List interleaved = interleave( sfc, total_coordinates );
    Rcpp::IntegerVector n_coordinates = interleaved["n_coordinates"];

    Rcpp::NumericVector expanded_index( total_coordinates );
    R_xlen_t counter = 0;

    for( i = 0; i < n_geometries; ++i ) {
      R_xlen_t expand_by = n_coordinates[ i ];

      for( j = 0; j < expand_by; ++j ) {
        expanded_index[ counter + j ] = i;
      }
      counter = counter + expand_by;
    }

    Rcpp::List res( n_col - 1 );
    Rcpp::StringVector res_names( n_col - 1 );

    R_xlen_t name_position = 0;

    for( i = 0; i < n_col; ++i ) {

      if( sf_names[ i ] != geom_column ) {

        res_names[ name_position ] = sf_names[ i ];
        SEXP v = sf[ i ];
        sfheaders::df::expand_vector( res, v, expanded_index, name_position );
        name_position += 1;
      }
    }

    //res.names() = res_names;
    Rcpp::DataFrame df = sfheaders::utils::make_dataframe( res, total_coordinates, res_names );

    // construct final object
    interleaved["data"] = df;
    return interleaved;

  }

} // interleave
} // sfheaders


#endif
