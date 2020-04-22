#ifndef R_SFHEADERS_INTERLEAVE_H
#define R_SFHEADERS_INTERLEAVE_H

#include <Rcpp.h>
#include "sfheaders/df/sfc.hpp"
#include "sfheaders/utils/lists/list.hpp"

namespace sfheaders {
namespace interleave {

  template < int RTYPE >
  inline SEXP interleave( Rcpp::Matrix< RTYPE >& mat ) {
    R_xlen_t n_col = mat.ncol();
    R_xlen_t n_row = mat.nrow();
    Rcpp::Vector< RTYPE > res( n_col * n_row );
    R_xlen_t i, j;
    R_xlen_t position_counter = 0;
    for( i = 0; i < n_row; ++i ) {
      for( j = 0; j < n_col; ++j ) {
        res[ position_counter ] = mat( i, j );
        position_counter = position_counter + 1;
      }
    }
    return res;
  }

  // templated version with a vector you want to fill with the result of interleaving
  // requires knowing the start index.
  // template < int RTYPE >
  // inline SEXP interleave(
  //     Rcpp::Matrix< RTYPE >& mat,
  //     Rcpp::Matrix< RTYPE >& to_fill,
  //     R_xlen_t& start_index
  //   ) {
  //   Rcpp::Vector< RTYPE > interleaved = interleave( mat );
  //   sfheaders::utils::fill_vector( to_fill, interleaved, start_index );
  //   return to_fill;
  // }

  inline SEXP interleave( SEXP& sfg ) {

    switch( TYPEOF ( sfg ) ) {
    case INTSXP: {
    if( Rf_isMatrix( sfg ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( sfg );
      return interleave( im );
    } else {
      return sfg; // it's already a vector
    }
    }
    case REALSXP: {
    if( Rf_isMatrix( sfg ) ) {
      Rcpp::NumericMatrix im = Rcpp::as< Rcpp::NumericMatrix >( sfg );
      return interleave( im );
    } else {
      return sfg; // it's already a vector
    }
    }
    case VECSXP: {
    if( Rf_isNewList( sfg ) ) {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      // iterate through until we get a matrix
      // which can be interleaved
      R_xlen_t n = lst.size();
      R_xlen_t i;
      Rcpp::List res( n ); // store interleaved vectors in the same nested-list structure

      //R_xlen_t coordinate_counter = 0;

      // Rcpp::NumericMatrix coords = sfheaders::df::sfc_n_coordinates( lst );
      // Rcpp::Rcout << "sfg_coordinates: " << coords << std::endl;

      Rcpp::Rcout << "n: " << n << std::endl;
      for( i = 0; i < n; ++i ) {
        Rcpp::Rcout << "i: " << i << std::endl;
        SEXP sfg = lst[ i ];
        // Rcpp::NumericMatrix coords = sfheaders::df::sfg_n_coordinates( sfg );
        // Rcpp::Rcout << "sfg_coordinates: " << coords << std::endl;
        res[ i ] = interleave( sfg );
      }

      return sfheaders::utils::unlist_list( res );
      //return res;
    }
    }
    default: {
      Rcpp::stop("sfheaders - can not interleave this type of object");
    }
    }
    return Rcpp::List::create();
  }

} // interleave
} // sfheaders


#endif
