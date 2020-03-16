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
      bool m_only
  ) {
    sfheaders::sfg::make_sfg( im, sfheaders::sfg::SFG_LINESTRING, m_only );
    return im;
  }

  inline SEXP sfg_linestring(
      Rcpp::IntegerVector& iv,
      bool m_only
  ) {
    R_xlen_t n = iv.length();
    Rcpp::IntegerMatrix im( 1, n );
    im( 0, Rcpp::_ ) = iv;
    return sfg_linestring( im, m_only );
  }


  inline SEXP sfg_linestring(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& cols,
      bool m_only
  ) {
    Rcpp::IntegerMatrix im2 = sfheaders::shapes::get_mat( im, cols );
    return sfg_linestring( im2, m_only );
  }

  inline SEXP sfg_linestring(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& cols,
      bool m_only
  ) {
    Rcpp::IntegerMatrix im2 = sfheaders::shapes::get_mat( im, cols );
    return sfg_linestring( im2, m_only );
  }

  inline SEXP sfg_linestring(
      Rcpp::NumericMatrix& nm,
      bool m_only
  ) {
    sfheaders::sfg::make_sfg( nm, sfheaders::sfg::SFG_LINESTRING, m_only );
    return nm;
  }

  inline SEXP sfg_linestring(
      Rcpp::NumericVector& nv,
      bool m_only
  ) {
    R_xlen_t n = nv.length();
    Rcpp::NumericMatrix nm( 1, n );
    nm( 0, Rcpp::_ ) = nv;
    return sfg_linestring( nm, m_only );
  }

  inline SEXP sfg_linestring(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& cols,
      bool m_only
  ) {
    Rcpp::NumericMatrix nm2 = sfheaders::shapes::get_mat( nm, cols );
    return sfg_linestring( nm2, m_only );
  }

  inline SEXP sfg_linestring(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& cols,
      bool m_only
  ) {
    Rcpp::NumericMatrix nm2 = sfheaders::shapes::get_mat( nm, cols );
    return sfg_linestring( nm2, m_only );
  }

  // expects only lon/lat/z/m columns
  inline SEXP sfg_linestring(
      Rcpp::DataFrame& df,
      bool m_only
  ) {
    Rcpp::NumericMatrix nm = sfheaders::utils::df_to_matrix( df );
    return sfg_linestring( nm, m_only );
  }

  inline SEXP sfg_linestring(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& cols,
      bool m_only
  ) {
    Rcpp::NumericMatrix nm = sfheaders::shapes::get_mat( df, cols );
    return sfg_linestring( nm, m_only );
  }

  inline SEXP sfg_linestring(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& cols,
      bool m_only
  ) {
    Rcpp::NumericMatrix nm = sfheaders::shapes::get_mat( df, cols );
    return sfg_linestring( nm, m_only );
  }

  inline SEXP sfg_linestring(
      SEXP& x,
      Rcpp::IntegerVector& cols,
      bool m_only
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix"); // #nocov
    }
      SEXP xc = Rcpp::clone( x );
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
      return sfg_linestring( im, cols, m_only );
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix"); // #nocov
    }
      SEXP xc = Rcpp::clone( x );
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
      return sfg_linestring( nm, cols, m_only );
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_linestring( df, cols, m_only );
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
      bool m_only
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix"); // #nocov
    }
      SEXP xc = Rcpp::clone( x );
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
      return sfg_linestring( im, cols, m_only );
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix"); // #nocov
    }
      SEXP xc = Rcpp::clone( x );
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
      return sfg_linestring( nm, cols, m_only );
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_linestring( df, cols, m_only );
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
      bool m_only
  ) {
    // switch on type of x
    switch ( TYPEOF( x ) ) {
    case INTSXP: {
    if( !Rf_isMatrix( x ) ) {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
      return sfg_linestring( iv, m_only );
    }
      SEXP xc = Rcpp::clone( x );
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
      return sfg_linestring( im, m_only );
    }
    case REALSXP: {
    if( !Rf_isMatrix( x ) ) {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
      return sfg_linestring( nv, m_only );
    }
      SEXP xc = Rcpp::clone( x );
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
      return sfg_linestring( nm, m_only );
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_linestring( df, m_only );
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
      bool m_only
  ) {
    if( Rf_isNull( cols ) ) {
      return sfg_linestring( x, m_only );
    }
    switch( TYPEOF( cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( cols );
      return sfg_linestring( x, iv, m_only );
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( cols );
      return sfg_linestring( x, sv, m_only );
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
