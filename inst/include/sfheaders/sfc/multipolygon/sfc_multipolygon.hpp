#ifndef R_SFHEADERS_SFC_MULTIPOLYGON_H
#define R_SFHEADERS_SFC_MULTIPOLYGON_H

#include <Rcpp.h>
#include "sfheaders/sfc/sfc_attributes.hpp"
#include "sfheaders/sfc/sfc_types.hpp"
#include "sfheaders/sfg/multipolygon/sfg_multipolygon.hpp"
#include "sfheaders/sfc/bbox.hpp"
#include "sfheaders/sfc/zm_range.hpp"
#include "sfheaders/shapes/shapes.hpp"

namespace sfheaders {
namespace sfc {

  // Requirs a list of sfg_MULTIPOLYGON, and the bbox / ranges
  // does not do any calculations; just makes the SFC structure
  inline SEXP sfc_multipolygon(
      Rcpp::List& sfc,
      Rcpp::NumericVector& bbox,
      Rcpp::NumericVector& z_range,
      Rcpp::NumericVector& m_range
  ) {
    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTIPOLYGON, bbox, z_range, m_range );
    return sfc;
  }

  // #nocov start
  inline SEXP sfc_multipolygon(
      Rcpp::IntegerMatrix& im,
      bool close = true
  ) {
    //
    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

    R_xlen_t n_col = im.ncol();

    Rcpp::List sfc( 1 );

    sfheaders::bbox::calculate_bbox( bbox, im );
    sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, im );

    Rcpp::List mp = sfheaders::sfg::sfg_multipolygon( im, close );

