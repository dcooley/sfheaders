#ifndef R_SFHEADERS_SFG_MULTILINESTRING_H
#define R_SFHEADERS_SFG_MULTILINESTRING_H

#include <Rcpp.h>
#include "sfheaders/utils/utils.hpp"
#include "sfheaders/shapes/shapes.hpp"
#include "sfheaders/sfg/sfg_types.hpp"

namespace sfheaders {
namespace sfg {

  // multilinestring is a list of linestrings (matrices)
  // but can also be a single matrix
  inline SEXP sfg_multilinestring(
      Rcpp::IntegerMatrix& im,
      bool m_only = false
  ) {
    Rcpp::List mls( 1 );
    mls[0] = im;
    R_xlen_t n_col = im.ncol();
    sfheaders::sfg::make_sfg( mls, n_col, sfheaders::sfg::SFG_MULTILINESTRING, m_only );

    return mls;
  }

  inline SEXP sfg_multilinestring(
      Rcpp::IntegerVector& iv,
      bool m_only = false
  ) {
    R_xlen_t n = iv.length();
    Rcpp::IntegerMatrix im( 1, n );
    im( 0, Rcpp::_ ) = iv;
    return sfg_multilinestring( im, m_only );
  }

  inline SEXP sfg_multilinestring(
      Rcpp::NumericMatrix& nm,
      bool m_only = false
  ) {
    Rcpp::List mls( 1 );
    mls[0] = nm;
    R_xlen_t n_col = nm.ncol();
    sfheaders::sfg::make_sfg( mls, n_col, sfheaders::sfg::SFG_MULTILINESTRING, m_only );
    return mls;
  }

  inline SEXP sfg_multilinestring(
      Rcpp::NumericVector& nv,
      bool m_only = false
  ) {
    R_xlen_t n = nv.length();
    Rcpp::NumericMatrix nm( 1, n );
    nm( 0, Rcpp::_ ) = nv;
    return sfg_multilinestring( nm, m_only );
  }

  inline SEXP sfg_multilinestring(
      Rcpp::DataFrame& df,
      bool m_only = false
  ) {
    Rcpp::List mls( 1 );
    Rcpp::NumericMatrix nm = sfheaders::utils::df_to_matrix( df );
    mls[0] = nm;
    R_xlen_t n_col = nm.ncol();
    sfheaders::sfg::make_sfg( mls, n_col, sfheaders::sfg::SFG_MULTILINESTRING, m_only );
    return mls;
  }

  inline SEXP sfg_multilinestring(
    Rcpp::List& lst,
    bool m_only = false
  ) {
    sfheaders::sfg::make_sfg( lst, sfheaders::sfg::SFG_MULTILINESTRING, m_only );
    return lst;
  }


  inline SEXP sfg_multilinestring(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& cols,
      bool m_only = false
  ) {
    Rcpp::NumericMatrix nm = sfheaders::shapes::get_mat( df, cols );
    return sfg_multilinestring( nm, m_only );
  }

  inline SEXP sfg_multilinestring(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& cols,
      bool m_only = false
  ) {
    Rcpp::NumericMatrix nm = sfheaders::shapes::get_mat( df, cols );
    return sfg_multilinestring( nm, m_only );
  }

  inline SEXP sfg_multilinestring(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& cols,
      bool m_only = false
  ) {
    Rcpp::NumericMatrix nm2 = sfheaders::shapes::get_mat( nm, cols );
    return sfg_multilinestring( nm2, m_only );
  }

  inline SEXP sfg_multilinestring(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& cols,
      bool m_only = false
  ) {
    Rcpp::NumericMatrix nm2 = sfheaders::shapes::get_mat( nm, cols );
    return sfg_multilinestring( nm2, m_only );
  }

  inline SEXP sfg_multilinestring(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& cols,
      bool m_only = false
  ) {
    Rcpp::IntegerMatrix im2 = sfheaders::shapes::get_mat( im, cols );
    return sfg_multilinestring( im2, m_only );
  }

  inline SEXP sfg_multilinestring(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& cols,
      bool m_only = false
  ) {
    Rcpp::IntegerMatrix im2 = sfheaders::shapes::get_mat( im, cols );
    return sfg_multilinestring( im2, m_only );
  }

  // We're still on single sfg objects.
  // when we go up to sfc objects then we will need multiline_id & line_id
  inline SEXP sfg_multilinestring(
    Rcpp::DataFrame& df,
    Rcpp::IntegerVector& cols,
    int& id_col,
    bool m_only = false
  ) {
    Rcpp::List lst = sfheaders::shapes::get_listMat( df, cols, id_col );
    return sfg_multilinestring( lst, m_only );
  }

  inline SEXP sfg_multilinestring(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& cols,
    Rcpp::String& id_col,
    bool m_only = false
  ) {
    Rcpp::List lst = sfheaders::shapes::get_listMat( df, cols, id_col );
    return sfg_multilinestring( lst, m_only );
  }

