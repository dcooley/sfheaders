#include <Rcpp.h>
#include "sfheaders/df/sf.hpp"

// [[Rcpp::export]]
SEXP rcpp_sfg_to_df( SEXP sfg ) {
  return sfheaders::df::sfg_to_df( sfg );
}

// [[Rcpp::export]]
SEXP rcpp_sfc_to_df( Rcpp::List sfc ) {
  return sfheaders::df::sfc_to_df( sfc );
}

// [[Rcpp::export]]
SEXP rcpp_sf_to_df( Rcpp::DataFrame sf, bool fill = false ) {
  return sfheaders::df::sf_to_df( sf, fill );
}

// [[Rcpp::export]]
SEXP rcpp_sf_to_df_unlist( Rcpp::DataFrame sf, Rcpp::StringVector unlist, bool fill = false ) {
  return sfheaders::df::sf_to_df( sf, unlist, fill );
}
