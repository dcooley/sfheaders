#include <Rcpp.h>
#include "sfheaders/utils/utils.hpp"


// [[Rcpp::export]]
SEXP rcpp_other_columns(
  SEXP x,
  SEXP id_cols,
  SEXP id_col2,
  SEXP id_col3
) {
  return sfheaders::utils::other_columns( x, id_cols, id_col2, id_col3 );
}

// [[Rcpp::export]]
Rcpp::IntegerMatrix rcpp_line_ids(
    Rcpp::NumericVector line_ids,
    Rcpp::NumericVector unique_ids
) {
  return sfheaders::utils::line_ids( line_ids, unique_ids );
}

// [[Rcpp::export]]
Rcpp::DataFrame rcpp_subset_dataframe(
  Rcpp::DataFrame df,
  Rcpp::StringVector cols,
  int start,
  int end
) {
  return sfheaders::utils::subset_dataframe(df, cols, start, end);
}




