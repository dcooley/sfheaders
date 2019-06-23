#ifndef R_SFHEADERS_SHAPES_POLYGON_H
#define R_SFHEADERS_SHAPES_POLYGON_H

#include <Rcpp.h>
#include "sfheaders/utils/utils.hpp"
#include "sfheaders/shapes/line/line.hpp"
#include "sfheaders/shapes/lines/lines.hpp"

#include <Rcpp.h>

namespace sfheaders {
namespace shapes {


  inline SEXP get_polygon(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& geometry_cols,
    Rcpp::NumericVector& polygon_ids,
    Rcpp::NumericVector& line_ids
  ) {
    // given polygon & line ids, collapse and matricise and listify

    Rcpp::NumericVector unique_polygon_ids = Rcpp::sort_unique( polygon_ids );
    Rcpp::IntegerMatrix polygon_positions = sfheaders::utils::line_ids( polygon_ids, unique_polygon_ids );

    size_t n_polygons = unique_polygon_ids.length();

    Rcpp::List mpl( n_polygons );

    // // now iterate through the data.frame and get the matrices of lines
    // size_t i;
    // for( i = 0; i < n_polygosn; i++ ) {
    //
    //   // for each polygon, now get all the lines?
    //   // - TODO
    //   // - a list for each polygon, to go inside mpl
    //   Rcpp::List ply( 1 );
    //   int start = polygon_positions(i, 0);
    //   int end = polygon_positions(i, 1);
    //
    //   // need a subset-df based on start & end
    //   // and subset line_ids based on which polygon we're getting
    //   Rcpp::NumericVector these_lines = line_ids[ Rcpp::Range( start, end ) ]; // are these indices correct?
    //   // then call get_lines( df_sub, geometry_cols, line_ids );
    //
    //
    //   ply[ 0 ] = sfheaders::shapes::get_lines( df_sub, geometry_cols, start, end );
    //   mpl[ i ] = ply;
    // }
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
