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
    SEXP& point_id,
    SEXP& multipoint_id,
    SEXP& linestring_id,
    SEXP& multilinestring_id,
    SEXP& polygon_id,
    SEXP& multipolygon_id,
    SEXP& list_columns,
    bool& close,
    bool& keep,
    const std::string sf_type
  ) {
      // TODO - Make the id_columns the correct type
      // then inside each if() condition, split it by polygon_id & linestring_id (for example)
      // assume the 0th index is the outer-most geometry
      // as this function will be called from R this is controllable.

    Rcpp::List sf;

    if( sf_type == "POINT" ) {
      sf = sfheaders::sf::sf_point( obj, geometry_columns, keep );
    } else if ( sf_type == "MULTIPOINT" ) {
      sf = sfheaders::sf::sf_multipoint( obj, geometry_columns, multipoint_id, keep );
    } else if ( sf_type == "LINESTRING" ) {
      sf = sfheaders::sf::sf_linestring( obj, geometry_columns, linestring_id, keep );
    } else if ( sf_type == "MULTILINESTRING" ) {
      sf = sfheaders::sf::sf_multilinestring( obj, geometry_columns, multilinestring_id, linestring_id, keep );
    } else if ( sf_type == "POLYGON" ) {
      sf = sfheaders::sf::sf_polygon( obj, geometry_columns, polygon_id, linestring_id, close, keep );
    } else if ( sf_type == "MULTIPOLYGON" ) {
      sf = sfheaders::sf::sf_multipolygon( obj, geometry_columns, multipolygon_id, polygon_id, linestring_id, close, keep );
    } else {
      Rcpp::stop("sfheaders - unknown sf type");
    }

    return sf;
 }

} // api
} // sfheaders


#endif
