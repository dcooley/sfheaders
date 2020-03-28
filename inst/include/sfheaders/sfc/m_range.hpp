#ifndef R_SFHEADERS_M_RANGE_H
#define R_SFHEADERS_M_RANGE_H

#include <Rcpp.h>
#include "sfheaders/utils/sexp/sexp.hpp"

namespace sfheaders {
namespace zm {

  inline void attach_m_range_attributes( Rcpp::NumericVector& m_range ) {
    m_range.attr("class") = Rcpp::CharacterVector::create("m_range");
    m_range.attr("names") = Rcpp::CharacterVector::create("mmin","mmax");
  }

  inline Rcpp::NumericVector start_m_range() {
    Rcpp::NumericVector range(2);
    range(0) = range(1) = NA_REAL;
    return range;
  }


  inline void m_range_size_check( Rcpp::IntegerVector& point ) {
    if( point.length() < 4 ) {
      Rcpp::stop("sfheaders - incorrect size of m_range");
    }
  }

  inline void m_range_size_check( Rcpp::NumericVector& point ) {
    if( point.length() < 4 ) {
      Rcpp::stop("sfheaders - incorrect size of m_range");
    }
  }

  inline void m_range_size_check( Rcpp::IntegerMatrix& im ) {
    if( im.ncol() < 4 ) {
      Rcpp::stop("sfheaders - incorrect size of m_range");
    }
  }

  inline void m_range_size_check( Rcpp::NumericMatrix& nm ) {
    if( nm.ncol() < 4 ) {
      Rcpp::stop("sfheaders - incorrect size of m_range");
    }
  }

  inline void m_range_size_check( Rcpp::DataFrame& df ) {
    if( df.ncol() < 4 ) {
      Rcpp::stop("sfheaders - incorrect size of m_range");
    }
  }

  inline void m_range_size_check( SEXP& x ) {
    R_xlen_t n_col = sfheaders::utils::get_sexp_n_col( x );
    if( n_col < 4 ) {
      Rcpp::stop("sfheaders - incorrect size of m_range");
    }
  }


  inline void calculate_m_range(
      Rcpp::NumericVector& m_range,
      double& val
  ) {

    //xmin, ymin, xmax, ymax
    m_range[0] = std::min( val, m_range[0] );
    m_range[1] = std::max( val, m_range[1] );
  }

  inline void calculate_m_range(
      Rcpp::NumericVector& m_range,
      int& val
  ) {
    double d = static_cast< double >( val );
    calculate_m_range( m_range, d );
  }


  inline void calculate_m_range(
      Rcpp::NumericVector& m_range,
      Rcpp::NumericVector& point
  ) {
    m_range_size_check( point );

    double d = point[3];
    //xmin, ymin, xmax, ymax
    m_range[0] = std::min( d, m_range[0] );
    m_range[1] = std::max( d, m_range[1] );
  }

  inline void calculate_m_range(
      Rcpp::NumericVector& m_range,
      Rcpp::IntegerVector& point
  ) {
    m_range_size_check( point );

    int i = point[3];

    double d = static_cast< double >( i );
    calculate_m_range( m_range, d );
  }

  inline void calculate_m_range(
      Rcpp::NumericVector& m_range,
      Rcpp::IntegerMatrix& im
  ) {

    m_range_size_check( im );

    Rcpp::IntegerVector m = im( Rcpp::_, 3 );
    double zmin = Rcpp::min( m );
    double zmax = Rcpp::max( m );

    m_range[0] = std::min( zmin, m_range[0] );
    m_range[1] = std::max( zmax, m_range[1] );

  }

  inline void calculate_m_range(
      Rcpp::NumericVector& m_range,
      Rcpp::NumericMatrix& nm
  ) {

    m_range_size_check( nm );

    Rcpp::NumericVector m = nm( Rcpp::_, 3 );

    double zmin = Rcpp::min( m );
    double zmax = Rcpp::max( m );

    m_range[0] = std::min( zmin, m_range[0] );
    m_range[1] = std::max( zmax, m_range[1] );

  }