    sfc[0] = mp;
    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTIPOLYGON, bbox, z_range, m_range );
    return sfc;
  }


  inline SEXP sfc_multipolygon(
      Rcpp::NumericMatrix& nm,
      bool close = true
  ) {
    //
    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

    R_xlen_t n_col = nm.ncol();

    Rcpp::List sfc( 1 );

    sfheaders::bbox::calculate_bbox( bbox, nm );
    sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, nm );

    Rcpp::List mp = sfheaders::sfg::sfg_multipolygon( nm, close );

    sfc[0] = mp;
    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTIPOLYGON, bbox, z_range, m_range );
    return sfc;
  }

  inline SEXP sfc_multipolygon(
      Rcpp::DataFrame& df,
      bool close = true
  ) {

    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

    R_xlen_t n_col = df.ncol();

    Rcpp::List sfc( 1 );

    sfheaders::bbox::calculate_bbox( bbox, df );
    sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, df );

    Rcpp::List mp = sfheaders::sfg::sfg_multipolygon( df, close );

    sfc[0] = mp;
    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTIPOLYGON, bbox, z_range, m_range );
    return sfc;
  }

  inline SEXP sfc_multipolygon(
      Rcpp::IntegerVector& iv,
      bool close = true
  ) {
    int n_col = iv.size();
    Rcpp::IntegerMatrix im(1, n_col);
    im(0, Rcpp::_ ) = iv;
    return sfc_multipolygon( im, close );
  }

  inline SEXP sfc_multipolygon(
      Rcpp::NumericVector& nv,
      bool close = true
  ) {
    int n_col = nv.size();
    Rcpp::NumericMatrix nm(1, n_col);
    nm(0, Rcpp::_ ) = nv;
    return sfc_multipolygon( nm, close );
  }


  // inline SEXP sfc_multipolygon(
  //     Rcpp::List& lst
  // ) {
  //   // iterate each 'sfg' and assign 'sfg' attributes
  //
  //   Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
  //   Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
  //   Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();
  //
  //   std::string geom_type = "MULTIPOLYGON";
  //   std::unordered_set< std::string > geometry_types{ geom_type };
  //
  //   Rcpp::String epsg = NA_STRING;
  //   Rcpp::String proj4string = NA_STRING;
  //   int n_empty = 0;
  //   double precision = 0.0;
  //
  //   R_xlen_t n_multipolygons = lst.size();
  //
  //   Rcpp::List sfc( n_multipolygons );
  //
  //   R_xlen_t i, j, k;
  //
  //   for( i = 0; i < n_multipolygons; i++ ) {
  //     Rcpp::List sfgs = lst[i];
  //     R_xlen_t n_polygons = sfgs.size();
  //
  //     Rcpp::List pl( n_polygons );
  //
  //     for( j = 0; j < n_polygons; j++ ) {
  //
  //       Rcpp::List ls = sfgs[j];
  //       R_xlen_t n_linestrings = ls.size();
  //
  //       Rcpp::List l( n_linestrings );
  //
  //       for( k = 0; k < n_linestrings; k++ ) {
  //         SEXP this_linestring = ls[k];
  //
  //         switch( TYPEOF( this_linestring ) ) {
  //         case INTSXP: {
  //           if( !Rf_isMatrix( this_linestring ) ) {
  //           Rcpp::stop("sfheaders - expecting a matrix for polygons");
  //         } else {
  //           Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( this_linestring );
  //           sfheaders::bbox::calculate_bbox( bbox, im );
  //
  //           R_xlen_t n_col = im.ncol();
  //           if( n_col > 2 ) {
  //             sfheaders::zm::calculate_z_range( z_range, im );
  //             if( n_col > 3 ) {
  //               sfheaders::zm::calculate_m_range( m_range, im );
  //             }
  //           }
  //
  //           l[k] = im;
  //         }
  //         break;
  //         }
  //         case REALSXP: {
  //           if( !Rf_isMatrix( this_linestring ) ) {
  //           Rcpp::stop("sfheaders - expecting a matrix for polygons");
  //         } else {
  //           Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( this_linestring );
  //           sfheaders::bbox::calculate_bbox( bbox, nm );
  //
  //           R_xlen_t n_col = nm.ncol();
  //           if( n_col > 2 ) {
  //             sfheaders::zm::calculate_z_range( z_range, nm );
  //             if( n_col > 3 ) {
  //               sfheaders::zm::calculate_m_range( m_range, nm );
  //             }
  //           }
  //
  //           l[k] = nm;
  //         }
  //         break;
  //         }
  //         default: {
  //           Rcpp::stop("sfheaders - unknown multipolygon type");
  //         }
  //         }
  //       }
  //       pl[j] = ls;
  //     }
  //
  //     sfc[i] = sfheaders::sfg::sfg_multipolygon( pl );
  //
  //   }
  //   return sfheaders::sfc::create_sfc( sfc, geom_type, geometry_types, bbox, z_range, m_range, epsg, proj4string, n_empty, precision );
  // }


  // no subsetting to do; so just turn the object into a matrix;
  inline SEXP sfc_multipolygon(
      SEXP& x,
      bool close = true
  ) {
    // here there is no subsetting required;
    // we have to assume the columsn are in order x,y,(z,(m))
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return sfc_multipolygon( im, close );
    } else {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
      return sfc_multipolygon( iv, close );
    }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return sfc_multipolygon( nm, close );
    } else {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
      return sfc_multipolygon( nv, close );
    }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfc_multipolygon( df, close );
    }
    }
    default: {
      Rcpp::stop("sfheaders - unsupported multipolygon type");
    }
    }
    return Rcpp::List::create();
  }

  // no subsetting to do (except for columsn)
  inline SEXP sfc_multipolygon(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& geometry_cols,
      bool close = true
  ) {
    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

    sfheaders::bbox::calculate_bbox( bbox, im, geometry_cols );

    R_xlen_t n_col = im.ncol();
    sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, im, geometry_cols );

    Rcpp::List sfc( 1 );
    Rcpp::List sfg = sfheaders::sfg::sfg_multipolygon( im, geometry_cols, close );
    sfc[0] = sfg;
    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTIPOLYGON, bbox, z_range, m_range );
    return sfc;
  }

inline SEXP sfc_multipolygon(
    Rcpp::IntegerMatrix& im,
    Rcpp::StringVector& geometry_cols,
    bool close = true
) {

  Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );
  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
  Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
  Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

  R_xlen_t n_col = df.ncol();

  sfheaders::bbox::calculate_bbox( bbox, df, geometry_cols );
  sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, df, geometry_cols );

  Rcpp::List sfc( 1 );
  Rcpp::List sfg = sfheaders::sfg::sfg_multipolygon( df, geometry_cols, close );
  sfc[0] = sfg;
  sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTIPOLYGON, bbox, z_range, m_range );
  return sfc;
}

