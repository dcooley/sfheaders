#ifndef R_SFHEADERS_SFG_MULTIPOINT_H
#define R_SFHEADERS_SFG_MULTIPOINT_H

#include <Rcpp.h>

#include "sfheaders/sfg/sfg_types.hpp"
#include "sfheaders/utils/utils.hpp"

#include "geometries/utils/columns/columns.hpp"
#include "geometries/geometries.hpp"
#include "geometries/nest/nest.hpp"


namespace sfheaders {
namespace sfg {

  inline SEXP sfg_multipoint(
      SEXP& x,
      SEXP& geometry_cols,
      std::string xyzm
  ) {

    Rcpp::NumericMatrix geometry_mat = geometries::matrix::to_matrix( x, geometry_cols );
    xyzm = sfheaders::utils::validate_xyzm( xyzm, geometry_mat.ncol() );
    sfheaders::sfg::make_sfg( geometry_mat, sfheaders::sfg::SFG_MULTIPOINT, xyzm );
    return geometry_mat;
  }
} // sfg
} // sfheaders


#endif
