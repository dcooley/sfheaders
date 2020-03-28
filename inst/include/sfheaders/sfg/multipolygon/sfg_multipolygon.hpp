#ifndef R_SFHEADERS_SFG_MULTIPOLYGON_H
#define R_SFHEADERS_SFG_MULTIPOLYGON_H

#include <Rcpp.h>
#include "sfheaders/utils/utils.hpp"
#include "sfheaders/shapes/shapes.hpp"
#include "sfheaders/sfg/sfg_types.hpp"
#include "sfheaders/sfg/polygon/close_polygon.hpp"

namespace sfheaders {
namespace sfg {

// multipolygon is a list of list of linestrings (matrices)
inline SEXP sfg_multipolygon(
    Rcpp::IntegerMatrix& im,
    bool close = true
) {
  Rcpp::List p( 1 );
  Rcpp::List mp( 1 );
  p[0] = sfheaders::polygon_utils::close_polygon( im, close );;
  mp[0] = p;
  R_xlen_t n_col = im.ncol();
  sfheaders::sfg::make_sfg( mp, n_col, sfheaders::sfg::SFG_MULTIPOLYGON );

  return mp;
}

inline SEXP sfg_multipolygon(
    Rcpp::NumericMatrix& nm,
    bool close = true
) {
  Rcpp::List p( 1 );
  Rcpp::List mp( 1 );
  p[0] = sfheaders::polygon_utils::close_polygon( nm, close );;
  mp[0] = p;
  R_xlen_t n_col = nm.ncol();
  sfheaders::sfg::make_sfg( mp, n_col, sfheaders::sfg::SFG_MULTIPOLYGON );

  return mp;
}

inline SEXP sfg_multipolygon(
    Rcpp::DataFrame& df,
    bool close = true
) {

  Rcpp::NumericMatrix nm = sfheaders::utils::df_to_matrix( df );
  Rcpp::List p( 1 );
  Rcpp::List mp( 1 );
  p[0] = sfheaders::polygon_utils::close_polygon( nm, close );;
  mp[0] = p;
  R_xlen_t n_col = nm.ncol();
  sfheaders::sfg::make_sfg( mp, n_col, sfheaders::sfg::SFG_MULTIPOLYGON );

  return mp;
}

// need to check if it's a list of lists, OR a list with a matrix or df...

inline SEXP sfg_multipolygon(
    Rcpp::List& lst,
    bool close = true
) {

  lst = sfheaders::polygon_utils::close_polygon( lst, close );
  sfheaders::sfg::make_sfg( lst, sfheaders::sfg::SFG_MULTIPOLYGON );
  return lst;
}


inline SEXP sfg_multipolygon(
    Rcpp::DataFrame& df,
    Rcpp::IntegerVector& cols,
    bool close = true
) {
  Rcpp::NumericMatrix nm = sfheaders::shapes::get_mat( df, cols );
  return sfg_multipolygon( nm, close );
}

inline SEXP sfg_multipolygon(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& cols,
    bool close = true
) {
  Rcpp::NumericMatrix nm = sfheaders::shapes::get_mat( df, cols );
  return sfg_multipolygon( nm, close );
}

inline SEXP sfg_multipolygon(
    Rcpp::NumericMatrix& nm,
    Rcpp::IntegerVector& cols,
    bool close = true
) {
  Rcpp::NumericMatrix nm2 = sfheaders::shapes::get_mat( nm, cols );
  return sfg_multipolygon( nm2, close );
}

inline SEXP sfg_multipolygon(
    Rcpp::NumericMatrix& nm,
    Rcpp::StringVector& cols,
    bool close = true
) {
  Rcpp::NumericMatrix nm2 = sfheaders::shapes::get_mat( nm, cols );
  return sfg_multipolygon( nm2, close );
}

inline SEXP sfg_multipolygon(
    Rcpp::IntegerMatrix& im,
    Rcpp::IntegerVector& cols,
    bool close = true
) {
  Rcpp::IntegerMatrix im2 = sfheaders::shapes::get_mat( im, cols );
  return sfg_multipolygon( im2, close );
}

inline SEXP sfg_multipolygon(
    Rcpp::IntegerMatrix& im,
    Rcpp::StringVector& cols,
    bool close = true
) {
  Rcpp::IntegerMatrix im2 = sfheaders::shapes::get_mat( im, cols );
  return sfg_multipolygon( im2, close );
}

// We're still on single sfg objects.
// when we go up to sfc objects then we will need multiline_id & line_id
inline SEXP sfg_multipolygon(
    Rcpp::DataFrame& df,
    Rcpp::IntegerVector& cols,
    int& id_col,
    bool close = true
) {
  Rcpp::List lst = sfheaders::shapes::get_listMat( df, cols, id_col );
  return sfg_multipolygon( lst, close );
}

inline SEXP sfg_multipolygon(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& cols,
    Rcpp::String& id_col,
    bool close = true
) {
  Rcpp::List lst = sfheaders::shapes::get_listMat( df, cols, id_col );
  return sfg_multipolygon( lst, close );
}

inline SEXP sfg_multipolygon(
    Rcpp::NumericMatrix& nm,
    Rcpp::IntegerVector& cols,
    int& id_col,
    bool close = true
) {
  Rcpp::List lst = sfheaders::shapes::get_listMat( nm, cols, id_col );
  return sfg_multipolygon( lst, close );
}

inline SEXP sfg_multipolygon(
    Rcpp::NumericMatrix& nm,
    Rcpp::StringVector& cols,
    Rcpp::String& id_col,
    bool close = true
) {
  Rcpp::List lst = sfheaders::shapes::get_listMat( nm, cols, id_col );
  return sfg_multipolygon( lst, close );
}

inline SEXP sfg_multipolygon(
    Rcpp::IntegerMatrix& im,
    Rcpp::IntegerVector& cols,
    int& id_col,
    bool close = true
) {
  Rcpp::List lst = sfheaders::shapes::get_listMat( im, cols, id_col );
  return sfg_multipolygon( lst, close );
}

inline SEXP sfg_multipolygon(
    Rcpp::IntegerMatrix& im,
    Rcpp::StringVector& cols,
    Rcpp::String& id_col,
    bool close = true
) {
  Rcpp::List lst = sfheaders::shapes::get_listMat( im, cols, id_col );
  return sfg_multipolygon( lst, close );
}

