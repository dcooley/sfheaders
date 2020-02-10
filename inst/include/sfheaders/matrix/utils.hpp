
#ifndef R_SFHEADERS_MATRIX_UTILS_H
#define R_SFHEADERS_MATRIX_UTILS_H

namespace sfheaders {
namespace utils {

  // needed for sfc objects to collapse list into a matrix
  template< int RTYPE >
  inline Rcpp::Matrix< RTYPE > construct_matrix( Rcpp::List& res, Rcpp::StringVector& mat_names, R_xlen_t& n_rows ) {
      R_xlen_t i;
      Rcpp::Matrix< RTYPE > mat( n_rows, res.length() );

      for( i = 0; i < res.length(); ++i ) {
        mat( Rcpp::_, i ) = Rcpp::as< Rcpp::NumericVector >( res[ i ] );
      }

      return mat;
  }

} // utils
} //sfheaders


#endif