  inline void calculate_m_range(
      Rcpp::NumericVector& m_range,
      Rcpp::DataFrame& df
  ) {
    // assumes 'x' & 'y' column vectors
    m_range_size_check( df );

    Rcpp::NumericVector m = df[3];
    double zmin = Rcpp::min( m );
    double zmax = Rcpp::max( m );

    m_range[0] = std::min( zmin, m_range[0] );
    m_range[1] = std::max( zmax, m_range[1] );

  }

  inline void calculate_m_range(
      Rcpp::NumericVector& m_range,
      SEXP& x
  ) {

    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      calculate_m_range( m_range, im );
    } else {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
      calculate_m_range( m_range, iv );
    }
    break;
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      calculate_m_range( m_range, nm );
    } else {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
      calculate_m_range( m_range, nv );
    }
    break;
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      calculate_m_range( m_range, df );
      break;
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - can't calculate bounding box for this type");  // #nocov
    }
    }
  }

  // #nocov start
  inline void calculate_m_range(
      Rcpp::NumericVector& m_range,
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& geometry_cols
  ) {
    if( geometry_cols.length() > 3 ) {
      int idx = geometry_cols[3];
      Rcpp::IntegerVector m = im( Rcpp::_, idx );
      double zmin = Rcpp::min( m );
      double zmax = Rcpp::max( m );

      m_range[0] = std::min( zmin, m_range[0] );
      m_range[1] = std::max( zmax, m_range[1] );
    }
  }

  inline void calculate_m_range(
      Rcpp::NumericVector& m_range,
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& geometry_cols
  ) {

    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );

    if( geometry_cols.length() > 3 ) {
      Rcpp::String idx = geometry_cols[3];
      std::string s_idx = idx.get_cstring();
      Rcpp::IntegerVector m = df[ s_idx ];
      double zmin = Rcpp::min( m );
      double zmax = Rcpp::max( m );

      m_range[0] = std::min( zmin, m_range[0] );
      m_range[1] = std::max( zmax, m_range[1] );
    }
  }

  inline void calculate_m_range(
      Rcpp::NumericVector& m_range,
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& geometry_cols
  ) {
    if( geometry_cols.length() > 3 ) {
      int idx = geometry_cols[3];
      Rcpp::NumericVector m = nm( Rcpp::_, idx );
      double zmin = Rcpp::min( m );
      double zmax = Rcpp::max( m );

      m_range[0] = std::min( zmin, m_range[0] );
      m_range[1] = std::max( zmax, m_range[1] );
    }
  }

  inline void calculate_m_range(
      Rcpp::NumericVector& m_range,
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& geometry_cols
  ) {

    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );

    if( geometry_cols.length() > 3 ) {
      Rcpp::String idx = geometry_cols[3];
      std::string s_idx = idx.get_cstring();
      Rcpp::NumericVector m = df[ s_idx ];
      double zmin = Rcpp::min( m );
      double zmax = Rcpp::max( m );

      m_range[0] = std::min( zmin, m_range[0] );
      m_range[1] = std::max( zmax, m_range[1] );
    }
  }
  // #nocov end

  inline void calculate_m_range(
      Rcpp::NumericVector& m_range,
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& geometry_cols
  ) {
    if( geometry_cols.length() > 3 ) {
      int idx = geometry_cols[3];
      Rcpp::NumericVector m = df[ idx ];
      double zmin = Rcpp::min( m );
      double zmax = Rcpp::max( m );

      m_range[0] = std::min( zmin, m_range[0] );
      m_range[1] = std::max( zmax, m_range[1] );
    }
  }

  inline void calculate_m_range(
      Rcpp::NumericVector& m_range,
      Rcpp::DataFrame& df,
      Rcpp::StringVector& geometry_cols
  ) {

    if( geometry_cols.length() > 3 ) {
      Rcpp::String idx = geometry_cols[3];
      std::string s_idx = idx.get_cstring();
      Rcpp::NumericVector m = df[ s_idx ];
      double zmin = Rcpp::min( m );
      double zmax = Rcpp::max( m );

      m_range[0] = std::min( zmin, m_range[0] );
      m_range[1] = std::max( zmax, m_range[1] );
    }
  }

} // bbox
} // sfheaders


#endif
