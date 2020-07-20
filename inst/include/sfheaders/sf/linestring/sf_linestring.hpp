#ifndef R_SFHEADERS_SF_LINESTRING_H
#define R_SFHEADERS_SF_LINESTRING_H

#include <Rcpp.h>
#include "geometries/utils/sexp/sexp.hpp"
#include "geometries/utils/unique/unique.hpp"

#include "geometries/utils/rleid/rleid.hpp"

#include "sfheaders/sf/sf_utils.hpp"
#include "sfheaders/sfc/linestring/sfc_linestring.hpp"

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

    // if( Rf_isNull( geometry_cols ) ) {
    //   Rcpp::stop("sfheaders - please specify the geometry columns x, y (z, (m)) when keep = TRUE");
    // }

    // Iff linestring_id is NULL, and we're keeping properties
    // we can ad a column of 1s, like we do in sfc

    Rcpp::List lst = geometries::utils::as_list( x );
    Rcpp::List sfc = sfheaders::sfc::sfc_linestring( x, geometry_cols, linestring_id, xyzm );
    // R_xlen_t n_col = lst.length();

    // Dont' do thisvvv
    // if there's no ID, we only need one row, and it can be added at the end?
    // Rcpp::IntegerVector int_linestring_id(1);
    // if( Rf_isNull( linestring_id ) ) {
    //   lst = sfheaders::utils::append_id_column( lst );
    //   int_linestring_id[0] = n_col;
    // } else {
    //   int_linestring_id = geometries::utils::sexp_col_int( x, linestring_id );
    // }

    SEXP property_cols = geometries::utils::other_columns( x, geometry_cols, linestring_id );
    Rcpp::IntegerVector int_property_cols = geometries::utils::sexp_col_int( x, property_cols );
    Rcpp::Rcout << "int_property_cols: " << int_property_cols << std::endl;
    //R

    if( Rf_isNull( linestring_id ) ) {
      Rcpp::Rcout << "linestring id is null " << std::endl;
      // There is no ID column
      // so return it without one

      Rcpp::IntegerVector geometry_index(1);
      geometry_index[0] = 0;

      return Rcpp::List::create(
        Rcpp::_["x"] = lst,
        Rcpp::_["sfc"] = sfc,
        Rcpp::_["property_cols"] = int_property_cols,
        Rcpp::_["geometry_idx"] = geometry_index
        // no id_column because it's null
      );
    }

    Rcpp::IntegerVector int_linestring_id = geometries::utils::sexp_col_int( x, linestring_id );
    // TODO:
    // - can I get this during 'sfc_linestring()' so I don't have to do it twice?
    Rcpp::IntegerVector geometry_idx = geometries::utils::rleid_indices( lst, int_linestring_id );

    Rcpp::Rcout << "property_cols: " << int_property_cols << std::endl;
    Rcpp::Rcout << "linestring_id_int: " << int_linestring_id << std::endl;
    Rcpp::Rcout << "geometry_idx: " << geometry_idx << std::endl;

    Rcpp::List res = Rcpp::List::create(
      Rcpp::_["x"] = lst,
      Rcpp::_["sfc"] = sfc,
      Rcpp::_["property_cols"] = int_property_cols,
      Rcpp::_["geometry_idx"] = geometry_idx,
      Rcpp::_["id_column"] = int_linestring_id
    );

    return res;

    // Iff linestring_id isn't NULL, it means the user supplied the column
    // so there's no need to return a column called 'id'


    return sfc;

    // if linestring_id (outer-id) is NULL, it's a single geometry
    // so we only need the first row of data

    // otherwise, we need the index where the linestring_id (outer-id) changes
    //
    // add to geometries a id_indices() function, which takes a single vector,
    // runs rleid(), and returns the index where the changes occur.


    // TODO
    // can I re-do this by making 'sfc'
    // then subseting the input 'x' by the other columns that aren't the geometries?

    // //if( Rf_isNull( linestring_id ) ) {
    //   Rcpp::List sfc = sfheaders::sfc::sfc_linestring( x, geometry_cols, linestring_id, xyzm );
    //   SEXP property_columns = geometries::utils::other_columns( x, geometry_cols );
    //
    //   //Rcpp::IntegerVector property_idx = geometries::utils::where_is( property_columns, x );
    //
    //   Rcpp::IntegerMatrix line_positions(1,2);
    //   line_positions(0,0) = 0;
    //   line_positions(0,1) = geometries::utils::sexp_n_row( x ) - 1;
    //
    //   Rcpp::List res = Rcpp::List::create(
    //     Rcpp::_["x"] = x,
    //     Rcpp::_["sfc"] = sfc,
    //     Rcpp::_["property_cols"] = property_columns,
    //     Rcpp::_["property_idx"] = property_idx,
    //     Rcpp::_["line_positions"] = line_positions
    //   );
    //
    //   return res;
    //}

  }


} // sf
} // sfheaders

#endif
