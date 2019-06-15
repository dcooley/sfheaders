#ifndef R_SFHEADERS_SFC_ATTRIBUTES_H
#define R_SFHEADERS_SFC_ATTRIBUTES_H

#include <Rcpp.h>
#include "sfheaders.hpp"

namespace sfheaders {
namespace sfc {

  inline Rcpp::StringVector start_sfc_classes( size_t collectionCount ) {
    Rcpp::StringVector sfc_classes( collectionCount );
    return sfc_classes;
  }

  /* sfc class
   *
   * Determins the class of the sfc object
   * attr(sfc, "class") : c("sfc_POLYGON", "sfc")
   *
   */
  inline std::string sfc_class(
      Rcpp::List& sfc,
      std::string geom_type,
      std::unordered_set< std::string >& geometry_types
  ) {

    std::string geometry_class;

    if (geometry_types.size() == 0 ) {
      return "GEOMETRY";
    }

    if (geom_type == "GEOMETRYCOLLECTION") {
      geometry_class = "GEOMETRYCOLLECTION";
    } else {

      if (geometry_types.size() > 1) {
        geometry_class = "GEOMETRY";

        Rcpp::StringVector sfc_classes = start_sfc_classes( sfc.size() );
        for (int i = 0; i < sfc.size(); i++) {
          SEXP sfci = sfc[i];
          Rcpp::CharacterVector cls = sfheaders::getSfClass( sfci );
          sfc_classes[i] = cls[1];
        }

        // attribute::classes
        sfc.attr("classes") = sfc_classes;

      } else {
        std::string type = *geometry_types.begin();
        transform(type.begin(), type.end(), type.begin(), toupper);
        geometry_class = type;
      }
    }
    return geometry_class;
  }

  /* Attach SFC attributes
   *
   * attaches the attributes required to make an sfc object
   *
   */
  inline void attach_sfc_attributes(
      Rcpp::List& sfc,
      std::string& geom_type,
      std::unordered_set< std::string >& geometry_types,
      Rcpp::NumericVector& bbox,
      std::string epsg,
      std::string proj4string,
      int n_empty,
      double precision
  ) {

    // to enter this function, will the geometry type already be sorted?

    std::string geometry_class = sfc_class( sfc, geom_type, geometry_types );
    sfc.attr("class") = Rcpp::CharacterVector::create("sfc_" + geometry_class, "sfc");

    // attribute::crs
    Rcpp::List crs = Rcpp::List::create(
      Rcpp::Named("epsg") = epsg,
      Rcpp::Named("proj4string") = proj4string
    );

    crs.attr("class") = Rcpp::CharacterVector::create("crs");
    sfc.attr("crs") = crs;

    // attribute::precision
    sfc.attr("precision") = precision;

    // attribute::n_empty
    sfc.attr("n_empty") = n_empty;

    // attribute::bbox
    bbox.attr("class") = Rcpp::CharacterVector::create("bbox");
    bbox.attr("names") = Rcpp::CharacterVector::create("xmin", "ymin", "xmax", "ymax");
    sfc.attr("bbox") = bbox;
  }

} // sfc
} // sfheaders


#endif
