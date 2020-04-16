#ifndef R_SFHEADERS_SFG_POLYGON_H
#define R_SFHEADERS_SFG_POLYGON_H

#include <Rcpp.h>
#include "sfheaders/utils/utils.hpp"
#include "sfheaders/sfg/polygon/close_polygon.hpp"
#include "sfheaders/shapes/shapes.hpp"
#include "sfheaders/sfg/sfg_types.hpp"

namespace sfheaders {
namespace sfg {

  // polygon is a list of linestrings (matrices)
  inline SEXP sfg_polygon(
      Rcpp::IntegerMatrix& im,
      std::string xyzm,
      bool close = true
  ) {
    Rcpp::List mls( 1 );
    mls[0] = sfheaders::polygon_utils::close_polygon( im, close );
    R_xlen_t n_col = im.ncol();

    sfheaders::sfg::make_sfg( mls, n_col, sfheaders::sfg::SFG_POLYGON, xyzm );

    return mls;
  }

  inline SEXP sfg_polygon(
      Rcpp::NumericMatrix& nm,
      std::string xyzm,
      bool close = true
  ) {
    Rcpp::List mls( 1 );
    mls[0] = sfheaders::polygon_utils::close_polygon( nm, close );;
    R_xlen_t n_col = nm.ncol();

    sfheaders::sfg::make_sfg( mls, n_col, sfheaders::sfg::SFG_POLYGON, xyzm );

    return mls;
  }

  inline SEXP sfg_polygon(
      Rcpp::DataFrame& df,
      std::string xyzm,
      bool close = true
  ) {
    Rcpp::List mls( 1 );
    Rcpp::NumericMatrix nm = sfheaders::utils::df_to_matrix( df );
    mls[0] = sfheaders::polygon_utils::close_polygon( nm, close );;
    R_xlen_t n_col = nm.ncol();

    sfheaders::sfg::make_sfg( mls, n_col, sfheaders::sfg::SFG_POLYGON, xyzm );

    return mls;
  }

  inline SEXP sfg_polygon(
      Rcpp::List& lst,
      std::string xyzm,
      bool close = true
  ) {

    lst = sfheaders::polygon_utils::close_polygon( lst, close );
    sfheaders::sfg::make_sfg( lst, sfheaders::sfg::SFG_POLYGON, xyzm );

    return lst;
  }


  inline SEXP sfg_polygon(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& cols,
      std::string xyzm,
      bool close = true
  ) {
    Rcpp::NumericMatrix nm = sfheaders::shapes::get_mat( df, cols );
    return sfg_polygon( nm, xyzm, close );
  }

  inline SEXP sfg_polygon(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& cols,
      std::string xyzm,
      bool close = true
  ) {
    Rcpp::NumericMatrix nm = sfheaders::shapes::get_mat( df, cols );
    return sfg_polygon( nm, xyzm, close );
  }

  inline SEXP sfg_polygon(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& cols,
      std::string xyzm,
      bool close = true
  ) {
    Rcpp::NumericMatrix nm2 = sfheaders::shapes::get_mat( nm, cols );
    return sfg_polygon( nm2, xyzm, close );
  }

  inline SEXP sfg_polygon(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& cols,
      std::string xyzm,
      bool close = true
  ) {
    Rcpp::NumericMatrix nm2 = sfheaders::shapes::get_mat( nm, cols );
    return sfg_polygon( nm2, xyzm, close );
  }

  inline SEXP sfg_polygon(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& cols,
      std::string xyzm,
      bool close = true
  ) {
    Rcpp::IntegerMatrix im2 = sfheaders::shapes::get_mat( im, cols );
    return sfg_polygon( im2, xyzm, close );
  }

  inline SEXP sfg_polygon(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& cols,
      std::string xyzm,
      bool close = true
  ) {
    Rcpp::IntegerMatrix im2 = sfheaders::shapes::get_mat( im, cols );
    return sfg_polygon( im2, xyzm, close );
  }

  // We're still on single sfg objects.
  // when we go up to sfc objects then we will need multiline_id & line_id
  inline SEXP sfg_polygon(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& cols,
      int& id_col,
      std::string xyzm,
      bool close = true
  ) {
    Rcpp::List lst = sfheaders::shapes::get_listMat( df, cols, id_col );
    return sfg_polygon( lst, xyzm, close );
  }

