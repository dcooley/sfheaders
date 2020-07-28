#ifndef R_SFHEADERS_SFC_POLYGON_H
#define R_SFHEADERS_SFC_POLYGON_H

#include <Rcpp.h>
#include "sfheaders/sfc/sfc_attributes.hpp"
#include "sfheaders/sfc/sfc_types.hpp"
#include "sfheaders/sfc/zm_range.hpp"

#include "sfheaders/utils/utils.hpp"

#include "geometries/bbox/bbox.hpp"
#include "geometries/utils/columns/columns.hpp"
#include "geometries/geometries.hpp"

namespace sfheaders {
namespace sfc {

  inline SEXP sfc_polygon(
      SEXP& x,
      SEXP& geometry_cols,
      SEXP& polygon_id,
      SEXP& linestring_id,
      std::string xyzm,
      bool close = true
  ) {


    if( Rf_isNull( geometry_cols ) ) {
      // make this all the other columns, then send back in
      SEXP geometry_cols2 = geometries::utils::other_columns( x, polygon_id, linestring_id );
      return sfc_polygon( x, geometry_cols2, polygon_id, linestring_id, xyzm, close );
    }

    // Rcpp::Rcout << "sfc_polygon" << std::endl;

    int n_id_cols = 2;
    R_xlen_t col_counter = geometries::utils::sexp_length( geometry_cols );

    // After subset_geometries we have moved the geometry columns
    // into the 0:(n_geometry-1) positions
    Rcpp::IntegerVector int_geometry_cols = Rcpp::seq( 0, ( col_counter - 1 ) );

    xyzm = sfheaders::utils::validate_xyzm( xyzm, col_counter );

    Rcpp::StringVector class_attribute = { xyzm.c_str(), "POLYGON","sfg" };
    Rcpp::List attributes = Rcpp::List::create(
      Rcpp::_["class"] = class_attribute
    );

    // Rcpp::Rcout << "sfc_polygon 2" << std::endl;


    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

    // Rcpp::Rcout << "sfc_polygon 3"  << std::endl;

    geometries::bbox::calculate_bbox( bbox, x, geometry_cols );

    // Rcpp::Rcout << "sfc_polygon 4"  << std::endl;
    sfheaders::zm::calculate_zm_ranges( z_range, m_range, x, geometry_cols, xyzm );

    // Rcpp::Rcout << "sfc_polygon 5"  << std::endl;

    R_xlen_t required_cols = col_counter + n_id_cols;

    Rcpp::IntegerVector geometry_cols_int = geometries::utils::sexp_col_int( x, geometry_cols );

    Rcpp::List lst = geometries::utils::as_list( x );
    Rcpp::List res( required_cols );

    sfheaders::utils::subset_geometries( lst, res, geometry_cols_int );

    Rcpp::IntegerVector int_polygon_id(1);
    sfheaders::utils::resolve_id( x, polygon_id, int_polygon_id, res, lst, col_counter );


    Rcpp::IntegerVector int_linestring_id(1);
    sfheaders::utils::resolve_id( x, linestring_id, int_linestring_id, res, lst, col_counter );

    Rcpp::IntegerVector int_id_cols = geometries::utils::concatenate_vectors( int_polygon_id, int_linestring_id );

    Rcpp::List sfc = geometries::make_geometries( res, int_id_cols, int_geometry_cols, attributes, close );
    return sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_POLYGON, bbox, z_range, m_range );

  }

  inline SEXP sfc_polygon(
      SEXP& x
  ) {
    SEXP geometry_cols = R_NilValue;
    SEXP polygon_id = R_NilValue;
    SEXP linestring_id = R_NilValue;
    std::string xyzm;
    return sfc_polygon( x, geometry_cols, polygon_id, linestring_id, xyzm );
  }

} // sfc
} // sfheaders

#endif
