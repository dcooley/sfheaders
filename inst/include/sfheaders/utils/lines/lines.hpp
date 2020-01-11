#ifndef R_SFHEADERS_UTILS_LINES_H
#define R_SFHEADERS_UTILS_LINES_H

#include <Rcpp.h>
#include "sfheaders/utils/unique/unique_sort.hpp"

namespace sfheaders {
namespace utils {

  /* line_ids
   *
   * returns a 2-colummn matrix giving the start & end locations in a vector of'ids'
   * where the ids start & end
   *
   */
  inline Rcpp::IntegerMatrix id_positions(
      Rcpp::IntegerVector& line_ids,
      Rcpp::IntegerVector& unique_ids
  ) {

    R_xlen_t n = line_ids.length();
    R_xlen_t unique_n = unique_ids.length();

    Rcpp::IntegerMatrix im( unique_n, 2 );
    // 3 columns:
    // 1 - start position
    // 2 - end position
    // 3 - id value

    // // if n = 1, there's only 1 unique ID
    // if( n == 1 ) {
    //   im( 0, 0 ) = 0;
    //   im( 0, 1 ) = n - 1;
    //   return im;
    // }

    R_xlen_t i;

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

        if( idx >= start_positions.length() ) {
          Rcpp::stop("sfheaders - error indexing lines, perhaps caused by un-ordered data?");
        }

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


  inline Rcpp::IntegerMatrix id_positions(
      Rcpp::NumericVector& line_ids,
      Rcpp::NumericVector& unique_ids
  ) {

    R_xlen_t n = line_ids.length();
    R_xlen_t unique_n = unique_ids.length();

    Rcpp::IntegerMatrix im( unique_n, 2);


    // // if n = 1, there's only 1 unique ID
    // if( n == 1 ) {
    //   im( 0, 0 ) = 0;
    //   im( 0, 1 ) = n - 1;
    //   return im;
    // }

    R_xlen_t i;

    Rcpp::IntegerVector start_positions( unique_n );
    Rcpp::IntegerVector end_positions( unique_n );

    int idx = 0;
    double this_id;
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

        if( idx >= start_positions.length() ) {
          Rcpp::stop("sfheaders - error indexing lines, perhaps caused by un-ordered data?");  // #nocov
        }

        start_positions[ idx ] = i;
        this_id = line_ids[ i ];
      }

      if( i == ( n - 1 ) ) {
        end_positions[ idx ] = i;
      }
    }

    if( start_positions.length() != end_positions.length() ) {
      Rcpp::stop("sfheaders - error indexing lines, perhaps caused by un-ordered data?");  // #nocov
    }

    im( Rcpp::_, 0 ) = start_positions;
    im( Rcpp::_, 1 ) = end_positions;

    return im;
  }

  inline Rcpp::IntegerMatrix id_positions(
      Rcpp::StringVector& line_ids,
      Rcpp::StringVector& unique_ids
  ) {

    R_xlen_t n = line_ids.length();
    R_xlen_t unique_n = unique_ids.length();

    Rcpp::IntegerMatrix im( unique_n, 2);

    // // if n = 1, there's only 1 unique ID
    // if( n == 1 ) {
    //   im( 0, 0 ) = 0;
    //   im( 0, 1 ) = n - 1;
    //   return im;
    // }

    R_xlen_t i;

    Rcpp::IntegerVector start_positions( unique_n );
    Rcpp::IntegerVector end_positions( unique_n );

    int idx = 0;
    Rcpp::String this_id;
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

        if( idx >= start_positions.length() ) {
          Rcpp::stop("sfheaders - error indexing lines, perhaps caused by un-ordered data?"); // #nocov
        }

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

  // returns a matrix with the indeces of the start & end of each shape/ geometry
  inline Rcpp::IntegerMatrix id_positions(
    SEXP& line_ids,
    SEXP& unique_ids
  ) {
    if( TYPEOF( line_ids ) != TYPEOF( unique_ids ) ) {
      Rcpp::stop("sfheaders - line_ids and unique_ids are not the same type"); // #nocov
    }

    switch( TYPEOF( line_ids ) ) {
    case LGLSXP: {
      // Rcpp::LogicalVector lv_line_ids = Rcpp::as< Rcpp::LogicalVector >( line_ids );
      // Rcpp::LogicalVector lv_unique_ids = Rcpp::as< Rcpp::LogicalVector >( unique_ids );
      // return id_positions( lv_line_ids, lv_unique_ids );
    }
    case INTSXP: {
      Rcpp::IntegerVector iv_line_ids = Rcpp::as< Rcpp::IntegerVector >( line_ids );
      Rcpp::IntegerVector iv_unique_ids = Rcpp::as< Rcpp::IntegerVector >( unique_ids );
      return id_positions( iv_line_ids, iv_unique_ids );
    }
    case REALSXP: {
      Rcpp::NumericVector nv_line_ids = Rcpp::as< Rcpp::NumericVector >( line_ids );
      Rcpp::NumericVector nv_unique_ids = Rcpp::as< Rcpp::NumericVector >( unique_ids );
      return id_positions( nv_line_ids, nv_unique_ids );
    }
    case STRSXP: {
      Rcpp::StringVector sv_line_ids = Rcpp::as< Rcpp::StringVector >( line_ids );
      Rcpp::StringVector sv_unique_ids = Rcpp::as< Rcpp::StringVector >( unique_ids );
      return id_positions( sv_line_ids, sv_unique_ids );
    }
    default: {
      Rcpp::stop("sfheaders - unsupported vector type for determining id positions"); // #nocov
    }
    }

    return Rcpp::IntegerMatrix(0);
  }

  inline Rcpp::IntegerMatrix id_positions(
    Rcpp::StringVector& line_ids
  ) {
    Rcpp::StringVector unique_ids = sfheaders::utils::get_sexp_unique( line_ids );
    return id_positions( line_ids, unique_ids );
  }

  inline Rcpp::IntegerMatrix id_positions(
    Rcpp::IntegerVector& line_ids
  ) {
    Rcpp::IntegerVector unique_ids = sfheaders::utils::get_sexp_unique( line_ids );
    return id_positions( line_ids, unique_ids );
  }

  inline Rcpp::IntegerMatrix id_positions(
    Rcpp::NumericVector& line_ids
  ) {
    Rcpp::NumericVector unique_ids = sfheaders::utils::get_sexp_unique( line_ids );
    return id_positions( line_ids, unique_ids );
  }

  inline Rcpp::IntegerMatrix id_positions(
    SEXP& line_ids
  ) {
    SEXP unique_ids = sfheaders::utils::get_sexp_unique( line_ids );
    return id_positions( line_ids, unique_ids );
  }

} // utils
} // sfheaders

#endif
