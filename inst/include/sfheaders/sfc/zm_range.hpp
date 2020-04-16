#ifndef R_SFHEADERS_ZM_RANGE_H
#define R_SFHEADERS_ZM_RANGE_H

#include <Rcpp.h>
#include "sfheaders/utils/columns/columns.hpp"
#include "sfheaders/sfc/m_range.hpp"
#include "sfheaders/sfc/z_range.hpp"

namespace sfheaders {
namespace zm {

  inline std::string guess_xyzm( R_xlen_t n_col ) {

    switch( n_col ) {
    case 2: { return "XY"; }
    case 3: { return "XYZ"; }
    case 4: { return "XYZM"; }
    default: { Rcpp::stop("sfheaders - can't work out the dimension"); }
    }
    return ""; // #nocov - never reaches
  }

  // #nocov start
  inline void calculate_zm_ranges(
      Rcpp::NumericVector& z_range,
      Rcpp::NumericVector& m_range,
      Rcpp::IntegerVector& iv,
      std::string xyzm
  ) {

    if( xyzm.empty() ) {
      xyzm = guess_xyzm( iv.length() );
    }

    if ( xyzm ==  "XYM" ) {
      sfheaders::zm::calculate_m_range( m_range, iv, xyzm );
    } else if ( xyzm == "XYZ" ) {
      sfheaders::zm::calculate_z_range( z_range, iv );
    } else if ( xyzm == "XYZM" ) {
      sfheaders::zm::calculate_z_range( z_range, iv );
      sfheaders::zm::calculate_m_range( m_range, iv, xyzm );
    }
  }


  inline void calculate_zm_ranges(
    Rcpp::NumericVector& z_range,
    Rcpp::NumericVector& m_range,
    Rcpp::NumericVector& nv,
    std::string xyzm
  ) {

    if( xyzm.empty() ) {
      xyzm = guess_xyzm( nv.length() );
    }

    if ( xyzm ==  "XYM" ) {
      sfheaders::zm::calculate_m_range( m_range, nv, xyzm );
    } else if ( xyzm == "XYZ" ) {
      sfheaders::zm::calculate_z_range( z_range, nv );
    } else if ( xyzm == "XYZM" ) {
      sfheaders::zm::calculate_z_range( z_range, nv );
      sfheaders::zm::calculate_m_range( m_range, nv, xyzm );
    }
  }

  inline void calculate_zm_ranges(
      Rcpp::NumericVector& z_range,
      Rcpp::NumericVector& m_range,
      Rcpp::IntegerMatrix& im,
      std::string xyzm
  ) {

    if( xyzm.empty() ) {
      xyzm = guess_xyzm( im.ncol() );
    }

    if ( xyzm ==  "XYM" ) {
      sfheaders::zm::calculate_m_range( m_range, im, xyzm );
    } else if ( xyzm == "XYZ" ) {
      sfheaders::zm::calculate_z_range( z_range, im );
    } else if ( xyzm == "XYZM" ) {
      sfheaders::zm::calculate_z_range( z_range, im );
      sfheaders::zm::calculate_m_range( m_range, im, xyzm );
    }
  }

  inline void calculate_zm_ranges(
      Rcpp::NumericVector& z_range,
      Rcpp::NumericVector& m_range,
      Rcpp::NumericMatrix& nm,
      std::string xyzm
  ) {

    if( xyzm.empty() ) {
      xyzm = guess_xyzm( nm.ncol() );
    }

    if ( xyzm ==  "XYM" ) {
      sfheaders::zm::calculate_m_range( m_range, nm, xyzm );
    } else if ( xyzm == "XYZ" ) {
      sfheaders::zm::calculate_z_range( z_range, nm );
    } else if ( xyzm == "XYZM" ) {
      sfheaders::zm::calculate_z_range( z_range, nm );
      sfheaders::zm::calculate_m_range( m_range, nm, xyzm );
    }
  }

  inline void calculate_zm_ranges(
      Rcpp::NumericVector& z_range,
      Rcpp::NumericVector& m_range,
      Rcpp::DataFrame& df,
      std::string xyzm
  ) {

    if( xyzm.empty() ) {
      xyzm = guess_xyzm( df.ncol() );
    }

    if ( xyzm ==  "XYM" ) {
      sfheaders::zm::calculate_m_range( m_range, df, xyzm );
    } else if ( xyzm == "XYZ" ) {
      sfheaders::zm::calculate_z_range( z_range, df );
    } else if ( xyzm == "XYZM" ) {
      sfheaders::zm::calculate_z_range( z_range, df );
      sfheaders::zm::calculate_m_range( m_range, df, xyzm );
    }
  }

  inline void calculate_zm_ranges(
    Rcpp::NumericVector& z_range,
    Rcpp::NumericVector& m_range,
    Rcpp::IntegerMatrix& im,
    Rcpp::IntegerVector& geometry_cols,
    std::string xyzm
  ) {
    if( xyzm.empty() ) {
      xyzm = guess_xyzm( geometry_cols.size() );
    }

    if ( xyzm ==  "XYM" ) {
      sfheaders::zm::calculate_m_range( m_range, im, geometry_cols, xyzm );
    } else if ( xyzm == "XYZ" ) {
      sfheaders::zm::calculate_z_range( z_range, im, geometry_cols );
    } else if ( xyzm == "XYZM" ) {
      sfheaders::zm::calculate_z_range( z_range, im, geometry_cols );
      sfheaders::zm::calculate_m_range( m_range, im, geometry_cols, xyzm );
    }
  }

