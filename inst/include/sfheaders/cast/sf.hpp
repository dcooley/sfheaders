#ifndef R_SFHEADERS_CAST_SF_H
#define R_SFHEADERS_CAST_SF_H

#include "sfheaders/sf/sf_utils.hpp"
#include "sfheaders/cast/sfc.hpp"

#include "geometries/utils/vectors/vectors.hpp"

#include <Rcpp.h>

namespace sfheaders {
namespace cast {

  inline Rcpp::List cast_sf(
      Rcpp::DataFrame& sf,
      std::string& cast_to,
      bool close = true
  ) {
    if( !sf.hasAttribute("sf_column") ) {
      Rcpp::stop("sfheaders - sf_column not found");
    }


    Rcpp::StringVector df_names = sf.names();
    R_xlen_t n_names = df_names.length();
    R_xlen_t i, j;
    R_xlen_t n_row = sf.nrow();
    R_xlen_t n_col = sf.ncol();

    std::string geom_column = sf.attr("sf_column");
    Rcpp::List sfc = sf[ geom_column ];
    Rcpp::NumericVector n_results = count_new_sfc_objects( sfc, cast_to );

    R_xlen_t total_coordinates = Rcpp::sum( n_results );

    Rcpp::IntegerVector expanded_index( total_coordinates );

    R_xlen_t counter = 0;
    for( i = 0; i < n_row; ++i ) {
      R_xlen_t expand_by = n_results[ i ];

      for( j = 0; j < expand_by; ++j ) {
        expanded_index[ counter + j ] = i;
      }
      counter = counter + expand_by;
    }

    // other than the sfc column, expand all the other columsn by 'n_reuslts'
    Rcpp::List casted_sfc = cast_sfc( sfc, n_results, cast_to, close );

    Rcpp::List sf_res( n_names );
    // loop over each of the df_names which aren't the geometry
    // then add on the created_sfc;
    Rcpp::StringVector res_names( n_col );
    R_xlen_t column_counter = 0;

    for( i = 0; i < n_names; ++i ) {
      // iff this_name != geom_column, expand the vector and doene.
      Rcpp::String this_name = df_names[ i ];
      std::string str_name = this_name;

      Rcpp::Rcout << "this_name: " << str_name << std::endl;

      if( str_name != geom_column ) {
        SEXP v = sf[ i ];

        Rcpp::Rcout << "Type of property column: " << TYPEOF( v ) << std::endl;
        Rcpp::Rcout << "expanded_index: " << expanded_index << std::endl;

        // TODO:
        // IFF v is a LIST (VECSXP) column, then it should contain the same number of elements
        // as teh sfg
        // - e.g., a POLYGON((), (), ()) has 3 rings. The lsit column should have 3 elements
        // - if we are down-casting, then each ring is being separated. so the list needs to be separated too.
        if( TYPEOF( v ) == VECSXP ) {
          Rcpp::List lst_v = Rcpp::as< Rcpp::List >( v );
          Rcpp::Rcout << "lst_v length: " << lst_v.length() << std::endl;
          if( expanded_index.length() != lst_v.length() ) {
            // this isn't correct....
            Rcpp::stop("sfheaders - invalid list column");

          }
          for( j = 0; j < lst_v.length(); ++j ) {
            SEXP lv = lst_v[ j ];
            Rcpp::IntegerVector ie = expanded_index[ j ];
            geometries::utils::expand_vector( sf_res, lv, ie, column_counter );
          }
        } else {
          geometries::utils::expand_vector( sf_res, v, expanded_index, column_counter );
        }

        res_names[ column_counter ] = str_name;
        ++column_counter;
      }
    }

    // append 'geom_column' to res_columns;
    res_names[ column_counter ] = geom_column;

    sf_res[ column_counter ] = casted_sfc;
    sf_res.names() = res_names;
    sfheaders::sf::attach_dataframe_attributes( sf_res, total_coordinates, geom_column );
    return sf_res;

  }

} // cast
} // sfheaders

#endif
