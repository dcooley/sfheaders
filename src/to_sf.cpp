

#include <Rcpp.h>
//#include "sfheaders/sf/sf.hpp"

#include "sfheaders/sf/sf.hpp"
//#include "sfheaders/sf/point/sf_point.hpp"
//#include "sfheaders/sf/multipoint/sf_multipoint.hpp"
//#include "sfheaders/sf/linestring/sf_linestring.hpp"
//#include "sfheaders/sf/multilinestring/sf_multilinestring.hpp"
//#include "sfheaders/sf/polygon/sf_polygon.hpp"
//#include "sfheaders/sf/multipolygon/sf_multipolygon.hpp"

// /*
//  * rcpp_make_sf
//  *
//  * Creates an 'sf' object from an sfc, and a vector of ids
//  */
// // [[Rcpp::export]]
// SEXP rcpp_make_sf( Rcpp::List sfc, SEXP ids ) {
//   return sfheaders::sf::make_sf( sfc, ids );
// }

// [[Rcpp::export]]
SEXP rcpp_to_sf(
    SEXP obj,
    SEXP geometry_columns,
    SEXP multipoint_id,
    SEXP linestring_id,
    SEXP multilinestring_id,
    SEXP polygon_id,
    SEXP multipolygon_id,
    SEXP list_columns,
    bool close,
    bool keep,
    std::string xyzm,
    std::string sf_type
) {
  return sfheaders::api::to_sf(
    obj,
    geometry_columns,
    multipoint_id,
    linestring_id,
    multilinestring_id,
    polygon_id,
    multipolygon_id,
    list_columns,
    close,
    keep,
    xyzm,
    sf_type
  );
}


// [[Rcpp::export]]
SEXP rcpp_sf_point( SEXP x, SEXP cols, bool keep, std::string xyzm ) {
  return sfheaders::api::rcpp_sf_point( x, cols, keep, xyzm );
}

// [[Rcpp::export]]
SEXP rcpp_sf_multipoint( SEXP x, SEXP cols, SEXP multipoint_id, bool keep, std::string xyzm ) {
  return sfheaders::api::rcpp_sf_multipoint( x, cols, multipoint_id, keep, xyzm );
}


// [[Rcpp::export]]
SEXP rcpp_sf_linestring( SEXP x, SEXP cols, SEXP linestring_id, bool keep, std::string xyzm ) {
  return sfheaders::sf::sf_linestring( x, cols, linestring_id, keep, xyzm );
}

// [[Rcpp::export]]
SEXP rcpp_sf_multilinestring( SEXP x, SEXP cols, SEXP multilinestring_id, SEXP linestring_id, bool keep, std::string xyzm ) {
  return sfheaders::sf::sf_multilinestring( x, cols, multilinestring_id, linestring_id, keep, xyzm );
}

// [[Rcpp::export]]
SEXP rcpp_sf_polygon( SEXP x, SEXP cols, SEXP polygon_id, SEXP linestring_id, bool close, bool keep, std::string xyzm ) {
  return sfheaders::sf::sf_polygon( x, cols, polygon_id, linestring_id, xyzm, close, keep );
}

// [[Rcpp::export]]
SEXP rcpp_sf_multipolygon( SEXP x, SEXP cols, SEXP multipolygon_id, SEXP polygon_id, SEXP linestring_id, bool close, bool keep, std::string xyzm ) {
  return sfheaders::sf::sf_multipolygon( x, cols, multipolygon_id, polygon_id, linestring_id, xyzm, close, keep );
}

