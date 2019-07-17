#include <Rcpp.h>
#include "sfheaders/sfc/sfc_attributes.hpp"

// [[Rcpp::export]]
void rcpp_attach_sfc_attributes(
    Rcpp::List& sfc,
    std::string geom_type,
    Rcpp::NumericVector& bbox,
    Rcpp::NumericVector& z_range,
    Rcpp::NumericVector& m_range,
    std::string epsg,
    std::string proj4string,
    int n_empty,
    double precision
) {

  std::unordered_set< std::string > geometry_types;
  sfheaders::sfc::attach_sfc_attributes(sfc, geom_type, geometry_types, bbox, z_range, m_range, epsg, proj4string, n_empty, precision );
}
