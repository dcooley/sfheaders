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
