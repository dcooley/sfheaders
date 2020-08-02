#include <Rcpp.h>
#include "geometries/utils/lists/list.hpp"

// [[Rcpp::export]]
Rcpp::List rcpp_fill_list( Rcpp::NumericVector v, Rcpp::IntegerMatrix line_ids ) {
  return geometries::utils::fill_list( v, line_ids );
}

// [[Rcpp::export]]
Rcpp::List rcpp_list_sizes( Rcpp::List lst ) {
  R_xlen_t total_size = 0;
  int existing_type = 10;
  Rcpp::List lst_sizes = geometries::utils::list_size( lst, total_size, existing_type );
  return Rcpp::List::create(
    Rcpp::_["elements"] = lst_sizes,
    Rcpp::_["total"] = total_size
  );
}

// [[Rcpp::export]]
int rcpp_list_type( Rcpp::List lst ) {
  R_xlen_t total_size = 0;
  int existing_type = 10;
  Rcpp::List lst_sizes = geometries::utils::list_size( lst, total_size, existing_type );
  return existing_type;
}

// [[Rcpp::export]]
SEXP rcpp_unlist_list( Rcpp::List lst ) {
  R_xlen_t total_size = 0;
  int existing_type = 10;
  R_xlen_t position = 0;
  Rcpp::List lst_sizes = geometries::utils::list_size( lst, total_size, existing_type );
  switch( existing_type ) {
  case LGLSXP: {
    Rcpp::LogicalVector lv( total_size );
    geometries::utils::unlist_list( lst, lst_sizes, lv, position );
    return lv;
  }
  case INTSXP: {
    Rcpp::IntegerVector iv( total_size );
    geometries::utils::unlist_list( lst, lst_sizes, iv, position );
    return iv;
  }
  case REALSXP: {
    Rcpp::NumericVector nv( total_size );
    geometries::utils::unlist_list( lst, lst_sizes, nv, position );
    return nv;
  }
  default: {
    Rcpp::StringVector sv( total_size );
    geometries::utils::unlist_list( lst, lst_sizes, sv, position );
    return sv;
  }
  }

  Rcpp::stop("sfheaders - couldn't unlist this object");
  return lst; // #nocov - never reaches

}
