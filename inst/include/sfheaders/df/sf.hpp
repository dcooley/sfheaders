#ifndef R_SFHEADERS_DF_SF_H
#define R_SFHEADERS_DF_SF_H

#include "sfheaders/df/sfc.hpp"

#include <Rcpp.h>

namespace sfheaders {
namespace df {

  template < int RTYPE >
  inline SEXP expand_vector( Rcpp::Vector< RTYPE > v, Rcpp::NumericVector& expand_index ) {
    return v[ expand_index ];
  }

  inline Rcpp::List sf_to_df( Rcpp::DataFrame& sf ) {

    std::string geom_column = sf.attr("sf_column");

    Rcpp::List sfc = sf[ geom_column ];

    // TODO - don't re-call the sfc-n_coordinates function.
    Rcpp::List sfc_df = sfheaders::df::sfc_to_df( sfc );

    R_xlen_t sfc_cols = sfc_df.length();

    //sf[ geom_column ] = R_NilValue;

    Rcpp::NumericMatrix sfc_coordinates = sfc_n_coordinates( sfc );

    R_xlen_t n_geometries = sfc_coordinates.nrow();
    R_xlen_t total_coordinates = sfc_coordinates( n_geometries - 1 , 1 );
    total_coordinates = total_coordinates + 1;

    //Rcpp::Rcout << "sfc_coordinates: " << std::endl;
    //Rcpp::Rcout << sfc_coordinates << std::endl;
    Rcpp::NumericVector expanded_index( total_coordinates );

    R_xlen_t i;
    R_xlen_t j;
    R_xlen_t counter = 0;

    for( i = 0; i < n_geometries; ++i ) {
      R_xlen_t expand_by = sfc_coordinates( i, 1 ) - sfc_coordinates( i, 0 );

      for( j = 0; j < expand_by; ++j ) {
        expanded_index[ counter + j ] = i;
      }
      counter = counter + expand_by;
    }

    // Rcpp::Rcout << "expandex_index: " << expanded_index << std::endl;

    R_xlen_t n_col = sf.ncol();
    Rcpp::List res( n_col + sfc_cols );

    Rcpp::CharacterVector res_names( n_col + sfc_cols );

    Rcpp::CharacterVector sf_names = sf.names();

    // TODO: Dates / Posixct && Factors
    for( i = 0; i < n_col; ++i ) {

      // Rcpp::Rcout << "col: " << sf_names[ i ] << std::endl;
      if( sf_names[ i ] != geom_column ) {

        res_names[ i ] = sf_names[ i ];

        SEXP v = sf[ i ];
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
          //Rcpp::Rcout << "nv: " << nv << std::endl;
          Rcpp::NumericVector res_nv = nv[ expanded_index ];
          //Rcpp::Rcout << "res_nv: " << res_nv << std::endl;
          res[ i ] = res_nv;
          break;
        }
        case STRSXP: {
          Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( v );
          res[ i ] = sv[ expanded_index ];
          break;
        }
        default: {
          Rcpp::stop("sfheaders - unknown column type for data.frames");
        }
        }
      }

    }

    Rcpp::CharacterVector sfc_df_names = sfc_df.names();
    for( i = 0; i < sfc_cols; ++i ) {
      res_names[ i + n_col ] = sfc_df_names[ i ];
      res[ i + n_col ] = sfc_df[ i ];
    }


    res.attr("class") = Rcpp::CharacterVector("data.frame");

    if( total_coordinates > 0 ) {
      Rcpp::IntegerVector rownames = Rcpp::seq( 1, total_coordinates );
      res.attr("row.names") = rownames;
    } else {
      res.attr("row.names") = Rcpp::IntegerVector(0);
    }

    res.attr("names") = res_names;
    return res;

  }


} // df
} // sfheaders

#endif
