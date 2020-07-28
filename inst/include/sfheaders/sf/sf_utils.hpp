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
      //Rcpp::IntegerMatrix& line_positions
  ) {

    // Rcpp::Rcout << "create_sf" << std::endl;
    // Rcpp::Rcout << "id_column: " << id_column << std::endl;
    // Rcpp::Rcout << "property_col: " << property_cols << std::endl;
    // Rcpp::Rcout << "list_col_idx: " << list_column_idx << std::endl;
    // Rcpp::Rcout << "geometry_idx: " << geometry_idx << std::endl;

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
      //R_xlen_t n_names = Rcpp::max( property_cols ) + 1;
      //R_xlen_t m = n_names > total_cols ? n_names : total_cols;
      //Rcpp::Rcout << "m: " << m << std::endl;

      data_names = make_names( data_n_cols );
      // TODO/ this needs to be max( property_cols );
      // or at leaste max( n_properties ) of the input data object
    }

    // Rcpp::Rcout << "names: " << data_names << std::endl;
    // Rcpp::Rcout << "property cols " << property_cols << std::endl;


    //SEXP unique_ids;
    if( has_id ) {
      // Rcpp::Rcout << "id_column: " << id_column << std::endl;
      //return data;
      //Rcpp::stop("stopping");
      //return data;
      //Rcpp::stop("stopping");
      int id = id_column[0];
      SEXP ids = VECTOR_ELT( data, id );
      //return ids;
      // Rcpp::Rcout << "type of id : " << TYPEOF( ids ) << std::endl;
      SEXP unique_ids = geometries::utils::get_sexp_unique( ids );
      id_length_check( unique_ids, sfc );

      sf[ 0 ] = unique_ids;
      res_names[ 0 ] = data_names[ id ];
    }


    if( has_properties ) {

      // Rcpp::Rcout << "n_properties: " << n_properties << std::endl;
      // Rcpp::Rcout << "data_names: " << data_names << std::endl;

      //Rcpp::stop("Stopping");

      for( i = 0; i < n_properties; ++i ) {

        int idx = property_cols[ i ];
        // Rcpp::Rcout << "idx: " << idx << std::endl;
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
    //Rcpp::stop("Stopping");

    // make data.frame
    Rcpp::String sfc_name = "geometry";

    sf[ total_cols - 1 ] = sfc;
    res_names[ total_cols - 1 ] = sfc_name;
    sf.names() = res_names;

    R_xlen_t n_row = geometry_idx.length();

    sfheaders::sf::attach_dataframe_attributes( sf, n_row );
    //Rcpp::stop("Stopping");

    return sf;
  }

  // // where the input is a data.frame, and output includes an id column
  // inline Rcpp::List create_sf(
  //     Rcpp::DataFrame& df,
  //     Rcpp::List& sfc,
  //     Rcpp::String& id_column,
  //     Rcpp::StringVector& property_cols,
  //     Rcpp::IntegerVector& property_idx,
  //     Rcpp::IntegerVector& list_column_idx,
  //     Rcpp::IntegerVector& row_idx,
  //     Rcpp::IntegerMatrix& line_positions
  // ) {
  //
  //   // Rcpp::Rcout << "create_sf(df) + id " << std::endl;
  //   R_xlen_t n_col = property_idx.length();
  //   Rcpp::List sf( n_col + 2 );  // +1 == sfc, +1 == sf_id
  //   Rcpp::StringVector res_names( n_col + 2 );
  //   R_xlen_t i;
  //
  //   // fill columns of properties
  //   for( i = 0; i < n_col; ++i ) {
  //     int idx = property_idx[ i ];
  //
  //     // Rcpp::Rcout << "idx: " << idx << std::endl;
  //     // Rcpp::Rcout << "lst_columns: " << list_column_idx << std::endl;
  //
  //     bool is_in = ( std::find( list_column_idx.begin(), list_column_idx.end(), idx ) != list_column_idx.end()  );
  //     SEXP v = df[ idx ];
  //     if( is_in ) {
  //       sf[ i + 1 ] = geometries::utils::fill_list( v, line_positions );
  //     } else {
  //       sf[ i + 1 ] = subset_properties( v, row_idx );
  //     }
  //
  //     //SEXP v = df[ idx ];
  //     //sf[ i + 1 ] = subset_properties( v, row_idx );
  //     res_names[ i + 1 ] = property_cols[ i ];
  //   }
  //
  //   // id column
  //   SEXP id = df[ id_column ];
  //   sf[ 0 ] = subset_properties( id, row_idx );
  //   res_names[ 0 ] = id_column;
  //
  //   // make data.frame
  //   sf[ n_col + 1 ] = sfc;
  //   Rcpp::String sfc_name = "geometry";
  //   res_names[ n_col + 1 ] = sfc_name;
  //   sf.names() = res_names;
  //
  //   R_xlen_t n_row = row_idx.length();
  //
  //   sfheaders::sf::attach_dataframe_attributes( sf, n_row );
  //
  //   return sf;
  // }


  // // where there's only one-row sf
  // inline SEXP create_sf(
  //     Rcpp::DataFrame& df,
  //     Rcpp::List& sfc,
  //     SEXP& property_columns,
  //     Rcpp::IntegerVector& list_column_idx,
  //     Rcpp::IntegerMatrix& line_positions
  // ) {
  //
  //   //Rcpp::Rcout << "create_sf(df)" << std::endl;
  //   Rcpp::StringVector df_names = df.names();
  //   Rcpp::StringVector str_property_columns;
  //
  //   switch( TYPEOF( property_columns ) ) {
  //   case REALSXP: {}
  //   case INTSXP: {
  //     Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( property_columns );
  //     str_property_columns = df_names[ iv ];
  //     break;
  //   }
  //   case STRSXP: {
  //     str_property_columns = Rcpp::as< Rcpp::StringVector >( property_columns );
  //     break;
  //   }
  //   default: {
  //     Rcpp::stop("sfheaders - unknown column types"); // #nocov
  //   }
  //   }
  //
  //   // make_data.frame
  //   Rcpp::IntegerVector row_idx(1);
  //   row_idx[0] = 0;
  //
  //   Rcpp::IntegerVector property_idx = geometries::utils::where_is( str_property_columns, df_names );
  //   return sfheaders::sf::create_sf( df, sfc, str_property_columns, property_idx, list_column_idx, row_idx, line_positions );
  // }
  //
  // inline SEXP create_sf(
  //     SEXP& x,
  //     Rcpp::List& sfc,
  //     SEXP& property_columns,
  //     Rcpp::IntegerVector& list_column_idx,
  //     Rcpp::IntegerMatrix& line_positions
  // ) {
  //
  //   //Rcpp::Rcout << "create_sf(x)" << std::endl;
  //   Rcpp::DataFrame df;
  //   switch( TYPEOF( x ) ) {
  //   case INTSXP: {
  //     Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
  //     df = Rcpp::as< Rcpp::DataFrame >( im );
  //     break;
  //   }
  //   case REALSXP: {
  //     Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
  //     df = Rcpp::as< Rcpp::DataFrame >( nm );
  //     break;
  //   }
  //   case VECSXP: {
  //     df = Rcpp::as< Rcpp::DataFrame >( x );
  //     break;
  //   }
  //   default: {
  //     Rcpp::stop("sfheaders - unknown type"); // #nocov
  //   }
  //   }
  //   return create_sf( df, sfc, property_columns, list_column_idx, line_positions );
  // }


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
