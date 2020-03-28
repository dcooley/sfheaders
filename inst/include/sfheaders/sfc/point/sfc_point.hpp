#ifndef R_SFHEADERS_SFC_POINT_H
#define R_SFHEADERS_SFC_POINT_H

#include <Rcpp.h>
#include "sfheaders/sfc/sfc_types.hpp"
#include "sfheaders/sfc/sfc_attributes.hpp"
#include "sfheaders/sfg/point/sfg_point.hpp"
#include "sfheaders/sfc/bbox.hpp"
#include "sfheaders/sfc/zm_range.hpp"
#include "sfheaders/shapes/shapes.hpp"

namespace sfheaders {
namespace sfc {

  // Requirs a list of sfg_POINTs, and the bbox / ranges
  // does not do any calculations; just makes the SFC structure
  inline SEXP sfc_point(
      Rcpp::List& sfc,
      Rcpp::NumericVector& bbox,
      Rcpp::NumericVector& z_range,
      Rcpp::NumericVector& m_range
  ) {
    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_POINT, bbox, z_range, m_range );
    return sfc;
  }

  inline SEXP sfc_point(
    Rcpp::IntegerMatrix& im
  ) {

    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();
    int n_empty = 0;

    // matrix; iterate through each row, get bbox, create sfg of each point
    // then an sfc of all other points
    R_xlen_t n_row = im.nrow();
    R_xlen_t n_col = im.ncol();

    sfheaders::bbox::calculate_bbox( bbox, im );
    sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, im );

    R_xlen_t i;
    Rcpp::List sfc( n_row );

