

#include <Rcpp.h>
//#include "sfheaders/sf/sf.hpp"

#include "sfheaders/sf/point/sf_point.hpp"
#include "sfheaders/sf/multipoint/sf_multipoint.hpp"
#include "sfheaders/sf/linestring/sf_linestring.hpp"
#include "sfheaders/sf/multilinestring/sf_multilinestring.hpp"

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
Rcpp::DataFrame rcpp_sf_point( SEXP x, SEXP cols, SEXP point_id) {
  return sfheaders::sf::sf_point( x, cols, point_id );
}

// [[Rcpp::export]]
Rcpp::DataFrame rcpp_sf_multipoint( SEXP x, SEXP cols, SEXP multipoint_id) {
  return sfheaders::sf::sf_multipoint( x, cols, multipoint_id );
}


// [[Rcpp::export]]
Rcpp::DataFrame rcpp_sf_linestring( SEXP x, SEXP cols, SEXP linestring_id) {
  return sfheaders::sf::sf_linestring( x, cols, linestring_id );
}

// [[Rcpp::export]]
Rcpp::DataFrame rcpp_sf_multilinestring( SEXP x, SEXP cols, SEXP multilinestring_id, SEXP linestring_id) {
  return sfheaders::sf::sf_multilinestring( x, cols, multilinestring_id, linestring_id );
}


