#ifndef R_SFHEADERS_SF_MULTIPOLYGON_H
#define R_SFHEADERS_SF_MULTIPOLYGON_H

#include <Rcpp.h>
#include "sfheaders/utils/sexp/sexp.hpp"
#include "sfheaders/sf/sf_utils.hpp"
#include "sfheaders/sfc/multipolygon/sfc_multipolygon.hpp"
#include "sfheaders/utils/unique/unique_ids.hpp"
#include "sfheaders/shapes/shapes.hpp"

namespace sfheaders {
namespace sf {

inline SEXP sf_multipolygon(
    SEXP& x,
    SEXP& geometry_cols,
    SEXP& multipolygon_id,
    SEXP& polygon_id,
    SEXP& linestring_id,
    bool close = true
) {
  Rcpp::List sfc = sfheaders::sfc::sfc_multipolygon( x, geometry_cols, multipolygon_id, polygon_id, linestring_id, close );

  SEXP ids = sfheaders::utils::get_ids( x, multipolygon_id );
  Rcpp::DataFrame sf = sfheaders::sf::make_sf( sfc, ids );
  return sf;
}

inline SEXP sf_multipolygon(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& geometry_cols,
    SEXP& multiline_ids,
    Rcpp::String& polygon_ids,
    Rcpp::String& line_ids,
    Rcpp::StringVector& property_cols,
    bool close = true
) {
  Rcpp::IntegerMatrix polygon_positions = sfheaders::utils::id_positions( multiline_ids );
  Rcpp::IntegerVector row_idx = polygon_positions( Rcpp::_, 0 );
  Rcpp::StringVector df_names = df.names();
  Rcpp::IntegerVector property_idx = sfheaders::utils::where_is( property_cols, df_names );
  Rcpp::List sfc = sfheaders::sfc::sfc_multipolygon( df, geometry_cols, polygon_ids, line_ids, polygon_positions );

  return sfheaders::sf::create_sf( df, sfc, property_cols, property_idx, row_idx );
}

inline SEXP sf_multipolygon(
    Rcpp::DataFrame& df,
    Rcpp::IntegerVector& geometry_cols,
    SEXP& multiline_ids,
    int& polygon_id,
    int& linestring_id,
    Rcpp::IntegerVector& property_idx,
    bool close = true
) {

  // get the property cols as a string_vector so we get the column names
  Rcpp::StringVector df_names = df.names();
  Rcpp::StringVector property_cols = df_names[ property_idx ];
  Rcpp::StringVector str_geometry_cols = df_names[ geometry_cols ];
  Rcpp::String str_linestring_id = df_names[ linestring_id ];
  Rcpp::String str_polygon_id = df_names[ polygon_id ];

  return sf_multipolygon( df, str_geometry_cols, multiline_ids, str_polygon_id, str_linestring_id, property_cols, close );
}

inline SEXP sf_multipolygon(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& geometry_cols,
    Rcpp::String& multipolygon_id,
    Rcpp::String& polygon_id,
    Rcpp::String& linestring_id,
    bool close = true
) {

  Rcpp::StringVector df_names = df.names();
  SEXP multiline_ids = df[ multipolygon_id ];
  Rcpp::StringVector cols = sfheaders::utils::concatenate_vectors( geometry_cols, polygon_id );
  Rcpp::StringVector cols2 = sfheaders::utils::concatenate_vectors( cols, linestring_id );
  Rcpp::StringVector property_cols = sfheaders::utils::other_columns( df_names, cols2 );
  return sf_multipolygon( df, geometry_cols, multiline_ids, polygon_id, linestring_id, property_cols, close );
}

inline SEXP sf_multipolygon(
    Rcpp::DataFrame& df,
    Rcpp::IntegerVector& geometry_cols,
    int& multipolygon_id,
    int& polygon_id,
    int& linestring_id,
    bool close = true
) {

  Rcpp::StringVector df_names = df.names();
  Rcpp::StringVector str_geometry_cols = df_names[ geometry_cols ];
  Rcpp::String multipolygonline_id = df_names[ multipolygon_id ];
  Rcpp::String multiline_id = df_names[ polygon_id ];
  Rcpp::String line_id = df_names[ linestring_id ];
  return sf_multipolygon( df, str_geometry_cols, multipolygonline_id, multiline_id, line_id, close );
}

inline SEXP sf_multipolygon(
    Rcpp::IntegerMatrix& im,
    Rcpp::IntegerVector& geometry_cols,
    int& multipolygon_id,
    int& polygon_id,
    int& linestring_id,
    bool close = true
) {

  sfheaders::utils::column_exists( im, polygon_id );
  Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );
  return sf_multipolygon( df, geometry_cols, multipolygon_id, polygon_id, linestring_id, close );
}

inline SEXP sf_multipolygon(
    Rcpp::NumericMatrix& nm,
    Rcpp::IntegerVector& geometry_cols,
    int& multipolygon_id,
    int& polygon_id,
    int& linestring_id,
    bool close = true
) {
  Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );
  return sf_multipolygon( df, geometry_cols, multipolygon_id, polygon_id, linestring_id, close );
}

