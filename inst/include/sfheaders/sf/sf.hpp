#ifndef R_SFHEADERS_SF_H
#define R_SFHEADERS_SF_H

#include <Rcpp.h>
#include "sfheaders/sf/point/sf_point.hpp"
#include "sfheaders/sf/multipoint/sf_multipoint.hpp"
#include "sfheaders/sf/linestring/sf_linestring.hpp"
#include "sfheaders/sf/multilinestring/sf_multilinestring.hpp"
#include "sfheaders/sf/polygon/sf_polygon.hpp"
#include "sfheaders/sf/multipolygon/sf_multipolygon.hpp"

// TODO
// make an API entry point
// and ONLY this function will call the create_df() function
// or the make_sf() function

namespace sfheaders {
namespace api {

  inline Rcpp::DataFrame to_sf(
    SEXP& obj,
    SEXP& geometry_columns,
    SEXP& point_id,
    SEXP& multipoint_id,
    SEXP& linestring_id,
    SEXP& multilinestring_id,
    SEXP& polygon_id,
    SEXP& multipolygon_id,
    SEXP& list_columns,
    bool& close,
    bool& keep,
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
      sf_objs = sfheaders::sf::sf_point( obj, geometry_columns, keep );
    } else if ( sf_type == "MULTIPOINT" ) {
      sf_objs = sfheaders::sf::sf_multipoint( obj, geometry_columns, multipoint_id, keep );
    } else if ( sf_type == "LINESTRING" ) {
      sf_objs = sfheaders::sf::sf_linestring( obj, geometry_columns, linestring_id, keep );
    } else if ( sf_type == "MULTILINESTRING" ) {
      sf_objs = sfheaders::sf::sf_multilinestring( obj, geometry_columns, multilinestring_id, linestring_id, keep );
    } else if ( sf_type == "POLYGON" ) {
      sf_objs = sfheaders::sf::sf_polygon( obj, geometry_columns, polygon_id, linestring_id, close, keep );
    } else if ( sf_type == "MULTIPOLYGON" ) {
      sf_objs = sfheaders::sf::sf_multipolygon( obj, geometry_columns, multipolygon_id, polygon_id, linestring_id, close, keep );
    } else {
      Rcpp::stop("sfheaders - unknown sf type");
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

    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( sf_objs["df"] );
    Rcpp::List sfc = sf_objs["sfc"];
    Rcpp::String id_column = sf_objs["id_column"];
    Rcpp::StringVector property_cols = sf_objs[ "property_cols" ];
    Rcpp::IntegerVector property_idx = sf_objs[ "property_idx" ];
    Rcpp::IntegerVector row_idx = sf_objs["row_idx"];
    Rcpp::IntegerMatrix line_positions = sf_objs["line_positions"];

    Rcpp::IntegerVector list_column_idx;

    if( !Rf_isNull( list_columns ) ) {
      Rcpp::Rcout << "is_not_null" << std::endl;
      switch( TYPEOF( list_columns ) ) {
      case INTSXP: {
        list_column_idx = Rcpp::as< Rcpp::IntegerVector >( list_columns );
        break;
      }
      case STRSXP: {
        // find the locations of these within property cols
        // then subset property_idx[] by these values
        // to get teh list_column_idx;
        Rcpp::StringVector str_list_columns = Rcpp::as< Rcpp::StringVector >( list_columns );
        Rcpp::IntegerVector idx = sfheaders::utils::where_is( str_list_columns, property_cols );
        list_column_idx = property_idx[ idx ];
        break;

      }
      default:{
        Rcpp::stop("sfheaders - unknown list-column type");
      }
      }
    }

    // this should give us list_column_idx, which is a subset (or all) of property_idx,
    // which can be passed into create_sf()
    // and checked iff property_idx %in% list_column_idx;
    // and if so, make it a list-column, rather than subset the first row.
    Rcpp::Rcout << "list_columns: " << list_column_idx << std::endl;


    return sfheaders::sf::create_sf(df, sfc, id_column, property_cols, property_idx, row_idx);
    return sf_objs;
 }

} // api
} // sfheaders


#endif
