#ifndef R_SFHEADERS_SFC_POLYGONS_H
#define R_SFHEADERS_SFC_POLYGONS_H

#include <Rcpp.h>
#include "sfheaders/sfc/polygon/sfc_polygon.hpp"

namespace sfheaders {
namespace sfc {

  inline Rcpp::List sfc_polygons( Rcpp::List& lst ) {
    size_t n = lst.size();
    size_t i;
    Rcpp::List sfcs(n);

    for( i = 0; i < n; i++ ) {
      SEXP x = lst[i];
      sfcs[i] = sfheaders::sfc::sfc_polygon( x );
    }
    return sfcs;
  }

} // sfc
} // sfheaders

#endif