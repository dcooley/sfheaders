#ifndef R_SFHEADERS_ZM_RANGE_H
#define R_SFHEADERS_ZM_RANGE_H

#include <Rcpp.h>
#include "sfheaders/sfc/m_range.hpp"
#include "sfheaders/sfc/z_range.hpp"

namespace sfheaders {
namespace zm {

  inline void calculate_zm_ranges(
      size_t& n_col,
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
      size_t& n_col,
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
      size_t& n_col,
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
    size_t& n_col,
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
      size_t& n_col,
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
      size_t& n_col,
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
      size_t& n_col,
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

} // zm
} // sfheaders


#endif
