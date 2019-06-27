#include <Rcpp.h>
#include "sfheaders/sfc/sfc_attributes.hpp"

// [[Rcpp::export]]
void rcpp_attach_sfc_attributes(
    Rcpp::List& sfc,
    std::string geom_type,
    Rcpp::NumericVector& bbox,
    std::string epsg,
    std::string proj4string,
    int n_empty,
    double precision
) {

  std::unordered_set< std::string > geometry_types;
  sfheaders::sfc::attach_sfc_attributes(sfc, geom_type, geometry_types, bbox, epsg, proj4string, n_empty, precision );
}
