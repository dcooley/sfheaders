#ifndef R_SFHEADERS_SFC_POLYGONS_H
#define R_SFHEADERS_SFC_POLYGONS_H

#include <Rcpp.h>
#include "sfheaders/sfg/polygon/sfg_polygon.hpp"
#include "sfheaders/sfc/bbox.hpp"
#include "sfheaders/sfc/sfc.hpp"


namespace sfheaders {
namespace sfc {

  inline SEXP sfc_polygon(
      Rcpp::IntegerMatrix& im
  ) {
    //
    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();

    std::string geom_type = "POLYGON";
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
    Rcpp::List ml = sfheaders::sfg::sfg_polygon( im );

    sfc[0] = ml;
    return sfheaders::sfc::to_sfc( sfc, geom_type, geometry_types, bbox, epsg, proj4string, n_empty, precision );
  }


  inline SEXP sfc_polygon(
      Rcpp::NumericMatrix& nm
  ) {
    //
    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();

    std::string geom_type = "POLYGON";
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
    Rcpp::List ml = sfheaders::sfg::sfg_polygon( nm );

    sfc[0] = ml;

    return sfheaders::sfc::to_sfc( sfc, geom_type, geometry_types, bbox, epsg, proj4string, n_empty, precision );
  }


  inline SEXP sfc_polygon(
      Rcpp::IntegerVector& iv
  ) {
    int n_col = iv.size();
    Rcpp::IntegerMatrix im(1, n_col);
    im(0, Rcpp::_ ) = iv;
    return sfc_polygon( im );
  }

  inline SEXP sfc_polygon(
      Rcpp::NumericVector& nv
  ) {
    int n_col = nv.size();
    Rcpp::NumericMatrix nm(1, n_col);
    nm(0, Rcpp::_ ) = nv;
    return sfc_polygon( nm );
  }

  inline SEXP sfc_polygon(
      Rcpp::List& lst
  ) {
    // iterate each 'sfg' and assign 'sfg' attributes

    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();

    std::string geom_type = "POLYGON";
    std::unordered_set< std::string > geometry_types{ geom_type };

    Rcpp::String epsg = NA_STRING;
    Rcpp::String proj4string = NA_STRING;
    int n_empty = 0;
    double precision = 0.0;

    size_t n_polygons = lst.size();
    // Rcpp::Rcout << "n_polygons: " << n_polygons << std::endl;
    Rcpp::List sfc( n_polygons );

    size_t i, j;

    for( i = 0; i < n_polygons; i++ ) {
      Rcpp::List sfgs = lst[i];
      size_t n_linestrings = sfgs.size();

      // Rcpp::Rcout << "n_linestrings: " << n_linestrings << std::endl;
      Rcpp::List ml( n_linestrings );

      for( j = 0; j < n_linestrings; j++ ) {

        SEXP this_linestring = sfgs[j];

        switch( TYPEOF( this_linestring ) ) {
        case INTSXP: {
          if( !Rf_isMatrix( this_linestring ) ) {
          Rcpp::stop("sfheaders - expecting a matrix for polygons");
        } else {
          Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( this_linestring );
          sfheaders::bbox::calculate_bbox( bbox, im );
          ml[j] = im;
        }
        break;
        }
        case REALSXP: {
          if( !Rf_isMatrix( this_linestring ) ) {
          Rcpp::stop("sfheaders - expecting a matrix for polygons");
        } else {
          Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( this_linestring );
          sfheaders::bbox::calculate_bbox( bbox, nm );
          ml[j] = nm;
        }
        break;
        }
        default: {
          Rcpp::stop("sfheaders - unknown polygon type");
        }
        }

      }
      sfc[i] = sfheaders::sfg::sfg_polygon( ml );

    }
    return sfheaders::sfc::to_sfc( sfc, geom_type, geometry_types, bbox, epsg, proj4string, n_empty, precision );

  }

  // no subsetting to do; so just turn the object into a matrix;
  inline SEXP sfc_polygon(
      SEXP& x
  ) {
    Rcpp::List ml(1);
    Rcpp::List sfc(1);
    ml[0] = sfheaders::shapes::get_mat( x );
    sfc[0] = ml;
    return sfc_polygon( sfc );
  }


