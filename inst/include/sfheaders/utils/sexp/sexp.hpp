
#ifndef R_SFHEADERS_UTILS_SEXP_H
#define R_SFHEADERS_UTILS_SEXP_H

#include <Rcpp.h>


namespace sfheaders{
namespace utils {

  template < int RTYPE >
  inline Rcpp::StringVector sexp_col_names( Rcpp::Matrix < RTYPE > m ) {
    return colnames( m );
  }

  inline Rcpp::StringVector get_sexp_col_names( SEXP m ) {
    switch( TYPEOF( m ) ) {
    case INTSXP: {
      return sexp_col_names< INTSXP >( m );
    }
    case REALSXP: {
      return sexp_col_names< REALSXP >( m );
    }
    default: {
      Rcpp::stop("sfheaders - expecting a matrix when trying to get colnames");
    }
    }
  }

  template < int RTYPE >
  inline size_t sexp_n_col( Rcpp::Matrix < RTYPE > v ) {
    return v.ncol();
  }

  inline size_t get_sexp_n_col( SEXP s ) {
    switch( TYPEOF( s ) ) {
    case REALSXP: {
      return sexp_n_col< REALSXP >( s );
    }
    case INTSXP: {
      return sexp_n_col< INTSXP >( s );
    }
    default: {
      Rcpp::stop("sfheaders - can't determine n_col");
    }
    }
  }

  template <int RTYPE>
  inline int sexp_length(Rcpp::Vector<RTYPE> v) {
    return v.length();
  }

  inline int get_sexp_length( SEXP s ) {

    switch( TYPEOF(s) ) {
    case REALSXP:
      return sexp_length< REALSXP >( s );
    case VECSXP:
      return sexp_length< VECSXP >( s );
    case INTSXP:
      return sexp_length< INTSXP >( s );
    case STRSXP:
      return sexp_length< STRSXP >( s );
    default: Rcpp::stop("sfheaders - unknown vector type");
    }
    return 0;
  }

} // utils
} // sfheaders




#endif
