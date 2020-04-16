#ifndef R_SFHEADERS_SFC_MULTIPOINT_H
#define R_SFHEADERS_SFC_MULTIPOINT_H

#include <Rcpp.h>
#include "sfheaders/sfc/sfc_types.hpp"
#include "sfheaders/sfc/sfc_attributes.hpp"
#include "sfheaders/sfg/multipoint/sfg_multipoint.hpp"
#include "sfheaders/sfc/bbox.hpp"
#include "sfheaders/sfc/zm_range.hpp"
#include "sfheaders/shapes/shapes.hpp"

namespace sfheaders {
namespace sfc {

  // Requirs a list of sfg_MULTIPOINTs, and the bbox / ranges
  // does not do any calculations; just makes the SFC structure
  inline SEXP sfc_multipoint(
      Rcpp::List& sfc,
      Rcpp::NumericVector& bbox,
      Rcpp::NumericVector& z_range,
      Rcpp::NumericVector& m_range
  ) {
    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTIPOINT, bbox, z_range, m_range );
    return sfc;
  }

inline SEXP sfc_multipoint(
    Rcpp::IntegerMatrix& im,
    std::string xyzm
) {
  //
  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
  Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
  Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

  Rcpp::List sfc( 1 );

  sfheaders::bbox::calculate_bbox( bbox, im );
  sfheaders::zm::calculate_zm_ranges( z_range, m_range, im, xyzm );

  Rcpp::IntegerMatrix mp = sfheaders::sfg::sfg_multipoint( im, xyzm );

  sfc[0] = mp;
  sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTIPOINT, bbox, z_range, m_range );
  return sfc;
}


inline SEXP sfc_multipoint(
    Rcpp::NumericMatrix& nm,
    std::string xyzm
) {

  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
  Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
  Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

  Rcpp::List sfc( 1 );

  sfheaders::bbox::calculate_bbox( bbox, nm );
  sfheaders::zm::calculate_zm_ranges( z_range, m_range, nm, xyzm );

  Rcpp::NumericMatrix mp = sfheaders::sfg::sfg_multipoint( nm, xyzm );

  sfc[0] = mp;
  sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTIPOINT, bbox, z_range, m_range );
  return sfc;
}

inline SEXP sfc_multipoint(
    Rcpp::DataFrame& df,
    std::string xyzm
) {

  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
  Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
  Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

  sfheaders::bbox::calculate_bbox( bbox, df );
  sfheaders::zm::calculate_zm_ranges( z_range, m_range, df, xyzm );

  Rcpp::NumericMatrix mp = sfheaders::sfg::sfg_multipoint( df, xyzm );

  Rcpp::List sfc( 1 );
  sfc[0] = mp;
  sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTIPOINT, bbox, z_range, m_range );
  return sfc;
}


inline SEXP sfc_multipoint(
    Rcpp::IntegerVector& iv,
    std::string xyzm
) {
  int n_col = iv.size();
  Rcpp::IntegerMatrix im(1, n_col);
  im(0, Rcpp::_ ) = iv;
  return sfc_multipoint( im, xyzm );
}

inline SEXP sfc_multipoint(
    Rcpp::NumericVector& nv,
    std::string xyzm
) {
  int n_col = nv.size();
  Rcpp::NumericMatrix nm(1, n_col);
  nm(0, Rcpp::_ ) = nv;
  return sfc_multipoint( nm, xyzm );
}

