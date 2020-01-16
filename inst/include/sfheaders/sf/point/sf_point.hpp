#ifndef R_SFHEADERS_SF_POINT_H
#define R_SFHEADERS_SF_POINT_H

#include <Rcpp.h>
#include "sfheaders/utils/sexp/sexp.hpp"
#include "sfheaders/sf/sf_utils.hpp"
#include "sfheaders/sfc/point/sfc_point.hpp"
#include "sfheaders/utils/unique/unique_ids.hpp"
#include "sfheaders/shapes/shapes.hpp"

namespace sfheaders {
namespace sf {

  inline SEXP sf_point(
      SEXP& x,
      SEXP& geometry_cols
  ) {

    Rcpp::List sfc = sfheaders::sfc::sfc_point( x, geometry_cols );

    Rcpp::DataFrame sf = sfheaders::sf::make_sf( sfc );
    return sf;

  }

  inline SEXP sf_point(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& geometry_cols,
      Rcpp::StringVector& property_cols
  ) {

    Rcpp::IntegerVector row_idx = Rcpp::seq( 0, df.nrow() - 1 );
    Rcpp::StringVector df_names = df.names();
    Rcpp::IntegerVector property_idx = sfheaders::utils::where_is( property_cols, df_names );
    Rcpp::List sfc = sfheaders::sfc::sfc_point( df, geometry_cols );

    return sfheaders::sf::create_sf( df, sfc, property_cols, property_idx, row_idx );
  }

  inline SEXP sf_point(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& geometry_cols,
      Rcpp::IntegerVector& property_idx
  ) {

    // get the property cols as a string_vector so we get the column names
    Rcpp::StringVector df_names = df.names();
    Rcpp::StringVector property_cols = df_names[ property_idx ];
    Rcpp::StringVector str_geometry_cols = df_names[ geometry_cols ];
    return sf_point( df, str_geometry_cols, property_cols );
  }

  inline SEXP sf_point(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& geometry_cols
  ) {

    Rcpp::StringVector df_names = df.names();
    Rcpp::StringVector property_cols = sfheaders::utils::other_columns( df_names, geometry_cols );
    return sf_point( df, geometry_cols, property_cols );
  }

  inline SEXP sf_point(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& geometry_cols
  ) {

    Rcpp::StringVector df_names = df.names();
    Rcpp::StringVector str_geometry_cols = df_names[ geometry_cols ];
    return sf_point( df, str_geometry_cols );
  }

  inline SEXP sf_point(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& geometry_cols
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );
    return sf_point( df, geometry_cols );
  }

  inline SEXP sf_point(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& geometry_cols
  ) {

    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );
    return sf_point( df, geometry_cols );
  }

  inline SEXP sf_point(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& geometry_cols
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );
    return sf_point( df, geometry_cols );
  }

  inline SEXP sf_point(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& geometry_cols
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );
    return sf_point( df, geometry_cols );
  }

  inline SEXP sf_point(
      SEXP& x,
      Rcpp::IntegerVector& geometry_cols
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
      SEXP xc = Rcpp::clone( x );
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
      return sf_point( im, geometry_cols );
    }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
      SEXP xc = Rcpp::clone( x );
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
      return sf_point( nm, geometry_cols );
    }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sf_point( df, geometry_cols );
    }
    }
    default: {
      Rcpp::stop("sfheaders - unsupported linestring type"); // #nocov
    }
    }

    return Rcpp::List::create();
  }

  inline SEXP sf_point(
      SEXP& x,
      Rcpp::StringVector& geometry_cols
  ) {

    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
      SEXP xc = Rcpp::clone( x );
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
      return sf_point( im, geometry_cols );
    }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
      SEXP xc = Rcpp::clone( x );
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
      return sf_point( nm, geometry_cols );
    }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sf_point( df, geometry_cols );
    }
    }
    default: {
      Rcpp::stop("sfheaders - unsupported point type");  // #nocov
    }
    }

    return Rcpp::List::create();
  }

  inline SEXP sf_point(
      SEXP& x,
      SEXP& geometry_cols,
      bool& keep
  ) {
    if( !keep ) {
      return sf_point( x, geometry_cols );
    }

    if( Rf_isNull( geometry_cols ) ) {
      Rcpp::stop("sfheaders - please specify the geometry columns x, y (z, (m)) when keep = TRUE");
    }

    sfheaders::utils::geometry_column_check( geometry_cols );

    switch( TYPEOF( geometry_cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv_geometry_cols = Rcpp::as< Rcpp::IntegerVector >( geometry_cols );
      return sf_point( x, iv_geometry_cols );
    }
    case STRSXP: {
      Rcpp::StringVector sv_geometry_cols = Rcpp::as< Rcpp::StringVector >( geometry_cols );
      return sf_point( x, sv_geometry_cols );
    }
    default: {
      Rcpp::stop("sfheaders - unsupported point type");  // #nocov
    }
    }

    return Rcpp::List::create(); // ??
  }


} // sf
} // sfheaders

#endif
