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


  inline SEXP get_polygon(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& geometry_cols,
    Rcpp::String& polygon_id_column,
    Rcpp::String& line_id_column
  ) {
    // given polygon & line ids, collapse and matricise and listify

    Rcpp::NumericVector polygon_ids = df[ polygon_id_column ];
    Rcpp::NumericVector line_ids = df[ line_id_column ];
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
      Rcpp::NumericVector polygon_line_ids = line_ids[ rng ];
      Rcpp::NumericVector unique_polygon_line_ids = Rcpp::sort_unique( polygon_line_ids );

      Rcpp::Rcout << "polygon_line_ids : " << polygon_line_ids << std::endl;
      Rcpp::Rcout << "unique_polygon_line_id: " << unique_polygon_line_ids << std::endl;

      Rcpp::IntegerMatrix polygon_lines = sfheaders::utils::line_ids( polygon_ids, unique_polygon_line_ids );
      Rcpp::DataFrame df_subset = sfheaders::utils::subset_dataframe( df, df_names, start, end );

      mpl[ i ] = sfheaders::shapes::get_lines( df_subset, geometry_cols, line_id_column );
    }
    return mpl;
  }

  inline SEXP get_polygon(
    SEXP& x,
    SEXP& cols,
    SEXP& line_id
  ) {
    // do something...
    // same as get_lines?
    // like get_multilinestring
  }

  inline SEXP get_polygons(
    SEXP& x,
    SEXP& cols, // IntegerVector or StringVector
    SEXP& polygon_id,
    SEXP& line_id
  ) {
    //  given polygon
    // first get lines/
    // then get lines again?
    // but, get lines will get
  }

} // shapes
} // sfheaders


#endif
