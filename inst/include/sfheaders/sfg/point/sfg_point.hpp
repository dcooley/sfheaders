#ifndef R_SFHEADERS_SFG_POINT_H
#define R_SFHEADERS_SFG_POINT_H

#include <Rcpp.h>
#include "sfheaders/shapes/shapes.hpp"
#include "sfheaders/sfg/sfg_attributes.hpp"
#include "sfheaders/sfg/sfg_dimension.hpp"

namespace sfheaders {
namespace sfg {

  inline SEXP to_point( Rcpp::IntegerVector& iv ) {
    // takes a vector of size >= 2 && size <= 4 (for z & m)
    // attaches sfg_POINT attributes
    size_t n = iv.size();
    std::string dim = sfheaders::sfg::sfg_dimension( n );
    std::string geom_type = "POINT";
    iv.attr("class") = sfheaders::sfg::sfg_attributes(dim, geom_type);
    return iv;
  }

  inline SEXP to_point( Rcpp::NumericVector& nv ) {
    // takes a vector of size >= 2 && size <= 4 (for z & m)
    // attaches sfg_POINT attributes
    size_t n = nv.size();
    std::string dim = sfheaders::sfg::sfg_dimension( n );
    std::string geom_type = "POINT";
    nv.attr("class") = sfheaders::sfg::sfg_attributes(dim, geom_type) ;
    return nv;
  }

  /*
   * assumes columns are in lon/lat/z/m order
   */
  inline SEXP to_point(
      Rcpp::IntegerMatrix& im
  ) {
    Rcpp::IntegerVector iv = sfheaders::shapes::get_point( im );
    return to_point( iv );
  }

  inline SEXP to_point(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& cols
  ) {
    Rcpp::IntegerMatrix im2 = sfheaders::shapes::get_point( im, cols );
    return to_point( im2 );
  }

  inline SEXP to_point(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& cols
  ) {
    Rcpp::IntegerMatrix im2 = sfheaders::shapes::get_point( im, cols );
    return to_point( im2 );
  }

  inline SEXP to_point(
      Rcpp::NumericMatrix& nm
  ) {
    Rcpp::NumericVector nv = sfheaders::shapes::get_point( nm );
    return to_point( nv );
  }

  inline SEXP to_point(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& cols
  ) {
    Rcpp::NumericMatrix nm2 = sfheaders::shapes::get_point( nm, cols );
    return to_point( nm2 );
  }

  inline SEXP to_point(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& cols
  ) {
    Rcpp::Rcout << "to_poitn( nm, cols ) " << std::endl;
    Rcpp::NumericMatrix nm2 = sfheaders::shapes::get_point( nm, cols );
    Rcpp::Rcout << "matrix made? " << std::endl;
    return to_point( nm2 );
  }

  // expects only lon/lat/z/m columns in correct order
  inline SEXP to_point(
      Rcpp::DataFrame& df
  ) {
    // expecting single-row data.frame
    Rcpp::NumericVector nv = sfheaders::shapes::get_point( df );
    return to_point( nv );
  }

  inline SEXP to_point(
    Rcpp::DataFrame& df,
    Rcpp::IntegerVector& cols
  ) {
    //Rcpp::NumericMatrix nm = sfheaders::utils::df_to_matrix( df );
    Rcpp::NumericVector nv = sfheaders::shapes::get_point( df, cols );
    return to_point( nv );
  }

  inline SEXP to_point(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& cols
  ) {
    Rcpp::NumericVector nv = sfheaders::shapes::get_point( df, cols );
    return to_point( nv );
  }

  inline SEXP to_point(
    SEXP& x
  ) {

    // switch on type of x
    switch ( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return to_point( im );
    } else {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
      return to_point( iv );
    }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::NumericMatrix im = Rcpp::as< Rcpp::NumericMatrix >( x );
      return to_point( im );
    } else {
      Rcpp::NumericVector iv = Rcpp::as< Rcpp::NumericVector >( x );
      return to_point( iv );
    }
    }
    case VECSXP: { // data.frame && list?
    if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return to_point( df );
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_POINT type");
    }
    }

    return x; // never reaches
  }

  inline SEXP to_point(
      SEXP& x,
      Rcpp::IntegerVector& cols
  ) {

    switch( TYPEOF( x ) ) {
    case INTSXP: {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return to_point( im, cols );
    }
    case REALSXP: {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return to_point( nm, cols );
    }
    case VECSXP: {
      // TODO - data.frame using numbers to index columns
      if ( Rf_inherits( x, "data.frame" ) ) {
        Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
        return to_point( df, cols );
      } //else - default
    }
    default: {
      Rcpp::stop("sfheaders - unknown point type");
    }
    }
    return Rcpp::List::create(); // never reaches
  }

  inline SEXP to_point(
      SEXP& x,
      Rcpp::StringVector& cols
  ) {
    // with string columns it must be a data.frame(?)

    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
    return to_point( df, cols );
  }


  /*
   * Unknown x and col types
   * First switch based on column types
   */
  inline SEXP to_point(
    SEXP& x,
    SEXP& cols
  ) {
    if( Rf_isNull( cols ) ) {
      return to_point( x );
    }
    switch( TYPEOF( cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector int_cols = Rcpp::as< Rcpp::IntegerVector >( cols );
      return to_point( x, int_cols );
    }
    case STRSXP: {
      Rcpp::StringVector str_cols = Rcpp::as< Rcpp::StringVector >( cols );
      return to_point( x, str_cols );
    }
    default: {
      Rcpp::stop("sfheaders - unknown column types");
    }
    }
    return Rcpp::List::create(); // never reaches
  }


} // sfg
} // sfheaders


#endif