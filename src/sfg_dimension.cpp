#include <Rcpp.h>

#include "sfheaders/sfg/sfg_dimension.hpp"

// [[Rcpp::export]]
std::string rcpp_sfg_dimension(
  SEXP x,
  std::string xyzm
) {
  return sfheaders::sfg::sfg_dimension( x, xyzm );
}