    for( i = 0; i < n_row; ++i ) {
      Rcpp::IntegerVector this_point = im( i, Rcpp::_ );
      if( sfheaders::utils::is_null_geometry( this_point, "POINT" ) ) {
        n_empty++;
      }
      sfc[i] = sfheaders::sfg::sfg_point( this_point );
    }

    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_POINT, bbox, z_range, m_range, n_empty );
    return sfc;
  }

  inline SEXP sfc_point(
    Rcpp::IntegerVector& iv
  ) {
    int n_col = iv.size();
    Rcpp::IntegerMatrix im(1, n_col);
    im(0, Rcpp::_ ) = iv;
    return sfc_point( im );
  }


  inline SEXP sfc_point(
      Rcpp::NumericMatrix& nm
  ) {

    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();
    int n_empty = 0;

    // matrix; iterate through each row, get bbox, create sfg of each point
    // then an sfc of all other points
    R_xlen_t n_row = nm.nrow();
    R_xlen_t n_col = nm.ncol();

    sfheaders::bbox::calculate_bbox( bbox, nm );
    sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, nm );

    R_xlen_t i;
    Rcpp::List sfc( n_row );

    for( i = 0; i < n_row; ++i ) {
      Rcpp::NumericVector this_point = nm( i, Rcpp::_ );
      if( sfheaders::utils::is_null_geometry( this_point, "POINT" ) ) {
        n_empty++;
      }
      sfc[i] = sfheaders::sfg::sfg_point( this_point );
    }

    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_POINT, bbox, z_range, m_range, n_empty );
    return sfc;
  }

  inline SEXP sfc_point(
      Rcpp::NumericVector& iv
  ) {
    int n_col = iv.size();
    Rcpp::NumericMatrix nm(1, n_col);
    nm(0, Rcpp::_ ) = iv;
    return sfc_point( nm );
  }


  inline SEXP sfc_point(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& cols
  ) {

    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();
    int n_empty = 0;

    R_xlen_t n_row = im.nrow();
    R_xlen_t n_col = im.ncol();
    R_xlen_t i;

    sfheaders::bbox::calculate_bbox( bbox, im, cols );
    sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, im, cols );

    Rcpp::List sfc(n_row);
    for( i = 0; i < n_row; ++i ) {
      Rcpp::IntegerVector this_point = im( i, Rcpp::_ );
      if( sfheaders::utils::is_null_geometry( this_point, "POINT" ) ) {
        n_empty++;  // #nocov
      }
      sfc[i] = sfheaders::sfg::sfg_point( this_point, cols );
    }

    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_POINT, bbox, z_range, m_range, n_empty );
    return sfc;
  }

  inline SEXP sfc_point(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& cols
  ) {

    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

    Rcpp::IntegerVector column_positions = sfheaders::utils::column_positions( im, cols );

    R_xlen_t i;
    R_xlen_t n_row = im.nrow();
    R_xlen_t n_col = im.ncol();

    sfheaders::bbox::calculate_bbox( bbox, im );
    sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, im );

    Rcpp::List sfc(n_row);

    for( i = 0; i < n_row; ++i ) {
      Rcpp::IntegerMatrix this_point = sfheaders::utils::matrix_row_to_matrix( im, i );
      sfc[i] = sfheaders::sfg::sfg_point( this_point, column_positions );
    }

    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_POINT, bbox, z_range, m_range );
    return sfc;
  }

  inline SEXP sfc_point(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& cols
  ) {

    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();
    int n_empty = 0;

    R_xlen_t n_row = nm.nrow();
    R_xlen_t n_col = nm.ncol();
    R_xlen_t i;

    sfheaders::bbox::calculate_bbox( bbox, nm, cols );
    sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, nm, cols );

    Rcpp::List sfc( n_row );
    for( i = 0; i < n_row; ++i ) {
      Rcpp::NumericVector this_point = nm( i, Rcpp::_ );
      if( sfheaders::utils::is_null_geometry( this_point, "POINT" ) ) {
        n_empty++;
      }
      sfc[i] = sfheaders::sfg::sfg_point( this_point, cols );
    }

    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_POINT, bbox, z_range, m_range, n_empty );
    return sfc;
  }

  inline SEXP sfc_point(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& cols
  ) {

    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

    Rcpp::IntegerVector column_positions = sfheaders::utils::column_positions( nm, cols );

    R_xlen_t i;
    R_xlen_t n_row = nm.nrow();
    R_xlen_t n_col = nm.ncol();

    sfheaders::bbox::calculate_bbox( bbox, nm );
    sfheaders::zm::calculate_zm_ranges( n_col, z_range, m_range, nm );

    Rcpp::List sfc(n_row);

    for( i = 0; i < n_row; ++i ) {
      Rcpp::NumericMatrix this_point = sfheaders::utils::matrix_row_to_matrix( nm, i );
      sfc[i] = sfheaders::sfg::sfg_point( this_point, column_positions );
    }

    sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_POINT, bbox, z_range, m_range );
    return sfc;
  }

  inline SEXP sfc_point(
      Rcpp::DataFrame& df
  ) {
    Rcpp::NumericMatrix nm = sfheaders::utils::df_to_matrix( df );
    return sfc_point( nm );
  }

  inline SEXP sfc_point(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& cols
  ) {
    Rcpp::NumericMatrix nm = sfheaders::utils::df_to_matrix( df, cols );
    return sfc_point( nm );
  }

  inline SEXP sfc_point(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& cols
  ) {
    Rcpp::NumericMatrix nm = sfheaders::utils::df_to_matrix( df, cols );
    return sfc_point( nm );
  }

  inline SEXP sfc_point(
      SEXP& x
  ) {

    SEXP xc = Rcpp::clone( x );

    // switch on type of x
    switch ( TYPEOF( xc ) ) {
    case INTSXP: {
      if( Rf_isMatrix( xc ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
      return sfc_point( im );
    } else {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( xc );
      return sfc_point( iv );
    }
    }
    case REALSXP: {
      if( Rf_isMatrix( xc ) ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
      return sfc_point( nm );
    } else {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( xc );
      return sfc_point( nv );
    }
    }
    case VECSXP: { // data.frame && list?
      if( Rf_inherits( xc, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( xc );
      return sfc_point( df );
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_POINT type");
    }
    }

    return x; // never reaches
  }

  inline SEXP sfc_point(
      SEXP& x,
      Rcpp::IntegerVector& cols
  ) {

    SEXP xc = Rcpp::clone( x );

    switch( TYPEOF( xc ) ) {
    case INTSXP: {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
      return sfc_point( im, cols );
    }
    case REALSXP: {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
      return sfc_point( nm, cols );
    }
    case VECSXP: {
      if ( Rf_inherits( xc, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( xc );
      return sfc_point( df, cols );
    } //else - default
    }
    default: {
      Rcpp::stop("sfheaders - unknown point type");  // #nocov
    }
    }
    return Rcpp::List::create(); // never reaches
  }

  inline SEXP sfc_point(
      SEXP& x,
      Rcpp::StringVector& cols
  ) {

    SEXP xc = Rcpp::clone( x );

    switch( TYPEOF( xc ) ) {
    case INTSXP: {
    if( Rf_isMatrix( xc ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( xc );
      return sfc_point( im, cols );
    // } else {
    //   Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
    //   return sfc_point( iv, cols );
    }
    }
    case REALSXP: {
    if( Rf_isMatrix( xc ) ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( xc );
      return sfc_point( nm, cols );
    // } else {
    //   Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
    //   return sfc_point( nv, cols );
    }
    }
    case VECSXP: {
    if( Rf_inherits( xc, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( xc );
      return sfc_point( df, cols );
    }
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfc_POINT type");  // #nocov
    }
    }
    return Rcpp::List::create();
  }

  inline SEXP sfc_point(
      SEXP& x,
      SEXP& cols
  ) {

    if( Rf_isNull( cols ) ) {
      return sfc_point( x );
    }
    sfheaders::utils::geometry_column_check( cols );

    switch( TYPEOF( cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector int_cols = Rcpp::as< Rcpp::IntegerVector >( cols );
      return sfc_point( x, int_cols );
    }
    case STRSXP: {
      Rcpp::StringVector str_cols = Rcpp::as< Rcpp::StringVector >( cols );
      return sfc_point( x, str_cols );
    }
    default: {
      Rcpp::stop("sfheaders - unknown column types");  // #nocov
    }
    }
    return Rcpp::List::create(); // never reaches
  }




  // for POINTs, each row is a unique point
  // and for sfc objects we don't keep the id column
  // so don't need this case
  // inline SEXP sfc_point(
  //     SEXP& x,
  //     SEXP& geometry_cols,
  //     SEXP& point_id,
  // ) {
  //   if( Rf_isNull( geometry_cols ) && Rf_isNull( point_id ) ) {
  //     return sfc_point( x );
  //   }
  //
  //   if( Rf_isNull( point_id ) && !Rf_isNull( geometry_cols ) ) {
  //     return sfc_point( x, geometry_cols );
  //   }
  //
  //   if( !Rf_isNull( point_id ) && Rf_isNull( geometry_cols ) ) {
  //     SEXP geometry_cols2 = sfheaders::utils::other_columns( x, point_id );
  //     return sfc_point( x, geometry_cols, point_id ); // send back in
  //   }
  //
  //   if( TYPEOF( geometry_cols ) != TYPEOF( point_id ) ) {
  //     Rcpp::stop("sfheaders - point columns types are different");
  //   }
  //
  //   sfheaders::utils::geometry_column_check( geometry_cols );
  //
  //   switch( TYPEOF( geometry_cols ) ) {
  //   case REALSXP: {}
  //   case INTSXP: {
  //     Rcpp::IntegerVector iv_geometry_cols = Rcpp::as< Rcpp::IntegerVector >( geometry_cols );
  //     Rcpp::IntegerVector iv_point_id_col = Rcpp::as< Rcpp::IntegerVector >( point_id );
  //     int i_point_id_col = iv_point_id_col[0];
  //     return sfc_point( x, iv_geometry_cols, i_point_id_col );
  //
  //   }
  //   case STRSXP: {
  //     Rcpp::StringVector sv_geometry_cols = Rcpp::as< Rcpp::StringVector >( geometry_cols );
  //     Rcpp::StringVector sv_point_id_col = Rcpp::as< Rcpp::StringVector >( point_id );
  //     Rcpp::String s_point_id_col = sv_point_id_col[0];
  //     return sfc_point( x, sv_geometry_cols, s_point_id_col );
  //   }
  //   default: {
  //     Rcpp::stop("sfheaders - unsupported multipoint type");
  //   }
  //   }
  //
  //   return Rcpp::List::create(); // never reaches
  // }


} // sfc
} // sfheaders

#endif
