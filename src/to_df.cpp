#include <Rcpp.h>
#include "sfheaders/df/sfg.hpp"

// [[Rcpp::export]]
SEXP rcpp_sfg_coordinates( SEXP sfg ) {
  return sfheaders::df::sfg_coordinates( sfg );
}
