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

// [[Rcpp::export]]
Rcpp::List rcpp_list_sizes( Rcpp::List lst ) {
  int total_size = 0;
  int existing_type = 10;
  Rcpp::List lst_sizes = sfheaders::df::list_size( lst, total_size, existing_type );
  return Rcpp::List::create(
    Rcpp::_["elements"] = lst_sizes,
    Rcpp::_["total"] = total_size
  );
}

// [[Rcpp::export]]
int rcpp_list_type( Rcpp::List lst ) {
  int total_size = 0;
  int existing_type = 10;
  Rcpp::List lst_sizes = sfheaders::df::list_size( lst, total_size, existing_type );
  return existing_type;
}

// [[Rcpp::export]]
SEXP rcpp_unlist_list( Rcpp::List lst ) {
  int total_size = 0;
  int existing_type = 10;
  int position = 0;
  Rcpp::List lst_sizes = sfheaders::df::list_size( lst, total_size, existing_type );
  switch( existing_type ) {
  case LGLSXP: {
    Rcpp::LogicalVector lv( total_size );
    sfheaders::df::unlist_list( lst, lst_sizes, lv, position );
    return lv;
  }
  case INTSXP: {
    Rcpp::IntegerVector iv( total_size );
    sfheaders::df::unlist_list( lst, lst_sizes, iv, position );
    return iv;
  }
  case REALSXP: {
    Rcpp::NumericVector nv( total_size );
    sfheaders::df::unlist_list( lst, lst_sizes, nv, position );
    return nv;
  }
  default: {
    Rcpp::StringVector sv( total_size );
    sfheaders::df::unlist_list( lst, lst_sizes, sv, position );
    return sv;
  }
  }

  Rcpp::stop("sfheaders - couldn't unlist this object");
  return lst; // #nocov - never reaches

}
