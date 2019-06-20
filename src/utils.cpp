#include <Rcpp.h>
#include "sfheaders/utils/utils.hpp"


// [[Rcpp::export]]
SEXP rcpp_other_columns(
  SEXP x,
  SEXP id_cols
) {
  return sfheaders::utils::other_columns( x, id_cols );
}

