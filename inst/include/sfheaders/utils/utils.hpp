#ifndef R_SFHEADERS_UTILS_H
#define R_SFHEADERS_UTILS_H

#include <Rcpp.h>
#include "sfheaders/sfg/sfg_dimension.hpp"
#include "geometries/utils/utils.hpp"
#include "geometries/utils/sexp/sexp.hpp"

namespace sfheaders {
namespace utils {

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

  // inline Rcpp::List append_id_column( Rcpp::List& lst ) {
  //   // appends a column of 1s to a list
  //   R_xlen_t n_col = lst.length();
  //   if( n_col == 0 ) {
  //     Rcpp::stop("sfheaders - not enough columns");
  //   }
  //   R_xlen_t n_row = Rf_length( VECTOR_ELT( lst, 0 ) );
  //   R_xlen_t i;
  //   Rcpp::List res( n_col + 1 );
  //   for( i = 0; i < n_col; ++i ) {
  //     res[ i ] = lst[ i ];
  //   }
  //   Rcpp::IntegerVector ids( n_row, 1 );
  //   res[ n_col ] = ids;
  //   return res;
  // }

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
      return sfheaders::sfg::guess_xyzm( n_col );
    }
    return xyzm;
  }

  inline void resolve_id(
      SEXP& x,
      SEXP& id_columns,
      Rcpp::IntegerVector& int_id_column,
      Rcpp::List& res,
      Rcpp::List& lst,
      R_xlen_t& col_counter
  ) {
    if( Rf_isNull( id_columns ) ) {
      // add a vector / column to x
      append_id_column( res, col_counter );
      int_id_column = col_counter;
    } else {

      Rcpp::IntegerVector iv = validate_id_column( x, id_columns );
      // make sure it exists before subsetting it
      geometries::utils::column_exists( lst, iv );

      int col = iv[0];

      int_id_column[0] = col_counter;
      res[ col_counter ] = VECTOR_ELT( lst, col );
    }
    col_counter++;
  }

} // utils
} // sfheaders

#endif
