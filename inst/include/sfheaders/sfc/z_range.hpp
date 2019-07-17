#ifndef R_SFHEADERS_Z_RANGE_H
#define R_SFHEADERS_Z_RANGE_H

#include <Rcpp.h>

namespace sfheaders {
namespace zm {

  inline Rcpp::NumericVector start_z_range() {
    Rcpp::NumericVector range(2);
    range(0) = range(1) = NA_REAL;
    return range;
  }


  inline void z_range_size_check( Rcpp::IntegerVector& point ) {
    if( point.length() < 3 ) {
      Rcpp::stop("sfheaders - incorrect size of z_range");
    }
  }

  inline void z_range_size_check( Rcpp::NumericVector& point ) {
    if( point.length() < 3 ) {
      Rcpp::stop("sfheaders - incorrect size of z_range");
    }
  }

  inline void z_range_size_check( Rcpp::IntegerMatrix& im ) {
    if( im.ncol() < 3 ) {
      Rcpp::stop("sfheaders - incorrect size of z_range");
    }
  }

  inline void z_range_size_check( Rcpp::NumericMatrix& nm ) {
    if( nm.ncol() < 3 ) {
      Rcpp::stop("sfheaders - incorrect size of z_range");
    }
  }

  inline void z_range_size_check( Rcpp::DataFrame& df ) {
    if( df.ncol() < 3 ) {
      Rcpp::stop("sfheaders - incorrect size of z_range");
    }
  }


  inline void calculate_z_range(
      Rcpp::NumericVector& z_range,
      double& val
  ) {

    //xmin, ymin, xmax, ymax
    z_range[0] = std::min( val, z_range[0] );
    z_range[1] = std::max( val, z_range[1] );
  }

  inline void calculate_z_range(
      Rcpp::NumericVector& z_range,
      int& val
  ) {
    double d = static_cast< double >( val );
    calculate_z_range( z_range, d );
  }


  inline void calculate_z_range(
      Rcpp::NumericVector& z_range,
      Rcpp::NumericVector& point
  ) {
    z_range_size_check( point );

    double d = point[2];
    //xmin, ymin, xmax, ymax
    z_range[0] = std::min( d, z_range[0] );
    z_range[1] = std::max( d, z_range[1] );
  }

  inline void calculate_z_range(
      Rcpp::NumericVector& z_range,
      Rcpp::IntegerVector& point
  ) {
    z_range_size_check( point );

    int i = point[2];

    double d = static_cast< double >( i );
    calculate_z_range( z_range, d );
  }

  inline void calculate_z_range(
      Rcpp::NumericVector& z_range,
      Rcpp::IntegerMatrix& im
  ) {

    z_range_size_check( im );

    Rcpp::IntegerVector z = im( Rcpp::_, 2 );
    double zmin = Rcpp::min( z );
    double zmax = Rcpp::max( z );

    z_range[0] = std::min( zmin, z_range[0] );
    z_range[1] = std::max( zmax, z_range[1] );


    // size_t n_row = im.nrow();
    // size_t i;
    // for( i = 0; i < n_row; i++ ) {
    //   Rcpp::IntegerVector iv = im( i, Rcpp::_ );
    //   calculate_bbox( bbox, iv );
    // }
  }

  inline void calculate_z_range(
      Rcpp::NumericVector& z_range,
      Rcpp::NumericMatrix& nm
  ) {

    z_range_size_check( nm );

    Rcpp::NumericVector z = nm( Rcpp::_, 2 );

    double zmin = Rcpp::min( z );
    double zmax = Rcpp::max( z );

    z_range[0] = std::min( zmin, z_range[0] );
    z_range[1] = std::max( zmax, z_range[1] );

    // size_t n_row = nm.nrow();
    // size_t i;
    // for( i = 0; i < n_row; i++ ) {
    //   Rcpp::NumericVector nv = nm( i, Rcpp::_ );
    //   calculate_bbox( bbox, nv );
    // }
  }

  inline void calculate_z_range(
      Rcpp::NumericVector& z_range,
      Rcpp::DataFrame& df
  ) {
    // assumes 'x' & 'y' column vectors
    z_range_size_check( df );

    Rcpp::NumericVector z = df[2];
    double zmin = Rcpp::min( z );
    double zmax = Rcpp::max( z );

    z_range[0] = std::min( zmin, z_range[0] );
    z_range[1] = std::max( zmax, z_range[1] );

  }

  inline void calculate_z_range(
      Rcpp::NumericVector& z_range,
      SEXP& x
  ) {

    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      calculate_z_range( z_range, im );
    } else {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
      calculate_z_range( z_range, iv );
    }
    break;
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      calculate_z_range( z_range, nm );
    } else {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
      calculate_z_range( z_range, nv );
    }
    break;
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      calculate_z_range( z_range, df );
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
