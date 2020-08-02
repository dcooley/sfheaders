#ifndef R_SFHEADERS_SF_UTILS_H
#define R_SFHEADERS_SF_UTILS_H

#include "geometries/utils/vectors/vectors.hpp"
#include "geometries/utils/lists/list.hpp"

namespace sfheaders {
namespace sf {

  inline void id_length_check(
    SEXP& ids,
    Rcpp::List& sfc
  ) {
    if( Rf_length( ids ) != sfc.length() ) {
      Rcpp::stop("sfheaders - error indexing lines, perhaps caused by un-ordered data? ");
    }
  }

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

  inline Rcpp::StringVector make_names( R_xlen_t& n_col ) {
    R_xlen_t i;
    Rcpp::StringVector res( n_col );
    for( i = 0; i < n_col; ++i ) {
      std::ostringstream os;
      os << "V" << ( i + 1 );
      res[ i ] = os.str();
    }
    return res;
  }

  inline Rcpp::List create_sf(
      Rcpp::List& data,
      Rcpp::List& sfc,
      Rcpp::IntegerVector& id_column,
      Rcpp::IntegerVector& property_cols,
      Rcpp::IntegerVector& list_column_idx,
      Rcpp::IntegerVector& geometry_idx
  ) {

    bool has_id = !Rf_isNull( id_column ) && Rf_length( id_column ) > 0;
    bool has_properties = !Rf_isNull( property_cols ) && Rf_length( property_cols ) > 0;
    bool has_list_cols = !Rf_isNull( list_column_idx );

    R_xlen_t data_n_cols = Rf_length( data );

    R_xlen_t n_properties = property_cols.length();
    //_xlen_t n_col = has_id ? property_cols.length() : property_cols.length() + 1;
    Rcpp::StringVector data_names( data_n_cols );

    R_xlen_t total_cols = n_properties + 1 + has_id; // +1 == sfc
    Rcpp::List sf( total_cols );
    Rcpp::StringVector res_names( total_cols );
    R_xlen_t i;

    if( !Rf_isNull( data.names() ) ) {
      data_names = data.names();
    } else {

      // the property_cols object points to index of data_names
      // so we need the maxium property_cols value

      data_names = make_names( data_n_cols );
      // TODO/ this needs to be max( property_cols );
      // or at leaste max( n_properties ) of the input data object
    }

    if( has_id ) {
      int id = id_column[0];
      SEXP ids = VECTOR_ELT( data, id );
      SEXP unique_ids = geometries::utils::get_sexp_unique( ids );
      id_length_check( unique_ids, sfc );

      sf[ 0 ] = unique_ids;
      res_names[ 0 ] = data_names[ id ];
    }


    if( has_properties ) {

      for( i = 0; i < n_properties; ++i ) {

        int idx = property_cols[ i ];
        bool is_in = has_list_cols && ( std::find( list_column_idx.begin(), list_column_idx.end(), idx ) != list_column_idx.end()  );
        SEXP v = data[ idx ];

        if( is_in ) {
          sf[ i + has_id ] = geometries::utils::fill_list( v, geometry_idx );
        } else {
          sf[ i + has_id ] = subset_properties( v, geometry_idx );
        }
        res_names[ i + has_id ] = data_names[ idx ];
      }
    }

    // make data.frame
    Rcpp::String sfc_name = "geometry";

    sf[ total_cols - 1 ] = sfc;
    res_names[ total_cols - 1 ] = sfc_name;
    sf.names() = res_names;

    R_xlen_t n_row = geometry_idx.length();

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