inline SEXP sfc_multipolygon(
    Rcpp::NumericMatrix& nm,
    Rcpp::IntegerVector& geometry_cols,
    bool close = true
) {
  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
  Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
  Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

  R_xlen_t n_col = nm.ncol();

  sfheaders::bbox::calculate_bbox( bbox, nm, geometry_cols );
  sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, nm, geometry_cols );

  Rcpp::List sfc( 1 );
  Rcpp::List sfg = sfheaders::sfg::sfg_multipolygon( nm, geometry_cols, close );
  sfc[0] = sfg;
  sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTIPOLYGON, bbox, z_range, m_range );
  return sfc;
}

inline SEXP sfc_multipolygon(
    Rcpp::NumericMatrix& nm,
    Rcpp::StringVector& geometry_cols,
    bool close = true
) {

  Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );
  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
  Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
  Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

  R_xlen_t n_col = df.ncol();

  sfheaders::bbox::calculate_bbox( bbox, df, geometry_cols );
  sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, df, geometry_cols );

  Rcpp::List sfc( 1 );
  Rcpp::List sfg = sfheaders::sfg::sfg_multipolygon( df, geometry_cols, close );
  sfc[0] = sfg;
  sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTIPOLYGON, bbox, z_range, m_range );
  return sfc;
}

inline SEXP sfc_multipolygon(
    Rcpp::DataFrame& df,
    Rcpp::IntegerVector& geometry_cols,
    bool close = true
) {
  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
  Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
  Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

  sfheaders::bbox::calculate_bbox( bbox, df, geometry_cols );

  R_xlen_t n_col = df.ncol();
  sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, df, geometry_cols );

  Rcpp::List sfc( 1 );
  Rcpp::List sfg = sfheaders::sfg::sfg_multipolygon( df, geometry_cols, close );
  sfc[0] = sfg;
  sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTIPOLYGON, bbox, z_range, m_range );
  return sfc;
}

inline SEXP sfc_multipolygon(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& geometry_cols,
    bool close = true
) {

  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
  Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
  Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

  sfheaders::bbox::calculate_bbox( bbox, df, geometry_cols );

  R_xlen_t n_col = df.ncol();
  sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, df, geometry_cols );

  Rcpp::List sfc( 1 );
  Rcpp::List sfg = sfheaders::sfg::sfg_multipolygon( df, geometry_cols, close );
  sfc[0] = sfg;
  sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTIPOLYGON, bbox, z_range, m_range );
  return sfc;
}

inline SEXP sfc_multipolygon(
    SEXP& x,
    Rcpp::StringVector& geometry_cols,
    bool close = true
) {
  switch( TYPEOF( x ) ) {
  case INTSXP: {
    if( Rf_isMatrix( x ) ) {
    Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
    return sfc_multipolygon( im, geometry_cols, close );
    // } else {
    //   Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
    //   return sfc_multipolygon( iv, geometry_cols );
  }
  }
  case REALSXP: {
    if( Rf_isMatrix( x ) ) {
    Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
    return sfc_multipolygon( nm, geometry_cols, close );
    // } else {
    //   Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
    //   return sfc_multipolygon( nv, geometry_cols );
  }
  }
  case VECSXP: {
    if( Rf_inherits( x, "data.frame" ) ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
    return sfc_multipolygon( df, geometry_cols, close );
  }
  }
  default: {
    Rcpp::stop("sfheaders - unsupported polygon type");
  }
  }
  return Rcpp::List::create();
}

inline SEXP sfc_multipolygon(
    SEXP& x,
    Rcpp::IntegerVector& geometry_cols,
    bool close = true
) {
  switch( TYPEOF( x ) ) {
  case INTSXP: {
    if( Rf_isMatrix( x ) ) {
    Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
    return sfc_multipolygon( im, geometry_cols, close );
    // } else {
    //   Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
    //   return sfc_multipolygon( iv, geometry_cols );
  }
  }
  case REALSXP: {
    if( Rf_isMatrix( x ) ) {
    Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
    return sfc_multipolygon( nm, geometry_cols, close );
    // } else {
    //   Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
    //   return sfc_multipolygon( nv, geometry_cols );
  }
  }
  case VECSXP: {
    if( Rf_inherits( x, "data.frame" ) ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
    return sfc_multipolygon( df, geometry_cols, close );
  }
  }
  default: {
    Rcpp::stop("sfheaders - unsupported polygon type");
  }
  }
  return Rcpp::List::create();
}

