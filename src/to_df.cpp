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

// // TODO - remove this function for release
// // [[Rcpp::export]]
// SEXP rcpp_get_sfg_coordinates( SEXP sfg ) {
//   R_xlen_t sfc_rows = 0;
//
//   Rcpp::CharacterVector cls;
//   std::string dim;
//   std::string sfg_class;
//   int sfg_type;
//
//   cls = sfheaders::utils::getSfgClass( sfg );
//
//   dim = cls[0];
//
//   sfg_class = cls[1];
//   sfg_type = sfheaders::df::get_sfg_type( sfg_class );
//   return sfheaders::df::get_sfg_coordinates( sfg, sfc_rows, sfg_type );
// }

// // TODO - remove ths function for release
// // [[Rcpp::export]]
// Rcpp::List rcpp_collapse_list( Rcpp::List lst ) {
//
//   R_xlen_t total_rows = 5;
//   return sfheaders::df::collapse_list( lst, total_rows );
// }
