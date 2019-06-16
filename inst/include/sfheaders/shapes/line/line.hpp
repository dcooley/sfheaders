#ifndef R_SFHEADERS_SHAPES_LINE_H
#define R_SFHEADERS_SHAPES_LINE_H

#include <Rcpp.h>
#include "sfheaders/utils.hpp"

namespace sfheaders {
namespace shapes {

// -- LINES
// get lines from
// - matrix
// - matrix with columns identified
// - data.frame
// - data.frame with columns identified
inline SEXP get_line(
    Rcpp::IntegerMatrix& im,
    Rcpp::IntegerVector& cols
) {
  size_t n_row = im.nrow();
  size_t n_col = cols.size();
  size_t i;
  Rcpp::IntegerMatrix im2( n_row, n_col );
  for( i = 0; i < n_col; i++ ) {
    int this_col = cols[ i ];
    im2( Rcpp::_, i ) = im( Rcpp::_, this_col );
  }
  return im2;
}


inline SEXP get_line(
    Rcpp::NumericMatrix& nm,
    Rcpp::IntegerVector& cols
) {
  size_t n_row = nm.nrow();
  size_t n_col = cols.size();
  size_t i;
  Rcpp::NumericMatrix nm2( n_row, n_col );
  for( i = 0; i < n_col; i++ ) {
    int this_col = cols[ i ];
    nm2( Rcpp::_, i ) = nm( Rcpp::_, this_col );
  }
  return nm2;
}

inline SEXP get_line(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& geometry_cols
) {
  size_t n_col = geometry_cols.size();
  if( df.ncol() < n_col ) {
    Rcpp::stop("sfheaders - incorrect number of columns");
  }
  size_t n_row = df.nrow();
  Rcpp::NumericMatrix nm( n_row, n_col );
  size_t i;

  for( i = 0; i < n_col; i++ ) {
    Rcpp::String this_col = geometry_cols[i];
    Rcpp::NumericVector this_vec = df[ this_col ];
    nm( Rcpp::_, i ) = this_vec;
  }
  return nm;
}

// gets lines from data.farme
// when the start & end rows are known
inline SEXP get_line(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& geometry_cols,
    int& start,
    int& end
) {

  size_t i;
  size_t n_col = geometry_cols.length();
  int line_rows = end - start + 1;
  Rcpp::NumericMatrix a_line( line_rows, ( n_col) );

  for( i = 0; i < n_col; i++ ) {
    Rcpp::String this_col = geometry_cols[ i ];
    Rcpp::NumericVector v = Rcpp::as< Rcpp::NumericVector >( df[ this_col ] );
    a_line( Rcpp::_, i ) = v[ Rcpp::Range(start, end) ];
  }
  return a_line;
}

inline SEXP get_line(
    Rcpp::DataFrame& df,
    Rcpp::IntegerVector& geometry_cols,
    int& start,
    int& end
) {

  size_t i;
  size_t n_col = geometry_cols.length();
  int line_rows = end - start + 1;
  Rcpp::NumericMatrix a_line( line_rows, ( n_col) );

  for( i = 0; i < n_col; i++ ) {
    int this_col = geometry_cols[ i ];
    Rcpp::NumericVector v = Rcpp::as< Rcpp::NumericVector >( df[ this_col ] );
    a_line( Rcpp::_, i ) = v[ Rcpp::Range(start, end) ];
  }
  return a_line;
}


// gets lines from data.farme
// when the start & end rows are known
// where geometry_cols are ordered?
inline SEXP get_line(
    Rcpp::NumericMatrix& nm,
    Rcpp::IntegerVector& geometry_cols,
    int& start,
    int& end
) {

  size_t i;
  size_t n_col = geometry_cols.length();
  int line_rows = end - start + 1;

  // matrix can just be subset by cols and rows
  Rcpp::Range rows = Rcpp::Range( start, end );
  Rcpp::Range cols = Rcpp::Range( geometry_cols[0], geometry_cols[ ( n_col - 1 ) ] );
  Rcpp::NumericMatrix a_line = nm( rows, cols );

  return a_line;
}


inline SEXP get_line(
    Rcpp::NumericMatrix& nm,
    Rcpp::StringVector& geometry_cols,
    int& start,
    int& end
) {

  Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );
  return get_line( df, geometry_cols, start, end );
}

// get list of lines (e.g. MULTILINESTRING)
// from a data.frame, where geometry_cols are specified, and a vector of line_ids
// gives a 'line_id' for each row
// - assumes df is sorted by line_id
inline SEXP get_lines(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& geometry_cols,
    Rcpp::IntegerVector& line_ids
) {

  Rcpp::IntegerVector unique_ids = Rcpp::sort_unique( line_ids );
  Rcpp::IntegerMatrix line_positions = sfheaders::utils::line_ids( line_ids, unique_ids );

  size_t n_lines = unique_ids.length();

  Rcpp::List mls( n_lines );

  // now iterate through the data.frame and get the matrices of lines
  int first_id = line_ids[0];
  size_t i, j;
  for( i = 0; i < n_lines; i++ ) {

    int start = line_positions(i, 0);
    int end = line_positions(i, 1);
    int line_rows = end - start + 1;

    mls( i ) = get_line( df, geometry_cols, start, end );
  }
  return mls;
}

inline SEXP get_lines(
    Rcpp::DataFrame& df,
    Rcpp::IntegerVector& geometry_cols,
    Rcpp::IntegerVector& line_ids
) {

  Rcpp::IntegerVector unique_ids = Rcpp::sort_unique( line_ids );
  Rcpp::IntegerMatrix line_positions = sfheaders::utils::line_ids( line_ids, unique_ids );

  size_t n_lines = unique_ids.length();

  Rcpp::List mls( n_lines );

  // now iterate through the data.frame and get the matrices of lines
  int first_id = line_ids[0];
  size_t i, j;
  for( i = 0; i < n_lines; i++ ) {

    int start = line_positions(i, 0);
    int end = line_positions(i, 1);
    int line_rows = end - start + 1;

    mls( i ) = get_line( df, geometry_cols, start, end );
  }
  return mls;
}


}
} // sfheaders


#endif