// no subsetting to do (except for columns)
inline SEXP sfc_multipolygon(
    SEXP& x,
    SEXP& geometry_cols,
    bool close = true
) {

  sfheaders::utils::geometry_column_check( geometry_cols );

  switch( TYPEOF( geometry_cols ) ) {
  case REALSXP: {}
  case INTSXP: {
    Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( geometry_cols );
    return sfc_multipolygon( x, iv, close );
  }
  case STRSXP: {
    Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( geometry_cols );
    return sfc_multipolygon( x, sv, close );
  }
  default: {
    Rcpp::stop("sfheaders - unknown column type");
  }
  }
  return Rcpp::List::create();
}
// #nocov end


// is the idea here to first get the vector of polygon_ids
// but keep the line_ids as a column reference
// then subset the df in teh outerloop by polygon_id
// then go in and get the sfg_multipolygon based on the line_ids?
inline SEXP sfc_multipolygon(
    Rcpp::DataFrame& df,
    Rcpp::IntegerVector& geometry_cols,
    SEXP& multipolygon_ids,
    int& polygon_id,
    int& linestring_id,
    bool close = true
) {
  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
  Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
  Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

  sfheaders::bbox::calculate_bbox( bbox, df, geometry_cols );

  R_xlen_t n_col = df.ncol();
  sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, df, geometry_cols );

  SEXP unique_multipolygon_ids = sfheaders::utils::get_sexp_unique( multipolygon_ids );
  Rcpp::IntegerMatrix multipolygon_positions = sfheaders::utils::id_positions( multipolygon_ids, unique_multipolygon_ids );

  R_xlen_t n_multipolygons = sfheaders::utils::get_sexp_length( unique_multipolygon_ids );
  R_xlen_t i;
  Rcpp::List sfc( n_multipolygons );

  int start;
  int end;
  Rcpp::StringVector df_names = df.names();

  for( i = 0; i < n_multipolygons; i++ ) {
    start = multipolygon_positions( i, 0 );
    end = multipolygon_positions( i, 1 );
    Rcpp::DataFrame df_subset = sfheaders::utils::subset_dataframe( df, df_names, start, end );
    sfc( i ) = sfheaders::sfg::sfg_multipolygon( df_subset, geometry_cols, polygon_id, linestring_id, close );
  }

  sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTIPOLYGON, bbox, z_range, m_range );
  return sfc;
}

inline SEXP sfc_multipolygon(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& geometry_cols,
    SEXP& multipolygon_ids,
    Rcpp::String& polygon_id,
    Rcpp::String& linestring_id,
    bool close = true
) {
  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
  Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
  Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

  sfheaders::bbox::calculate_bbox( bbox, df, geometry_cols );

  R_xlen_t n_col = df.ncol();
  sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, df, geometry_cols );

  SEXP unique_multipolygon_ids = sfheaders::utils::get_sexp_unique( multipolygon_ids );
  Rcpp::IntegerMatrix multipolygon_positions = sfheaders::utils::id_positions( multipolygon_ids, unique_multipolygon_ids );

  R_xlen_t n_multipolygons = sfheaders::utils::get_sexp_length( unique_multipolygon_ids );
  R_xlen_t i;
  Rcpp::List sfc( n_multipolygons );

  int start;
  int end;
  Rcpp::StringVector df_names = df.names();

  for( i = 0; i < n_multipolygons; i++ ) {
    start = multipolygon_positions( i, 0 );
    end = multipolygon_positions( i, 1 );
    Rcpp::DataFrame df_subset = sfheaders::utils::subset_dataframe( df, df_names, start, end );
    sfc( i ) = sfheaders::sfg::sfg_multipolygon( df_subset, geometry_cols, polygon_id, linestring_id, close );
  }

  sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTIPOLYGON, bbox, z_range, m_range );
  return sfc;
}

