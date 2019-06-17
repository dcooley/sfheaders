#include <Rcpp.h>
#include "sfheaders/sfg/sfg.hpp"

// [[Rcpp::export]]
SEXP rcpp_to_point( SEXP x ) {
  return sfheaders::sfg::to_point( x );
}

// [[Rcpp::export]]
SEXP rcpp_to_multipoint( SEXP x ) {
  return sfheaders::sfg::to_multipoint( x );
}

// [[Rcpp::export]]
SEXP rcpp_to_linestring( SEXP x ) {
  return sfheaders::sfg::to_linestring( x );
}

// [[Rcpp::export]]
SEXP rcpp_to_multilinestring( SEXP x ) {
  return sfheaders::sfg::to_multilinestring( x );
}

// // [[Rcpp::export]]
// SEXP rcpp_to_multilinestring(
//   Rcpp::DataFrame df,
//   Rcpp::String line_id,
//   Rcpp::StringVector geometry_columns
// ) {
//   return sfheaders::sfg::to_multilinestring( df, line_id, geometry_columns );
// }

// [[Rcpp::export]]
SEXP rcpp_to_sfg( SEXP x, std::string geom_type ) {
  return sfheaders::sfg::to_sfg( x, geom_type );
}
