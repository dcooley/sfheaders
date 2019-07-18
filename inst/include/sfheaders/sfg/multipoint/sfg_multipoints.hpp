#ifndef R_SFHEADERS_SFG_MULTIPOINTS_H
#define R_SFHEADERS_SFG_MULTIPOINTS_H

#include <Rcpp.h>
#include "sfheaders/sfg/multipoint/sfg_multipoint.hpp"

namespace sfheaders {
namespace sfg {

  Rcpp::List sfg_multipoints( Rcpp::List& lst ) {
    size_t n = lst.size();
    size_t i;
    Rcpp::List sfcs(n);

    for( i = 0; i < n; i++ ) {
      SEXP x = lst[i];
      sfcs[i] = sfheaders::sfg::sfg_multipoint( x );
    }
    return sfcs;
  }

} // sfg
} // sfheaders


#endif
