#ifndef R_SFHEADERS_SFC_MULTIPOLYGON_H
#define R_SFHEADERS_SFC_MULTIPOLYGON_H

#include <Rcpp.h>
#include "sfheaders/sfc/sfc_attributes.hpp"
#include "sfheaders/sfg/multipolygon/sfg_multipolygon.hpp"
#include "sfheaders/sfc/bbox.hpp"


namespace sfheaders {
namespace sfc {

  inline SEXP sfc_multipolygon(
      Rcpp::IntegerMatrix& im
  ) {
    //
    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();

    std::string geom_type = "MULTIPOLYGON";
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
    Rcpp::List ml = sfheaders::sfg::sfg_multipolygon( im );

    sfc[0] = ml;
    return sfheaders::sfc::create_sfc( sfc, geom_type, geometry_types, bbox, epsg, proj4string, n_empty, precision );
  }


  inline SEXP sfc_multipolygon(
      Rcpp::NumericMatrix& nm
  ) {
    //
    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();

    std::string geom_type = "MULTIPOLYGON";
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
    Rcpp::List ml = sfheaders::sfg::sfg_multipolygon( nm );

    sfc[0] = ml;

    return sfheaders::sfc::create_sfc( sfc, geom_type, geometry_types, bbox, epsg, proj4string, n_empty, precision );
  }


  inline SEXP sfc_multipolygon(
      Rcpp::IntegerVector& iv
  ) {
    int n_col = iv.size();
    Rcpp::IntegerMatrix im(1, n_col);
    im(0, Rcpp::_ ) = iv;
    return sfc_multipolygon( im );
  }

  inline SEXP sfc_multipolygon(
      Rcpp::NumericVector& nv
  ) {
    int n_col = nv.size();
    Rcpp::NumericMatrix nm(1, n_col);
    nm(0, Rcpp::_ ) = nv;
    return sfc_multipolygon( nm );
  }

  inline SEXP sfc_multipolygon(
      Rcpp::List& lst
  ) {
    // iterate each 'sfg' and assign 'sfg' attributes

    Rcpp::NumericVector bbox = sfheaders::bbox::start_bbox();

    std::string geom_type = "MULTIPOLYGON";
    std::unordered_set< std::string > geometry_types{ geom_type };

    Rcpp::String epsg = NA_STRING;
    Rcpp::String proj4string = NA_STRING;
    int n_empty = 0;
    double precision = 0.0;

    size_t n_multipolygons = lst.size();

    Rcpp::List sfc( n_multipolygons );

    size_t i, j, k;

    for( i = 0; i < n_multipolygons; i++ ) {
      Rcpp::List sfgs = lst[i];
      size_t n_polygons = sfgs.size();

      Rcpp::List pl( n_polygons );

      for( j = 0; j < n_polygons; j++ ) {

        Rcpp::List ls = sfgs[j];
        size_t n_linestrings = ls.size();

        Rcpp::List l( n_linestrings );

        for( k = 0; k < n_linestrings; k++ ) {
          SEXP this_linestring = ls[k];

          switch( TYPEOF( this_linestring ) ) {
          case INTSXP: {
            if( !Rf_isMatrix( this_linestring ) ) {
            Rcpp::stop("sfheaders - expecting a matrix for polygons");
          } else {
            Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( this_linestring );
            sfheaders::bbox::calculate_bbox( bbox, im );
            l[k] = im;
          }
          break;
          }
          case REALSXP: {
            if( !Rf_isMatrix( this_linestring ) ) {
            Rcpp::stop("sfheaders - expecting a matrix for polygons");
          } else {
            Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( this_linestring );
            sfheaders::bbox::calculate_bbox( bbox, nm );
            l[k] = nm;
          }
          break;
          }
          default: {
            Rcpp::stop("sfheaders - unknown multipolygon type");
          }
          }
        }
        pl[j] = ls;
      }

      sfc[i] = sfheaders::sfg::sfg_multipolygon( pl );

    }
    return sfheaders::sfc::create_sfc( sfc, geom_type, geometry_types, bbox, epsg, proj4string, n_empty, precision );
  }


  // no subsetting to do; so just turn the object into a matrix;
  inline SEXP sfc_multipolygon(
      SEXP& x
  ) {
    Rcpp::List p(1);
    Rcpp::List mp(1);
    Rcpp::List sfc(1);
    p[0] = sfheaders::shapes::get_mat( x );
    mp[0] = p;
    sfc[0] = mp;
    return sfc_multipolygon( sfc );
  }


  // no subsetting to do (except for columsn)
  inline SEXP sfc_multipolygon(
      SEXP& x,
      SEXP& geometry_cols
  ) {
    Rcpp::List p(1);
    Rcpp::List mp(1);
    p[0] = sfheaders::shapes::get_listMat( x, geometry_cols );
    mp[0] = p;
    return sfc_multipolygon( mp );
  }

