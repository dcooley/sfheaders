
#ifndef R_SFHEADERS_DF_UTILS_H
#define R_SFHEADERS_DF_UTILS_H

namespace sfheaders {
namespace utils {

  inline void construct_df(
      Rcpp::List& df,
      Rcpp::StringVector& column_names,
      R_xlen_t& n_rows
  ) {
    df.attr("class") = Rcpp::CharacterVector("data.frame");

    if( n_rows > 0 ) {
      Rcpp::IntegerVector rownames = Rcpp::seq( 1, n_rows );
      df.attr("row.names") = rownames;
    } else {
      df.attr("row.names") = Rcpp::IntegerVector(0);  // #nocov
    }

    df.attr("names") = column_names;
  }

} // utils
} // sfheaders

#endif
