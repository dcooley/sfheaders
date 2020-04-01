#ifndef R_SFHEADERS_SFG_POLYGONS_H
#define R_SFHEADERS_SFG_POLYGONS_H

#include <Rcpp.h>
#include "sfheaders/sfg/polygon/sfg_polygon.hpp"

namespace sfheaders {
namespace sfg {

  inline Rcpp::List sfg_polygons( Rcpp::List& lst, std::string xyzm, bool close = true ) {
    R_xlen_t n = lst.size();
    R_xlen_t i;
    Rcpp::List sfcs(n);

    for( i = 0; i < n; ++i ) {
      SEXP x = lst[i];
      sfcs[i] = sfheaders::sfg::sfg_polygon( x, xyzm, close );
    }
    return sfcs;
  }

} // sfg
} // sfheaders

#endif
