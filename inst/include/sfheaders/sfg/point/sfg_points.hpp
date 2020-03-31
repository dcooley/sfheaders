#ifndef R_SFHEADERS_SFG_POINTS_H
#define R_SFHEADERS_SFG_POINTS_H

#include <Rcpp.h>
#include "sfheaders/sfg/point/sfg_point.hpp"

namespace sfheaders {
namespace sfg {

  inline Rcpp::List sfg_points( Rcpp::List& lst, std::string xyzm ) {
    R_xlen_t n = lst.size();
    R_xlen_t i;
    Rcpp::List sfcs( n );

    for( i = 0; i < n; ++i ) {
      SEXP x = lst[ i ];
      sfcs[ i ] = sfheaders::sfg::sfg_point( x, xyzm );
    }
    return sfcs;
  }

  inline Rcpp::List sfg_points( Rcpp::NumericMatrix& nm, std::string xyzm ) {
    R_xlen_t n = nm.nrow();
    R_xlen_t i;
    Rcpp::List sfcs( n );
    for( i = 0; i < n; ++i ) {
      Rcpp::NumericVector nv = nm( i, Rcpp::_ );
      sfcs[ i ] = sfheaders::sfg::sfg_point( nv, xyzm );
    }
    return sfcs;
  }

} // sfg
} // sfheaders


#endif
