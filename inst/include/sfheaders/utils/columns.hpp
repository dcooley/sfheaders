#ifndef R_SFHEADERS_UTILS_COLUMNS_H
#define R_SFHEADERS_UTILS_COLUMNS_H

#include <Rcpp.h>

namespace sfheaders {
namespace utils {

  // if the line_id cols are supplied, but the geometry_cols are not
  // we need to know the rest of the columns so we can supply them
  inline SEXP other_columns(
      Rcpp::IntegerVector& other_cols,
      Rcpp::IntegerVector& id_cols
  ) {
    int n_id_cols = id_cols.length();
    int i;
    for( i = 0; i < n_id_cols; i++ ) {
      int to_remove = id_cols[ i ];
      other_cols.erase( to_remove );
    }
    return other_cols;
  }


  inline SEXP other_columns(
      Rcpp::StringVector& all_cols,
      Rcpp::StringVector& id_cols
  ) {
    int n_id_cols = id_cols.size();
    int n_other_cols = all_cols.size();
    int i, j;
    bool is_in = false;
    Rcpp::IntegerVector id_col_index( n_id_cols );
    for( i = 0; i < n_id_cols; i++ ) {
      is_in = false;
      Rcpp::String id_col = id_cols[i];
      for( j = 0; j < n_other_cols; j++ ) {
        Rcpp::String a_col = all_cols[j];
        if( id_col == a_col ) {
          // this column is one of the id ones, so we shouldn't keep it.
          is_in = true;
          break;
        }
      }
      if( is_in ) {
        all_cols.erase( j );
      }
    }
    return all_cols;
    //return other_cols;
  }

  inline SEXP other_columns(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& id_cols
  ) {
    Rcpp::StringVector df_names = df.names();
    return other_columns( df_names, id_cols );
  }

  inline SEXP other_columns(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& id_cols
  ) {
    int n_col = df.ncol();
    Rcpp::IntegerVector other_cols = Rcpp::seq( 0, n_col - 1 );
    return other_columns( other_cols, id_cols );
  }

  inline SEXP other_columns(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& id_cols
  ) {
    Rcpp::StringVector nm_names = sfheaders::utils::matrix_names( nm );
    return other_columns( nm_names, id_cols );
  }

  inline SEXP other_columns(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& id_cols
  ) {
    int n_col = nm.ncol();
    Rcpp::IntegerVector other_cols = Rcpp::seq( 0, n_col - 1 );
    return other_columns( other_cols, id_cols );
  }

  inline SEXP other_columns(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& id_cols
  ) {
    Rcpp::StringVector im_names = sfheaders::utils::matrix_names( im );
    return other_columns( im_names, id_cols );
  }

  inline SEXP other_columns(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& id_cols
  ) {
    int n_col = im.ncol();
    Rcpp::IntegerVector im_cols = Rcpp::seq( 0, n_col - 1 );
    return other_columns( im_cols, id_cols );
  }


  inline SEXP other_columns(
      SEXP& x,
      Rcpp::IntegerVector& id_cols
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x ) ;
      return other_columns( im, id_cols );
    }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return other_columns( nm, id_cols );
    }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return other_columns( df, id_cols );
    }
    }
    default: {
      Rcpp::stop("sfheaders - unsupported object");
    }
    }
  }

  inline SEXP other_columns(
      SEXP& x,
      Rcpp::StringVector& id_cols
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x ) ;
      return other_columns( im, id_cols );
    }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return other_columns( nm, id_cols );
    }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return other_columns( df, id_cols );
    }
    }
    default: {
      Rcpp::stop("sfheaders - unsupported object");
    }
    }
  }


  inline SEXP other_columns(
      SEXP& x,
      SEXP& id_cols // will be a vector
  ) {
    switch( TYPEOF( id_cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( id_cols );
      return other_columns( x, iv );
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( id_cols );
      return other_columns( x, sv );
    }
    default: {
      Rcpp::stop("sfheaders - unsupported column types");
    }
    }
  }

} // utils
} // sfheaders

#endif
