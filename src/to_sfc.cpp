#include <Rcpp.h>
#include "geometries/bbox/bbox.hpp"
#include "sfheaders/sfc/sfc.hpp"

#include "sfheaders/sfg/polygon/sfg_polygon.hpp"
#include "sfheaders/sfg/multipolygon/sfg_multipolygon.hpp"

// [[Rcpp::export]]
SEXP rcpp_sfc_point( SEXP x, SEXP cols, std::string xyzm ) {
  return sfheaders::sfc::sfc_point( x, cols, xyzm );
}

// [[Rcpp::export]]
SEXP rcpp_sfc_points( Rcpp::List lst, std::string xyzm ) {
  return sfheaders::sfc::sfc_points( lst, xyzm );
}

// [[Rcpp::export]]
SEXP rcpp_sfc_multipoint( SEXP x, SEXP cols, SEXP id_col, std::string xyzm ) {
  return sfheaders::sfc::sfc_multipoint( x, cols, id_col, xyzm );
}

// [[Rcpp::export]]
SEXP rcpp_sfc_multipoints( Rcpp::List lst, std::string xyzm ) {
  return sfheaders::sfc::sfc_multipoints( lst, xyzm );
}

// [[Rcpp::export]]
SEXP rcpp_sfc_linestring( SEXP x, SEXP cols, SEXP id_col, std::string xyzm ) {
  return sfheaders::sfc::sfc_linestring( x, cols, id_col, xyzm );
}

// [[Rcpp::export]]
SEXP rcpp_sfc_linestrings( Rcpp::List lst, std::string xyzm ) {
  return sfheaders::sfc::sfc_linestrings( lst, xyzm );
}

// [[Rcpp::export]]
SEXP rcpp_sfc_multilinestring( SEXP x, SEXP cols, SEXP multiline_id, SEXP line_id, std::string xyzm) {
  return sfheaders::sfc::sfc_multilinestring( x, cols, multiline_id, line_id, xyzm );
}

// [[Rcpp::export]]
SEXP rcpp_sfc_multilinestrings( Rcpp::List lst, std::string xyzm ) {
  return sfheaders::sfc::sfc_multilinestrings( lst, xyzm );
}

// [[Rcpp::export]]
SEXP rcpp_sfc_polygon( SEXP x, SEXP cols, SEXP polygon_id, SEXP line_id, std::string xyzm, bool close ) {
  return sfheaders::sfc::sfc_polygon( x, cols, polygon_id, line_id, xyzm, close );
}

// [[Rcpp::export]]
SEXP rcpp_sfc_polygons( Rcpp::List lst, std::string xyzm, bool close ) {
  return sfheaders::sfc::sfc_polygons( lst, xyzm, close );
}


// [[Rcpp::export]]
SEXP rcpp_sfc_multipolygon( SEXP x, SEXP cols, SEXP multipolygon_id, SEXP polygon_id, SEXP linestring_id, std::string xyzm, bool close ) {
  return sfheaders::sfc::sfc_multipolygon( x, cols, multipolygon_id, polygon_id, linestring_id, xyzm, close );
}

// [[Rcpp::export]]
SEXP rcpp_sfc_multipolygons( Rcpp::List lst, std::string xyzm, bool close ) {
  return sfheaders::sfc::sfc_multipolygons( lst, xyzm, close );
}

// [[Rcpp::export]]
Rcpp::List rcpp_sfc_remove_holes( Rcpp::List sfc, bool close ) {

  Rcpp::List attributes = sfheaders::sfc::get_sfc_attributes( sfc );

  R_xlen_t i;
  R_xlen_t n_sfc = sfc.size();
  Rcpp::List res( n_sfc );
  for( i = 0; i < n_sfc; ++i ) {
    SEXP sfg = sfc[ i ];
    Rcpp::CharacterVector cls = sfheaders::sfc::getSfClass( sfg );
    std::string sfg_type;
    sfg_type = cls[1];
    std::string xyzm;
    xyzm = cls[0];
    if( sfg_type == "POLYGON" ) {
      Rcpp::List p = Rcpp::as< Rcpp::List >( sfg );
      res[ i ] = sfheaders::sfg::remove_polygon_holes( p, xyzm, close );
    } else if ( sfg_type == "MULTIPOLYGON" ) {
      Rcpp::List mp = Rcpp::as< Rcpp::List >( sfg );
      res[ i ] = sfheaders::sfg::remove_multipolygon_holes( mp, xyzm, close );
    } else {
      res[ i ] = sfg;
    }
  }
  sfheaders::sfc::attach_sfc_attributes( res, attributes );
  return res;
}


// // [[Rcpp::export]]
// Rcpp::List rcpp_get_sfc_attributes( Rcpp::List sfc ) {
//   return sfheaders::sfc::get_sfc_attributes( sfc );
// }

// [[Rcpp::export]]
SEXP rcpp_sfg_boxes( SEXP sfg ) {
  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
  geometries::bbox::calculate_bbox( bbox, sfg );
  return sfheaders::sfg::sfg_box( bbox );
}


// [[Rcpp::export]]
SEXP rcpp_sfc_boxes( Rcpp::List sfc ) {
  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
  Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
  Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();
  R_xlen_t n = sfc.length();
  R_xlen_t i;
  Rcpp::List res( n );
  for( i = 0; i < n; ++i ) {
    SEXP sfg = sfc[ i ];
    Rcpp::NumericVector box = sfheaders::bbox::start_bbox();
    geometries::bbox::calculate_bbox( box, sfg );
    Rcpp::List p = sfheaders::sfg::sfg_box( box );
    geometries::bbox::calculate_bbox( bbox, sfg );
    res[ i ] = p;
  }

  sfheaders::sfc::make_sfc( res, sfheaders::sfc::SFC_POLYGON, bbox, z_range, m_range );
  return res;
}
