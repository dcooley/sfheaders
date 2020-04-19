#ifndef R_SFHEADERS_INTERLEAVE_H
#define R_SFHEADERS_INTERLEAVE_H

#include "sfheaders/df/sfc.hpp"
#include <Rcpp.h>

namespace sfheaders {
namespace interleave {

  template < int RTYPE >
  inline SEXP interleave( Rcpp::Matrix< RTYPE >& mat ) {
    R_xlen_t n_col = mat.ncol();
    R_xlen_t n_row = mat.nrow();
    Rcpp::Vector< RTYPE > res( n_col * n_row );
    R_xlen_t i, j;
    for( i = 0; i < n_row; ++i ) {
      for( j = 0; j < n_col; ++j ) {
        res[ j ] = mat( i, j );
      }
    }
    return res;
  }

  inline SEXP interleave( Rcpp::List& lst) {
    R_xlen_t i;
    R_xlen_t n = lst.length();


    Rcpp::NumericMatrix sfc_coordinates = sfheaders::df::sfc_n_coordinates( lst );
    R_xlen_t n_geometries = sfc_coordinates.nrow();
    R_xlen_t total_coordinates = sfc_coordinates( n_geometries - 1 , 1 );
    total_coordinates = total_coordinates + 1;

    //Rcpp::Rcout << "sfc_coordinates: " << sfc_coordinates << std::endl;

    for( i = 0; i < n; ++i ) {
      //SEXP sfg = sfc[ i ];

    }
    return Rcpp::List::create();
  }

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
      return interleave( lst );
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
