#ifndef R_SFHEADERS_SF_H
#define R_SFHEADERS_SF_H

#include <Rcpp.h>
#include "sfheaders/sf/point/sf_point.hpp"
#include "sfheaders/sf/multipoint/sf_multipoint.hpp"
#include "sfheaders/sf/linestring/sf_linestring.hpp"
#include "sfheaders/sf/multilinestring/sf_multilinestring.hpp"
#include "sfheaders/sf/polygon/sf_polygon.hpp"
#include "sfheaders/sf/multipolygon/sf_multipolygon.hpp"

namespace sfheaders {
namespace api {

  inline void get_list_column_index(
      SEXP& list_columns,
      Rcpp::IntegerVector& list_column_idx,
      SEXP& property_cols,  // only needs to be stringified IFF list_columns is a string?
      Rcpp::IntegerVector& property_idx
  ) {

    if( !Rf_isNull( list_columns ) ) {
      switch( TYPEOF( list_columns ) ) {
      case REALSXP: {}
      case INTSXP: {
        list_column_idx = Rcpp::as< Rcpp::IntegerVector >( list_columns );
        break;
      }
      case STRSXP: {
        Rcpp::StringVector str_list_columns = Rcpp::as< Rcpp::StringVector >( list_columns );
        Rcpp::StringVector str_property_cols = Rcpp::as< Rcpp::StringVector >( property_cols );
        Rcpp::IntegerVector idx = sfheaders::utils::where_is( str_list_columns, str_property_cols );
        list_column_idx = property_idx[ idx ];
        break;

      }
      default:{
        Rcpp::stop("sfheaders - unknown list-column type");
      }
      }
    }
  }

  inline SEXP to_sf(
    SEXP& obj,
    SEXP& geometry_columns,
    SEXP& multipoint_id,
    SEXP& linestring_id,
    SEXP& multilinestring_id,
    SEXP& polygon_id,
    SEXP& multipolygon_id,
    SEXP& list_columns,
    bool close,
    bool keep,
    std::string xyzm,
    const std::string sf_type
  ) {
      // TODO - Make the id_columns the correct type
      // then inside each if() condition, split it by polygon_id & linestring_id (for example)
      // assume the 0th index is the outer-most geometry
      // as this function will be called from R this is controllable.

    Rcpp::List sf_objs;

    // can I make the obj a data.frame here?
    // then can sort out all the column names as well

    // If numeric values are sent it; can I rely on them beign the same?
    // will the output 'df' remain un-sorted?
    // I think it will... right??....


    if( sf_type == "POINT" ) {
      sf_objs = sfheaders::sf::sf_point( obj, geometry_columns, keep, xyzm );
    } else if ( sf_type == "MULTIPOINT" ) {
      sf_objs = sfheaders::sf::sf_multipoint( obj, geometry_columns, multipoint_id, keep, xyzm );
    } else if ( sf_type == "LINESTRING" ) {
      sf_objs = sfheaders::sf::sf_linestring( obj, geometry_columns, linestring_id, keep, xyzm );
    } else if ( sf_type == "MULTILINESTRING" ) {
      sf_objs = sfheaders::sf::sf_multilinestring( obj, geometry_columns, multilinestring_id, linestring_id, keep, xyzm );
    } else if ( sf_type == "POLYGON" ) {
      sf_objs = sfheaders::sf::sf_polygon( obj, geometry_columns, polygon_id, linestring_id, xyzm, close, keep );
    } else if ( sf_type == "MULTIPOLYGON" ) {
      sf_objs = sfheaders::sf::sf_multipolygon( obj, geometry_columns, multipolygon_id, polygon_id, linestring_id, xyzm, close, keep );
    } else {
      Rcpp::stop("sfheaders - unknown sf type");
    }

    // if sf_objs doesn't contain any elements, it means it went directly through make_sf()
    if( !sf_objs.containsElementNamed("df") && !sf_objs.containsElementNamed("x") ) {
      return sf_objs;
    }
    // sf_objs is an object of either
    // 1. x, sfc, property_columns
    // 2. df, sfc, id_column, property_cols, row_idx, line_positions

    // previously each of the sf_ functions would call create_sf();
    // but now we can have SEXP list_columns
    // which we can use to fill lists
    //
    // need to know what type of object is list_columns (string or integer)
    // so we can subset the x / df
    //
    // list columns HAVE TO exist within property_columns (sf_objs[["property_cols"]])
    // so strings are OK.
    // integers?
    // integers HAVE to exist within property_idx (sf_objs[["property_idx"]] )
    // so IFF list_columns is an integerVector, then it corresponds

    //SEXP x = sf_objs["df"];

    SEXP property_cols = sf_objs[ "property_cols" ];
    Rcpp::List sfc = sf_objs["sfc"];
    Rcpp::IntegerMatrix line_positions = Rcpp::as< Rcpp::IntegerMatrix >( sf_objs["line_positions"] );
    Rcpp::IntegerVector property_idx = sf_objs[ "property_idx" ];

    Rcpp::String id_column;
    Rcpp::IntegerVector row_idx;
    Rcpp::IntegerVector list_column_idx;  // TODO - initialise as -1 ?? so its' never NULL and we only
    // need one 'create_sf()' function?
    Rcpp::StringVector str_property_cols;



    // need to 'exit early' if some of the properties don't exist
    if( sf_objs.containsElementNamed("x") ) {
      SEXP x = sf_objs["x"];
      get_list_column_index(
        list_columns, list_column_idx, property_cols, property_idx
      );
      return sfheaders::sf::create_sf( x, sfc, property_cols, list_column_idx, line_positions );
    }


    row_idx = sf_objs["row_idx"];

    str_property_cols = Rcpp::as< Rcpp::StringVector >( property_cols );

    if( sf_objs.containsElementNamed("id_column") ) {
      id_column = Rcpp::as< Rcpp::String >( sf_objs["id_column"] );
    }

    // this should give us list_column_idx, which is a subset (or all) of property_idx,
    // which can be passed into create_sf()
    // and checked iff property_idx %in% list_column_idx;
    // and if so, make it a list-column, rather than subset the first row.
    //Rcpp::Rcout << "list_columns: " << list_column_idx << std::endl;
    get_list_column_index(
      list_columns, list_column_idx, property_cols, property_idx
    );

    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( sf_objs["df"] );

    if( !sf_objs.containsElementNamed("id_column") ) {
      return sfheaders::sf::create_sf( df, sfc, str_property_cols, property_idx, list_column_idx, row_idx, line_positions );
    }

    return sfheaders::sf::create_sf(
      df, sfc, id_column, str_property_cols, property_idx, list_column_idx, row_idx, line_positions
      );
 }

