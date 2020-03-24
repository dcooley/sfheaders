#ifndef R_SFHEADERS_SF_UTILS_H
#define R_SFHEADERS_SF_UTILS_H

#include "sfheaders/utils/vectors/vectors.hpp"

namespace sfheaders {
namespace sf {

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
      Rcpp::stop("sfheaders - unsupported column type using keep = TRUE"); // #nocov
    }
    }
  }

  inline void attach_dataframe_attributes(
      Rcpp::List& df,
      R_xlen_t& n_row,
      std::string geometry_column = "geometry"
  ) {
    df.attr("class") = Rcpp::CharacterVector::create("sf", "data.frame");
    df.attr("sf_column") = geometry_column;

    if( n_row == 0 ) {
      df.attr("row.names") = Rcpp::IntegerVector(0);  // #nocov
    } else {
      Rcpp::IntegerVector rn = Rcpp::seq( 1, n_row );
      df.attr("row.names") = rn;
    }
  }

  inline Rcpp::List create_sf(
      Rcpp::DataFrame& df,
      Rcpp::List& sfc,
      Rcpp::StringVector& property_cols,
      Rcpp::IntegerVector& property_idx,
      Rcpp::IntegerVector& row_idx
  ) {

    R_xlen_t n_col = property_idx.length();
    Rcpp::List sf( n_col + 1 );  // +1 == sfc
    Rcpp::StringVector res_names( n_col + 1 );
    R_xlen_t i;

    // fill columns of properties
    for( i = 0; i < n_col; ++i ) {
      int idx = property_idx[i];
      SEXP v = df[ idx ];
      sf[ i ] = subset_properties( v, row_idx );
      res_names[ i ] = property_cols[ i ];
    }

    // make data.frame
    Rcpp::String sfc_name = "geometry";

    sf[ n_col ] = sfc;
    res_names[ n_col ] = sfc_name;
    sf.names() = res_names;

    R_xlen_t n_row = row_idx.length();

    sfheaders::sf::attach_dataframe_attributes( sf, n_row );

    return sf;
  }

  // where the input is a data.frame, and output includes an id column
  inline Rcpp::List create_sf(
      Rcpp::DataFrame& df,
      Rcpp::List& sfc,
      Rcpp::String& id_column,
      Rcpp::StringVector& property_cols,
      Rcpp::IntegerVector& property_idx,
      Rcpp::IntegerVector& row_idx
  ) {

    R_xlen_t n_col = property_idx.length();
    Rcpp::List sf( n_col + 2 );  // +1 == sfc, +1 == sf_id
    Rcpp::StringVector res_names( n_col + 2 );
    R_xlen_t i;

    // fill columns of properties
    for( i = 0; i < n_col; ++i ) {
      int idx = property_idx[i];
      SEXP v = df[ idx ];
      sf[ i + 1 ] = subset_properties( v, row_idx );
      res_names[ i + 1 ] = property_cols[ i ];
    }

    // id column
    SEXP id = df[ id_column ];
    sf[ 0 ] = subset_properties( id, row_idx );
    res_names[ 0 ] = id_column;

    // make data.frame
    sf[ n_col + 1 ] = sfc;
    Rcpp::String sfc_name = "geometry";
    res_names[ n_col + 1 ] = sfc_name;
    sf.names() = res_names;

    R_xlen_t n_row = row_idx.length();

    sfheaders::sf::attach_dataframe_attributes( sf, n_row );

    return sf;
  }


  // where there's only one-row sf
  inline SEXP create_sf(
      Rcpp::DataFrame& df,
      Rcpp::List& sfc,
      SEXP& property_columns
  ) {

    Rcpp::StringVector df_names = df.names();
    Rcpp::StringVector str_property_columns;

    switch( TYPEOF( property_columns ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( property_columns );
      str_property_columns = df_names[ iv ];
      break;
    }
    case STRSXP: {
      str_property_columns = Rcpp::as< Rcpp::StringVector >( property_columns );
      break;
    }
    default: {
      Rcpp::stop("sfheaders - unknown column types"); // #nocov
    }
    }

    // make_data.frame
    Rcpp::IntegerVector row_idx(1);
    row_idx[0] = 0;

    Rcpp::IntegerVector property_idx = sfheaders::utils::where_is( str_property_columns, df_names );
    return sfheaders::sf::create_sf( df, sfc, str_property_columns, property_idx, row_idx );
  }

  inline SEXP create_sf(
      SEXP& x,
      Rcpp::List& sfc,
      SEXP& property_columns
  ) {
    Rcpp::DataFrame df;
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      df = Rcpp::as< Rcpp::DataFrame >( im );
      break;
    }
    case REALSXP: {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      df = Rcpp::as< Rcpp::DataFrame >( nm );
      break;
    }
    case VECSXP: {
      df = Rcpp::as< Rcpp::DataFrame >( x );
      break;
    }
    default: {
      Rcpp::stop("sfheaders - unknown type"); // #nocov
    }
    }
    return create_sf( df, sfc, property_columns );
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
