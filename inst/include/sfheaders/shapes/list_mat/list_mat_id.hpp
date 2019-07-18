#ifndef R_SFHEADERS_SHAPES_LIST_MAT_ID_H
#define R_SFHEADERS_SHAPES_LIST_MAT_ID_H

#include <Rcpp.h>
#include "sfheaders/utils/utils.hpp"
#include "sfheaders/shapes/list_mat/list_mat.hpp"

namespace sfheaders {
namespace shapes {

// inline SEXP get_listMatId(
//     Rcpp::IntegerMatrix& im
// ) {
//   Rcpp::List lst(1);
//   lst[0] = im;
//   return lst;
// }
//
// inline SEXP get_listMatId(
//     Rcpp::NumericMatrix& nm
// ) {
//   Rcpp::List lst(1);
//   lst[0] = nm;
//   return lst;
// }
//
// inline SEXP get_listMatId(
//     Rcpp::DataFrame& df
// ) {
//   Rcpp::NumericMatrix nm = sfheaders::utils::df_to_matrix( df );
//   return get_listMatId( nm );
// }
//
// inline SEXP get_listMatId(
//     Rcpp::DataFrame& df,
//     Rcpp::StringVector& geometry_cols,
//     int& start,
//     int& end
// ) {
//   size_t i;
//   size_t n_col = geometry_cols.length();
//   int line_rows = end - start + 1;
//
//   Rcpp::NumericMatrix a_line( line_rows, ( n_col) );
//
//   for( i = 0; i < n_col; i++ ) {
//     Rcpp::String this_col = geometry_cols[ i ];
//     Rcpp::NumericVector v = Rcpp::as< Rcpp::NumericVector >( df[ this_col ] );
//     a_line( Rcpp::_, i ) = v[ Rcpp::Range(start, end) ];
//   }
//   return a_line;
// }
//
// inline SEXP get_listMatId(
//     Rcpp::DataFrame& df,
//     Rcpp::IntegerVector& geometry_cols,
//     int& start,
//     int& end
// ) {
//
//   size_t i;
//   size_t n_col = geometry_cols.length();
//   int line_rows = end - start + 1;
//   Rcpp::NumericMatrix a_line( line_rows, ( n_col) );
//
//   for( i = 0; i < n_col; i++ ) {
//     int this_col = geometry_cols[ i ];
//     Rcpp::NumericVector v = Rcpp::as< Rcpp::NumericVector >( df[ this_col ] );
//     a_line( Rcpp::_, i ) = v[ Rcpp::Range(start, end) ];
//   }
//   return a_line;
// }
//
//
// // gets lines from data.farme
// // when the start & end rows are known
// // where geometry_cols are ordered?
// inline SEXP get_listMatId(
//     Rcpp::NumericMatrix& nm,
//     Rcpp::IntegerVector& geometry_cols,
//     int& start,
//     int& end
// ) {
//   size_t n_col = geometry_cols.length();
//   // matrix can just be subset by cols and rows
//   Rcpp::Range rows = Rcpp::Range( start, end );
//   Rcpp::Range cols = Rcpp::Range( geometry_cols[0], geometry_cols[ ( n_col - 1 ) ] );
//   Rcpp::NumericMatrix a_line = nm( rows, cols );
//   return a_line;
// }
//
// inline SEXP get_listMatId(
//     Rcpp::NumericMatrix& nm,
//     Rcpp::StringVector& geometry_cols,
//     int& start,
//     int& end
// ) {
//
//   Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );
//   return get_listMatId( df, geometry_cols, start, end );
// }
//
//
// inline SEXP get_listMatId(
//     Rcpp::IntegerMatrix& im,
//     Rcpp::IntegerVector& geometry_cols,
//     int& start,
//     int& end
// ) {
//   size_t n_col = geometry_cols.length();
//
//   if( n_col <= 1 ) {
//     Rcpp::stop("sfheaders - need at least 2 columns");
//   }
//
//   // Rcpp::Rcout << "n_col: " << n_col << std::endl;
//   // Rcpp::Rcout << "start: " << start << std::endl;
//   // Rcpp::Rcout << "end: " << end << std::endl;
//
//   //return im;
//
//   // matrix can just be subset by cols and rows
//   Rcpp::Range rows = Rcpp::Range( start, end );
//   Rcpp::Range cols = Rcpp::Range( geometry_cols[0], geometry_cols[ ( n_col - 1 ) ] );
//   Rcpp::IntegerMatrix a_line = im( rows, cols );
//   return a_line;
// }
//
// inline SEXP get_listMatId(
//     Rcpp::IntegerMatrix& im,
//     Rcpp::StringVector& geometry_cols,
//     int& start,
//     int& end
// ) {
//
//   Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );
//   return get_listMatId( df, geometry_cols, start, end );
// }
//
// inline SEXP get_listMatId(
//     Rcpp::DataFrame& df,
//     Rcpp::IntegerVector& geometry_cols
// ) {
//   Rcpp::List lst(1);
//   lst[0] = sfheaders::shapes::get_mat( df, geometry_cols );
//   return lst;
// }

// get list of lines (e.g. MULTILINESTRING)
// from a data.frame, where geometry_cols are specified, and a vector of line_ids
// gives a 'line_id' for each row
// - assumes df is sorted by line_id
inline SEXP get_listMatId(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& geometry_cols,
    Rcpp::NumericVector& line_ids
) {

  Rcpp::NumericVector unique_ids = Rcpp::sort_unique( line_ids );
  Rcpp::IntegerMatrix line_positions = sfheaders::utils::line_ids( line_ids, unique_ids );

  size_t n_lines = unique_ids.length();

  Rcpp::List mls( n_lines );

  // now iterate through the data.frame and get the matrices of lines
  size_t i;
  for( i = 0; i < n_lines; i++ ) {

    int start = line_positions(i, 0);
    int end = line_positions(i, 1);

    mls( i ) = sfheaders::shapes::get_listMat( df, geometry_cols, start, end );
  }
  Rcpp::List sf(2);
  sf[0] = unique_ids;
  sf[1] = mls;
  return sf;
}

inline SEXP get_listMatId(
    Rcpp::DataFrame& df,
    Rcpp::IntegerVector& geometry_cols,
    Rcpp::NumericVector& line_ids
) {

  Rcpp::NumericVector unique_ids = Rcpp::sort_unique( line_ids );
  Rcpp::IntegerMatrix line_positions = sfheaders::utils::line_ids( line_ids, unique_ids );

  size_t n_lines = unique_ids.length();

  Rcpp::List mls( n_lines );

  int start;
  int end;
  if( n_lines == 1 ) {
    mls( 0 ) = sfheaders::shapes::get_mat( df, geometry_cols );
    return mls;
  }

  // now iterate through the data.frame and get the matrices of lines
  size_t i;
  for( i = 0; i < n_lines; i++ ) {

    start = line_positions(i, 0);
    end = line_positions(i, 1);

    mls( i ) = sfheaders::shapes::get_listMat( df, geometry_cols, start, end );
  }
  Rcpp::List sf(2);
  sf[0] = unique_ids;
  sf[1] = mls;
  return sf;
}

// now we know where the columns are, we need to get teh vector of line_ids
// then we can start subsetting
inline SEXP get_listMatId(
    Rcpp::DataFrame& df,
    Rcpp::IntegerVector& cols,
    int& id_col
) {
  Rcpp::NumericVector line_ids = df[ id_col ];
  // Rcpp::Rcout << "get list mat 6 " << std::endl;
  return get_listMatId( df, cols, line_ids );
}


inline SEXP get_listMatId(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& cols,
    Rcpp::String& id_col
) {
  Rcpp::NumericVector line_ids = df[ id_col ];
  return get_listMatId( df, cols, line_ids );
}

inline SEXP get_listMatId(
    Rcpp::IntegerMatrix& im,
    Rcpp::StringVector& cols,
    Rcpp::String& id_col
) {
  Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );
  return get_listMatId( df, cols, id_col );
}

inline SEXP get_listMatId(
    Rcpp::IntegerMatrix& im,
    Rcpp::IntegerVector& cols,
    int& id_col
) {
  Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );
  return get_listMatId( df, cols, id_col );
}