// inline SEXP sfc_multipoint(
//     Rcpp::List& sfc
// ) {
//
//   Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
//   Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
//   Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();
//
//   R_xlen_t n_multipoints = sfc.size();
//   R_xlen_t i;
//
//   for( i = 0; i < n_multipoints; i++ ) {
//     SEXP this_multipoint = sfc[i];
//
//     // should each element only be allowed to be a matrix??
//     switch( TYPEOF( this_multipoint ) ) {
//     case INTSXP: {
//       if( !Rf_isMatrix( this_multipoint ) ) {
//       Rcpp::stop("sfheaders - expecting a matrix for multipoints");
//     } else {
//       Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( this_multipoint );
//       sfheaders::bbox::calculate_bbox( bbox, im );
//
//       R_xlen_t n_col = im.ncol();
//       if( n_col > 2 ) {
//         sfheaders::zm::calculate_z_range( z_range, im );
//         if( n_col > 3 ) {
//           sfheaders::zm::calculate_m_range( m_range, im );
//         }
//       }
//
//       sfc[i] = sfheaders::sfg::sfg_multipoint( im );
//     }
//     break;
//     }
//     case REALSXP: {
//       if( !Rf_isMatrix( this_multipoint ) ) {
//       Rcpp::stop("sfheaders - expecting a matrix for multipoints");
//     } else {
//       Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( this_multipoint );
//       sfheaders::bbox::calculate_bbox( bbox, nm );
//
//       R_xlen_t n_col = nm.ncol();
//       if( n_col > 2 ) {
//         sfheaders::zm::calculate_z_range( z_range, nm );
//         if( n_col > 3 ) {
//           sfheaders::zm::calculate_m_range( m_range, nm );
//         }
//       }
//
//       sfc[i] = sfheaders::sfg::sfg_multipoint( nm );
//     }
//     break;
//     }
//     default: {
//       Rcpp::stop("sfheaders - unknown multipoint type");
//     }
//     }
//   }
//   sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTIPOINT, bbox, z_range, m_range );
//   return sfc;
//
// }

// no subsetting to do; so just turn the object into a matrix;
inline SEXP sfc_multipoint(
    SEXP& x,
    std::string xyzm
) {
  // here there is no subsetting required;
  // we have to assume the columsn are in order x,y,(z,(m))

  switch( TYPEOF( x ) ) {
  case INTSXP: {
    if( Rf_isMatrix( x ) ) {
    SEXP xc = Rcpp::clone( x );
    Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
    return sfc_multipoint( im, xyzm );
  } else {
    Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
    return sfc_multipoint( iv, xyzm );
  }
  }
  case REALSXP: {
    if( Rf_isMatrix( x ) ) {
    SEXP xc = Rcpp::clone( x );
    Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
    return sfc_multipoint( nm, xyzm );
  } else {
    Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
    return sfc_multipoint( nv, xyzm );
  }
  }
  case VECSXP: {
    if( Rf_inherits( x, "data.frame" ) ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
    return sfc_multipoint( df, xyzm );
  }
  }
  default: {
    Rcpp::stop("sfheaders - unsupported multipoint type");  // #nocov
  }
  }
  return Rcpp::List::create();
}

inline SEXP sfc_multipoint(
    Rcpp::IntegerMatrix& im,
    Rcpp::IntegerVector& geometry_cols,
    std::string xyzm
) {
  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
  Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
  Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

  sfheaders::bbox::calculate_bbox( bbox, im, geometry_cols );

  sfheaders::zm::calculate_zm_ranges( z_range, m_range, im, geometry_cols, xyzm );

  Rcpp::List sfc( 1 );
  Rcpp::NumericMatrix sfg = sfheaders::sfg::sfg_multipoint( im, geometry_cols, xyzm );
  sfc[0] = sfg;
  sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTIPOINT, bbox, z_range, m_range );
  return sfc;
}

inline SEXP sfc_multipoint(
    Rcpp::IntegerMatrix& im,
    Rcpp::StringVector& geometry_cols,
    std::string xyzm
) {

  Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );
  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
  Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
  Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

  sfheaders::bbox::calculate_bbox( bbox, df, geometry_cols );

  sfheaders::zm::calculate_zm_ranges( z_range, m_range, df, geometry_cols, xyzm );

  Rcpp::List sfc( 1 );
  Rcpp::NumericMatrix sfg = sfheaders::sfg::sfg_multipoint( df, geometry_cols, xyzm );
  sfc[0] = sfg;
  sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTIPOINT, bbox, z_range, m_range );
  return sfc;
}

