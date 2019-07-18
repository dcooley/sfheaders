#ifndef R_SFHEADERS_SFG_POINTS_H
#define R_SFHEADERS_SFG_POINTS_H

#include <Rcpp.h>
#include "sfheaders/sfg/point/sfg_point.hpp"

namespace sfheaders {
namespace sfg {

  Rcpp::List sfg_points( Rcpp::List& lst ) {
    size_t n = lst.size();
    size_t i;
    Rcpp::List sfcs(n);

    for( i = 0; i < n; i++ ) {
      SEXP x = lst[i];
      sfcs[i] = sfheaders::sfg::sfg_point( x );
    }
    return sfcs;
  }

} // sfg
} // sfheaders


#endif
