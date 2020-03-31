#ifndef R_SFHEADERS_SFG_MULTIPOINT_H
#define R_SFHEADERS_SFG_MULTIPOINT_H

#include <Rcpp.h>
#include "sfheaders/utils/utils.hpp"
#include "sfheaders/shapes/shapes.hpp"
#include "sfheaders/sfg/sfg_types.hpp"

namespace sfheaders {
namespace sfg {

  /*
   * assumes columns are in lon/lat/z/m order
   */
  inline SEXP sfg_multipoint(
      Rcpp::IntegerMatrix& im
  ) {
    sfheaders::sfg::make_sfg( im, sfheaders::sfg::SFG_MULTIPOINT );
    return im;
  }

  inline SEXP sfg_multipoint(
      Rcpp::IntegerVector& iv
  ) {
    R_xlen_t n = iv.length();
    Rcpp::IntegerMatrix im( 1, n );
    im( 0, Rcpp::_ ) = iv;
    return sfg_multipoint( im );
  }

  inline SEXP sfg_multipoint(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& cols
  ) {
    Rcpp::IntegerMatrix im2 = sfheaders::shapes::get_mat( im, cols );
    return sfg_multipoint( im2 );
  }

  inline SEXP sfg_multipoint(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& cols
  ) {
    Rcpp::IntegerMatrix im2 = sfheaders::shapes::get_mat( im, cols );
    return sfg_multipoint( im2 );
  }

  inline SEXP sfg_multipoint(
      Rcpp::NumericMatrix& nm
  ) {
    sfheaders::sfg::make_sfg( nm, sfheaders::sfg::SFG_MULTIPOINT );
    return nm;
  }

  inline SEXP sfg_multipoint(
      Rcpp::NumericVector& nv
  ) {
    R_xlen_t n = nv.length();
    Rcpp::NumericMatrix nm( 1, n );
    nm( 0, Rcpp::_ ) = nv;
    return sfg_multipoint( nm );
  }

  inline SEXP sfg_multipoint(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& cols
  ) {
    Rcpp::NumericMatrix nm2 = sfheaders::shapes::get_mat( nm, cols );
    return sfg_multipoint( nm2 );
  }

  inline SEXP sfg_multipoint(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& cols
  ) {
    Rcpp::NumericMatrix nm2 = sfheaders::shapes::get_mat( nm, cols );
    return sfg_multipoint( nm2 );
  }

  // expects only lon/lat/z/m columns
  inline SEXP sfg_multipoint(
      Rcpp::DataFrame& df
  ) {
    Rcpp::NumericMatrix nm = sfheaders::utils::df_to_matrix( df );
    return sfg_multipoint( nm );
  }

  inline SEXP sfg_multipoint(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& cols
  ) {
    Rcpp::NumericMatrix nm = sfheaders::shapes::get_mat( df, cols );
    return sfg_multipoint( nm );
  }

  inline SEXP sfg_multipoint(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& cols
  ) {
    Rcpp::NumericMatrix nm = sfheaders::shapes::get_mat( df, cols );
    return sfg_multipoint( nm );
  }

inline SEXP sfg_multipoint(
    SEXP& x,
    Rcpp::IntegerVector& cols
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
        Rcpp::stop("sfheaders - expecting a matrix"); // #nocov
      } else {
        SEXP xc = Rcpp::clone( x );
        Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
        return sfg_multipoint( im, cols );
      }
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
        Rcpp::stop("sfheaders - expecting a matrix"); // #nocov
      } else {
        SEXP xc = Rcpp::clone( x );
        Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
        return sfg_multipoint( nm, cols );
      }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_multipoint( df, cols );
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_MULTIPOINT type");  // #nocov
    }
    }

    return Rcpp::List::create(); // never reaches
  }

  inline SEXP sfg_multipoint(
      SEXP& x,
      Rcpp::StringVector& cols
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
        SEXP xc = Rcpp::clone( x );
        Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
        return sfg_multipoint( im, cols );
      } else {
        // #nocov start
        Rcpp::warning("sfheaders - ignoring geometry_columns argument");
        Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
        return sfg_multipoint( iv );
        // #nocov end
      }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
        SEXP xc = Rcpp::clone( x );
        Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
        return sfg_multipoint( nm, cols );
      } else {
        // #nocov start
        Rcpp::warning("sfheaders - ignoring geometry_columns argument");
        Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
        return sfg_multipoint( nv );
        // #nocov end
      }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_multipoint( df, cols );
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_MULTIPOINT type");  // #nocov
    }
    }

    return Rcpp::List::create(); // never reaches
  }


  inline SEXP sfg_multipoint(
      SEXP& x
  ) {
    switch ( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
        SEXP xc = Rcpp::clone( x );
        Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
        return sfg_multipoint( im );
      } else {
        Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
        return sfg_multipoint( iv );
      }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
        SEXP xc = Rcpp::clone( x );
        Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
        return sfg_multipoint( nm );
      } else {
        Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
        return sfg_multipoint( nv );
      }
    }
    case VECSXP: {
    if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_multipoint( df );
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_MULTIPOINT type");
    }
    }
    return x; // never reaches
  }

  inline SEXP sfg_multipoint(
    SEXP& x,
    SEXP& cols
  ) {
    if( Rf_isNull( cols ) ) {
      return sfg_multipoint( x );
    }
    switch( TYPEOF( cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( cols );
      return sfg_multipoint( x, iv );
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( cols );
      return sfg_multipoint( x, sv );
    }
    default: {
      Rcpp::stop("sfheaders - unknown column types");   // #nocov
    }
    }
    return Rcpp::List::create(); // never reaches
  }

} // sfg
} // sfheaders


#endif
