#ifndef R_SFHEADERS_UTILS_UNIQUE_H
#define R_SFHEADERS_UTILS_UNIQUE_H

#include <Rcpp.h>

namespace sfheaders {
namespace utils {

  // template <int RTYPE>
  // inline SEXP sexp_unique(Rcpp::Vector< RTYPE > v) {
  //   return Rcpp::sort_unique( v );
  // }
  //

  // issue 27
  template < typename T, int RTYPE >
  inline SEXP sexp_unique( Rcpp::Vector< RTYPE > x ) {
    std::set< T > seen;
    auto newEnd = std::remove_if( x.begin(), x.end(), [&seen]( const T value ) {
      if ( seen.find( value ) != std::end( seen ) ) {
        return true;
      }
      seen.insert( value );
      return false;
    });
    x.erase( newEnd, x.end() );
    return x;
  }


  // returns unique values in their original input order
  inline SEXP get_sexp_unique( SEXP s ) {

    SEXP s2 = Rcpp::clone( s );

    switch( TYPEOF( s2 ) ) {
    case LGLSXP: {
      return sexp_unique< bool, LGLSXP >( s2 );
    }
    case REALSXP: {
      return sexp_unique< double, REALSXP >( s2 );
    }
    case INTSXP: {
      return sexp_unique< int, INTSXP >( s2 );
    }
    case STRSXP: {
      return sexp_unique< char* , STRSXP >( s2 );
    }
    default: Rcpp::stop("sfheaders - unknown vector type"); // #nocov
    }
    return 0;
  }

} // utils
} // sfheaders


#endif
