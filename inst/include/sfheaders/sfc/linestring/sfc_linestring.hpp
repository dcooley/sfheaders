#ifndef R_SFHEADERS_SFC_LINESTRING_H
#define R_SFHEADERS_SFC_LINESTRING_H

#include <Rcpp.h>
#include "sfheaders/sfc/sfc_attributes.hpp"
#include "sfheaders/sfg/linestring/sfg_linestring.hpp"
#include "sfheaders/sfc/bbox.hpp"

namespace sfheaders {
namespace sfc {

inline SEXP sfc_linestring(
    Rcpp::IntegerMatrix& im
) {
  //
  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();

  std::string geom_type = "LINESTRING";
  std::unordered_set< std::string > geometry_types{ geom_type };

  Rcpp::String epsg = NA_STRING;
  Rcpp::String proj4string = NA_STRING;
  int n_empty = 0;
  double precision = 0.0;

  //size_t n_col = im.ncol();
  //size_t i;
  Rcpp::List sfc( 1 );

  // need to loop through ad get the bbox
  sfheaders::bbox::calculate_bbox( bbox, im );
  Rcpp::IntegerMatrix mp = sfheaders::sfg::sfg_linestring( im );

  sfc[0] = mp;
  return sfheaders::sfc::create_sfc( sfc, geom_type, geometry_types, bbox, epsg, proj4string, n_empty, precision );
}


inline SEXP sfc_linestring(
    Rcpp::NumericMatrix& nm
) {
  //
  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();

  std::string geom_type = "LINESTRING";
  std::unordered_set< std::string > geometry_types{ geom_type };

  Rcpp::String epsg = NA_STRING;
  Rcpp::String proj4string = NA_STRING;
  int n_empty = 0;
  double precision = 0.0;

  //size_t n_col = nm.ncol();
  //size_t i;
  Rcpp::List sfc( 1 );

  // need to loop through ad get the bbox
  sfheaders::bbox::calculate_bbox( bbox, nm );
  Rcpp::NumericMatrix mp = sfheaders::sfg::sfg_linestring( nm );

  sfc[0] = mp;

  return sfheaders::sfc::create_sfc( sfc, geom_type, geometry_types, bbox, epsg, proj4string, n_empty, precision );
}


inline SEXP sfc_linestring(
    Rcpp::IntegerVector& iv
) {
  int n_col = iv.size();
  Rcpp::IntegerMatrix im(1, n_col);
  im(0, Rcpp::_ ) = iv;
  return sfc_linestring( im );
}

inline SEXP sfc_linestring(
    Rcpp::NumericVector& nv
) {
  int n_col = nv.size();
  Rcpp::NumericMatrix nm(1, n_col);
  nm(0, Rcpp::_ ) = nv;
  return sfc_linestring( nm );
}

inline SEXP sfc_linestring(
    Rcpp::List& sfc
) {
  // iterate each 'sfg' and assign 'sfg' attributes

  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();

  std::string geom_type = "LINESTRING";
  std::unordered_set< std::string > geometry_types{ geom_type };

  Rcpp::String epsg = NA_STRING;
  Rcpp::String proj4string = NA_STRING;
  int n_empty = 0;
  double precision = 0.0;

  size_t n_linestrings = sfc.size();
  size_t i;

  for( i = 0; i < n_linestrings; i++ ) {
    SEXP this_linestring = sfc[i];

    //int tp = TYPEOF( this_linestring );
    // Rcpp::Rcout << "tp: " << tp << std::endl;

    // should each element only be allowed to be a matrix??
    switch( TYPEOF( this_linestring ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( this_linestring ) ) {
      Rcpp::stop("sfheaders - expecting a matrix for linestrings");
    } else {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( this_linestring );
      sfheaders::bbox::calculate_bbox( bbox, im );
      sfc[i] = sfheaders::sfg::sfg_linestring( im );
    }
    break;
    }
    case REALSXP: {
      if( !Rf_isMatrix( this_linestring ) ) {
      Rcpp::stop("sfheaders - expecting a matrix for linestrings");
    } else {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( this_linestring );
      sfheaders::bbox::calculate_bbox( bbox, nm );
      sfc[i] = sfheaders::sfg::sfg_linestring( nm );
    }
    break;
    }
    default: {
      Rcpp::stop("sfheaders - unknown linestring type");
    }
    }
    // Rcpp::Rcout << "bbox: " << bbox << std::endl;
  }
  return sfheaders::sfc::create_sfc( sfc, geom_type, geometry_types, bbox, epsg, proj4string, n_empty, precision );

}

// no subsetting to do; so just turn the object into a matrix;
inline SEXP sfc_linestring(
    SEXP& x
) {
  Rcpp::List mp(1);
  mp[0] = sfheaders::shapes::get_mat( x );
  return sfc_linestring( mp );
}


// no subsetting to do (except for columsn)
inline SEXP sfc_linestring(
    SEXP& x,
    SEXP& geometry_cols
) {
  sfheaders::utils::geometry_column_check( geometry_cols );
  Rcpp::List mp(1);
  mp[0] = sfheaders::shapes::get_mat( x, geometry_cols );
  return sfc_linestring( mp );
}

// if an 'id' col is supplied, it means we have many linestrings
// linestring_id & point_id
inline SEXP sfc_linestring(
    SEXP& x,
    SEXP& geometry_cols,
    SEXP& linestring_id
) {
  // TODO - how to handle bbox
  if( Rf_isNull( geometry_cols ) && Rf_isNull( linestring_id ) ) {
    return sfc_linestring( x );

  } else if ( !Rf_isNull( geometry_cols ) && Rf_isNull( linestring_id ) ) {

    // make the geometry cols all the other columns??
    return sfc_linestring( x, geometry_cols );
  } else if ( Rf_isNull( geometry_cols ) && !Rf_isNull( linestring_id ) ) {

    SEXP other_cols = sfheaders::utils::other_columns( x, linestring_id );
    sfheaders::utils::geometry_column_check( other_cols );
    //return sfc_linestrings( x, other_cols, geometry_cols );
    Rcpp::List mp = sfheaders::shapes::get_listMat( x, other_cols, linestring_id );
    return sfc_linestring( mp );

  } else {
    sfheaders::utils::geometry_column_check( geometry_cols );
    Rcpp::List mp = sfheaders::shapes::get_listMat( x, geometry_cols, linestring_id );
    return sfc_linestring( mp );
  }

  return Rcpp::List::create(); // ??
}



} // sfc
} // sfheaders

#endif