  inline SEXP sfg_multilinestring(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& cols,
      int& id_col,
      bool m_only = false
  ) {
    Rcpp::List lst = sfheaders::shapes::get_listMat( nm, cols, id_col );
    return sfg_multilinestring( lst, m_only );
  }

  inline SEXP sfg_multilinestring(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& cols,
      Rcpp::String& id_col,
      bool m_only = false
  ) {
    Rcpp::List lst = sfheaders::shapes::get_listMat( nm, cols, id_col );
    return sfg_multilinestring( lst, m_only );
  }

  inline SEXP sfg_multilinestring(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& cols,
      int& id_col,
      bool m_only = false
  ) {
    Rcpp::List lst = sfheaders::shapes::get_listMat( im, cols, id_col );
    return sfg_multilinestring( lst, m_only );
  }

  // #nocov start
  inline SEXP sfg_multilinestring(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& cols,
      Rcpp::String& id_col,
      bool m_only = false
  ) {
    Rcpp::List lst = sfheaders::shapes::get_listMat( im, cols, id_col );
    return sfg_multilinestring( lst, m_only );
  }
  // #nocov end

  inline SEXP sfg_multilinestring(
      SEXP& x,
      Rcpp::IntegerVector& cols,
      bool m_only = false
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");  // #nocov
    }
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return sfg_multilinestring( im, cols, m_only );
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");  // #nocov
    }
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return sfg_multilinestring( nm, cols, m_only );
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_multilinestring( df, cols, m_only );
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_LINESTRING type");  // #nocov
    }
    }

    return Rcpp::List::create(); // never reaches
  }



  inline SEXP sfg_multilinestring(
      SEXP& x,
      Rcpp::IntegerVector& cols,
      int& line_id,
      bool m_only = false
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");  // #nocov
    }
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return sfg_multilinestring( im, cols, line_id, m_only );
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");  // #nocov
    }
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return sfg_multilinestring( nm, cols, line_id, m_only );
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_multilinestring( df, cols, line_id, m_only );
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_LINESTRING type"); // #nocov
    }
    }

    return Rcpp::List::create(); // never reaches
  }


  // inline SEXP sfg_multilinestring(
  //     SEXP& x,
  //     Rcpp::IntegerVector& cols,
  //     Rcpp::String& line_id
  // ) {
  //   switch( TYPEOF( x ) ) {
  //   case INTSXP: {
  //     if( !Rf_isMatrix( x ) ) {
  //     Rcpp::stop("sfheaders - expecting a matrix");
  //   }
  //     Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
  //     return sfg_multilinestring( im, cols, line_id );
  //   }
  //   case REALSXP: {
  //     if( !Rf_isMatrix( x ) ) {
  //     Rcpp::stop("sfheaders - expecting a matrix");
  //   }
  //     Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
  //     return sfg_multilinestring( nm, cols, line_id );
  //   }
  //   case VECSXP: {
  //     if( Rf_inherits( x, "data.frame") ) {
  //     Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
  //     return sfg_multilinestring( df, cols, line_id );
  //   } // else default
  //   }
  //   default: {
  //     Rcpp::stop("sfheaders - unsupported sfg_LINESTRING type");
  //   }
  //   }
  //
  //   return Rcpp::List::create(); // never reaches
  // }


  inline SEXP sfg_multilinestring(
      SEXP& x,
      Rcpp::StringVector& cols,
      bool m_only = false
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");  // #nocov
    }
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return sfg_multilinestring( im, cols, m_only );
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");  // #nocov
    }
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return sfg_multilinestring( nm, cols, m_only );
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_multilinestring( df, cols, m_only );
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_MULTILINESTRING type");   // #nocov
    }
    }

    return Rcpp::List::create(); // never reaches
  }

  // inline SEXP sfg_multilinestring(
  //     SEXP& x,
  //     Rcpp::StringVector& cols,
  //     int& line_id
  // ) {
  //   switch( TYPEOF( x ) ) {
  //   case INTSXP: {
  //     if( !Rf_isMatrix( x ) ) {
  //     Rcpp::stop("sfheaders - expecting a matrix");
  //   }
  //     Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
  //     return sfg_multilinestring( im, cols, line_id );
  //   }
  //   case REALSXP: {
  //     if( !Rf_isMatrix( x ) ) {
  //     Rcpp::stop("sfheaders - expecting a matrix");
  //   }
  //     Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
  //     return sfg_multilinestring( nm, cols, line_id );
  //   }
  //   case VECSXP: {
  //     if( Rf_inherits( x, "data.frame") ) {
  //     Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
  //     return sfg_multilinestring( df, cols, line_id );
  //   } // else default
  //   }
  //   default: {
  //     Rcpp::stop("sfheaders - unsupported sfg_MULTILINESTRING type");
  //   }
  //   }
  //
  //   return Rcpp::List::create(); // never reaches
  // }

  inline SEXP sfg_multilinestring(
      SEXP& x,
      Rcpp::StringVector& cols,
      Rcpp::String& line_id,
      bool m_only = false
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");  // #nocov
    }
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return sfg_multilinestring( im, cols, line_id, m_only );
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");  // #nocov
    }
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return sfg_multilinestring( nm, cols, line_id, m_only );
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_multilinestring( df, cols, line_id, m_only );
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_MULTILINESTRING type");   // #nocov
    }
    }

    return Rcpp::List::create(); // never reaches
  }


  inline SEXP sfg_multilinestring(
      SEXP& x,
      bool m_only = false
  ) {
    switch ( TYPEOF( x ) ) {
    case INTSXP: {
    if( !Rf_isMatrix( x ) ) { // #nocov
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x ); // #nocov
      return sfg_multilinestring( iv, m_only );
    }
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return sfg_multilinestring( im, m_only );
    }
    case REALSXP: {
    if( !Rf_isMatrix( x ) ) {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
      return sfg_multilinestring( nv, m_only );
    }
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return sfg_multilinestring( nm, m_only );
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_multilinestring( df, m_only );
    } else {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( x ); // #nocov
      return sfg_multilinestring( lst, m_only );            // #nocov
    }
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_MULTILINESTRING type");  // #nocov
    }
    }
    return x; // never reaches
  }


  inline SEXP sfg_multilinestring(
      SEXP& x,
      SEXP& geometry_cols,
      bool m_only = false
  ) {
    if( Rf_isNull( geometry_cols ) ) {
      return sfg_multilinestring( x );   // #nocov
    }
    switch( TYPEOF( geometry_cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( geometry_cols );
      return sfg_multilinestring( x, iv, m_only );
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( geometry_cols );
      return sfg_multilinestring( x, sv, m_only );
    }
    default: {
      Rcpp::stop("sfheaders - unknown column types");   // #nocov
    }
    }
    return Rcpp::List::create(); // never reaches
  }


  inline SEXP sfg_multilinestring(
      SEXP& x,
      SEXP& cols,
      Rcpp::String& line_id,
      bool m_only = false
  ) {
    if( Rf_isNull( cols ) ) {
      // #nocov start
      Rcpp::StringVector id_cols( 1 );
      id_cols[0] = line_id;
      SEXP other_cols = sfheaders::utils::other_columns( x, id_cols );
      return sfg_multilinestring( x, other_cols, line_id, m_only );
      // #nocov end
    }
    switch( TYPEOF( cols ) ) {
    // case REALSXP: {}
    // case INTSXP: {
    //   Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( cols );
    //   return sfg_multilinestring( x, iv, line_id );
    // }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( cols );
      return sfg_multilinestring( x, sv, line_id, m_only );
    }
    default: {
      Rcpp::stop("sfheaders - unknown column types");   // #nocov
    }
    }
    return Rcpp::List::create(); // never reaches
  }


  inline SEXP sfg_multilinestring(
      SEXP& x,
      SEXP& cols,
      int& line_id,
      bool m_only = false
  ) {

    if( Rf_isNull( cols ) ) {
      // #nocov start
      Rcpp::IntegerVector id_cols( 1 );
      id_cols[0] = line_id;
      SEXP other_cols = sfheaders::utils::other_columns( x, id_cols );
      return sfg_multilinestring( x, other_cols, line_id, m_only );
      // #nocov end
    }
    switch( TYPEOF( cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( cols );
      return sfg_multilinestring( x, iv, line_id, m_only );
    }
    // case STRSXP: {
    //   Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( cols );
    //   return sfg_multilinestring( x, sv, line_id );
    // }
    default: {
      Rcpp::stop("sfheaders - unknown column types");  // #nocov
    }
    }
    return Rcpp::List::create(); // never reaches
  }

  inline SEXP sfg_multilinestring(
      SEXP& x,
      SEXP& cols,
      SEXP& line_id,
      bool m_only = false
  ) {

    if( Rf_isNull( cols ) && Rf_isNull( line_id ) ) {
      return sfg_multilinestring( x, m_only );
    }

    if( !Rf_isNull( line_id ) && Rf_isNull( cols ) ) {
      SEXP other_cols = sfheaders::utils::other_columns( x, line_id );
      return sfg_multilinestring( x, other_cols, line_id, m_only );
    }

    if( Rf_isNull( line_id ) && !Rf_isNull( cols ) ) {
      return sfg_multilinestring( x, cols, m_only );
    }
    switch( TYPEOF( line_id ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( line_id );
      int i = iv[0];
      return sfg_multilinestring( x, cols, i, m_only );
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( line_id );
      Rcpp::String s = sv[0];
      return sfg_multilinestring( x, cols, s, m_only );
    }
    default: {
      Rcpp::stop("sfheaders - unknown column types");  // #nocov
    }
    }
    return Rcpp::List::create(); // never reaches
  }


} // sfg
} // sfheaders

#endif