  inline SEXP sfg_multipolygon(
    Rcpp::IntegerMatrix& im,
    Rcpp::IntegerVector& geometry_cols,
    int& polygon_id_column,
    int& line_id_column,
    bool close = true
  ) {
    Rcpp::List mp = sfheaders::shapes::get_listListMat( im, geometry_cols, polygon_id_column, line_id_column );
    return sfg_multipolygon( mp, close );
  }

  inline SEXP sfg_multipolygon(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& geometry_cols,
      Rcpp::String& polygon_id_column,
      Rcpp::String& line_id_column,
      bool close = true
  ) {
    Rcpp::List mp = sfheaders::shapes::get_listListMat( im, geometry_cols, polygon_id_column, line_id_column );
    return sfg_multipolygon( mp, close );
  }

  inline SEXP sfg_multipolygon(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& geometry_cols,
      int& polygon_id_column,
      int& line_id_column,
      bool close = true
  ) {
    Rcpp::List mp = sfheaders::shapes::get_listListMat( nm, geometry_cols, polygon_id_column, line_id_column );
    return sfg_multipolygon( mp, close );
  }

  inline SEXP sfg_multipolygon(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& geometry_cols,
      Rcpp::String& polygon_id_column,
      Rcpp::String& line_id_column,
      bool close = true
  ) {
    Rcpp::List mp = sfheaders::shapes::get_listListMat( nm, geometry_cols, polygon_id_column, line_id_column );
    return sfg_multipolygon( mp, close );
  }

  inline SEXP sfg_multipolygon(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& geometry_cols,
      int& polygon_id_column,
      int& line_id_column,
      bool close = true
  ) {
    Rcpp::List mp = sfheaders::shapes::get_listListMat( df, geometry_cols, polygon_id_column, line_id_column );
    return sfg_multipolygon( mp, close );
  }


