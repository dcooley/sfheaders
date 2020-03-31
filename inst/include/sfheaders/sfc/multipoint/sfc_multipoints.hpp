#ifndef R_SFHEADERS_SFC_MULTIPOINTS_H
#define R_SFHEADERS_SFC_MULTIPOINTS_H

#include <Rcpp.h>
#include "sfheaders/sfc/multipoint/sfc_multipoint.hpp"

namespace sfheaders {
namespace sfc {

  inline Rcpp::List sfc_multipoints( Rcpp::List& lst, std::string xyzm ) {
    R_xlen_t n = lst.size();
    R_xlen_t i;
    Rcpp::List sfcs(n);

    for( i = 0; i < n; ++i ) {
      SEXP x = lst[i];
      sfcs[i] = sfheaders::sfc::sfc_multipoint( x, xyzm );
    }
    return sfcs;
  }

} // sfc
} // sfheaders

#endif
