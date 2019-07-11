#ifndef R_SFHEADERS_UTILS_COLUMNS_H
#define R_SFHEADERS_UTILS_COLUMNS_H

#include <Rcpp.h>
#include "sfheaders/utils/matrix/matrix.hpp"
#include "sfheaders/utils/sexp/sexp.hpp"

namespace sfheaders {
namespace utils {

  // if the line_id cols are supplied, but the geometry_cols are not
  // we need to know the rest of the columns so we can supply them
  inline SEXP other_columns(
      Rcpp::IntegerVector& other_cols,
      Rcpp::IntegerVector& id_cols
  ) {

    // Can't use SETDIFF because I need the order maintained
    // Rcpp::IntegerVector iv = Rcpp::setdiff( other_cols, id_cols );
    // return iv;

    int n_id_cols = id_cols.length();
    int i;
    for( i = (n_id_cols - 1); i >= 0; i-- ) {
      int to_remove = id_cols[ i ];
      other_cols.erase( to_remove );
    }
    return other_cols;
  }

  inline SEXP other_columns(
      Rcpp::NumericVector& other_cols,
      Rcpp::NumericVector& id_cols
  ) {

    // Rcpp::Rcout << "other_cols: " << other_cols << std::endl;
    // Rcpp::Rcout << "id_cols: " << id_cols << std::endl;

    // Rcpp::NumericVector nv = Rcpp::setdiff( other_cols, id_cols );
    // return nv;

    int n_id_cols = id_cols.length();
    int i;
    for( i = (n_id_cols - 1); i >= 0; i-- ) {
      int to_remove = id_cols[ i ];
      other_cols.erase( to_remove );
    }
    // Rcpp::Rcout << "erased columns, left with : " << other_cols << std::endl;
    return other_cols;
  }