inline SEXP sfc_multipolygon(
    Rcpp::IntegerMatrix& im,
    Rcpp::IntegerVector& geometry_cols,
    Rcpp::IntegerVector& multipolygon_ids,
    int& polygon_id,
    int& linestring_id,
    bool close = true
) {
  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
  Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
  Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

  sfheaders::bbox::calculate_bbox( bbox, im, geometry_cols );

  R_xlen_t n_col = im.ncol();
  sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, im, geometry_cols );

  Rcpp::IntegerVector unique_multipolygon_ids = Rcpp::sort_unique( multipolygon_ids );
  Rcpp::IntegerMatrix multipolygon_positions = sfheaders::utils::id_positions( multipolygon_ids, unique_multipolygon_ids );

  R_xlen_t n_multipolygons = unique_multipolygon_ids.length();
  R_xlen_t i;
  Rcpp::List sfc( n_multipolygons );

  int start;
  int end;

  for( i = 0; i < n_multipolygons; i++ ) {
    start = multipolygon_positions( i, 0 );
    end = multipolygon_positions( i, 1 );
    Rcpp::IntegerMatrix im2 = im( Rcpp::Range(start, end), Rcpp::_ );
    sfc( i ) = sfheaders::sfg::sfg_multipolygon( im2, geometry_cols, polygon_id, linestring_id, close );
  }

  sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTIPOLYGON, bbox, z_range, m_range );
  return sfc;
}

inline SEXP sfc_multipolygon(
    Rcpp::NumericMatrix& nm,
    Rcpp::IntegerVector& geometry_cols,
    Rcpp::NumericVector& multipolygon_ids,
    int& polygon_id,
    int& linestring_id,
    bool close = true
) {
  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
  Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
  Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

  sfheaders::bbox::calculate_bbox( bbox, nm, geometry_cols );

  R_xlen_t n_col = nm.ncol();
  sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, nm, geometry_cols );

  Rcpp::NumericVector unique_multipolygon_ids = Rcpp::sort_unique( multipolygon_ids );
  Rcpp::IntegerMatrix multipolygon_positions = sfheaders::utils::id_positions( multipolygon_ids, unique_multipolygon_ids );

  R_xlen_t n_multipolygons = unique_multipolygon_ids.length();
  R_xlen_t i;
  Rcpp::List sfc( n_multipolygons );

  int start;
  int end;

  for( i = 0; i < n_multipolygons; i++ ) {
    start = multipolygon_positions( i, 0 );
    end = multipolygon_positions( i, 1 );
    Rcpp::NumericMatrix nm2 = nm( Rcpp::Range(start, end), Rcpp::_ );
    sfc( i ) = sfheaders::sfg::sfg_multipolygon( nm2, geometry_cols, polygon_id, linestring_id, close );
  }

  sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTIPOLYGON, bbox, z_range, m_range );
  return sfc;
}

inline SEXP sfc_multipolygon(
    Rcpp::IntegerMatrix& im,
    Rcpp::IntegerVector& geometry_cols,
    int& multipolygon_id,
    int& polygon_id,
    int& linestring_id,
    bool close = true
) {
  sfheaders::utils::column_exists( im, multipolygon_id );
  Rcpp::IntegerVector multipolygon_ids = im( Rcpp::_, multipolygon_id );
  return sfc_multipolygon( im, geometry_cols, multipolygon_ids, polygon_id, linestring_id, close );
}

inline SEXP sfc_multipolygon(
    Rcpp::NumericMatrix& nm,
    Rcpp::IntegerVector& geometry_cols,
    int& multipolygon_id,
    int& polygon_id,
    int& linestring_id,
    bool close = true
) {
  sfheaders::utils::column_exists( nm, multipolygon_id );
  Rcpp::NumericVector multipolygon_ids = nm( Rcpp::_, multipolygon_id );
  return sfc_multipolygon( nm, geometry_cols, multipolygon_ids, polygon_id, linestring_id, close );
}

inline SEXP sfc_multipolygon(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& geometry_cols,
    Rcpp::String& multipolygon_id,
    Rcpp::String& polygon_id,
    Rcpp::String& linestring_id,
    bool close = true
) {
  SEXP multipolygon_ids = df[ multipolygon_id ];
  return sfc_multipolygon( df, geometry_cols, multipolygon_ids, polygon_id, linestring_id, close );
}

