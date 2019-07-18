#include <Rcpp.h>
#include "sfheaders/sfc/sfc.hpp"

// [[Rcpp::export]]
SEXP rcpp_sfc_point( SEXP x, SEXP cols ) {
  return sfheaders::sfc::sfc_point( x, cols );
}

// [[Rcpp::export]]
Rcpp::List rcpp_sfc_points( Rcpp::List lst ) {
  return sfheaders::sfc::sfc_points( lst );
}

// [[Rcpp::export]]
SEXP rcpp_sfc_multipoint( SEXP x, SEXP cols, SEXP id_col ) {
  return sfheaders::sfc::sfc_multipoint( x, cols, id_col );
  //return sfheaders::sfc::sfc_multipoints( x );
}

// [[Rcpp::export]]
Rcpp::List rcpp_sfc_multipoints( Rcpp::List lst ) {
  return sfheaders::sfc::sfc_multipoints( lst );
}

// [[Rcpp::export]]
SEXP rcpp_sfc_linestring( SEXP x, SEXP cols, SEXP id_col ) {
  return sfheaders::sfc::sfc_linestring( x, cols, id_col );
}

// [[Rcpp::export]]
Rcpp::List rcpp_sfc_linestrings( Rcpp::List lst ) {
  return sfheaders::sfc::sfc_linestrings( lst );
}

// [[Rcpp::export]]
SEXP rcpp_sfc_multilinestring( SEXP x, SEXP cols, SEXP multiline_id, SEXP line_id ) {
  return sfheaders::sfc::sfc_multilinestring( x, cols, multiline_id, line_id );
}

// [[Rcpp::export]]
Rcpp::List rcpp_sfc_multilinestrings( Rcpp::List lst ) {
  return sfheaders::sfc::sfc_multilinestrings( lst );
}

// [[Rcpp::export]]
SEXP rcpp_sfc_polygon( SEXP x, SEXP cols, SEXP polygon_id, SEXP line_id ) {
  return sfheaders::sfc::sfc_polygon( x, cols, polygon_id, line_id );
}

// [[Rcpp::export]]
Rcpp::List rcpp_sfc_polygons( Rcpp::List lst ) {
  return sfheaders::sfc::sfc_polygons( lst );
}


// [[Rcpp::export]]
SEXP rcpp_sfc_multipolygon( SEXP x, SEXP cols, SEXP multipolygon_id, SEXP polygon_id, SEXP linestring_id ) {
  return sfheaders::sfc::sfc_multipolygon( x, cols, multipolygon_id, polygon_id, linestring_id );
}

// [[Rcpp::export]]
Rcpp::List rcpp_sfc_multipolygons( Rcpp::List lst ) {
  return sfheaders::sfc::sfc_multipolygons( lst );
}

// // [[Rcpp::export]]
// SEXP rcpp_to_multipolygon(
//     Rcpp::NumericVector x,
//     Rcpp::NumericVector y,
//     Rcpp::NumericVector z = R_NilValue,
//     Rcpp::NumericVector m = R_NilValue,
//     Rcpp::NumericVector multipolygon_id = R_NilValue,
//     Rcpp::NumericVector polygon_id = R_NilValue,
//     Rcpp::NumericVector linestring_id = R_NilValue
// ) {
//   return sfheaders::sfc::sfc_multipolygon(x, y, z, m, multipolygon_id, polygon_id, linestring_id);
// }

// SEXP rcpp_sfc_sfc( SEXP x ) {
//
// }

