#ifndef R_SFHEADERS_ZM_RANGE_H
#define R_SFHEADERS_ZM_RANGE_H

#include <Rcpp.h>
#include "sfheaders/utils/columns/columns.hpp"
#include "sfheaders/sfc/m_range.hpp"
#include "sfheaders/sfc/z_range.hpp"

namespace sfheaders {
namespace zm {

  // #nocov start
  inline void calculate_zm_ranges(
      R_xlen_t& n_col,
      Rcpp::NumericVector& z_range,
      Rcpp::NumericVector& m_range,
      Rcpp::IntegerVector& iv
  ) {
    if( n_col > 2 ) {
      sfheaders::zm::calculate_z_range( z_range, iv );
      if( n_col > 3 ) {
        sfheaders::zm::calculate_m_range( m_range, iv );
      }
    }
  }


  inline void calculate_zm_ranges(
    R_xlen_t& n_col,
    Rcpp::NumericVector& z_range,
    Rcpp::NumericVector& m_range,
    Rcpp::NumericVector& nv
  ) {
    if( n_col > 2 ) {
      sfheaders::zm::calculate_z_range( z_range, nv );
      if( n_col > 3 ) {
        sfheaders::zm::calculate_m_range( m_range, nv );
      }
    }
  }

  inline void calculate_zm_ranges(
      R_xlen_t& n_col,
      Rcpp::NumericVector& z_range,
      Rcpp::NumericVector& m_range,
      Rcpp::IntegerMatrix& im
  ) {
    if( n_col > 2 ) {
      sfheaders::zm::calculate_z_range( z_range, im );
      if( n_col > 3 ) {
        sfheaders::zm::calculate_m_range( m_range, im );
      }
    }
  }

  inline void calculate_zm_ranges(
      R_xlen_t& n_col,
      Rcpp::NumericVector& z_range,
      Rcpp::NumericVector& m_range,
      Rcpp::NumericMatrix& nm
  ) {
    if( n_col > 2 ) {
      sfheaders::zm::calculate_z_range( z_range, nm );
      if( n_col > 3 ) {
        sfheaders::zm::calculate_m_range( m_range, nm );
      }
    }
  }

  inline void calculate_zm_ranges(
      R_xlen_t& n_col,
      Rcpp::NumericVector& z_range,
      Rcpp::NumericVector& m_range,
      Rcpp::DataFrame& df
  ) {
    if( n_col > 2 ) {
      sfheaders::zm::calculate_z_range( z_range, df );
      if( n_col > 3 ) {
        sfheaders::zm::calculate_m_range( m_range, df );
      }
    }
  }

  inline void calculate_zm_ranges(
    R_xlen_t& n_col,
    Rcpp::NumericVector& z_range,
    Rcpp::NumericVector& m_range,
    Rcpp::IntegerMatrix& im,
    Rcpp::IntegerVector& geometry_cols
  ) {
    if( n_col > 2 ) {
      sfheaders::zm::calculate_z_range( z_range, im, geometry_cols );
      if( n_col > 3 ) {
        sfheaders::zm::calculate_m_range( m_range, im, geometry_cols );
      }
    }
  }

  inline void calculate_zm_ranges(
      R_xlen_t& n_col,
      Rcpp::NumericVector& z_range,
      Rcpp::NumericVector& m_range,
      Rcpp::NumericMatrix& im,
      Rcpp::IntegerVector& geometry_cols
  ) {
    if( n_col > 2 ) {
      sfheaders::zm::calculate_z_range( z_range, im, geometry_cols );
      if( n_col > 3 ) {
        sfheaders::zm::calculate_m_range( m_range, im, geometry_cols );
      }
    }
  }

  inline void calculate_zm_ranges(
      R_xlen_t& n_col,
      Rcpp::NumericVector& z_range,
      Rcpp::NumericVector& m_range,
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& geometry_cols
  ) {
    if( n_col > 2 ) {
      sfheaders::zm::calculate_z_range( z_range, df, geometry_cols );
      if( n_col > 3 ) {
        sfheaders::zm::calculate_m_range( m_range, df, geometry_cols );
      }
    }
  }

  inline void calculate_zm_ranges(
      R_xlen_t& n_col,
      Rcpp::NumericVector& z_range,
      Rcpp::NumericVector& m_range,
      Rcpp::DataFrame& df,
      Rcpp::StringVector& geometry_cols
  ) {
    if( n_col > 2 ) {
      sfheaders::zm::calculate_z_range( z_range, df, geometry_cols );
      if( n_col > 3 ) {
        sfheaders::zm::calculate_m_range( m_range, df, geometry_cols );
      }
    }
  }

  inline void calculate_zm_ranges(
    R_xlen_t& n_col,
    Rcpp::NumericVector& z_range,
    Rcpp::NumericVector& m_range,
    Rcpp::IntegerMatrix& im,
    SEXP& geometry_cols
  ) {
    switch( TYPEOF( geometry_cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( geometry_cols );
      calculate_zm_ranges( n_col, z_range, m_range, im, iv );
      break;
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( geometry_cols );
      Rcpp::IntegerVector iv = sfheaders::utils::column_positions( im, sv );
      calculate_zm_ranges( n_col, z_range, m_range, im, iv );
      break;
    }
    default: {
      Rcpp::stop("sfheaders - unknown geometry column type for calculating zm ranges");  // #nocov
    }
    }
  }

  inline void calculate_zm_ranges(
      R_xlen_t& n_col,
      Rcpp::NumericVector& z_range,
      Rcpp::NumericVector& m_range,
      Rcpp::NumericMatrix& nm,
      SEXP& geometry_cols
  ) {
    switch( TYPEOF( geometry_cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( geometry_cols );
      calculate_zm_ranges( n_col, z_range, m_range, nm, iv );
      break;
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( geometry_cols );
      Rcpp::IntegerVector iv = sfheaders::utils::column_positions( nm, sv );
      calculate_zm_ranges( n_col, z_range, m_range, nm, iv );
      break;
    }
    default: {
      Rcpp::stop("sfheaders - unknown geometry column type for calculating zm ranges");  // #nocov
    }
    }
  }

  inline void calculate_zm_ranges(
      R_xlen_t& n_col,
      Rcpp::NumericVector& z_range,
      Rcpp::NumericVector& m_range,
      Rcpp::DataFrame& df,
      SEXP& geometry_cols
  ) {
    switch( TYPEOF( geometry_cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( geometry_cols );
      calculate_zm_ranges( n_col, z_range, m_range, df, iv );
      break;
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( geometry_cols );
      calculate_zm_ranges( n_col, z_range, m_range, df, sv );
      break;
    }
    default: {
      Rcpp::stop("sfheaders - unknown geometry column type for calculating zm ranges");  // #nocov
    }
    }
  }
  // #nocov end
} // zm
} // sfheaders


#endif
