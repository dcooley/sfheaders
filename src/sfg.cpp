#include <Rcpp.h>
#include "sfheaders/sfg/sfg.hpp"

// [[Rcpp::export]]
SEXP rcpp_to_point( SEXP x, SEXP geometry_columns ) {
  return sfheaders::sfg::to_point( x, geometry_columns );
}


// [[Rcpp::export]]
SEXP rcpp_to_multipoint( SEXP x, SEXP geometry_columns ) {
  return sfheaders::sfg::to_multipoint( x, geometry_columns );
}

// [[Rcpp::export]]
SEXP rcpp_to_linestring( SEXP x, SEXP geometry_columns ) {
  return sfheaders::sfg::to_linestring( x, geometry_columns );
}

// [[Rcpp::export]]
SEXP rcpp_to_multilinestring( SEXP x, SEXP geometry_columns, SEXP line_id ) {
  return sfheaders::sfg::to_multilinestring( x, geometry_columns, line_id );
}

// [[Rcpp::export]]
SEXP rcpp_to_polygon( SEXP x, SEXP geometry_columns, SEXP line_id ) {
  return sfheaders::sfg::to_polygon( x, geometry_columns, line_id );
}

// [[Rcpp::export]]
SEXP rcpp_to_multipolygon( SEXP x, SEXP geometry_columns, SEXP polygon_id, SEXP line_id ) {
  return sfheaders::sfg::to_multipolygon( x, geometry_columns, polygon_id, line_id );
}

// // [[Rcpp::export]]
// SEXP rcpp_get_polygons(
//     Rcpp::DataFrame x,
//     Rcpp::StringVector geometry_cols,
//     Rcpp::String polygon_id_column,
//     Rcpp::String line_id_column
// ) {
//   return sfheaders::shapes::get_polygons( x, geometry_cols, polygon_id_column, line_id_column );
// }
//
// // [[Rcpp::export]]
// SEXP rcpp_get_polygons2(
//     Rcpp::DataFrame x,
//     Rcpp::IntegerVector geometry_cols,
//     int polygon_id_column,
//     int line_id_column
// ) {
//   return sfheaders::shapes::get_polygons( x, geometry_cols, polygon_id_column, line_id_column );
// }


// [[Rcpp::export]]
SEXP rcpp_to_sfg( SEXP x, std::string geom_type ) {
  return sfheaders::sfg::to_sfg( x, geom_type );
}