  inline SEXP sfg_polygon(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& cols,
      Rcpp::String& id_col,
      std::string xyzm,
      bool close = true
  ) {
    Rcpp::List lst = sfheaders::shapes::get_listMat( df, cols, id_col );
    return sfg_polygon( lst, xyzm, close );
  }

  inline SEXP sfg_polygon(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& cols,
      int& id_col,
      std::string xyzm,
      bool close = true
  ) {
    Rcpp::List lst = sfheaders::shapes::get_listMat( nm, cols, id_col );
    return sfg_polygon( lst, xyzm, close );
  }

  inline SEXP sfg_polygon(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& cols,
      Rcpp::String& id_col,
      std::string xyzm,
      bool close = true
  ) {
    Rcpp::List lst = sfheaders::shapes::get_listMat( nm, cols, id_col );
    return sfg_polygon( lst, xyzm, close );
  }

  inline SEXP sfg_polygon(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& cols,
      int& id_col,
      std::string xyzm,
      bool close = true
  ) {
    Rcpp::List lst = sfheaders::shapes::get_listMat( im, cols, id_col );
    return sfg_polygon( lst, xyzm, close );
  }

  inline SEXP sfg_polygon(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& cols,
      Rcpp::String& id_col,
      std::string xyzm,
      bool close = true
  ) {
    Rcpp::List lst = sfheaders::shapes::get_listMat( im, cols, id_col );
    return sfg_polygon( lst, xyzm, close );
  }

  inline SEXP sfg_polygon(
      SEXP& x,
      Rcpp::IntegerVector& cols,
      std::string xyzm,
      bool close = true
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return sfg_polygon( im, cols, xyzm, close );
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return sfg_polygon( nm, cols, xyzm, close );
    }
    case VECSXP: {
      // #nocov start
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_polygon( df, cols, xyzm, close);
      // #nocov end
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_POLYGON type");  // #nocov
    }
    }

