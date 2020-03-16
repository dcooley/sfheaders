#ifndef R_SFHEADERS_SFG_POINT_H
#define R_SFHEADERS_SFG_POINT_H

#include <Rcpp.h>
#include "sfheaders/utils/utils.hpp"
#include "sfheaders/shapes/shapes.hpp"
#include "sfheaders/sfg/sfg_types.hpp"

namespace sfheaders {
namespace sfg {

  inline SEXP sfg_point( Rcpp::IntegerVector& iv, bool m_only ) {
    sfheaders::sfg::make_sfg( iv, sfheaders::sfg::SFG_POINT, m_only );
    return iv;
  }

  inline SEXP sfg_point( Rcpp::NumericVector& nv, bool m_only ) {
    sfheaders::sfg::make_sfg( nv, sfheaders::sfg::SFG_POINT, m_only );
    return nv;
  }

  inline SEXP sfg_point( Rcpp::IntegerVector& iv, Rcpp::IntegerVector& cols, bool m_only ) {
    Rcpp::IntegerVector iv2 = iv[ cols ];
    return sfg_point( iv2, m_only );
  }

  inline SEXP sfg_point( Rcpp::NumericVector& nv, Rcpp::IntegerVector& cols, bool m_only ) {
    Rcpp::NumericVector nv2 = nv[ cols ];
    return sfg_point( nv2, m_only );
  }

  /*
   * assumes columns are in lon/lat/z/m order
   */
  inline SEXP sfg_point(
      Rcpp::IntegerMatrix& im,
      bool m_only
  ) {
    Rcpp::IntegerVector iv = sfheaders::shapes::get_vec( im );
    return sfg_point( iv, m_only );
  }

  inline SEXP sfg_point(
      Rcpp::NumericMatrix& nm,
      bool m_only
  ) {
    Rcpp::NumericVector nv = sfheaders::shapes::get_vec( nm );
    return sfg_point( nv, m_only );
  }

  inline SEXP sfg_point(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& cols,
      bool m_only
  ) {
    Rcpp::IntegerVector iv = sfheaders::shapes::get_vec( im, cols );
    return sfg_point( iv, m_only );
  }

  inline SEXP sfg_point(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& cols,
      bool m_only
  ) {
    Rcpp::IntegerVector iv = sfheaders::shapes::get_vec( im, cols );
    return sfg_point( iv, m_only );
  }

  inline SEXP sfg_point(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& cols,
      bool m_only
  ) {
    Rcpp::NumericVector nv = sfheaders::shapes::get_vec( nm, cols );
    return sfg_point( nv, m_only );
  }

  inline SEXP sfg_point(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& cols,
      bool m_only
  ) {
    Rcpp::NumericVector nv = sfheaders::shapes::get_vec( nm, cols );
    return sfg_point( nv, m_only );
  }

  // expects only lon/lat/z/m columns in correct order
  inline SEXP sfg_point(
      Rcpp::DataFrame& df,
      bool m_only
  ) {
    // expecting single-row data.frame
    Rcpp::NumericVector nv = sfheaders::shapes::get_vec( df );
    return sfg_point( nv, m_only );
  }

  inline SEXP sfg_point(
    Rcpp::DataFrame& df,
    Rcpp::IntegerVector& cols,
    bool m_only
  ) {
    //Rcpp::NumericMatrix nm = sfheaders::utils::df_sfg_matrix( df );
    Rcpp::NumericVector nv = sfheaders::shapes::get_vec( df, cols );
    return sfg_point( nv, m_only );
  }

  inline SEXP sfg_point(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& cols,
    bool m_only
  ) {
    Rcpp::NumericVector nv = sfheaders::shapes::get_vec( df, cols );
    return sfg_point( nv, m_only );
  }

  inline SEXP sfg_point(
    SEXP& x,
    bool m_only
  ) {

    SEXP xc = Rcpp::clone( x );

    // switch on type of x
    switch ( TYPEOF( xc ) ) {
    case INTSXP: {
      if( Rf_isMatrix( xc ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
      return sfg_point( im, m_only );
    } else {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( xc );
      return sfg_point( iv, m_only );
    }
    }
    case REALSXP: {
      if( Rf_isMatrix( xc ) ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
      return sfg_point( nm, m_only );
    } else {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( xc );
      return sfg_point( nv, m_only );
    }
    }
    case VECSXP: { // data.frame && list?
    if( Rf_inherits( xc, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( xc );
      return sfg_point( df, m_only );
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_POINT type");
    }
    }

    return x; // never reaches
  }

  inline SEXP sfg_point(
      SEXP& x,
      Rcpp::IntegerVector& cols,
      bool m_only
  ) {

    SEXP xc = Rcpp::clone( x );

    switch( TYPEOF( xc ) ) {
    case INTSXP: {
      if( Rf_isMatrix( xc ) ) {
        Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
        return sfg_point( im, cols, m_only );
    } else {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( xc );
      return sfg_point( iv, cols, m_only );
    }
    }
    case REALSXP: {
      if( Rf_isMatrix( xc ) ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
      return sfg_point( nm, cols, m_only );
    } else {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( xc );
      return sfg_point( nv, cols, m_only );
    }
    }
    case VECSXP: {
      if ( Rf_inherits( x, "data.frame" ) ) {
        Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( xc );
        return sfg_point( df, cols, m_only );
      } //else - default
    }
    default: {
      Rcpp::stop("sfheaders - unknown point type");  // #nocov
    }
    }
    return Rcpp::List::create(); // never reaches
  }

  inline SEXP sfg_point(
      SEXP& x,
      Rcpp::StringVector& cols,
      bool m_only
  ) {
    // with string columns it must be a data.frame(?)

    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
    return sfg_point( df, cols, m_only );
  }


  /*
   * Unknown x and col types
   * First switch based on column types
   */
  inline SEXP sfg_point(
    SEXP& x,
    SEXP& cols,
    bool m_only
  ) {

    if( Rf_isNull( cols ) ) {
      return sfg_point( x, m_only );
    }
    switch( TYPEOF( cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector int_cols = Rcpp::as< Rcpp::IntegerVector >( cols );
      return sfg_point( x, int_cols, m_only );
    }
    case STRSXP: {
      Rcpp::StringVector str_cols = Rcpp::as< Rcpp::StringVector >( cols );
      return sfg_point( x, str_cols, m_only );
    }
    default: {
      Rcpp::stop("sfheaders - unknown column types");  // #nocov
    }
    }
    return Rcpp::List::create(); // never reaches
  }


} // sfg
} // sfheaders


#endif
