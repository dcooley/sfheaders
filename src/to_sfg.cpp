#include <Rcpp.h>
#include "sfheaders/sfg/sfg.hpp"

// [[Rcpp::export]]
std::string rcpp_get_sfg_type( int sfg_type ) {
  return sfheaders::sfg::get_sfg_type( sfg_type );
}

// [[Rcpp::export]]
SEXP rcpp_sfg_point( SEXP x, SEXP geometry_columns, bool m_only = false ) {
  return sfheaders::sfg::sfg_point( x, geometry_columns, m_only );
}

// [[Rcpp::export]]
Rcpp::List rcpp_sfg_points( Rcpp::List& lst, bool m_only = false ) {
  return sfheaders::sfg::sfg_points( lst, m_only );
}

// [[Rcpp::export]]
SEXP rcpp_sfg_multipoint( SEXP x, SEXP geometry_columns, bool m_only = false ) {
  return sfheaders::sfg::sfg_multipoint( x, geometry_columns, m_only );
}

// [[Rcpp::export]]
Rcpp::List rcpp_sfg_multipoints( Rcpp::List& lst, bool m_only = false ) {
  return sfheaders::sfg::sfg_multipoints( lst, m_only );
}

// [[Rcpp::export]]
SEXP rcpp_sfg_linestring( SEXP x, SEXP geometry_columns, bool m_only = false ) {
  return sfheaders::sfg::sfg_linestring( x, geometry_columns, m_only );
}

// [[Rcpp::export]]
Rcpp::List rcpp_sfg_linestrings( Rcpp::List& lst, bool m_only = false ) {
  return sfheaders::sfg::sfg_linestrings( lst, m_only );
}


// [[Rcpp::export]]
SEXP rcpp_sfg_multilinestring( SEXP x, SEXP geometry_columns, SEXP line_id, bool m_only = false ) {
  return sfheaders::sfg::sfg_multilinestring( x, geometry_columns, line_id, m_only );
}

// [[Rcpp::export]]
Rcpp::List rcpp_sfg_multilinestrings( Rcpp::List& lst, bool m_only = false ) {
  return sfheaders::sfg::sfg_multilinestrings( lst, m_only );
}

// [[Rcpp::export]]
SEXP rcpp_sfg_polygon( SEXP x, SEXP geometry_columns, SEXP line_id, bool close = true, bool m_only = false ) {
  return sfheaders::sfg::sfg_polygon( x, geometry_columns, line_id, close, m_only );
}

// [[Rcpp::export]]
Rcpp::List rcpp_sfg_polygons( Rcpp::List& lst, bool close = true, bool m_only = false ) {
  return sfheaders::sfg::sfg_polygons( lst, close, m_only );
}

// [[Rcpp::export]]
SEXP rcpp_sfg_multipolygon( SEXP x, SEXP geometry_columns, SEXP polygon_id, SEXP line_id, bool close = true, bool m_only = false ) {
  return sfheaders::sfg::sfg_multipolygon( x, geometry_columns, polygon_id, line_id, close, m_only );
}

// [[Rcpp::export]]
Rcpp::List rcpp_sfg_multipolygons( Rcpp::List& lst, bool close = true, bool m_only = false ) {
  return sfheaders::sfg::sfg_multipolygons( lst, close, m_only );
}


// [[Rcpp::export]]
SEXP rcpp_sfg_remove_holes( SEXP sfg, bool close ) {

  Rcpp::CharacterVector cls = sfheaders::sfg::getSfgClass( sfg );
  std::string sfg_type;
  sfg_type = cls[1];

  if( sfg_type == "POLYGON" ) {
    Rcpp::List p = Rcpp::as< Rcpp::List >( sfg );
    return sfheaders::sfg::remove_polygon_holes( p, close );
  } else if ( sfg_type == "MULTIPOLYGON" ) {
    Rcpp::List mp = Rcpp::as< Rcpp::List >( sfg );
    return sfheaders::sfg::remove_multipolygon_holes( mp, close );
  }
   return sfg;
}
