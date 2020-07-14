#ifndef R_SFHEADERS_SFG_LINESTRING_H
#define R_SFHEADERS_SFG_LINESTRING_H

#include <Rcpp.h>
#include "sfheaders/sfg/sfg_types.hpp"
#include "sfheaders/utils/utils.hpp"

#include "geometries/utils/columns/columns.hpp"
#include "geometries/geometries.hpp"
#include "geometries/nest/nest.hpp"


namespace sfheaders {
namespace sfg {

  inline SEXP sfg_linestring(
    SEXP& x,
    SEXP& geometry_cols,
    std::string xyzm
  ) {
    SEXP geometry_mat = geometries::matrix::to_matrix( x, geometry_cols );
    R_xlen_t n_col = geometries::utils::sexp_n_col( geometry_mat );
    xyzm = sfheaders::utils::validate_xyzm( xyzm, n_col );
    sfheaders::sfg::make_sfg( geometry_mat, n_col, sfheaders::sfg::SFG_LINESTRING, xyzm );
    return geometry_mat;
  }

} // sfg
} // sfheaders


#endif
