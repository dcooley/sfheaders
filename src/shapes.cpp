#include <Rcpp.h>
#include "sfheaders/shapes/shapes.hpp"


// POINTS -----------
// [[Rcpp::export]]
SEXP rcpp_get_vec(
  SEXP x,
  SEXP cols
) {
  return sfheaders::shapes::get_vec( x, cols );
}

// LINE ----------
// [[Rcpp::export]]
SEXP rcpp_get_mat(
  SEXP x,
  SEXP cols
) {
  return sfheaders::shapes::get_mat( x, cols );
}

// LINES -----------
// [[Rcpp::export]]
SEXP rcpp_get_list_mat(
  SEXP x,
  SEXP cols,
  SEXP id
) {
  return sfheaders::shapes::get_listMat( x, cols, id );
}
