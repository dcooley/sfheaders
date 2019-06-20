#ifndef R_SFHEADERS_UTILS_H
#define R_SFHEADERS_UTILS_H

#include <Rcpp.h>

namespace sfheaders {
namespace utils {

  inline Rcpp::NumericMatrix df_to_matrix(
    Rcpp::DataFrame& df
  ) {
    int i;
    int n_cols = df.cols();
    int n_rows = df.rows();
    Rcpp::StringVector df_names = df.names();
    Rcpp::NumericMatrix nm( n_rows, n_cols );
    for( i = 0; i < n_cols; i++ ) {
      Rcpp::NumericVector this_column = Rcpp::as< Rcpp::NumericVector >( df[ i ] );
      nm( Rcpp::_, i ) = this_column;
    }
    //nm.names() = df_names;
    Rcpp::List m_attr(2);
    m_attr(1) = df_names;
    //Rcpp::Rcout << "here" << std::endl;
    nm.attr("dimnames") = m_attr;
    return nm;
  }

  inline Rcpp::StringVector matrix_names(
    Rcpp::List m_attr
  ) {
    Rcpp::StringVector matrix_names = m_attr[1];
    return matrix_names;
  }

  inline Rcpp::StringVector matrix_names(
    Rcpp::IntegerMatrix& m
  ) {
    Rcpp::List m_attr = m.attr("dimnames");
    return matrix_names( m_attr );
  }

  inline Rcpp::StringVector matrix_names(
    Rcpp::NumericMatrix& m
  ) {
    Rcpp::List m_attr = m.attr("dimnames");
    return matrix_names( m_attr );
  }

  /* line_ids
   *
   * returns a 2-colummn matrix giving the start & end locations in a vector of'ids'
   * where the ids start & end
   *
   */
  inline Rcpp::IntegerMatrix line_ids(
    Rcpp::NumericVector& line_ids,
    Rcpp::NumericVector& unique_ids
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
    Rcpp::StringVector nm_names = matrix_names( nm );
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
    Rcpp::StringVector im_names = matrix_names( im );
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
