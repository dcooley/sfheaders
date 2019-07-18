#ifndef R_SFHEADERS_SFC_MULTIPOLYGONS_H
#define R_SFHEADERS_SFC_MULTIPOLYGONS_H

#include <Rcpp.h>
#include "sfheaders/sfc/multipolygon/sfc_multipolygon.hpp"

namespace sfheaders {
namespace sfc {

  Rcpp::List sfc_multipolygons( Rcpp::List& lst ) {
    size_t n = lst.size();
    size_t i;
    Rcpp::List sfcs(n);

    for( i = 0; i < n; i++ ) {
      SEXP x = lst[i];
      sfcs[i] = sfheaders::sfc::sfc_multipolygon( x );
    }
    return sfcs;
  }

} // sfc
} // sfheaders

#endif
