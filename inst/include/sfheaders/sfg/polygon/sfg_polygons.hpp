#ifndef R_SFHEADERS_SFG_POLYGONS_H
#define R_SFHEADERS_SFG_POLYGONS_H

#include <Rcpp.h>
#include "sfheaders/sfg/polygon/sfg_polygon.hpp"

namespace sfheaders {
namespace sfg {

  Rcpp::List sfg_polygons( Rcpp::List& lst ) {
    size_t n = lst.size();
    size_t i;
    Rcpp::List sfcs(n);

    for( i = 0; i < n; i++ ) {
      SEXP x = lst[i];
      sfcs[i] = sfheaders::sfg::sfg_polygon( x );
    }
    return sfcs;
  }

} // sfg
} // sfheaders

#endif
