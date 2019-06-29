#ifndef R_SFHEADERS_SFC_H
#define R_SFHEADERS_SFC_H

#include <Rcpp.h>
#include "sfheaders/sfc/sfc_attributes.hpp"

namespace sfheaders {
namespace sfc {

  inline SEXP to_sfc(
      Rcpp::List& sfc,
      std::string& geom_type,
      std::unordered_set< std::string >& geometry_types,
      Rcpp::NumericVector& bbox,
      Rcpp::String& epsg,
      Rcpp::String& proj4string,
      int& n_empty,
      double& precision
  ) {
    sfheaders::sfc::attach_sfc_attributes(
      sfc, geom_type, geometry_types, bbox, epsg, proj4string, n_empty, precision
    );
    return sfc;
  }

  inline SEXP to_sfc( SEXP& x, Rcpp::List params ) {

    if( params.containsElementNamed("multipolygon_id") ) {
      if( !params.containsElementNamed("polygon_id") || !params.containsElementNamed("line_id") ) {
        Rcpp::stop("MULTIPOLYGONs require polygon_id and line_id arguments" );
        // return to_multipolygon( ) ;
      }
    }

    if( params.containsElementNamed("point_id") ) {
      SEXP point_id = params["point_id"];
      // can be a char giving column of data.frame, or numeric / int for column of matrix
      switch( TYPEOF( point_id ) ) {
      case INTSXP: {}
      case REALSXP: {
        // the parameters should be column indices, so int should be fine?
        Rcpp::IntegerVector pt_id = Rcpp::as< Rcpp::IntegerVector >( point_id );
        // if the point_id column has been supplied,
        // we need to loop on those values and create sfc objects
        // because sfg is a single object, not a collection?

        //return sfheaders::sfg::to_multipoint( x, pt_id );
      }
      }
    }

    return Rcpp::List::create(); // never reaches
  }


  // inline SEXP to_sfc( SEXP& x, std::string geom_type ) {
  //   if( geom_type == "POINT" ) {
  //     // must be a vector
  //     return sfheaders::sfc::to_point( x );
  //   } else if ( geom_type == "MULTIPOINT" ) {
  //     return sfheaders::sfc::to_multipoint( x );
  //   } else if ( geom_type == "LINESTRING" ) {
  //     return sfheaders::sfc::to_linestring( x );
  //   } else if ( geom_type == "MULTIILNESTRING" ) {
  //     return sfheaders::sfc::to_multilinestring( x );
  //   } else if ( geom_type == "POLYGON" ) {
  //     return sfheaders::sfc::to_polygon( x );
  //   } else if ( geom_type == "MULTIPOLYGON" ) {
  //     return sfheaders::sfc::to_multipolygon( x );
  //   }
  //
  //   return Rcpp::List::create();
  // }
  //
  // inline SEXP to_sfc( SEXP& x, std::string geom_type, SEXP geometry_columns ) {
  //   if( geom_type == "POINT" ) {
  //     return sfheaders::sfc::to_point( x, geometry_columns );
  //   } else if ( geom_type == "MULTIPOINT" ) {
  //     return sfheaders::sfc::to_multipoint( x, geometry_columns );
  //   } else if ( geom_type == "LINESTRING" ) {
  //     return sfheaders::sfc::to_linestring( x, geometry_columns );
  //   } else if ( geom_type == "MULTIILNESTRING" ) {
  //     return sfheaders::sfc::to_multilinestring( x, geometry_columns );
  //   } else if ( geom_type == "POLYGON" ) {
  //     return sfheaders::sfc::to_polygon( x, geometry_columns );
  //   } else if ( geom_type == "MULTIPOLYGON" ) {
  //     return sfheaders::sfc::to_multipolygon( x, geometry_columns );
  //   }
  //
  //   return Rcpp::List::create(); // never reaches
  // }

} // sfc
} // sfheaders

#endif
