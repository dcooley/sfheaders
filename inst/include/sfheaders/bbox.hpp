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

  inline void calculate_bbox(Rcpp::NumericVector& bbox, Rcpp::NumericVector& point) {
    //xmin, ymin, xmax, ymax
    bbox[0] = std::min(point[0], bbox[0]);
    bbox[2] = std::max(point[0], bbox[2]);

    bbox[1] = std::min(point[1], bbox[1]);
    bbox[3] = std::max(point[1], bbox[3]);
  }

  inline void calculate_bbox(Rcpp::NumericVector& bbox, Rcpp::IntegerVector& point) {
    Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( point );
    calculate_bbox( bbox, nv );
  }

} // bbox
} // sfheaders


#endif
