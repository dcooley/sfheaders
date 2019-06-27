#ifndef R_SFHEADERS_SFC_POINTS_H
#define R_SFHEADERS_SFC_POINTS_H

#include <Rcpp.h>
#include "sfheaders/sfg/point/sfg_point.hpp"
#include "sfheaders/bbox.hpp"
#include "sfheaders/sfc/sfc.hpp"
#include "sfheaders/sfc/sfc_attributes.hpp"

namespace sfheaders {
namespace sfc {

  inline SEXP to_points(
    Rcpp::IntegerMatrix& im,
    Rcpp::NumericVector& bbox
  ) {

    // given an 'sfg', attach sfc attributes
    // (if im.attr("class") != "sfg", attach it)

    // matrix; iterate through each row, get bbox, create sfg of each point
    // then an sfc of all other points
    size_t n_row = im.nrow();
    size_t n_col = im.ncol();
    size_t i;
    Rcpp::List sfc( n_row );

    for( i = 0; i < n_row; i++ ) {
      Rcpp::IntegerVector this_point = im( i, Rcpp::_ );
      sfheaders::bbox::calculate_bbox( bbox, this_point );
      sfc[i] = sfheaders::sfg::to_point( this_point );
    }

    std::string geom_type = "POINT";
    std::unordered_set< std::string > geometry_types{ "POINT" };
    std::string epsg = "";
    std::string proj4string = "";
    int n_empty = 0.0;
    double precision = 0.0;

    sfheaders::sfc::attach_sfc_attributes( sfc, geom_type, geometry_types, bbox, epsg, proj4string, n_empty, precision );
    return sfc;
  }


  inline SEXP to_points(
      Rcpp::NumericMatrix& nm,
      Rcpp::NumericVector& bbox
  ) {

    size_t n_row = nm.nrow();
    size_t n_col = nm.ncol();
    size_t i;
    Rcpp::List sfc( n_row );

    for( i = 0; i < n_row; i++ ) {
      Rcpp::NumericVector this_point = nm( i, Rcpp::_ );
      sfheaders::bbox::calculate_bbox( bbox, this_point );
      sfc[i] = sfheaders::sfg::to_point( this_point );
    }

    std::string geom_type = "POINT";
    std::unordered_set< std::string > geometry_types{ "POINT" };
    std::string epsg = "";
    std::string proj4string = "";
    int n_empty = 0.0;
    double precision = 0.0;

    sfheaders::sfc::attach_sfc_attributes( sfc, geom_type, geometry_types, bbox, epsg, proj4string, n_empty, precision );
    return sfc;
  }


  // inline SEXP to_points(
  //     Rcpp::DataFrame& df,
  //     Rcpp::NumericVector& bbox
  // ) {
  //
  //   Rcpp::StringVector df_names = df.names();
  //   size_t n_row = df.nrow();
  //   size_t n_col = df.ncol();
  //   size_t i;
  //   Rcpp::List sfc( n_row );
  //
  //   for( i = 0; i < n_row; i++ ) {
  //
  //     // subset df
  //     int start = i;
  //     int end = i;
  //
  //     Rcpp::Range rng( start, end );
  //     Rcpp::DataFrame df_subset = sfheaders::utils::subset_dataframe( df, df_names, start, end );
  //
  //     sfheaders::bbox::calculate_bbox( bbox, df_subset );
  //     sfc[i] = sfheaders::sfg::to_point( df_subset );
  //   }
  //
  //   std::string geom_type = "POINT";
  //   std::unordered_set< std::string > geometry_types{ "POINT" };
  //   std::string epsg = "";
  //   std::string proj4string = "";
  //   int n_empty = 0.0;
  //   double precision = 0.0;
  //
  //   sfheaders::sfc::attach_sfc_attributes( sfc, geom_type, geometry_types, bbox, epsg, proj4string, n_empty, precision );
  //   return sfc;
  // }

  inline SEXP to_points( SEXP& x ) {

    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();

    // switch on type of x
    switch ( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return to_points( im, bbox );
    // } else {
    //   Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
    //   return to_points( iv, bbox );
    }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return to_points( nm, bbox );
    // } else {
    //   Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
    //   return to_points( nv, bbox );
    }
    }
    // case VECSXP: { // data.frame && list?
    //   if( Rf_inherits( x, "data.frame") ) {
    //   Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
    //   return to_points( df, bbox );
    // } // else default
    // }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_POINT type");
    }
    }

    return x; // never reaches
  }


} // sfc
} // sfheaders

#endif
