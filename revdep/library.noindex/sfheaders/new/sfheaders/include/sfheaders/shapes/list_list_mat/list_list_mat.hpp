#ifndef R_SFHEADERS_SHAPES_LIST_LIST_MAT_H
#define R_SFHEADERS_SHAPES_LIST_LIST_MAT_H

#include <Rcpp.h>
#include "sfheaders/utils/utils.hpp"
#include "sfheaders/utils/subset/subset.hpp"
#include "sfheaders/shapes/mat/mat.hpp"
#include "sfheaders/shapes/list_mat/list_mat.hpp"

/*
 * get_listListMat
 *
 * Converts various inputs into a list[[ list[[ matrix ]] ]] structure
 */

namespace sfheaders {
namespace shapes {

  // #nocov start
  inline SEXP get_listListMat(
    Rcpp::IntegerMatrix& im
  ) {
    Rcpp::List mp(1);
    mp[0] = sfheaders::shapes::get_listMat(im);
    return mp;
  }

  inline SEXP get_listListMat(
      Rcpp::NumericMatrix& nm
  ) {
    Rcpp::List mp(1);
    mp[0] = sfheaders::shapes::get_listMat(nm);
    return mp;
  }

  inline SEXP get_listListMat(
      Rcpp::DataFrame& df
  ) {
    Rcpp::List mp(1);
    mp[0] = sfheaders::shapes::get_listMat(df);
    return mp;
  }

  inline SEXP get_listListMat(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& geometry_cols,
    Rcpp::String& group_id_col_1,
    Rcpp::String& group_id_col_2
  ) {

    SEXP group_ids = df[ group_id_col_1 ];

    Rcpp::IntegerMatrix line_positions = sfheaders::utils::id_positions( group_ids );
    R_xlen_t n_lines = line_positions.nrow();

    Rcpp::List mpl( n_lines );

    R_xlen_t i;

    // issue 56 - no need to keep all the columns in the subset_dataframe
    Rcpp::StringVector keep_columns = sfheaders::utils::concatenate_vectors( geometry_cols, group_id_col_1 );
    keep_columns = sfheaders::utils::concatenate_vectors( keep_columns, group_id_col_2 );
    Rcpp::DataFrame df_keep = df[ keep_columns ];
    Rcpp::StringVector df_names = df_keep.names();

    for( i = 0; i < n_lines; ++i ) {
      int start = line_positions(i, 0);
      int end = line_positions(i, 1);

      Rcpp::Range rng( start, end );
      Rcpp::DataFrame df_subset = sfheaders::utils::subset_dataframe( df_keep, df_names, start, end );

      mpl[ i ] = sfheaders::shapes::get_listMat( df_subset, geometry_cols, group_id_col_2 );
    }
    return mpl;
  }



  inline SEXP get_listListMat(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& geometry_cols,
      Rcpp::String& group_id_col_1,
      Rcpp::String& group_id_col_2,
      Rcpp::String& group_id_col_3
  ) {

    SEXP group_ids = df[ group_id_col_1 ];

    Rcpp::IntegerMatrix line_positions = sfheaders::utils::id_positions( group_ids );
    R_xlen_t n_lines = line_positions.nrow();

    Rcpp::List mpl( n_lines );

    R_xlen_t i;

    // issue 56 - no need to keep all the columns in the subset_dataframe
    Rcpp::StringVector keep_columns = sfheaders::utils::concatenate_vectors( geometry_cols, group_id_col_1 );
    keep_columns = sfheaders::utils::concatenate_vectors( keep_columns, group_id_col_2 );
    Rcpp::DataFrame df_keep = df[ keep_columns ];
    Rcpp::StringVector df_names = df_keep.names();

    for( i = 0; i < n_lines; ++i ) {
      int start = line_positions(i, 0);
      int end = line_positions(i, 1);

      Rcpp::Range rng( start, end );
      Rcpp::DataFrame df_subset = sfheaders::utils::subset_dataframe( df_keep, df_names, start, end );

      mpl[ i ] = sfheaders::shapes::get_listListMat( df_subset, geometry_cols, group_id_col_2, group_id_col_3 );
    }
    return mpl;
  }


