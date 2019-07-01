#include <Rcpp.h>
#include "sfheaders/sfc/point/sfc_points.hpp"
#include "sfheaders/sfc/multipoint/sfc_multipoints.hpp"
#include "sfheaders/sfc/linestring/sfc_linestrings.hpp"
#include "sfheaders/sfc/multilinestring/sfc_multilinestring.hpp"

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



// SEXP rcpp_sfc_sfc( SEXP x ) {
//
// }

