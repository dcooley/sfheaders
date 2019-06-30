#include <Rcpp.h>
#include "sfheaders/sfc/point/sfc_points.hpp"
#include "sfheaders/sfc/multipoint/sfc_multipoints.hpp"
#include "sfheaders/sfc/linestring/sfc_linestrings.hpp"

// [[Rcpp::export]]
SEXP rcpp_to_points( SEXP x, SEXP cols ) {
  return sfheaders::sfc::to_points( x, cols );
}


// [[Rcpp::export]]
SEXP rcpp_to_multipoints( SEXP x, SEXP cols, SEXP id_col ) {
  return sfheaders::sfc::to_multipoints( x, cols, id_col );
  //return sfheaders::sfc::to_multipoints( x );
}

// [[Rcpp::export]]
SEXP rcpp_to_linestrings( SEXP x, SEXP cols, SEXP id_col ) {
  return sfheaders::sfc::to_linestrings( x, cols, id_col );
}


// SEXP rcpp_to_sfc( SEXP x ) {
//
// }

