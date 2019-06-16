#ifndef R_SFHEADERS_SFG_MULTIPOINT_H
#define R_SFHEADERS_SFG_MULTIPOINT_H

#include <Rcpp.h>
#include "sfheaders/shapes/line/line.hpp"
#include "sfheaders/sfg/sfg_attributes.hpp"
#include "sfheaders/sfg/sfg_dimension.hpp"

namespace sfheaders {
namespace sfg {


  /*
   * assumes columns are in lon/lat/z/m order
   */
  inline SEXP to_multipoint(
      Rcpp::IntegerMatrix& im
  ) {
    size_t n_col = im.ncol();
    std::string dim = sfheaders::sfg::sfg_dimension( n_col );

    std::string geom_type = "MULTIPOINT";
    im.attr("class") = sfheaders::sfg::sfg_attributes( dim, geom_type );

    return im;
  }


  inline SEXP to_multipoint(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& cols
  ) {
    Rcpp::IntegerMatrix im2 = sfheaders::shapes::get_line( im, cols );
    return to_multipoint( im2 );
  }

  inline SEXP to_multipoint(
      Rcpp::NumericMatrix& nm
  ) {

    size_t n_col = nm.ncol();
    std::string dim = sfheaders::sfg::sfg_dimension( n_col );

    std::string geom_type = "MULTIPOINT";
    nm.attr("class") = sfheaders::sfg::sfg_attributes(dim, geom_type);

    return nm;
  }

  inline SEXP to_multipoint(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& cols
  ) {

    Rcpp::NumericMatrix nm2 = sfheaders::shapes::get_line( nm, cols );
    return to_multipoint( nm2 );
  }

  // expects only lon/lat/z/m columns
  inline SEXP to_multipoint(
      Rcpp::DataFrame& df
  ) {
    // need to extract each column-vector, then create a numeric vector from those
    Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( df );
    return to_multipoint( nm );
  }

  inline SEXP to_multipoint(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& cols
  ) {
    Rcpp::NumericMatrix nm = sfheaders::shapes::get_line( df, cols );
    return to_multipoint( nm );
  }

inline SEXP to_multipoint(
    SEXP& x,
    Rcpp::IntegerVector& cols
  ) {
    // with string columns it must be a data.frame(?)

    return Rcpp::List::create(); // never reaches
  }


  inline SEXP to_multipoint(
      SEXP& x
  ) {
    // switch on type of x
    switch ( TYPEOF( x ) ) {
    case INTSXP: {
    if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return to_multipoint( im );
    }
    case REALSXP: {
    if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return to_multipoint( nm );
    }
    case VECSXP: {
    if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return to_multipoint( df );
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_MULTIPOINT type");
    }
    }
    return x; // never reaches
  }

  inline SEXP to_multipoint(
    SEXP& x,
    SEXP& cols
  ) {

    return Rcpp::List::create(); // never reaches
  }

} // sfg
} // sfheaders


#endif
