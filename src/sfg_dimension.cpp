#include <Rcpp.h>

#include "sfheaders/sfg/sfg_dimension.hpp"

// [[Rcpp::export]]
std::string rcpp_sfg_dimension(
  SEXP x
) {
  return sfheaders::sfg::sfg_dimension( x );
}
