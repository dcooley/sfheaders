#include "sfheaders/sf/point/sf_point.hpp"
#include <Rcpp.h>

// [[Rcpp::export]]
SEXP rcpp_sf_point( SEXP x, SEXP cols, SEXP id_col ) {
  return sfheaders::sf::sf_point( x, cols, id_col );
}
