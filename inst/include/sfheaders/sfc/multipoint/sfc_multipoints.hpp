#ifndef R_SFHEADERS_SFC_MULTIPOINTS_H
#define R_SFHEADERS_SFC_MULTIPOINTS_H

#include <Rcpp.h>
#include "sfheaders/sfg/multipoint/sfg_multipoint.hpp"
//#include "sfheaders/shapes/list_mat/list_mat.hpp"
#include "sfheaders/shapes/list_list_mat/list_list_mat.hpp"
#include "sfheaders/bbox.hpp"
#include "sfheaders/sfc/sfc.hpp"


namespace sfheaders {
namespace sfc {

  inline SEXP to_multipoints(
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

    size_t n_col = im.ncol();
    size_t i;
    Rcpp::List sfc( 1 );

    // need to loop through ad get the bbox
    sfheaders::bbox::calculate_bbox( bbox, im );
    Rcpp::IntegerMatrix mp = sfheaders::sfg::to_multipoint( im );

    sfc[0] = mp;
    return sfheaders::sfc::to_sfc( sfc, geom_type, geometry_types, bbox, epsg, proj4string, n_empty, precision );
  }


  inline SEXP to_multipoints(
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

    size_t n_col = nm.ncol();
    size_t i;
    Rcpp::List sfc( 1 );

    // need to loop through ad get the bbox
    sfheaders::bbox::calculate_bbox( bbox, nm );
    Rcpp::NumericMatrix mp = sfheaders::sfg::to_multipoint( nm );

    sfc[0] = mp;

    return sfheaders::sfc::to_sfc( sfc, geom_type, geometry_types, bbox, epsg, proj4string, n_empty, precision );
  }


  inline SEXP to_multipoints(
      Rcpp::IntegerVector& iv
  ) {
    int n_col = iv.size();
    Rcpp::IntegerMatrix im(1, n_col);
    im(0, Rcpp::_ ) = iv;
    return to_multipoints( im );
  }

  inline SEXP to_multipoints(
    Rcpp::NumericVector& nv
  ) {
    int n_col = nv.size();
    Rcpp::NumericMatrix nm(1, n_col);
    nm(0, Rcpp::_ ) = nv;
    return to_multipoints( nm );
  }

  inline SEXP to_multipoints(
      Rcpp::List& sfc
  ) {
    // iterate each 'sfg' and assign 'sfg' attributes
    size_t n_multipoints = sfc.size();
    size_t i;
    for( i = 0; i < n_multipoints; i++ ) {
      SEXP this_multipoint = sfc[i];
      sfc[i] = sfheaders::sfg::to_multipoint( this_multipoint ); // sets the attributes
      // need to calculate bbox and stuff
      // I could create one here,
    }

  }

  inline SEXP to_multipoints(
    SEXP& x
  ) {

  }

  inline SEXP to_multipoints(
    SEXP& x,
    SEXP& geometry_cols
  ) {

  }

  // if an 'id' col is supplied, it means we have many multipoints
  // multipoint_id & point_id
  inline SEXP to_multipoints(
    SEXP& x,
    SEXP& geometry_cols,
    SEXP& multipoint_id
  ) {
    // TODO - how to handle bbox
    Rcpp::List mp = sfheaders::shapes::get_listMat( x, geometry_cols, multipoint_id );
    return to_multipoints( mp );
  }



} // sfc
} // sfheaders

#endif
