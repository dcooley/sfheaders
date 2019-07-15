#ifndef R_SFHEADERS_SFG_LINESTRING_H
#define R_SFHEADERS_SFG_LINESTRING_H

#include <Rcpp.h>
#include "sfheaders/utils/utils.hpp"
#include "sfheaders/shapes/shapes.hpp"
#include "sfheaders/sfg/sfg_attributes.hpp"
#include "sfheaders/sfg/sfg_dimension.hpp"

namespace sfheaders {
namespace sfg {

  /*
   * assumes columns are in lon/lat/z/m order
   */
  inline SEXP sfg_linestring(
      Rcpp::IntegerMatrix& im
  ) {
    size_t n_col = im.ncol();
    std::string dim = sfheaders::sfg::sfg_dimension( n_col );

    std::string geom_type = "LINESTRING";
    im.attr("class") = sfheaders::sfg::sfg_attributes( dim, geom_type );

    return im;
  }

  inline SEXP sfg_linestring(
      Rcpp::IntegerVector& iv
  ) {
    size_t n = iv.length();
    Rcpp::IntegerMatrix im( 1, n );
    im( 0, Rcpp::_ ) = iv;
    return sfg_linestring( im );
  }


  inline SEXP sfg_linestring(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& cols
  ) {
    Rcpp::IntegerMatrix im2 = sfheaders::shapes::get_mat( im, cols );
    return sfg_linestring( im2 );
  }

  inline SEXP sfg_linestring(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& cols
  ) {
    Rcpp::IntegerMatrix im2 = sfheaders::shapes::get_mat( im, cols );
    return sfg_linestring( im2 );
  }

  inline SEXP sfg_linestring(
      Rcpp::NumericMatrix& nm
  ) {

    size_t n_col = nm.ncol();
    std::string dim = sfheaders::sfg::sfg_dimension( n_col );

    std::string geom_type = "LINESTRING";
    nm.attr("class") = sfheaders::sfg::sfg_attributes(dim, geom_type);

    return nm;
  }

  inline SEXP sfg_linestring(
      Rcpp::NumericVector& nv
  ) {
    size_t n = nv.length();
    Rcpp::NumericMatrix nm( 1, n );
    nm( 0, Rcpp::_ ) = nv;
    return sfg_linestring( nm );
  }

  inline SEXP sfg_linestring(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& cols
  ) {
    Rcpp::NumericMatrix nm2 = sfheaders::shapes::get_mat( nm, cols );
    return sfg_linestring( nm2 );
  }

  inline SEXP sfg_linestring(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& cols
  ) {
    Rcpp::NumericMatrix nm2 = sfheaders::shapes::get_mat( nm, cols );
    return sfg_linestring( nm2 );
  }

  // expects only lon/lat/z/m columns
  inline SEXP sfg_linestring(
      Rcpp::DataFrame& df
  ) {
    Rcpp::NumericMatrix nm = sfheaders::utils::df_to_matrix( df );
    return sfg_linestring( nm );
  }

  inline SEXP sfg_linestring(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& cols
  ) {
    Rcpp::NumericMatrix nm = sfheaders::shapes::get_mat( df, cols );
    return sfg_linestring( nm );
  }

  inline SEXP sfg_linestring(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& cols
  ) {
    Rcpp::NumericMatrix nm = sfheaders::shapes::get_mat( df, cols );
    return sfg_linestring( nm );
  }

  inline SEXP sfg_linestring(
      SEXP& x,
      Rcpp::IntegerVector& cols
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return sfg_linestring( im, cols );
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return sfg_linestring( nm, cols );
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_linestring( df, cols );
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_LINESTRING type");
    }
    }

    return Rcpp::List::create(); // never reaches
  }

  inline SEXP sfg_linestring(
      SEXP& x,
      Rcpp::StringVector& cols
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return sfg_linestring( im, cols );
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return sfg_linestring( nm, cols );
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_linestring( df, cols );
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_LINESTRING type");
    }
    }

    return Rcpp::List::create(); // never reaches
  }


  inline SEXP sfg_linestring(
      SEXP& x
  ) {
    // switch on type of x
    switch ( TYPEOF( x ) ) {
    case INTSXP: {
    if( !Rf_isMatrix( x ) ) {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
      return sfg_linestring( iv );
    }
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return sfg_linestring( im );
    }
    case REALSXP: {
    if( !Rf_isMatrix( x ) ) {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
      return sfg_linestring( nv );
    }
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return sfg_linestring( nm );
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_linestring( df );
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_LINESTRING type");
    }
    }
    return x; // never reaches
  }

  inline SEXP sfg_linestring(
      SEXP& x,
      SEXP& cols
  ) {
    if( Rf_isNull( cols ) ) {
      return sfg_linestring( x );
    }
    switch( TYPEOF( cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( cols );
      return sfg_linestring( x, iv );
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( cols );
      return sfg_linestring( x, sv );
    }
    default: {
      Rcpp::stop("sfheaders - unknown column types");
    }
    }
    return Rcpp::List::create(); // never reaches
  }

} // sfg
} // sfheaders


#endif
