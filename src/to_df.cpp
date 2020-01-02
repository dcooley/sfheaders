#include <Rcpp.h>
#include "sfheaders/df/sfg.hpp"

// [[Rcpp::export]]
SEXP rcpp_sfg_coordinates( SEXP sfg ) {
  return sfheaders::df::sfg_coordinates( sfg );
}

// [[Rcpp::export]]
SEXP rcpp_sfg_to_df( SEXP sfg ) {
  return sfheaders::df::sfg_to_df( sfg );
}
