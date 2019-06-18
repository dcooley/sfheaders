#ifndef R_SFHEADERS_SFG_H
#define R_SFHEADERS_SFG_H

#include "sfheaders/sfg/point/sfg_point.hpp"
#include "sfheaders/sfg/multipoint/sfg_multipoint.hpp"
#include "sfheaders/sfg/linestring/sfg_linestring.hpp"
#include "sfheaders/sfg/multilinestring/sfg_multilinestring.hpp"

// TODO
// - to_sfg() function, which works out, given the object and parameters which to_* to use
// - where parameters are point_id, linestring_id, etc

namespace sfheaders {
namespace sfg {

  // optinos
  // - defined parameter column-ids - use them
  // - params not defined, best-guess given number of columns / size of object.

  // assumes the simpliest structures : POINT, LINESTRING, POLYGON
  inline SEXP to_sfg( SEXP& x ) {
    // guessing the type, given the object x

    switch( TYPEOF( x ) ) {
    case INTSXP: {
    if( Rf_isMatrix( x ) ) {
      // matrix can be MULTIPOINT or LINESTRING
      //return sfheaders::sfg::to_linestring( x );
      return sfheaders::sfg::to_linestring( x );
    } else {
      // vector is POINT
      return sfheaders::sfg::to_point( x );
    }
    }
    case REALSXP: {
    if( Rf_isMatrix( x ) ) {
      // matrix can be MULTIPOINT or LINESTRING
      return sfheaders::sfg::to_linestring( x );
    } else {
      // vector is POINT
      return sfheaders::sfg::to_point( x );
    }
    }
    case VECSXP: {
      // LIST is POLYIGON
      // list of lists is MULTIPOLYGON
      // or can be a GEOMETRYCOLLECTION
      // data.frame could be single POINT, MULTIPOINT or LINESTRING
    }
    default: {
      Rcpp::stop("sfheaders - could not guess the geometry type");
    }
    }

    return Rcpp::List::create(); // never reaches?
  }

  inline SEXP to_sfg( SEXP& x, std::string geom_type ) {
    if( geom_type == "POINT" ) {
      // must be a vector
      return sfheaders::sfg::to_point( x );
    } else if ( geom_type == "MULTIPOINT" ) {
      return sfheaders::sfg::to_multipoint( x );
    } else if ( geom_type == "LINESTRING" ) {
      return sfheaders::sfg::to_linestring( x );
    } else if ( geom_type == "MULTIILNESTRING" ) {
      //return sfheaders::sfg::to_multilinestring( x );
    }

    return Rcpp::List::create();
  }

  inline SEXP to_sfg( SEXP& x, std::string geom_type, SEXP geometry_columns ) {
    if( geom_type == "POINT" ) {
      return sfheaders::sfg::to_point( x, geometry_columns );
    }

    return Rcpp::List::create(); // never reaches
  }


} // sfg
} // sfheaders

#endif
