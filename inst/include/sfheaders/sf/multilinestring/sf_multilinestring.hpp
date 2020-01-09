#ifndef R_SFHEADERS_SF_MULTILINESTRING_H
#define R_SFHEADERS_SF_MULTILINESTRING_H

#include <Rcpp.h>
#include "sfheaders/utils/sexp/sexp.hpp"
#include "sfheaders/sf/sf_utils.hpp"
#include "sfheaders/sfc/multilinestring/sfc_multilinestring.hpp"
#include "sfheaders/utils/unique/unique_ids.hpp"
#include "sfheaders/shapes/shapes.hpp"

namespace sfheaders {
namespace sf {

  inline SEXP sf_multilinestring(
      SEXP& x,
      SEXP& geometry_cols,
      SEXP& multilinestring_id,
      SEXP& linestring_id
  ) {
    Rcpp::List sfc = sfheaders::sfc::sfc_multilinestring( x, geometry_cols, multilinestring_id, linestring_id );

    SEXP ids = sfheaders::utils::get_ids( x, multilinestring_id );
    Rcpp::DataFrame sf = sfheaders::sf::make_sf( sfc, ids );
    return sf;
  }

  inline SEXP sf_multilinestring(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& geometry_cols,
      SEXP& multiline_ids,
      Rcpp::String& line_ids,
      Rcpp::StringVector& property_cols
  ) {
    Rcpp::IntegerMatrix multilinestring_positions = sfheaders::utils::id_positions( multiline_ids );
    Rcpp::IntegerVector row_idx = multilinestring_positions( Rcpp::_, 0 );
    Rcpp::StringVector df_names = df.names();
    Rcpp::IntegerVector property_idx = sfheaders::utils::where_is( property_cols, df_names );
    Rcpp::List sfc = sfheaders::sfc::sfc_multilinestring( df, geometry_cols, line_ids, multilinestring_positions );

    return sfheaders::sf::create_sf( df, sfc, property_cols, property_idx, row_idx );
  }

  inline SEXP sf_multilinestring(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& geometry_cols,
      SEXP& multiline_ids,
      int& linestring_id,
      Rcpp::IntegerVector& property_idx
  ) {

    // get the property cols as a string_vector so we get the column names
    Rcpp::StringVector df_names = df.names();
    Rcpp::StringVector property_cols = df_names[ property_idx ];
    Rcpp::StringVector str_geometry_cols = df_names[ geometry_cols ];
    Rcpp::String str_linestring_id = df_names[ linestring_id ];

    return sf_multilinestring( df, str_geometry_cols, multiline_ids, str_linestring_id, property_cols );
  }

  inline SEXP sf_multilinestring(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& geometry_cols,
      Rcpp::String& multilinestring_id,
      Rcpp::String& linestring_id
  ) {

    Rcpp::StringVector df_names = df.names();
    Rcpp::StringVector cols = sfheaders::utils::concatenate_vectors( geometry_cols, linestring_id );
    Rcpp::StringVector property_cols = sfheaders::utils::other_columns( df_names, cols );

    SEXP multiline_ids = df[ multilinestring_id ];
    //SEXP line_ids = df[ linestring_id ];
    return sf_multilinestring( df, geometry_cols, multiline_ids, linestring_id, property_cols );
  }

  inline SEXP sf_multilinestring(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& geometry_cols,
      int& multilinestring_id,
      int& linestring_id
  ) {

    Rcpp::StringVector df_names = df.names();
    Rcpp::StringVector str_geometry_cols = df_names[ geometry_cols ];
    Rcpp::String multiline_id = df_names[ multilinestring_id ];
    Rcpp::String line_id = df_names[ linestring_id ];

    return sf_multilinestring( df, str_geometry_cols, multiline_id, line_id );
  }

  inline SEXP sf_multilinestring(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& geometry_cols,
      int& multilinestring_id,
      int& linestring_id
  ) {

    sfheaders::utils::column_exists( im, multilinestring_id );
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );
    return sf_multilinestring( df, geometry_cols, multilinestring_id, linestring_id );
  }