  // if an 'id' col is supplied, it means we have many polygons
  // linestring_id & point_id
  inline SEXP sfc_multipolygon(
      SEXP& x,
      SEXP& geometry_cols,
      SEXP& multipolygon_id,
      SEXP& polygon_id,
      SEXP& linestring_id
  ) {

    if( Rf_isNull( geometry_cols ) &&
        Rf_isNull( linestring_id ) &&
        Rf_isNull( polygon_id ) &&
        Rf_isNull( multipolygon_id) ) {
      return sfc_multipolygon( x );
    }

    // JUST polygon_id == each polygon is just one line
    // JSUT linestring_id == they are all the same polygon_id

    if ( ( Rf_isNull( geometry_cols ) &&
         Rf_isNull( multipolygon_id ) &&
         !Rf_isNull( polygon_id ) &&
         !Rf_isNull( linestring_id ) )
    ) {

      // polygon and linestring is provided
      // so they are all the same MULTIPOLYGON

      SEXP other_cols = sfheaders::utils::other_columns( x, polygon_id, linestring_id );

      Rcpp::List lst(1);
      lst[0] = sfheaders::shapes::get_listListMat( x, other_cols, polygon_id, linestring_id );
      return sfc_multipolygon( lst );
    }

    if ( ( Rf_isNull( geometry_cols ) &&
         !Rf_isNull( multipolygon_id ) &&
         !Rf_isNull( polygon_id ) &&
         !Rf_isNull( linestring_id ) )
    ) {

      // polygon and linestring is provided
      // so they are all the same MULTIPOLYGON

      SEXP other_cols = sfheaders::utils::other_columns( x, multipolygon_id, polygon_id, linestring_id );

      Rcpp::List lst = sfheaders::shapes::get_listListMat( x, other_cols, multipolygon_id, polygon_id, linestring_id );
      return sfc_multipolygon( lst );
    }

    if(
      Rf_isNull( geometry_cols ) &&
        !Rf_isNull( multipolygon_id ) &&
        !Rf_isNull( polygon_id ) &&
        Rf_isNull( linestring_id )
    ) {
      SEXP other_cols = sfheaders::utils::other_columns( x, multipolygon_id, polygon_id );
      Rcpp::List lst = sfheaders::shapes::get_listListMat( x, other_cols, multipolygon_id, polygon_id );

      size_t n = lst.size();
      Rcpp::List mpl( n );
      size_t i;
      for( i = 0; i < n; i++ ) {
        Rcpp::List l1(1);
        l1[0] = lst[i];
        mpl[i] = l1;
      }
      return sfc_multipolygon( mpl );
    }

    if( ( Rf_isNull( geometry_cols ) &&
        !Rf_isNull( multipolygon_id ) &&
        Rf_isNull( polygon_id ) &&
        Rf_isNull( linestring_id )
    ) ) {
      // multipolygon_id provided, but not the others
      // so there is only only polygon per multipolygon
      SEXP other_cols = sfheaders::utils::other_columns( x, multipolygon_id );

      Rcpp::List lst = sfheaders::shapes::get_listMat( x, other_cols, multipolygon_id );

      size_t n = lst.size();
      Rcpp::List mpl( n );
      size_t i;
      for( i = 0; i < n; i++ ) {
        Rcpp::List l1(1);
        Rcpp::List l2(1);
        l2[0] = lst[i];
        l1[0] = l2;
        mpl[i] = l1;
      }
      return sfc_multipolygon( mpl );
    }

    if ( !Rf_isNull( geometry_cols ) &&
         Rf_isNull( linestring_id ) &&
         Rf_isNull( polygon_id ) &&
         Rf_isNull( multipolygon_id )
      ) {
      // make the geometry cols all the other columns??
      return sfc_multipolygon( x, geometry_cols );
    }

    if(
      !Rf_isNull( geometry_cols ) &&
        Rf_isNull( multipolygon_id ) &&
        !Rf_isNull( polygon_id ) &&
        !Rf_isNull( linestring_id )
      ) {

      Rcpp::List mp = sfheaders::shapes::get_listListMat( x, geometry_cols, polygon_id, linestring_id );
      Rcpp::List mpl(1);
      mpl[0] = mp;
      return sfc_multipolygon( mpl );
    }

    if(
      !Rf_isNull( geometry_cols ) &&
        Rf_isNull( multipolygon_id ) &&
        !Rf_isNull( polygon_id ) &&
        Rf_isNull( linestring_id )
    ) {

      Rcpp::List mp = sfheaders::shapes::get_listMat( x, geometry_cols, polygon_id );
      Rcpp::List l1(1);
      Rcpp::List l2(1);
      l1[0] = mp;
      l2[0] = l1;
      return sfc_multipolygon( l2 );
    }

    if(
      !Rf_isNull( geometry_cols ) &&
        Rf_isNull( multipolygon_id ) &&
        Rf_isNull( polygon_id ) &&
        !Rf_isNull( linestring_id )
    ) {

      Rcpp::List mp = sfheaders::shapes::get_listMat( x, geometry_cols, linestring_id );
      Rcpp::List l1(1);
      Rcpp::List l2(1);
      l1[0] = mp;
      l2[0] = l1;
      return sfc_multipolygon( l2 );
    }

    if( !Rf_isNull( geometry_cols ) &&
        !Rf_isNull( multipolygon_id ) &&
        !Rf_isNull( polygon_id ) &&
        !Rf_isNull( linestring_id )
        ) {

      Rcpp::List mp = sfheaders::shapes::get_listListMat( x, geometry_cols, multipolygon_id, polygon_id, linestring_id );
      return sfc_multipolygon( mp );
    }

    Rcpp::stop("sfheaders - multipolygon case not yet implemented");
    return Rcpp::List::create(); // ??
  }


