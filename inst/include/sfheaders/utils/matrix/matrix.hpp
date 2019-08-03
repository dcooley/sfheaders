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

  inline Rcpp::NumericMatrix df_to_matrix(
      Rcpp::DataFrame& df
  ) {
    int i;
    int n_cols = df.cols();
    int n_rows = df.rows();
    Rcpp::StringVector df_names = df.names();
    Rcpp::NumericMatrix nm( n_rows, n_cols );
    for( i = 0; i < n_cols; i++ ) {
      Rcpp::NumericVector this_column = Rcpp::as< Rcpp::NumericVector >( df[ i ] );
      nm( Rcpp::_, i ) = this_column;
    }

    Rcpp::List m_attr(2);
    m_attr(1) = df_names;

    nm.attr("dimnames") = m_attr;
    return nm;
  }

  inline Rcpp::IntegerMatrix matrix_row_to_matrix(
    Rcpp::IntegerMatrix& im,
    size_t& i
  ) {
    Rcpp::IntegerVector this_row = im( i, Rcpp::_ );
    size_t n_col = im.ncol();
    Rcpp::IntegerMatrix im2( 1, n_col );
    im2( 0, Rcpp::_ ) = this_row;
    return im2;
  }

  inline Rcpp::NumericMatrix matrix_row_to_matrix(
      Rcpp::NumericMatrix& nm,
      size_t& i
  ) {
    Rcpp::NumericVector this_row = nm( i, Rcpp::_ );
    size_t n_col = nm.ncol();
    Rcpp::NumericMatrix nm2( 1, n_col );
    nm2( 0, Rcpp::_ ) = this_row;
    return nm2;
  }


} // utils
} // sfheadesr

#endif
