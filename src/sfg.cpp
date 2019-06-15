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
SEXP rcpp_to_multilinestring(
  Rcpp::DataFrame df,
  Rcpp::StringVector cols
) {
  return sfheaders::sfg::to_multilinestring( df, cols );
}

// [[Rcpp::export]]
SEXP rcpp_to_sfg( SEXP x, std::string geom_type ) {
  return sfheaders::sfg::to_sfg( x, geom_type );
}

