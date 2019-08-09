#ifndef R_SFHEADERS_H
#define R_SFHEADERS_H

#include <Rcpp.h>

// // from r-spatial/sf
// #define SF_Unknown             0 /* sfc_GEOMETRY */
// #define SF_Point               1
// #define SF_LineString          2
// #define SF_Polygon             3
// #define SF_MultiPoint          4
// #define SF_MultiLineString     5
// #define SF_MultiPolygon        6
// #define SF_GeometryCollection  7
// #define SF_CircularString      8
// #define SF_CompoundCurve       9
// #define SF_CurvePolygon       10
// #define SF_MultiCurve         11
// #define SF_MultiSurface       12
// #define SF_Curve              13
// #define SF_Surface            14
// #define SF_PolyhedralSurface  15
// #define SF_TIN                16
// #define SF_Triangle           17

namespace sfheaders {

  // #nocov start
  template <int RTYPE>
  inline Rcpp::CharacterVector sfClass( Rcpp::Vector<RTYPE> v ) {
    return v.attr("class");
  }

  inline Rcpp::CharacterVector getSfClass( SEXP sf ) {

    switch( TYPEOF(sf) ) {
    case REALSXP:
      return sfClass<REALSXP>( sf );
    case VECSXP:
      return sfClass<VECSXP>( sf );
    case INTSXP:
      return sfClass<INTSXP>( sf );
    default: Rcpp::stop("unknown sf type");
    }
    return "";
  }

  template <int RTYPE>
  inline Rcpp::CharacterVector rClass( Rcpp::Vector<RTYPE> v ) {
    return v.attr("class");
  }

  inline Rcpp::CharacterVector getRClass( SEXP sf ) {

    switch( TYPEOF(sf) ) {
    case REALSXP:
      return rClass<REALSXP>( sf );
    case VECSXP:
      return rClass<VECSXP>( sf );
    case INTSXP:
      return rClass<INTSXP>( sf );
    }
    return "";
  }
  // #nocov end

} // sfheaders

#endif
