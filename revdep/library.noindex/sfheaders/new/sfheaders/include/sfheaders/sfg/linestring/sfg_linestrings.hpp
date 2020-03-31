#ifndef R_SFHEADERS_SFG_LINESTRINGS_H
#define R_SFHEADERS_SFG_LINESTRINGS_H

#include <Rcpp.h>
#include "sfheaders/sfg/linestring/sfg_linestring.hpp"

namespace sfheaders {
namespace sfg {

  inline Rcpp::List sfg_linestrings( Rcpp::List& lst, std::string xyzm ) {
    R_xlen_t n = lst.size();
    // Rcpp::Rcout << "linestring sizes: " << n << std::endl;
    R_xlen_t i;
    Rcpp::List sfcs(n);

    for( i = 0; i < n; ++i ) {
      SEXP x = lst[i];
      sfcs[i] = sfheaders::sfg::sfg_linestring( x, xyzm );
    }
    return sfcs;
  }

} // sfg
} // sfheaders


#endif
