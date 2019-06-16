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

