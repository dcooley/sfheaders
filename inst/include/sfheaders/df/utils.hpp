
#ifndef R_SFHEADERS_DF_UTILS_H
#define R_SFHEADERS_DF_UTILS_H

namespace sfheaders {
namespace utils {

  inline Rcpp::NumericVector fill_vector(
      Rcpp::NumericVector& vec_1,
      Rcpp::NumericVector& vec_2,
      R_xlen_t& start_idx
  ) {
    // fills vec_1 with vec_2, starting at 'start_idx'
    R_xlen_t i;
    R_xlen_t n = vec_2.length();

    for( i = 0; i < n; i++ ) {
      vec_1[ i + start_idx ] = vec_2[ i ] ;
    }
    return vec_1;
  }

} // utils
} // sfheaders

#endif
