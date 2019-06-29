#include <Rcpp.h>

#include "sfheaders/bbox.hpp"

/*
 * calculate bbox
 *
 * assumes 2-column object, in the order x, y
 */
// [[Rcpp::export]]
SEXP rcpp_calculate_bbox( SEXP x ) {
  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
  sfheaders::bbox::calculate_bbox( bbox, x );
  return bbox;
}
