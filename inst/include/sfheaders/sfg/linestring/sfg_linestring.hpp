#ifndef R_SFHEADERS_SFG_LINESTRING_H
#define R_SFHEADERS_SFG_LINESTRING_H

#include <Rcpp.h>
#include "sfheaders/sfg/sfg_types.hpp"
#include "sfheaders/utils/utils.hpp"
#include "sfheaders/shapes/shapes.hpp"


namespace sfheaders {
namespace sfg {

  /*
   * assumes columns are in lon/lat/z/m order
   */
  inline SEXP sfg_linestring(
      Rcpp::IntegerMatrix& im,
      std::string xyzm
  ) {
    sfheaders::sfg::make_sfg( im, sfheaders::sfg::SFG_LINESTRING, xyzm );
    return im;
  }

  inline SEXP sfg_linestring(
      Rcpp::IntegerVector& iv,
      std::string xyzm
  ) {
    R_xlen_t n = iv.length();
    Rcpp::IntegerMatrix im( 1, n );
    im( 0, Rcpp::_ ) = iv;
    return sfg_linestring( im, xyzm );
  }


  inline SEXP sfg_linestring(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& cols,
      std::string xyzm
  ) {
    Rcpp::IntegerMatrix im2 = sfheaders::shapes::get_mat( im, cols );
    return sfg_linestring( im2, xyzm );
  }

  inline SEXP sfg_linestring(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& cols,
      std::string xyzm
  ) {
    Rcpp::IntegerMatrix im2 = sfheaders::shapes::get_mat( im, cols );
    return sfg_linestring( im2, xyzm );
  }

  inline SEXP sfg_linestring(
      Rcpp::NumericMatrix& nm,
      std::string xyzm
  ) {
    sfheaders::sfg::make_sfg( nm, sfheaders::sfg::SFG_LINESTRING, xyzm );
    return nm;
  }

  inline SEXP sfg_linestring(
      Rcpp::NumericVector& nv,
      std::string xyzm
  ) {
    R_xlen_t n = nv.length();
    Rcpp::NumericMatrix nm( 1, n );
    nm( 0, Rcpp::_ ) = nv;
    return sfg_linestring( nm, xyzm );
  }

  inline SEXP sfg_linestring(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& cols,
      std::string xyzm
  ) {
    Rcpp::NumericMatrix nm2 = sfheaders::shapes::get_mat( nm, cols );
    return sfg_linestring( nm2, xyzm );
  }

  inline SEXP sfg_linestring(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& cols,
      std::string xyzm
  ) {
    Rcpp::NumericMatrix nm2 = sfheaders::shapes::get_mat( nm, cols );
    return sfg_linestring( nm2, xyzm );
  }

  // expects only lon/lat/z/m columns
  inline SEXP sfg_linestring(
      Rcpp::DataFrame& df,
      std::string xyzm
  ) {
    Rcpp::NumericMatrix nm = sfheaders::utils::df_to_matrix( df );
    return sfg_linestring( nm, xyzm );
  }

  inline SEXP sfg_linestring(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& cols,
      std::string xyzm
  ) {
    Rcpp::NumericMatrix nm = sfheaders::shapes::get_mat( df, cols );
    return sfg_linestring( nm, xyzm );
  }

  inline SEXP sfg_linestring(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& cols,
      std::string xyzm
  ) {
    Rcpp::NumericMatrix nm = sfheaders::shapes::get_mat( df, cols );
    return sfg_linestring( nm, xyzm );
  }

  inline SEXP sfg_linestring(
      SEXP& x,
      Rcpp::IntegerVector& cols,
      std::string xyzm
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix"); // #nocov
    }
      SEXP xc = Rcpp::clone( x );
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
      return sfg_linestring( im, cols, xyzm );
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix"); // #nocov
    }
      SEXP xc = Rcpp::clone( x );
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
      return sfg_linestring( nm, cols, xyzm );
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_linestring( df, cols, xyzm );
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_LINESTRING type"); // #nocov
    }
    }

    return Rcpp::List::create(); // never reaches
  }

  inline SEXP sfg_linestring(
      SEXP& x,
      Rcpp::StringVector& cols,
      std::string xyzm
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix"); // #nocov
    }
      SEXP xc = Rcpp::clone( x );
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
      return sfg_linestring( im, cols, xyzm );
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix"); // #nocov
    }
      SEXP xc = Rcpp::clone( x );
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
      return sfg_linestring( nm, cols, xyzm );
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_linestring( df, cols, xyzm );
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_LINESTRING type"); // #nocov
    }
    }

    return Rcpp::List::create(); // never reaches
  }


  inline SEXP sfg_linestring(
      SEXP& x,
      std::string xyzm
  ) {
    // switch on type of x
    switch ( TYPEOF( x ) ) {
    case INTSXP: {
    if( !Rf_isMatrix( x ) ) {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
      return sfg_linestring( iv, xyzm );
    }
      SEXP xc = Rcpp::clone( x );
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
      return sfg_linestring( im, xyzm );
    }
    case REALSXP: {
    if( !Rf_isMatrix( x ) ) {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
      return sfg_linestring( nv, xyzm );
    }
      SEXP xc = Rcpp::clone( x );
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
      return sfg_linestring( nm, xyzm );
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_linestring( df, xyzm );
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
      SEXP& cols,
      std::string xyzm
  ) {
    if( Rf_isNull( cols ) ) {
      return sfg_linestring( x, xyzm );
    }
    switch( TYPEOF( cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( cols );
      return sfg_linestring( x, iv, xyzm );
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( cols );
      return sfg_linestring( x, sv, xyzm );
    }
    default: {
      Rcpp::stop("sfheaders - unknown column types"); // #nocov
    }
    }
    return Rcpp::List::create(); // never reaches
  }

} // sfg
} // sfheaders


#endif
