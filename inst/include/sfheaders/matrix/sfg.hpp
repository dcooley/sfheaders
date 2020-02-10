#ifndef R_SFHEADERS_MATRIX_SFG_H
#define R_SFHEADERS_MATRIX_SFG_H

// #include "sfheaders/utils/sexp/sexp.hpp"
// #include "sfheaders/df/utils.hpp"
#include "sfheaders/coordinates/coordinates.hpp"
#include <Rcpp.h>


#define X_COLUMN      0
#define Y_COLUMN      1
#define Z_COLUMN      2
#define M_COLUMN      3
#define L1_COLUMN     4
#define L2_COLUMN     5
#define L3_COLUMN     6

#define MAX_COLUMNS   7

namespace sfheaders {
namespace matrix {

  const Rcpp::CharacterVector column_names = {
    "X","Y","Z","M","L1","L2","L3"
  };

  inline Rcpp::CharacterVector make_names( Rcpp::CharacterVector& cls ) {

    std::string dim;
    std::string geometry;

    Rcpp::LogicalVector columns( column_names.length() );

    dim = cls[0];
    geometry = cls[1];

    if ( dim == "XYZM" ) {
      columns[ Z_COLUMN ] = true;
      columns[ M_COLUMN ] = true;
    } else if ( dim == "XYZ" ) {
      columns[ Z_COLUMN ] = true;
    } else if ( dim == "XYM" ) {
      columns[ M_COLUMN ] = true;  // #nocov
    }

    columns[ X_COLUMN ] = true;
    columns[ Y_COLUMN ] = true;

    if( geometry == "POINT" ) {

    } else if ( geometry == "MULTIPOINT" ) {
      columns[ L1_COLUMN ] = true;

    } else if ( geometry == "LINESTRING" ) {
      columns[ L1_COLUMN ] = true;

    } else if ( geometry == "MULTILINESTRING" ) {
      columns[ L1_COLUMN ] = true;
      columns[ L2_COLUMN ] = true;

    } else if ( geometry == "POLYGON" ) {
      columns[ L1_COLUMN ] = true;
      columns[ L2_COLUMN ] = true;

    } else if ( geometry == "MULTIPOLYGON" ) {
      columns[ L1_COLUMN ] = true;
      columns[ L2_COLUMN ] = true;
      columns[ L3_COLUMN ] = true;

    }

    return column_names[ columns ];
  }

  inline Rcpp::List sfg_to_matrix( SEXP& sfg ) {

    Rcpp::List res;

    Rcpp::CharacterVector cls = sfheaders::coordinates::getSfgClass( sfg );

    std::string dim;
    std::string geometry;

    Rcpp::LogicalVector columns( column_names.length() );

    dim = cls[0];
    geometry = cls[1];

    R_xlen_t sfg_rows = 0;

    if( geometry == "POINT" ) {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( sfg );
      res = sfheaders::coordinates::sfg_point_coordinates( nv, sfg_rows );

    } else if ( geometry == "MULTIPOINT" ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( sfg );
      res = sfheaders::coordinates::sfg_multipoint_coordinates( nm, sfg_rows );

    } else if ( geometry == "LINESTRING" ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( sfg );
      res = sfheaders::coordinates::sfg_linestring_coordinates( nm, sfg_rows );

    } else if ( geometry == "MULTILINESTRING" ) {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      res = sfheaders::coordinates::sfg_multilinestring_coordinates( lst, sfg_rows );

    } else if ( geometry == "POLYGON" ) {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      res = sfheaders::coordinates::sfg_polygon_coordinates( lst, sfg_rows );

    } else if ( geometry == "MULTIPOLYGON" ) {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      res = sfheaders::coordinates::sfg_multipolygon_coordinates( lst, sfg_rows );

    } else {
      Rcpp::stop("sfheaders - unknown geometry type"); // #nocov
    }

    Rcpp::CharacterVector df_names = make_names( cls );

    sfheaders::utils::construct_matrix( res, df_names, sfg_rows );
    return res;

  }

} // matrix
} // sfheaders

#endif
