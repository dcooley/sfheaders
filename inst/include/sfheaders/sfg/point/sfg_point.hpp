#ifndef R_SFHEADERS_SFG_POINT_H
#define R_SFHEADERS_SFG_POINT_H

#include <Rcpp.h>
#include "sfheaders/utils/utils.hpp"
#include "sfheaders/shapes/shapes.hpp"
#include "sfheaders/sfg/sfg_types.hpp"

namespace sfheaders {
namespace sfg {

  inline SEXP sfg_point( Rcpp::IntegerVector& iv, std::string xyzm ) {
    sfheaders::sfg::make_sfg( iv, sfheaders::sfg::SFG_POINT, xyzm );
    return iv;
  }

  inline SEXP sfg_point( Rcpp::NumericVector& nv, std::string xyzm ) {
    sfheaders::sfg::make_sfg( nv, sfheaders::sfg::SFG_POINT, xyzm );
    return nv;
  }

  inline SEXP sfg_point( Rcpp::IntegerVector& iv, Rcpp::IntegerVector& cols, std::string xyzm ) {
    Rcpp::IntegerVector iv2 = iv[ cols ];
    return sfg_point( iv2, xyzm );
  }

  inline SEXP sfg_point( Rcpp::NumericVector& nv, Rcpp::IntegerVector& cols, std::string xyzm ) {
    Rcpp::NumericVector nv2 = nv[ cols ];
    return sfg_point( nv2, xyzm );
  }

  /*
   * assumes columns are in lon/lat/z/m order
   */
  inline SEXP sfg_point(
      Rcpp::IntegerMatrix& im,
      std::string xyzm
  ) {
    Rcpp::IntegerVector iv = sfheaders::shapes::get_vec( im );
    return sfg_point( iv, xyzm );
  }

  inline SEXP sfg_point(
      Rcpp::NumericMatrix& nm,
      std::string xyzm
  ) {
    Rcpp::NumericVector nv = sfheaders::shapes::get_vec( nm );
    return sfg_point( nv, xyzm );
  }

  inline SEXP sfg_point(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& cols,
      std::string xyzm
  ) {
    Rcpp::IntegerVector iv = sfheaders::shapes::get_vec( im, cols );
    return sfg_point( iv, xyzm );
  }

  inline SEXP sfg_point(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& cols,
      std::string xyzm
  ) {
    Rcpp::IntegerVector iv = sfheaders::shapes::get_vec( im, cols );
    return sfg_point( iv, xyzm );
  }

  inline SEXP sfg_point(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& cols,
      std::string xyzm
  ) {
    Rcpp::NumericVector nv = sfheaders::shapes::get_vec( nm, cols );
    return sfg_point( nv, xyzm );
  }

  inline SEXP sfg_point(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& cols,
      std::string xyzm
  ) {
    Rcpp::NumericVector nv = sfheaders::shapes::get_vec( nm, cols );
    return sfg_point( nv, xyzm );
  }

  // expects only lon/lat/z/m columns in correct order
  inline SEXP sfg_point(
      Rcpp::DataFrame& df,
      std::string xyzm
  ) {
    // expecting single-row data.frame
    Rcpp::NumericVector nv = sfheaders::shapes::get_vec( df );
    return sfg_point( nv, xyzm );
  }

  inline SEXP sfg_point(
    Rcpp::DataFrame& df,
    Rcpp::IntegerVector& cols,
    std::string xyzm
  ) {
    //Rcpp::NumericMatrix nm = sfheaders::utils::df_sfg_matrix( df );
    Rcpp::NumericVector nv = sfheaders::shapes::get_vec( df, cols );
    return sfg_point( nv, xyzm );
  }

  inline SEXP sfg_point(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& cols,
    std::string xyzm
  ) {
    Rcpp::NumericVector nv = sfheaders::shapes::get_vec( df, cols );
    return sfg_point( nv, xyzm );
  }

  inline SEXP sfg_point(
    SEXP& x,
    std::string xyzm
  ) {

    SEXP xc = Rcpp::clone( x );

    // switch on type of x
    switch ( TYPEOF( xc ) ) {
    case INTSXP: {
      if( Rf_isMatrix( xc ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
      return sfg_point( im, xyzm );
    } else {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( xc );
      return sfg_point( iv, xyzm );
    }
    }
    case REALSXP: {
      if( Rf_isMatrix( xc ) ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
      return sfg_point( nm, xyzm );
    } else {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( xc );
      return sfg_point( nv, xyzm );
    }
    }
    case VECSXP: { // data.frame && list?
    if( Rf_inherits( xc, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( xc );
      return sfg_point( df, xyzm );
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
      std::string xyzm
  ) {

    SEXP xc = Rcpp::clone( x );

    switch( TYPEOF( xc ) ) {
    case INTSXP: {
      if( Rf_isMatrix( xc ) ) {
        Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
        return sfg_point( im, cols, xyzm );
    } else {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( xc );
      return sfg_point( iv, cols, xyzm );
    }
    }
    case REALSXP: {
      if( Rf_isMatrix( xc ) ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
      return sfg_point( nm, cols, xyzm );
    } else {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( xc );
      return sfg_point( nv, cols, xyzm );
    }
    }
    case VECSXP: {
      if ( Rf_inherits( x, "data.frame" ) ) {
        Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( xc );
        return sfg_point( df, cols, xyzm );
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
      std::string xyzm
  ) {
    // with string columns it must be a data.frame(?)

    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
    return sfg_point( df, cols, xyzm );
  }


  /*
   * Unknown x and col types
   * First switch based on column types
   */
  inline SEXP sfg_point(
    SEXP& x,
    SEXP& cols,
    std::string xyzm      // this _can_ come from R, but it can also be 'empty' std::string("") (default string constructor)
    // iff it's empty, it means it has to be inferred.
    //
  ) {

    if( Rf_isNull( cols ) ) {
      return sfg_point( x, xyzm );
    }
    switch( TYPEOF( cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector int_cols = Rcpp::as< Rcpp::IntegerVector >( cols );
      return sfg_point( x, int_cols, xyzm );
    }
    case STRSXP: {
      Rcpp::StringVector str_cols = Rcpp::as< Rcpp::StringVector >( cols );
      return sfg_point( x, str_cols, xyzm );
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
