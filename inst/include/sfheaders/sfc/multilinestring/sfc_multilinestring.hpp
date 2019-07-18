#ifndef R_SFHEADERS_SFC_MULTILINESTRING_H
#define R_SFHEADERS_SFC_MULTILINESTRING_H

#include <Rcpp.h>
#include "sfheaders/sfc/sfc_attributes.hpp"
#include "sfheaders/sfg/multilinestring/sfg_multilinestring.hpp"
#include "sfheaders/sfc/bbox.hpp"
#include "sfheaders/sfc/z_range.hpp"
#include "sfheaders/sfc/m_range.hpp"

namespace sfheaders {
namespace sfc {

  inline SEXP sfc_multilinestring(
      Rcpp::IntegerMatrix& im
  ) {
    //
    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

    std::string geom_type = "MULTILINESTRING";
    std::unordered_set< std::string > geometry_types{ geom_type };

    Rcpp::String epsg = NA_STRING;
    Rcpp::String proj4string = NA_STRING;
    int n_empty = 0;
    double precision = 0.0;

    size_t n_col = im.ncol();
    //size_t i;
    Rcpp::List sfc( 1 );
    // need to loop through ad get the bbox
    sfheaders::bbox::calculate_bbox( bbox, im );

    if( n_col > 2 ) {
      sfheaders::zm::calculate_z_range( z_range, im );
      if( n_col > 3 ) {
        sfheaders::zm::calculate_m_range( m_range, im );
      }
    }

    Rcpp::List ml = sfheaders::sfg::sfg_multilinestring( im );

    sfc[0] = ml;
    return sfheaders::sfc::create_sfc( sfc, geom_type, geometry_types, bbox, z_range, m_range, epsg, proj4string, n_empty, precision );
  }


  inline SEXP sfc_multilinestring(
      Rcpp::NumericMatrix& nm
  ) {
    //
    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

    std::string geom_type = "MULTILINESTRING";
    std::unordered_set< std::string > geometry_types{ geom_type };

    Rcpp::String epsg = NA_STRING;
    Rcpp::String proj4string = NA_STRING;
    int n_empty = 0;
    double precision = 0.0;

    size_t n_col = nm.ncol();
    //size_t i;
    Rcpp::List sfc( 1 );

    // need to loop through ad get the bbox
    sfheaders::bbox::calculate_bbox( bbox, nm );

    if( n_col > 2 ) {
      sfheaders::zm::calculate_z_range( z_range, nm );
      if( n_col > 3 ) {
        sfheaders::zm::calculate_m_range( m_range, nm );
      }
    }

    Rcpp::List ml = sfheaders::sfg::sfg_multilinestring( nm );

    sfc[0] = ml;

    return sfheaders::sfc::create_sfc( sfc, geom_type, geometry_types, bbox, z_range, m_range, epsg, proj4string, n_empty, precision );
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
    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range();
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range();

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

          size_t n_col = im.ncol();
          if( n_col > 2 ) {
            sfheaders::zm::calculate_z_range( z_range, im );
            if( n_col > 3 ) {
              sfheaders::zm::calculate_m_range( m_range, im );
            }
          }

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

          size_t n_col = nm.ncol();
          if( n_col > 2 ) {
            sfheaders::zm::calculate_z_range( z_range, nm );
            if( n_col > 3 ) {
              sfheaders::zm::calculate_m_range( m_range, nm );
            }
          }

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
    return sfheaders::sfc::create_sfc( sfc, geom_type, geometry_types, bbox, z_range, m_range, epsg, proj4string, n_empty, precision );

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

    if( Rf_isNull( geometry_cols ) && Rf_isNull( linestring_id ) && Rf_isNull( multilinestring_id ) ) {
      return sfc_multilinestring( x );
    }

    // JUST multilinestring_id == each multilinestring is just one line
    // JSUT linestring_id == they are all the same multilinestring_id

    if ( ( Rf_isNull( geometry_cols ) &&  Rf_isNull( multilinestring_id ) && !Rf_isNull( linestring_id ) ) ) {
      // linestring is provided
      // so they are all the same MULTILINESTRING

      SEXP other_cols = sfheaders::utils::other_columns( x, linestring_id );

      // Rcpp::Rcout << "typeof( other_cols ) " << TYPEOF( other_cols ) << std::endl;
      // Rcpp::Rcout << "typeof( linestring_id ) " << TYPEOF( linestring_id ) << std::endl;
      //
      // Rcpp::Rcout << "linestring WITHOUT multilinestring" << std::endl;
      Rcpp::List lst(1);
      lst[0] = sfheaders::shapes::get_listMat( x, other_cols, linestring_id );
      return sfc_multilinestring( lst );
    }

    if ( ( Rf_isNull( geometry_cols ) && !Rf_isNull( multilinestring_id ) && Rf_isNull( linestring_id ) ) ) {
      // multilinestring is provided, so there is only one line per multiline
      SEXP other_cols = sfheaders::utils::other_columns( x, multilinestring_id );

      //Rcpp::stop("not working yet");
      Rcpp::List lst = sfheaders::shapes::get_listMat( x, other_cols, multilinestring_id );

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
      return sfc_multilinestring( mls );
    }

    if( Rf_isNull( geometry_cols ) && !Rf_isNull( linestring_id ) && !Rf_isNull( multilinestring_id ) ) {
      SEXP other_cols = sfheaders::utils::other_columns( x, linestring_id, multilinestring_id );

      return sfc_multilinestring( x, other_cols, multilinestring_id, linestring_id );
    }

    if ( !Rf_isNull( geometry_cols ) && Rf_isNull( linestring_id ) && Rf_isNull( multilinestring_id ) ) {
      // make the geometry cols all the other columns??
      return sfc_multilinestring( x, geometry_cols );
    }


    // if ( Rf_isNull( geometry_cols ) && !Rf_isNull( linestring_id ) ) {
    //   SEXP other_cols = sfheaders::utils::other_columns( x, linestring_id );
    //   //return sfc_multilinestring( x, other_cols, geometry_cols );
    //   Rcpp::List mp = sfheaders::shapes::get_listListMat( x, other_cols, multilinestring_id, linestring_id );
    //   return sfc_multilinestring( mp );
    // }

    if( !Rf_isNull( geometry_cols ) && !Rf_isNull( multilinestring_id ) && !Rf_isNull( linestring_id ) ) {
      // Rcpp::Rcout << "get list mat " << std::endl;
      Rcpp::List mp = sfheaders::shapes::get_listListMat( x, geometry_cols, multilinestring_id, linestring_id );
      return sfc_multilinestring( mp );
    }

    Rcpp::stop("sfheaders - multilinestring case not yet implemented");
    return Rcpp::List::create(); // ??
  }



} // sfc
} // sfheaders

#endif
