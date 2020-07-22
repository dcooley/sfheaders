#ifndef R_SFHEADERS_SFG_MULTILINESTRING_H
#define R_SFHEADERS_SFG_MULTILINESTRING_H

#include <Rcpp.h>
#include "sfheaders/sfg/sfg_types.hpp"
#include "sfheaders/utils/utils.hpp"

#include "geometries/utils/utils.hpp"
#include "geometries/geometries.hpp"

namespace sfheaders {
namespace sfg {

  template < int RTYPE >
  inline SEXP sfg_multilinestring(
    Rcpp::Vector< RTYPE >& vec,
    std::string xyzm
  ) {
    R_xlen_t n = vec.length();
    Rcpp::NumericMatrix nm( 1, n );
    nm( 0, Rcpp::_ ) = vec;
    return sfg_multilinestring( nm, xyzm );
  }

  template < int RTYPE >
  inline SEXP sfg_multilinestring(
      Rcpp::Matrix< RTYPE >& mat,
      std::string xyzm
  ) {
    Rcpp::List mls( 1 );
    mls[0] = mat;
    R_xlen_t n_col = mat.ncol();
    sfheaders::sfg::make_sfg( mls, n_col, sfheaders::sfg::SFG_MULTILINESTRING, xyzm );
    return mls;
  }

  inline SEXP sfg_multilinestring(
      SEXP& x,
      SEXP& geometry_cols,
      SEXP& linestring_id,
      std::string xyzm
  ) {

    // needs to go through the make_geoemtries()
    // but attributes are assigned at the end

    if( Rf_isNull( geometry_cols ) ) {
      // make this all the other columns, then send back in
      SEXP geometry_cols2 = geometries::utils::other_columns( x, linestring_id );
      return sfg_multilinestring( x, geometry_cols2, linestring_id, xyzm );
    }

    int n_id_cols = 1;
    R_xlen_t col_counter = geometries::utils::sexp_length( geometry_cols );

    // After subset_geometries we have moved the geometry columns
    // into the 0:(n_geometry-1) positions
    Rcpp::IntegerVector int_geometry_cols = Rcpp::seq( 0, ( col_counter - 1 ) );

    xyzm = sfheaders::utils::validate_xyzm( xyzm, col_counter );

    R_xlen_t required_cols = col_counter + n_id_cols;

    Rcpp::IntegerVector geometry_cols_int = geometries::utils::sexp_col_int( x, geometry_cols );

    Rcpp::List lst = geometries::utils::as_list( x );
    Rcpp::List res( required_cols );

    sfheaders::utils::subset_geometries( lst, res, geometry_cols_int );

    Rcpp::IntegerVector int_linestring_id(1);

    sfheaders::utils::resolve_id( x, linestring_id, int_linestring_id, res, lst, col_counter );

    Rcpp::List attributes = Rcpp::List::create();
    Rcpp::List sfg = geometries::make_geometries( res, int_linestring_id, int_geometry_cols, attributes );


    Rcpp::StringVector class_attribute = { xyzm.c_str(), "MULTILINESTRING","sfg" };
    Rcpp::List atts = Rcpp::List::create(
      Rcpp::_["class"] = class_attribute
    );
    geometries::utils::attach_attributes( sfg, atts );

    return sfg;
  }

  inline SEXP sfg_multilinestring(
      SEXP& x,
      std::string xyzm
  ) {
    SEXP geometry_cols;
    SEXP linestring_id;
    return sfg_multilinestring( x, geometry_cols, linestring_id, xyzm );
  }


} // sfg
} // sfheaders

#endif