  inline SEXP sfg_multipolygon(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& geometry_cols,
      Rcpp::String& polygon_id_column,
      Rcpp::String& line_id_column,
      bool close = true
  ) {
    Rcpp::List mp = sfheaders::shapes::get_listListMat( df, geometry_cols, polygon_id_column, line_id_column );
    return sfg_multipolygon( mp, close );
  }


inline SEXP sfg_multipolygon(
    SEXP& x,
    Rcpp::IntegerVector& cols,
    bool close = true
) {
  switch( TYPEOF( x ) ) {
  case INTSXP: {
    if( !Rf_isMatrix( x ) ) {
    Rcpp::stop("sfheaders - expecting a matrix"); // #nocov
  }
    Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
    return sfg_multipolygon( im, cols, close );
  }
  case REALSXP: {
    if( !Rf_isMatrix( x ) ) {
    Rcpp::stop("sfheaders - expecting a matrix"); // #nocov
  }
    Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
    return sfg_multipolygon( nm, cols, close );
  }
  case VECSXP: {
    if( Rf_inherits( x, "data.frame") ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
    return sfg_multipolygon( df, cols, close );
  } // else default
  }
  default: {
    Rcpp::stop("sfheaders - unsupported sfg_LINESTRING type");  // #nocov
  }
  }

  return Rcpp::List::create(); // never reaches
}



inline SEXP sfg_multipolygon(
    SEXP& x,
    Rcpp::IntegerVector& cols,
    int& line_id,
    bool close = true
) {
  switch( TYPEOF( x ) ) {
  case INTSXP: {
    if( !Rf_isMatrix( x ) ) {
    Rcpp::stop("sfheaders - expecting a matrix"); // #nocov
  }
    Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
    return sfg_multipolygon( im, cols, line_id, close );
  }
  case REALSXP: {
    if( !Rf_isMatrix( x ) ) {
    Rcpp::stop("sfheaders - expecting a matrix"); // #nocov
  }
    Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
    return sfg_multipolygon( nm, cols, line_id, close );
  }
  case VECSXP: {
    if( Rf_inherits( x, "data.frame") ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
    return sfg_multipolygon( df, cols, line_id, close );
  } // else default
  }
  default: {
    Rcpp::stop("sfheaders - unsupported sfg_LINESTRING type");  // #nocov
  }
  }

  return Rcpp::List::create(); // never reaches
}


// inline SEXP sfg_multipolygon(
//     SEXP& x,
//     Rcpp::IntegerVector& cols,
//     Rcpp::String& line_id
// ) {
//   switch( TYPEOF( x ) ) {
//   case INTSXP: {
//     if( !Rf_isMatrix( x ) ) {
//     Rcpp::stop("sfheaders - expecting a matrix");
//   }
//     Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
//     return sfg_multipolygon( im, cols, line_id );
//   }
//   case REALSXP: {
//     if( !Rf_isMatrix( x ) ) {
//     Rcpp::stop("sfheaders - expecting a matrix");
//   }
//     Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
//     return sfg_multipolygon( nm, cols, line_id );
//   }
//   case VECSXP: {
//     if( Rf_inherits( x, "data.frame") ) {
//     Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
//     return sfg_multipolygon( df, cols, line_id );
//   } // else default
//   }
//   default: {
//     Rcpp::stop("sfheaders - unsupported sfg_LINESTRING type");
//   }
//   }
//
//   return Rcpp::List::create(); // never reaches
// }


inline SEXP sfg_multipolygon(
    SEXP& x,
    Rcpp::StringVector& cols,
    bool close = true
) {
  switch( TYPEOF( x ) ) {
  case INTSXP: {
    if( !Rf_isMatrix( x ) ) {
    Rcpp::stop("sfheaders - expecting a matrix"); // #nocov
  }
    Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
    return sfg_multipolygon( im, cols, close );
  }
  case REALSXP: {
    if( !Rf_isMatrix( x ) ) {
    Rcpp::stop("sfheaders - expecting a matrix"); // #nocov
  }
    Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
    return sfg_multipolygon( nm, cols, close );
  }
  case VECSXP: {
    if( Rf_inherits( x, "data.frame") ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
    return sfg_multipolygon( df, cols, close );
  } // else default
  }
  default: {
    Rcpp::stop("sfheaders - unsupported sfg_MULTIPOLYGON type");  // #nocov
  }
  }

  return Rcpp::List::create(); // never reaches
}

// inline SEXP sfg_multipolygon(
//     SEXP& x,
//     Rcpp::StringVector& cols,
//     int& line_id
// ) {
//   switch( TYPEOF( x ) ) {
//   case INTSXP: {
//     if( !Rf_isMatrix( x ) ) {
//     Rcpp::stop("sfheaders - expecting a matrix");
//   }
//     Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
//     return sfg_multipolygon( im, cols, line_id );
//   }
//   case REALSXP: {
//     if( !Rf_isMatrix( x ) ) {
//     Rcpp::stop("sfheaders - expecting a matrix");
//   }
//     Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
//     return sfg_multipolygon( nm, cols, line_id );
//   }
//   case VECSXP: {
//     if( Rf_inherits( x, "data.frame") ) {
//     Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
//     return sfg_multipolygon( df, cols, line_id );
//   } // else default
//   }
//   default: {
//     Rcpp::stop("sfheaders - unsupported sfg_MULTIPOLYGON type");
//   }
//   }
//
//   return Rcpp::List::create(); // never reaches
// }

inline SEXP sfg_multipolygon(
    SEXP& x,
    Rcpp::StringVector& cols,
    Rcpp::String& line_id,
    bool close = true
) {
  switch( TYPEOF( x ) ) {
  case INTSXP: {
    if( !Rf_isMatrix( x ) ) {
    Rcpp::stop("sfheaders - expecting a matrix"); // #nocov
  }
    Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
    return sfg_multipolygon( im, cols, line_id, close );
  }
  case REALSXP: {
    if( !Rf_isMatrix( x ) ) {
    Rcpp::stop("sfheaders - expecting a matrix"); // #nocov
  }
    Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
    return sfg_multipolygon( nm, cols, line_id, close );
  }
  case VECSXP: {
    if( Rf_inherits( x, "data.frame") ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
    return sfg_multipolygon( df, cols, line_id, close );
  } // else default
  }
  default: {
    Rcpp::stop("sfheaders - unsupported sfg_MULTIPOLYGON type");  // #nocov
  }
  }

  return Rcpp::List::create(); // never reaches
}


inline SEXP sfg_multipolygon(
    SEXP& x,
    bool close = true
) {

  switch ( TYPEOF( x ) ) {
  case INTSXP: {
    if( !Rf_isMatrix( x ) ) {
    Rcpp::stop("sfheaders - expecting a matrix"); // #nocov
  }
    Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
    return sfg_multipolygon( im, close );
  }
  case REALSXP: {
    if( !Rf_isMatrix( x ) ) {
    Rcpp::stop("sfheaders - expecting a matrix"); // #nocov
  }
    Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
    return sfg_multipolygon( nm, close );
  }
  case VECSXP: {
    if( Rf_inherits( x, "data.frame") ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
    return sfg_multipolygon( df, close );
  } else {
    Rcpp::List lst = Rcpp::as< Rcpp::List >( x );
    return sfg_multipolygon( lst, close );
  }
  }
  default: {
    Rcpp::stop("sfheaders - unsupported sfg_MULTIPOLYGON type");  // #nocov
  }
  }
  return x; // never reaches
}


inline SEXP sfg_multipolygon(
    SEXP& x,
    SEXP& cols,
    bool close = true
) {
  if( Rf_isNull( cols ) ) {
    return sfg_multipolygon( x, close );
  }
  switch( TYPEOF( cols ) ) {
  case REALSXP: {}
  case INTSXP: {
    Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( cols );
    return sfg_multipolygon( x, iv, close );
  }
  case STRSXP: {
    Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( cols );
    return sfg_multipolygon( x, sv, close );
  }
  default: {
    Rcpp::stop("sfheaders - unknown column types");  // #nocov
  }
  }
  return Rcpp::List::create(); // never reaches
}


inline SEXP sfg_multipolygon(
    SEXP& x,
    SEXP& cols,
    Rcpp::String& line_id,
    bool close = true
) {
  if( Rf_isNull( cols ) ) {
    Rcpp::StringVector id_cols( 1 );
    id_cols[0] = line_id;
    SEXP other_cols = sfheaders::utils::other_columns( x, id_cols );
    return sfg_multipolygon( x, other_cols, line_id, close );
  }
  switch( TYPEOF( cols ) ) {
  // case REALSXP: {}
  // case INTSXP: {
  //   Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( cols );
  //   return sfg_multipolygon( x, iv, line_id );
  // }
  case STRSXP: {
    Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( cols );
    return sfg_multipolygon( x, sv, line_id, close );
  }
  default: {
    Rcpp::stop("sfheaders - unknown column types");
  }
  }
  return Rcpp::List::create(); // never reaches
}


inline SEXP sfg_multipolygon(
    SEXP& x,
    SEXP& cols,
    int& line_id,
    bool close = true
) {

  if( Rf_isNull( cols ) ) {
    Rcpp::IntegerVector id_cols( 1 );
    id_cols[0] = line_id;
    SEXP other_cols = sfheaders::utils::other_columns( x, id_cols );
    return sfg_multipolygon( x, other_cols, line_id, close );
  }
  switch( TYPEOF( cols ) ) {
  case REALSXP: {}
  case INTSXP: {
    Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( cols );
    return sfg_multipolygon( x, iv, line_id, close );
  }
  // case STRSXP: {
  //   Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( cols );
  //   return sfg_multipolygon( x, sv, line_id );
  // }
  default: {
    Rcpp::stop("sfheaders - unknown column types");
  }
  }
  return Rcpp::List::create(); // never reaches
}

inline SEXP sfg_multipolygon(
  SEXP& x,
  Rcpp::IntegerVector geometry_cols,
  int& polygon_id,
  int& line_id,
  bool close = true
) {
  Rcpp::List mp = sfheaders::shapes::get_listListMat( x, geometry_cols, polygon_id, line_id );
  return sfg_multipolygon( mp, close );
}

inline SEXP sfg_multipolygon(
    SEXP& x,
    Rcpp::StringVector geometry_cols,
    Rcpp::String& polygon_id,
    Rcpp::String& line_id,
    bool close = true
) {
  Rcpp::List mp = sfheaders::shapes::get_listListMat( x, geometry_cols, polygon_id, line_id );
  return sfg_multipolygon( mp, close );
}


inline SEXP sfg_multipolygon(
    SEXP& x,
    SEXP& cols,
    int& polygon_id,
    int& line_id,
    bool close = true
) {

  // #nocov start
  if( Rf_isNull( cols ) ) {
    Rcpp::IntegerVector id_cols( 2 );
    id_cols[0] = polygon_id;
    id_cols[1] = line_id;
    SEXP other_cols = sfheaders::utils::other_columns( x, id_cols );
    return sfg_multipolygon( x, other_cols, polygon_id, line_id, close );
  }
  // #nocov end

  switch( TYPEOF( cols ) ) {
  case REALSXP: {}
  case INTSXP: {
    Rcpp::IntegerVector geometry_cols = Rcpp::as< Rcpp::IntegerVector >( cols );
    return sfg_multipolygon( x, geometry_cols, polygon_id, line_id, close );
  }
  // case STRSXP: {
  //   Rcpp::StringVector geometry_cols = Rcpp::as< Rcpp::StringVector >( cols );
  //   return sfg_multipolygon( x, geometry_cols, polygon_id, line_id );
  // }
  default: {
    Rcpp::stop("sfheaders - unknown column types");  // #nocov
  }
  }
}

inline SEXP sfg_multipolygon(
    SEXP& x,
    SEXP& cols,
    Rcpp::String& polygon_id,
    Rcpp::String& line_id,
    bool close = true
) {

  // #nocov start
  if( Rf_isNull( cols ) ) {
    Rcpp::StringVector id_cols( 2 );
    id_cols[0] = polygon_id;
    id_cols[1] = line_id;
    SEXP other_cols = sfheaders::utils::other_columns( x, id_cols );
    return sfg_multipolygon( x, other_cols, polygon_id, line_id, close );
  }
  // #nocov end

  switch( TYPEOF( cols ) ) {
  // case REALSXP: {}
  // case INTSXP: {
  //   Rcpp::IntegerVector geometry_cols = Rcpp::as< Rcpp::IntegerVector >( cols );
  //   return sfg_multipolygon( x, geometry_cols, polygon_id, line_id );
  // }
  case STRSXP: {
    Rcpp::StringVector geometry_cols = Rcpp::as< Rcpp::StringVector >( cols );
    return sfg_multipolygon( x, geometry_cols, polygon_id, line_id, close );
  }
  default: {
    Rcpp::stop("sfheaders - unknown column types");
  }
  }
}


inline SEXP sfg_multipolygon(
    SEXP& x,
    SEXP& cols,
    SEXP& polygon_id,
    SEXP& line_id,
    bool close = true
) {
  if( Rf_isNull( polygon_id ) && Rf_isNull( line_id ) ) {
    return sfg_multipolygon( x, cols, close );
  }

  // at this point one or both of polygon_id and line_id will not be null
  //
  if( Rf_isNull( cols ) ) {
    // make them the other columns
    SEXP other_cols = sfheaders::utils::other_columns(x, polygon_id, line_id );
    return sfg_multipolygon( x, other_cols, polygon_id, line_id, close );
  }

  if( Rf_isNull( polygon_id ) && !Rf_isNull( line_id ) ) {
    // in this case the multiolygon is made of one polygon
    // with one or more internal rings

    // TODO: 'cols' may be null here


    Rcpp::List sfg(1);
    sfg[0] = sfheaders::shapes::get_listMat( x, cols, line_id );
    return sfg_multipolygon( sfg, close );
  }

  if( !Rf_isNull( polygon_id ) && Rf_isNull( line_id ) ) {
    // in this case the multipolygon is made of one polygon
    // with one or more polygons,
    // but each polygon has a single line
    SEXP line_id2 = polygon_id;
    return sfg_multipolygon( x, cols, polygon_id, line_id2, close );
  }

  // otherwise they are both provided
  if( TYPEOF( polygon_id ) != TYPEOF( line_id ) ) {
    Rcpp::stop("polygon_id and line_id must be the same type");  // #nocov
  }

  switch( TYPEOF( line_id ) ) {
  case REALSXP: {}
  case INTSXP: {
    Rcpp::IntegerVector iv_line = Rcpp::as< Rcpp::IntegerVector >( line_id );
    Rcpp::IntegerVector iv_polygon = Rcpp::as< Rcpp::IntegerVector >( polygon_id );
    int il = iv_line[0];
    int ip = iv_polygon[0];
    return sfg_multipolygon( x, cols, ip, il, close );
  }
  case STRSXP: {
    Rcpp::StringVector sv_line = Rcpp::as< Rcpp::StringVector >( line_id );
    Rcpp::StringVector sv_polygon = Rcpp::as< Rcpp::StringVector >( polygon_id );

    Rcpp::String sl = sv_line[0];
    Rcpp::String sp = sv_polygon[0];
    //return Rcpp::List();
    return sfg_multipolygon( x, cols, sp, sl, close );
  }
  default: {
    Rcpp::stop("sfheaders - unknown column types");  // #nocov
  }
  }
  return Rcpp::List::create(); // never reaches
}

  // only keep the outer-linestring / ring / matrix
  inline SEXP remove_multipolygon_holes(
      Rcpp::List& sfg_mp,
      bool close = true
  ) {
    // loop over and only keep the first line
    R_xlen_t i;
    R_xlen_t n = sfg_mp.size();
    Rcpp::List res( n );
    for( i = 0; i < n; ++i ) {
      Rcpp::List poly = sfg_mp[ i ];
      Rcpp::List new_poly(1);
      new_poly[ 0 ] = poly[ 0 ];
      res[ i ] = new_poly;
    }
    return sfg_multipolygon( res, close );

  }

} // sfg
} // sfheaders

#endif