  inline SEXP sf_multilinestring(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& geometry_cols,
      int& multilinestring_id,
      int& linestring_id
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );
    return sf_multilinestring( df, geometry_cols, multilinestring_id, linestring_id );
  }

  inline SEXP sf_multilinestring(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& geometry_cols,
      Rcpp::String& multilinestring_id,
      Rcpp::String& linestring_id
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );

    Rcpp::StringVector df_names = df.names();
    Rcpp::StringVector cols = sfheaders::utils::concatenate_vectors( geometry_cols, linestring_id );
    Rcpp::StringVector cols2 = sfheaders::utils::concatenate_vectors( cols, multilinestring_id );
    Rcpp::StringVector property_cols = sfheaders::utils::other_columns( df_names, cols2 );

    SEXP multiline_ids = df[ multilinestring_id ];
    return sf_multilinestring( df, geometry_cols, multiline_ids, linestring_id, property_cols );
  }


    inline SEXP sf_multilinestring(
        Rcpp::NumericMatrix& nm,
        Rcpp::StringVector& geometry_cols,
        Rcpp::String& multilinestring_id,
        Rcpp::String& linestring_id
    ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );

      Rcpp::StringVector df_names = df.names();
      Rcpp::StringVector cols = sfheaders::utils::concatenate_vectors( geometry_cols, linestring_id );
      Rcpp::StringVector cols2 = sfheaders::utils::concatenate_vectors( cols, multilinestring_id );
      Rcpp::StringVector property_cols = sfheaders::utils::other_columns( df_names, cols2 );

      SEXP multiline_ids = df[ multilinestring_id ];
      return sf_multilinestring( df, geometry_cols, multiline_ids, linestring_id, property_cols );
    }


  // Rcpp::String& |
  // int&          | -- both these are the column indexes
  // when they become
  // SEXP - they are the vector of id's.

  inline SEXP sf_multilinestring(
      SEXP& x,
      Rcpp::IntegerVector& geometry_cols,
      int& multilinestring_id,
      int& linestring_id
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
      SEXP xc = Rcpp::clone( x );
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
      return sf_multilinestring( im, geometry_cols, multilinestring_id, linestring_id );
    }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
      SEXP xc = Rcpp::clone( x );
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
      return sf_multilinestring( nm, geometry_cols, multilinestring_id, linestring_id );
    }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sf_multilinestring( df, geometry_cols, multilinestring_id, linestring_id );
    }
    }
    default: {
      Rcpp::stop("sfheaders - unsupported linestring type"); // #nocov
    }
    }

    return Rcpp::List::create();
  }

  inline SEXP sf_multilinestring(
      SEXP& x,
      Rcpp::StringVector& geometry_cols,
      Rcpp::String& multilinestring_id,
      Rcpp::String& linestring_id
  ) {

    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
      SEXP xc = Rcpp::clone( x );
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
      return sf_multilinestring( im, geometry_cols, multilinestring_id, linestring_id );
    }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
      SEXP xc = Rcpp::clone( x );
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
      return sf_multilinestring( nm, geometry_cols, multilinestring_id, linestring_id );
    }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sf_multilinestring( df, geometry_cols, multilinestring_id, linestring_id );
    }
    }
    default: {
      Rcpp::stop("sfheaders - unsupported linestring type");
    }
    }

    return Rcpp::List::create();
  }

  inline SEXP sf_multilinestring(
      SEXP& x,
      SEXP& geometry_cols,
      SEXP& multilinestring_id,
      SEXP& linestring_id,
      bool& keep
  ) {

    if( !keep ) {
      return sf_multilinestring( x, geometry_cols, multilinestring_id, linestring_id );
    }


    if( Rf_isNull( geometry_cols ) || Rf_isNull( linestring_id ) || Rf_isNull( multilinestring_id) ) {

      // can't work out which are the geometry columns
      Rcpp::stop("sfheaders - please specify the geometry and id columns");

    } else {

      sfheaders::utils::geometry_column_check( geometry_cols );

      if ( TYPEOF( geometry_cols ) != TYPEOF( linestring_id ) ||
           TYPEOF( geometry_cols ) != TYPEOF( multilinestring_id ) ) {
        Rcpp::stop("sfheaders - multilinestring columns types are different");  // #nocov
      }

      switch( TYPEOF( geometry_cols ) ) {
      case REALSXP: {}
      case INTSXP: {
        Rcpp::IntegerVector iv_geometry_cols = Rcpp::as< Rcpp::IntegerVector >( geometry_cols );
        Rcpp::IntegerVector iv_multilinestring_id_col = Rcpp::as< Rcpp::IntegerVector >( multilinestring_id );
        Rcpp::IntegerVector iv_linestring_id_col = Rcpp::as< Rcpp::IntegerVector >( linestring_id );
        int i_multilinestring_id_col = iv_multilinestring_id_col[0];
        int i_linestring_id_col = iv_linestring_id_col[0];
        return sf_multilinestring( x, iv_geometry_cols, i_multilinestring_id_col, i_linestring_id_col );

      }
      case STRSXP: {
        Rcpp::StringVector sv_geometry_cols = Rcpp::as< Rcpp::StringVector >( geometry_cols );
        Rcpp::StringVector sv_multilinestring_id_col = Rcpp::as< Rcpp::StringVector >( multilinestring_id );
        Rcpp::StringVector sv_linestring_id_col = Rcpp::as< Rcpp::StringVector >( linestring_id );
        Rcpp::String s_multilinestring_id_col = sv_multilinestring_id_col[0];
        Rcpp::String s_linestring_id_col = sv_linestring_id_col[0];
        return sf_multilinestring( x, sv_geometry_cols, s_multilinestring_id_col, s_linestring_id_col );
      }
      default: {
        Rcpp::stop("sfheaders - unsupported multilinestring type");  // #nocov
      }
      }
    }

    Rcpp::stop("sfheaders - multilinestring case not yet implemented"); // #nocov
    return Rcpp::List::create(); // ??
  }

} // sfc
} // sfheaders

#endif
