#ifndef R_SFHEADERS_SHAPES_VEC_H
#define R_SFHEADERS_SHAPES_VEC_H

#include <Rcpp.h>
#include "sfheaders/utils/utils.hpp"

namespace sfheaders {
namespace shapes {

  // POINTS are vectors

  inline SEXP get_vec(
      Rcpp::IntegerVector& iv
  ) {
    return iv;
  }

  inline SEXP get_vec(
      Rcpp::NumericVector& nv
  ) {
    return nv;
  }

  inline SEXP get_vec(
      Rcpp::IntegerMatrix& im
  ) {
    R_xlen_t n_row = im.nrow();
    if( n_row != 1 ) {
      Rcpp::stop("sfheaders - expecting single-row matrix");
    }
    Rcpp::IntegerVector iv = im( 0, Rcpp::_ );
    return iv;
  }

  inline SEXP get_vec(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& cols
  ) {
    R_xlen_t n_row = im.nrow();
    if( n_row != 1 ) {
      Rcpp::stop("sfheaders - expecting single-row matrix");
    }
    R_xlen_t n_col = cols.length();
    R_xlen_t i;
    Rcpp::IntegerVector iv( n_col );
    for( i = 0; i < n_col; i++ ) {
      int this_col = cols[ i ];
      iv[ i ] = im( 0, this_col );
    }
    return iv;
  }

  inline SEXP get_vec(
      Rcpp::DataFrame& df
  ) {
    R_xlen_t n_row = df.nrow();
    if( n_row != 1 ) {
      Rcpp::stop("sfheaders - expecting single-row data.frame");
    }
    R_xlen_t n_col = df.ncol();
    Rcpp::NumericVector nv( n_col );
    R_xlen_t i;
    for( i = 0; i < n_col; i++ ) {
      nv[i] = df[i];
    }
    return nv;
  }

  inline SEXP get_vec(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& cols
  ) {
    R_xlen_t n_col = cols.length();
    if( df.ncol() < n_col ) {
      Rcpp::stop("sfheaders - incorrect number of columns");
    }
    R_xlen_t n_row = df.nrow();
    if( n_row != 1 ) {
      Rcpp::stop("sfheaders - expecting single-row data.frame");
    }
    Rcpp::NumericVector nv( n_col );
    R_xlen_t i;
    for( i = 0; i < n_col; i++ ) {
      Rcpp::String this_col = cols[ i ];
      nv[i] = df[ this_col ];
    }
    return nv;
  }


  inline SEXP get_vec(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& cols
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );
    return get_vec( df, cols );
  }

  inline SEXP get_vec(
      Rcpp::NumericMatrix& nm
  ) {
    R_xlen_t n_row = nm.nrow();
    if( n_row != 1 ) {
      Rcpp::stop("sfheaders - expecting single-row matrix");
    }
    Rcpp::NumericVector nv = nm( 0, Rcpp::_ );
    return nv;
  }

  inline SEXP get_vec(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& cols
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );
    return get_vec( df, cols );
  }


  inline SEXP get_vec(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& cols
  ) {
    R_xlen_t n_row = nm.nrow();
    if( n_row != 1 ) {
      Rcpp::stop("sfheaders - expecting single-row matrix");
    }
    R_xlen_t n_col = cols.length();
    R_xlen_t i;
    Rcpp::NumericVector nv( n_col );
    for( i = 0; i < n_col; i++ ) {
      int this_col = cols[ i ];
      nv[ i ] = nm( 0, this_col );
    }
    return nv;
  }

  inline SEXP get_vec(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& cols
  ) {
    Rcpp::NumericMatrix nm = sfheaders::utils::df_to_matrix( df, cols );
    return get_vec( nm );
  }

  inline SEXP get_vec(
      SEXP& x,
      Rcpp::IntegerVector& cols
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return get_vec( im, cols );
    }
    case REALSXP: {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return get_vec( nm, cols );
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return get_vec( df );
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported POINT type");
    }
    }
    return Rcpp::List::create(); // never reaches
  }

  inline SEXP get_vec(
      SEXP& x,
      Rcpp::StringVector& cols
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return get_vec( im, cols );
    }
    case REALSXP: {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return get_vec( nm, cols );
    }
    case VECSXP: {
    if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return get_vec( df, cols );
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported POINT type");
    }
    }
    return Rcpp::List::create(); // never reaches
  }

  inline SEXP get_vec(
      SEXP& x
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return get_vec( im );
    } else {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
      return get_vec( iv );
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return get_vec( nm );
    } else {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
      return get_vec( nv );
    }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return get_vec( df );
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported POINT type");
    }
    }
    }
    return Rcpp::List::create(); // never reaches
  }

  inline SEXP get_vec(
      SEXP& x,
      SEXP& cols
  ) {

    if( Rf_isNull( cols ) ) {
      return get_vec( x );
    }

    switch( TYPEOF( cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( cols );
      if( iv.length() == 0 ) {
        return get_vec( x );
      } else {
        return get_vec( x, iv );
      }
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( cols );
      if( sv.length() == 0 ) {
        return get_vec( x );
      } else {
        return get_vec( x, sv );
      }
    }
    default: {
      Rcpp::stop("sfheaders - unknown column types");
    }
    }
  }

}
} // sfheaders


#endif
