#ifndef R_SFHEADERS_SFC_MULTIPOLYGONS_H
#define R_SFHEADERS_SFC_MULTIPOLYGONS_H

#include <Rcpp.h>
#include "sfheaders/sfc/multipolygon/sfc_multipolygon.hpp"

namespace sfheaders {
namespace sfc {

  inline Rcpp::List sfc_multipolygons( Rcpp::List& lst, bool close = true ) {
    R_xlen_t n = lst.size();
    R_xlen_t i;
    Rcpp::List sfcs(n);

    for( i = 0; i < n; ++i ) {
      SEXP x = lst[i];
      sfcs[i] = sfheaders::sfc::sfc_multipolygon( x, close );
    }
    return sfcs;
  }

} // sfc
} // sfheaders

#endif
