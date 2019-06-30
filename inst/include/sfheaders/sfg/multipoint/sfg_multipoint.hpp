#ifndef R_SFHEADERS_SFG_MULTIPOINT_H
#define R_SFHEADERS_SFG_MULTIPOINT_H

#include <Rcpp.h>
#include "sfheaders/shapes/mat/mat.hpp"
#include "sfheaders/sfg/sfg_attributes.hpp"
#include "sfheaders/sfg/sfg_dimension.hpp"

namespace sfheaders {
namespace sfg {

  /*
   * assumes columns are in lon/lat/z/m order
   */
  inline SEXP to_multipoint(
      Rcpp::IntegerMatrix& im
  ) {
    size_t n_col = im.ncol();
    std::string dim = sfheaders::sfg::sfg_dimension( n_col );

    std::string geom_type = "MULTIPOINT";
    im.attr("class") = sfheaders::sfg::sfg_attributes( dim, geom_type );

    return im;
  }

  inline SEXP to_multipoint(
      Rcpp::IntegerVector& iv
  ) {
    size_t n = iv.length();
    Rcpp::IntegerMatrix im( 1, n );
    im( 0, Rcpp::_ ) = iv;
    return to_multipoint( im );
  }

  inline SEXP to_multipoint(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& cols
  ) {
    Rcpp::IntegerMatrix im2 = sfheaders::shapes::get_mat( im, cols );
    return to_multipoint( im2 );
  }

  inline SEXP to_multipoint(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& cols
  ) {
    Rcpp::IntegerMatrix im2 = sfheaders::shapes::get_mat( im, cols );
    return to_multipoint( im2 );
  }

  inline SEXP to_multipoint(
      Rcpp::NumericMatrix& nm
  ) {

    size_t n_col = nm.ncol();
    std::string dim = sfheaders::sfg::sfg_dimension( n_col );

    std::string geom_type = "MULTIPOINT";
    nm.attr("class") = sfheaders::sfg::sfg_attributes(dim, geom_type);

    return nm;
  }

  inline SEXP to_multipoint(
      Rcpp::NumericVector& nv
  ) {
    size_t n = nv.length();
    Rcpp::NumericMatrix nm( 1, n );
    nm( 0, Rcpp::_ ) = nv;
    return to_multipoint( nm );
  }

  inline SEXP to_multipoint(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& cols
  ) {
    Rcpp::NumericMatrix nm2 = sfheaders::shapes::get_mat( nm, cols );
    return to_multipoint( nm2 );
  }

  inline SEXP to_multipoint(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& cols
  ) {
    Rcpp::NumericMatrix nm2 = sfheaders::shapes::get_mat( nm, cols );
    return to_multipoint( nm2 );
  }

  // expects only lon/lat/z/m columns
  inline SEXP to_multipoint(
      Rcpp::DataFrame& df
  ) {
    Rcpp::NumericMatrix nm = sfheaders::utils::df_to_matrix( df );
    return to_multipoint( nm );
  }

  inline SEXP to_multipoint(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& cols
  ) {
    Rcpp::NumericMatrix nm = sfheaders::shapes::get_mat( df, cols );
    return to_multipoint( nm );
  }

  inline SEXP to_multipoint(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& cols
  ) {
    Rcpp::NumericMatrix nm = sfheaders::shapes::get_mat( df, cols );
    return to_multipoint( nm );
  }

inline SEXP to_multipoint(
    SEXP& x,
    Rcpp::IntegerVector& cols
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
        Rcpp::stop("sfheaders - expecting a matrix");
      } else {
        Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
        return to_multipoint( im, cols );
      }
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
        Rcpp::stop("sfheaders - expecting a matrix");
      } else {
        Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
        return to_multipoint( nm, cols );
      }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return to_multipoint( df, cols );
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_MULTIPOINT type");
    }
    }

    return Rcpp::List::create(); // never reaches
  }

  inline SEXP to_multipoint(
      SEXP& x,
      Rcpp::StringVector& cols
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
        Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
        return to_multipoint( im, cols );
      } else {
        Rcpp::warning("sfheaders - ignoring geometry_columns argument");
        Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
        return to_multipoint( iv );
      }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
        Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
        return to_multipoint( nm, cols );
      } else {
        Rcpp::warning("sfheaders - ignoring geometry_columns argument");
        Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
        return to_multipoint( nv );
      }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return to_multipoint( df, cols );
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_MULTIPOINT type");
    }
    }

    return Rcpp::List::create(); // never reaches
  }


  inline SEXP to_multipoint(
      SEXP& x
  ) {
    // switch on type of x
    //int tp = TYPEOF( x );
    // Rcpp::Rcout << "type of multipoint: " << tp << std::endl;

    switch ( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
        Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
        return to_multipoint( im );
      } else {
        Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
        return to_multipoint( iv );
      }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
        Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
        return to_multipoint( nm );
      } else {
        Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
        return to_multipoint( nv );
      }
    }
    case VECSXP: {
    if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return to_multipoint( df );
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_MULTIPOINT type");
    }
    }
    return x; // never reaches
  }

  inline SEXP to_multipoint(
    SEXP& x,
    SEXP& cols
  ) {
    if( Rf_isNull( cols ) ) {
      return to_multipoint( x );
    }
    switch( TYPEOF( cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( cols );
      return to_multipoint( x, iv );
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( cols );
      return to_multipoint( x, sv );
    }
    default: {
      Rcpp::stop("sfheaders - unknown column types");
    }
    }
    return Rcpp::List::create(); // never reaches
  }

} // sfg
} // sfheaders


#endif
