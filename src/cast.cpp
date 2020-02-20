#include <Rcpp.h>
#include "sfheaders/cast/sfg.hpp"
#include "sfheaders/cast/sfc.hpp"

// [[Rcpp::export]]
SEXP rcpp_sfg_cast_df( SEXP sfg ) {
  return sfheaders::cast::sfg_to_cast_df( sfg );
}


// [[Rcpp::export]]
SEXP rcpp_sfc_cast_df( Rcpp::List sfc ) {
  return sfheaders::cast::sfc_to_cast_df( sfc );
}

// [[Rcpp::export]]
SEXP rcpp_vec_to_vec( Rcpp::NumericVector sfg ) {
  double id = 1;
  R_xlen_t sfg_rows = 0;
  return sfheaders::cast::vec_to_vec( sfg, sfg_rows, id );
}

// [[Rcpp::export]]
SEXP rcpp_mat_to_vec( Rcpp::NumericMatrix sfg ) {
  double id = 1;
  R_xlen_t sfg_rows = 0;
  return sfheaders::cast::mat_to_vec( sfg, sfg_rows, id );
}

// [[Rcpp::export]]
SEXP rcpp_listMat_to_vec( Rcpp::List sfg ) {
  double id = 1;
  R_xlen_t sfg_rows = 0;
  return sfheaders::cast::listMat_to_vec( sfg, sfg_rows, id );
}

// [[Rcpp::export]]
SEXP rcpp_listListMat_to_vec( Rcpp::List sfg ) {
  double id = 1;
  R_xlen_t sfg_rows = 0;
  return sfheaders::cast::listListMat_to_vec( sfg, sfg_rows, id );
}

// [[Rcpp::export]]
SEXP rcpp_vec_to_mat( Rcpp::NumericVector sfg ) {
  double id = 1;
  R_xlen_t sfg_rows = 0;
  return sfheaders::cast::vec_to_mat( sfg, sfg_rows, id );
}

// [[Rcpp::export]]
SEXP rcpp_mat_to_mat( Rcpp::NumericMatrix sfg ) {
  double id = 1;
  R_xlen_t sfg_rows = 0;
  return sfheaders::cast::mat_to_mat( sfg, sfg_rows, id );
}


// [[Rcpp::export]]
SEXP rcpp_listMat_to_mat( Rcpp::List sfg ) {
  double id = 1;
  R_xlen_t sfg_rows = 0;
  return sfheaders::cast::listMat_to_mat( sfg, sfg_rows, id );
}


// [[Rcpp::export]]
SEXP rcpp_listListMat_to_mat( Rcpp::List sfg ) {
  double id = 1;
  R_xlen_t sfg_rows = 0;
  return sfheaders::cast::listListMat_to_mat( sfg, sfg_rows, id );
}


// [[Rcpp::export]]
SEXP rcpp_listMat_to_listMat( Rcpp::List sfg ) {
  double id = 1;
  R_xlen_t sfg_rows = 0;
  return sfheaders::cast::listMat_to_listMat( sfg, sfg_rows, id );
}


// [[Rcpp::export]]
SEXP rcpp_listListMat_to_listMat( Rcpp::List sfg ) {
  double id = 1;
  R_xlen_t sfg_rows = 0;
  return sfheaders::cast::listListMat_to_listMat( sfg, sfg_rows, id );
}
