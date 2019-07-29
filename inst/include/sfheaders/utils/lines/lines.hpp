#ifndef R_SFHEADERS_UTILS_LINES_H
#define R_SFHEADERS_UTILS_LINES_H

#include <Rcpp.h>

namespace sfheaders {
namespace utils {

  /* line_ids
   *
   * returns a 2-colummn matrix giving the start & end locations in a vector of'ids'
   * where the ids start & end
   *
   */
  inline Rcpp::IntegerMatrix line_ids(
      Rcpp::IntegerVector& line_ids,
      Rcpp::IntegerVector& unique_ids
  ) {

    size_t n = line_ids.length();
    size_t unique_n = unique_ids.length();

    Rcpp::IntegerMatrix im( unique_n, 2);

    // if n = 1, there's only 1 unique ID
    if( n == 1 ) {
      im( 0, 0 ) = 0;
      im( 0, 1 ) = n - 1;
      return im;
    }

    size_t i;

    Rcpp::IntegerVector start_positions( unique_n );
    Rcpp::IntegerVector end_positions( unique_n );

    int idx = 0;
    int this_id;
    for( i = 0; i < n; i++ ) {
      //go through line_ids and find where ids change
      if( i == 0 ) {
        this_id = line_ids[ i ];
        start_positions[ idx ] = i;
      }

      if( this_id != line_ids[ i ] ) {
        //the id has changed
        end_positions[ idx ] = i - 1;
        idx++;
        start_positions[ idx ] = i;
        this_id = line_ids[ i ];
      }

      if( i == ( n - 1 ) ) {
        end_positions[ idx ] = i;
      }
    }

    im( Rcpp::_, 0 ) = start_positions;
    im( Rcpp::_, 1 ) = end_positions;

    return im;
  }


  inline Rcpp::IntegerMatrix line_ids(
      Rcpp::NumericVector& line_ids,
      Rcpp::NumericVector& unique_ids
  ) {

    size_t n = line_ids.length();
    size_t unique_n = unique_ids.length();

    Rcpp::IntegerMatrix im( unique_n, 2);

    // if n = 1, there's only 1 unique ID
    if( n == 1 ) {
      im( 0, 0 ) = 0;
      im( 0, 1 ) = n - 1;
      return im;
    }

    size_t i;

    Rcpp::IntegerVector start_positions( unique_n );
    Rcpp::IntegerVector end_positions( unique_n );

    int idx = 0;
    int this_id;
    for( i = 0; i < n; i++ ) {
      //go through line_ids and find where ids change
      if( i == 0 ) {
        this_id = line_ids[ i ];
        start_positions[ idx ] = i;
      }

      if( this_id != line_ids[ i ] ) {
        //the id has changed
        end_positions[ idx ] = i - 1;
        idx++;
        start_positions[ idx ] = i;
        this_id = line_ids[ i ];
      }

      if( i == ( n - 1 ) ) {
        end_positions[ idx ] = i;
      }
    }

    im( Rcpp::_, 0 ) = start_positions;
    im( Rcpp::_, 1 ) = end_positions;

    return im;
  }


} // utils
} // sfheaders

#endif
