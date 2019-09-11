#ifndef R_SFHEADERS_SF_MULTIPOINT_H
#define R_SFHEADERS_SF_MULTIPOINT_H

#include <Rcpp.h>
#include "sfheaders/utils/sexp/sexp.hpp"
#include "sfheaders/sf/sf_utils.hpp"
#include "sfheaders/sfc/multipoint/sfc_multipoint.hpp"
#include "sfheaders/utils/unique/unique_ids.hpp"
#include "sfheaders/shapes/shapes.hpp"

namespace sfheaders {
namespace sf {

inline SEXP sf_multipoint(
    SEXP& x,
    SEXP& geometry_cols,
    SEXP& multipoint_id
) {
  Rcpp::List sfc = sfheaders::sfc::sfc_multipoint( x, geometry_cols, multipoint_id );

  SEXP ids = sfheaders::utils::get_ids( x, multipoint_id );
  Rcpp::DataFrame sf = sfheaders::sf::make_sf( sfc, ids );
  return sf;
}

} // sfc
} // sfheaders

#endif
