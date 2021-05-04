#include <Rcpp.h>
#include "sfheaders/cast/sfg_cast.hpp"
#include "sfheaders/cast/sfc_cast.hpp"
#include "sfheaders/cast/sf_cast.hpp"
// #include "sfheaders/cast/list_cast.hpp"
#include "sfheaders/sfc/sfc.hpp"

// [[Rcpp::export]]
Rcpp::IntegerVector rcpp_count_new_objects( SEXP sfg, std::string cast_to ) {
  R_xlen_t x = sfheaders::cast::count_new_objects( sfg, cast_to );
  Rcpp::IntegerVector res(1);
  res[0] = x;
  return res;
}

// [[Rcpp::export]]
Rcpp::IntegerVector rcpp_count_new_sfc_objects( Rcpp::List sfc, std::string cast_to ) {
 return sfheaders::cast::count_new_sfc_objects( sfc, cast_to );
}

// [[Rcpp::export]]
Rcpp::List rcpp_cast_sfc( Rcpp::List sfc, std::string cast_to, bool close = true ) {
  Rcpp::List sfc2 = Rcpp::clone( sfc );
  return sfheaders::cast::cast_sfc( sfc2, cast_to, close );
}

// [[Rcpp::export]]
Rcpp::DataFrame rcpp_cast_sf( Rcpp::DataFrame sf, std::string cast_to, SEXP list_columns, bool close = true ) {
  return sfheaders::cast::cast_sf( sf, cast_to, list_columns, close );
}

// // [[Rcpp::export]]
// SEXP rcpp_cast_remove_one( Rcpp::List lst ) {
//   return sfheaders::cast::remove_one( lst );
// }