  inline SEXP get_listListMat(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& geometry_cols,
      int& group_id_col_1,
      int& group_id_col_2
  ) {

    sfheaders::utils::column_exists( df, group_id_col_1 );
    sfheaders::utils::column_exists( df, group_id_col_2 );
    sfheaders::utils::column_check( df, geometry_cols );

    // given polygon & line ids, collapse and matricise and listify
    Rcpp::StringVector df_names = df.names();

    // use the indexes to subset the df_names to get the columns
    Rcpp::String str_group_id_col_1 = df_names[ group_id_col_1 ];
    Rcpp::String str_group_id_col_2 = df_names[ group_id_col_2 ];
    Rcpp::StringVector str_geometry_cols = df_names[ geometry_cols ];

    return get_listListMat( df, str_geometry_cols, str_group_id_col_1, str_group_id_col_2 );
  }


  inline SEXP get_listListMat(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& geometry_cols,
      int& group_id_col_1,
      int& group_id_col_2,
      int& group_id_col_3
  ) {

    sfheaders::utils::column_exists( df, group_id_col_1 );
    sfheaders::utils::column_exists( df, group_id_col_2 );
    sfheaders::utils::column_exists( df, group_id_col_3 );

    sfheaders::utils::column_check( df, geometry_cols );

    // given polygon & line ids, collapse and matricise and listify
    Rcpp::StringVector df_names = df.names();

    // use the indexes to subset the df_names to get the columns
    Rcpp::String str_group_id_col_1 = df_names[ group_id_col_1 ];
    Rcpp::String str_group_id_col_2 = df_names[ group_id_col_2 ];
    Rcpp::String str_group_id_col_3 = df_names[ group_id_col_3 ];
    Rcpp::StringVector str_geometry_cols = df_names[ geometry_cols ];

    return get_listListMat( df, str_geometry_cols, str_group_id_col_1, str_group_id_col_2, str_group_id_col_3 );
  }



  inline SEXP get_listListMat(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& geometry_cols,
      Rcpp::String& group_id_col_1,
      Rcpp::String& group_id_col_2
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );
    return get_listListMat( df, geometry_cols, group_id_col_1, group_id_col_2 );
  }


