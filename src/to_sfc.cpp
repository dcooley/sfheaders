#include <Rcpp.h>
#include "sfheaders/sfc/point/sfc_points.hpp"
#include "sfheaders/sfc/multipoint/sfc_multipoints.hpp"

// [[Rcpp::export]]
SEXP rcpp_to_points( SEXP x, SEXP cols ) {
  return sfheaders::sfc::to_points( x, cols );
}


// [[Rcpp::export]]
SEXP rcpp_to_multipoints( Rcpp::NumericMatrix x ) {
  //return sfheaders::sfc::to_multipoints( x, geometry_cols, id_col );
  return sfheaders::sfc::to_multipoints( x );
}


// SEXP rcpp_to_sfc( SEXP x ) {
//
// }

