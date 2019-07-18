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

} // sf
} // sfheaders


#endif
