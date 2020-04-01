#ifndef R_SFHEADERS_M_RANGE_H
#define R_SFHEADERS_M_RANGE_H

#include <Rcpp.h>
#include "sfheaders/utils/sexp/sexp.hpp"

namespace sfheaders {
namespace zm {

  inline void attach_m_range_attributes( Rcpp::NumericVector& m_range ) {
    m_range.attr("class") = Rcpp::CharacterVector::create("m_range");
    m_range.attr("names") = Rcpp::CharacterVector::create("mmin","mmax");
  }

  inline Rcpp::NumericVector start_m_range() {
    Rcpp::NumericVector range(2);
    range(0) = range(1) = NA_REAL;
    return range;
  }


  inline void m_range_size_check( Rcpp::IntegerVector& point, std::string xyzm ) {
    int size_required = xyzm == "XYM" ? 3 : 4;
    if( point.length() < size_required ) {
      Rcpp::stop("sfheaders - incorrect size of m_range");
    }
  }

  inline void m_range_size_check( Rcpp::NumericVector& point, std::string xyzm ) {
    int size_required = xyzm == "XYM" ? 3 : 4;
    if( point.length() < size_required ) {
      Rcpp::stop("sfheaders - incorrect size of m_range");
    }
  }

  inline void m_range_size_check( Rcpp::IntegerMatrix& im, std::string xyzm ) {
    int size_required = xyzm == "XYM" ? 3 : 4;
    if( im.ncol() < size_required ) {
      Rcpp::stop("sfheaders - incorrect size of m_range");
    }
  }

  inline void m_range_size_check( Rcpp::NumericMatrix& nm, std::string xyzm ) {
    int size_required = xyzm == "XYM" ? 3 : 4;
    if( nm.ncol() < size_required ) {
      Rcpp::stop("sfheaders - incorrect size of m_range");
    }
  }

  inline void m_range_size_check( Rcpp::DataFrame& df, std::string xyzm ) {
    int size_required = xyzm == "XYM" ? 3 : 4;
    if( df.ncol() < size_required ) {
      Rcpp::stop("sfheaders - incorrect size of m_range");
    }
  }

  inline void m_range_size_check( SEXP& x, std::string xyzm ) {
    int size_required = xyzm == "XYM" ? 3 : 4;
    R_xlen_t n_col = sfheaders::utils::get_sexp_n_col( x );
    if( n_col < size_required ) {
      Rcpp::stop("sfheaders - incorrect size of m_range");
    }
  }


  inline void calculate_m_range(
      Rcpp::NumericVector& m_range,
      double& val
  ) {

    //xmin, ymin, xmax, ymax
    m_range[0] = std::min( val, m_range[0] );
    m_range[1] = std::max( val, m_range[1] );
  }

  inline void calculate_m_range(
      Rcpp::NumericVector& m_range,
      int& val
  ) {
    double d = static_cast< double >( val );
    calculate_m_range( m_range, d );
  }


  inline void calculate_m_range(
      Rcpp::NumericVector& m_range,
      Rcpp::NumericVector& point,
      std::string xyzm
  ) {
    m_range_size_check( point, xyzm );

    double d = xyzm == "XYM" ? point[2] : point[3];
    //xmin, ymin, xmax, ymax
    m_range[0] = std::min( d, m_range[0] );
    m_range[1] = std::max( d, m_range[1] );
  }

  inline void calculate_m_range(
      Rcpp::NumericVector& m_range,
      Rcpp::IntegerVector& point,
      std::string xyzm
  ) {
    m_range_size_check( point, xyzm );

    int i = xyzm == "XYM" ? point[2] : point[3];

    double d = static_cast< double >( i );
    calculate_m_range( m_range, d );
  }

  inline void calculate_m_range(
      Rcpp::NumericVector& m_range,
      Rcpp::IntegerMatrix& im,
      std::string xyzm
  ) {

    m_range_size_check( im, xyzm );

    Rcpp::IntegerVector m = xyzm == "XYM" ? im( Rcpp::_, 2 ) : im( Rcpp::_, 3 );

    double zmin = Rcpp::min( m );
    double zmax = Rcpp::max( m );

    m_range[0] = std::min( zmin, m_range[0] );
    m_range[1] = std::max( zmax, m_range[1] );

  }

  inline void calculate_m_range(
      Rcpp::NumericVector& m_range,
      Rcpp::NumericMatrix& nm,
      std::string xyzm
  ) {

    m_range_size_check( nm, xyzm );

    Rcpp::NumericVector m = xyzm == "XYM" ? nm( Rcpp::_, 2 ) : nm( Rcpp::_, 3 );

    double zmin = Rcpp::min( m );
    double zmax = Rcpp::max( m );

    m_range[0] = std::min( zmin, m_range[0] );
    m_range[1] = std::max( zmax, m_range[1] );

  }

