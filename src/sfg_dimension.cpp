#include <Rcpp.h>

#include "sfheaders/sfg/sfg_dimension.hpp"

// [[Rcpp::export]]
std::string rcpp_sfg_dimension(
  SEXP x,
  bool m_only
) {
  return sfheaders::sfg::sfg_dimension( x, m_only );
}