  inline SEXP get_listListMat(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& geometry_cols,
      Rcpp::String& group_id_col_1,
      Rcpp::String& group_id_col_2,
      Rcpp::String& group_id_col_3
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );
    return get_listListMat( df, geometry_cols, group_id_col_1, group_id_col_2, group_id_col_3 );
  }


  inline SEXP get_listListMat(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& geometry_cols,
      int& group_id_col_1,
      int& group_id_col_2
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );
    return get_listListMat( df, geometry_cols, group_id_col_1, group_id_col_2 );
  }

  inline SEXP get_listListMat(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& geometry_cols,
      int& group_id_col_1,
      int& group_id_col_2,
      int& group_id_col_3
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( im );
    return get_listListMat( df, geometry_cols, group_id_col_1, group_id_col_2, group_id_col_3 );
  }


  inline SEXP get_listListMat(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& geometry_cols,
      Rcpp::String& group_id_col_1,
      Rcpp::String& group_id_col_2
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );
    return get_listListMat( df, geometry_cols, group_id_col_1, group_id_col_2 );
  }

  inline SEXP get_listListMat(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& geometry_cols,
      Rcpp::String& group_id_col_1,
      Rcpp::String& group_id_col_2,
      Rcpp::String& group_id_col_3
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );
    return get_listListMat( df, geometry_cols, group_id_col_1, group_id_col_2, group_id_col_3 );
  }


  inline SEXP get_listListMat(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& geometry_cols,
      int& group_id_col_1,
      int& group_id_col_2
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );
    return get_listListMat( df, geometry_cols, group_id_col_1, group_id_col_2 );
  }

  inline SEXP get_listListMat(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& geometry_cols,
      int& group_id_col_1,
      int& group_id_col_2,
      int& group_id_col_3
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( nm );
    return get_listListMat( df, geometry_cols, group_id_col_1, group_id_col_2, group_id_col_3 );
  }


  inline SEXP get_listListMat(
      SEXP& x,
      Rcpp::StringVector& geometry_cols,
      Rcpp::String& group_id_col_1,
      Rcpp::String& group_id_col_2
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - polygons needs to be matrices or dataframes");  // #nocov
    } else {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return get_listListMat( im, geometry_cols, group_id_col_1, group_id_col_2 );
    }
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - polygons needs to be matrices or dataframes");  // #nocov
    } else {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return get_listListMat( nm, geometry_cols, group_id_col_1, group_id_col_2 );
    }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return get_listListMat( df, geometry_cols, group_id_col_1, group_id_col_2 );
    }
    }
    default: {
      Rcpp::stop("sfheaders - unknown polygons type");
    }
    }
  }


  inline SEXP get_listListMat(
      SEXP& x,
      Rcpp::StringVector& geometry_cols,
      Rcpp::String& group_id_col_1,
      Rcpp::String& group_id_col_2,
      Rcpp::String& group_id_col_3
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - polygons needs to be matrices or dataframes");
    } else {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return get_listListMat( im, geometry_cols, group_id_col_1, group_id_col_2, group_id_col_3 );
    }
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - polygons needs to be matrices or dataframes");
    } else {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return get_listListMat( nm, geometry_cols, group_id_col_1, group_id_col_2, group_id_col_3 );
    }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return get_listListMat( df, geometry_cols, group_id_col_1, group_id_col_2, group_id_col_3 );
    }
    }
    default: {
      Rcpp::stop("sfheaders - unknown polygons type");
    }
    }
  }


  inline SEXP get_listListMat(
    SEXP& x,
    Rcpp::IntegerVector& geometry_cols,
    int& group_id_col_1,
    int& group_id_col_2
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
    if( !Rf_isMatrix( x ) ) {
        Rcpp::stop("sfheaders - polygons needs to be matrices or dataframes");
    } else {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return get_listListMat( im, geometry_cols, group_id_col_1, group_id_col_2 );
    }
    }
    case REALSXP: {
    if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - polygons needs to be matrices or dataframes");
    } else {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return get_listListMat( nm, geometry_cols, group_id_col_1, group_id_col_2 );
    }
    }
    case VECSXP: {
    if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return get_listListMat( df, geometry_cols, group_id_col_1, group_id_col_2 );
    }
    }
    default: {
      Rcpp::stop("sfheaders - unknown polygons type");
    }
    }
  }


  inline SEXP get_listListMat(
      SEXP& x,
      Rcpp::IntegerVector& geometry_cols,
      int& group_id_col_1,
      int& group_id_col_2,
      int& group_id_col_3
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - polygons needs to be matrices or dataframes");
    } else {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return get_listListMat( im, geometry_cols, group_id_col_1, group_id_col_2, group_id_col_3 );
    }
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - polygons needs to be matrices or dataframes");
    } else {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return get_listListMat( nm, geometry_cols, group_id_col_1, group_id_col_2, group_id_col_3 );
    }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return get_listListMat( df, geometry_cols, group_id_col_1, group_id_col_2, group_id_col_3 );
    }
    }
    default: {
      Rcpp::stop("sfheaders - unknown polygons type");
    }
    }
  }



  inline SEXP get_listListMat(
    SEXP& x,
    SEXP& geometry_cols,  // IntegerVector or StringVector
    SEXP& group_id_col_1, // the outer-most ID column; e.g. polygon_id
    SEXP& group_id_col_2  // the inner-most ID column; e.g. line_id
  ) {

    if( ( TYPEOF( group_id_col_1 ) != TYPEOF( group_id_col_2 ) ) ||
        TYPEOF( geometry_cols ) != TYPEOF( group_id_col_1 ) ) {
      Rcpp::stop("sfheaders - different column types detected");
    }

    switch( TYPEOF( geometry_cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv_geometry_cols = Rcpp::as< Rcpp::IntegerVector >( geometry_cols );
      Rcpp::IntegerVector iv_group_id_col_1 = Rcpp::as< Rcpp::IntegerVector >( group_id_col_1 );
      Rcpp::IntegerVector iv_group_id_col_2 = Rcpp::as< Rcpp::IntegerVector >( group_id_col_2 );
      int i_group_id_col_1 = iv_group_id_col_1[0];
      int i_group_id_col_2 = iv_group_id_col_2[0];
      return get_listListMat( x, iv_geometry_cols, i_group_id_col_1, i_group_id_col_2 );
    }
    case STRSXP: {
      Rcpp::StringVector sv_geometry_cols = Rcpp::as< Rcpp::StringVector >( geometry_cols );
      Rcpp::StringVector sv_group_id_col_1 = Rcpp::as< Rcpp::StringVector >( group_id_col_1 );
      Rcpp::StringVector sv_group_id_col_2 = Rcpp::as< Rcpp::StringVector >( group_id_col_2 );
      Rcpp::String s_group_id_col_1 = sv_group_id_col_1[0];
      Rcpp::String s_group_id_col_2 = sv_group_id_col_2[0];
      return get_listListMat( x, sv_geometry_cols, s_group_id_col_1, s_group_id_col_2 );
    }
    default: {
      Rcpp::stop("sfheaders - unknown id column types");
    }
    }

  }


