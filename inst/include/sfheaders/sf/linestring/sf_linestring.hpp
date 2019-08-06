#ifndef R_SFHEADERS_SF_LINESTRING_H
#define R_SFHEADERS_SF_LINESTRING_H

#include <Rcpp.h>
#include "sfheaders/utils/sexp/sexp.hpp"
#include "sfheaders/sf/sf.hpp"
#include "sfheaders/sfc/linestring/sfc_linestring.hpp"

namespace sfheaders {
namespace sf {

// the design should be;
// given the objet, get the 'ids' out here;
// then create an sfc
// and attach the ids
//
// BUT, this is a two-step id extract
// and is there a guarantee they'll be combined in the correct order??

  inline SEXP get_ids(
    SEXP& x,
    int& id_col
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      Rcpp::IntegerVector ids = im( Rcpp::_, id_col );
      return ids;
    }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      Rcpp::NumericVector ids = nm( Rcpp::_, id_col );
    }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );

    }
    }
    }
  }

  inline SEXP get_ids(
    SEXP& x,
    Rcpp::String& id_col
  ) {

  }

inline SEXP get_ids(
  SEXP& x,
  SEXP& id_col
) {
  if( Rf_isNull( id_col ) ) {
    size_t n_row = sfheaders::utils::sexp_n_row( x );
    Rcpp::IntegerVector ids = Rcpp::seq( 1, n_row );
    return ids;
  }
  switch( TYPEOF( id_col ) ) {
  case REALSXP: {}
  case INTSXP: {
    Rcpp::IntegerVector iv_id_col = Rcpp::as< Rcpp::IntegerVector >( id_col );
    int i_id_col = iv_id_col[0];
    return get_ids( x, i_id_col );
  }
  case STRSXP: {
    Rcpp::StringVector sv_id_col = Rcpp::as< Rcpp::StringVector >( id_col );
    Rcpp::String s_id_col = sv_id_col[0];
    return get_ids( x, s_id_col );
  }
  default: {
    Rcpp::stop("sfheaders - can't determine id column type");
  }
  }
  return Rcpp::List::create();
}


inline SEXP sf_linestring(
  SEXP& x,
  SEXP& geometry_cols,
  SEXP& linestring_id
) {



}


} // sfc
} // sfheaders

#endif
