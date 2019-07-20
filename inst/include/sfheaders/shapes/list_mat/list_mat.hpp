#ifndef R_SFHEADERS_SHAPES_LIST_MAT_H
#define R_SFHEADERS_SHAPES_LIST_MAT_H

#include <Rcpp.h>
#include "sfheaders/sfc/bbox.hpp"
#include "sfheaders/sfc/z_range.hpp"
#include "sfheaders/sfc/m_range.hpp"
#include "sfheaders/sfg/sfg_types.hpp"
#include "sfheaders/sfc/sfc_types.hpp"
#include "sfheaders/sfg/sfg_attributes.hpp"

#include "sfheaders/utils/utils.hpp"
#include "sfheaders/shapes/mat/mat.hpp"

/*
 * get_listMat
 *
 * Returns a list of matrices
 *
 * - sfg_MULTILINESTRING
 * - sfg_POLYGON
 * - sfc_MULTIPOINTs
 * - sfc_LINESTRINGs
 */

namespace sfheaders {
namespace shapes {

  inline SEXP get_listMat(
    Rcpp::IntegerMatrix& im,
    int sfg_type = 0
  ) {
    Rcpp::List lst(1);
    lst[0] = im;
    return lst;
  }

  inline SEXP get_listMat(
    Rcpp::NumericMatrix& nm,
    int sfg_type = 0
  ) {
    Rcpp::List lst(1);
    lst[0] = nm;
    return lst;
  }

  inline SEXP get_listMat(
    Rcpp::DataFrame& df,
    int sfg_type = 0
  ) {
    Rcpp::NumericMatrix nm = sfheaders::utils::df_to_matrix( df );
    return get_listMat( nm );
  }

  inline SEXP get_listMat(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& geometry_cols,
      int& start,
      int& end,
      int sfg_type = 0
  ) {
    size_t i;
    size_t n_col = geometry_cols.length();
    int line_rows = end - start + 1;

    Rcpp::NumericMatrix a_line( line_rows, ( n_col) );

    for( i = 0; i < n_col; i++ ) {
      Rcpp::String this_col = geometry_cols[ i ];
      Rcpp::NumericVector v = Rcpp::as< Rcpp::NumericVector >( df[ this_col ] );
      a_line( Rcpp::_, i ) = v[ Rcpp::Range(start, end) ];
    }
    if( sfg_type > 0 ) {
      sfheaders::sfg::make_sfg( a_line, sfg_type );
    }
    return a_line;
  }

  inline SEXP get_listMat(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& geometry_cols,
      int& start,
      int& end,
      int sfg_type = 0
  ) {

    size_t i;
    size_t n_col = geometry_cols.length();
    int line_rows = end - start + 1;
    Rcpp::NumericMatrix a_line( line_rows, ( n_col) );

    for( i = 0; i < n_col; i++ ) {
      int this_col = geometry_cols[ i ];
      Rcpp::NumericVector v = Rcpp::as< Rcpp::NumericVector >( df[ this_col ] );
      a_line( Rcpp::_, i ) = v[ Rcpp::Range(start, end) ];
    }

    if( sfg_type > 0 ) {
      sfheaders::sfg::make_sfg( a_line, sfg_type );
    }

    return a_line;
  }


  // gets lines from data.farme
  // when the start & end rows are known
  // where geometry_cols are ordered?
  inline SEXP get_listMat(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& geometry_cols,
      int& start,
      int& end,
      int sfg_type = 0
  ) {
    size_t n_col = geometry_cols.length();
    // matrix can just be subset by cols and rows
    Rcpp::Range rows = Rcpp::Range( start, end );
    Rcpp::Range cols = Rcpp::Range( geometry_cols[0], geometry_cols[ ( n_col - 1 ) ] );
    Rcpp::NumericMatrix a_line = nm( rows, cols );

    if( sfg_type > 0 ) {
      sfheaders::sfg::make_sfg( nm, sfg_type );
    }

    return a_line;
  }

  inline SEXP get_listMat(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& geometry_cols,
      int& start,
      int& end,
      int sfg_type = 0
  ) {

    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );
    return get_listMat( df, geometry_cols, start, end, sfg_type );
  }


  inline SEXP get_listMat(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& geometry_cols,
      int& start,
      int& end,
      int sfg_type = 0
  ) {
    size_t n_col = geometry_cols.length();

    if( n_col <= 1 ) {
      Rcpp::stop("sfheaders - need at least 2 columns");
    }

    // matrix can just be subset by cols and rows
    Rcpp::Range rows = Rcpp::Range( start, end );
    Rcpp::Range cols = Rcpp::Range( geometry_cols[0], geometry_cols[ ( n_col - 1 ) ] );
    Rcpp::IntegerMatrix a_line = im( rows, cols );

    // here's the last call to 'get_listMat()'
    // so we can attach the sfg_type here??
    if( sfg_type > 0 ) {
      sfheaders::sfg::make_sfg( im, sfg_type );
    }
    return a_line;
  }