  inline SEXP other_columns(
      Rcpp::StringVector& all_cols,
      Rcpp::StringVector& id_cols
  ) {

    // Rcpp::StringVector sv = Rcpp::setdiff( all_cols, id_cols );
    // return sv;
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
      Rcpp::DataFrame& df,
      Rcpp::NumericVector& id_cols
  ) {
    int n_col = df.ncol();

    // Rcpp::Rcout << "n_col: " << n_col << std::endl;

    Rcpp::IntegerVector other_cols = Rcpp::seq( 0, n_col - 1 );
    Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( other_cols );
    return other_columns( nv, id_cols );
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
      Rcpp::NumericMatrix& nm,
      Rcpp::NumericVector& id_cols
  ) {
    int n_col = nm.ncol();
    Rcpp::IntegerVector other_cols = Rcpp::seq( 0, n_col - 1 );
    Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( other_cols );
    return other_columns( nv, id_cols );
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
      Rcpp::IntegerMatrix& im,
      Rcpp::NumericVector& id_cols
  ) {
    int n_col = im.ncol();
    Rcpp::IntegerVector im_cols = Rcpp::seq( 0, n_col - 1 );
    Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( im_cols );
    return other_columns( nv, id_cols );
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
      Rcpp::NumericVector& id_cols
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
    case REALSXP: {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( id_cols );
      return other_columns( x, nv );
    }
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

  // when 2 columns are known
  inline SEXP other_columns(
    SEXP& x,
    SEXP& col_1,
    SEXP& col_2
  ) {

    if( Rf_isNull( col_1 ) ) {
      return other_columns( x, col_2 );
    }

    if( Rf_isNull( col_2 ) ) {
      return other_columns( x, col_1 );
    }

    if( TYPEOF( col_1 ) != TYPEOF( col_2) ) {
      Rcpp::stop("sfheaders - different column types found");
    }

    // else - combine col_1 & col_2 into a single vector
    int n_1 = sfheaders::utils::get_sexp_length( col_1 );
    int n_2 = sfheaders::utils::get_sexp_length( col_2 );
    int n = n_1 + n_2;
    int i;

    switch(TYPEOF( col_1 ) ) {
    case INTSXP: {
      Rcpp::IntegerVector iv_1 = Rcpp::as< Rcpp::IntegerVector >( col_1 );
      Rcpp::IntegerVector iv_2 = Rcpp::as< Rcpp::IntegerVector >( col_2 );

      Rcpp::IntegerVector iv( n );

      if( n_1 == 1 ) {
        iv[0] = iv_1[0];
      } else {
        for( i = 0; i < n_1; i++ ) {
          iv[i] = iv_1[i];
        }
      }

      if( n_2 == 1 ) {
        iv[ n_1 ] = iv_2[0];
      } else {
        int idx = 0;
        for( i = n_1; i < n; i++ ) {
          iv[i] = iv_2[ idx ];
          idx++;
        }
      }

      Rcpp::IntegerVector iv2 = Rcpp::sort_unique( iv );

      return other_columns( x, iv2 );
    }
    case REALSXP: {
      Rcpp::NumericVector nv_1 = Rcpp::as< Rcpp::NumericVector >( col_1 );
      Rcpp::NumericVector nv_2 = Rcpp::as< Rcpp::NumericVector >( col_2 );

      Rcpp::NumericVector nv( n );

      if( n_1 == 1 ) {
        nv[0] = nv_1[0];
      } else {
        for( i = 0; i < n_1; i++ ) {
          nv[i] = nv_1[i];
        }
      }

      if( n_2 == 1 ) {
        nv[ n_1 ] = nv_2[0];
      } else {
        int idx = 0;
        for( i = n_1; i < n; i++ ) {
          nv[i] = nv_2[ idx ];
          idx++;
        }
      }

      Rcpp::NumericVector nv2 = Rcpp::sort_unique( nv );

      return other_columns( x, nv2 );
    }
    case STRSXP: {
      Rcpp::StringVector sv_1 = Rcpp::as< Rcpp::StringVector >( col_1 );
      Rcpp::StringVector sv_2 = Rcpp::as< Rcpp::StringVector >( col_2 );

      Rcpp::StringVector sv( n );

      for( i = 0; i < n_1; i++ ) {
        sv[i] = sv_1[i];
      }

      int idx = 0;
      for( i = n_1; i < n; i++ ) {
        sv[i] = sv_2[ idx ];
        idx++;
      }

      return other_columns( x, sv );
    }
    default: {
      Rcpp::stop("sfheaders - can't combine columns");
    }
    }

  }

    inline SEXP other_columns(
        SEXP& x,
        SEXP& col_1,
        SEXP& col_2,
        SEXP& col_3
    ) {

      if( !Rf_isNull( col_1 ) && Rf_isNull( col_2 ) && Rf_isNull( col_3 ) ) {
        return other_columns( x, col_1 );
      }

      if( Rf_isNull( col_1 ) && !Rf_isNull( col_2 ) && Rf_isNull( col_3 ) ) {
        return other_columns( x, col_2 );
      }

      if( Rf_isNull( col_1 ) && Rf_isNull( col_2 ) && !Rf_isNull( col_3 ) ) {
        return other_columns( x, col_3 );
      }

      if( Rf_isNull( col_1) && !Rf_isNull( col_2 ) && !Rf_isNull( col_3 ) ) {
        return other_columns( x, col_2, col_3 );
      }

      if ( !Rf_isNull( col_1 ) && Rf_isNull( col_2 ) && !Rf_isNull( col_3 ) ) {
        return other_columns( x, col_1, col_3 );
      }

      if ( !Rf_isNull( col_1 ) && !Rf_isNull( col_2 ) && Rf_isNull( col_3 ) ) {
        return other_columns( x, col_1, col_2 );
      }


      Rcpp::stop("sfheaders - not yet implemented this other_columns function yet");
      // SEXP other_cols1 = other_columns(x, col_1, col_2);
      // SEXP other_cols2 = other_columns(x, col_1, col_3);
      // return other_columns( x, other_cols1, other_cols2 );
    }

} // utils
} // sfheaders

#endif
