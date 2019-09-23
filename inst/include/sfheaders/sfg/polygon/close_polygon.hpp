#ifndef R_SFHEADERS_POLYGON_CLOSE_POLYGON_H
#define R_SFHEADERS_POLYGON_CLOSE_POLYGON_H

#include <Rcpp.h>

namespace sfheaders {
namespace polygon {

  // TODO
  // close polygons (matrices, lists, data.frames)
  // check if closed for 2-columns, 3-columns & 4-columns
  // closed when first row == last row
  inline IntegerMatrix close_polygon(
    Rcpp::IntegerMatrix& im
  ) {
    R_xlen_t n_row = im.nrow();
    if( n_row < 2 ) {
      return false;
    }

    R_xlen_t n_col = im.ncol();
    R_xlen_t i;

    bool is_closed = true;

    Rcpp::IntegerVector first_row = im( 0, Rcpp::_ );
    Rcpp::IntegerVector last_row = im( n_row - 1, Rcpp::_ );

    for( i = 0; i < n_col; i++ ) {
      if( first_row[i] != last_row[i] ) {
        is_closed = false;
        break;
      }
    }

    if( !is_closed ) {
      Rcpp::IntegerMatrix im2( n_row + 1, n_col );
      for( i = 0; i < n_col; i++ ) {
        Rcpp::IntegerVector iv( n_row + 1);
        Rcpp::Range rng( 0, n_row - 1 );

        iv[ rng ] = im( Rcpp::_, i );
        iv[ n_row ] = first_row[i];
        im2( Rcpp::_ , i ) = iv;
      }
      return im2;
    }

    // it is closed
    return im;
  }

  inline NumericMatrix close_polygon(
      Rcpp::NumericMatrix& nm
  ) {
    R_xlen_t n_row = nm.nrow();
    if( n_row < 2 ) {
      return false;
    }

    R_xlen_t n_col = nm.ncol();
    R_xlen_t i;

    bool is_closed = true;

    Rcpp::NumericVector first_row = nm( 0, Rcpp::_ );
    Rcpp::NumericVector last_row = nm( n_row - 1, Rcpp::_ );

    for( i = 0; i < n_col; i++ ) {
      if( first_row[i] != last_row[i] ) {
        is_closed = false;
        break;
      }
    }

    if( !is_closed ) {
      Rcpp::NumericMatrix nm2( n_row + 1, n_col );
      for( i = 0; i < n_col; i++ ) {
        Rcpp::NumericVector nv( n_row + 1);
        Rcpp::Range rng( 0, n_row - 1 );

        nv[ rng ] = nm( Rcpp::_, i );
        nv[ n_row ] = first_row[i];
        nm2( Rcpp::_ , i ) = nv;
      }
      return nm2;
    }

    // it is closed
    return nm;
  }

} // polygon
} // sfheaders

#endif
