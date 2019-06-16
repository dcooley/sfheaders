#ifndef R_SFHEADERS_UTILS_H
#define R_SFHEADERS_UTILS_H

#include <Rcpp.h>

namespace sfheaders {
namespace utils {

  /* line_ids
   *
   * returns a 2-colummn matrix giving the start & end locations in a vector of'ids'
   * where the ids start & end
   *
   */
  inline Rcpp::IntegerMatrix line_ids(
    Rcpp::IntegerVector& line_ids,
    Rcpp::IntegerVector& unique_ids
  ) {

    size_t n = line_ids.length();
    size_t unique_n = unique_ids.length();
    size_t i;

    Rcpp::IntegerVector start_positions( unique_n );
    Rcpp::IntegerVector end_positions( unique_n );

    int idx = 0;
    int this_id;
    for( i = 0; i < n; i++ ) {
      // go through line_ids and find where ids change
      if( i == 0 ) {
        this_id = line_ids[ i ];
        start_positions[ idx ] = i;
      }

      if( this_id != line_ids[ i ] ) {
        // the id has changed
        end_positions[ idx ] = i - 1;
        idx++;
        start_positions[ idx ] = i;
        this_id = line_ids[ i ];
      }

      if( i == ( n - 1 ) ) {
        end_positions[ idx ] = i;
      }
    }

    Rcpp::IntegerMatrix im( unique_n, 2);

    im( Rcpp::_, 0 ) = start_positions;
    im( Rcpp::_, 1 ) = end_positions;

    return im;
  }

  template <int RTYPE>
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
    default: Rcpp::stop("unknown sf type");
    }
    return 0;
  }

  inline bool is_null_geometry( SEXP& sfg, std::string& geom_type ) {
    int n = get_sexp_length( sfg );
    if( geom_type == "POINT" ) {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( sfg );
      if (ISNAN( nv[0] ) ) {
        return true;
      }
    } else if ( n == 0 ) {
      return true;
    }
    return false;
  }

  inline std::string make_dimension( size_t n ) {
    switch( n ) {
    case 2: {
      return "XY";
      break;
    }
    case 3: {
      return "XYZ";
      break;
    }
    case 4: {
      return "XYZM";
      break;
    }
    default: {
      Rcpp::stop("unknown dimension attribute");
    }
    }
    return "XY"; // never reached
  }

} // namespace utils
} // namespace sfheaders

#endif