  inline void calculate_zm_ranges(
      Rcpp::NumericVector& z_range,
      Rcpp::NumericVector& m_range,
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& geometry_cols,
      std::string xyzm
  ) {
    if( xyzm.empty() ) {
      xyzm = guess_xyzm( geometry_cols.size() );
    }

    if ( xyzm ==  "XYM" ) {
      sfheaders::zm::calculate_m_range( m_range, nm, geometry_cols, xyzm );
    } else if ( xyzm == "XYZ" ) {
      sfheaders::zm::calculate_z_range( z_range, nm, geometry_cols );
    } else if ( xyzm == "XYZM" ) {
      sfheaders::zm::calculate_z_range( z_range, nm, geometry_cols );
      sfheaders::zm::calculate_m_range( m_range, nm, geometry_cols, xyzm );
    }
  }

  inline void calculate_zm_ranges(
      Rcpp::NumericVector& z_range,
      Rcpp::NumericVector& m_range,
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& geometry_cols,
      std::string xyzm
  ) {

    if( xyzm.empty() ) {
      xyzm = guess_xyzm( geometry_cols.size() );
    }

    if ( xyzm ==  "XYM" ) {
      sfheaders::zm::calculate_m_range( m_range, df, geometry_cols, xyzm );
    } else if ( xyzm == "XYZ" ) {
      sfheaders::zm::calculate_z_range( z_range, df, geometry_cols );
    } else if ( xyzm == "XYZM" ) {
      sfheaders::zm::calculate_z_range( z_range, df, geometry_cols );
      sfheaders::zm::calculate_m_range( m_range, df, geometry_cols, xyzm );
    }
  }

  inline void calculate_zm_ranges(
      Rcpp::NumericVector& z_range,
      Rcpp::NumericVector& m_range,
      Rcpp::DataFrame& df,
      Rcpp::StringVector& geometry_cols,
      std::string xyzm
  ) {

    if( xyzm.empty() ) {
      xyzm = guess_xyzm( geometry_cols.size() );
    }

    if ( xyzm ==  "XYM" ) {
      sfheaders::zm::calculate_m_range( m_range, df, geometry_cols, xyzm );
    } else if ( xyzm == "XYZ" ) {
      sfheaders::zm::calculate_z_range( z_range, df, geometry_cols );
    } else if ( xyzm == "XYZM" ) {
      sfheaders::zm::calculate_z_range( z_range, df, geometry_cols );
      sfheaders::zm::calculate_m_range( m_range, df, geometry_cols, xyzm );
    }
  }

  inline void calculate_zm_ranges(
    Rcpp::NumericVector& z_range,
    Rcpp::NumericVector& m_range,
    Rcpp::IntegerMatrix& im,
    SEXP& geometry_cols,
    std::string xyzm
  ) {
    switch( TYPEOF( geometry_cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( geometry_cols );
      calculate_zm_ranges( z_range, m_range, im, iv, xyzm );
      break;
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( geometry_cols );
      Rcpp::IntegerVector iv = sfheaders::utils::column_positions( im, sv );
      calculate_zm_ranges( z_range, m_range, im, iv, xyzm );
      break;
    }
    default: {
      Rcpp::stop("sfheaders - unknown geometry column type for calculating zm ranges");  // #nocov
    }
    }
  }

  inline void calculate_zm_ranges(
      Rcpp::NumericVector& z_range,
      Rcpp::NumericVector& m_range,
      Rcpp::NumericMatrix& nm,
      SEXP& geometry_cols,
      std::string xyzm
  ) {
    switch( TYPEOF( geometry_cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( geometry_cols );
      calculate_zm_ranges( z_range, m_range, nm, iv, xyzm );
      break;
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( geometry_cols );
      Rcpp::IntegerVector iv = sfheaders::utils::column_positions( nm, sv );
      calculate_zm_ranges( z_range, m_range, nm, iv, xyzm );
      break;
    }
    default: {
      Rcpp::stop("sfheaders - unknown geometry column type for calculating zm ranges");  // #nocov
    }
    }
  }

  inline void calculate_zm_ranges(
      Rcpp::NumericVector& z_range,
      Rcpp::NumericVector& m_range,
      Rcpp::DataFrame& df,
      SEXP& geometry_cols,
      std::string xyzm
  ) {
    switch( TYPEOF( geometry_cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( geometry_cols );
      calculate_zm_ranges( z_range, m_range, df, iv, xyzm );
      break;
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( geometry_cols );
      calculate_zm_ranges( z_range, m_range, df, sv, xyzm );
      break;
    }
    default: {
      Rcpp::stop("sfheaders - unknown geometry column type for calculating zm ranges");  // #nocov
    }
    }
  }
  // #nocov end

  // overloads for revedeps (geojsonsf)
  inline void calculate_zm_ranges(
    R_xlen_t n_col,
    Rcpp::NumericVector z_range,
    Rcpp::NumericVector m_range,
    Rcpp::NumericVector nv
  ) {
    std::string xyzm;
    calculate_zm_ranges( z_range, m_range, nv, xyzm );
  }

} // zm
} // sfheaders


#endif
