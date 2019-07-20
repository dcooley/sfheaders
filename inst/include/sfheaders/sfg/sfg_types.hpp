#ifndef R_SFHEADERS_SFG_TYPES_H
#define R_SFHEADERS_SFG_TYPES_H

#include <Rcpp.h>

#include "sfheaders/sfg/sfg_attributes.hpp"
#include "sfheaders/sfg/sfg_dimension.hpp"

namespace sfheaders {
namespace sfg {

  const int SFG_POINT           = 1;
  const int SFG_MULTIPOINT      = 2;
  const int SFG_LINESTRING      = 3;
  const int SFG_MULTILINESTRING = 4;
  const int SFG_POLYGON         = 5;
  const int SFG_MULTIPOLYGON    = 6;

  inline std::string get_sfg_type( int sfg_type ) {
    switch( sfg_type ) {
    case SFG_POINT: { return "POINT"; }
    case SFG_MULTIPOINT: { return "MULTIPOING"; }
    case SFG_LINESTRING: { return "LINESTRING"; }
    case SFG_MULTILINESTRING: { return "MULTILINESTRING"; }
    case SFG_POLYGON: { return "POLYGON"; }
    case SFG_MULTIPOLYGON: { return "MULTIPOLYGON"; }
    default: {
      Rcpp::stop("sfheaders - unknown sfg type");
    }
    }
    return ""; // never reaches
  }

  inline SEXP make_sfg(
    Rcpp::IntegerMatrix& im,
    int sfg_type
  ) {

    size_t n_col = im.ncol();
    std::string dim = sfheaders::sfg::sfg_dimension( n_col );

    std::string geom_type = get_sfg_type( sfg_type );
    im.attr("class") = sfheaders::sfg::sfg_attributes( dim, geom_type );
    return im;
  }

  inline SEXP make_sfg(
      Rcpp::NumericMatrix& nm,
      int sfg_type
  ) {

    size_t n_col = nm.ncol();
    std::string dim = sfheaders::sfg::sfg_dimension( n_col );

    std::string geom_type = get_sfg_type( sfg_type );
    nm.attr("class") = sfheaders::sfg::sfg_attributes( dim, geom_type );
    return nm;
  }


} // sfg
} // sfheaders


#endif
