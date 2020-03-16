#ifndef R_SFHEADERS_SFG_DIMENSION_H
#define R_SFHEADERS_SFG_DIMENSION_H

#include <Rcpp.h>

namespace sfheaders {
namespace sfg {

  inline void dimension_check( R_xlen_t& n ) {
    if( n < 2 || n > 4 ) {
      Rcpp::stop("sfheaders - invalid dimension ");
    }
  }

  // re-write
  // it can be XYM, and we'll know from R based on the x, y, m columns specified.
  // but if none are specified, and just 3 columns, it will defualt to XYZ
  //
  // for c++ will need an overloaded function, or a flag, to say 'm-first',
  // and R will use something similar after the x, y, m args are defined
  // then enter teh appropriate C++ function.


  inline std::string sfg_dimension( R_xlen_t& n, bool m_only ) {
    dimension_check( n );
    std::string dim = "XY";

    // TODO: is "XYM" a valid dimension?
    switch ( n ) {
    case 3: {
      if( m_only ) {
        return "XYM";
      }
      return "XYZ";
    }
    case 4: {
      return "XYZM";
    }
    }
    return dim;
  }

  inline std::string sfg_dimension( Rcpp::IntegerVector& iv, bool m_only ) {
    R_xlen_t n = iv.size();
    return sfg_dimension( n, m_only );
  }

  inline std::string sfg_dimension( Rcpp::NumericVector& nv, bool m_only ) {
    R_xlen_t n = nv.size();
    return sfg_dimension( n, m_only );
  }

  inline std::string sfg_dimension( Rcpp::IntegerMatrix& im, bool m_only ) {
    R_xlen_t n_col = im.ncol();
    return sfg_dimension( n_col, m_only );
  }

  inline std::string sfg_dimension( Rcpp::NumericMatrix& nm, bool m_only ) {
    R_xlen_t n_col = nm.ncol();
    return sfg_dimension( n_col, m_only );
  }

  inline std::string sfg_dimension( Rcpp::DataFrame& df, bool m_only ) {
    R_xlen_t n_col = df.ncol();
    return sfg_dimension( n_col, m_only );
  }

  inline std::string sfg_dimension( SEXP x, bool m_only ) {

    switch ( TYPEOF( x ) ) {
    case INTSXP: {
    if( Rf_isMatrix( x ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return sfg_dimension( im, m_only );
    } else {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
      return sfg_dimension( iv, m_only );
    }
    }
    case REALSXP: {
    if( Rf_isMatrix( x ) ) {
      Rcpp::NumericMatrix im = Rcpp::as< Rcpp::NumericMatrix >( x );
      return sfg_dimension( im, m_only );
    } else {
      Rcpp::NumericVector iv = Rcpp::as< Rcpp::NumericVector >( x );
      return sfg_dimension( iv, m_only );
    }
    }
    case VECSXP: { // data.frame && list?
    if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_dimension( df, m_only );
    } else if ( Rf_isNewList( x ) ) {
      // we can just get the first element, because by this point
      // all the elements should have been made correctly (?)
      Rcpp::List lst = Rcpp::as< Rcpp::List >( x );
      SEXP list_element = lst[ 0 ];
      return sfg_dimension( list_element, m_only );
    } // else default


    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg type"); // #nocov
    }
    }

    return ""; // never reaches
  }

} // sfg
} // sfheaders

#endif
