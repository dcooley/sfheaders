#ifndef R_SFHEADERS_UTILS_MATRIX_H
#define R_SFHEADERS_UTILS_MATRIX_H

#include <Rcpp.h>

namespace sfheaders {
namespace utils {

  inline Rcpp::StringVector matrix_names(
      Rcpp::List m_attr
  ) {
    Rcpp::StringVector matrix_names = m_attr[1];
    return matrix_names;
  }

  inline Rcpp::StringVector matrix_names(
      Rcpp::IntegerMatrix& m
  ) {
    Rcpp::List m_attr = m.attr("dimnames");
    return matrix_names( m_attr );
  }

  inline Rcpp::StringVector matrix_names(
      Rcpp::NumericMatrix& m
  ) {
    Rcpp::List m_attr = m.attr("dimnames");
    return matrix_names( m_attr );
  }

} // utils
} // sfheadesr

#endif