  inline void calculate_m_range(
      Rcpp::NumericVector& m_range,
      Rcpp::DataFrame& df,
      std::string xyzm
  ) {
    // assumes 'x' & 'y' column vectors
    m_range_size_check( df, xyzm );

    Rcpp::NumericVector m = xyzm == "XYM" ? df[2] : df[3];

    double zmin = Rcpp::min( m );
    double zmax = Rcpp::max( m );

    m_range[0] = std::min( zmin, m_range[0] );
    m_range[1] = std::max( zmax, m_range[1] );

  }

  inline void calculate_m_range(
      Rcpp::NumericVector& m_range,
      SEXP& x,
      std::string xyzm
  ) {

    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      calculate_m_range( m_range, im, xyzm );
    } else {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
      calculate_m_range( m_range, iv, xyzm );
    }
    break;
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      calculate_m_range( m_range, nm, xyzm );
    } else {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
      calculate_m_range( m_range, nv, xyzm );
    }
    break;
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      calculate_m_range( m_range, df, xyzm );
      break;
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - can't calculate bounding box for this type");  // #nocov
    }
    }
  }

  // #nocov start
  inline void calculate_m_range(
      Rcpp::NumericVector& m_range,
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& geometry_cols,
      std::string xyzm
  ) {

    int index_required = xyzm == "XYM" ? 2 : 3;

    if( geometry_cols.length() > index_required ) {
      int idx = geometry_cols[ index_required ];
      Rcpp::IntegerVector m = im( Rcpp::_, idx );
      double zmin = Rcpp::min( m );
      double zmax = Rcpp::max( m );

      m_range[0] = std::min( zmin, m_range[0] );
      m_range[1] = std::max( zmax, m_range[1] );
    }
  }

  inline void calculate_m_range(
      Rcpp::NumericVector& m_range,
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& geometry_cols,
      std::string xyzm
  ) {

    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );

    int index_required = xyzm == "XYM" ? 2 : 3;

    if( geometry_cols.length() > index_required ) {
      Rcpp::String idx = geometry_cols[ index_required ];
      std::string s_idx = idx.get_cstring();
      Rcpp::IntegerVector m = df[ s_idx ];
      double zmin = Rcpp::min( m );
      double zmax = Rcpp::max( m );

      m_range[0] = std::min( zmin, m_range[0] );
      m_range[1] = std::max( zmax, m_range[1] );
    }
  }

  inline void calculate_m_range(
      Rcpp::NumericVector& m_range,
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& geometry_cols,
      std::string xyzm
  ) {

    int index_required = xyzm == "XYM" ? 2 : 3;

    if( geometry_cols.length() > index_required ) {
      int idx = geometry_cols[ index_required ];
      Rcpp::NumericVector m = nm( Rcpp::_, idx );
      double zmin = Rcpp::min( m );
      double zmax = Rcpp::max( m );

      m_range[0] = std::min( zmin, m_range[0] );
      m_range[1] = std::max( zmax, m_range[1] );
    }
  }

  inline void calculate_m_range(
      Rcpp::NumericVector& m_range,
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& geometry_cols,
      std::string xyzm
  ) {

    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );

    int index_required = xyzm == "XYM" ? 2 : 3;

    if( geometry_cols.length() > index_required ) {
      Rcpp::String idx = geometry_cols[ index_required ];
      std::string s_idx = idx.get_cstring();
      Rcpp::NumericVector m = df[ s_idx ];
      double zmin = Rcpp::min( m );
      double zmax = Rcpp::max( m );

      m_range[0] = std::min( zmin, m_range[0] );
      m_range[1] = std::max( zmax, m_range[1] );
    }
  }
  // #nocov end

  inline void calculate_m_range(
      Rcpp::NumericVector& m_range,
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& geometry_cols,
      std::string xyzm
  ) {

    int index_required = xyzm == "XYM" ? 2 : 3;

    if( geometry_cols.length() > index_required ) {
      int idx = geometry_cols[ index_required ];
      Rcpp::NumericVector m = df[ idx ];
      double zmin = Rcpp::min( m );
      double zmax = Rcpp::max( m );

      m_range[0] = std::min( zmin, m_range[0] );
      m_range[1] = std::max( zmax, m_range[1] );
    }
  }

  inline void calculate_m_range(
      Rcpp::NumericVector& m_range,
      Rcpp::DataFrame& df,
      Rcpp::StringVector& geometry_cols,
      std::string xyzm
  ) {

    // if( xyzm.empty() ) {
    //   // it needs to be something for this function to work
    //
    // }
    int index_required = xyzm == "XYM" ? 2 : 3;

    if( geometry_cols.length() > index_required ) {
      Rcpp::String idx = geometry_cols[ index_required ];
      std::string s_idx = idx.get_cstring();
      Rcpp::NumericVector m = df[ s_idx ];
      double zmin = Rcpp::min( m );
      double zmax = Rcpp::max( m );

      m_range[0] = std::min( zmin, m_range[0] );
      m_range[1] = std::max( zmax, m_range[1] );
    }
  }

} // bbox
} // sfheaders


#endif