  // no subsetting to do (except for columsn)
  inline SEXP sfc_polygon(
      SEXP& x,
      SEXP& geometry_cols
  ) {
    Rcpp::List mp(1);
    mp[0] = sfheaders::shapes::get_listMat( x, geometry_cols );
    return sfc_polygon( mp );
  }

  // if an 'id' col is supplied, it means we have many polygons
  // linestring_id & point_id
  inline SEXP sfc_polygon(
      SEXP& x,
      SEXP& geometry_cols,
      SEXP& polygon_id,
      SEXP& linestring_id
  ) {

    if( Rf_isNull( geometry_cols ) && Rf_isNull( linestring_id ) && Rf_isNull( polygon_id ) ) {
      return sfc_polygon( x );
    }

    // JUST polygon_id == each polygon is just one line
    // JSUT linestring_id == they are all the same polygon_id

    if ( ( Rf_isNull( geometry_cols ) &&  Rf_isNull( polygon_id ) && !Rf_isNull( linestring_id ) ) ) {
      // linestring is provided
      // so they are all the same MULTILINESTRING

      SEXP other_cols = sfheaders::utils::other_columns( x, linestring_id );

      // Rcpp::Rcout << "typeof( other_cols ) " << TYPEOF( other_cols ) << std::endl;
      // Rcpp::Rcout << "typeof( linestring_id ) " << TYPEOF( linestring_id ) << std::endl;
      //
      // Rcpp::Rcout << "linestring WITHOUT polygon" << std::endl;
      Rcpp::List lst(1);
      lst[0] = sfheaders::shapes::get_listMat( x, other_cols, linestring_id );
      return sfc_polygon( lst );
    }

    if ( ( Rf_isNull( geometry_cols ) && !Rf_isNull( polygon_id ) && Rf_isNull( linestring_id ) ) ) {
      // polygon is provided, so there is only one line per multiline
      SEXP other_cols = sfheaders::utils::other_columns( x, polygon_id );

      //Rcpp::stop("not working yet");
      Rcpp::List lst = sfheaders::shapes::get_listMat( x, other_cols, polygon_id );

      // each list element needs to be nested one level deeper
      size_t n = lst.size();
      Rcpp::List mls( n );
      size_t i;
      for( i = 0; i < n; i++ ) {
        Rcpp::List l(1);
        l[0] = lst[i];
        mls[i] = l;
      }
      //return lst;
      // Rcpp::Rcout << "lst.size() " << lst.size() << std::endl;
      // Rcpp::List mls( 1 );
      // mls[0] = lst;
      return sfc_polygon( mls );
    }

    if( Rf_isNull( geometry_cols ) && !Rf_isNull( linestring_id ) && !Rf_isNull( polygon_id ) ) {
      SEXP other_cols = sfheaders::utils::other_columns( x, linestring_id, polygon_id );

      return sfc_polygon( x, other_cols, polygon_id, linestring_id );
    }

    if ( !Rf_isNull( geometry_cols ) && Rf_isNull( linestring_id ) && Rf_isNull( polygon_id ) ) {
      // make the geometry cols all the other columns??
      return sfc_polygon( x, geometry_cols );
    }


    // if ( Rf_isNull( geometry_cols ) && !Rf_isNull( linestring_id ) ) {
    //   SEXP other_cols = sfheaders::utils::other_columns( x, linestring_id );
    //   //return sfc_polygon( x, other_cols, geometry_cols );
    //   Rcpp::List mp = sfheaders::shapes::get_listListMat( x, other_cols, polygon_id, linestring_id );
    //   return sfc_polygon( mp );
    // }

    if( !Rf_isNull( geometry_cols ) && !Rf_isNull( polygon_id ) && !Rf_isNull( linestring_id ) ) {
      // Rcpp::Rcout << "get list mat " << std::endl;
      Rcpp::List mp = sfheaders::shapes::get_listListMat( x, geometry_cols, polygon_id, linestring_id );
      return sfc_polygon( mp );
    }

    Rcpp::stop("sfheaders - polygon case not yet implemented");
    return Rcpp::List::create(); // ??
  }



} // sfc
} // sfheaders

#endif
