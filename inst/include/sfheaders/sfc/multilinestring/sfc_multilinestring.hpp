#ifndef R_SFHEADERS_SFC_MULTILINESTRINGS_H
#define R_SFHEADERS_SFC_MULTILINESTRINGS_H

#include <Rcpp.h>
#include "sfheaders/sfg/multilinestring/sfg_multilinestring.hpp"
#include "sfheaders/shapes/mat/mat.hpp"
#include "sfheaders/shapes/list_mat/list_mat.hpp"
#include "sfheaders/shapes/list_list_mat/list_list_mat.hpp"
#include "sfheaders/bbox.hpp"
#include "sfheaders/sfc/sfc.hpp"


namespace sfheaders {
namespace sfc {

inline SEXP sfc_multilinestring(
    Rcpp::IntegerMatrix& im
) {
  //
  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();

  std::string geom_type = "MULTILINESTRING";
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
  Rcpp::List ml = sfheaders::sfg::sfg_multilinestring( im );

  sfc[0] = ml;
  return sfheaders::sfc::to_sfc( sfc, geom_type, geometry_types, bbox, epsg, proj4string, n_empty, precision );
}


inline SEXP sfc_multilinestring(
    Rcpp::NumericMatrix& nm
) {
  //
  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();

  std::string geom_type = "MULTILINESTRING";
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
  Rcpp::List ml = sfheaders::sfg::sfg_multilinestring( nm );

  sfc[0] = ml;

  return sfheaders::sfc::to_sfc( sfc, geom_type, geometry_types, bbox, epsg, proj4string, n_empty, precision );
}


inline SEXP sfc_multilinestring(
    Rcpp::IntegerVector& iv
) {
  int n_col = iv.size();
  Rcpp::IntegerMatrix im(1, n_col);
  im(0, Rcpp::_ ) = iv;
  return sfc_multilinestring( im );
}

inline SEXP sfc_multilinestring(
    Rcpp::NumericVector& nv
) {
  int n_col = nv.size();
  Rcpp::NumericMatrix nm(1, n_col);
  nm(0, Rcpp::_ ) = nv;
  return sfc_multilinestring( nm );
}

inline SEXP sfc_multilinestring(
    Rcpp::List& lst
) {
  // iterate each 'sfg' and assign 'sfg' attributes

  Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();

  std::string geom_type = "MULTILINESTRING";
  std::unordered_set< std::string > geometry_types{ geom_type };

  Rcpp::String epsg = NA_STRING;
  Rcpp::String proj4string = NA_STRING;
  int n_empty = 0;
  double precision = 0.0;

  size_t n_multilinestrings = lst.size();
  // Rcpp::Rcout << "n_multilinestrings: " << n_multilinestrings << std::endl;
  Rcpp::List sfc( n_multilinestrings );

  size_t i, j;

  for( i = 0; i < n_multilinestrings; i++ ) {
    Rcpp::List sfgs = lst[i];
    size_t n_linestrings = sfgs.size();

    // Rcpp::Rcout << "n_linestrings: " << n_linestrings << std::endl;
    Rcpp::List ml( n_linestrings );

    for( j = 0; j < n_linestrings; j++ ) {

      SEXP this_linestring = sfgs[j];

      // int tp = TYPEOF( this_linestring );
      // Rcpp::Rcout << "tp: " << tp << std::endl;

      switch( TYPEOF( this_linestring ) ) {
      case INTSXP: {
        if( !Rf_isMatrix( this_linestring ) ) {
        Rcpp::stop("sfheaders - expecting a matrix for multilinestrings");
      } else {
        Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( this_linestring );
        sfheaders::bbox::calculate_bbox( bbox, im );
        ml[j] = im;
      }
      break;
      }
      case REALSXP: {
        if( !Rf_isMatrix( this_linestring ) ) {
        Rcpp::stop("sfheaders - expecting a matrix for multilinestrings");
      } else {
        Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( this_linestring );
        sfheaders::bbox::calculate_bbox( bbox, nm );
        ml[j] = nm;
      }
      break;
      }
      default: {
        Rcpp::stop("sfheaders - unknown multilinestring type");
      }
      }

    }
    sfc[i] = sfheaders::sfg::sfg_multilinestring( ml );

  }
  return sfheaders::sfc::to_sfc( sfc, geom_type, geometry_types, bbox, epsg, proj4string, n_empty, precision );

}

// no subsetting to do; so just turn the object into a matrix;
inline SEXP sfc_multilinestring(
    SEXP& x
) {
  Rcpp::List ml(1);
  Rcpp::List sfc(1);
  ml[0] = sfheaders::shapes::get_mat( x );
  sfc[0] = ml;
  return sfc_multilinestring( sfc );
}


// no subsetting to do (except for columsn)
inline SEXP sfc_multilinestring(
    SEXP& x,
    SEXP& geometry_cols
) {
  Rcpp::List mp(1);
  mp[0] = sfheaders::shapes::get_listMat( x, geometry_cols );
  return sfc_multilinestring( mp );
}

// if an 'id' col is supplied, it means we have many multilinestrings
// linestring_id & point_id
inline SEXP sfc_multilinestring(
    SEXP& x,
    SEXP& geometry_cols,
    SEXP& multilinestring_id,
    SEXP& linestring_id
) {
  // TODO - how to handle bbox

  if( ( Rf_isNull( multilinestring_id ) && !Rf_isNull( linestring_id ) ) ||
      ( !Rf_isNull( multilinestring_id ) && Rf_isNull( linestring_id ) )  ) {
    Rcpp::stop("sfheaders - multilinestring AND linestring ids are required");
  }

  if( Rf_isNull( geometry_cols ) && Rf_isNull( linestring_id ) && Rf_isNull( multilinestring_id ) ) {
    return sfc_multilinestring( x );

  } else if ( !Rf_isNull( geometry_cols ) && Rf_isNull( linestring_id ) ) {

    // make the geometry cols all the other columns??
    return sfc_multilinestring( x, geometry_cols );
  } else if ( Rf_isNull( geometry_cols ) && !Rf_isNull( linestring_id ) ) {

    SEXP other_cols = sfheaders::utils::other_columns( x, linestring_id );
    //return sfc_multilinestring( x, other_cols, geometry_cols );
    Rcpp::List mp = sfheaders::shapes::get_listListMat( x, other_cols, multilinestring_id, linestring_id );
    return sfc_multilinestring( mp );

  } else {
    // Rcpp::Rcout << "get list mat " << std::endl;
    Rcpp::List mp = sfheaders::shapes::get_listListMat( x, geometry_cols, multilinestring_id, linestring_id );
    return sfc_multilinestring( mp );
  }

  return Rcpp::List::create(); // ??
}



} // sfc
} // sfheaders

#endif
