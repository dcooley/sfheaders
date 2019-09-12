#ifndef R_SFHEADERS_SF_H
#define R_SFHEADERS_SF_H

#include <Rcpp.h>
#include "sfheaders/sf/point/sf_point.hpp"
#include "sfheaders/sf/multipoint/sf_multipoint.hpp"
#include "sfheaders/sf/linestring/sf_linestring.hpp"
#include "sfheaders/sf/multilinestring/sf_multilinestring.hpp"
#include "sfheaders/sf/polygon/sf_polygon.hpp"
#include "sfheaders/sf/multipolygon/sf_multipolygon.hpp"

namespace sfheaders {
namespace sfc {

  inline SEXP to_sfc( SEXP& x, std::string geom_type ) {
    if( geom_type == "POINT" ) {
      return sfheaders::sf::sf_point( x );
    } else if ( geom_type == "MULTIPOINT" ) {
      return sfheaders::sf::sf_multipoint( x );
    } else if ( geom_type == "LINESTRING" ) {
      return sfheaders::sf::sf_linestring( x );
    } else if ( geom_type == "MULTIILNESTRING" ) {
      return sfheaders::sf::sf_multilinestring( x );
    } else if ( geom_type == "POLYGON" ) {
      return sfheaders::sf::sf_polygon( x );
    } else if ( geom_type == "MULTIPOLYGON" ) {
      return sfheaders::sf::sf_multipolygon( x );
    }

    Rcpp::stop("sfheaders - unknown sfc geometry type");
    return Rcpp::List::create();
  }

  inline SEXP to_sfc( SEXP& x, std::string geom_type, SEXP geometry_columns ) {
    if( geom_type == "POINT" ) {
      return sfheaders::sf::sf_point( x, geometry_columns );
    } else if ( geom_type == "MULTIPOINT" ) {
      return sfheaders::sf::sf_multipoint( x, geometry_columns );
    } else if ( geom_type == "LINESTRING" ) {
      return sfheaders::sf::sf_linestring( x, geometry_columns );
    } else if ( geom_type == "MULTIILNESTRING" ) {
      return sfheaders::sf::sf_multilinestring( x, geometry_columns );
    } else if ( geom_type == "POLYGON" ) {
      return sfheaders::sf::sf_polygon( x, geometry_columns );
    } else if ( geom_type == "MULTIPOLYGON" ) {
      return sfheaders::sf::sf_multipolygon( x, geometry_columns );
    }

    Rcpp::stop("sfheaders - unknown sfc geometry type");
    return Rcpp::List::create(); // never reaches
  }

} // sf
} // sfheaders

#endif
