
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

    for( i = 0; i < n; ++i ) {
      vec_1[ i + start_idx ] = vec_2[ i ] ;
    }
    return vec_1;
  }

  template <int RTYPE>
  inline Rcpp::CharacterVector sfgClass( Rcpp::Vector<RTYPE> v ) {
    return v.attr("class");
  }

  inline Rcpp::CharacterVector getSfgClass( SEXP sfg ) {
    switch( TYPEOF( sfg ) ) {
    case REALSXP:
      return sfgClass<REALSXP>( sfg );
    case VECSXP:
      return sfgClass<VECSXP>( sfg );
    case INTSXP:
      return sfgClass<INTSXP>( sfg );
    default: Rcpp::stop("unknown sf type");   // #nocov
    }
    return Rcpp::CharacterVector();
  }

  inline Rcpp::List make_dataframe(
      Rcpp::List& res,
      R_xlen_t& total_rows,
      Rcpp::StringVector& column_names
    ) {

    res.attr("class") = Rcpp::CharacterVector("data.frame");

    if( total_rows > 0 ) {
      Rcpp::IntegerVector rownames = Rcpp::seq( 1, total_rows );
      res.attr("row.names") = rownames;
    } else {
      res.attr("row.names") = Rcpp::IntegerVector(0);  // #nocov
    }

    res.attr("names") = column_names;
    return res;
  }

  inline Rcpp::List make_dataframe(
    Rcpp::List& res,
    R_xlen_t& total_rows
  ) {
    Rcpp::StringVector res_names = res.names();
    return make_dataframe( res, total_rows, res_names );
  }

} // utils
} // sfheaders

#endif
