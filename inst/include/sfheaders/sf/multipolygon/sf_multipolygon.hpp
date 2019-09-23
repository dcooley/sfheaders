#ifndef R_SFHEADERS_SF_MULTIPOLYGON_H
#define R_SFHEADERS_SF_MULTIPOLYGON_H

#include <Rcpp.h>
#include "sfheaders/utils/sexp/sexp.hpp"
#include "sfheaders/sf/sf_utils.hpp"
#include "sfheaders/sfc/multipolygon/sfc_multipolygon.hpp"
#include "sfheaders/utils/unique/unique_ids.hpp"
#include "sfheaders/shapes/shapes.hpp"

namespace sfheaders {
namespace sf {

inline SEXP sf_multipolygon(
    SEXP& x,
    SEXP& geometry_cols,
    SEXP& multipolygon_id,
    SEXP& polygon_id,
    SEXP& linestring_id,
    bool close = true
) {
  Rcpp::List sfc = sfheaders::sfc::sfc_multipolygon( x, geometry_cols, multipolygon_id, polygon_id, linestring_id, close );

  SEXP ids = sfheaders::utils::get_ids( x, multipolygon_id );
  Rcpp::DataFrame sf = sfheaders::sf::make_sf( sfc, ids );
  return sf;
}

} // sfc
} // sfheaders

#endif
