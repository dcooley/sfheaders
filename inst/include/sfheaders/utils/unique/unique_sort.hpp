#ifndef R_SFHEADERS_UTILS_UNIQUE_H
#define R_SFHEADERS_UTILS_UNIQUE_H

#include <Rcpp.h>

namespace sfheaders {
namespace utils {

  template <int RTYPE>
  inline SEXP sexp_unique(Rcpp::Vector< RTYPE > v) {
    return Rcpp::sort_unique( v );
  }

  inline SEXP get_sexp_unique( SEXP s ) {

    switch( TYPEOF( s ) ) {
    case REALSXP:
      return sexp_unique< REALSXP >( s );
    case INTSXP:
      return sexp_unique< INTSXP >( s );
    case STRSXP:
      return sexp_unique< STRSXP >( s );
    default: Rcpp::stop("sfheaders - unknown vector type"); // #nocov
    }
    return 0;
  }

} // utils
} // sfheaders


#endif
