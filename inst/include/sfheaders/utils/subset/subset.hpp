#ifndef R_SFHEADERS_UTILS_SUBSETTING_H
#define R_SFHEADERS_UTILS_SUBSETTING_H

#include <Rcpp.h>

namespace sfheaders {
namespace utils {

  inline Rcpp::LogicalVector subset_vector(
      Rcpp::LogicalVector& lv,
      Rcpp::Range& rng
  ) {
    return lv[ rng ];
  }

  inline Rcpp::IntegerVector subset_vector(
      Rcpp::IntegerVector& iv,
      Rcpp::Range& rng
  ) {
    return iv[ rng ];
  }

  inline Rcpp::NumericVector subset_vector(
    Rcpp::NumericVector& nv,
    Rcpp::Range& rng
  ) {
    return nv[ rng ];
  }

  inline Rcpp::StringVector subset_vector(
      Rcpp::StringVector& sv,
      Rcpp::Range& rng
  ) {
    return sv[ rng ];
  }

  inline SEXP subset_vector(
    SEXP& x,
    int& start,
    int& end
  ) {
    Rcpp::Range rng = Rcpp::Range( start, end );

    switch( TYPEOF( x ) ) {
    case LGLSXP: {
      Rcpp::LogicalVector lv = Rcpp::as< Rcpp::LogicalVector >( x );
      return subset_vector( lv, rng );
    }
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
      return subset_vector( iv, rng );
    }
    case REALSXP: {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
      return subset_vector( nv, rng );
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( x );
      return subset_vector( sv, rng ); // shouldn't get here? should only be numerics
    }
    default: {
      Rcpp::stop("sfheaders - unsupported vector type for subsetting");  // #nocov
    }
    }
    return Rcpp::List::create(); // never reaches
  }

  inline Rcpp::List subset_dataframe(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& cols,
    int& start,
    int& end
  ) {

    R_xlen_t n_cols = cols.size();
    Rcpp::StringVector df_names = df.names();
    Rcpp::IntegerVector row_names = Rcpp::seq( start + 1, end + 1 );
    R_xlen_t i;
    Rcpp::List df_subset( n_cols );
    for( i = 0; i < n_cols; i++ ) {
      Rcpp::String this_col = cols[i];

      SEXP this_vec = df[ this_col ];
      df_subset[i] = sfheaders::utils::subset_vector( this_vec, start, end );
    }
    df_subset.names() = cols;
    return df_subset;
  }

} // utils
} // sfheaderes


#endif