inline SEXP sfc_multipoint(
    Rcpp::NumericMatrix& nm,
    Rcpp::IntegerVector& geometry_cols,
    std::string xyzm
) {
  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
  Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
  Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

  sfheaders::bbox::calculate_bbox( bbox, nm, geometry_cols );

  sfheaders::zm::calculate_zm_ranges( z_range, m_range, nm, geometry_cols, xyzm );

  Rcpp::List sfc( 1 );
  Rcpp::NumericMatrix sfg = sfheaders::sfg::sfg_multipoint( nm, geometry_cols, xyzm );
  sfc[0] = sfg;
  sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTIPOINT, bbox, z_range, m_range );
  return sfc;
}

inline SEXP sfc_multipoint(
    Rcpp::NumericMatrix& nm,
    Rcpp::StringVector& geometry_cols,
    std::string xyzm
) {

  Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );
  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
  Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
  Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

  sfheaders::bbox::calculate_bbox( bbox, df, geometry_cols );
  sfheaders::zm::calculate_zm_ranges( z_range, m_range, df, geometry_cols, xyzm );

  Rcpp::List sfc( 1 );
  Rcpp::NumericMatrix sfg = sfheaders::sfg::sfg_multipoint( df, geometry_cols, xyzm );
  sfc[0] = sfg;
  sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTIPOINT, bbox, z_range, m_range );
  return sfc;
}

inline SEXP sfc_multipoint(
    Rcpp::DataFrame& df,
    Rcpp::IntegerVector& geometry_cols,
    std::string xyzm
) {
  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
  Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
  Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

  sfheaders::bbox::calculate_bbox( bbox, df, geometry_cols );

  sfheaders::zm::calculate_zm_ranges( z_range, m_range, df, geometry_cols, xyzm );

  Rcpp::List sfc( 1 );
  Rcpp::NumericMatrix sfg = sfheaders::sfg::sfg_multipoint( df, geometry_cols, xyzm );
  sfc[0] = sfg;
  sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTIPOINT, bbox, z_range, m_range );
  return sfc;
}

inline SEXP sfc_multipoint(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& geometry_cols,
    std::string xyzm
) {

  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
  Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
  Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

  sfheaders::bbox::calculate_bbox( bbox, df, geometry_cols );

  sfheaders::zm::calculate_zm_ranges( z_range, m_range, df, geometry_cols, xyzm );

  Rcpp::List sfc( 1 );
  Rcpp::NumericMatrix sfg = sfheaders::sfg::sfg_multipoint( df, geometry_cols, xyzm );
  sfc[0] = sfg;
  sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTIPOINT, bbox, z_range, m_range );
  return sfc;
}

inline SEXP sfc_multipoint(
    SEXP& x,
    Rcpp::StringVector& geometry_cols,
    std::string xyzm
) {
  switch( TYPEOF( x ) ) {
  case INTSXP: {
    if( Rf_isMatrix( x ) ) {
    SEXP xc = Rcpp::clone( x );
    Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
    return sfc_multipoint( im, geometry_cols, xyzm );
    // } else {
    //   Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
    //   return sfc_multipoint( iv, geometry_cols );
  }
  }
  case REALSXP: {
    if( Rf_isMatrix( x ) ) {
    SEXP xc = Rcpp::clone( x );
    Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
    return sfc_multipoint( nm, geometry_cols, xyzm );
    // } else {
    //   Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
    //   return sfc_multipoint( nv, geometry_cols );
  }
  }
  case VECSXP: {
    if( Rf_inherits( x, "data.frame" ) ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
    return sfc_multipoint( df, geometry_cols, xyzm );
  }
  }
  default: {
    Rcpp::stop("sfheaders - unsupported multipoint type");  // #nocov
  }
  }
  return Rcpp::List::create();
}

