#ifndef R_SFHEADERS_SF_POINT_H
#define R_SFHEADERS_SF_POINT_H

#include <Rcpp.h>
#include "sfheaders/utils/sexp/sexp.hpp"
#include "sfheaders/sf/sf_utils.hpp"
#include "sfheaders/sfc/point/sfc_point.hpp"
#include "sfheaders/utils/unique/unique_ids.hpp"
#include "sfheaders/shapes/shapes.hpp"

namespace sfheaders {
namespace sf {

  inline SEXP sf_point(
      SEXP& x,
      SEXP& geometry_cols
  ) {

    // SEXP ids = sfheaders::utils::get_ids( x, point_id );
    Rcpp::List sfc = sfheaders::sfc::sfc_point( x, geometry_cols );

    Rcpp::DataFrame sf = sfheaders::sf::make_sf( sfc );
    return sf;
  }

} // sfc
} // sfheaders

#endif