inline SEXP sf_multipolygon(
    Rcpp::IntegerMatrix& im,
    Rcpp::StringVector& geometry_cols,
    Rcpp::String& multipolygon_id,
    Rcpp::String& polygon_id,
    Rcpp::String& linestring_id,
    bool close = true
) {
  Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );

  Rcpp::StringVector df_names = df.names();
  Rcpp::StringVector cols = sfheaders::utils::concatenate_vectors( geometry_cols, linestring_id );
  Rcpp::StringVector cols2 = sfheaders::utils::concatenate_vectors( cols, polygon_id );
  Rcpp::StringVector cols3 = sfheaders::utils::concatenate_vectors( cols, multipolygon_id );
  Rcpp::StringVector property_cols = sfheaders::utils::other_columns( df_names, cols3 );

  SEXP multiline_ids = df[ multipolygon_id ];
  return sf_multipolygon( df, geometry_cols, multiline_ids, polygon_id, linestring_id, property_cols, close );
}


inline SEXP sf_multipolygon(
    Rcpp::NumericMatrix& nm,
    Rcpp::StringVector& geometry_cols,
    Rcpp::String& multipolygon_id,
    Rcpp::String& polygon_id,
    Rcpp::String& linestring_id,
    bool close = true
) {
  Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );

  Rcpp::StringVector df_names = df.names();
  Rcpp::StringVector cols = sfheaders::utils::concatenate_vectors( geometry_cols, linestring_id );
  Rcpp::StringVector cols2 = sfheaders::utils::concatenate_vectors( cols, polygon_id );
  Rcpp::StringVector cols3 = sfheaders::utils::concatenate_vectors( cols, multipolygon_id );
  Rcpp::StringVector property_cols = sfheaders::utils::other_columns( df_names, cols3 );

  SEXP multiline_ids = df[ multipolygon_id ];
  return sf_multipolygon( df, geometry_cols, multiline_ids, polygon_id, linestring_id, property_cols, close );
}


// Rcpp::String& |
// int&          | -- both these are the column indexes
// when they become
// SEXP - they are the vector of id's.

inline SEXP sf_multipolygon(
    SEXP& x,
    Rcpp::IntegerVector& geometry_cols,
    int& multipolygon_id,
    int& polygon_id,
    int& linestring_id,
    bool close = true
) {
  switch( TYPEOF( x ) ) {
  case INTSXP: {
    if( Rf_isMatrix( x ) ) {
    SEXP xc = Rcpp::clone( x );
    Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
    return sf_multipolygon( im, geometry_cols, multipolygon_id,polygon_id, linestring_id, close );
  }
  }
  case REALSXP: {
    if( Rf_isMatrix( x ) ) {
    SEXP xc = Rcpp::clone( x );
    Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
    return sf_multipolygon( nm, geometry_cols, multipolygon_id,polygon_id, linestring_id, close );
  }
  }
  case VECSXP: {
    if( Rf_inherits( x, "data.frame" ) ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
    return sf_multipolygon( df, geometry_cols, multipolygon_id,polygon_id, linestring_id, close );
  }
  }
  default: {
    Rcpp::stop("sfheaders - unsupported linestring type"); // #nocov
  }
  }

  return Rcpp::List::create();
}

