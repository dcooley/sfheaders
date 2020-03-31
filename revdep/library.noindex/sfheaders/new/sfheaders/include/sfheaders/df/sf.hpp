#ifndef R_SFHEADERS_DF_SF_H
#define R_SFHEADERS_DF_SF_H

#include "sfheaders/df/sfc.hpp"
#include "sfheaders/utils/vectors/vectors.hpp"

#include <Rcpp.h>

namespace sfheaders {
namespace df {

  inline Rcpp::String unique_name( Rcpp::String this_name, Rcpp::StringVector& existing_names ) {
    int is_in = sfheaders::utils::where_is( this_name, existing_names );

    if( is_in != -1 ) {
      // the name already exists, so we need to uniqueify it
      int counter = 1;
      std::string new_name;
      do {                       // #nocov
        std::ostringstream os;
        os << this_name.get_cstring() << ".." << counter;
        new_name = os.str();
        is_in = sfheaders::utils::where_is( new_name, existing_names );
        counter += 1;
      } while ( is_in != -1 );
      this_name = new_name;
    }

    return this_name;
  }

  /*
   * Expand Vector
   *
   *
   */
  inline void expand_vector(
      Rcpp::List& res,
      SEXP& v,
      Rcpp::NumericVector& expanded_index,
      R_xlen_t& i
  ) {

    switch( TYPEOF( v ) ) {
    case LGLSXP: {
      Rcpp::LogicalVector lv = Rcpp::as< Rcpp::LogicalVector >( v );
      res[ i ] = lv[ expanded_index ];
      break;
    }
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( v );
      res[ i ] = iv[ expanded_index ];
      break;
    }
    case REALSXP: {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( v );
      Rcpp::NumericVector res_nv = nv[ expanded_index ];
      res[ i ] = res_nv;
      break;
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( v );
      res[ i ] = sv[ expanded_index ];
      break;
    }
    case CPLXSXP: {
      Rcpp::ComplexVector cv = Rcpp::as< Rcpp::ComplexVector >( v );
      res[ i ] = cv[ expanded_index ];
      break;
    }
    case RAWSXP: {
      Rcpp::RawVector rv = Rcpp::as< Rcpp::RawVector >( v );
      res[ i ] = rv[ expanded_index ];
      break;
    }
    case VECSXP: {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( v );
      res[ i ] = lst[ expanded_index ];
      break;
    }
    default: {
      Rcpp::stop("sfheaders - unsupported column type using fill = TRUE");
    }
    }
  }

  inline Rcpp::List sf_to_df(
      Rcpp::DataFrame& sf,
      Rcpp::List& sfc,
      std::string& geom_column,
      Rcpp::NumericMatrix& sfc_coordinates,
      bool fill = false
  ) {

    R_xlen_t n_geometries = sfc_coordinates.nrow();
    R_xlen_t total_coordinates = sfc_coordinates( n_geometries - 1 , 1 );
    total_coordinates = total_coordinates + 1;

    Rcpp::List sfc_df = sfheaders::df::get_sfc_coordinates( sfc, total_coordinates );

    if( !fill ) {
      return sfc_df;  // #nocov
    }

    R_xlen_t sfc_cols = sfc_df.length();

    Rcpp::NumericVector expanded_index( total_coordinates );

    R_xlen_t i;
    R_xlen_t j;
    R_xlen_t counter = 0;

    for( i = 0; i < n_geometries; ++i ) {
      R_xlen_t expand_by = sfc_coordinates( i, 1 ) - sfc_coordinates( i, 0 ) + 1;

      for( j = 0; j < expand_by; ++j ) {
        expanded_index[ counter + j ] = i;
      }
      counter = counter + expand_by;
    }

    R_xlen_t n_col = sf.ncol();
    Rcpp::List res( n_col - 1 + sfc_cols ); // -1 to remove the geometry

    Rcpp::CharacterVector res_names( n_col - 1 + sfc_cols );

    // the 'non-geometry' names of the data.frame
    Rcpp::CharacterVector sf_names = sf.names();
    // iff these names are in res_names

    R_xlen_t name_position = 0;
    for( i = 0; i < n_col; ++i ) {

      if( sf_names[ i ] != geom_column ) {

        res_names[ name_position ] = sf_names[ i ];
        SEXP v = sf[ i ];
        expand_vector( res, v, expanded_index, name_position );
        name_position += 1;
      }
    }

    Rcpp::CharacterVector sfc_df_names = sfc_df.names();
    //Rcpp::Rcout << "sfc_df_names " << sfc_df_names << std::endl;

    // in sfc.hpp I define geometry columns with names 'x','y','z','m'
    // so I know these will be geometry columns
    Rcpp::StringVector geometry_columns = {"x","y","z","m"};
    Rcpp::LogicalVector keep_columns( sfc_df_names.length() );
    // set true / false if the sfc_df_names are in sfc.hpp names
    int is_in;

    for( i = 0; i < sfc_df_names.length(); ++i ) {
      Rcpp::String geom = sfc_df_names[ i ];
      is_in = sfheaders::utils::where_is( geom, geometry_columns );
      keep_columns[ i ] = is_in == -1 ? false : true;
    }

    //Rcpp::Rcout << "keep: " << keep_columns << std::endl;

    for( i = 0; i < sfc_cols; ++i ) {
      Rcpp::String this_name = unique_name( sfc_df_names[ i ], res_names );
      // unique-ify 'this_name;
      //sfc_df_names[ i ] = unique_name( this_name, res_names );
      sfc_df_names[ i ] = this_name; // use these names as sfc_columns attr

      res_names[ i + n_col - 1 ] = this_name;
      res[ i + n_col - 1 ] = sfc_df[ i ];
    }

    res.attr("sfc_columns") = sfc_df_names[ keep_columns ];
    return sfheaders::utils::make_dataframe( res, total_coordinates, res_names );

    // res.attr("class") = Rcpp::CharacterVector("data.frame");
    //
    //
    // if( total_coordinates > 0 ) {
    //   Rcpp::IntegerVector rownames = Rcpp::seq( 1, total_coordinates );
    //   res.attr("row.names") = rownames;
    // } else {
    //   res.attr("row.names") = Rcpp::IntegerVector(0);  // #nocov
    // }
    //
    // res.attr("names") = res_names;
    // return res;
  }

  inline Rcpp::List sf_to_df(
    Rcpp::DataFrame& sf,
    bool fill = false
  ) {
    if( !sf.hasAttribute("sf_column") ) {
      Rcpp::stop("sfheaders - sf_column not found");
    }

    std::string geom_column = sf.attr("sf_column");
    Rcpp::List sfc = sf[ geom_column ];
    Rcpp::NumericMatrix sfc_coordinates = sfc_n_coordinates( sfc );
    return sf_to_df( sf, sfc, geom_column, sfc_coordinates, fill );
  }


} // df
} // sfheaders

#endif
