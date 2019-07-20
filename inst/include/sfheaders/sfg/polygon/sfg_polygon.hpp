#ifndef R_SFHEADERS_SFG_POLYGON_H
#define R_SFHEADERS_SFG_POLYGON_H

#include <Rcpp.h>
#include "sfheaders/utils/utils.hpp"
#include "sfheaders/shapes/shapes.hpp"
#include "sfheaders/sfg/sfg_attributes.hpp"
#include "sfheaders/sfg/sfg_dimension.hpp"

namespace sfheaders {
namespace sfg {

  // polygon is a list of linestrings (matrices)
  inline SEXP sfg_polygon(
      Rcpp::IntegerMatrix& im
  ) {
    Rcpp::List mls( 1 );
    mls[0] = im;
    size_t n_col = im.ncol();
    std::string dim = sfheaders::sfg::sfg_dimension( n_col );

    std::string geom_type = "POLYGON";
    mls.attr("class") = sfheaders::sfg::sfg_attributes( dim, geom_type );

    return mls;
  }

  inline SEXP sfg_polygon(
      Rcpp::NumericMatrix& nm
  ) {
    Rcpp::List mls( 1 );
    mls[0] = nm;
    size_t n_col = nm.ncol();
    std::string dim = sfheaders::sfg::sfg_dimension( n_col );

    std::string geom_type = "POLYGON";
    mls.attr("class") = sfheaders::sfg::sfg_attributes( dim, geom_type );

    return mls;
  }

  inline SEXP sfg_polygon(
      Rcpp::DataFrame& df
  ) {
    Rcpp::List mls( 1 );
    Rcpp::NumericMatrix nm = sfheaders::utils::df_to_matrix( df );
    mls[0] = nm;
    size_t n_col = nm.ncol();
    //Rcpp::Rcout << "n_col: " << n_col << std::endl;

    std::string dim = sfheaders::sfg::sfg_dimension( n_col );

    std::string geom_type = "POLYGON";
    mls.attr("class") = sfheaders::sfg::sfg_attributes( dim, geom_type );

    return mls;
  }

  inline SEXP sfg_polygon(
      Rcpp::List& lst
  ) {

    // each list element must be a matrix
    std::string dim = sfheaders::sfg::sfg_dimension( lst );

    std::string geom_type = "POLYGON";
    lst.attr("class") = sfheaders::sfg::sfg_attributes( dim, geom_type );

    return lst;
  }


  inline SEXP sfg_polygon(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& cols
  ) {
    Rcpp::NumericMatrix nm = sfheaders::shapes::get_mat( df, cols );
    return sfg_polygon( nm );
  }

  inline SEXP sfg_polygon(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& cols
  ) {
    Rcpp::NumericMatrix nm = sfheaders::shapes::get_mat( df, cols );
    return sfg_polygon( nm );
  }

  inline SEXP sfg_polygon(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& cols
  ) {
    Rcpp::NumericMatrix nm2 = sfheaders::shapes::get_mat( nm, cols );
    return sfg_polygon( nm2 );
  }

  inline SEXP sfg_polygon(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& cols
  ) {
    Rcpp::NumericMatrix nm2 = sfheaders::shapes::get_mat( nm, cols );
    return sfg_polygon( nm2 );
  }

  inline SEXP sfg_polygon(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& cols
  ) {
    Rcpp::IntegerMatrix im2 = sfheaders::shapes::get_mat( im, cols );
    return sfg_polygon( im2 );
  }

  inline SEXP sfg_polygon(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& cols
  ) {
    Rcpp::IntegerMatrix im2 = sfheaders::shapes::get_mat( im, cols );
    return sfg_polygon( im2 );
  }

  // We're still on single sfg objects.
  // when we go up to sfc objects then we will need multiline_id & line_id
  inline SEXP sfg_polygon(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& cols,
      int& id_col
  ) {
    Rcpp::List lst = sfheaders::shapes::get_listMat( df, cols, id_col, 0, 0, false );
    return sfg_polygon( lst );
  }

  inline SEXP sfg_polygon(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& cols,
      Rcpp::String& id_col
  ) {
    Rcpp::List lst = sfheaders::shapes::get_listMat( df, cols, id_col, 0, 0, false );
    return sfg_polygon( lst );
  }

  inline SEXP sfg_polygon(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& cols,
      int& id_col
  ) {
    Rcpp::List lst = sfheaders::shapes::get_listMat( nm, cols, id_col, 0, 0, false );
    return sfg_polygon( lst );
  }

  inline SEXP sfg_polygon(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& cols,
      Rcpp::String& id_col
  ) {
    Rcpp::List lst = sfheaders::shapes::get_listMat( nm, cols, id_col, 0, 0, false );
    return sfg_polygon( lst );
  }

  inline SEXP sfg_polygon(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& cols,
      int& id_col
  ) {
    Rcpp::List lst = sfheaders::shapes::get_listMat( im, cols, id_col, 0, 0, false );
    return sfg_polygon( lst );
  }

  inline SEXP sfg_polygon(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& cols,
      Rcpp::String& id_col
  ) {
    Rcpp::List lst = sfheaders::shapes::get_listMat( im, cols, id_col, 0, 0, false );
    return sfg_polygon( lst );
  }

  inline SEXP sfg_polygon(
      SEXP& x,
      Rcpp::IntegerVector& cols
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return sfg_polygon( im, cols );
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return sfg_polygon( nm, cols );
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_polygon( df, cols );
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_LINESTRING type");
    }
    }