inline SEXP sfc_multipoint(
    SEXP& x,
    Rcpp::IntegerVector& geometry_cols,
    std::string xyzm
) {
  switch( TYPEOF( x ) ) {
  case INTSXP: {
    if( Rf_isMatrix( x ) ) {
    SEXP xc = Rcpp::clone( x );
    Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
    return sfc_multipoint( im, geometry_cols, xyzm );
    // } else {
    //   Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
    //   return sfc_multipoint( iv, geometry_cols );
  }
  }
  case REALSXP: {
    if( Rf_isMatrix( x ) ) {
    SEXP xc = Rcpp::clone( x );
    Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
    return sfc_multipoint( nm, geometry_cols, xyzm );
    // } else {
    //   Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
    //   return sfc_multipoint( nv, geometry_cols );
  }
  }
  case VECSXP: {
    if( Rf_inherits( x, "data.frame" ) ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
    return sfc_multipoint( df, geometry_cols, xyzm );
  }
  }
  default: {
    Rcpp::stop("sfheaders - unsupported multipoint type");  // #nocov
  }
  }
  return Rcpp::List::create();
}

// no subsetting to do (except for columns)
inline SEXP sfc_multipoint(
    SEXP& x,
    SEXP& geometry_cols,
    std::string xyzm
) {
  sfheaders::utils::geometry_column_check( geometry_cols );

  switch( TYPEOF( geometry_cols ) ) {
  case REALSXP: {}
  case INTSXP: {
    Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( geometry_cols );
    return sfc_multipoint( x, iv, xyzm );
  }
  case STRSXP: {
    Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( geometry_cols );
    return sfc_multipoint( x, sv, xyzm );
  }
  default: {
    Rcpp::stop("sfheaders - unknown column type");    // #nocov
  }
  }
  return Rcpp::List::create();
}

inline SEXP sfc_multipoint(
  Rcpp::IntegerMatrix& im,
  Rcpp::IntegerVector& geometry_cols,
  Rcpp::IntegerMatrix& line_positions,
  std::string xyzm
) {
  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
  Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
  Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

  sfheaders::bbox::calculate_bbox( bbox, im, geometry_cols );

  sfheaders::zm::calculate_zm_ranges( z_range, m_range, im, geometry_cols, xyzm );


  R_xlen_t n_lines = line_positions.nrow();

  Rcpp::List sfc( n_lines );

  int start;
  int end;
  if( n_lines == 1 ) {
    sfc( 0 ) = sfheaders::sfg::sfg_multipoint( im, geometry_cols, xyzm );    // #nocov
  } else {

    R_xlen_t i;
    for( i = 0; i < n_lines; ++i ) {

      start = line_positions(i, 0);
      end = line_positions(i, 1);

      Rcpp::NumericMatrix m = sfheaders::shapes::get_listMat( im, geometry_cols, start, end );  // returns a matrix
      sfc( i ) = sfheaders::sfg::sfg_multipoint( m, xyzm );
    }
  }

  sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTIPOINT, bbox, z_range, m_range );
  return sfc;
}

inline SEXP sfc_multipoint(
    Rcpp::IntegerMatrix& im,
    Rcpp::IntegerVector& geometry_cols,
    Rcpp::IntegerVector& line_ids,
    std::string xyzm
) {
  Rcpp::IntegerMatrix line_positions = sfheaders::utils::id_positions( line_ids );
  return sfc_multipoint( im, geometry_cols, line_positions, xyzm );
}

