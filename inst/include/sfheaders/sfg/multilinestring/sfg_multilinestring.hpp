#ifndef R_SFHEADERS_SFG_MULTILINESTRING_H
#define R_SFHEADERS_SFG_MULTILINESTRING_H

#include "sfheaders/utils.hpp"
#include "sfheaders/shapes/shapes.hpp"
#include "sfheaders/sfg/sfg_dimension.hpp"
#include "sfheaders/sfg/sfg_attributes.hpp"

namespace sfheaders {
namespace sfg {

  // multilinestring is a list of linestrings (matrices)
  // but can also be a single matrix
  inline SEXP to_multilinestring(
      Rcpp::IntegerMatrix& im
  ) {
    Rcpp::List mls( 1 );
    mls[0] = im;
    size_t n_col = im.ncol();
    std::string dim = sfheaders::sfg::sfg_dimension( n_col );

    std::string geom_type = "MULTILINESTRING";
    mls.attr("class") = sfheaders::sfg::sfg_attributes( dim, geom_type );

    return mls;
  }

  inline SEXP to_multilinestring(
      Rcpp::NumericMatrix& nm
  ) {
    Rcpp::List mls( 1 );
    mls[0] = nm;
    size_t n_col = nm.ncol();
    std::string dim = sfheaders::sfg::sfg_dimension( n_col );

    std::string geom_type = "MULTILINESTRING";
    mls.attr("class") = sfheaders::sfg::sfg_attributes( dim, geom_type );

    return mls;
  }

  inline SEXP to_multilinestring(
      Rcpp::DataFrame& df
  ) {
    Rcpp::List mls( 1 );
    Rcpp::NumericMatrix nm = sfheaders::utils::df_to_matrix( df );
    mls[0] = nm;
    size_t n_col = nm.ncol();
    Rcpp::Rcout << "n_col: " << n_col << std::endl;
    std::string dim = sfheaders::sfg::sfg_dimension( n_col );

    std::string geom_type = "MULTILINESTRING";
    mls.attr("class") = sfheaders::sfg::sfg_attributes( dim, geom_type );

    return mls;
  }

  inline SEXP to_multilinestring(
    Rcpp::List& lst
  ) {

    // each list element must be a matrix
    std::string dim = sfheaders::sfg::sfg_dimension( lst );

    std::string geom_type = "MULTILINESTRING";
    lst.attr("class") = sfheaders::sfg::sfg_attributes( dim, geom_type );

    return lst;
  }


  inline SEXP to_multilinestring(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& cols
  ) {
    Rcpp::NumericMatrix nm = sfheaders::shapes::get_line( df, cols );
    return to_multilinestring( nm );
  }

  inline SEXP to_multilinestring(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& cols
  ) {
    Rcpp::NumericMatrix nm = sfheaders::shapes::get_line( df, cols );
    return to_multilinestring( nm );
  }

  inline SEXP to_multilinestring(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& cols
  ) {
    Rcpp::NumericMatrix nm2 = sfheaders::shapes::get_line( nm, cols );
    return to_multilinestring( nm2 );
  }

  inline SEXP to_multilinestring(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& cols
  ) {
    Rcpp::NumericMatrix nm2 = sfheaders::shapes::get_line( nm, cols );
    return to_multilinestring( nm2 );
  }

  inline SEXP to_multilinestring(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& cols
  ) {
    Rcpp::IntegerMatrix im2 = sfheaders::shapes::get_line( im, cols );
    return to_multilinestring( im2 );
  }

  inline SEXP to_multilinestring(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& cols
  ) {
    Rcpp::IntegerMatrix im2 = sfheaders::shapes::get_line( im, cols );
    return to_multilinestring( im2 );
  }

  // We're still on single sfg objects.
  // when we go up to sfc objects then we will need multiline_id & line_id
  inline SEXP to_multilinestring(
    Rcpp::DataFrame& df,
    Rcpp::IntegerVector& cols,
    int& id_col
  ) {
    Rcpp::List lst = sfheaders::shapes::get_lines( df, cols, id_col );
    return to_multilinestring( lst );
  }

  inline SEXP to_multilinestring(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& cols,
    Rcpp::String& id_col
  ) {
    Rcpp::List lst = sfheaders::shapes::get_lines( df, cols, id_col );
    return to_multilinestring( lst );
  }

  inline SEXP to_multilinestring(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& cols,
      int& id_col
  ) {
    Rcpp::List lst = sfheaders::shapes::get_lines( nm, cols, id_col );
    return to_multilinestring( lst );
  }

  inline SEXP to_multilinestring(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& cols,
      Rcpp::String& id_col
  ) {
    Rcpp::List lst = sfheaders::shapes::get_lines( nm, cols, id_col );
    return to_multilinestring( lst );
  }

  inline SEXP to_multilinestring(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& cols,
      int& id_col
  ) {
    Rcpp::List lst = sfheaders::shapes::get_lines( im, cols, id_col );
    return to_multilinestring( lst );
  }

  inline SEXP to_multilinestring(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& cols,
      Rcpp::String& id_col
  ) {
    Rcpp::List lst = sfheaders::shapes::get_lines( im, cols, id_col );
    return to_multilinestring( lst );
  }

  inline SEXP to_multilinestring(
      SEXP& x,
      Rcpp::IntegerVector& cols
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return to_multilinestring( im, cols );
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return to_multilinestring( nm, cols );
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return to_multilinestring( df, cols );
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_LINESTRING type");
    }
    }

    return Rcpp::List::create(); // never reaches
  }



  inline SEXP to_multilinestring(
      SEXP& x,
      Rcpp::StringVector& cols
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return to_multilinestring( im, cols );
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return to_multilinestring( nm, cols );
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return to_multilinestring( df, cols );
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_MULTILINESTRING type");
    }
    }

    return Rcpp::List::create(); // never reaches
  }


  inline SEXP to_multilinestring(
      SEXP& x
  ) {
    switch ( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return to_multilinestring( im );
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return to_multilinestring( nm );
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      //Rcpp::Rcout << "inherites df : " << std::endl;
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return to_multilinestring( df );
    } else {
      //Rcpp::Rcout << "doesn't inherit df : " << std::endl;
      Rcpp::List lst = Rcpp::as< Rcpp::List >( x );
      return to_multilinestring( lst );
    }
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_MULTILINESTRING type");
    }
    }
    return x; // never reaches
  }

  inline SEXP to_multilinestring(
      SEXP& x,
      SEXP& cols
  ) {
    if( Rf_isNull( cols ) ) {
      return to_multilinestring( x );
    }
    switch( TYPEOF( cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( cols );
      return to_multilinestring( x, iv );
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( cols );
      return to_multilinestring( x, sv );
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