  inline SEXP get_listMat(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& geometry_cols,
      int& start,
      int& end,
      int sfg_type = 0
  ) {

    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );
    return get_listMat( df, geometry_cols, start, end, sfg_type );
  }

  inline SEXP get_listMat(
    Rcpp::DataFrame& df,
    Rcpp::IntegerVector& geometry_cols,
    int sfg_type = 0,
    int sfc_type = 0,
    bool is_sf = false
  ) {
    Rcpp::List lst(1);
    lst[0] = sfheaders::shapes::get_mat( df, geometry_cols );
    return lst;
  }


  // get list of lines (e.g. MULTILINESTRING)
  // from a data.frame, where geometry_cols are specified, and a vector of line_ids
  // gives a 'line_id' for each row
  // - assumes df is sorted by line_id
  inline SEXP get_listMat(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& geometry_cols,
      Rcpp::NumericVector& line_ids,       // functions with line_ids can return sf objects
      int sfg_type = 0,
      int sfc_type = 0,    // iff > 0; assign the type, as specified by SFG_LINESTRING etc
      bool is_sf = false   // then in the calling function, we can return straight away
      // if is_sf; keep the id and return a list/data.frame (?)
  ) {

    // if sfc_type > 0; get bbox and z_range & m_range
    Rcpp::NumericVector bbox;
    Rcpp::NumericVector z_range;
    Rcpp::NumericVector m_range;
    if( sfc_type > 0 ) {
      bbox = sfheaders::bbox::start_bbox();
      z_range = sfheaders::zm::start_z_range();
      m_range = sfheaders::zm::start_m_range();
      sfheaders::bbox::calculate_bbox( bbox, df );
    }

    Rcpp::NumericVector unique_ids = Rcpp::sort_unique( line_ids );
    Rcpp::IntegerMatrix line_positions = sfheaders::utils::line_ids( line_ids, unique_ids );

    size_t n_lines = unique_ids.length();

    Rcpp::List mls( n_lines );

    // now iterate through the data.frame and get the matrices of lines
    size_t i;
    for( i = 0; i < n_lines; i++ ) {
    Rcpp::Rcout << "looping for get_listMat() " <<  i << std::endl;

      int start = line_positions(i, 0);
      int end = line_positions(i, 1);
      mls( i ) = get_listMat( df, geometry_cols, start, end, sfg_type );  // this version returns a matrix
      // TODO: can I just make the 'sfc' or 'sf' here??
    }
    // if sfc_type > 0; attach_sfc_attributes()
    if( sfc_type > 0 ) {
      // make an sfc object from this lst
      mls = sfheaders::sfc::make_sfc( mls, sfc_type, bbox, z_range, m_range );
    }
    // if sf > 0; attach the unique_ids
    return mls;
  }

  inline SEXP get_listMat(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& geometry_cols,
      Rcpp::NumericVector& line_ids,
      int sfg_type = 0,
      int sfc_type = 0,
      bool is_sf = false
  ) {

    Rcpp::NumericVector unique_ids = Rcpp::sort_unique( line_ids );
    Rcpp::IntegerMatrix line_positions = sfheaders::utils::line_ids( line_ids, unique_ids );

    size_t n_lines = unique_ids.length();

    Rcpp::List mls( n_lines );


    int start;
    int end;
    if( n_lines == 1 ) {
      //mls( 0 ) = get_listMat( df, geometry_cols );
      //return mls;
      mls( 0 ) = sfheaders::shapes::get_mat( df, geometry_cols );
      return mls;
    }

    // now iterate through the data.frame and get the matrices of lines
    size_t i;
    for( i = 0; i < n_lines; i++ ) {

      start = line_positions(i, 0);
      end = line_positions(i, 1);

      mls( i ) = get_listMat( df, geometry_cols, start, end, sfg_type );
    }
    return mls;
  }

  // now we know where the columns are, we need to get teh vector of line_ids
  // then we can start subsetting
  inline SEXP get_listMat(
    Rcpp::DataFrame& df,
    Rcpp::IntegerVector& cols,
    int& id_col,
    int sfg_type = 0,
    int sfc_type = 0,
    bool is_sf = false
  ) {
    Rcpp::NumericVector line_ids = df[ id_col ];
    // Rcpp::Rcout << "get list mat 6 " << std::endl;
    return get_listMat( df, cols, line_ids, sfg_type, sfc_type, is_sf );
  }


  inline SEXP get_listMat(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& cols,
    Rcpp::String& id_col,
    int sfg_type = 0,
    int sfc_type = 0,
    bool is_sf = false
  ) {
    Rcpp::NumericVector line_ids = df[ id_col ];
    return get_listMat( df, cols, line_ids, sfg_type, sfc_type, is_sf );
  }

  inline SEXP get_listMat(
    Rcpp::IntegerMatrix& im,
    Rcpp::StringVector& cols,
    Rcpp::String& id_col,
    int sfg_type = 0,
    int sfc_type = 0,
    bool is_sf = false
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );
    return get_listMat( df, cols, id_col, sfg_type, sfc_type, is_sf );
  }

  inline SEXP get_listMat(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& cols,
      int& id_col,
      int sfg_type = 0,
      int sfc_type = 0,
      bool is_sf = false
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );
    return get_listMat( df, cols, id_col, sfg_type, sfc_type, is_sf );
  }

  inline SEXP get_listMat(
    Rcpp::NumericMatrix& nm,
    Rcpp::StringVector& cols,
    Rcpp::String& id_col,
    int sfg_type = 0,
    int sfc_type = 0,
    bool is_sf = false
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );
    return get_listMat( df, cols, id_col, sfg_type, sfc_type, is_sf );
  }

  inline SEXP get_listMat(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& cols,
      int& id_col,
      int sfg_type = 0,
      int sfc_type = 0,
      bool is_sf = false
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );
    // Rcpp::Rcout << "get list mat 5 " << std::endl;
    return get_listMat( df, cols, id_col, sfg_type, sfc_type, is_sf );
  }

  inline SEXP get_listMat(
    SEXP& x,
    SEXP& cols,
    int sfg_type = 0,
    int sfc_type = 0,
    bool is_sf = false
  ) {
    Rcpp::NumericMatrix nm = sfheaders::shapes::get_mat( x, cols );
    return get_listMat( nm );
  }

  inline SEXP get_listMat(
      SEXP& x,
      Rcpp::StringVector& cols,
      Rcpp::String& id_col,
      int sfg_type = 0,
      int sfc_type = 0,
      bool is_sf = false
  ){
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
        Rcpp::stop("sfheaders - lines need to be matrices or data.frames");
      } else {
        Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
        return get_listMat( im, cols, id_col, sfg_type, sfc_type, is_sf );
      }
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
        Rcpp::stop("sfheaders - lines need to be matrices or data.frames");
      } else {
        Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
        return get_listMat( nm, cols, id_col, sfg_type, sfc_type, is_sf );
      }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame" ) ) {
        Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
        return get_listMat( df, cols, id_col, sfg_type, sfc_type, is_sf );
      } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unknown lines types");
    }
    }
    return Rcpp::List::create(); // never reaches
  }

  inline SEXP get_listMat(
    SEXP& x,
    Rcpp::IntegerVector& cols,
    int& id_col,
    int sfg_type = 0,
    int sfc_type = 0,
    bool is_sf = false
  ){
    switch( TYPEOF( x ) ) {
    case INTSXP: {
    if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - lines need to be matrices or data.frames");
    } else {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      // Rcpp::Rcout << "get list mat 3 " << std::endl;
      return get_listMat( im, cols, id_col, sfg_type, sfc_type, is_sf );
    }
    }
    case REALSXP: {
    if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - lines need to be matrices or data.frames");
    } else {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      // Rcpp::Rcout << "get list mat 4 " << std::endl;
      return get_listMat( nm, cols, id_col, sfg_type, sfc_type, is_sf );
    }
    }
    case VECSXP: {
    if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return get_listMat( df, cols, id_col, sfg_type, sfc_type, is_sf );
    } // else default
    }
    default: {
      Rcpp::stop("sfheaders - unknown lines types");
    }
    }
    return Rcpp::List::create(); // never reaches
  }

  // inline SEXP get_listMat(
  //     SEXP& x,
  //     SEXP& cols,
  //     Rcpp::StringVector& id_col
  // ){
  //
  // }

  inline SEXP get_listMat(
    SEXP& x,
    SEXP& cols,  // stringvector or integervector
    SEXP& id_col, // stringvector or integervector
    int sfg_type = 0,
    int sfc_type = 0,
    bool is_sf = false
  ) {

    if( TYPEOF( id_col ) != TYPEOF( cols ) ) {
      Rcpp::stop("sfheaders - different column types detected");
    }

    switch( TYPEOF( id_col ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv_id_col = Rcpp::as< Rcpp::IntegerVector >( id_col );
      int i_id_col = iv_id_col[0];
      Rcpp::IntegerVector iv_cols = Rcpp::as< Rcpp::IntegerVector >( cols );
      // Rcpp::Rcout << "get list mat 2 " << std::endl;
      return get_listMat( x, iv_cols, i_id_col, sfg_type, sfc_type, is_sf );
    }
    case STRSXP: {
      Rcpp::StringVector sv_id_col = Rcpp::as< Rcpp::StringVector >( id_col );
      Rcpp::String s_id_col = sv_id_col[0];
      Rcpp::StringVector sv_cols = Rcpp::as< Rcpp::StringVector >( cols );
      return get_listMat( x, sv_cols, s_id_col, sfg_type, sfc_type, is_sf );
    }
    default: {
      Rcpp::stop("sfheaders - unknown id column types");
    }
    }
    return Rcpp::List::create(); // never reaches
  }

}
} // sfheaders


#endif