  // TODO
  // write each of the rcpp_sf_xxx functions here, so they appropriately call the to_sf() code
  inline SEXP rcpp_sf_point( SEXP x, SEXP cols, bool keep, std::string xyzm ) {
    return to_sf( x, cols, R_NilValue, R_NilValue, R_NilValue, R_NilValue, R_NilValue, R_NilValue, false, keep, xyzm, "POINT" );
  }

  inline SEXP rcpp_sf_multipoint( SEXP x, SEXP cols, SEXP multipoint_id, bool keep, std::string xyzm ) {
    return to_sf( x, cols, multipoint_id, R_NilValue, R_NilValue, R_NilValue, R_NilValue, R_NilValue, false, keep, xyzm, "MULTIPOINT" );
  }

  inline SEXP rcpp_sf_linestring( SEXP x, SEXP cols, SEXP linestring_id, bool keep, std::string xyzm ) {
    return to_sf( x, cols, R_NilValue, linestring_id, R_NilValue, R_NilValue, R_NilValue, R_NilValue, false, keep, xyzm, "LINESTRING" );
  }

  inline SEXP rcpp_sf_multilinestring( SEXP x, SEXP cols, SEXP multilinestring_id, SEXP linestring_id, bool keep, std::string xyzm ) {
    return to_sf( x, cols, R_NilValue, linestring_id, multilinestring_id, R_NilValue, R_NilValue, R_NilValue, false, keep, xyzm, "MULTILINESTRING" );
  }

  inline SEXP rcpp_sf_polygon( SEXP x, SEXP cols, SEXP polygon_id, SEXP linestring_id, bool close, bool keep, std::string xyzm ) {
    return to_sf( x, cols, R_NilValue, linestring_id, R_NilValue, polygon_id, R_NilValue, R_NilValue, close, keep, xyzm, "POLYGON" );
  }

  inline SEXP rcpp_sf_multipolygon( SEXP x, SEXP cols, SEXP multipolygon_id, SEXP polygon_id, SEXP linestring_id, bool close, bool keep, std::string xyzm ) {
    return to_sf( x, cols, R_NilValue, linestring_id, R_NilValue, polygon_id, multipolygon_id, R_NilValue, close, keep, xyzm, "MULTIPOLYGON" );
  }


} // api
} // sfheaders


#endif
