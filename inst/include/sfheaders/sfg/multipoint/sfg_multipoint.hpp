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
      bool m_only
  ) {
    sfheaders::sfg::make_sfg( im, sfheaders::sfg::SFG_MULTIPOINT, m_only );
    return im;
  }

  inline SEXP sfg_multipoint(
      Rcpp::IntegerVector& iv,
      bool m_only
  ) {
    R_xlen_t n = iv.length();
    Rcpp::IntegerMatrix im( 1, n );
    im( 0, Rcpp::_ ) = iv;
    return sfg_multipoint( im, m_only );
  }

  inline SEXP sfg_multipoint(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& cols,
      bool m_only
  ) {
    Rcpp::IntegerMatrix im2 = sfheaders::shapes::get_mat( im, cols );
    return sfg_multipoint( im2, m_only );
  }

  inline SEXP sfg_multipoint(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& cols,
      bool m_only
  ) {
    Rcpp::IntegerMatrix im2 = sfheaders::shapes::get_mat( im, cols );
    return sfg_multipoint( im2, m_only );
  }

  inline SEXP sfg_multipoint(
      Rcpp::NumericMatrix& nm,
      bool m_only
  ) {
    sfheaders::sfg::make_sfg( nm, sfheaders::sfg::SFG_MULTIPOINT, m_only );
    return nm;
  }

  inline SEXP sfg_multipoint(
      Rcpp::NumericVector& nv,
      bool m_only
  ) {
    R_xlen_t n = nv.length();
    Rcpp::NumericMatrix nm( 1, n );
    nm( 0, Rcpp::_ ) = nv;
    return sfg_multipoint( nm, m_only );
  }

  inline SEXP sfg_multipoint(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& cols,
      bool m_only
  ) {
    Rcpp::NumericMatrix nm2 = sfheaders::shapes::get_mat( nm, cols );
    return sfg_multipoint( nm2, m_only );
  }

  inline SEXP sfg_multipoint(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& cols,
      bool m_only
  ) {
    Rcpp::NumericMatrix nm2 = sfheaders::shapes::get_mat( nm, cols );
    return sfg_multipoint( nm2, m_only );
  }

  // expects only lon/lat/z/m columns
  inline SEXP sfg_multipoint(
      Rcpp::DataFrame& df,
      bool m_only
  ) {
    Rcpp::NumericMatrix nm = sfheaders::utils::df_to_matrix( df );
    return sfg_multipoint( nm, m_only );
  }

  inline SEXP sfg_multipoint(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& cols,
      bool m_only
  ) {
    Rcpp::NumericMatrix nm = sfheaders::shapes::get_mat( df, cols );
    return sfg_multipoint( nm, m_only );
  }

  inline SEXP sfg_multipoint(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& cols,
      bool m_only
  ) {
    Rcpp::NumericMatrix nm = sfheaders::shapes::get_mat( df, cols );
    return sfg_multipoint( nm, m_only );
  }

inline SEXP sfg_multipoint(
    SEXP& x,
    Rcpp::IntegerVector& cols,
    bool m_only
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
        Rcpp::stop("sfheaders - expecting a matrix"); // #nocov
      } else {
        SEXP xc = Rcpp::clone( x );
        Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
        return sfg_multipoint( im, cols, m_only );
      }
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
        Rcpp::stop("sfheaders - expecting a matrix"); // #nocov
      } else {
        SEXP xc = Rcpp::clone( x );
        Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
        return sfg_multipoint( nm, cols, m_only );
      }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_multipoint( df, cols, m_only );
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
      bool m_only
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
        SEXP xc = Rcpp::clone( x );
        Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
        return sfg_multipoint( im, cols, m_only );
      } else {
        // #nocov start
        Rcpp::warning("sfheaders - ignoring geometry_columns argument");
        Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
        return sfg_multipoint( iv, m_only );
        // #nocov end
      }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
        SEXP xc = Rcpp::clone( x );
        Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
        return sfg_multipoint( nm, cols, m_only );
      } else {
        // #nocov start
        Rcpp::warning("sfheaders - ignoring geometry_columns argument");
        Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
        return sfg_multipoint( nv, m_only );
        // #nocov end
      }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_multipoint( df, cols, m_only );
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
      bool m_only
  ) {
    switch ( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
        SEXP xc = Rcpp::clone( x );
        Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
        return sfg_multipoint( im, m_only );
      } else {
        Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
        return sfg_multipoint( iv, m_only );
      }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
        SEXP xc = Rcpp::clone( x );
        Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
        return sfg_multipoint( nm, m_only );
      } else {
        Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
        return sfg_multipoint( nv, m_only );
      }
    }
    case VECSXP: {
    if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_multipoint( df, m_only );
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
    bool m_only
  ) {
    if( Rf_isNull( cols ) ) {
      return sfg_multipoint( x, m_only );
    }
    switch( TYPEOF( cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( cols );
      return sfg_multipoint( x, iv, m_only );
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( cols );
      return sfg_multipoint( x, sv, m_only );
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
