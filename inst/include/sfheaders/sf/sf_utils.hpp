#ifndef R_SFHEADERS_SF_UTILS_H
#define R_SFHEADERS_SF_UTILS_H

#include "sfheaders/utils/vectors/vectors.hpp"

namespace sfheaders {
namespace sf {

  // TODO
  // - make_sf( Rcpp::List& sfc, Rcpp::List& data_cols ) {}

  // issue 41 - will subset a vector
  inline SEXP subset_properties(
      SEXP& v,
      Rcpp::IntegerVector& subset_index
  ) {

    switch( TYPEOF( v ) ) {
    case LGLSXP: {
      Rcpp::LogicalVector lv = Rcpp::as< Rcpp::LogicalVector >( v );
      return lv[ subset_index ];
    }
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( v );
      return iv[ subset_index ];
    }
    case REALSXP: {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( v );
      return nv[ subset_index ];
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( v );
      return sv[ subset_index ];
    }
    case CPLXSXP: {
      Rcpp::ComplexVector cv = Rcpp::as< Rcpp::ComplexVector >( v );
      return cv[ subset_index ];
    }
    case RAWSXP: {
      Rcpp::RawVector rv = Rcpp::as< Rcpp::RawVector >( v );
      return rv[ subset_index ];
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

  // where the input is a data.frame
  inline Rcpp::List create_sf(
      Rcpp::DataFrame& df,
      Rcpp::List& sfc,
      Rcpp::StringVector& property_cols,
      Rcpp::IntegerVector& property_idx,
      Rcpp::IntegerVector& row_idx
  ) {

    R_xlen_t n_col = property_idx.length();
    Rcpp::List sf( n_col + 1 );  // +1 == sfc
    R_xlen_t i;

    // fill columns of properties
    for( i = 0; i < n_col; ++i ) {
      int idx = property_idx[i];
      SEXP v = df[ idx ];
      sf[ i ] = subset_properties( v, row_idx );
    }

    // make data.frame
    Rcpp::String sfc_name = "geometry";
    Rcpp::StringVector res_names = sfheaders::utils::concatenate_vectors( property_cols, sfc_name );
    sf[ n_col ] = sfc;
    sf.names() = res_names;

    R_xlen_t n_row = row_idx.length();

    sfheaders::sf::attach_dataframe_attributes( sf, n_row );

    return sf;
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
