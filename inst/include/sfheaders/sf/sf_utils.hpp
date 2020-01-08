#ifndef R_SFHEADERS_SF_UTILS_H
#define R_SFHEADERS_SF_UTILS_H

namespace sfheaders {
namespace sf {

  // TODO
  // - make_sf( Rcpp::List& sfc, Rcpp::List& data_cols ) {}

  // issue 41 - will subset a vector
  inline void subset_properties(
      Rcpp::List& res,
      SEXP& v,
      Rcpp::IntegerVector& subset_index,
      R_xlen_t& i
  ) {

    switch( TYPEOF( v ) ) {
    case LGLSXP: {
      Rcpp::LogicalVector lv = Rcpp::as< Rcpp::LogicalVector >( v );
      res[ i ] = lv[ subset_index ];
      break;
    }
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( v );
      res[ i ] = iv[ subset_index ];
      break;
    }
    case REALSXP: {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( v );
      res[ i ] = nv[ subset_index ];
      break;
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( v );
      res[ i ] = sv[ subset_index ];
      break;
    }
    case CPLXSXP: {
      Rcpp::ComplexVector cv = Rcpp::as< Rcpp::ComplexVector >( v );
      res[ i ] = cv[ subset_index ];
      break;
    }
    case RAWSXP: {
      Rcpp::RawVector rv = Rcpp::as< Rcpp::RawVector >( v );
      res[ i ] = rv[ subset_index ];
      break;
    }
    default: {
      Rcpp::stop("sfheaders - unsupported column type using keep = TRUE");
    }
    }
  }

  inline void attach_dataframe_attributes( Rcpp::List& df, R_xlen_t& n_row ) {
    df.attr("class") = Rcpp::CharacterVector::create("sf", "data.frame");
    df.attr("sf_column") = "geometry";

    if( n_row == 0 ) {
      df.attr("row.names") = Rcpp::IntegerVector(0);;
    } else {
      Rcpp::IntegerVector rn = Rcpp::seq( 1, n_row );
      df.attr("row.names") = rn;
    }
  }


  inline SEXP make_sf( Rcpp::List& sfc ) {

    Rcpp::List df = Rcpp::List::create(
      Rcpp::Named("geometry") = sfc
    );

    R_xlen_t n_row = sfc.length();
    attach_dataframe_attributes( df, n_row );

    return df;

  }

  inline SEXP make_sf( Rcpp::List& sfc, Rcpp::IntegerVector& iv ) {

    Rcpp::List df = Rcpp::List::create(
      Rcpp::Named("id") = iv,
      Rcpp::Named("geometry") = sfc
    );

    R_xlen_t n_row = sfc.length();
    attach_dataframe_attributes( df, n_row );

    return df;
  }

  inline SEXP make_sf( Rcpp::List& sfc, Rcpp::NumericVector& nv ) {
    Rcpp::List df = Rcpp::List::create(
      Rcpp::Named("id") = nv,
      Rcpp::Named("geometry") = sfc
    );

    R_xlen_t n_row = sfc.length();
    attach_dataframe_attributes( df, n_row );

    return df;
  }

  inline SEXP make_sf( Rcpp::List& sfc, Rcpp::StringVector& sv ) {
    Rcpp::List df = Rcpp::List::create(
      Rcpp::Named("id") = sv,
      Rcpp::Named("geometry") = sfc
    );

    R_xlen_t n_row = sfc.length();
    attach_dataframe_attributes( df, n_row );

    return df;
  }


  inline SEXP make_sf(
      Rcpp::List& sfc,
      SEXP& ids
  ) {

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