inline SEXP sfc_multipoint(
  Rcpp::NumericMatrix& nm,
  Rcpp::IntegerVector& geometry_cols,
  Rcpp::IntegerMatrix& line_positions,
  std::string xyzm
) {
  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
  Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
  Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

  sfheaders::bbox::calculate_bbox( bbox, nm, geometry_cols );

  sfheaders::zm::calculate_zm_ranges( z_range, m_range, nm, geometry_cols, xyzm );

  R_xlen_t n_lines = line_positions.nrow();

  Rcpp::List sfc( n_lines );

  int start;
  int end;
  if( n_lines == 1 ) {
    sfc( 0 ) = sfheaders::sfg::sfg_multipoint( nm, geometry_cols, xyzm );  // #nocov
  } else {

    R_xlen_t i;
    for( i = 0; i < n_lines; ++i ) {

      start = line_positions(i, 0);
      end = line_positions(i, 1);

      Rcpp::NumericMatrix m = sfheaders::shapes::get_listMat( nm, geometry_cols, start, end );  // returns a matrix
      sfc( i ) = sfheaders::sfg::sfg_multipoint( m, xyzm );
    }
  }

  sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTIPOINT, bbox, z_range, m_range );
  return sfc;
}

inline SEXP sfc_multipoint(
    Rcpp::NumericMatrix& nm,
    Rcpp::IntegerVector& geometry_cols,
    Rcpp::NumericVector& line_ids,
    std::string xyzm
) {
  Rcpp::IntegerMatrix line_positions = sfheaders::utils::id_positions( line_ids );
  return sfc_multipoint( nm, geometry_cols, line_positions, xyzm );
}

inline SEXP sfc_multipoint(
  Rcpp::DataFrame& df,
  Rcpp::StringVector& geometry_cols,
  Rcpp::IntegerMatrix& line_positions,
  std::string xyzm
) {
  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
  Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
  Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

  sfheaders::bbox::calculate_bbox( bbox, df, geometry_cols );

  sfheaders::zm::calculate_zm_ranges( z_range, m_range, df, geometry_cols, xyzm );


  R_xlen_t n_lines = line_positions.nrow();

  Rcpp::List sfc( n_lines );

  int start;
  int end;
  if( n_lines == 1 ) {
    sfc( 0 ) = sfheaders::sfg::sfg_multipoint( df, geometry_cols, xyzm );  // #nocov
  } else {

    R_xlen_t i;
    for( i = 0; i < n_lines; ++i ) {

      start = line_positions(i, 0);
      end = line_positions(i, 1);

      Rcpp::NumericMatrix m = sfheaders::shapes::get_listMat( df, geometry_cols, start, end );  // returns a matrix
      sfc( i ) = sfheaders::sfg::sfg_multipoint( m, xyzm );
    }
  }

  sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTIPOINT, bbox, z_range, m_range );
  return sfc;
}

inline SEXP sfc_multipoint(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& geometry_cols,
    SEXP& line_ids,
    std::string xyzm
) {
  Rcpp::IntegerMatrix line_positions = sfheaders::utils::id_positions( line_ids );
  return sfc_multipoint( df, geometry_cols, line_positions, xyzm );
}

inline SEXP sfc_multipoint(
  Rcpp::DataFrame& df,
  Rcpp::IntegerVector& geometry_cols,
  Rcpp::IntegerMatrix& line_positions,
  std::string xyzm
) {
  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
  Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
  Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

  sfheaders::bbox::calculate_bbox( bbox, df, geometry_cols );

  sfheaders::zm::calculate_zm_ranges( z_range, m_range, df, geometry_cols, xyzm );


  R_xlen_t n_lines = line_positions.nrow();

  Rcpp::List sfc( n_lines );

  int start;
  int end;
  if( n_lines == 1 ) {
    sfc( 0 ) = sfheaders::sfg::sfg_multipoint( df, geometry_cols, xyzm );  // #nocov
  } else {

    R_xlen_t i;
    for( i = 0; i < n_lines; ++i ) {

      start = line_positions(i, 0);
      end = line_positions(i, 1);

      Rcpp::NumericMatrix m = sfheaders::shapes::get_listMat( df, geometry_cols, start, end );  // returns a matrix
      sfc( i ) = sfheaders::sfg::sfg_multipoint( m, xyzm );
    }
  }

  sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTIPOINT, bbox, z_range, m_range );
  return sfc;
}
inline SEXP sfc_multipoint(
    Rcpp::DataFrame& df,
    Rcpp::IntegerVector& geometry_cols,
    SEXP& line_ids,
    std::string xyzm
) {
  Rcpp::IntegerMatrix line_positions = sfheaders::utils::id_positions( line_ids );
  return sfc_multipoint( df, geometry_cols, line_positions, xyzm );
}

