#include <Rcpp.h>
#include "sfheaders/df/sfc.hpp"

// [[Rcpp::export]]
SEXP rcpp_sfg_point_coordinates( Rcpp::NumericVector sfg ) {
  R_xlen_t sfg_rows = 0;
  return sfheaders::df::sfg_point_coordinates( sfg, sfg_rows );
}

// [[Rcpp::export]]
SEXP rcpp_sfg_multipoint_coordinates( Rcpp::NumericMatrix sfg ) {
  R_xlen_t sfg_rows = 0;
  return sfheaders::df::sfg_multipoint_coordinates( sfg, sfg_rows );
}

// [[Rcpp::export]]
SEXP rcpp_sfg_linestring_coordinates( Rcpp::NumericMatrix sfg ) {
  R_xlen_t sfg_rows = 0;
  return sfheaders::df::sfg_linestring_coordinates( sfg, sfg_rows );
}

// [[Rcpp::export]]
SEXP rcpp_sfg_multilinestring_coordinates( Rcpp::List sfg ) {
  R_xlen_t sfg_rows = 0;
  return sfheaders::df::sfg_multilinestring_coordinates( sfg, sfg_rows );
}

// [[Rcpp::export]]
SEXP rcpp_sfg_polygon_coordinates( Rcpp::List sfg ) {
  R_xlen_t sfg_rows = 0;
  return sfheaders::df::sfg_polygon_coordinates( sfg, sfg_rows );
}

// [[Rcpp::export]]
SEXP rcpp_sfg_multipolygon_coordinates( Rcpp::List sfg ) {
  R_xlen_t sfg_rows = 0;
  return sfheaders::df::sfg_multipolygon_coordinates( sfg, sfg_rows );
}

// // [[Rcpp::export]]
// SEXP rcpp_sfg_coordinates( SEXP sfg ) {
//   return sfheaders::df::sfg_coordinates( sfg);
// }
//
// // [[Rcpp::export]]
// SEXP rcpp_sfg_coordinate_lists( SEXP sfg ) {
//   R_xlen_t total_rows = 0;
//   return sfheaders::df::sfg_coordinate_lists( sfg, total_rows );
// }

// [[Rcpp::export]]
SEXP rcpp_sfg_to_df( SEXP sfg ) {
  return sfheaders::df::sfg_to_df( sfg );
}


// [[Rcpp::export]]
SEXP rcpp_sfc_linestring_coordinates( Rcpp::List sfc ) {
  R_xlen_t sfc_rows = 0;
  return sfheaders::df::sfc_linestring_coordinates( sfc );
}