    return Rcpp::List::create(); // never reaches
  }



  inline SEXP sfg_polygon(
      SEXP& x,
      Rcpp::IntegerVector& cols,
      int& line_id
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return sfg_polygon( im, cols, line_id );
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return sfg_polygon( nm, cols, line_id );
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_polygon( df, cols, line_id );
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_LINESTRING type");
    }
    }

    return Rcpp::List::create(); // never reaches
  }


  // inline SEXP sfg_polygon(
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
  //     return sfg_polygon( im, cols, line_id );
  //   }
  //   case REALSXP: {
  //     if( !Rf_isMatrix( x ) ) {
  //     Rcpp::stop("sfheaders - expecting a matrix");
  //   }
  //     Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
  //     return sfg_polygon( nm, cols, line_id );
  //   }
  //   case VECSXP: {
  //     if( Rf_inherits( x, "data.frame") ) {
  //     Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
  //     return sfg_polygon( df, cols, line_id );
  //   } // else default
  //   }
  //   default: {
  //     Rcpp::stop("sfheaders - unsupported sfg_LINESTRING type");
  //   }
  //   }
  //
  //   return Rcpp::List::create(); // never reaches
  // }


  inline SEXP sfg_polygon(
      SEXP& x,
      Rcpp::StringVector& cols
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return sfg_polygon( im, cols );
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return sfg_polygon( nm, cols );
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_polygon( df, cols );
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_POLYGON type");
    }
    }

    return Rcpp::List::create(); // never reaches
  }

  // inline SEXP sfg_polygon(
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
  //     return sfg_polygon( im, cols, line_id );
  //   }
  //   case REALSXP: {
  //     if( !Rf_isMatrix( x ) ) {
  //     Rcpp::stop("sfheaders - expecting a matrix");
  //   }
  //     Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
  //     return sfg_polygon( nm, cols, line_id );
  //   }
  //   case VECSXP: {
  //     if( Rf_inherits( x, "data.frame") ) {
  //     Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
  //     return sfg_polygon( df, cols, line_id );
  //   } // else default
  //   }
  //   default: {
  //     Rcpp::stop("sfheaders - unsupported sfg_POLYGON type");
  //   }
  //   }
  //
  //   return Rcpp::List::create(); // never reaches
  // }

  inline SEXP sfg_polygon(
      SEXP& x,
      Rcpp::StringVector& cols,
      Rcpp::String& line_id
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return sfg_polygon( im, cols, line_id );
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return sfg_polygon( nm, cols, line_id );
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_polygon( df, cols, line_id );
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_POLYGON type");
    }
    }

    return Rcpp::List::create(); // never reaches
  }


  inline SEXP sfg_polygon(
      SEXP& x
  ) {
    switch ( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return sfg_polygon( im );
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return sfg_polygon( nm );
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_polygon( df );
    } else {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( x );
      return sfg_polygon( lst );
    }
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_POLYGON type");
    }
    }
    return x; // never reaches
  }


  inline SEXP sfg_polygon(
      SEXP& x,
      SEXP& cols
  ) {
    if( Rf_isNull( cols ) ) {
      return sfg_polygon( x );
    }
    switch( TYPEOF( cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( cols );
      return sfg_polygon( x, iv );
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( cols );
      return sfg_polygon( x, sv );
    }
    default: {
      Rcpp::stop("sfheaders - unknown column types");
    }
    }
    return Rcpp::List::create(); // never reaches
  }


  inline SEXP sfg_polygon(
      SEXP& x,
      SEXP& cols,
      Rcpp::String& line_id
  ) {
    if( Rf_isNull( cols ) ) {
      //Rcpp::Rcout << "String line_id" << std::endl;
      Rcpp::StringVector id_cols( 1 );
      id_cols[0] = line_id;
      SEXP other_cols = sfheaders::utils::other_columns( x, id_cols );
      return sfg_polygon( x, other_cols, line_id );
    }
    switch( TYPEOF( cols ) ) {
    // case REALSXP: {}
    // case INTSXP: {
    //   Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( cols );
    //   return sfg_polygon( x, iv, line_id );
    // }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( cols );
      return sfg_polygon( x, sv, line_id );
    }
    default: {
      Rcpp::stop("sfheaders - unknown column types");
    }
    }
    return Rcpp::List::create(); // never reaches
  }


  inline SEXP sfg_polygon(
      SEXP& x,
      SEXP& cols,
      int& line_id
  ) {

    if( Rf_isNull( cols ) ) {
      Rcpp::IntegerVector id_cols( 1 );
      id_cols[0] = line_id;
      SEXP other_cols = sfheaders::utils::other_columns( x, id_cols );
      return sfg_polygon( x, other_cols, line_id );
    }
    switch( TYPEOF( cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( cols );
      return sfg_polygon( x, iv, line_id );
    }
      // case STRSXP: {
      //   Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( cols );
      //   return sfg_polygon( x, sv, line_id );
      // }
    default: {
      Rcpp::stop("sfheaders - unknown column types");
    }
    }
    return Rcpp::List::create(); // never reaches
  }

  inline SEXP sfg_polygon(
      SEXP& x,
      SEXP& cols,
      SEXP& line_id
  ) {
    if( Rf_isNull( line_id ) ) {
      return sfg_polygon( x, cols );
    }
    switch( TYPEOF( line_id ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( line_id );
      int i = iv[0];
      return sfg_polygon( x, cols, i );
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( line_id );
      Rcpp::String s = sv[0];
      return sfg_polygon( x, cols, s );
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
