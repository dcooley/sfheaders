#ifndef R_SFHEADERS_SFC_MULTILINESTRINGS_H
#define R_SFHEADERS_SFC_MULTILINESTRINGS_H

#include <Rcpp.h>
#include "sfheaders/sfc/multilinestring/sfc_multilinestring.hpp"

namespace sfheaders {
namespace sfc {

  inline Rcpp::List sfc_multilinestrings( Rcpp::List& lst ) {
    size_t n = lst.size();
    size_t i;
    Rcpp::List sfcs(n);

    for( i = 0; i < n; i++ ) {
      SEXP x = lst[i];
      sfcs[i] = sfheaders::sfc::sfc_multilinestring( x );
    }
    return sfcs;
  }


} // sfc
} // sfheaders

#endif
