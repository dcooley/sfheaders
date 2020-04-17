
#include <Rcpp.h>
#include "sfheaders/df/sfc.hpp"

// [[Rcpp::export]]
Rcpp::IntegerVector rcpp_n_coordinates( Rcpp::List sfc ) {
  R_xlen_t n = sfc.length();
  R_xlen_t i;
  Rcpp::IntegerVector res( n );
  for( i = 0; i < n; ++i ) {
    R_xlen_t sfg_count = 0;
    SEXP sfg = sfc[ i ] ;
    sfheaders::df::sfg_n_coordinates( sfg, sfg_count );
    res[ i ] = sfg_count;
  }
  return res;
}
