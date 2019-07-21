

#include "sfheaders/sf/sf.hpp"
#include <Rcpp.h>

/*
 * rcpp_make_sf
 *
 * Creates an 'sf' object from an sfc, and a vector of ids
 */
// [[Rcpp::export]]
SEXP rcpp_make_sf( Rcpp::List sfc, SEXP ids ) {
  return sfheaders::sf::make_sf( sfc, ids );
}
