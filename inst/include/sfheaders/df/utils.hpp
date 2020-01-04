
#ifndef R_SFHEADERS_DF_UTILS_H
#define R_SFHEADERS_DF_UTILS_H

namespace sfheaders {
namespace utils {

  inline void fill_vector(
      Rcpp::NumericVector& vec_1,
      Rcpp::NumericVector& vec_2,
      R_xlen_t& start_idx
  ) {
    // fills vec_1 with vec_2, starting at 'start_idx'
    //Rcpp::NumericVector res = Rcpp::clone( vec_1 );
    R_xlen_t i;
    R_xlen_t n = vec_2.length();

    // Rcpp::Rcout << "vec_1.length() " << vec_1.length() << std::endl;
    // Rcpp::Rcout << "start_idx: " << start_idx << std::endl;
    // Rcpp::Rcout << "n: " << n << std::endl;

    for( i = 0; i < n; i++ ) {
      // Rcpp::Rcout << "i: " << i << std::endl;
      vec_1[ i + start_idx ] = vec_2[ i ] ;
    }
    //return vec_1;
  }

} // utils
} // sfheaders

#endif