inline SEXP get_listListMat(
    SEXP& x,
    SEXP& geometry_cols,  // IntegerVector or StringVector
    SEXP& group_id_col_1, // the outer-most ID column; e.g. multipolygon_id
    SEXP& group_id_col_2,  // the second-outer-most ID column; e.g. polygon_id
    SEXP& group_id_col_3  // the inner-most ID column; e.g. line_id
) {

  if( ( TYPEOF( group_id_col_1 ) != TYPEOF( group_id_col_2 ) ) ||
      ( TYPEOF( geometry_cols ) != TYPEOF( group_id_col_1 ) ) ||
      ( TYPEOF( geometry_cols ) != TYPEOF( group_id_col_3 ) ) ) {
    Rcpp::stop("sfheaders - different column types detected");
  }

  switch( TYPEOF( geometry_cols ) ) {
  case REALSXP: {}
  case INTSXP: {
    Rcpp::IntegerVector iv_geometry_cols = Rcpp::as< Rcpp::IntegerVector >( geometry_cols );
    Rcpp::IntegerVector iv_group_id_col_1 = Rcpp::as< Rcpp::IntegerVector >( group_id_col_1 );
    Rcpp::IntegerVector iv_group_id_col_2 = Rcpp::as< Rcpp::IntegerVector >( group_id_col_2 );
    Rcpp::IntegerVector iv_group_id_col_3 = Rcpp::as< Rcpp::IntegerVector >( group_id_col_3 );
    int i_group_id_col_1 = iv_group_id_col_1[0];
    int i_group_id_col_2 = iv_group_id_col_2[0];
    int i_group_id_col_3 = iv_group_id_col_3[0];

    //Rcpp::stop("stopping");
    return get_listListMat( x, iv_geometry_cols, i_group_id_col_1, i_group_id_col_2, i_group_id_col_3 );
  }
  case STRSXP: {
    Rcpp::StringVector sv_geometry_cols = Rcpp::as< Rcpp::StringVector >( geometry_cols );
    Rcpp::StringVector sv_group_id_col_1 = Rcpp::as< Rcpp::StringVector >( group_id_col_1 );
    Rcpp::StringVector sv_group_id_col_2 = Rcpp::as< Rcpp::StringVector >( group_id_col_2 );
    Rcpp::StringVector sv_group_id_col_3 = Rcpp::as< Rcpp::StringVector >( group_id_col_3 );
    Rcpp::String s_group_id_col_1 = sv_group_id_col_1[0];
    Rcpp::String s_group_id_col_2 = sv_group_id_col_2[0];
    Rcpp::String s_group_id_col_3 = sv_group_id_col_3[0];
    return get_listListMat( x, sv_geometry_cols, s_group_id_col_1, s_group_id_col_2, s_group_id_col_3 );
  }
  default: {
    Rcpp::stop("sfheaders - unknown id column types");
  }
  }

}

// #nocov end

} // shapes
} // sfheaders


#endif
