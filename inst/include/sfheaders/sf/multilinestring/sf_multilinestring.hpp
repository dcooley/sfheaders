#ifndef R_SFHEADERS_SF_MULTILINESTRING_H
#define R_SFHEADERS_SF_MULTILINESTRING_H

#include <Rcpp.h>
#include "sfheaders/utils/sexp/sexp.hpp"
#include "sfheaders/sf/sf_utils.hpp"
#include "sfheaders/sfc/multilinestring/sfc_multilinestring.hpp"
#include "sfheaders/utils/unique/unique_ids.hpp"
#include "sfheaders/shapes/shapes.hpp"

namespace sfheaders {
namespace sf {

inline SEXP sf_multilinestring(
    SEXP& x,
    SEXP& geometry_cols,
    SEXP& multilinestring_id,
    SEXP& linestring_id
) {
  Rcpp::List sfc = sfheaders::sfc::sfc_multilinestring( x, geometry_cols, multilinestring_id, linestring_id );

  SEXP ids = sfheaders::utils::get_ids( x, multilinestring_id );
  Rcpp::DataFrame sf = sfheaders::sf::make_sf( sfc, ids );
  return sf;
}

} // sfc
} // sfheaders

#endif
