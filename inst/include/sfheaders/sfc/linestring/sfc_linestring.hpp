#ifndef R_SFHEADERS_SFC_LINESTRING_H
#define R_SFHEADERS_SFC_LINESTRING_H

#include <Rcpp.h>
#include "sfheaders/sfc/sfc_types.hpp"
#include "sfheaders/sfc/sfc_attributes.hpp"
#include "sfheaders/sfg/linestring/sfg_linestring.hpp"
#include "sfheaders/sfc/bbox.hpp"
#include "sfheaders/sfc/zm_range.hpp"
#include "sfheaders/shapes/shapes.hpp"

namespace sfheaders {
namespace sfc {

  // Requirs a list of sfg_LINESTRINGs, and the bbox / ranges
  // does not do any calculations; just makes the SFC structure
  inline SEXP sfc_linestring(
      Rcpp::List& sfc,
      Rcpp::NumericVector& bbox,
      Rcpp::NumericVector& z_range,
      Rcpp::NumericVector& m_range
  ) {
    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_LINESTRING, bbox, z_range, m_range );
    return sfc;
  }

  inline SEXP sfc_linestring(
      Rcpp::IntegerMatrix& im
  ) {

    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

    R_xlen_t n_col = im.ncol();

    Rcpp::List sfc( 1 );

    sfheaders::bbox::calculate_bbox( bbox, im );
    sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, im );

    Rcpp::IntegerMatrix mp = sfheaders::sfg::sfg_linestring( im );

