#ifndef R_SFHEADERS_SF_H
#define R_SFHEADERS_SF_H

#include <Rcpp.h>

namespace sfheaders {
namespace sf {

  inline SEXP create_sf( Rcpp::List lst ) {

    Rcpp::DataFrame df = Rcpp::DataFrame::create(
      Rcpp::Named("id") = lst[0],
      Rcpp::Named("geometry") = lst[1]
    );

    // if (sfg_objects > 0 ) {
    //   Rcpp::IntegerVector nv = Rcpp::seq( 1, sfg_objects );
    //   properties.attr("row.names") = nv;
    // } else {
    //   properties.attr("row.names") = Rcpp::IntegerVector(0);
    // }
    df.attr("class") = Rcpp::CharacterVector::create("sf", "data.frame");
    df.attr("sf_column") = "geometry";

    return df;

  }

  inline SEXP make_sf( Rcpp::List& sfc, Rcpp::IntegerVector& iv ) {

    Rcpp::DataFrame df = Rcpp::DataFrame::create(
      Rcpp::Named("id") = iv,
      Rcpp::Named("geometry") = sfc
    );

    df.attr("class") = Rcpp::CharacterVector::create("sf", "data.frame");
    df.attr("sf_column") = "geometry";

    return df;
  }

  inline SEXP make_sf( Rcpp::List& sfc, Rcpp::NumericVector& nv ) {
    Rcpp::DataFrame df = Rcpp::DataFrame::create(
      Rcpp::Named("id") = nv,
      Rcpp::Named("geometry") = sfc
    );

    df.attr("class") = Rcpp::CharacterVector::create("sf", "data.frame");
    df.attr("sf_column") = "geometry";

    return df;
  }

  inline SEXP make_sf( Rcpp::List& sfc, Rcpp::StringVector& sv ) {
    Rcpp::DataFrame df = Rcpp::DataFrame::create(
      Rcpp::Named("id") = sv,
      Rcpp::Named("geometry") = sfc
    );

    df.attr("class") = Rcpp::CharacterVector::create("sf", "data.frame");
    df.attr("sf_column") = "geometry";

    return df;
  }


  inline SEXP make_sf( Rcpp::List& sfc, SEXP ids ) {

    switch( TYPEOF( ids ) ) {
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( ids );
      return make_sf( sfc, iv );
    }
    case REALSXP: {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( ids );
      return make_sf( sfc, nv );
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( ids );
      return make_sf( sfc, sv );
    }
    default: {
      Rcpp::stop("sfheaders - invalid sf id columns");
    }
    }

    return Rcpp::List::create();
  }


} // sf
} // sfheaders


#endif
