#ifndef R_SFHEADERS_SFC_LINESTRING_H
#define R_SFHEADERS_SFC_LINESTRING_H

#include <Rcpp.h>
#include "sfheaders/sfc/sfc_types.hpp"
#include "sfheaders/sfc/sfc_attributes.hpp"
#include "sfheaders/sfg/linestring/sfg_linestring.hpp"
#include "sfheaders/sfc/zm_range.hpp"

#include "geometries/bbox/bbox.hpp"
#include "geometries/utils/columns/columns.hpp"
#include "geometries/geometries.hpp"
#include "geometries/nest/nest.hpp"

namespace sfheaders {
namespace sfc {

  inline SEXP sfc_linestring(
      SEXP& x,
      SEXP& geometry_cols,
      SEXP& linestring_id,
      std::string xyzm
  ) {

    Rcpp::StringVector class_attribute = {xyzm.c_str(), "LINESTRING","sfg"};

    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

    geometries::bbox::calculate_bbox( bbox, x );

    if( Rf_isNull( geometry_cols ) && Rf_isNull( linestring_id ) ) {

      // all columns are geometries
      SEXP geom_cols = geometries::utils::other_columns( x );
      return sfc_linestring( x, geom_cols, linestring_id, xyzm );

    } else if ( !Rf_isNull( geometry_cols ) && Rf_isNull( linestring_id ) ) {


      // without id column we only need to subset by columns and then 'nest'
      Rcpp::NumericMatrix sfg = geometries::matrix::to_matrix( x, geometry_cols );
      sfheaders::sfg::make_sfg( sfg, sfheaders::sfg::SFG_LINESTRING, xyzm );

      Rcpp::List sfc = geometries::nest::nest( sfg, 1 );

      sfheaders::zm::calculate_zm_ranges( z_range, m_range, x, geometry_cols, xyzm );
      return sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_LINESTRING, bbox, z_range, m_range );

    } else if ( Rf_isNull( geometry_cols ) && !Rf_isNull( linestring_id ) ) {

      SEXP other_cols = geometries::utils::other_columns( x, linestring_id );
      geometries::utils::geometry_column_check( other_cols );


      return sfc_linestring( x, other_cols, linestring_id, xyzm );

    } else {
      // we have all the columns sorted, so we can now get their types, calcaulte ranges/bbox etc
      geometries::utils::geometry_column_check( geometry_cols );
      Rcpp::List sfc = geometries::make_geometries( x, linestring_id, geometry_cols, class_attribute );

      sfheaders::zm::calculate_zm_ranges( z_range, m_range, x, geometry_cols, xyzm );
      return sfheaders::sfc::make_sfc( sfc, sfheaders::sfc::SFC_LINESTRING, bbox, z_range, m_range );
    }

    return Rcpp::List::create(); // ??
  }

} // sfc
} // sfheaders

#endif
