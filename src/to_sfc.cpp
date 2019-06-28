#include <Rcpp.h>
#include "sfheaders/sfc/point/sfc_points.hpp"

// [[Rcpp::export]]
SEXP rcpp_to_points( SEXP x, SEXP cols ) {
  return sfheaders::sfc::to_points( x, cols );
}



// SEXP rcpp_to_sfc( SEXP x ) {
//
// }

