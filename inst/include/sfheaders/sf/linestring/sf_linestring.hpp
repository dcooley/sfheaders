#ifndef R_SFHEADERS_SF_LINESTRING_H
#define R_SFHEADERS_SF_LINESTRING_H

#include <Rcpp.h>
#include "sfheaders/utils/sexp/sexp.hpp"
#include "sfheaders/sf/sf_utils.hpp"
#include "sfheaders/sfc/linestring/sfc_linestring.hpp"
#include "sfheaders/utils/unique/unique_ids.hpp"
#include "sfheaders/shapes/shapes.hpp"

namespace sfheaders {
namespace sf {

// the design should be;
// given the objet, get the 'ids' out here;
// then create an sfc
// and attach the ids
//
// BUT, this is a two-step id extract
// and is there a guarantee they'll be combined in the correct order??

  // this function won't keep any attributes
  inline SEXP sf_linestring(
    SEXP& x,
    SEXP& geometry_cols,
    SEXP& linestring_id
  ) {

    Rcpp::List sfc = sfheaders::sfc::sfc_linestring( x, geometry_cols, linestring_id );
    // TODO: we're getting the linestring_ids inside sfc_linestring,
    // and re-doing it here... say what...
    SEXP ids = sfheaders::utils::get_ids( x, linestring_id );
    Rcpp::DataFrame sf = sfheaders::sf::make_sf( sfc, ids );
    return sf;
  }

  inline SEXP sf_linestring(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& geometry_cols,
      SEXP& line_ids,
      Rcpp::StringVector& property_cols
  ) {
    Rcpp::IntegerMatrix line_positions = sfheaders::utils::id_positions( line_ids );
    Rcpp::IntegerVector row_idx = line_positions( Rcpp::_, 0 );
    Rcpp::StringVector df_names = df.names();
    Rcpp::IntegerVector property_idx = sfheaders::utils::where_is( property_cols, df_names );
    Rcpp::List sfc = sfheaders::sfc::sfc_linestring( df, geometry_cols, line_positions );

    return sfheaders::sf::create_sf( df, sfc, property_cols, property_idx, row_idx );
  }

  inline SEXP sf_linestring(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& geometry_cols,
      SEXP& line_ids,
      Rcpp::IntegerVector& property_idx
  ) {

    // get the property cols as a string_vector so we get the column names
    Rcpp::StringVector df_names = df.names();
    Rcpp::StringVector property_cols = df_names[ property_idx ];
    Rcpp::StringVector str_geometry_cols = df_names[ geometry_cols ];
    return sf_linestring( df, str_geometry_cols, line_ids, property_cols );
  }

  inline SEXP sf_linestring(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& geometry_cols,
      Rcpp::String& linestring_id
  ) {

    Rcpp::StringVector df_names = df.names();
    Rcpp::StringVector cols = sfheaders::utils::concatenate_vectors( geometry_cols, linestring_id );
    Rcpp::StringVector property_cols = sfheaders::utils::other_columns( df_names, cols );

    SEXP line_ids = df[ linestring_id ];
    return sf_linestring( df, geometry_cols, line_ids, property_cols );
  }

  inline SEXP sf_linestring(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& geometry_cols,
      int& linestring_id
  ) {

    Rcpp::StringVector df_names = df.names();
    Rcpp::StringVector str_geometry_cols = df_names[ geometry_cols ];
    Rcpp::String line_id = df_names[ linestring_id ];
    return sf_linestring( df, str_geometry_cols, line_id );
  }

  inline SEXP sf_linestring(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& geometry_cols,
      int& linestring_id
  ) {
    sfheaders::utils::column_exists( im, linestring_id );
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );
    return sf_linestring( df, geometry_cols, linestring_id );
  }

