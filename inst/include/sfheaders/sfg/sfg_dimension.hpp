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


  inline std::string sfg_dimension(
      R_xlen_t& n,
      std::string xyzm = ""
  ) {

    if( !xyzm.empty() ) {
      return xyzm;
    }

    dimension_check( n );
    std::string dim = "XY";

    switch ( n ) {
    case 3: {
      return "XYZ";  // default to XYZ if dimension is not provided, and n == 3
    }
    case 4: {
      return "XYZM";
    }
    }
    return dim;
  }

  inline std::string sfg_dimension( Rcpp::IntegerVector& iv, std::string xyzm = "" ) {
    R_xlen_t n = iv.size();
    return sfg_dimension( n, xyzm );
  }

  inline std::string sfg_dimension( Rcpp::NumericVector& nv, std::string xyzm = "" ) {
    R_xlen_t n = nv.size();
    return sfg_dimension( n, xyzm );
  }

  inline std::string sfg_dimension( Rcpp::IntegerMatrix& im, std::string xyzm = "" ) {
    R_xlen_t n_col = im.ncol();
    return sfg_dimension( n_col, xyzm );
  }

  inline std::string sfg_dimension( Rcpp::NumericMatrix& nm, std::string xyzm = "" ) {
    R_xlen_t n_col = nm.ncol();
    return sfg_dimension( n_col, xyzm );
  }

  inline std::string sfg_dimension( Rcpp::DataFrame& df, std::string xyzm = "" ) {
    R_xlen_t n_col = df.ncol();
    return sfg_dimension( n_col, xyzm );
  }

  inline std::string sfg_dimension( SEXP x, std::string xyzm = "" ) {

    switch ( TYPEOF( x ) ) {
    case INTSXP: {
    if( Rf_isMatrix( x ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return sfg_dimension( im, xyzm );
    } else {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
      return sfg_dimension( iv, xyzm );
    }
    }
    case REALSXP: {
    if( Rf_isMatrix( x ) ) {
      Rcpp::NumericMatrix im = Rcpp::as< Rcpp::NumericMatrix >( x );
      return sfg_dimension( im, xyzm );
    } else {
      Rcpp::NumericVector iv = Rcpp::as< Rcpp::NumericVector >( x );
      return sfg_dimension( iv, xyzm );
    }
    }
    case VECSXP: { // data.frame && list?
    if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_dimension( df, xyzm );
    } else if ( Rf_isNewList( x ) ) {
      // we can just get the first element, because by this point
      // all the elements should have been made correctly (?)
      Rcpp::List lst = Rcpp::as< Rcpp::List >( x );
      SEXP list_element = lst[ 0 ];
      return sfg_dimension( list_element, xyzm );
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