inline SEXP get_listMatId(
    Rcpp::NumericMatrix& nm,
    Rcpp::StringVector& cols,
    Rcpp::String& id_col
) {
  Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );
  return get_listMatId( df, cols, id_col );
}

inline SEXP get_listMatId(
    Rcpp::NumericMatrix& nm,
    Rcpp::IntegerVector& cols,
    int& id_col
) {
  Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );
  // Rcpp::Rcout << "get list mat 5 " << std::endl;
  return get_listMatId( df, cols, id_col );
}

inline SEXP get_listMatId(
    SEXP& x,
    SEXP& cols
) {
  Rcpp::NumericMatrix nm = sfheaders::shapes::get_mat( x, cols );
  return sfheaders::shapes::get_listMat( nm );
}

inline SEXP get_listMatId(
    SEXP& x,
    Rcpp::StringVector& cols,
    Rcpp::String& id_col
){
  switch( TYPEOF( x ) ) {
  case INTSXP: {
    if( !Rf_isMatrix( x ) ) {
    Rcpp::stop("sfheaders - lines need to be matrices or data.frames");
  } else {
    Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
    return get_listMatId( im, cols, id_col );
  }
  }
  case REALSXP: {
    if( !Rf_isMatrix( x ) ) {
    Rcpp::stop("sfheaders - lines need to be matrices or data.frames");
  } else {
    Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
    return get_listMatId( nm, cols, id_col );
  }
  }
  case VECSXP: {
    if( Rf_inherits( x, "data.frame" ) ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
    return get_listMatId( df, cols, id_col );
  } // else default
  }
  default: {
    Rcpp::stop("sfheaders - unknown lines types");
  }
  }
  return Rcpp::List::create(); // never reaches
}