  inline SEXP sf_linestring(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& geometry_cols,
      int& linestring_id
  ) {
    sfheaders::utils::column_exists( nm, linestring_id );
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );
    return sf_linestring( df, geometry_cols, linestring_id );
  }

  inline SEXP sf_linestring(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& geometry_cols,
      Rcpp::String& linestring_id
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );

    // Rcpp::StringVector df_names = df.names();
    // Rcpp::StringVector cols = sfheaders::utils::concatenate_vectors( geometry_cols, linestring_id );
    // Rcpp::StringVector property_cols = sfheaders::utils::other_columns( df_names, cols );
    //SEXP line_ids = df[ linestring_id ];
    //return sf_linestring( df, geometry_cols, line_ids, property_cols );
    return sf_linestring( df, geometry_cols, linestring_id );
  }

  inline SEXP sf_linestring(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& geometry_cols,
      Rcpp::String& linestring_id
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );
//
//     Rcpp::StringVector df_names = df.names();
//     Rcpp::StringVector cols = sfheaders::utils::concatenate_vectors( geometry_cols, linestring_id );
//     Rcpp::StringVector property_cols = sfheaders::utils::other_columns( df_names, cols );
//
//     SEXP line_ids = df[ linestring_id ];
//    return sf_linestring( df, geometry_cols, line_ids, property_cols );
    return sf_linestring( df, geometry_cols, linestring_id );
  }

  inline SEXP sf_linestring(
      SEXP& x,
      Rcpp::IntegerVector& geometry_cols,
      int& linestring_id
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
      SEXP xc = Rcpp::clone( x );
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
      return sf_linestring( im, geometry_cols, linestring_id );
    }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
      SEXP xc = Rcpp::clone( x );
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
      return sf_linestring( nm, geometry_cols, linestring_id );
    }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sf_linestring( df, geometry_cols, linestring_id );
    }
    }
    default: {
      Rcpp::stop("sfheaders - unsupported linestring type"); // #nocov
    }
    }

    return Rcpp::List::create();
  }

  inline SEXP sf_linestring(
      SEXP& x,
      Rcpp::StringVector& geometry_cols,
      Rcpp::String& linestring_id
  ) {

    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
      SEXP xc = Rcpp::clone( x );
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
      return sf_linestring( im, geometry_cols, linestring_id );
    }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
      SEXP xc = Rcpp::clone( x );
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
      return sf_linestring( nm, geometry_cols, linestring_id );
    }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sf_linestring( df, geometry_cols, linestring_id );
    }
    }
    default: {
      Rcpp::stop("sfheaders - unsupported linestring type");
    }
    }

    return Rcpp::List::create();
  }

  inline SEXP sf_linestring(
    SEXP& x,
    SEXP& geometry_cols,
    SEXP& linestring_id,
    bool& keep
  ) {
    if( !keep ) {
      return sf_linestring( x, geometry_cols, linestring_id );
    }

    // TODO:
    // - get line_positions.
    // - get call sfc_linestring with line_positions as an argument
    //
    // To get line_positions, need to know the types of x and linestring_id column

    if( Rf_isNull( geometry_cols ) || Rf_isNull( linestring_id ) ) {

      // can't work out which are the geometry columns
      Rcpp::stop("sfheaders - please specify the geometry and id columns");

    } else {
      // we have all the columns sorted, so the 'properties' are all the other columns
      //
      sfheaders::utils::geometry_column_check( geometry_cols );

      if ( TYPEOF( geometry_cols ) != TYPEOF( linestring_id ) ) {
        Rcpp::stop("sfheaders - linestring columns types are different");
      }

      switch( TYPEOF( geometry_cols ) ) {
      case REALSXP: {}
      case INTSXP: {
        Rcpp::IntegerVector iv_geometry_cols = Rcpp::as< Rcpp::IntegerVector >( geometry_cols );
        Rcpp::IntegerVector iv_linestring_id_col = Rcpp::as< Rcpp::IntegerVector >( linestring_id );
        int i_linestring_id_col = iv_linestring_id_col[0];
        return sf_linestring( x, iv_geometry_cols, i_linestring_id_col );
      }
      case STRSXP: {
        Rcpp::StringVector sv_geometry_cols = Rcpp::as< Rcpp::StringVector >( geometry_cols );
        Rcpp::StringVector sv_linestring_id_col = Rcpp::as< Rcpp::StringVector >( linestring_id );
        Rcpp::String s_linestring_id_col = sv_linestring_id_col[0];
        return sf_linestring( x, sv_geometry_cols, s_linestring_id_col );
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
