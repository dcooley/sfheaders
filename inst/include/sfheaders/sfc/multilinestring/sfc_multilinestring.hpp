#ifndef R_SFHEADERS_SFC_MULTILINESTRING_H
#define R_SFHEADERS_SFC_MULTILINESTRING_H

#include <Rcpp.h>
#include "sfheaders/sfc/sfc_attributes.hpp"
#include "sfheaders/sfc/sfc_types.hpp"
#include "sfheaders/sfg/multilinestring/sfg_multilinestring.hpp"
#include "sfheaders/sfc/bbox.hpp"
#include "sfheaders/sfc/zm_range.hpp"
#include "sfheaders/shapes/shapes.hpp"

namespace sfheaders {
namespace sfc {

  // Requirs a list of sfg_MULTILINESTRINGs, and the bbox / ranges
  // does not do any calculations; just makes the SFC structure
  inline SEXP sfc_multilinestring(
      Rcpp::List& sfc,
      Rcpp::NumericVector& bbox,
      Rcpp::NumericVector& z_range,
      Rcpp::NumericVector& m_range
  ) {
    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTILINESTRING, bbox, z_range, m_range );
    return sfc;
  }

  // #nocov start
  inline SEXP sfc_multilinestring(
      Rcpp::IntegerMatrix& im
  ) {
    //
    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

    R_xlen_t n_col = im.ncol();

    Rcpp::List sfc( 1 );

    sfheaders::bbox::calculate_bbox( bbox, im );
    sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, im );

    Rcpp::List mp = sfheaders::sfg::sfg_multilinestring( im );

    sfc[0] = mp;
    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTILINESTRING, bbox, z_range, m_range );
    return sfc;
  }


  inline SEXP sfc_multilinestring(
      Rcpp::NumericMatrix& nm
  ) {
    //
    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

    R_xlen_t n_col = nm.ncol();

    Rcpp::List sfc( 1 );

    sfheaders::bbox::calculate_bbox( bbox, nm );
    sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, nm );

    Rcpp::List mp = sfheaders::sfg::sfg_multilinestring( nm );

    sfc[0] = mp;
    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTILINESTRING, bbox, z_range, m_range );
    return sfc;

  }

  inline SEXP sfc_multilinestring(
      Rcpp::DataFrame& df
  ) {

    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

    R_xlen_t n_col = df.ncol();

    Rcpp::List sfc( 1 );

    sfheaders::bbox::calculate_bbox( bbox, df );
    sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, df );

    Rcpp::List mp = sfheaders::sfg::sfg_multilinestring( df );

    sfc[0] = mp;
    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTILINESTRING, bbox, z_range, m_range );
    return sfc;
  }


  inline SEXP sfc_multilinestring(
      Rcpp::IntegerVector& iv
  ) {
    int n_col = iv.size();
    Rcpp::IntegerMatrix im(1, n_col);
    im(0, Rcpp::_ ) = iv;
    return sfc_multilinestring( im );
  }

  inline SEXP sfc_multilinestring(
      Rcpp::NumericVector& nv
  ) {
    int n_col = nv.size();
    Rcpp::NumericMatrix nm(1, n_col);
    nm(0, Rcpp::_ ) = nv;
    return sfc_multilinestring( nm );
  }

