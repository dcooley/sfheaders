#ifndef R_SFHEADERS_SF_H
#define R_SFHEADERS_SF_H

#include <Rcpp.h>
#include "sfheaders/sf/point/sf_point.hpp"
#include "sfheaders/sf/multipoint/sf_multipoint.hpp"
#include "sfheaders/sf/linestring/sf_linestring.hpp"
#include "sfheaders/sf/multilinestring/sf_multilinestring.hpp"
#include "sfheaders/sf/polygon/sf_polygon.hpp"
#include "sfheaders/sf/multipolygon/sf_multipolygon.hpp"

// TODO
// make an API entry point
// and ONLY this function will call the create_df() function
// or the make_sf() function

namespace sfheaders {
namespace api {

  inline Rcpp::DataFrame to_sf(
    SEXP& obj,
    SEXP& geometry_columns,
    SEXP& id_columns,
    SEXP& list_columns,
    bool& close,
    bool& keep,
    const std::string sf_type
  ) {

    Rcpp::List sf;
    if( sf_type == "POINT" ) {
      sf = sfheaders::sf::sf_point( obj, geometry_columns, keep );
    } else if ( sf_type == "MULTIPOINT" ) {
      sf = sfheaders::sf::sf_multipoint( obj, geometry_columns, id_columns, keep );
    } else if ( sf_type == "LINESTRING" ) {
      sf = sfheaders::sf::sf_linestring( obj, geometry_columns, id_columns, keep );
    }

    return sf;
 }

} // api
} // sfheaders


#endif