inline SEXP sfc_multipoint(
    Rcpp::IntegerMatrix& im,
    Rcpp::IntegerVector& geometry_cols,
    int& multipoint_id,
    std::string xyzm
) {
  sfheaders::utils::column_exists( im, multipoint_id );
  Rcpp::IntegerVector line_ids = im( Rcpp::_, multipoint_id );
  return sfc_multipoint( im, geometry_cols, line_ids, xyzm );
}

inline SEXP sfc_multipoint(
    Rcpp::NumericMatrix& nm,
    Rcpp::IntegerVector& geometry_cols,
    int& multipoint_id,
    std::string xyzm
) {
  sfheaders::utils::column_exists( nm, multipoint_id );
  Rcpp::NumericVector line_ids = nm( Rcpp::_, multipoint_id );
  return sfc_multipoint( nm, geometry_cols, line_ids, xyzm );
}

// #nocov start
inline SEXP sfc_multipoint(
    Rcpp::IntegerMatrix& im,
    Rcpp::StringVector& geometry_cols,
    Rcpp::String& multipoint_id,
    std::string xyzm
) {
  Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );
  SEXP line_ids = df[ multipoint_id ];
  return sfc_multipoint( df, geometry_cols, line_ids, xyzm );
}

inline SEXP sfc_multipoint(
    Rcpp::NumericMatrix& nm,
    Rcpp::StringVector& geometry_cols,
    Rcpp::String& multipoint_id,
    std::string xyzm
) {
  Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );
  SEXP line_ids = df[ multipoint_id ];
  return sfc_multipoint( df, geometry_cols, line_ids, xyzm );
}
// #nocov end

inline SEXP sfc_multipoint(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& geometry_cols,
    Rcpp::String& multipoint_id,
    std::string xyzm
) {
  SEXP line_ids = df[ multipoint_id ];
  return sfc_multipoint( df, geometry_cols, line_ids, xyzm );
}

inline SEXP sfc_multipoint(
    Rcpp::DataFrame& df,
    Rcpp::IntegerVector& geometry_cols,
    int& multipoint_id,
    std::string xyzm
) {
  sfheaders::utils::column_exists( df, multipoint_id );
  SEXP line_ids = df[ multipoint_id ];
  return sfc_multipoint( df, geometry_cols, line_ids, xyzm );
}

inline SEXP sfc_multipoint(
    SEXP& x,
    Rcpp::IntegerVector& geometry_cols,
    int& multipoint_id,
    std::string xyzm
) {
  switch( TYPEOF( x ) ) {
  case INTSXP: {
    if( Rf_isMatrix( x ) ) {
    SEXP xc = Rcpp::clone( x );
    Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
    return sfc_multipoint( im, geometry_cols, multipoint_id, xyzm );
    // } else {
    // Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
    // return sfc_multipoint( iv, geometry_cols, multipoint_id );
  }
  }
  case REALSXP: {
    if( Rf_isMatrix( x ) ) {
    SEXP xc = Rcpp::clone( x );
    Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
    return sfc_multipoint( nm, geometry_cols, multipoint_id, xyzm );
    // } else {
    //   Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
    //   return sfc_multipoint( nv, geometry_cols, multipoint_id );
  }
  }
  case VECSXP: {
    if( Rf_inherits( x, "data.frame" ) ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
    return sfc_multipoint( df, geometry_cols, multipoint_id, xyzm );
  }
  }
  default: {
    Rcpp::stop("sfheaders - unsupported multipoint type");  // #nocov
  }
  }

  return Rcpp::List::create();

}

