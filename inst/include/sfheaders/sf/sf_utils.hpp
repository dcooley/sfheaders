#ifndef R_SFHEADERS_SF_UTILS_H
#define R_SFHEADERS_SF_UTILS_H

namespace sfheaders {
namespace sf {

  // TODO
  // - make_sf( Rcpp::List& sfc, Rcpp::List& data_cols ) {}

  inline SEXP make_sf( Rcpp::List& sfc ) {

    Rcpp::List df = Rcpp::List::create(
      Rcpp::Named("geometry") = sfc
    );

    df.attr("class") = Rcpp::CharacterVector::create("sf", "data.frame");
    df.attr("sf_column") = "geometry";

    Rcpp::IntegerVector rn = Rcpp::seq( 1, sfc.length() );
    df.attr("row.names") = rn;

    return df;

  }

  inline SEXP make_sf( Rcpp::List& sfc, Rcpp::IntegerVector& iv ) {

    Rcpp::List df = Rcpp::List::create(
      Rcpp::Named("id") = iv,
      Rcpp::Named("geometry") = sfc
    );

    df.attr("class") = Rcpp::CharacterVector::create("sf", "data.frame");
    df.attr("sf_column") = "geometry";

    Rcpp::IntegerVector rn = Rcpp::seq( 1, sfc.length() );
    df.attr("row.names") = rn;

    return df;
  }

  inline SEXP make_sf( Rcpp::List& sfc, Rcpp::NumericVector& nv ) {
    Rcpp::List df = Rcpp::List::create(
      Rcpp::Named("id") = nv,
      Rcpp::Named("geometry") = sfc
    );

    df.attr("class") = Rcpp::CharacterVector::create("sf", "data.frame");
    df.attr("sf_column") = "geometry";

    Rcpp::IntegerVector rn = Rcpp::seq( 1, sfc.length() );
    df.attr("row.names") = rn;

    return df;
  }

  inline SEXP make_sf( Rcpp::List& sfc, Rcpp::StringVector& sv ) {
    Rcpp::List df = Rcpp::List::create(
      Rcpp::Named("id") = sv,
      Rcpp::Named("geometry") = sfc
    );

    df.attr("class") = Rcpp::CharacterVector::create("sf", "data.frame");
    df.attr("sf_column") = "geometry";

    Rcpp::IntegerVector rn = Rcpp::seq( 1, sfc.length() );
    df.attr("row.names") = rn;

    return df;
  }


  inline SEXP make_sf(
      Rcpp::List& sfc,
      SEXP& ids
  ) {

    // if( Rf_isNull( ids ) ) {
    //   // need 1:n ids
    //   // int n_sfc = sfc.size();
    //   // Rcpp::IntegerVector ids2 = Rcpp::seq( 1, n_sfc );
    //   Rcpp::IntegerVector ids(1);
    //   ids[0] = 1;
    //   make_sf( sfc, ids );
    // }
    if( Rf_isNull( ids ) ) {
      make_sf( sfc );          // #nocov
    }

    switch( TYPEOF( ids ) ) {
    case LGLSXP: {}
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
      Rcpp::stop("sfheaders - invalid sf id columns");   // #nocov
    }
    }

    return Rcpp::List::create();
  }


} // sf
} // sfheaders

#endif
