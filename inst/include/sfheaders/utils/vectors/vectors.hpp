#ifndef R_SFHEADERS_UTILS_VECTORS_H
#define R_SFHEADERS_UTILS_VECTORS_H

#include <Rcpp.h>
#include "sfheaders/utils/sexp/sexp.hpp"

namespace sfheaders {
namespace utils {

  inline int where_is(
      Rcpp::String to_find,
      Rcpp::StringVector& sv ) {
    int n = sv.size();
    int i;
    for( i = 0; i < n; i++ ) {
      if ( to_find == sv[i] ) {
        return i;
      }
    }
    return -1;
  }

  inline Rcpp::IntegerVector where_is(
      Rcpp::StringVector& param_value,
      Rcpp::StringVector& data_names) {

    int n = param_value.size();
    int i;
    Rcpp::IntegerVector res( n );
    for ( i = 0; i < n; i++ ) {
      Rcpp::String to_find = param_value[i];
      res[i] = where_is( to_find, data_names );
    }
    return res;
  }

  inline SEXP concatenate_vectors(
    SEXP& vec_1,
    SEXP& vec_2
  ) {

    if( TYPEOF( vec_1 ) != TYPEOF( vec_2 ) ) {
      Rcpp::stop("sfheaders - different vector types found");
    }

    // else - combine vec_1 & vec_2 into a single vector
    int n_1 = sfheaders::utils::get_sexp_length( vec_1 );
    int n_2 = sfheaders::utils::get_sexp_length( vec_2 );
    int n = n_1 + n_2;
    int i;

    switch(TYPEOF( vec_1 ) ) {
    case INTSXP: {
      Rcpp::IntegerVector iv_1 = Rcpp::as< Rcpp::IntegerVector >( vec_1 );
      Rcpp::IntegerVector iv_2 = Rcpp::as< Rcpp::IntegerVector >( vec_2 );

      Rcpp::IntegerVector iv( n );

      if( n_1 == 1 ) {
        iv[0] = iv_1[0];
      } else {
        for( i = 0; i < n_1; i++ ) {
          iv[i] = iv_1[i];
        }
      }

      if( n_2 == 1 ) {
        iv[ n_1 ] = iv_2[0];
      } else {
        int idx = 0;
        for( i = n_1; i < n; i++ ) {
          iv[i] = iv_2[ idx ];
          idx++;
        }
      }

      Rcpp::IntegerVector iv2 = Rcpp::sort_unique( iv );

      return iv2;
    }
    case REALSXP: {
      Rcpp::NumericVector nv_1 = Rcpp::as< Rcpp::NumericVector >( vec_1 );
      Rcpp::NumericVector nv_2 = Rcpp::as< Rcpp::NumericVector >( vec_2 );

      Rcpp::NumericVector nv( n );

      if( n_1 == 1 ) {
        nv[0] = nv_1[0];
      } else {
        for( i = 0; i < n_1; i++ ) {
          nv[i] = nv_1[i];
        }
      }

      if( n_2 == 1 ) {
        nv[ n_1 ] = nv_2[0];
      } else {
        int idx = 0;
        for( i = n_1; i < n; i++ ) {
          nv[i] = nv_2[ idx ];
          idx++;
        }
      }

      Rcpp::NumericVector nv2 = Rcpp::sort_unique( nv );

      return nv2;
    }
    case STRSXP: {
      Rcpp::StringVector sv_1 = Rcpp::as< Rcpp::StringVector >( vec_1 );
      Rcpp::StringVector sv_2 = Rcpp::as< Rcpp::StringVector >( vec_2 );

      Rcpp::StringVector sv( n );

      for( i = 0; i < n_1; i++ ) {
        sv[i] = sv_1[i];
      }

      int idx = 0;
      for( i = n_1; i < n; i++ ) {
        sv[i] = sv_2[ idx ];
        idx++;
      }

      return sv;
    }
    default: {
      Rcpp::stop("sfheaders - can't combine columns");  // #nocov
    }
    }

    return Rcpp::List::create(); // never reaches

  }


} // utils
} // sfheaders


#endif