// inline SEXP sfc_multilinestring(
//     Rcpp::List& lst
// ) {
//   // iterate each 'sfg' and assign 'sfg' attributes
//
//   Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
//   Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
//   Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();
//
//   std::string geom_type = "POLYGON";
//   std::unordered_set< std::string > geometry_types{ geom_type };
//
//   Rcpp::String epsg = NA_STRING;
//   Rcpp::String proj4string = NA_STRING;
//   int n_empty = 0;
//   double precision = 0.0;
//
//   R_xlen_t n_multilinestrings = lst.size();
//   Rcpp::List sfc( n_multilinestrings );
//
//   R_xlen_t i, j;
//
//   for( i = 0; i < n_multilinestrings; i++ ) {
//     Rcpp::List sfgs = lst[i];
//     R_xlen_t n_linestrings = sfgs.size();
//
//     Rcpp::List ml( n_linestrings );
//
//     for( j = 0; j < n_linestrings; j++ ) {
//
//       SEXP this_linestring = sfgs[j];
//
//       switch( TYPEOF( this_linestring ) ) {
//       case INTSXP: {
//         if( !Rf_isMatrix( this_linestring ) ) {
//         Rcpp::stop("sfheaders - expecting a matrix for multilinestrings");
//       } else {
//         Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( this_linestring );
//         sfheaders::bbox::calculate_bbox( bbox, im );
//
//         R_xlen_t n_col = im.ncol();
//         if( n_col > 2 ) {
//           sfheaders::zm::calculate_z_range( z_range, im );
//           if( n_col > 3 ) {
//             sfheaders::zm::calculate_m_range( m_range, im );
//           }
//         }
//
//         ml[j] = im;
//       }
//       break;
//       }
//       case REALSXP: {
//         if( !Rf_isMatrix( this_linestring ) ) {
//         Rcpp::stop("sfheaders - expecting a matrix for multilinestrings");
//       } else {
//         Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( this_linestring );
//         sfheaders::bbox::calculate_bbox( bbox, nm );
//
//         R_xlen_t n_col = nm.ncol();
//         if( n_col > 2 ) {
//           sfheaders::zm::calculate_z_range( z_range, nm );
//           if( n_col > 3 ) {
//             sfheaders::zm::calculate_m_range( m_range, nm );
//           }
//         }
//
//         ml[j] = nm;
//       }
//       break;
//       }
//       default: {
//         Rcpp::stop("sfheaders - unknown multilinestring type");
//       }
//       }
//
//     }
//     sfc[i] = sfheaders::sfg::sfg_multilinestring( ml );
//
//   }
//   return sfheaders::sfc::create_sfc( sfc, geom_type, geometry_types, bbox, z_range, m_range, epsg, proj4string, n_empty, precision );
//
// }

  // no subsetting to do; so just turn the object into a matrix;
  inline SEXP sfc_multilinestring(
      SEXP& x
  ) {
    // here there is no subsetting required;
    // we have to assume the columsn are in order x,y,(z,(m))
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return sfc_multilinestring( im );
    } else {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
      return sfc_multilinestring( iv );
    }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return sfc_multilinestring( nm );
    } else {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
      return sfc_multilinestring( nv );
    }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfc_multilinestring( df );
    }
    }
    default: {
      Rcpp::stop("sfheaders - unsupported multilinestring type");
    }
    }
    return Rcpp::List::create();
  }

  inline SEXP sfc_multilinestring(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& geometry_cols
  ) {
    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

    sfheaders::bbox::calculate_bbox( bbox, im, geometry_cols );

    R_xlen_t n_col = im.ncol();
    sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, im, geometry_cols );

    Rcpp::List sfc( 1 );
    Rcpp::List sfg = sfheaders::sfg::sfg_multilinestring( im, geometry_cols );
    sfc[0] = sfg;
    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTILINESTRING, bbox, z_range, m_range );
    return sfc;
  }

  inline SEXP sfc_multilinestring(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& geometry_cols
  ) {

    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );
    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

    R_xlen_t n_col = df.ncol();

    sfheaders::bbox::calculate_bbox( bbox, df, geometry_cols );
    sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, df, geometry_cols );

    Rcpp::List sfc( 1 );
    Rcpp::List sfg = sfheaders::sfg::sfg_multilinestring( df, geometry_cols );
    sfc[0] = sfg;
    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTILINESTRING, bbox, z_range, m_range );
    return sfc;
  }

  inline SEXP sfc_multilinestring(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& geometry_cols
  ) {
    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

    R_xlen_t n_col = nm.ncol();

    sfheaders::bbox::calculate_bbox( bbox, nm, geometry_cols );
    sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, nm, geometry_cols );

    Rcpp::List sfc( 1 );
    Rcpp::List sfg = sfheaders::sfg::sfg_multilinestring( nm, geometry_cols );
    sfc[0] = sfg;
    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTILINESTRING, bbox, z_range, m_range );
    return sfc;
  }

  inline SEXP sfc_multilinestring(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& geometry_cols
  ) {

    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );
    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

    R_xlen_t n_col = df.ncol();

    sfheaders::bbox::calculate_bbox( bbox, df, geometry_cols );
    sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, df, geometry_cols );

    Rcpp::List sfc( 1 );
    Rcpp::List sfg = sfheaders::sfg::sfg_multilinestring( df, geometry_cols );
    sfc[0] = sfg;
    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTILINESTRING, bbox, z_range, m_range );
    return sfc;
  }

  inline SEXP sfc_multilinestring(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& geometry_cols
  ) {
    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

    sfheaders::bbox::calculate_bbox( bbox, df, geometry_cols );

    R_xlen_t n_col = df.ncol();
    sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, df, geometry_cols );

    Rcpp::List sfc( 1 );
    Rcpp::List sfg = sfheaders::sfg::sfg_multilinestring( df, geometry_cols );
    sfc[0] = sfg;
    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTILINESTRING, bbox, z_range, m_range );
    return sfc;
  }

  inline SEXP sfc_multilinestring(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& geometry_cols
  ) {

    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

    sfheaders::bbox::calculate_bbox( bbox, df, geometry_cols );

    R_xlen_t n_col = df.ncol();
    sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, df, geometry_cols );

    Rcpp::List sfc( 1 );
    Rcpp::List sfg = sfheaders::sfg::sfg_multilinestring( df, geometry_cols );
    sfc[0] = sfg;
    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTILINESTRING, bbox, z_range, m_range );
    return sfc;
  }

  inline SEXP sfc_multilinestring(
      SEXP& x,
      Rcpp::StringVector& geometry_cols
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return sfc_multilinestring( im, geometry_cols );
      // } else {
      //   Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
      //   return sfc_multilinestring( iv, geometry_cols );
    }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return sfc_multilinestring( nm, geometry_cols );
      // } else {
      //   Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
      //   return sfc_multilinestring( nv, geometry_cols );
    }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfc_multilinestring( df, geometry_cols );
    }
    }
    default: {
      Rcpp::stop("sfheaders - unsupported multilinestring type");
    }
    }
    return Rcpp::List::create();
  }


  inline SEXP sfc_multilinestring(
      SEXP& x,
      Rcpp::IntegerVector& geometry_cols
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return sfc_multilinestring( im, geometry_cols );
      // } else {
      //   Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
      //   return sfc_multilinestring( iv, geometry_cols );
    }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return sfc_multilinestring( nm, geometry_cols );
      // } else {
      //   Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
      //   return sfc_multilinestring( nv, geometry_cols );
    }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfc_multilinestring( df, geometry_cols );
    }
    }
    default: {
      Rcpp::stop("sfheaders - unsupported multilinestring type");
    }
    }
    return Rcpp::List::create();
  }

  // no subsetting to do (except for columns)
  inline SEXP sfc_multilinestring(
      SEXP& x,
      SEXP& geometry_cols
  ) {
    sfheaders::utils::geometry_column_check( geometry_cols );

    switch( TYPEOF( geometry_cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( geometry_cols );
      return sfc_multilinestring( x, iv );
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( geometry_cols );
      return sfc_multilinestring( x, sv );
    }
    default: {
      Rcpp::stop("sfheaders - unknown column type");
    }
    }
    return Rcpp::List::create();
  }

