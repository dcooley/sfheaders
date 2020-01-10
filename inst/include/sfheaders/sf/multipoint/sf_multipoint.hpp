#ifndef R_SFHEADERS_SF_MULTIPOINT_H
#define R_SFHEADERS_SF_MULTIPOINT_H

#include <Rcpp.h>
#include "sfheaders/utils/sexp/sexp.hpp"
#include "sfheaders/sf/sf_utils.hpp"
#include "sfheaders/sfc/multipoint/sfc_multipoint.hpp"
#include "sfheaders/utils/unique/unique_ids.hpp"
#include "sfheaders/shapes/shapes.hpp"

namespace sfheaders {
namespace sf {

inline SEXP sf_multipoint(
    SEXP& x,
    SEXP& geometry_cols,
    SEXP& multipoint_id
) {
  Rcpp::List sfc = sfheaders::sfc::sfc_multipoint( x, geometry_cols, multipoint_id );

  SEXP ids = sfheaders::utils::get_ids( x, multipoint_id );
  Rcpp::DataFrame sf = sfheaders::sf::make_sf( sfc, ids );
  return sf;
}

inline SEXP sf_multipoint(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& geometry_cols,
    SEXP& line_ids,
    Rcpp::StringVector& property_cols
) {
  Rcpp::IntegerMatrix line_positions = sfheaders::utils::id_positions( line_ids );
  Rcpp::IntegerVector row_idx = line_positions( Rcpp::_, 0 );
  Rcpp::StringVector df_names = df.names();
  Rcpp::IntegerVector property_idx = sfheaders::utils::where_is( property_cols, df_names );
  Rcpp::List sfc = sfheaders::sfc::sfc_multipoint( df, geometry_cols, line_positions );

  return sfheaders::sf::create_sf( df, sfc, property_cols, property_idx, row_idx );
}

inline SEXP sf_multipoint(
    Rcpp::DataFrame& df,
    Rcpp::IntegerVector& geometry_cols,
    SEXP& line_ids,
    Rcpp::IntegerVector& property_idx
) {

  // get the property cols as a string_vector so we get the column names
  Rcpp::StringVector df_names = df.names();
  Rcpp::StringVector property_cols = df_names[ property_idx ];
  Rcpp::StringVector str_geometry_cols = df_names[ geometry_cols ];
  return sf_multipoint( df, str_geometry_cols, line_ids, property_cols );
}

inline SEXP sf_multipoint(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& geometry_cols,
    Rcpp::String& multipoint_id
) {

  Rcpp::StringVector df_names = df.names();
  Rcpp::StringVector cols = sfheaders::utils::concatenate_vectors( geometry_cols, multipoint_id );
  Rcpp::StringVector property_cols = sfheaders::utils::other_columns( df_names, cols );

  SEXP line_ids = df[ multipoint_id ];
  return sf_multipoint( df, geometry_cols, line_ids, property_cols );
}

inline SEXP sf_multipoint(
    Rcpp::DataFrame& df,
    Rcpp::IntegerVector& geometry_cols,
    int& multipoint_id
) {

  Rcpp::StringVector df_names = df.names();
  Rcpp::StringVector str_geometry_cols = df_names[ geometry_cols ];
  Rcpp::String line_id = df_names[ multipoint_id ];
  return sf_multipoint( df, str_geometry_cols, line_id );
}

inline SEXP sf_multipoint(
    Rcpp::IntegerMatrix& im,
    Rcpp::IntegerVector& geometry_cols,
    int& multipoint_id
) {
  sfheaders::utils::column_exists( im, multipoint_id );
  Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );
  return sf_multipoint( df, geometry_cols, multipoint_id );
}

inline SEXP sf_multipoint(
    Rcpp::NumericMatrix& nm,
    Rcpp::IntegerVector& geometry_cols,
    int& multipoint_id
) {
  sfheaders::utils::column_exists( nm, multipoint_id );
  Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );
  return sf_multipoint( df, geometry_cols, multipoint_id );
}

inline SEXP sf_multipoint(
    Rcpp::IntegerMatrix& im,
    Rcpp::StringVector& geometry_cols,
    Rcpp::String& multipoint_id
) {
  Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );

  // Rcpp::StringVector df_names = df.names();
  // Rcpp::StringVector cols = sfheaders::utils::concatenate_vectors( geometry_cols, multipoint_id );
  // Rcpp::StringVector property_cols = sfheaders::utils::other_columns( df_names, cols );
  //SEXP line_ids = df[ multipoint_id ];
  //return sf_multipoint( df, geometry_cols, line_ids, property_cols );
  return sf_multipoint( df, geometry_cols, multipoint_id );
}