inline SEXP sfc_multipolygon(
    Rcpp::DataFrame& df,
    Rcpp::IntegerVector& geometry_cols,
    int& multipolygon_id,
    int& polygon_id,
    int& linestring_id,
    bool close = true
) {
  sfheaders::utils::column_exists( df, multipolygon_id );
  SEXP multipolygon_ids = df[ multipolygon_id ];
  return sfc_multipolygon( df, geometry_cols, multipolygon_ids, polygon_id, linestring_id, close );
}

inline SEXP sfc_multipolygon(
    Rcpp::IntegerMatrix& im,
    Rcpp::StringVector& geometry_cols,
    Rcpp::String& multipolygon_id,
    Rcpp::String& polygon_id,
    Rcpp::String& linestring_id,
    bool close = true
) {
  Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );
  return sfc_multipolygon( df, geometry_cols, multipolygon_id, polygon_id, linestring_id, close );
}

inline SEXP sfc_multipolygon(
    Rcpp::NumericMatrix& nm,
    Rcpp::StringVector& geometry_cols,
    Rcpp::String& multipolygon_id,
    Rcpp::String& polygon_id,
    Rcpp::String& linestring_id,
    bool close = true
) {
  Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );
  return sfc_multipolygon( df, geometry_cols, multipolygon_id, polygon_id, linestring_id, close );
}

inline SEXP sfc_multipolygon(
    SEXP& x,
    Rcpp::IntegerVector& geometry_cols,
    int& multipolygon_id,
    int& polygon_id,
    int& linestring_id,
    bool close = true
) {
  switch( TYPEOF( x ) ) {
  case INTSXP: {
    if( Rf_isMatrix( x ) ) {
    Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
    return sfc_multipolygon( im, geometry_cols, multipolygon_id, polygon_id, linestring_id, close );
    // } else {
    // Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
    // return sfc_multipolygon( iv, geometry_cols, linestring_id );
  }
  }
  case REALSXP: {
    if( Rf_isMatrix( x ) ) {
    Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
    return sfc_multipolygon( nm, geometry_cols, multipolygon_id, polygon_id, linestring_id, close );
    // } else {
    //   Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
    //   return sfc_linestring( nv, geometry_cols, linestring_id );
  }
  }
  case VECSXP: {
    if( Rf_inherits( x, "data.frame" ) ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
    return sfc_multipolygon( df, geometry_cols, multipolygon_id, polygon_id, linestring_id, close );
  }
  }
  default: {
    Rcpp::stop("sfheaders - unsupported polygon type");    // #nocov
  }
  }
  return Rcpp::List::create();
}