inline SEXP sf_multipolygon(
    SEXP& x,
    Rcpp::StringVector& geometry_cols,
    Rcpp::String& multipolygon_id,
    Rcpp::String& polygon_id,
    Rcpp::String& linestring_id,
    bool close = true
) {

  switch( TYPEOF( x ) ) {
  case INTSXP: {
    if( Rf_isMatrix( x ) ) {
    SEXP xc = Rcpp::clone( x );
    Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
    return sf_multipolygon( im, geometry_cols, multipolygon_id, polygon_id, linestring_id, close );
  }
  }
  case REALSXP: {
    if( Rf_isMatrix( x ) ) {
    SEXP xc = Rcpp::clone( x );
    Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
    return sf_multipolygon( nm, geometry_cols, multipolygon_id, polygon_id, linestring_id, close );
  }
  }
  case VECSXP: {
    if( Rf_inherits( x, "data.frame" ) ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
    return sf_multipolygon( df, geometry_cols, multipolygon_id, polygon_id, linestring_id, close );
  }
  }
  default: {
    Rcpp::stop("sfheaders - unsupported linestring type");
  }
  }

  return Rcpp::List::create();
}

inline SEXP sf_multipolygon(
    SEXP& x,
    SEXP& geometry_cols,
    SEXP& multipolygon_id,
    SEXP& polygon_id,
    SEXP& linestring_id,
    bool& close,
    bool& keep
) {

  if( !keep ) {
    return sf_multipolygon( x, geometry_cols, multipolygon_id, polygon_id, linestring_id, close );
  }


  // if all NULL, can we make any assumptions?
  // need at least outer-geometry id?
  if( Rf_isNull( geometry_cols ) ||
      Rf_isNull( linestring_id ) ||
      Rf_isNull( polygon_id) ||
      Rf_isNull( multipolygon_id)
    ) {

    // can't work out which are the geometry columns
    Rcpp::stop("sfheaders - please specify the geometry and id columns");

  } else {

    sfheaders::utils::geometry_column_check( geometry_cols );

    if ( TYPEOF( geometry_cols ) != TYPEOF( linestring_id ) ||
         TYPEOF( geometry_cols ) != TYPEOF( polygon_id ) ||
         TYPEOF( geometry_cols ) != TYPEOF( multipolygon_id ) ) {
      Rcpp::stop("sfheaders - polygon columns types are different");  // #nocov
    }

    switch( TYPEOF( geometry_cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv_geometry_cols = Rcpp::as< Rcpp::IntegerVector >( geometry_cols );
      Rcpp::IntegerVector iv_multipolygno_id_col = Rcpp::as< Rcpp::IntegerVector >( multipolygon_id );
      Rcpp::IntegerVector iv_polygon_id_col = Rcpp::as< Rcpp::IntegerVector >( polygon_id );
      Rcpp::IntegerVector iv_linestring_id_col = Rcpp::as< Rcpp::IntegerVector >( linestring_id );
      int i_multipolygon_id_col = iv_multipolygno_id_col[0];
      int i_polygon_id_col = iv_polygon_id_col[0];
      int i_linestring_id_col = iv_linestring_id_col[0];
      return sf_multipolygon( x, iv_geometry_cols, i_multipolygon_id_col, i_polygon_id_col, i_linestring_id_col, close );

    }
    case STRSXP: {
      Rcpp::StringVector sv_geometry_cols = Rcpp::as< Rcpp::StringVector >( geometry_cols );
      Rcpp::StringVector sv_multipolygno_id_col = Rcpp::as< Rcpp::StringVector >( multipolygon_id );
      Rcpp::StringVector sv_polygon_id_col = Rcpp::as< Rcpp::StringVector >( polygon_id );
      Rcpp::StringVector sv_linestring_id_col = Rcpp::as< Rcpp::StringVector >( linestring_id );
      Rcpp::String s_multipolygon_id_col = sv_multipolygno_id_col[0];
      Rcpp::String s_polygon_id_col = sv_polygon_id_col[0];
      Rcpp::String s_linestring_id_col = sv_linestring_id_col[0];
      return sf_multipolygon( x, sv_geometry_cols, s_multipolygon_id_col, s_polygon_id_col, s_linestring_id_col, close );
    }
    default: {
      Rcpp::stop("sfheaders - unsupported polygon type");  // #nocov
    }
    }
  }

  Rcpp::stop("sfheaders - polygon case not yet implemented"); // #nocov
  return Rcpp::List::create(); // ??
}

} // sf
} // sfheaders

#endif