inline SEXP get_listMatId(
    SEXP& x,
    Rcpp::IntegerVector& cols,
    int& id_col
){
  switch( TYPEOF( x ) ) {
  case INTSXP: {
    if( !Rf_isMatrix( x ) ) {
    Rcpp::stop("sfheaders - lines need to be matrices or data.frames");
  } else {
    Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
    // Rcpp::Rcout << "get list mat 3 " << std::endl;
    return get_listMatId( im, cols, id_col );
  }
  }
  case REALSXP: {
    if( !Rf_isMatrix( x ) ) {
    Rcpp::stop("sfheaders - lines need to be matrices or data.frames");
  } else {
    Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
    // Rcpp::Rcout << "get list mat 4 " << std::endl;
    return get_listMatId( nm, cols, id_col );
  }
  }
  case VECSXP: {
    if( Rf_inherits( x, "data.frame" ) ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
    return get_listMatId( df, cols, id_col );
  } // else default
  }
  default: {
    Rcpp::stop("sfheaders - unknown lines types");
  }
  }
  return Rcpp::List::create(); // never reaches
}


inline SEXP get_listMatId(
    SEXP& x,
    SEXP& cols,  // stringvector or integervector
    SEXP& id_col // stringvector or integervector
) {

  if( TYPEOF( id_col ) != TYPEOF( cols ) ) {
    Rcpp::stop("sfheaders - different column types detected");
  }

  switch( TYPEOF( id_col ) ) {
  case REALSXP: {}
  case INTSXP: {
    Rcpp::IntegerVector iv_id_col = Rcpp::as< Rcpp::IntegerVector >( id_col );
    int i_id_col = iv_id_col[0];
    Rcpp::IntegerVector iv_cols = Rcpp::as< Rcpp::IntegerVector >( cols );
    return get_listMatId( x, iv_cols, i_id_col );
  }
  case STRSXP: {
    Rcpp::StringVector sv_id_col = Rcpp::as< Rcpp::StringVector >( id_col );
    Rcpp::String s_id_col = sv_id_col[0];
    Rcpp::StringVector sv_cols = Rcpp::as< Rcpp::StringVector >( cols );
    return get_listMatId( x, sv_cols, s_id_col );
  }
  default: {
    Rcpp::stop("sfheaders - unknown id column types");
  }
  }
  return Rcpp::List::create(); // never reaches
}

}
} // sfheaders


#endif
