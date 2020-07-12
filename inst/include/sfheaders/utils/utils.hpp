#ifndef R_SFHEADERS_UTILS_H
#define R_SFHEADERS_UTILS_H

#include <Rcpp.h>
#include "geometries/utils/sexp/sexp.hpp"

namespace sfheaders {
namespace utils {

  inline bool is_null_geometry( Rcpp::IntegerVector& iv, std::string geom_type ) {
    int n = iv.length();
    if( geom_type == "POINT" ) {
      if ( iv[0] == NA_INTEGER || iv[1] == NA_INTEGER ) {
        return true;
      }
    } else if ( n == 0 ) { // #nocov
      return true;         // #nocov
    }
    return false;
  }

  inline bool is_null_geometry( Rcpp::NumericVector& nv, std::string geom_type ) {
    int n = nv.length();
    if( geom_type == "POINT" ) {

      if (ISNAN( nv[0] ) || ISNAN( nv[1] ) ) {
        return true;
      }
    } else if ( n == 0 ) { // #nocov
      return true;         // #nocov
    }
    return false;
  }

  inline bool is_null_geometry( SEXP& sfg, std::string geom_type ) {
    R_xlen_t n = geometries::utils::sexp_length( sfg );
    if( geom_type == "POINT" ) {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( sfg );
      if ( ISNAN( nv[0] ) ) {
        return true;
      }
    } else if ( n == 0 ) {   // #nocov
      return true;           // #nocov
    }
    return false;
  }

} // utils
} // sfheaders

#endif
