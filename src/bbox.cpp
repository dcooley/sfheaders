#include <Rcpp.h>


#include "geometries/bbox/bbox.hpp"
#include "sfheaders/sfc/bbox.hpp"
#include "sfheaders/sfc/z_range.hpp"
#include "sfheaders/sfc/m_range.hpp"

/*
 * calculate bbox
 *
 * assumes 2-column object, in the order x, y
 */
// [[Rcpp::export]]
SEXP rcpp_calculate_bbox( SEXP x, SEXP geometry_cols ) {
  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
  geometries::bbox::calculate_bbox( bbox, x, geometry_cols );
  sfheaders::bbox::attach_bbox_attributes( bbox );
  return bbox;
}

// [[Rcpp::export]]
SEXP rcpp_calculate_z_range( SEXP x ) {
  Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
  sfheaders::zm::calculate_z_range( z_range, x );
  return z_range;
}

// [[Rcpp::export]]
SEXP rcpp_calculate_m_range( SEXP x, std::string xyzm ) {
  Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();
  sfheaders::zm::calculate_m_range( m_range, x, xyzm );
  return m_range;
}

