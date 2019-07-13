#include <Rcpp.h>
#include "sfheaders/sfc/point/sfc_point.hpp"
#include "sfheaders/sfc/multipoint/sfc_multipoint.hpp"
#include "sfheaders/sfc/linestring/sfc_linestring.hpp"
#include "sfheaders/sfc/multilinestring/sfc_multilinestring.hpp"
#include "sfheaders/sfc/polygon/sfc_polygon.hpp"
#include "sfheaders/sfc/multipolygon/sfc_multipolygon.hpp"

// [[Rcpp::export]]
SEXP rcpp_sfc_point( SEXP x, SEXP cols ) {
  return sfheaders::sfc::sfc_point( x, cols );
}


// [[Rcpp::export]]
SEXP rcpp_sfc_multipoint( SEXP x, SEXP cols, SEXP id_col ) {
  return sfheaders::sfc::sfc_multipoint( x, cols, id_col );
  //return sfheaders::sfc::sfc_multipoints( x );
}

// [[Rcpp::export]]
SEXP rcpp_sfc_linestring( SEXP x, SEXP cols, SEXP id_col ) {
  return sfheaders::sfc::sfc_linestring( x, cols, id_col );
}

// [[Rcpp::export]]
SEXP rcpp_sfc_multilinestring( SEXP x, SEXP cols, SEXP multiline_id, SEXP line_id ) {
  return sfheaders::sfc::sfc_multilinestring( x, cols, multiline_id, line_id );
}


// [[Rcpp::export]]
SEXP rcpp_sfc_polygon( SEXP x, SEXP cols, SEXP polygon_id, SEXP line_id ) {
  return sfheaders::sfc::sfc_polygon( x, cols, polygon_id, line_id );
}


// [[Rcpp::export]]
SEXP rcpp_sfc_multipolygon( SEXP x, SEXP cols, SEXP multipolygon_id, SEXP polygon_id, SEXP linestring_id ) {
  return sfheaders::sfc::sfc_multipolygon( x, cols, multipolygon_id, polygon_id, linestring_id );
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

