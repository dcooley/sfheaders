#ifndef R_SFHEADERS_SFC_LINESTRINGS_H
#define R_SFHEADERS_SFC_LINESTRINGS_H

#include <Rcpp.h>
#include "sfheaders/sfg/linestring/sfg_linestring.hpp"
#include "sfheaders/shapes/mat/mat.hpp"
#include "sfheaders/shapes/list_mat/list_mat.hpp"
#include "sfheaders/shapes/list_list_mat/list_list_mat.hpp"
#include "sfheaders/bbox.hpp"
#include "sfheaders/sfc/sfc.hpp"


namespace sfheaders {
namespace sfc {

inline SEXP to_linestrings(
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
  Rcpp::IntegerMatrix mp = sfheaders::sfg::to_linestring( im );

  sfc[0] = mp;
  return sfheaders::sfc::to_sfc( sfc, geom_type, geometry_types, bbox, epsg, proj4string, n_empty, precision );
}


inline SEXP to_linestrings(
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
  Rcpp::NumericMatrix mp = sfheaders::sfg::to_linestring( nm );

  sfc[0] = mp;

  return sfheaders::sfc::to_sfc( sfc, geom_type, geometry_types, bbox, epsg, proj4string, n_empty, precision );
}


inline SEXP to_linestrings(
    Rcpp::IntegerVector& iv
) {
  int n_col = iv.size();
  Rcpp::IntegerMatrix im(1, n_col);
  im(0, Rcpp::_ ) = iv;
  return to_linestrings( im );
}

inline SEXP to_linestrings(
    Rcpp::NumericVector& nv
) {
  int n_col = nv.size();
  Rcpp::NumericMatrix nm(1, n_col);
  nm(0, Rcpp::_ ) = nv;
  return to_linestrings( nm );
}

inline SEXP to_linestrings(
    Rcpp::List& sfc
) {
  // iterate each 'sfg' and assign 'sfg' attributes

  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();

  std::string geom_type = "MULTIPOINT";
  std::unordered_set< std::string > geometry_types{ geom_type };

  Rcpp::String epsg = NA_STRING;
  Rcpp::String proj4string = NA_STRING;
  int n_empty = 0;
  double precision = 0.0;

  size_t n_multipoints = sfc.size();
  size_t i;

  for( i = 0; i < n_multipoints; i++ ) {
    SEXP this_multipoint = sfc[i];

    //int tp = TYPEOF( this_multipoint );
    // Rcpp::Rcout << "tp: " << tp << std::endl;

    // should each element only be allowed to be a matrix??
    switch( TYPEOF( this_multipoint ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( this_multipoint ) ) {
      Rcpp::stop("sfheaders - expecting a matrix for multipoints");
    } else {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( this_multipoint );
      sfheaders::bbox::calculate_bbox( bbox, im );
      sfc[i] = sfheaders::sfg::to_linestring( im );
    }
    break;
    }
    case REALSXP: {
      if( !Rf_isMatrix( this_multipoint ) ) {
      Rcpp::stop("sfheaders - expecting a matrix for multipoints");
    } else {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( this_multipoint );
      sfheaders::bbox::calculate_bbox( bbox, nm );
      sfc[i] = sfheaders::sfg::to_linestring( nm );
    }
    break;
    }
    default: {
      Rcpp::stop("sfheaders - unknown multipoint type");
    }
    }

    // need to calculate bbox and stuff
    // I could create one here,
  }
  return sfheaders::sfc::to_sfc( sfc, geom_type, geometry_types, bbox, epsg, proj4string, n_empty, precision );

}

// no subsetting to do; so just turn the object into a matrix;
inline SEXP to_linestrings(
    SEXP& x
) {
  Rcpp::List mp(1);
  mp[0] = sfheaders::shapes::get_mat( x );
  return to_linestrings( mp );
}


// no subsetting to do (except for columsn)
inline SEXP to_linestrings(
    SEXP& x,
    SEXP& geometry_cols
) {
  Rcpp::List mp(1);
  mp[0] = sfheaders::shapes::get_mat( x, geometry_cols );
  return to_linestrings( mp );
}

// if an 'id' col is supplied, it means we have many multipoints
// multipoint_id & point_id
inline SEXP to_linestrings(
    SEXP& x,
    SEXP& geometry_cols,
    SEXP& multipoint_id
) {
  // TODO - how to handle bbox
  if( Rf_isNull( geometry_cols ) && Rf_isNull( multipoint_id ) ) {
    return to_linestrings( x );

  } else if ( !Rf_isNull( geometry_cols ) && Rf_isNull( multipoint_id ) ) {

    // make the geometry cols all the other columns??
    return to_linestrings( x, geometry_cols );
  } else if ( Rf_isNull( geometry_cols ) && !Rf_isNull( multipoint_id ) ) {

    SEXP other_cols = sfheaders::utils::other_columns( x, multipoint_id );
    //return to_linestrings( x, other_cols, geometry_cols );
    Rcpp::List mp = sfheaders::shapes::get_listMat( x, other_cols, multipoint_id );
    return to_linestrings( mp );

  } else {
    // Rcpp::Rcout << "get list mat " << std::endl;
    Rcpp::List mp = sfheaders::shapes::get_listMat( x, geometry_cols, multipoint_id );
    return to_linestrings( mp );
  }

  return Rcpp::List::create(); // ??
}



} // sfc
} // sfheaders

#endif
