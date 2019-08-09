#ifndef R_SFHEADERS_SFG_MULTILINESTRINGS_H
#define R_SFHEADERS_SFG_MULTILINESTRINGS_H

#include <Rcpp.h>
#include "sfheaders/sfg/multilinestring/sfg_multilinestring.hpp"

namespace sfheaders {
namespace sfg {

  inline Rcpp::List sfg_multilinestrings( Rcpp::List& lst ) {
    R_xlen_t n = lst.size();
    R_xlen_t i;
    Rcpp::List sfcs(n);

    for( i = 0; i < n; i++ ) {
      SEXP x = lst[i];
      sfcs[i] = sfheaders::sfg::sfg_multilinestring( x );
    }
    return sfcs;
  }

} // sfg
} // sfheaders

#endif
