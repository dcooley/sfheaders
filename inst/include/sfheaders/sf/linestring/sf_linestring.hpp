#ifndef R_SFHEADERS_SF_LINESTRING_H
#define R_SFHEADERS_SF_LINESTRING_H

#include <Rcpp.h>
#include "geometries/utils/sexp/sexp.hpp"
#include "sfheaders/sf/sf_utils.hpp"
#include "sfheaders/sfc/linestring/sfc_linestring.hpp"
#include "geometries/utils/unique/unique.hpp"

namespace sfheaders {
namespace sf {

  // this function won't keep any attributes
  inline SEXP sf_linestring(
    SEXP& x,
    SEXP& geometry_cols,
    SEXP& linestring_id,
    std::string xyzm
  ) {

    Rcpp::List sfc = sfheaders::sfc::sfc_linestring( x, geometry_cols, linestring_id, xyzm );
    // TODO: we're getting the linestring_ids inside sfc_linestring,
    // and re-doing it here... say what...
    SEXP ids = geometries::utils::get_ids( x, linestring_id );
    Rcpp::DataFrame sf = sfheaders::sf::make_sf( sfc, ids );
    return sf;
  }

  inline SEXP sf_linestring(
    SEXP& x,
    SEXP& geometry_cols,
    SEXP& linestring_id,
    bool& keep,
    std::string xyzm
  ) {

    if( !keep ) {
      return sf_linestring( x, geometry_cols, linestring_id, xyzm );
    }

    if( Rf_isNull( geometry_cols ) ) {
      Rcpp::stop("sfheaders - please specify the geometry columns x, y (z, (m)) when keep = TRUE");
    }

    //if( Rf_isNull( linestring_id ) ) {
      Rcpp::List sfc = sfheaders::sfc::sfc_linestring( x, geometry_cols, linestring_id, xyzm );
      SEXP property_columns = geometries::utils::other_columns( x, geometry_cols );

      Rcpp::IntegerVector property_idx = geometries::utils::where_is( property_columns, x );

      Rcpp::IntegerMatrix line_positions(1,2);
      line_positions(0,0) = 0;
      line_positions(0,1) = geometries::utils::sexp_n_row( x ) - 1;

      Rcpp::List res = Rcpp::List::create(
        Rcpp::_["x"] = x,
        Rcpp::_["sfc"] = sfc,
        Rcpp::_["property_cols"] = property_columns,
        Rcpp::_["property_idx"] = property_idx,
        Rcpp::_["line_positions"] = line_positions
      );

      return res;
    //}

  }


} // sf
} // sfheaders

#endif
