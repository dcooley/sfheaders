#ifndef R_SFHEADERS_SFC_POINTS_H
#define R_SFHEADERS_SFC_POINTS_H

#include <Rcpp.h>
#include "sfheaders/sfg/point/sfg_point.hpp"
#include "sfheaders/bbox.hpp"
#include "sfheaders/sfc/sfc.hpp"

namespace sfheaders {
namespace sfc {

  inline SEXP to_points(
    Rcpp::IntegerMatrix& im
  ) {

    // given an 'sfg', attach sfc attributes
    // (if im.attr("class") != "sfg", attach it)

    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();

    std::string geom_type = "POINT";
    std::unordered_set< std::string > geometry_types{ geom_type };

    Rcpp::String epsg = NA_STRING;
    Rcpp::String proj4string = NA_STRING;
    int n_empty = 0;
    double precision = 0.0;

    // matrix; iterate through each row, get bbox, create sfg of each point
    // then an sfc of all other points
    size_t n_row = im.nrow();
    //size_t n_col = im.ncol();
    size_t i;
    Rcpp::List sfc( n_row );

    for( i = 0; i < n_row; i++ ) {
      Rcpp::IntegerVector this_point = im( i, Rcpp::_ );
      sfheaders::bbox::calculate_bbox( bbox, this_point );
      sfc[i] = sfheaders::sfg::to_point( this_point );
    }

    return sfheaders::sfc::to_sfc( sfc, geom_type, geometry_types, bbox, epsg, proj4string, n_empty, precision );
  }

  inline SEXP to_points(
    Rcpp::IntegerVector& iv
  ) {
    int n_col = iv.size();
    Rcpp::IntegerMatrix im(1, n_col);
    im(0, Rcpp::_ ) = iv;
    return to_points( im );
  }


  inline SEXP to_points(
      Rcpp::NumericMatrix& nm
  ) {

    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();

    std::string geom_type = "POINT";
    std::unordered_set< std::string > geometry_types{ geom_type };

    Rcpp::String epsg = NA_STRING;
    Rcpp::String proj4string = NA_STRING;
    int n_empty = 0;
    double precision = 0.0;

    size_t n_row = nm.nrow();
    //size_t n_col = nm.ncol();
    size_t i;
    Rcpp::List sfc( n_row );

    for( i = 0; i < n_row; i++ ) {
      Rcpp::NumericVector this_point = nm( i, Rcpp::_ );
      sfheaders::bbox::calculate_bbox( bbox, this_point );
      sfc[i] = sfheaders::sfg::to_point( this_point );
    }

    return sfheaders::sfc::to_sfc( sfc, geom_type, geometry_types, bbox, epsg, proj4string, n_empty, precision );
  }

  inline SEXP to_points(
      Rcpp::NumericVector& iv
  ) {
    int n_col = iv.size();
    Rcpp::NumericMatrix nm(1, n_col);
    nm(0, Rcpp::_ ) = iv;
    return to_points( nm );
  }


  inline SEXP to_points(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& cols
  ) {
    Rcpp::IntegerMatrix im2 = sfheaders::shapes::get_mat( im, cols );
    return to_points( im2 );
  }

  inline SEXP to_points(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& cols
  ) {
    Rcpp::IntegerMatrix im2 = sfheaders::shapes::get_mat( im, cols );
    return to_points( im2 );
  }

  inline SEXP to_points(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& cols
  ) {
    Rcpp::NumericMatrix nm2 = sfheaders::shapes::get_mat( nm, cols );
    return to_points( nm2 );
  }

  inline SEXP to_points(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& cols
  ) {
    Rcpp::NumericMatrix nm2 = sfheaders::shapes::get_mat( nm, cols );
    return to_points( nm2 );
  }

  // expects only lon/lat/z/m columns in correct order
  inline SEXP to_points(
      Rcpp::DataFrame& df
  ) {
    // expecting single-row data.frame
    Rcpp::NumericMatrix nv = sfheaders::shapes::get_mat( df );
    return to_points( nv );
  }

  inline SEXP to_points(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& cols
  ) {
    //Rcpp::NumericMatrix nm = sfheaders::utils::df_to_matrix( df );
    Rcpp::NumericMatrix nv = sfheaders::shapes::get_mat( df, cols );
    return to_points( nv );
  }

  inline SEXP to_points(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& cols
  ) {
    Rcpp::NumericMatrix nv = sfheaders::shapes::get_mat( df, cols );
    return to_points( nv );
  }

  inline SEXP to_points(
      SEXP& x
  ) {

    // switch on type of x
    switch ( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return to_points( im );
    } else {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
      return to_points( iv );
    }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return to_points( nm );
    } else {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
      return to_points( nv );
    }
    }
    case VECSXP: { // data.frame && list?
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return to_points( df );
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_POINT type");
    }
    }

    return x; // never reaches
  }

  inline SEXP to_points(
      SEXP& x,
      Rcpp::IntegerVector& cols
  ) {

    switch( TYPEOF( x ) ) {
    case INTSXP: {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return to_points( im, cols );
    }
    case REALSXP: {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return to_points( nm, cols );
    }
    case VECSXP: {
      // TODO - data.frame using numbers to index columns
      if ( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return to_points( df, cols );
    } //else - default
    }
    default: {
      Rcpp::stop("sfheaders - unknown point type");
    }
    }
    return Rcpp::List::create(); // never reaches
  }

  inline SEXP to_points(
      SEXP& x,
      Rcpp::StringVector& cols
  ) {
    // with string columns it must be a data.frame(?)

    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
    return to_points( df, cols );
  }


  /*
   * Unknown x and col types
   * First switch based on column types
   */
  inline SEXP to_points(
      SEXP& x,
      SEXP& cols
  ) {
    if( Rf_isNull( cols ) ) {
      return to_points( x );
    }
    switch( TYPEOF( cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector int_cols = Rcpp::as< Rcpp::IntegerVector >( cols );
      return to_points( x, int_cols );
    }
    case STRSXP: {
      Rcpp::StringVector str_cols = Rcpp::as< Rcpp::StringVector >( cols );
      return to_points( x, str_cols );
    }
    default: {
      Rcpp::stop("sfheaders - unknown column types");
    }
    }
    return Rcpp::List::create(); // never reaches
  }



} // sfc
} // sfheaders

#endif