    sfc[0] = mp;
    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_LINESTRING, bbox, z_range, m_range );
    return sfc;
  }


  inline SEXP sfc_linestring(
      Rcpp::NumericMatrix& nm
  ) {

    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

    R_xlen_t n_col = nm.ncol();

    Rcpp::List sfc( 1 );

    sfheaders::bbox::calculate_bbox( bbox, nm );
    sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, nm );

    Rcpp::NumericMatrix mp = sfheaders::sfg::sfg_linestring( nm );

    sfc[0] = mp;
    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_LINESTRING, bbox, z_range, m_range );
    return sfc;
  }

  inline SEXP sfc_linestring(
      Rcpp::DataFrame& df
  ) {

    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

    R_xlen_t n_col = df.ncol();

    Rcpp::List sfc( 1 );

    sfheaders::bbox::calculate_bbox( bbox, df );
    sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, df );

    Rcpp::NumericMatrix mp = sfheaders::sfg::sfg_linestring( df );

    sfc[0] = mp;
    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_LINESTRING, bbox, z_range, m_range );
    return sfc;
  }


  inline SEXP sfc_linestring(
      Rcpp::IntegerVector& iv
  ) {
    int n_col = iv.size();
    Rcpp::IntegerMatrix im(1, n_col);
    im(0, Rcpp::_ ) = iv;
    return sfc_linestring( im );
  }

  inline SEXP sfc_linestring(
      Rcpp::NumericVector& nv
  ) {
    int n_col = nv.size();
    Rcpp::NumericMatrix nm(1, n_col);
    nm(0, Rcpp::_ ) = nv;
    return sfc_linestring( nm );
  }

  // inline SEXP sfc_linestring(
  //     Rcpp::List& sfc
  // ) {
  //
  //   Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
  //   Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
  //   Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();
  //
  //   R_xlen_t n_linestrings = sfc.size();
  //   R_xlen_t i;
  //
  //   for( i = 0; i < n_linestrings; ++i ) {
  //     SEXP this_linestring = sfc[i];
  //
  //     // should each element only be allowed to be a matrix??
  //     switch( TYPEOF( this_linestring ) ) {
  //     case INTSXP: {
  //       if( !Rf_isMatrix( this_linestring ) ) {
  //       Rcpp::stop("sfheaders - expecting a matrix for linestrings");
  //     } else {
  //       Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( this_linestring );
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
  //       sfc[i] = sfheaders::sfg::sfg_linestring( im );
  //     }
  //     break;
  //     }
  //     case REALSXP: {
  //       if( !Rf_isMatrix( this_linestring ) ) {
  //       Rcpp::stop("sfheaders - expecting a matrix for linestrings");
  //     } else {
  //       Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( this_linestring );
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
  //       sfc[i] = sfheaders::sfg::sfg_linestring( nm );
  //     }
  //     break;
  //     }
  //     default: {
  //       Rcpp::stop("sfheaders - unknown linestring type");
  //     }
  //     }
  //   }
  //   sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_LINESTRING, bbox, z_range, m_range );
  //   return sfc;
  //
  // }

  // no subsetting to do; so just turn the object into a matrix;
  inline SEXP sfc_linestring(
      SEXP& x
  ) {
    // here there is no subsetting required;
    // we have to assume the columsn are in order x,y,(z,(m))
    switch( TYPEOF( x ) ) {
    case INTSXP: {
    if( Rf_isMatrix( x ) ) {
      SEXP xc = Rcpp::clone( x );
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
      return sfc_linestring( im );
    } else {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
      return sfc_linestring( iv );
    }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
      SEXP xc = Rcpp::clone( x );
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
      return sfc_linestring( nm );
    } else {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
      return sfc_linestring( nv );
    }
    }
    case VECSXP: {
    if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfc_linestring( df );
    }
    }
    default: {
      Rcpp::stop("sfheaders - unsupported linestring type");  // #nocov
    }
    }
    return Rcpp::List::create();
  }

  inline SEXP sfc_linestring(
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
    Rcpp::NumericMatrix sfg = sfheaders::sfg::sfg_linestring( im, geometry_cols );
    sfc[0] = sfg;
    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_LINESTRING, bbox, z_range, m_range );
    return sfc;
  }

  inline SEXP sfc_linestring(
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
    Rcpp::NumericMatrix sfg = sfheaders::sfg::sfg_linestring( df, geometry_cols );
    sfc[0] = sfg;
    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_LINESTRING, bbox, z_range, m_range );
    return sfc;
  }

  inline SEXP sfc_linestring(
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
    Rcpp::NumericMatrix sfg = sfheaders::sfg::sfg_linestring( nm, geometry_cols );
    sfc[0] = sfg;
    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_LINESTRING, bbox, z_range, m_range );
    return sfc;
  }

  inline SEXP sfc_linestring(
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
    Rcpp::NumericMatrix sfg = sfheaders::sfg::sfg_linestring( df, geometry_cols );
    sfc[0] = sfg;
    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_LINESTRING, bbox, z_range, m_range );
    return sfc;
  }

  inline SEXP sfc_linestring(
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
    Rcpp::NumericMatrix sfg = sfheaders::sfg::sfg_linestring( df, geometry_cols );
    sfc[0] = sfg;
    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_LINESTRING, bbox, z_range, m_range );
    return sfc;
  }

  inline SEXP sfc_linestring(
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
    Rcpp::NumericMatrix sfg = sfheaders::sfg::sfg_linestring( df, geometry_cols );
    sfc[0] = sfg;
    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_LINESTRING, bbox, z_range, m_range );
    return sfc;
  }

  inline SEXP sfc_linestring(
      SEXP& x,
      Rcpp::StringVector& geometry_cols
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
      SEXP xc = Rcpp::clone( x );
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
      return sfc_linestring( im, geometry_cols );
      // } else {
      //   Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
      //   return sfc_linestring( iv, geometry_cols );
    }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
      SEXP xc = Rcpp::clone( x );
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
      return sfc_linestring( nm, geometry_cols );
      // } else {
      //   Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
      //   return sfc_linestring( nv, geometry_cols );
    }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfc_linestring( df, geometry_cols );
    }
    }
    default: {
      Rcpp::stop("sfheaders - unsupported linestring type");  // #nocov
    }
    }
    return Rcpp::List::create();
  }

  inline SEXP sfc_linestring(
    SEXP& x,
    Rcpp::IntegerVector& geometry_cols
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
      SEXP xc = Rcpp::clone( x );
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
      return sfc_linestring( im, geometry_cols );
    // } else {
    //   Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
    //   return sfc_linestring( iv, geometry_cols );
    }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
      SEXP xc = Rcpp::clone( x );
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
      return sfc_linestring( nm, geometry_cols );
    // } else {
    //   Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
    //   return sfc_linestring( nv, geometry_cols );
    }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfc_linestring( df, geometry_cols );
    }
    }
    default: {
      Rcpp::stop("sfheaders - unsupported linestring type");   // #nocov
    }
    }
    return Rcpp::List::create();
  }

  // no subsetting to do (except for columns)
  inline SEXP sfc_linestring(
      SEXP& x,
      SEXP& geometry_cols
  ) {
    sfheaders::utils::geometry_column_check( geometry_cols );

    switch( TYPEOF( geometry_cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( geometry_cols );
      return sfc_linestring( x, iv );
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( geometry_cols );
      return sfc_linestring( x, sv );
    }
    default: {
      Rcpp::stop("sfheaders - unknown column type");    // #nocov
    }
    }
    return Rcpp::List::create();
  }


  inline SEXP sfc_linestring(
    Rcpp::IntegerMatrix& im,
    Rcpp::IntegerVector& geometry_cols,
    Rcpp::IntegerMatrix& line_positions
  ) {
    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

    sfheaders::bbox::calculate_bbox( bbox, im, geometry_cols );

    R_xlen_t n_col = im.ncol();
    sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, im, geometry_cols );

    R_xlen_t n_lines = line_positions.nrow();

    Rcpp::List sfc( n_lines );

    int start;
    int end;
    if( n_lines == 1 ) {
      sfc( 0 ) = sfheaders::sfg::sfg_linestring( im, geometry_cols );
    } else {

      R_xlen_t i;
      for( i = 0; i < n_lines; ++i ) {

        start = line_positions(i, 0);
        end = line_positions(i, 1);

        Rcpp::NumericMatrix m = sfheaders::shapes::get_listMat( im, geometry_cols, start, end );  // returns a matrix
        sfc( i ) = sfheaders::sfg::sfg_linestring( m );
      }
    }

    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_LINESTRING, bbox, z_range, m_range );
    return sfc;
  }

  inline SEXP sfc_linestring(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& geometry_cols,
      Rcpp::IntegerVector& line_ids
  ) {
    Rcpp::IntegerMatrix line_positions = sfheaders::utils::id_positions( line_ids );
    return sfc_linestring( im, geometry_cols, line_positions );
  }

  inline SEXP sfc_linestring(
    Rcpp::NumericMatrix& nm,
    Rcpp::IntegerVector& geometry_cols,
    Rcpp::IntegerMatrix& line_positions
  ) {
    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

    sfheaders::bbox::calculate_bbox( bbox, nm, geometry_cols );

    R_xlen_t n_col = nm.ncol();
    sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, nm, geometry_cols );

    R_xlen_t n_lines = line_positions.nrow();

    Rcpp::List sfc( n_lines );

    int start;
    int end;
    if( n_lines == 1 ) {
      sfc( 0 ) = sfheaders::sfg::sfg_linestring( nm, geometry_cols );
    } else {

      R_xlen_t i;
      for( i = 0; i < n_lines; ++i ) {

        start = line_positions(i, 0);
        end = line_positions(i, 1);

        Rcpp::NumericMatrix m = sfheaders::shapes::get_listMat( nm, geometry_cols, start, end );  // returns a matrix
        sfc( i ) = sfheaders::sfg::sfg_linestring( m );
      }
    }

    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_LINESTRING, bbox, z_range, m_range );
    return sfc;
  }

  inline SEXP sfc_linestring(
    Rcpp::NumericMatrix& nm,
    Rcpp::IntegerVector& geometry_cols,
    Rcpp::NumericVector& line_ids
  ) {
    Rcpp::IntegerMatrix line_positions = sfheaders::utils::id_positions( line_ids );
    return sfc_linestring( nm, geometry_cols, line_positions );
  }

  inline SEXP sfc_linestring(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& geometry_cols,
    Rcpp::IntegerMatrix& line_positions
  ) {
    R_xlen_t n_lines = line_positions.nrow();
    Rcpp::List sfc( n_lines );

    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

    sfheaders::bbox::calculate_bbox( bbox, df, geometry_cols );

    R_xlen_t n_col = df.ncol();
    sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, df, geometry_cols );

    int start;
    int end;
    if( n_lines == 1 ) {
      sfc( 0 ) = sfheaders::sfg::sfg_linestring( df, geometry_cols );
    } else {

      R_xlen_t i;
      for( i = 0; i < n_lines; ++i ) {

        start = line_positions(i, 0);
        end = line_positions(i, 1);

        Rcpp::NumericMatrix m = sfheaders::shapes::get_listMat( df, geometry_cols, start, end );  // returns a matrix
        sfc( i ) = sfheaders::sfg::sfg_linestring( m );
      }
    }
    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_LINESTRING, bbox, z_range, m_range );
    return sfc;
  }

  inline SEXP sfc_linestring(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& geometry_cols,
      SEXP& line_ids
  ) {
    Rcpp::IntegerMatrix line_positions = sfheaders::utils::id_positions( line_ids );
    return sfc_linestring( df, geometry_cols, line_positions );
  }

  inline SEXP sfc_linestring(
    Rcpp::DataFrame& df,
    Rcpp::IntegerVector& geometry_cols,
    Rcpp::IntegerMatrix& line_positions
  ) {
    R_xlen_t n_lines = line_positions.nrow();
    Rcpp::List sfc( n_lines );

    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

    sfheaders::bbox::calculate_bbox( bbox, df, geometry_cols );

    R_xlen_t n_col = df.ncol();
    sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, df, geometry_cols );

    int start;
    int end;
    if( n_lines == 1 ) {
      sfc( 0 ) = sfheaders::sfg::sfg_linestring( df, geometry_cols );
    } else {

      R_xlen_t i;
      for( i = 0; i < n_lines; ++i ) {

        start = line_positions(i, 0);
        end = line_positions(i, 1);

        Rcpp::NumericMatrix m = sfheaders::shapes::get_listMat( df, geometry_cols, start, end );  // returns a matrix
        sfc( i ) = sfheaders::sfg::sfg_linestring( m );
      }
    }

    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_LINESTRING, bbox, z_range, m_range );
    return sfc;
  }


  inline SEXP sfc_linestring(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& geometry_cols,
      SEXP& line_ids
  ) {
    Rcpp::IntegerMatrix line_positions = sfheaders::utils::id_positions( line_ids );
    return sfc_linestring( df, geometry_cols, line_positions );
  }

  inline SEXP sfc_linestring(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& geometry_cols,
      int& linestring_id
  ) {

    sfheaders::utils::column_exists( im, linestring_id );
    Rcpp::IntegerVector line_ids = im( Rcpp::_, linestring_id );
    return sfc_linestring( im, geometry_cols, line_ids );
  }

  inline SEXP sfc_linestring(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& geometry_cols,
      int& linestring_id
  ) {
    sfheaders::utils::column_exists( nm, linestring_id );
    Rcpp::NumericVector line_ids = nm( Rcpp::_, linestring_id );
    return sfc_linestring( nm, geometry_cols, line_ids );
  }

  // #nocov start
  inline SEXP sfc_linestring(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& geometry_cols,
      Rcpp::String& linestring_id
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );
    SEXP line_ids = df[ linestring_id ];
    return sfc_linestring( df, geometry_cols, line_ids );
  }
  // #nocov end

  inline SEXP sfc_linestring(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& geometry_cols,
      Rcpp::String& linestring_id
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );
    SEXP line_ids = df[ linestring_id ];
    return sfc_linestring( df, geometry_cols, line_ids );
  }


  inline SEXP sfc_linestring(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& geometry_cols,
      Rcpp::String& linestring_id
  ) {
    SEXP line_ids = df[ linestring_id ];
    return sfc_linestring( df, geometry_cols, line_ids );
  }

  inline SEXP sfc_linestring(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& geometry_cols,
      int& linestring_id
  ) {
    sfheaders::utils::column_exists( df, linestring_id );
    SEXP line_ids = df[ linestring_id ];
    return sfc_linestring( df, geometry_cols, line_ids );
  }

  inline SEXP sfc_linestring(
    SEXP& x,
    Rcpp::IntegerVector& geometry_cols,
    int& linestring_id
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
    if( Rf_isMatrix( x ) ) {
      SEXP xc = Rcpp::clone( x );
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
      return sfc_linestring( im, geometry_cols, linestring_id );
    // } else {
    // Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
    // return sfc_linestring( iv, geometry_cols, linestring_id );
    }
    }
    case REALSXP: {
    if( Rf_isMatrix( x ) ) {
      SEXP xc = Rcpp::clone( x );
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
      return sfc_linestring( nm, geometry_cols, linestring_id );
    // } else {
    //   Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
    //   return sfc_linestring( nv, geometry_cols, linestring_id );
    }
    }
    case VECSXP: {
    if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfc_linestring( df, geometry_cols, linestring_id );
    }
    }
    default: {
      Rcpp::stop("sfheaders - unsupported linestring type"); // #nocov
    }
    }

    return Rcpp::List::create();

  }

  inline SEXP sfc_linestring(
      SEXP& x,
      Rcpp::StringVector& geometry_cols,
      Rcpp::String& linestring_id
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
    if( Rf_isMatrix( x ) ) {  // #nocov
      SEXP xc = Rcpp::clone( x ); // #nocov
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
      return sfc_linestring( im, geometry_cols, linestring_id );
    // } else {
    //   Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
    //   return sfc_linestring( iv, geometry_cols, linestring_id );
    }
    }
    case REALSXP: {
    if( Rf_isMatrix( x ) ) {
      SEXP xc = Rcpp::clone( x );
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
      return sfc_linestring( nm, geometry_cols, linestring_id );
    // } else {
    //   Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
    //   return sfc_linestring( nv, geometry_cols, linestring_id );
    }
    }
    case VECSXP: {
    if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfc_linestring( df, geometry_cols, linestring_id );
    }
    }
    default: {
      Rcpp::stop("sfheaders - unsupported linestring type"); // #nocov
    }
    }

    return Rcpp::List::create();
  }

  // if an 'id' col is supplied, it means we have many linestrings
  // linestring_id & point_id
  inline SEXP sfc_linestring(
      SEXP& x,
      SEXP& geometry_cols,
      SEXP& linestring_id
  ) {
    if( Rf_isNull( geometry_cols ) && Rf_isNull( linestring_id ) ) {

      return sfc_linestring( x );

    } else if ( !Rf_isNull( geometry_cols ) && Rf_isNull( linestring_id ) ) {

      // make the geometry cols all the other columns??
      return sfc_linestring( x, geometry_cols );

    } else if ( Rf_isNull( geometry_cols ) && !Rf_isNull( linestring_id ) ) {

      SEXP other_cols = sfheaders::utils::other_columns( x, linestring_id );
      sfheaders::utils::geometry_column_check( other_cols );

      return sfc_linestring( x, other_cols, linestring_id );

    } else {
      // we have all the columns sorted, so we can now get their types, calcaulte ranges/bbox etc
      sfheaders::utils::geometry_column_check( geometry_cols );

      if ( TYPEOF( geometry_cols ) != TYPEOF( linestring_id ) ) {
        Rcpp::stop("sfheaders - linestring columns types are different");
      }

      switch( TYPEOF( geometry_cols ) ) {
      case REALSXP: {}
      case INTSXP: {
        Rcpp::IntegerVector iv_geometry_cols = Rcpp::as< Rcpp::IntegerVector >( geometry_cols );
        Rcpp::IntegerVector iv_linestring_id_col = Rcpp::as< Rcpp::IntegerVector >( linestring_id );
        int i_linestring_id_col = iv_linestring_id_col[0];
        return sfc_linestring( x, iv_geometry_cols, i_linestring_id_col );
      }
      case STRSXP: {
        Rcpp::StringVector sv_geometry_cols = Rcpp::as< Rcpp::StringVector >( geometry_cols );
        Rcpp::StringVector sv_linestring_id_col = Rcpp::as< Rcpp::StringVector >( linestring_id );
        Rcpp::String s_linestring_id_col = sv_linestring_id_col[0];
        return sfc_linestring( x, sv_geometry_cols, s_linestring_id_col );
      }
      default: {
          Rcpp::stop("sfheaders - unsupported linestring type");  // #nocov
        }
      }
    }

    return Rcpp::List::create(); // ??
  }

} // sfc
} // sfheaders

#endif
