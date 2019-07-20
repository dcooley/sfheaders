#ifndef R_SFHEADERS_SF_POINT_H
#define R_SFHEADERS_SF_POINT_H

#include <Rcpp.h>
#include "sfheaders/shapes/list_mat/list_mat_id.hpp"
#include "sfheaders/sfc/point/sfc_point.hpp"
#include "sfheaders/sf/sf.hpp"

namespace sfheaders {
namespace sf {


  // inline SEXP sf_point(
  //   SEXP& x,
  //   SEXP& cols,
  //   SEXP& id_col
  // ) {
  //
  //   // the 'id_col' can be kept, because each row of a matrix/data.frame is a unique point
  //   Rcpp::List lst = sfheaders::shapes::get_listMatId( x, cols, id_col );
  //   // also need to create sfc_point....
  //   Rcpp::DataFrame sf = sfheaders::sf::create_sf( lst );
  //   return sf;
  // }

} // sfc
} // sfheaders

#endif