inline SEXP sfc_multipoint(
    SEXP& x,
    Rcpp::StringVector& geometry_cols,
    Rcpp::String& multipoint_id,
    std::string xyzm
) {
  switch( TYPEOF( x ) ) {
  case INTSXP: {
    // #nocov start
    if( Rf_isMatrix( x ) ) {
    SEXP xc = Rcpp::clone( x );
    Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
    return sfc_multipoint( im, geometry_cols, multipoint_id, xyzm );
    // } else {
    //   Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
    //   return sfc_multipoint( iv, geometry_cols, multipoint_id );
  }
  }
  case REALSXP: {
    if( Rf_isMatrix( x ) ) {
    SEXP xc = Rcpp::clone( x );
    Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
    return sfc_multipoint( nm, geometry_cols, multipoint_id, xyzm );
    // } else {
    //   Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
    //   return sfc_multipoint( nv, geometry_cols, multipoint_id );
  }
  // #nocov end
  }
  case VECSXP: {
    if( Rf_inherits( x, "data.frame" ) ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
    return sfc_multipoint( df, geometry_cols, multipoint_id, xyzm );
  }
  }
  default: {
    Rcpp::stop("sfheaders - unsupported multipoint type");  // #nocov
  }
  }

  return Rcpp::List::create();
}

// if an 'id' col is supplied, it means we have many multipoints
// multipoint_id & point_id
inline SEXP sfc_multipoint(
    SEXP& x,
    SEXP& geometry_cols,
    SEXP& multipoint_id,
    std::string xyzm
) {

  if( Rf_isNull( geometry_cols ) && Rf_isNull( multipoint_id ) ) {

    return sfc_multipoint( x, xyzm );

  } else if ( !Rf_isNull( geometry_cols ) && Rf_isNull( multipoint_id ) ) {

    // make the geometry cols all the other columns??
    return sfc_multipoint( x, geometry_cols, xyzm );

  } else if ( Rf_isNull( geometry_cols ) && !Rf_isNull( multipoint_id ) ) {

    SEXP other_cols = sfheaders::utils::other_columns( x, multipoint_id );
    sfheaders::utils::geometry_column_check( other_cols );

    return sfc_multipoint( x, other_cols, multipoint_id, xyzm );

  } else {
    // we have all the columns sorted, so we can now get their types, calcaulte ranges/bbox etc
    sfheaders::utils::geometry_column_check( geometry_cols );

    if ( TYPEOF( geometry_cols ) != TYPEOF( multipoint_id ) ) {
      Rcpp::stop("sfheaders - multipoint columns types are different");    // #nocov
    }

    switch( TYPEOF( geometry_cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv_geometry_cols = Rcpp::as< Rcpp::IntegerVector >( geometry_cols );
      Rcpp::IntegerVector iv_multipoint_id_col = Rcpp::as< Rcpp::IntegerVector >( multipoint_id );
      int i_multipoint_id_col = iv_multipoint_id_col[0];
      return sfc_multipoint( x, iv_geometry_cols, i_multipoint_id_col, xyzm );

    }
    case STRSXP: {
      Rcpp::StringVector sv_geometry_cols = Rcpp::as< Rcpp::StringVector >( geometry_cols );
      Rcpp::StringVector sv_multipoint_id_col = Rcpp::as< Rcpp::StringVector >( multipoint_id );
      Rcpp::String s_multipoint_id_col = sv_multipoint_id_col[0];
      return sfc_multipoint( x, sv_geometry_cols, s_multipoint_id_col, xyzm );
    }
    default: {
      Rcpp::stop("sfheaders - unsupported multipoint type");  // #nocov
    }
    }
  }

  return Rcpp::List::create(); // ??
}



} // sfc
} // sfheaders

#endif
