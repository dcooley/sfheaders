#ifndef R_SFHEADERS_SFC_MULTIPOINTS_H
#define R_SFHEADERS_SFC_MULTIPOINTS_H

#include <Rcpp.h>
#include "sfheaders/sfg/multipoint/sfg_multipoint.hpp"
#include "sfheaders/sfc/bbox.hpp"
#include "sfheaders/sfc/sfc.hpp"

namespace sfheaders {
namespace sfc {

  inline SEXP sfc_multipoint(
      Rcpp::IntegerMatrix& im
  ) {
    //
    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();

    std::string geom_type = "MULTIPOINT";
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
    Rcpp::IntegerMatrix mp = sfheaders::sfg::sfg_multipoint( im );

    sfc[0] = mp;
    return sfheaders::sfc::to_sfc( sfc, geom_type, geometry_types, bbox, epsg, proj4string, n_empty, precision );
  }


  inline SEXP sfc_multipoint(
    Rcpp::NumericMatrix& nm
  ) {
    //
    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();

    std::string geom_type = "MULTIPOINT";
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
    Rcpp::NumericMatrix mp = sfheaders::sfg::sfg_multipoint( nm );

    sfc[0] = mp;

    return sfheaders::sfc::to_sfc( sfc, geom_type, geometry_types, bbox, epsg, proj4string, n_empty, precision );
  }


  inline SEXP sfc_multipoint(
      Rcpp::IntegerVector& iv
  ) {
    int n_col = iv.size();
    Rcpp::IntegerMatrix im(1, n_col);
    im(0, Rcpp::_ ) = iv;
    return sfc_multipoint( im );
  }

  inline SEXP sfc_multipoint(
    Rcpp::NumericVector& nv
  ) {
    int n_col = nv.size();
    Rcpp::NumericMatrix nm(1, n_col);
    nm(0, Rcpp::_ ) = nv;
    return sfc_multipoint( nm );
  }

  inline SEXP sfc_multipoint(
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
        sfc[i] = sfheaders::sfg::sfg_multipoint( im );
      }
      break;
      }
      case REALSXP: {
      if( !Rf_isMatrix( this_multipoint ) ) {
        Rcpp::stop("sfheaders - expecting a matrix for multipoints");
      } else {
        Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( this_multipoint );
        sfheaders::bbox::calculate_bbox( bbox, nm );
        sfc[i] = sfheaders::sfg::sfg_multipoint( nm );
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
  inline SEXP sfc_multipoint(
    SEXP& x
  ) {
    Rcpp::List mp(1);
    mp[0] = sfheaders::shapes::get_mat( x );
    return sfc_multipoint( mp );
  }


  // no subsetting to do (except for columsn)
  inline SEXP sfc_multipoint(
    SEXP& x,
    SEXP& geometry_cols
  ) {
    sfheaders::utils::geometry_column_check( geometry_cols );
    Rcpp::List mp(1);
    mp[0] = sfheaders::shapes::get_mat( x, geometry_cols );
    return sfc_multipoint( mp );
  }

  // if an 'id' col is supplied, it means we have many multipoints
  // multipoint_id & point_id
  inline SEXP sfc_multipoint(
    SEXP& x,
    SEXP& geometry_cols,
    SEXP& multipoint_id
  ) {
    // TODO - how to handle bbox
    if( Rf_isNull( geometry_cols ) && Rf_isNull( multipoint_id ) ) {
      return sfc_multipoint( x );

    } else if ( !Rf_isNull( geometry_cols ) && Rf_isNull( multipoint_id ) ) {
      sfheaders::utils::geometry_column_check( geometry_cols );

      return sfc_multipoint( x, geometry_cols );
    } else if ( Rf_isNull( geometry_cols ) && !Rf_isNull( multipoint_id ) ) {

      SEXP other_cols = sfheaders::utils::other_columns( x, multipoint_id );
      sfheaders::utils::geometry_column_check( other_cols );

      Rcpp::List mp = sfheaders::shapes::get_listMat( x, other_cols, multipoint_id );
      return sfc_multipoint( mp );

    } else {
      Rcpp::List mp = sfheaders::shapes::get_listMat( x, geometry_cols, multipoint_id );
      return sfc_multipoint( mp );
    }

    return Rcpp::List::create(); // ??
  }



} // sfc
} // sfheaders

#endif
