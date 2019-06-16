#include <Rcpp.h>
#include "sfheaders/shapes/shapes.hpp"


// POINTS -----------
// [[Rcpp::export]]
SEXP rcpp_get_point(
  SEXP x,
  SEXP cols
) {
  return sfheaders::shapes::get_point( x, cols );
}

// LINE ----------
// [[Rcpp::export]]
SEXP rcpp_get_line(
  SEXP x,
  SEXP cols
) {
  return sfheaders::shapes::get_line( x, cols );
}

// LINES -----------
// [[Rcpp::export]]
SEXP rcpp_get_lines(
  SEXP x,
  SEXP cols,
  SEXP id
) {
  return sfheaders::shapes::get_lines( x, cols, id );
}
