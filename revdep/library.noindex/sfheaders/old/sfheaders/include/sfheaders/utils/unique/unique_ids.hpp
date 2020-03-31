#ifndef R_SFHEADERS_UTILS_UNIQUE_IDS_H
#define R_SFHEADERS_UTILS_UNIQUE_IDS_H

#include <Rcpp.h>

#include "sfheaders/utils/unique/unique_sort.hpp"

namespace sfheaders {
namespace utils {

  inline SEXP get_ids(
      SEXP& x,
      int& id_col
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      Rcpp::IntegerVector ids = im( Rcpp::_, id_col );
      SEXP unique_ids = sfheaders::utils::get_sexp_unique( ids );
      return unique_ids;
    }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      Rcpp::NumericVector ids = nm( Rcpp::_, id_col );
      SEXP unique_ids = sfheaders::utils::get_sexp_unique( ids );
      return unique_ids;
    }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      SEXP ids = df[ id_col ];
      SEXP unique_ids = sfheaders::utils::get_sexp_unique( ids );
      return unique_ids;
    }
    }
    default: {
      Rcpp::stop("sfheaders - could not get id column");  // #nocov
    }
    }
    return Rcpp::List::create();
  }

  inline SEXP get_ids(
      SEXP& x,
      Rcpp::String& id_col
  ) {

    Rcpp::DataFrame df;

    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
      df = Rcpp::as< Rcpp::DataFrame >( x );
      break;
      // Rcpp::IntegerVector ids = im( Rcpp::_, id_col );
      // SEXP unique_ids = sfheaders::utils::get_sexp_unique( ids );
      // return unique_ids;
    }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
      df = Rcpp::as< Rcpp::DataFrame >( x );
      break;
      // Rcpp::NumericVector ids = nm( Rcpp::_, id_col );
      // SEXP unique_ids = sfheaders::utils::get_sexp_unique( ids );
      // return unique_ids;
    }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      df = Rcpp::as< Rcpp::DataFrame >( x );
      break;
    }
    }
    default: {
      Rcpp::stop("sfheaders - could not get id column");  // #nocov
    }
    }

    SEXP ids = df[ id_col ];
    //Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( ids );

    SEXP unique_ids = sfheaders::utils::get_sexp_unique( ids );
    return unique_ids;
  }

  inline SEXP get_ids(
      SEXP& x,
      SEXP& id_col
  ) {

    if( Rf_isNull( id_col ) ) {

      Rcpp::IntegerVector ids(1);
      ids[0] = 1;
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
      Rcpp::stop("sfheaders - can't determine id column type"); // #nocov
    }
    }
    return Rcpp::List::create();
  }

} // utils
} // sfheaders

#endif
