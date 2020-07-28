// #include <Rcpp.h>
#include "sfheaders/sfg/sfg.hpp"
//
// [[Rcpp::export]]
std::string rcpp_get_sfg_type( int sfg_type ) {
  return sfheaders::sfg::get_sfg_type( sfg_type );
}
//
// [[Rcpp::export]]
SEXP rcpp_sfg_point( SEXP x, SEXP geometry_columns, std::string xyzm ) {
  SEXP x2 = Rcpp::clone( x );
  return sfheaders::sfg::sfg_point( x2, geometry_columns, xyzm );
}

// [[Rcpp::export]]
Rcpp::List rcpp_sfg_points( Rcpp::List lst, std::string xyzm ) {
  //Rcpp::List lst2 = Rcpp::clone( lst );
  return sfheaders::sfg::sfg_points( lst, xyzm );
}

// [[Rcpp::export]]
SEXP rcpp_sfg_multipoint( SEXP x, SEXP geometry_columns, std::string xyzm ) {
  SEXP x2 = Rcpp::clone( x );
  return sfheaders::sfg::sfg_multipoint( x2, geometry_columns, xyzm );
}

// [[Rcpp::export]]
Rcpp::List rcpp_sfg_multipoints( Rcpp::List& lst, std::string xyzm ) {
  return sfheaders::sfg::sfg_multipoints( lst, xyzm );
}

// [[Rcpp::export]]
SEXP rcpp_sfg_linestring( SEXP x, SEXP geometry_columns, std::string xyzm ) {
  SEXP x2 = Rcpp::clone( x );
  return sfheaders::sfg::sfg_linestring( x2, geometry_columns, xyzm );
}

// [[Rcpp::export]]
Rcpp::List rcpp_sfg_linestrings( Rcpp::List& lst, std::string xyzm ) {
  return sfheaders::sfg::sfg_linestrings( lst, xyzm );
}


// [[Rcpp::export]]
SEXP rcpp_sfg_multilinestring( SEXP x, SEXP geometry_columns, SEXP line_id, std::string xyzm ) {
  SEXP x2 = Rcpp::clone( x );
  return sfheaders::sfg::sfg_multilinestring( x2, geometry_columns, line_id, xyzm );
}

// [[Rcpp::export]]
Rcpp::List rcpp_sfg_multilinestrings( Rcpp::List& lst, std::string xyzm ) {
  return sfheaders::sfg::sfg_multilinestrings( lst, xyzm );
}

// [[Rcpp::export]]
SEXP rcpp_sfg_polygon( SEXP x, SEXP geometry_columns, SEXP line_id, std::string xyzm, bool close ) {
  SEXP x2 = Rcpp::clone( x );
  return sfheaders::sfg::sfg_polygon( x2, geometry_columns, line_id, xyzm, close );
}

// [[Rcpp::export]]
Rcpp::List rcpp_sfg_polygons( Rcpp::List& lst,std::string xyzm, bool close ) {
  return sfheaders::sfg::sfg_polygons( lst, xyzm, close );
}

// [[Rcpp::export]]
SEXP rcpp_sfg_multipolygon( SEXP x, SEXP geometry_columns, SEXP polygon_id, SEXP line_id, std::string xyzm, bool close ) {
  SEXP x2 = Rcpp::clone( x );
  return sfheaders::sfg::sfg_multipolygon( x2, geometry_columns, polygon_id, line_id, xyzm, close );
}

// [[Rcpp::export]]
Rcpp::List rcpp_sfg_multipolygons( Rcpp::List& lst, std::string xyzm, bool close ) {
  return sfheaders::sfg::sfg_multipolygons( lst, xyzm, close );
}


// [[Rcpp::export]]
SEXP rcpp_sfg_remove_holes( SEXP sfg, bool close ) {

  Rcpp::CharacterVector cls = sfheaders::sfg::getSfgClass( sfg );
  std::string sfg_type;
  sfg_type = cls[1];
  std::string xyzm;
  xyzm = cls[0];

  if( sfg_type == "POLYGON" ) {
    Rcpp::List p = Rcpp::as< Rcpp::List >( sfg );
    return sfheaders::sfg::remove_polygon_holes( p, xyzm, close );
  } else if ( sfg_type == "MULTIPOLYGON" ) {
    Rcpp::List mp = Rcpp::as< Rcpp::List >( sfg );
    return sfheaders::sfg::remove_multipolygon_holes( mp, xyzm, close );
  }
   return sfg;
}
