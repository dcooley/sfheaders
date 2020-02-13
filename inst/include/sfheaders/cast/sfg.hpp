#ifndef R_SFHEADERS_CAST_SFG_H
#define R_SFHEADERS_CAST_SFG_H

#include "sfheaders/utils/sexp/sexp.hpp"
#include "sfheaders/df/sfg.hpp"
#include "sfheaders/df/utils.hpp"

#include <Rcpp.h>

#define M_COLUMN_CAST                8
#define Z_COLUMN_CAST                7
#define Y_COLUMN_CAST                6
#define X_COLUMN_CAST                5
#define MATRIX_ID                    4
#define LIST_MATRIX_ID               3
#define LIST_LIST_MATRIX_ID          2
#define SFG_COLUMN_CAST              1
#define SFC_COLUMN_CAST              0

#define MAX_COLUMNS_CAST             9

namespace sfheaders {
namespace cast {

  const Rcpp::CharacterVector column_names = {
    "sfc_id", "sfg_id", "list_list_matrix_id", "list_matrix_id", "matrix_id",
    "x","y","z","m"
  };

  inline Rcpp::CharacterVector make_names( Rcpp::CharacterVector& cls ) {

    std::string dim;
    std::string geometry;

    Rcpp::LogicalVector columns( column_names.length() );

    dim = cls[0];
    geometry = cls[1];

    if ( dim == "XYZM" ) {
      columns[ Z_COLUMN_CAST ] = true;
      columns[ M_COLUMN_CAST ] = true;
    } else if ( dim == "XYZ" ) {
      columns[ Z_COLUMN_CAST ] = true;
    } else if ( dim == "XYM" ) {
      columns[ M_COLUMN_CAST ] = true;  // #nocov
    }

    columns[ X_COLUMN_CAST ] = true;
    columns[ Y_COLUMN_CAST ] = true;


    if( geometry == "POINT" ) {
    } else if ( geometry == "MULTIPOINT" ) {

    } else if ( geometry == "LINESTRING" ) {

    } else if ( geometry == "MULTILINESTRING" ) {
      columns[ MATRIX_ID ] = true;

    } else if ( geometry == "POLYGON" ) {
      columns[ MATRIX_ID ] = true;

    } else if ( geometry == "MULTIPOLYGON" ) {
      columns[ MATRIX_ID ] = true;
      columns[ LIST_MATRIX_ID ] = true;
    }

    return column_names[ columns ];
  }


  inline Rcpp::List sfg_to_cast_df( SEXP& sfg ) {

    Rcpp::List res;

    Rcpp::CharacterVector cls = sfheaders::utils::getSfgClass( sfg );

    std::string dim;
    std::string geometry;

    Rcpp::LogicalVector columns( column_names.length() );

    dim = cls[0];
    geometry = cls[1];

    R_xlen_t sfg_rows = 0;

    if( geometry == "POINT" ) {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( sfg );
      res = sfheaders::df::sfg_point_coordinates( nv, sfg_rows );

    } else if ( geometry == "MULTIPOINT" ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( sfg );
      res = sfheaders::df::sfg_multipoint_coordinates( nm, sfg_rows );

    } else if ( geometry == "LINESTRING" ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( sfg );
      res = sfheaders::df::sfg_linestring_coordinates( nm, sfg_rows );

    } else if ( geometry == "MULTILINESTRING" ) {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      res = sfheaders::df::sfg_multilinestring_coordinates( lst, sfg_rows );

    } else if ( geometry == "POLYGON" ) {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      res = sfheaders::df::sfg_polygon_coordinates( lst, sfg_rows );

    } else if ( geometry == "MULTIPOLYGON" ) {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      res = sfheaders::df::sfg_multipolygon_coordinates( lst, sfg_rows );

    } else {
      Rcpp::stop("sfheaders - unknown geometry type"); // #nocov
    }

    Rcpp::CharacterVector df_names = make_names( cls );

    res.attr("class") = Rcpp::CharacterVector("data.frame");

    if( sfg_rows > 0 ) {
      Rcpp::IntegerVector rownames = Rcpp::seq( 1, sfg_rows );
      res.attr("row.names") = rownames;
    } else {
      res.attr("row.names") = Rcpp::IntegerVector(0); // #nocov
    }

    res.attr("names") = df_names;
    return res;

  }

} // cast
} // sfheaders

#endif
