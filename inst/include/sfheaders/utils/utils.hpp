#ifndef R_SFHEADERS_UTILS_H
#define R_SFHEADERS_UTILS_H

#include <Rcpp.h>
#include "sfheaders/utils/lines/lines.hpp"
#include "sfheaders/utils/columns/columns.hpp"
#include "sfheaders/utils/matrix/matrix.hpp"
#include "sfheaders/utils/subset/subset.hpp"
#include "sfheaders/utils/sexp/sexp.hpp"
#include "sfheaders/utils/vectors/vectors.hpp"

namespace sfheaders {
namespace utils {

  inline void geometry_column_check( SEXP x ) {
    size_t n = sfheaders::utils::get_sexp_length( x );
    if( n < 2 || n > 4) {
      Rcpp::stop("sfheaders - incorrect number of geometry columns");
    }
  }

  inline bool is_null_geometry( SEXP& sfg, std::string& geom_type ) {
    int n = get_sexp_length( sfg );
    if( geom_type == "POINT" ) {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( sfg );
      if (ISNAN( nv[0] ) ) {
        return true;
      }
    } else if ( n == 0 ) {
      return true;
    }
    return false;
  }

  inline std::string make_dimension( size_t n ) {
    switch( n ) {
    case 2: {
      return "XY";
      break;
    }
    case 3: {
      return "XYZ";
      break;
    }
    case 4: {
      return "XYZM";
      break;
    }
    default: {
      Rcpp::stop("unknown dimension attribute");
    }
    }
    return "XY"; // never reached
  }

} // namespace utils
} // namespace sfheaders

#endif