// #nocov end

// Must have both multilinestring_id and linestring_id
// so the functions can be overloaded properly
// otherwise there will be ambiguous functions
// inline SEXP sfc_multilinestring(
//     SEXP& x,
//     SEXP& geometry_cols,
//     SEXP& multilinestring_id
// ) {
//
// }

  inline SEXP sfc_multilinestring(
    Rcpp::DataFrame& df,
    Rcpp::IntegerVector& geometry_cols,
    int& linestring_id,
    Rcpp::IntegerMatrix& multilinestring_positions
  ) {

    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

    sfheaders::bbox::calculate_bbox( bbox, df, geometry_cols );

    R_xlen_t n_col = df.ncol();
    sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, df, geometry_cols );

    R_xlen_t n_multilinestrings = multilinestring_positions.nrow();

    R_xlen_t i;
    Rcpp::List sfc( n_multilinestrings );

    int start;
    int end;
    Rcpp::StringVector df_names = df.names();

    for( i = 0; i < n_multilinestrings; i++ ) {
      start = multilinestring_positions( i, 0 );
      end = multilinestring_positions( i, 1 );
      Rcpp::DataFrame df_subset = sfheaders::utils::subset_dataframe( df, df_names, start, end );
      sfc( i ) = sfheaders::sfg::sfg_multilinestring( df_subset, geometry_cols, linestring_id );
    }

    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTILINESTRING, bbox, z_range, m_range );
    return sfc;
  }

  inline SEXP sfc_multilinestring(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& geometry_cols,
      SEXP& multilinestring_ids,
      int& linestring_id
  ) {
    Rcpp::IntegerMatrix multilinestring_positions = sfheaders::utils::id_positions( multilinestring_ids );
    return sfc_multilinestring( df, geometry_cols, linestring_id, multilinestring_positions );
  }

  inline SEXP sfc_multilinestring(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& geometry_cols,
    Rcpp::String& linestring_id,
    Rcpp::IntegerMatrix& multilinestring_positions
  ) {
    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

    sfheaders::bbox::calculate_bbox( bbox, df, geometry_cols );

    R_xlen_t n_col = df.ncol();
    sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, df, geometry_cols );

    R_xlen_t n_multilinestrings = multilinestring_positions.nrow();

    R_xlen_t i;
    Rcpp::List sfc( n_multilinestrings );

    int start;
    int end;
    Rcpp::StringVector df_names = df.names();

    for( i = 0; i < n_multilinestrings; i++ ) {
      start = multilinestring_positions( i, 0 );
      end = multilinestring_positions( i, 1 );
      Rcpp::DataFrame df_subset = sfheaders::utils::subset_dataframe( df, df_names, start, end );
      sfc( i ) = sfheaders::sfg::sfg_multilinestring( df_subset, geometry_cols, linestring_id );
    }

    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTILINESTRING, bbox, z_range, m_range );
    return sfc;
  }

  inline SEXP sfc_multilinestring(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& geometry_cols,
      SEXP& multilinestring_ids,  // can be int, double, string, ...
      Rcpp::String& linestring_id
  ) {
    Rcpp::IntegerMatrix multilinestring_positions = sfheaders::utils::id_positions( multilinestring_ids );
    return sfc_multilinestring(df, geometry_cols, linestring_id, multilinestring_positions );
  }

  inline SEXP sfc_multilinestring(
    Rcpp::IntegerMatrix& im,
    Rcpp::IntegerVector& geometry_cols,
    int& linestring_id,
    Rcpp::IntegerMatrix& multilinestring_positions
  ) {
    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

    sfheaders::bbox::calculate_bbox( bbox, im, geometry_cols );

    R_xlen_t n_col = im.ncol();
    sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, im, geometry_cols );


    R_xlen_t n_multilinestrings = multilinestring_positions.nrow();
    R_xlen_t i;
    Rcpp::List sfc( n_multilinestrings );

    int start;
    int end;

    for( i = 0; i < n_multilinestrings; i++ ) {
      start = multilinestring_positions( i, 0 );
      end = multilinestring_positions( i, 1 );
      Rcpp::IntegerMatrix im2 = im( Rcpp::Range(start, end), Rcpp::_ );
      sfc( i ) = sfheaders::sfg::sfg_multilinestring( im2, geometry_cols, linestring_id );
    }

    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTILINESTRING, bbox, z_range, m_range );
    return sfc;
  }

  inline SEXP sfc_multilinestring(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& geometry_cols,
      Rcpp::IntegerVector& multilinestring_ids,
      int& linestring_id
  ) {
    Rcpp::IntegerMatrix multilinestring_positions = sfheaders::utils::id_positions( multilinestring_ids );
    return sfc_multilinestring( im, geometry_cols, linestring_id, multilinestring_positions );
  }

  inline SEXP sfc_multilinestring(
    Rcpp::NumericMatrix& nm,
    Rcpp::IntegerVector& geometry_cols,
    int& linestring_id,
    Rcpp::IntegerMatrix& multilinestring_positions
  ) {
    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

    sfheaders::bbox::calculate_bbox( bbox, nm, geometry_cols );

    R_xlen_t n_col = nm.ncol();
    sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, nm, geometry_cols );


    R_xlen_t n_multilinestrings = multilinestring_positions.nrow();
    R_xlen_t i;
    Rcpp::List sfc( n_multilinestrings );

    int start;
    int end;

    for( i = 0; i < n_multilinestrings; i++ ) {
      start = multilinestring_positions( i, 0 );
      end = multilinestring_positions( i, 1 );
      Rcpp::NumericMatrix nm2 = nm( Rcpp::Range(start, end), Rcpp::_ );
      sfc( i ) = sfheaders::sfg::sfg_multilinestring( nm2, geometry_cols, linestring_id );
    }

    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTILINESTRING, bbox, z_range, m_range );
    return sfc;
  }

  inline SEXP sfc_multilinestring(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& geometry_cols,
      Rcpp::NumericVector& multilinestring_ids,
      int& linestring_id
  ) {
    Rcpp::IntegerMatrix multilinestring_positions = sfheaders::utils::id_positions( multilinestring_ids );
    return sfc_multilinestring( nm, geometry_cols, linestring_id, multilinestring_positions );
  }

  inline SEXP sfc_multilinestring(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& geometry_cols,
      int& multilinestring_id,
      int& linestring_id
  ) {
    sfheaders::utils::column_exists( im, multilinestring_id );
    Rcpp::IntegerVector multilinestring_ids = im( Rcpp::_, multilinestring_id );
    return sfc_multilinestring( im, geometry_cols, multilinestring_ids, linestring_id );
  }

  inline SEXP sfc_multilinestring(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& geometry_cols,
      int& multilinestring_id,
      int& linestring_id
  ) {
    sfheaders::utils::column_exists( nm, multilinestring_id );
    Rcpp::NumericVector multilinestring_ids = nm( Rcpp::_, multilinestring_id );
    return sfc_multilinestring( nm, geometry_cols, multilinestring_ids, linestring_id );
  }

  inline SEXP sfc_multilinestring(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& geometry_cols,
      Rcpp::String& multilinestring_id,
      Rcpp::String& linestring_id
  ) {
    SEXP multilinestring_ids = df[ multilinestring_id ];
    return sfc_multilinestring( df, geometry_cols, multilinestring_ids, linestring_id );
  }

  inline SEXP sfc_multilinestring(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& geometry_cols,
      int& multilinestring_id,
      int& linestring_id
  ) {
    sfheaders::utils::column_exists( df, multilinestring_id );
    SEXP multilinestring_ids = df[ multilinestring_id ];
    return sfc_multilinestring( df, geometry_cols, multilinestring_ids, linestring_id );
  }

  inline SEXP sfc_multilinestring(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& geometry_cols,
      Rcpp::String& multilinestring_id,
      Rcpp::String& linestring_id
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );
    return sfc_multilinestring( df, geometry_cols, multilinestring_id, linestring_id );
  }

  inline SEXP sfc_multilinestring(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& geometry_cols,
      Rcpp::String& multilinestring_id,
      Rcpp::String& linestring_id
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );
    return sfc_multilinestring( df, geometry_cols, multilinestring_id, linestring_id );
  }

  inline SEXP sfc_multilinestring(
      SEXP& x,
      Rcpp::IntegerVector& geometry_cols,
      int& multilinestring_id,
      int& linestring_id
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return sfc_multilinestring( im, geometry_cols, multilinestring_id, linestring_id );
      // } else {
      // Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
      // return sfc_multilinestring( iv, geometry_cols, linestring_id );
    }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return sfc_multilinestring( nm, geometry_cols, multilinestring_id, linestring_id );
      // } else {
      //   Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
      //   return sfc_linestring( nv, geometry_cols, linestring_id );
    }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfc_multilinestring( df, geometry_cols, multilinestring_id, linestring_id );
    }
    }
    default: {
      Rcpp::stop("sfheaders - unsupported multilinestring type");  // #nocov
    }
    }
    return Rcpp::List::create();
  }

  inline SEXP sfc_multilinestring(
      SEXP& x,
      Rcpp::StringVector& geometry_cols,
      Rcpp::String& multilinestring_id,
      Rcpp::String& linestring_id
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return sfc_multilinestring( im, geometry_cols, multilinestring_id, linestring_id );
      // } else {
      //   Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
      //   return sfc_multilinestring( iv, geometry_cols, linestring_id );
    }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return sfc_multilinestring( nm, geometry_cols, multilinestring_id, linestring_id );
      // } else {
      //   Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
      //   return sfc_multilinestring( nv, geometry_cols, linestring_id );
    }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfc_multilinestring( df, geometry_cols, multilinestring_id, linestring_id );
    }
    }
    default: {
      Rcpp::stop("sfheaders - unsupported multilinestring type");  // #nocov
    }
    }

    return Rcpp::List::create();
  }


  inline SEXP sfc_multilinestring(
      SEXP& x,
      SEXP& geometry_cols,
      SEXP& multilinestring_id,
      SEXP& linestring_id
  ) {

    if( Rf_isNull( geometry_cols ) ) {
      // make this all the other columns, then send back in
      SEXP geometry_cols2 = sfheaders::utils::other_columns( x, multilinestring_id, linestring_id );
      return sfc_multilinestring( x, geometry_cols2, multilinestring_id, linestring_id );
    }

    // From now on, geometry_cols will never be null

    if( Rf_isNull( linestring_id ) &&
        Rf_isNull( multilinestring_id ) ) {
      return sfc_multilinestring( x, geometry_cols );
    }
    //
    // // JUST multilinestring_id == each multilinestring is just one line
    // // JSUT linestring_id == they are all the same multilinestring_id
    //
    if ( Rf_isNull( multilinestring_id ) &&
         !Rf_isNull( linestring_id )
    ) {
      // linestring is provided
      // so they are all the same POLYGON

      // whatever x is, the linestring_id col is the ids of lines
      // all the other columns are geometry columns
      // so we have a matrix / data.frame, which will all become one multilinestring
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
        Rcpp::stop("sfheaders - unsupported multilinestring type");  // #nocov
      }
      }

      sfc[0] = sfheaders::sfg::sfg_multilinestring( x, geometry_cols, linestring_id );
      sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_MULTILINESTRING, bbox, z_range, m_range );
      return sfc;
    }

    if ( !Rf_isNull( multilinestring_id ) &&
         Rf_isNull( linestring_id )
    ) {
      // multilinestring is provided, so there is only one line per multilinestring

      // and given each multilinestring only has one line, can we simply set the linestring_id to be the
      // same as the multilinestring_id column; will taht work??
      SEXP linestring_id2 = multilinestring_id;
      return sfc_multilinestring( x, geometry_cols, multilinestring_id, linestring_id2 );
    }

    // if( !Rf_isNull( linestring_id ) &&
    //     !Rf_isNull( multilinestring_id )
    //     ) {
    //   return sfc_multilinestring( x, geometry_cols, multilinestring_id, linestring_id );
    // }

    // if( !Rf_isNull( geometry_cols ) &&
    //     !Rf_isNull( multilinestring_id ) &&
    //     Rf_isNull( linestring_id )
    //       ) {
    //
    //   // each multilinestring only has one line
    //   SEXP linestring_id2 = multilinestring_id;
    //   return sfc_multilinestring( x, geometry_cols, multilinestring_id, linestring_id2 );
    // }

    if( !Rf_isNull( multilinestring_id ) &&
        !Rf_isNull( linestring_id )
    ) {

      sfheaders::utils::geometry_column_check( geometry_cols );

      if ( TYPEOF( geometry_cols ) != TYPEOF( linestring_id ) ||
           TYPEOF( geometry_cols ) != TYPEOF( multilinestring_id ) ) {
        Rcpp::stop("sfheaders - multilinestring columns types are different");  // #nocov
      }

      switch( TYPEOF( geometry_cols ) ) {
      case REALSXP: {}
      case INTSXP: {
        Rcpp::IntegerVector iv_geometry_cols = Rcpp::as< Rcpp::IntegerVector >( geometry_cols );
        Rcpp::IntegerVector iv_multilinestring_id_col = Rcpp::as< Rcpp::IntegerVector >( multilinestring_id );
        Rcpp::IntegerVector iv_linestring_id_col = Rcpp::as< Rcpp::IntegerVector >( linestring_id );
        int i_multilinestring_id_col = iv_multilinestring_id_col[0];
        int i_linestring_id_col = iv_linestring_id_col[0];
        return sfc_multilinestring( x, iv_geometry_cols, i_multilinestring_id_col, i_linestring_id_col );

      }
      case STRSXP: {
        Rcpp::StringVector sv_geometry_cols = Rcpp::as< Rcpp::StringVector >( geometry_cols );
        Rcpp::StringVector sv_multilinestring_id_col = Rcpp::as< Rcpp::StringVector >( multilinestring_id );
        Rcpp::StringVector sv_linestring_id_col = Rcpp::as< Rcpp::StringVector >( linestring_id );
        Rcpp::String s_multilinestring_id_col = sv_multilinestring_id_col[0];
        Rcpp::String s_linestring_id_col = sv_linestring_id_col[0];
        return sfc_multilinestring( x, sv_geometry_cols, s_multilinestring_id_col, s_linestring_id_col );
      }
      default: {
        Rcpp::stop("sfheaders - unsupported multilinestring type");  // #nocov
      }
      }
    }

    Rcpp::stop("sfheaders - multilinestring case not yet implemented"); // #nocov
    return Rcpp::List::create(); // ??
  }

} // sfc
} // sfheaders

#endif