inline SEXP sf_multipoint(
    Rcpp::NumericMatrix& nm,
    Rcpp::StringVector& geometry_cols,
    Rcpp::String& multipoint_id
) {
  Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );
  //
  //     Rcpp::StringVector df_names = df.names();
  //     Rcpp::StringVector cols = sfheaders::utils::concatenate_vectors( geometry_cols, multipoint_id );
  //     Rcpp::StringVector property_cols = sfheaders::utils::other_columns( df_names, cols );
  //
  //     SEXP line_ids = df[ multipoint_id ];
  //    return sf_multipoint( df, geometry_cols, line_ids, property_cols );
  return sf_multipoint( df, geometry_cols, multipoint_id );
}

inline SEXP sf_multipoint(
    SEXP& x,
    Rcpp::IntegerVector& geometry_cols,
    int& multipoint_id
) {
  switch( TYPEOF( x ) ) {
  case INTSXP: {
    if( Rf_isMatrix( x ) ) {
    SEXP xc = Rcpp::clone( x );
    Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
    return sf_multipoint( im, geometry_cols, multipoint_id );
  }
  }
  case REALSXP: {
    if( Rf_isMatrix( x ) ) {
    SEXP xc = Rcpp::clone( x );
    Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
    return sf_multipoint( nm, geometry_cols, multipoint_id );
  }
  }
  case VECSXP: {
    if( Rf_inherits( x, "data.frame" ) ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
    return sf_multipoint( df, geometry_cols, multipoint_id );
  }
  }
  default: {
    Rcpp::stop("sfheaders - unsupported linestring type"); // #nocov
  }
  }

  return Rcpp::List::create();
}

inline SEXP sf_multipoint(
    SEXP& x,
    Rcpp::StringVector& geometry_cols,
    Rcpp::String& multipoint_id
) {

  switch( TYPEOF( x ) ) {
  case INTSXP: {
    if( Rf_isMatrix( x ) ) {
    SEXP xc = Rcpp::clone( x );
    Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
    return sf_multipoint( im, geometry_cols, multipoint_id );
  }
  }
  case REALSXP: {
    if( Rf_isMatrix( x ) ) {
    SEXP xc = Rcpp::clone( x );
    Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
    return sf_multipoint( nm, geometry_cols, multipoint_id );
  }
  }
  case VECSXP: {
    if( Rf_inherits( x, "data.frame" ) ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
    return sf_multipoint( df, geometry_cols, multipoint_id );
  }
  }
  default: {
    Rcpp::stop("sfheaders - unsupported linestring type");
  }
  }

  return Rcpp::List::create();
}

inline SEXP sf_multipoint(
    SEXP& x,
    SEXP& geometry_cols,
    SEXP& multipoint_id,
    bool& keep
) {
  if( !keep ) {
    return sf_multipoint( x, geometry_cols, multipoint_id );
  }

  // TODO:
  // - get line_positions.
  // - get call sfc_linestring with line_positions as an argument
  //
  // To get line_positions, need to know the types of x and multipoint_id column

  if( Rf_isNull( geometry_cols ) || Rf_isNull( multipoint_id ) ) {

    // can't work out which are the geometry columns
    Rcpp::stop("sfheaders - please specify the geometry and id columns");

  } else {
    // we have all the columns sorted, so the 'properties' are all the other columns
    //
    sfheaders::utils::geometry_column_check( geometry_cols );

    if ( TYPEOF( geometry_cols ) != TYPEOF( multipoint_id ) ) {
      Rcpp::stop("sfheaders - linestring columns types are different");
    }

    switch( TYPEOF( geometry_cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv_geometry_cols = Rcpp::as< Rcpp::IntegerVector >( geometry_cols );
      Rcpp::IntegerVector iv_multipoint_id_col = Rcpp::as< Rcpp::IntegerVector >( multipoint_id );
      int i_multipoint_id_col = iv_multipoint_id_col[0];
      return sf_multipoint( x, iv_geometry_cols, i_multipoint_id_col );
    }
    case STRSXP: {
      Rcpp::StringVector sv_geometry_cols = Rcpp::as< Rcpp::StringVector >( geometry_cols );
      Rcpp::StringVector sv_multipoint_id_col = Rcpp::as< Rcpp::StringVector >( multipoint_id );
      Rcpp::String s_multipoint_id_col = sv_multipoint_id_col[0];
      return sf_multipoint( x, sv_geometry_cols, s_multipoint_id_col );
    }
    default: {
      Rcpp::stop("sfheaders - unsupported linestring type");  // #nocov
    }
    }
  }

  return Rcpp::List::create(); // ??

}

} // sfc
} // sfheaders

#endif