inline SEXP sfc_multipolygon(
    SEXP& x,
    Rcpp::StringVector& geometry_cols,
    Rcpp::String& multipolygon_id,
    Rcpp::String& polygon_id,
    Rcpp::String& linestring_id,
    bool close = true
) {
  switch( TYPEOF( x ) ) {
  case INTSXP: {
    if( Rf_isMatrix( x ) ) {
    Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
    return sfc_multipolygon( im, geometry_cols, multipolygon_id, polygon_id, linestring_id, close );
    // } else {
    //   Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
    //   return sfc_multipolygon( iv, geometry_cols, linestring_id );
  }
  }
  case REALSXP: {
    if( Rf_isMatrix( x ) ) {
    Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
    return sfc_multipolygon( nm, geometry_cols, multipolygon_id, polygon_id, linestring_id, close );
    // } else {
    //   Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
    //   return sfc_multipolygon( nv, geometry_cols, linestring_id );
  }
  }
  case VECSXP: {
    if( Rf_inherits( x, "data.frame" ) ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
    return sfc_multipolygon( df, geometry_cols, multipolygon_id, polygon_id, linestring_id, close );
  }
  }
  default: {
    Rcpp::stop("sfheaders - unsupported polygon type");  // #nocov
  }
  }

  return Rcpp::List::create();
}


  // if an 'id' col is supplied, it means we have many polygons
  // linestring_id & point_id
  inline SEXP sfc_multipolygon(
      SEXP& x,
      SEXP& geometry_cols,
      SEXP& multipolygon_id,
      SEXP& polygon_id,
      SEXP& linestring_id,
      bool close = true
  ) {

    if( Rf_isNull( geometry_cols ) ) {
      // make this all the other columns, then send back in
      SEXP geometry_cols2 = sfheaders::utils::other_columns( x, multipolygon_id, polygon_id, linestring_id );
      return sfc_multipolygon( x, geometry_cols2, multipolygon_id, polygon_id, linestring_id, close );
    }

    // From now on, geometry_cols will never be null

    if( Rf_isNull( linestring_id ) &&
        Rf_isNull( polygon_id ) &&
        Rf_isNull( multipolygon_id) ) {
      return sfc_multipolygon( x, geometry_cols, close );
    }

    // if ( !Rf_isNull( geometry_cols ) &&
    //      Rf_isNull( linestring_id ) &&
    //      Rf_isNull( polygon_id ) &&
    //      Rf_isNull( multipolygon_id )
    // ) {
    //   return sfc_multipolygon( x, geometry_cols );
    // }

    if ( !Rf_isNull( linestring_id ) &&
         Rf_isNull( polygon_id ) &&
         Rf_isNull( multipolygon_id )
    ) {
      // in this case, all other columns are geometry columns
      // and the whole object is a multipolygon
      // of one internal polygon
      // made up of one or many internal rings
      //SEXP geometry_cols2 = sfheaders::utils::other_columns( x, linestring_id );

      Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
      Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
      Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

      sfheaders::bbox::calculate_bbox( bbox, x, geometry_cols );

      Rcpp::List sfc(1);

      // need to calcualte zm ranges
      // but here we don't know the x object type...
      switch( TYPEOF( x ) ) {
      case INTSXP: {
        if( Rf_isMatrix( x ) ) {
        Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
        R_xlen_t n_col = im.ncol();
        sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, im, geometry_cols );
        break;
      }
      case REALSXP: {
        if( Rf_isMatrix( x ) ) {
        Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
        R_xlen_t n_col = nm.ncol();
        sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, nm, geometry_cols );
        break;
      }
      }
      case VECSXP: {
        if( Rf_inherits( x, "data.frame" ) ) {
        Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
        R_xlen_t n_col = df.ncol();
        sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, df, geometry_cols );
        break;
      }
      }
      default: {
        Rcpp::stop("sfheaders - unsupported multipolygon type");   // #nocov
      }
      }
      }

      sfc[0] = sfheaders::sfg::sfg_multipolygon( x, geometry_cols, polygon_id, linestring_id, close );
      sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTIPOLYGON, bbox, z_range, m_range );
      return sfc;

      //return sfc_multipolygon( x, geometry_cols );
    }

    if ( Rf_isNull( linestring_id ) &&
         !Rf_isNull( polygon_id ) &&
         Rf_isNull( multipolygon_id )
    ) {
      // in this case, all other columns are geometry columns
      // and the whole object is a multipolygon
      // of one or more internal polygons,
      // each made of a single ring
      SEXP linestring_id2 = polygon_id;
      return sfc_multipolygon( x, geometry_cols, multipolygon_id, polygon_id, linestring_id2, close );
    }

    if ( Rf_isNull( linestring_id ) &&
         Rf_isNull( polygon_id ) &&
         !Rf_isNull( multipolygon_id )
    ) {
      // in this case, all other columns are geometry columns
      // and the whole object is one or many multipolygons
      // made of of one polygon each, in turn made up
      // of a single ring
      SEXP polygon_id2 = multipolygon_id;
      SEXP linestring_id2 = multipolygon_id;
      return sfc_multipolygon( x, geometry_cols, multipolygon_id, polygon_id2, linestring_id2, close );
    }

    if (
      !Rf_isNull( linestring_id ) &&
      !Rf_isNull( polygon_id ) &&
      Rf_isNull( multipolygon_id )
    ) {
      Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
      Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
      Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

      sfheaders::bbox::calculate_bbox( bbox, x, geometry_cols );

      Rcpp::List sfc(1);

      switch( TYPEOF( x ) ) {
      case INTSXP: {
        if( Rf_isMatrix( x ) ) {
        Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
        R_xlen_t n_col = im.ncol();
        sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, im, geometry_cols );
        break;
      }
      case REALSXP: {
        if( Rf_isMatrix( x ) ) {
        Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
        R_xlen_t n_col = nm.ncol();
        sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, nm, geometry_cols );
        break;
      }
      }
      case VECSXP: {
        if( Rf_inherits( x, "data.frame" ) ) {
        Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
        R_xlen_t n_col = df.ncol();
        sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, df, geometry_cols );
        break;
      }
      }
      default: {
        Rcpp::stop("sfheaders - unsupported multipolygon type");  // #nocov
      }
      }
      }

      sfc[0] = sfheaders::sfg::sfg_multipolygon( x, geometry_cols, polygon_id, linestring_id, close );
      sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTIPOLYGON, bbox, z_range, m_range );
      return sfc;
    }

    if (
      !Rf_isNull( linestring_id ) &&
      Rf_isNull( polygon_id ) &&
      !Rf_isNull( multipolygon_id )
    ) {
      SEXP polygon_id2 = multipolygon_id;
      return sfc_multipolygon( x, geometry_cols, multipolygon_id, polygon_id2, linestring_id, close );
    }

    if (
      Rf_isNull( linestring_id ) &&
      !Rf_isNull( polygon_id ) &&
      !Rf_isNull( multipolygon_id )
    ) {
      SEXP linestring_id2 = polygon_id;
      return sfc_multipolygon( x, geometry_cols, multipolygon_id, polygon_id, linestring_id2, close );
    }


    if( !Rf_isNull( multipolygon_id ) &&
        !Rf_isNull( polygon_id ) &&
        !Rf_isNull( linestring_id )
    ) {

      sfheaders::utils::geometry_column_check( geometry_cols );

      if ( TYPEOF( geometry_cols ) != TYPEOF( linestring_id ) ||
           TYPEOF( geometry_cols ) != TYPEOF( polygon_id ) ||
           TYPEOF( geometry_cols ) != TYPEOF( multipolygon_id ) ) {
        Rcpp::stop("sfheaders - multipolygon columns types are different");  // #nocov
      }

      switch( TYPEOF( geometry_cols ) ) {
      case REALSXP: {}
      case INTSXP: {
        Rcpp::IntegerVector iv_geometry_cols = Rcpp::as< Rcpp::IntegerVector >( geometry_cols );
        Rcpp::IntegerVector iv_multipolygon_id_col = Rcpp::as< Rcpp::IntegerVector >( multipolygon_id );
        Rcpp::IntegerVector iv_polygon_id_col = Rcpp::as< Rcpp::IntegerVector >( polygon_id );
        Rcpp::IntegerVector iv_linestring_id_col = Rcpp::as< Rcpp::IntegerVector >( linestring_id );
        int i_multipolygon_id_col = iv_multipolygon_id_col[0];
        int i_polygon_id_col = iv_polygon_id_col[0];
        int i_linestring_id_col = iv_linestring_id_col[0];
        return sfc_multipolygon( x, iv_geometry_cols, i_multipolygon_id_col, i_polygon_id_col, i_linestring_id_col, close );

      }
      case STRSXP: {
        Rcpp::StringVector sv_geometry_cols = Rcpp::as< Rcpp::StringVector >( geometry_cols );
        Rcpp::StringVector sv_multipolygon_id_col = Rcpp::as< Rcpp::StringVector >( multipolygon_id );
        Rcpp::StringVector sv_polygon_id_col = Rcpp::as< Rcpp::StringVector >( polygon_id );
        Rcpp::StringVector sv_linestring_id_col = Rcpp::as< Rcpp::StringVector >( linestring_id );
        Rcpp::String s_multipolygon_id_col = sv_multipolygon_id_col[0];
        Rcpp::String s_polygon_id_col = sv_polygon_id_col[0];
        Rcpp::String s_linestring_id_col = sv_linestring_id_col[0];
        return sfc_multipolygon( x, sv_geometry_cols, s_multipolygon_id_col, s_polygon_id_col, s_linestring_id_col, close );
      }
      default: {
        Rcpp::stop("sfheaders - unsupported polygon type");  // #nocov
      }
      }
    }

    Rcpp::stop("sfheaders - multipolygon case not yet implemented");  // #nocov
    return Rcpp::List::create(); // ??
  }

} // sfc
} // sfheaders

#endif
