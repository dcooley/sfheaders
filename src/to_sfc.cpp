#include <Rcpp.h>
#include "sfheaders/sfc/point/sfc_points.hpp"

// [[Rcpp::export]]
SEXP rcpp_to_points( SEXP x ) {
  return sfheaders::sfc::to_points( x );
}