    return Rcpp::List::create(); // never reaches
  }



  inline SEXP sfg_polygon(
      SEXP& x,
      Rcpp::IntegerVector& cols,
      int& line_id,
      std::string xyzm,
      bool close = true
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return sfg_polygon( im, cols, line_id, xyzm, close);
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return sfg_polygon( nm, cols, line_id, xyzm, close);
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_polygon( df, cols, line_id, xyzm, close);
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_POLYGON type");  // #nocov
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
      Rcpp::StringVector& cols,
      std::string xyzm,
      bool close = true
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return sfg_polygon( im, cols, xyzm, close);
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return sfg_polygon( nm, cols, xyzm, close);
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_polygon( df, cols, xyzm, close);
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_POLYGON type");  // #nocov
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
      Rcpp::String& line_id,
      std::string xyzm,
      bool close = true
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return sfg_polygon( im, cols, line_id, xyzm, close);
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return sfg_polygon( nm, cols, line_id, xyzm, close);
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_polygon( df, cols, line_id, xyzm, close);
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_POLYGON type"); // #nocov
    }
    }

    return Rcpp::List::create(); // never reaches
  }


  inline SEXP sfg_polygon(
      SEXP& x,
      std::string xyzm,
      bool close = true
  ) {
    switch ( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return sfg_polygon( im, xyzm, close);
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting a matrix");
    }
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return sfg_polygon( nm, xyzm, close);
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return sfg_polygon( df, xyzm, close);
    } else {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( x ); // #nocov
      return sfg_polygon( lst, xyzm, close);                    // #nocov
    }
    }
    default: {
      Rcpp::stop("sfheaders - unsupported sfg_POLYGON type");  // #nocov
    }
    }
    return x; // never reaches
  }


  inline SEXP sfg_polygon(
      SEXP& x,
      SEXP& cols,
      std::string xyzm,
      bool close = true
  ) {
    if( Rf_isNull( cols ) ) {
      return sfg_polygon( x, xyzm, close);
    }
    switch( TYPEOF( cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( cols );
      return sfg_polygon( x, iv, xyzm, close);
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( cols );
      return sfg_polygon( x, sv, xyzm, close);
    }
    default: {
      Rcpp::stop("sfheaders - unknown column types");  // #nocov
    }
    }
    return Rcpp::List::create(); // never reaches
  }


  inline SEXP sfg_polygon(
      SEXP& x,
      SEXP& cols,
      Rcpp::String& line_id,
      std::string xyzm,
      bool close = true
  ) {
    if( Rf_isNull( cols ) ) {
      // #nocov start
      Rcpp::StringVector id_cols( 1 );
      id_cols[0] = line_id;
      SEXP other_cols = sfheaders::utils::other_columns( x, id_cols );
      return sfg_polygon( x, other_cols, line_id, xyzm, close);
      // #nocov end
    }
    switch( TYPEOF( cols ) ) {
    // case REALSXP: {}
    // case INTSXP: {
    //   Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( cols );
    //   return sfg_polygon( x, iv, line_id );
    // }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( cols );
      return sfg_polygon( x, sv, line_id, xyzm, close);
    }
    default: {
      Rcpp::stop("sfheaders - unknown column types"); // #nocov
    }
    }
    return Rcpp::List::create(); // never reaches
  }


  inline SEXP sfg_polygon(
      SEXP& x,
      SEXP& cols,
      int& line_id,
      std::string xyzm,
      bool close = true
  ) {

    if( Rf_isNull( cols ) ) {
      // #nocov start
      Rcpp::IntegerVector id_cols( 1 );
      id_cols[0] = line_id;
      SEXP other_cols = sfheaders::utils::other_columns( x, id_cols );
      return sfg_polygon( x, other_cols, line_id, xyzm, close);
      // #nocov end
    }
    switch( TYPEOF( cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( cols );
      return sfg_polygon( x, iv, line_id, xyzm, close);
    }
      // case STRSXP: {
      //   Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( cols );
      //   return sfg_polygon( x, sv, line_id );
      // }
    default: {
      Rcpp::stop("sfheaders - unknown column types");  // #nocov
    }
    }
    return Rcpp::List::create(); // never reaches
  }

  inline SEXP sfg_polygon(
      SEXP& x,
      SEXP& cols,
      SEXP& line_id,
      std::string xyzm,
      bool close = true
  ) {
    if( Rf_isNull( line_id ) ) {
      return sfg_polygon( x, cols, xyzm, close);
    }
    switch( TYPEOF( line_id ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( line_id );
      int i = iv[0];
      return sfg_polygon( x, cols, i, xyzm, close);
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( line_id );
      Rcpp::String s = sv[0];
      return sfg_polygon( x, cols, s, xyzm, close);
    }
    default: {
      Rcpp::stop("sfheaders - unknown column types");  // #nocov
    }
    }
    return Rcpp::List::create(); // never reaches
  }

  inline SEXP remove_polygon_holes(
      Rcpp::List& sfg_poly,
      std::string xyzm,
      bool close = true
  ){
    Rcpp::List res(1);
    res[0] = sfg_poly[0];
    return sfg_polygon( res, xyzm, close);
  }


  // sfg_box will convert a bounding-box 4-value vector into a polygon
  template< int RTYPE >
  inline SEXP sfg_box( Rcpp::Vector< RTYPE > x ) {
    if ( x.length() != 4 ) {
      Rcpp::stop("sfheaders - box requires a 4-value vector");
    }

    Rcpp::Matrix< RTYPE > mat( 5, 2 );
    Rcpp::IntegerVector bl = {0,1};
    Rcpp::IntegerVector br = {2,1};
    Rcpp::IntegerVector tr = {2,3};
    Rcpp::IntegerVector tl = {0,3};

    Rcpp::Vector< RTYPE > blv = x[ bl ];
    Rcpp::Vector< RTYPE > brv = x[ br ];
    Rcpp::Vector< RTYPE > trv = x[ tr ];
    Rcpp::Vector< RTYPE > tlv = x[ tl ];

    mat( 0, Rcpp::_ ) = blv;
    mat( 1, Rcpp::_ ) = brv;
    mat( 2, Rcpp::_ ) = trv;
    mat( 3, Rcpp::_ ) = tlv;
    mat( 4, Rcpp::_ ) = blv;

    std::string xyzm = "XY";
    bool close = false;
    return sfg_polygon( mat, xyzm, close );
  }

} // sfg
} // sfheaders

#endif
