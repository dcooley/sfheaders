#ifndef R_SFHEADERS_SFC_MULTILINESTRING_H
#define R_SFHEADERS_SFC_MULTILINESTRING_H

#include <Rcpp.h>
#include "sfheaders/sfc/sfc_attributes.hpp"
#include "sfheaders/sfc/sfc_types.hpp"
#include "sfheaders/sfg/multilinestring/sfg_multilinestring.hpp"
#include "sfheaders/sfc/zm_range.hpp"

#include "geometries/utils/sexp/sexp.hpp"
#include "geometries/bbox/bbox.hpp"
#include "geometries/utils/columns/columns.hpp"
#include "geometries/geometries.hpp"
#include "geometries/nest/nest.hpp"
#include "geometries/utils/lists/as_list.hpp"

namespace sfheaders {
namespace sfc {

  inline Rcpp::IntegerVector validate_id_column( SEXP& x, SEXP& id_col ) {
    if( TYPEOF( id_col ) == INTSXP ) {
      return Rcpp::as< Rcpp::IntegerVector >( id_col );
    }
    return geometries::utils::sexp_col_int( x, id_col );
  }

  inline void append_id_column( Rcpp::List& res, R_xlen_t col_counter ) {

    R_xlen_t n_col = Rf_length( res );
    if( n_col == 0 ) {
      Rcpp::stop("sfheaders - not enough columns");
    }
    R_xlen_t n_row = Rf_length( VECTOR_ELT( res, 0 ) );

    Rcpp::IntegerVector ids( n_row, 1 );

    res[ col_counter ] = ids;
  }

  inline void subset_geometries( Rcpp::List& x, Rcpp::List& res, Rcpp::IntegerVector& geometry_cols ) {

    // fill res with the geometry columns.
    R_xlen_t n_col = geometries::utils::sexp_length( geometry_cols );
    R_xlen_t i;
    for( i = 0; i < n_col; ++i ) {
      res[ i ] = VECTOR_ELT( x, geometry_cols[i] );
    }
  }

  inline std::string validate_xyzm( std::string xyzm, R_xlen_t n_col ) {
    std::string chk = "";
    if( strcmp( xyzm.c_str(), chk.c_str() ) == 0 ) {
      return sfheaders::zm::guess_xyzm( n_col );
    }
    return xyzm;
  }

  inline SEXP sfc_multilinestring(
      SEXP& x,
      SEXP& geometry_cols,
      SEXP& multilinestring_id,
      SEXP& linestring_id,
      std::string xyzm
  ) {

    if( Rf_isNull( geometry_cols ) ) {
      // make this all the other columns, then send back in
      SEXP geometry_cols2 = geometries::utils::other_columns( x, multilinestring_id, linestring_id );

      // send back in
      return sfc_multilinestring( x, geometry_cols2, multilinestring_id, linestring_id, xyzm );
    }

    R_xlen_t col_counter = geometries::utils::sexp_length( geometry_cols );
    xyzm = validate_xyzm( xyzm, col_counter );
    Rcpp::StringVector class_attribute = { xyzm.c_str(), "MULTILINESTRING","sfg" };

    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();
    geometries::bbox::calculate_bbox( bbox, x );
    sfheaders::zm::calculate_zm_ranges( z_range, m_range, x, geometry_cols, xyzm );


    R_xlen_t required_cols = col_counter + 2;

    Rcpp::IntegerVector int_geometry_cols = geometries::utils::sexp_col_int( x, geometry_cols );


    Rcpp::List lst = geometries::utils::as_list( x );
    Rcpp::List res( required_cols );

    subset_geometries( lst, res, int_geometry_cols );

    Rcpp::IntegerVector int_multilinestring_id(1);
    Rcpp::IntegerVector int_linestring_id(1);

    if( Rf_isNull( multilinestring_id ) ) {
      // add a vector / column to x
      append_id_column( res, col_counter );
      int_multilinestring_id = col_counter;
    } else {

      Rcpp::IntegerVector iv = validate_id_column( x, multilinestring_id );
      int col = iv[0];
      int_multilinestring_id[0] = col_counter;
      res[ col_counter ] = VECTOR_ELT( lst, col );
    }
    col_counter++;



    if( Rf_isNull( linestring_id ) ) {
      // add a vector / column to x
      append_id_column( res, col_counter );
      int_linestring_id = col_counter;
    } else {
      Rcpp::IntegerVector iv = validate_id_column( x, linestring_id );
      int col = iv[0];
      int_linestring_id[0] = col_counter;
      res[ col_counter ] = VECTOR_ELT( lst, col );
    }
    col_counter++;

    Rcpp::IntegerVector int_id_cols = geometries::utils::concatenate_vectors( int_multilinestring_id, int_linestring_id );



    Rcpp::List sfc = geometries::make_geometries( res, int_id_cols, int_geometry_cols, class_attribute );
    return sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTILINESTRING, bbox, z_range, m_range );

  }

} // sfc
} // sfheaders

#endif
