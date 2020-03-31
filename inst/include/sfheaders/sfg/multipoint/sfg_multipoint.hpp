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
      Rcpp::IntegerMatrix& im,
      std::string xyzm
  ) {
    sfheaders::sfg::make_sfg( im, sfheaders::sfg::SFG_MULTIPOINT, xyzm );
    return im;
  }

  inline SEXP sfg_multipoint(
      Rcpp::IntegerVector& iv,
      std::string xyzm
  ) {
    R_xlen_t n = iv.length();
    Rcpp::IntegerMatrix im( 1, n );
    im( 0, Rcpp::_ ) = iv;
    return sfg_multipoint( im, xyzm );
  }

  inline SEXP sfg_multipoint(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& cols,
      std::string xyzm
  ) {
    Rcpp::IntegerMatrix im2 = sfheaders::shapes::get_mat( im, cols );
    return sfg_multipoint( im2, xyzm );
  }

  inline SEXP sfg_multipoint(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& cols,
      std::string xyzm
  ) {
    Rcpp::IntegerMatrix im2 = sfheaders::shapes::get_mat( im, cols );
    return sfg_multipoint( im2, xyzm );
  }

  inline SEXP sfg_multipoint(
      Rcpp::NumericMatrix& nm,
      std::string xyzm
  ) {
    sfheaders::sfg::make_sfg( nm, sfheaders::sfg::SFG_MULTIPOINT, xyzm );
    return nm;
  }

  inline SEXP sfg_multipoint(
      Rcpp::NumericVector& nv,
      std::string xyzm
  ) {
    R_xlen_t n = nv.length();
    Rcpp::NumericMatrix nm( 1, n );
    nm( 0, Rcpp::_ ) = nv;
    return sfg_multipoint( nm, xyzm );
  }

  inline SEXP sfg_multipoint(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& cols,
      std::string xyzm
  ) {
    Rcpp::NumericMatrix nm2 = sfheaders::shapes::get_mat( nm, cols );
    return sfg_multipoint( nm2, xyzm );
  }

  inline SEXP sfg_multipoint(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& cols,
      std::string xyzm
  ) {
    Rcpp::NumericMatrix nm2 = sfheaders::shapes::get_mat( nm, cols );
    return sfg_multipoint( nm2, xyzm );
  }

  // expects only lon/lat/z/m columns
  inline SEXP sfg_multipoint(
      Rcpp::DataFrame& df,
      std::string xyzm
  ) {
    Rcpp::NumericMatrix nm = sfheaders::utils::df_to_matrix( df );
    return sfg_multipoint( nm, xyzm );
  }

  inline SEXP sfg_multipoint(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& cols,
      std::string xyzm
  ) {
    Rcpp::NumericMatrix nm = sfheaders::shapes::get_mat( df, cols );
    return sfg_multipoint( nm, xyzm );
  }

  inline SEXP sfg_multipoint(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& cols,
      std::string xyzm
  ) {
    Rcpp::NumericMatrix nm = sfheaders::shapes::get_mat( df, cols );
    return sfg_multipoint( nm, xyzm );
  }

inline SEXP sfg_multipoint(
    SEXP& x,
    Rcpp::IntegerVector& cols,
    std::string xyzm
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
        Rcpp::stop("sfheaders - expecting a matrix"); // #nocov
      } else {
        SEXP xc = Rcpp::clone( x );
        Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
        return sfg_multipoint( im, cols, xyzm );
      }
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
        Rcpp::stop("sfheaders - expecting a matrix"); // #nocov
      } else {
        SEXP xc = Rcpp::clone( x );
        Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
        return sfg_multipoint( nm, cols, xyzm );
      }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_multipoint( df, cols, xyzm );
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
      Rcpp::StringVector& cols,
      std::string xyzm
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
        SEXP xc = Rcpp::clone( x );
        Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
        return sfg_multipoint( im, cols, xyzm );
      } else {
        // #nocov start
        Rcpp::warning("sfheaders - ignoring geometry_columns argument");
        Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
        return sfg_multipoint( iv, xyzm );
        // #nocov end
      }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
        SEXP xc = Rcpp::clone( x );
        Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
        return sfg_multipoint( nm, cols, xyzm );
      } else {
        // #nocov start
        Rcpp::warning("sfheaders - ignoring geometry_columns argument");
        Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
        return sfg_multipoint( nv, xyzm );
        // #nocov end
      }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_multipoint( df, cols, xyzm );
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
      std::string xyzm
  ) {
    switch ( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
        SEXP xc = Rcpp::clone( x );
        Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
        return sfg_multipoint( im, xyzm );
      } else {
        Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
        return sfg_multipoint( iv, xyzm );
      }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
        SEXP xc = Rcpp::clone( x );
        Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
        return sfg_multipoint( nm, xyzm );
      } else {
        Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
        return sfg_multipoint( nv, xyzm );
      }
    }
    case VECSXP: {
    if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_multipoint( df, xyzm );
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
    SEXP& cols,
    std::string xyzm
  ) {
    if( Rf_isNull( cols ) ) {
      return sfg_multipoint( x, xyzm );
    }
    switch( TYPEOF( cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( cols );
      return sfg_multipoint( x, iv, xyzm );
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( cols );
      return sfg_multipoint( x, sv, xyzm );
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
