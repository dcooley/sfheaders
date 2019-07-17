#ifndef R_SFHEADERS_M_RANGE_H
#define R_SFHEADERS_M_RANGE_H

#include <Rcpp.h>

namespace sfheaders {
namespace zm {

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

    Rcpp::IntegerVector z = im( Rcpp::_, 3 );
    double zmin = Rcpp::min( z );
    double zmax = Rcpp::max( z );

    m_range[0] = std::min( zmin, m_range[0] );
    m_range[1] = std::max( zmax, m_range[1] );


    // size_t n_row = im.nrow();
    // size_t i;
    // for( i = 0; i < n_row; i++ ) {
    //   Rcpp::IntegerVector iv = im( i, Rcpp::_ );
    //   calculate_bbox( bbox, iv );
    // }
  }

  inline void calculate_m_range(
      Rcpp::NumericVector& m_range,
      Rcpp::NumericMatrix& nm
  ) {

    m_range_size_check( nm );

    Rcpp::NumericVector z = nm( Rcpp::_, 3 );

    double zmin = Rcpp::min( z );
    double zmax = Rcpp::max( z );

    m_range[0] = std::min( zmin, m_range[0] );
    m_range[1] = std::max( zmax, m_range[1] );

    // size_t n_row = nm.nrow();
    // size_t i;
    // for( i = 0; i < n_row; i++ ) {
    //   Rcpp::NumericVector nv = nm( i, Rcpp::_ );
    //   calculate_bbox( bbox, nv );
    // }
  }

  inline void calculate_m_range(
      Rcpp::NumericVector& m_range,
      Rcpp::DataFrame& df
  ) {
    // assumes 'x' & 'y' column vectors
    m_range_size_check( df );

    Rcpp::NumericVector z = df[3];
    double zmin = Rcpp::min( z );
    double zmax = Rcpp::max( z );

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
      Rcpp::stop("sfheaders - can't calculate bounding box for this type");
    }
    }
  }

} // bbox
} // sfheaders


#endif
