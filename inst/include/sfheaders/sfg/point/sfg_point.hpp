#ifndef R_SFHEADERS_SFG_POINT_H
#define R_SFHEADERS_SFG_POINT_H

#include <Rcpp.h>
#include "sfheaders/sfg/sfg_attributes.hpp"
#include "sfheaders/sfg/sfg_dimension.hpp"

namespace sfheaders {
namespace sfg {

  inline SEXP to_point( Rcpp::IntegerVector& iv ) {
    // takes a vector of size >= 2 && size <= 4 (for z & m)
    // attaches sfg_POINT attributes
    size_t n = iv.size();
    std::string dim = sfheaders::sfg::sfg_dimension( n );
    std::string geom_type = "POINT";
    iv.attr("class") = sfheaders::sfg::sfg_attributes(dim, geom_type);
    return iv;
  }

  inline SEXP to_point( Rcpp::NumericVector& nv ) {
    // takes a vector of size >= 2 && size <= 4 (for z & m)
    // attaches sfg_POINT attributes
    size_t n = nv.size();
    std::string dim = sfheaders::sfg::sfg_dimension( n );
    std::string geom_type = "POINT";
    nv.attr("class") = sfheaders::sfg::sfg_attributes(dim, geom_type) ;
    return nv;
  }

  /*
   * assumes columns are in lon/lat/z/m order
   */
  inline SEXP to_point(
      Rcpp::IntegerMatrix& im
  ) {

    size_t n_row = im.nrow();
    if( n_row != 1 ) {
      Rcpp::stop("sfheaders - expecting single-row matrix");
    }
    size_t n_col = im.ncol();
    Rcpp::IntegerVector iv = im( 0, Rcpp::_ );
    return to_point( iv );
  }

  inline SEXP to_point(
      Rcpp::IntegerMatrix& im,
      Rcpp::NumericVector& cols
  ) {

    size_t n_row = im.nrow();
    if( n_row != 1 ) {
      Rcpp::stop("sfheaders - expecting single-row matrix");
    }
    size_t n_col = im.ncol();
    size_t i;
    Rcpp::IntegerMatrix im2( n_row, n_col );
    for( i = 0; i < n_col; i++ ) {
      int this_col = cols[ i ];
      im2( Rcpp::_, i ) = im( Rcpp::_, this_col );
    }
    return to_point( im2 );
  }

  inline SEXP to_point(
      Rcpp::NumericMatrix& nm
  ) {

    size_t n_row = nm.nrow();
    if( n_row != 1 ) {
      Rcpp::stop("sfheaders - expecting single-row matrix");
    }
    size_t n_col = nm.ncol();
    Rcpp::NumericVector nv = nm( 0, Rcpp::_ );
    return to_point( nv );
  }

  inline SEXP to_point(
      Rcpp::NumericMatrix& nm,
      Rcpp::NumericVector& cols
  ) {

    size_t n_row = nm.nrow();
    if( n_row != 1 ) {
      Rcpp::stop("sfheaders - expecting single-row matrix");
    }
    size_t n_col = nm.ncol();
    size_t i;
    Rcpp::NumericMatrix nm2( n_row, n_col );
    for( i = 0; i < n_col; i++ ) {
      int this_col = cols[ i ];
      nm2( Rcpp::_, i ) = nm( Rcpp::_, this_col );
    }
    return to_point( nm2 );
  }

  // expects only lon/lat/z/m columns
  inline SEXP to_point(
      Rcpp::DataFrame& df
  ) {
    // expecting single-row data.frame
    size_t n_row = df.nrow();
    if( n_row != 1 ) {
      Rcpp::stop("sfheaders - expecting single-row data.frame");
    }
    size_t n_col = df.ncol();
    // need to extract each column-vector, then create a numeric vector from those
    Rcpp::NumericVector nv( n_col );
    size_t i;
    for( i = 0; i < n_col; i++ ) {
      nv[i] = df[i];
    }
    return to_point( nv );
  }

  inline SEXP to_point(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& cols
  ) {
    size_t n_col = cols.size();
    if( df.ncol() < n_col ) {
      Rcpp::stop("sfheaders - incorrect number of columns");
    }
    size_t n_row = df.nrow();
    if( n_row != 1 ) {
      Rcpp::stop("sfheaders - expecting single-row data.frame");
    }
    Rcpp::NumericVector nv( n_col );
    size_t i;
    for( i = 0; i < n_col; i++ ) {
      Rcpp::String this_col = cols[i];
      nv[i] = df[ this_col ];
    }
    return to_point( nv );
  }

  inline SEXP to_point(
    SEXP& x
  ) {

    // switch on type of x
    switch ( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return to_point( im );
    } else {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
      return to_point( iv );
    }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::NumericMatrix im = Rcpp::as< Rcpp::NumericMatrix >( x );
      return to_point( im );
    } else {
      Rcpp::NumericVector iv = Rcpp::as< Rcpp::NumericVector >( x );
      return to_point( iv );
    }
    }
    case VECSXP: { // data.frame && list?
    //   if( Rf_isNewList( x ) ) {
    //   Rcpp::stop("sfheaders - lists not supported for sfg_POINT");
    // }
      // TODO - rather than Rf_isNewList - need to check the class is not data.frame
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return to_point( df );
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_POINT type");
    }
    }

    return x; // never reaches
  }

  inline SEXP to_point(
      SEXP& x,
      Rcpp::NumericVector& cols
  ) {
    // with string columns it must be a data.frame(?)
    if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("Expecting a matrix ");
    }
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return to_point( im, cols );
    }
    case REALSXP: {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return to_point( nm, cols );
    }
    default: {
      Rcpp::stop("Expecting a matrix") ; //should never reach?
    }
    }
    return Rcpp::List::create(); // never reaches
  }

  inline SEXP to_point(
      SEXP& x,
      Rcpp::StringVector& cols
  ) {
    // with string columns it must be a data.frame(?)
    if( Rf_isMatrix( x ) ) {
      Rcpp::stop("Expecting a data.frame ");
    }
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
    return to_point( df, cols );
  }


} // sfg
} // sfheaders


#endif
