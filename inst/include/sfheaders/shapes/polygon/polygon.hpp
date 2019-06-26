#ifndef R_SFHEADERS_SHAPES_POLYGON_H
#define R_SFHEADERS_SHAPES_POLYGON_H

#include <Rcpp.h>
#include "sfheaders/utils/utils.hpp"
#include "sfheaders/utils/subset.hpp"
#include "sfheaders/shapes/line/line.hpp"
#include "sfheaders/shapes/lines/lines.hpp"

#include <Rcpp.h>

namespace sfheaders {
namespace shapes {

  // get_lines is used for get_polygon
  // get_polygons is used for multipolygons; list of lists of matrices

  inline SEXP get_polygons(
    Rcpp::IntegerMatrix& im
  ) {
    Rcpp::List mp(1);
    mp[0] = sfheaders::shapes::get_lines(im);
    return mp;
  }

  inline SEXP get_polygons(
      Rcpp::NumericMatrix& nm
  ) {
    Rcpp::List mp(1);
    mp[0] = sfheaders::shapes::get_lines(nm);
    return mp;
  }

  inline SEXP get_polygons(
      Rcpp::DataFrame& df
  ) {
    Rcpp::List mp(1);
    mp[0] = sfheaders::shapes::get_lines(df);
    return mp;
  }


  /*
   * get_polygon
   *
   * Gets all the polygons inside a single multipolygon
   *
   */
  inline SEXP get_polygons(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& geometry_cols,
    Rcpp::String& polygon_id_column,
    Rcpp::String& line_id_column
  ) {

    Rcpp::NumericVector polygon_ids = df[ polygon_id_column ];
    Rcpp::StringVector df_names = df.names();

    Rcpp::NumericVector unique_polygon_ids = Rcpp::sort_unique( polygon_ids );
    Rcpp::IntegerMatrix polygons = sfheaders::utils::line_ids( polygon_ids, unique_polygon_ids );

    size_t n_polygons = unique_polygon_ids.length();

    Rcpp::List mpl( n_polygons );

    size_t i;
    for( i = 0; i < n_polygons; i++ ) {
      int start = polygons(i, 0);
      int end = polygons(i, 1);

      Rcpp::Range rng( start, end );
      Rcpp::DataFrame df_subset = sfheaders::utils::subset_dataframe( df, df_names, start, end );

      mpl[ i ] = sfheaders::shapes::get_lines( df_subset, geometry_cols, line_id_column );
    }
    return mpl;
  }


  inline SEXP get_polygons(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& geometry_cols,
      int& polygon_id_column,
      int& line_id_column
  ) {
    // given polygon & line ids, collapse and matricise and listify
    Rcpp::StringVector df_names = df.names();

    // use the indexes to subset the df_names to get the columns
    Rcpp::String str_polygon_id_column = df_names[ polygon_id_column ];
    Rcpp::String str_line_id_column = df_names[ line_id_column ];
    Rcpp::StringVector str_geometry_cols = df_names[ geometry_cols ];

    return get_polygons( df, str_geometry_cols, str_polygon_id_column, str_line_id_column );
  }

  inline SEXP get_polygons(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& geometry_cols,
      Rcpp::String& polygon_id_column,
      Rcpp::String& line_id_column
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );
    return get_polygons( df, geometry_cols, polygon_id_column, line_id_column );
  }


  inline SEXP get_polygons(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& geometry_cols,
      int& polygon_id_column,
      int& line_id_column
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );
    return get_polygons( df, geometry_cols, polygon_id_column, line_id_column );
  }


  inline SEXP get_polygons(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& geometry_cols,
      Rcpp::String& polygon_id_column,
      Rcpp::String& line_id_column
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );
    return get_polygons( df, geometry_cols, polygon_id_column, line_id_column );
  }

  inline SEXP get_polygons(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& geometry_cols,
      int& polygon_id_column,
      int& line_id_column
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );
    return get_polygons( df, geometry_cols, polygon_id_column, line_id_column );
  }


  inline SEXP get_polygons(
      SEXP& x,
      Rcpp::StringVector& geometry_cols,
      Rcpp::String& polygon_id_column,
      Rcpp::String& line_id_column
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - polygons needs to be matrices or dataframes");
    } else {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return get_polygons( im, geometry_cols, polygon_id_column, line_id_column );
    }
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - polygons needs to be matrices or dataframes");
    } else {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return get_polygons( nm, geometry_cols, polygon_id_column, line_id_column );
    }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return get_polygons( df, geometry_cols, polygon_id_column, line_id_column );
    }
    }
    default: {
      Rcpp::stop("sfheaders - unknown polygons type");
    }
    }
  }


  inline SEXP get_polygons(
    SEXP& x,
    Rcpp::IntegerVector& geometry_cols,
    int& polygon_id_column,
    int& line_id_column
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
    if( !Rf_isMatrix( x ) ) {
        Rcpp::stop("sfheaders - polygons needs to be matrices or dataframes");
    } else {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return get_polygons( im, geometry_cols, polygon_id_column, line_id_column );
    }
    }
    case REALSXP: {
    if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - polygons needs to be matrices or dataframes");
    } else {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return get_polygons( nm, geometry_cols, polygon_id_column, line_id_column );
    }
    }
    case VECSXP: {
    if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return get_polygons( df, geometry_cols, polygon_id_column, line_id_column );
    }
    }
    default: {
      Rcpp::stop("sfheaders - unknown polygons type");
    }
    }
  }

  inline SEXP get_polygons(
    SEXP& x,
    SEXP& geometry_cols, // IntegerVector or StringVector
    SEXP& polygon_id_column,
    SEXP& line_id_column
  ) {

    if( ( TYPEOF( polygon_id_column ) != TYPEOF( line_id_column ) ) ||
        TYPEOF( geometry_cols ) != TYPEOF( polygon_id_column ) ) {
      Rcpp::stop("sfheaders - different column types detected");
    }

    switch( TYPEOF( geometry_cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv_geometry_cols = Rcpp::as< Rcpp::IntegerVector >( geometry_cols );
      Rcpp::IntegerVector iv_polygon_id_column = Rcpp::as< Rcpp::IntegerVector >( polygon_id_column );
      Rcpp::IntegerVector iv_line_id_column = Rcpp::as< Rcpp::IntegerVector >( line_id_column );
      int i_polygon_id_column = iv_polygon_id_column[0];
      int i_line_id_column = iv_line_id_column[0];
      return get_polygons( x, iv_geometry_cols, i_polygon_id_column, i_line_id_column );
    }
    case STRSXP: {
      Rcpp::StringVector sv_geometry_cols = Rcpp::as< Rcpp::StringVector >( geometry_cols );
      Rcpp::StringVector sv_polygon_id_column = Rcpp::as< Rcpp::StringVector >( polygon_id_column );
      Rcpp::StringVector sv_line_id_column = Rcpp::as< Rcpp::StringVector >( line_id_column );
      Rcpp::String s_polygon_id_column = sv_polygon_id_column[0];
      Rcpp::String s_line_id_column = sv_line_id_column[0];
      return get_polygons( x, sv_geometry_cols, s_polygon_id_column, s_line_id_column );
    }
    default: {
      Rcpp::stop("sfheaders - unknown id column types");
    }
    }

  }

} // shapes
} // sfheaders


#endif
