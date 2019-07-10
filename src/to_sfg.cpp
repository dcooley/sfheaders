#include <Rcpp.h>
#include "sfheaders/sfg/sfg.hpp"

// [[Rcpp::export]]
SEXP rcpp_sfg_point( SEXP x, SEXP geometry_columns ) {
  return sfheaders::sfg::sfg_point( x, geometry_columns );
}


// [[Rcpp::export]]
SEXP rcpp_sfg_multipoint( SEXP x, SEXP geometry_columns ) {
  return sfheaders::sfg::sfg_multipoint( x, geometry_columns );
}

// [[Rcpp::export]]
SEXP rcpp_sfg_linestring( SEXP x, SEXP geometry_columns ) {
  return sfheaders::sfg::sfg_linestring( x, geometry_columns );
}

// [[Rcpp::export]]
SEXP rcpp_sfg_multilinestring( SEXP x, SEXP geometry_columns, SEXP line_id ) {
  return sfheaders::sfg::sfg_multilinestring( x, geometry_columns, line_id );
}

// // [[Rcpp::export]]
// SEXP rcpp_sfg_polygon( SEXP x, SEXP geometry_columns, SEXP line_id ) {
//   return sfheaders::sfg::sfg_polygon( x, geometry_columns, line_id );
// }

// [[Rcpp::export]]
SEXP rcpp_sfg_multipolygon( SEXP x, SEXP geometry_columns, SEXP polygon_id, SEXP line_id ) {
  return sfheaders::sfg::sfg_multipolygon( x, geometry_columns, polygon_id, line_id );
}


// [[Rcpp::export]]
SEXP rcpp_to_sfg( SEXP x, std::string geom_type ) {
  return sfheaders::sfg::to_sfg( x, geom_type );
}