  // inline SEXP sfc_multipolygon(
  //   Rcpp::NumericVector x,
  //   Rcpp::NumericVector y,
  //   Rcpp::NumericVector z = R_NilValue,
  //   Rcpp::NumericVector m = R_NilValue,
  //   Rcpp::NumericVector multipolygon_id = R_NilValue,
  //   Rcpp::NumericVector polygon_id = R_NilValue,
  //   Rcpp::NumericVector linestring_id = R_NilValue
  // ) {
  //   if( Rf_isNull( x ) || Rf_isNull( y ) ) {
  //     Rcpp::stop("sfheaders - x and y columns required");
  //   }
  //
  //   Rcpp::Rcout << "inside:" << std::endl;
  //
  //   SEXP multipolygon_id_col = R_NilValue;
  //   SEXP polygon_id_col = R_NilValue;
  //   SEXP linestring_id_col = R_NilValue;
  //
  //   int n_cols = 2;
  //   Rcpp::StringVector sv_geometry_columns{"x","y","z","m"};
  //   Rcpp::StringVector sv_id_columns{"multipolygon_id","polygon_id","linestring_id"};
  //   std::vector< std::string > columns;
  //   columns.push_back("x");
  //   columns.push_back("y");
  //
  //   if( Rf_isNull( z ) && !Rf_isNull( m ) ) {
  //     Rcpp::stop("sfheaders - expecting z if m is provided");
  //   }
  //
  //   int pos;
  //
  //   if( !Rf_isNull( z ) ) {
  //     n_cols++;
  //     columns.push_back("z");
  //     if( !Rf_isNull( m ) ) {
  //       n_cols++;
  //       columns.push_back("m");
  //     } else {
  //       pos = sfheaders::utils::where_is( "m", sv_geometry_columns );
  //       sv_geometry_columns.erase( pos );
  //     }
  //   } else {
  //     pos = sfheaders::utils::where_is( "m", sv_geometry_columns );
  //     sv_geometry_columns.erase( pos );
  //     pos = sfheaders::utils::where_is( "z", sv_geometry_columns );
  //     sv_geometry_columns.erase( pos );
  //   }
  //
  //   if( !Rf_isNull( linestring_id ) ) {
  //     n_cols++;
  //     columns.push_back("linestring_id");
  //     linestring_id_col = Rcpp::StringVector("linestring_id");
  //   } else {
  //     pos = sfheaders::utils::where_is( "linestring_id", sv_id_columns );
  //     sv_id_columns.erase( pos );
  //   }
  //
  //   if( !Rf_isNull( polygon_id ) ) {
  //     n_cols++;
  //     columns.push_back("polygon_id");
  //     polygon_id_col = Rcpp::StringVector("polygon_id");
  //   } else {
  //     pos = sfheaders::utils::where_is( "polygon_id", sv_id_columns );
  //     sv_id_columns.erase( pos );
  //   }
  //
  //   if( !Rf_isNull( multipolygon_id ) ) {
  //     n_cols++;
  //     columns.push_back("multipolygon_id");
  //     multipolygon_id_col = Rcpp::StringVector("multipolygon_id");
  //   } else {
  //     pos = sfheaders::utils::where_is( "multipolygon_id", sv_id_columns );
  //     sv_id_columns.erase( pos );
  //   }
  //
  //   Rcpp::List lst( n_cols );
  //   int i;
  //   for( i = 0; i < n_cols; i++ ) {
  //     std::string this_col = columns[i];
  //     if( this_col == "x" ) {
  //       lst[i] = x;
  //     } else if ( this_col == "y" ) {
  //       lst[i] = y;
  //     } else if ( this_col == "z" ) {
  //       lst[i] = z;
  //     } else if ( this_col == "m" ) {
  //       lst[i] = m;
  //     } else if ( this_col == "multipolygon_id" ) {
  //       lst[i] = multipolygon_id;
  //     } else if ( this_col == "polygon_id" ) {
  //       lst[i] = polygon_id;
  //     } else if ( this_col == "linestring_id" ) {
  //       lst[i] = linestring_id;
  //     }
  //   }
  //
  //   lst.names() = columns;
  //   Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( lst );
  //   SEXP obj = df;
  //   SEXP geometry_columns = sv_geometry_columns;
  //
  //   return sfc_multipolygon(
  //     obj, geometry_columns, multipolygon_id_col, polygon_id_col, linestring_id_col
  //   );
  //
  // }

} // sfc
} // sfheaders

#endif
