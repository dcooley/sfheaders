#ifndef R_SFHEADERS_BBOX_H
#define R_SFHEADERS_BBOX_H

#include <Rcpp.h>

namespace sfheaders {
namespace bbox {

  inline Rcpp::NumericVector start_bbox() {
    Rcpp::NumericVector bbox(4);  // xmin, ymin, xmax, ymax
    bbox(0) = bbox(1) = bbox(2) = bbox(3) = NA_REAL;
    return bbox;
  }

  inline void bbox_size_check( Rcpp::NumericVector& point ) {

    // Rcpp::Rcout << "point: " << point << std::endl;

    if( point.length() < 2 ) {
      Rcpp::stop("sfheaders - incorrect size of bounding box");
    }
  }

  inline void bbox_size_check( Rcpp::DataFrame& df ) {
    if( df.ncol() < 2 ) {
      Rcpp::stop("sfheaders - incorrect size of bounding box");
    }
  }

  inline void calculate_bbox(
      Rcpp::NumericVector& bbox,
      Rcpp::NumericVector& point
  ) {

    bbox_size_check( point );

    //xmin, ymin, xmax, ymax
    bbox[0] = std::min( point[0], bbox[0] );
    bbox[2] = std::max( point[0], bbox[2] );

    bbox[1] = std::min( point[1], bbox[1] );
    bbox[3] = std::max( point[1], bbox[3] );
  }

  inline void calculate_bbox(
      Rcpp::NumericVector& bbox,
      Rcpp::IntegerVector& point
  ) {
    Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( point );
    calculate_bbox( bbox, nv );
  }

  inline void calculate_bbox(
      Rcpp::NumericVector& bbox,
      Rcpp::IntegerMatrix& im
  ) {
    size_t n_row = im.nrow();
    size_t i;
    for( i = 0; i < n_row; i++ ) {
      Rcpp::IntegerVector iv = im( i, Rcpp::_ );
      calculate_bbox( bbox, iv );
    }
  }

  inline void calculate_bbox(
      Rcpp::NumericVector& bbox,
      Rcpp::NumericMatrix& nm
  ) {
    size_t n_row = nm.nrow();
    size_t i;
    for( i = 0; i < n_row; i++ ) {
      Rcpp::NumericVector nv = nm( i, Rcpp::_ );
      calculate_bbox( bbox, nv );
    }
  }

  inline void calculate_bbox(
    Rcpp::NumericVector& bbox,
    Rcpp::DataFrame& df
  ) {
    // assumes 'x' & 'y' column vectors
    bbox_size_check( df );
    Rcpp::NumericVector x = df[0];
    Rcpp::NumericVector y = df[1];
    double xmin = Rcpp::min( x );
    double ymin = Rcpp::min( y );
    double xmax = Rcpp::max( x );
    double ymax = Rcpp::max( y );

    bbox[0] = std::min( xmin, bbox[0] );
    bbox[2] = std::max( xmax, bbox[2] );

    bbox[1] = std::min( ymin, bbox[1] );
    bbox[3] = std::max( ymax, bbox[3] );

  }

  inline void calculate_bbox(
    Rcpp::NumericVector& bbox,
    SEXP& x
  ) {
    // integervector
    // numericvector
    // integermatrix
    // numericmatrix
    // dataframe
    // assumes 2-column?, and in correct order?
    switch( TYPEOF( x ) ) {
    case INTSXP: {
    if( Rf_isMatrix( x ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      calculate_bbox( bbox, im );
    } else {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
      calculate_bbox( bbox, iv );
    }
    break;
    }
    case REALSXP: {
    if( Rf_isMatrix( x ) ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      calculate_bbox( bbox, nm );
    } else {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
      calculate_bbox( bbox, nv );
    }
    break;
    }
    case VECSXP: {
    if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      calculate_bbox( bbox, df );
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
