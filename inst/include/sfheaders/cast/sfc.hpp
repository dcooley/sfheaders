#ifndef R_SFHEADERS_CAST_SFC_H
#define R_SFHEADERS_CAST_SFC_H

//#include "sfheaders/sf/sf_utils.hpp"
#include "sfheaders/df/sf.hpp"
#include "sfheaders/cast/sfg.hpp"
#include "sfheaders/sfc/zm_range.hpp"
#include "sfheaders/sfc/sfc_attributes.hpp"
//#include "sfheaders/df/sfg.hpp"
//#include "sfheaders/df/utils.hpp"

#include <Rcpp.h>

namespace sfheaders {
namespace cast {

  inline void column_index_check( Rcpp::IntegerVector& sfg_cols, R_xlen_t& n_col ) {
    if( sfg_cols.length() != n_col ) {
      Rcpp::stop("sfheaders - column indexing error - please report this issue, along with an example, at github.com/dcooley/sfheaders");  // #nocov
    }
  }

  // inline Rcpp::List vec_to_vec( Rcpp::NumericVector& sfg, R_xlen_t& sfg_rows, double& id ) {
  //   return sfheaders::df::vector_to_list( sfg, sfg_rows, id );
  // }
  //
  // inline Rcpp::List mat_to_vec( Rcpp::NumericMatrix& sfg, R_xlen_t& sfg_rows, double& id ) {
  //   // add an id to each row of the matrix
  //   R_xlen_t n_row = sfg.nrow();
  //   Rcpp::NumericMatrix id_mat( n_row, 1 );
  //   Rcpp::IntegerVector id_vec = Rcpp::seq( id, id + n_row );
  //   id_mat( Rcpp::_, 0 ) = id_vec;
  //   Rcpp::NumericMatrix mat =  Rcpp::cbind( id_mat, sfg );
  //   Rcpp::List res = sfheaders::df::matrix_to_list( mat, n_row );
  //   sfg_rows = sfg_rows + n_row;
  //   id = id + n_row;    // each vector (row of matrix) gets an incremented id
  //   return res;
  // }
  //
  // // POLYGON to point
  // // column 1 can be ignored
  // inline Rcpp::List listMat_to_vec( Rcpp::List& sfg, R_xlen_t& sfg_rows, double& id ) {
  //   // each matrix gets a sequential id
  //   // then they get put into a list
  //   // and the list collapsed
  //   R_xlen_t n = sfg.size();
  //   R_xlen_t i;
  //   Rcpp::List res( n );
  //   R_xlen_t total_rows = 0;
  //   for( i = 0; i < n; ++i ) {
  //     Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( sfg [ i ] );
  //     R_xlen_t n_row = nm.nrow();
  //     total_rows = total_rows + n_row;
  //     res[ i ] = mat_to_vec( nm, n_row, id );
  //   }
  //   sfg_rows = sfg_rows + total_rows;
  //   return sfheaders::df::collapse_list( res, total_rows );
  // }
  //
  // // columns 1 and 2 of result can be ignored
  // inline Rcpp::List listListMat_to_vec( Rcpp::List& sfg, R_xlen_t& sfg_rows, double& id ) {
  //
  //   R_xlen_t n = sfg.size();
  //   R_xlen_t i;
  //   Rcpp::List res( n );
  //   R_xlen_t total_rows = 0;
  //   for( i = 0; i < n; ++i ) {
  //     Rcpp::List inner_list = sfg[ i ];
  //     R_xlen_t inner_n = inner_list.size();
  //     R_xlen_t inner_total_rows = 0;
  //     res[ i ] = listMat_to_vec( inner_list, inner_total_rows, id );
  //     //++id; // increment id for inner matrices
  //     // the id is incremented by-reference inside matrix_to_list
  //     total_rows = total_rows + inner_total_rows;
  //   }
  //
  //   sfg_rows = sfg_rows + total_rows;
  //   return sfheaders::df::collapse_list( res, sfg_rows );
  // }
  //
  // inline Rcpp::List vec_to_mat( Rcpp::NumericVector& sfg, R_xlen_t& sfg_rows, double& id ) {
  //   return sfheaders::df::vector_to_list( sfg, sfg_rows, id );
  // }
  //
  // inline Rcpp::List mat_to_mat( Rcpp::NumericMatrix& sfg, R_xlen_t& sfg_rows, double& id ) {
  //   // put an id column on and return it as a list
  //   return sfheaders::df::matrix_to_list( sfg, sfg_rows, id );
  // }
  //
  // // e.g. polygon to linestring
  // // - every matrix gets a unique incremented id
  // // - column 1 of the resutl can be ignored
  // inline Rcpp::List listMat_to_mat( Rcpp::List& sfg, R_xlen_t& sfg_rows, double& id ) {
  //   // a polygon is a list[[ matrix ]] structure
  //   // give each matrix an 'id', and increment the id each iteration
  //   // and store in a final list
  //
  //   R_xlen_t n = sfg.size();
  //   R_xlen_t i, j;
  //   Rcpp::List res( n );
  //   R_xlen_t total_rows = 0;
  //
  //   for( i = 0; i < n; ++i ) {
  //     Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( sfg[ i ] );
  //     R_xlen_t n_row = nm.nrow();
  //     total_rows = total_rows + n_row;
  //     res[i] = sfheaders::df::matrix_to_list( nm, n_row, id );  // does not increment 'id'
  //     ++id;
  //   }
  //
  //   sfg_rows = sfg_rows + total_rows;
  //   // collapse_list adds a 'list_id' column
  //   // but going to a matrix means we don't need this.
  //   // or rather, we can ignore it when we come to do the `df_to_sf()` step.
  //   res = sfheaders::df::collapse_list( res, total_rows );
  //   return res;
  // }
  //
  // // e.g. multipolygon to linestring
  // // each matrix has its own unique id
  // // - columns 1 & 2 of the result can be ignored
  // inline Rcpp::List listListMat_to_mat( Rcpp::List& sfg, R_xlen_t& sfg_rows, double& id ) {
  //
  //   R_xlen_t n = sfg.size();
  //   R_xlen_t i;
  //   R_xlen_t total_rows = 0;
  //   Rcpp::List res( n );
  //
  //   // Rcpp::Rcout << "looping" << std::endl;
  //
  //   for( i = 0; i < n; ++i ) {
  //     Rcpp::List inner_list = sfg[ i ];
  //     R_xlen_t inner_n = inner_list.size();
  //     R_xlen_t inner_total_rows = 0;
  //     res[ i ] = listMat_to_mat( inner_list, inner_total_rows, id );
  //     //++id; // increment id for inner matrices
  //     // the id is incremented by-reference inside matrix_to_list
  //     total_rows = total_rows + inner_total_rows;
  //   }
  //
  //   sfg_rows = sfg_rows + total_rows;
  //   return sfheaders::df::collapse_list( res, sfg_rows );
  // }
  //
  // // every list-element has the id incremented
  // inline Rcpp::List mat_to_listMat( Rcpp::NumericMatrix& sfg, R_xlen_t& sfg_rows, double& id ) {
  //   // does this need 2x id columns?
  //   R_xlen_t n_row = sfg.nrow();
  //   R_xlen_t n_col = sfg.ncol();
  //   R_xlen_t i;
  //   Rcpp::List res( n_col + 2 );  // MATRIX_ID + LIST_MAT_ID
  //   Rcpp::NumericVector id_column = Rcpp::rep( id, n_row );
  //   ++id;
  //
  //   res[ 0 ] = id_column;
  //   res[ 1 ] = id_column;
  //   for( i = 0; i < n_col; ++i ) {
  //     res[ i + 2 ] = sfg( Rcpp::_, i );
  //   }
  //   return res;
  // }
  //
  // inline Rcpp::List vec_to_listMat( Rcpp::NumericVector& sfg, R_xlen_t& sfg_rows, double& id ) {
  //   Rcpp::NumericMatrix nm( 1, sfg.size() );
  //   nm( 0, Rcpp::_ ) = sfg;
  //   return mat_to_listMat( nm, sfg_rows, id );
  // }
  //
  // // e.g. polygon to polygon
  // // in the result, the 1st column is the unique polygon_id
  // // the 2nd column is the matrix_id for the polygon
  // inline Rcpp::List listMat_to_listMat( Rcpp::List& sfg, R_xlen_t& sfg_rows, double& id ) {
  //   // each internal matrix needs an id
  //   R_xlen_t n = sfg.size();
  //   R_xlen_t i;
  //   Rcpp::List res( n );
  //   R_xlen_t total_rows = 0;
  //   double inner_id = 1;
  //   for( i = 0; i < n; ++i ) {
  //     Rcpp::NumericMatrix nm = sfg[ i ];
  //     R_xlen_t n_row = nm.nrow();
  //     total_rows = total_rows + n_row;
  //     res[ i ] = sfheaders::df::matrix_to_list( nm, n_row, inner_id );
  //     ++inner_id;
  //   }
  //   sfg_rows = sfg_rows + total_rows;
  //   res = sfheaders::df::infuse_list( res, total_rows, id );
  //   ++id;
  //   return res;
  // }

  // don't call other cast functions inside any other cast function
  // this way I can control when & where the 'id' is placed?
  // e.g. MULTIPOLYGON to POLYGON
  // - each list[[ list ]] gets an incremented 'id' value
  // - and each internal matrix is simply a 1:.N 'id'
  // - the incremented 'id' value comes from 'collapse_list'
  // In the result, he 2nd list element is redundant.
  // inline Rcpp::List listListMat_to_listMat( Rcpp::List& sfg, std::string& cast_to ) {
  //
  //   // each inner-list gets returned as a new sfg_CAST_TO
  //
  //   if( cast_to == "MULTILINESTRING" ) {
  //     return sfheaders::sfg::sfg_multilinestrings( sfg );
  //   } else if ( cast_to == "POLYGON" ) {
  //     return sfheaders::sfg::sfg_polygons( sfg );
  //   }

    // R_xlen_t total_rows = 0;
    // for( i = 0; i < n; ++i ) {
    //   Rcpp::List inner_list = sfg[ i ];
    //   R_xlen_t inner_n = inner_list.size();
    //   R_xlen_t inner_total_rows = 0;
    //
    //   Rcpp::List inner_res( inner_n );
    //   double inner_id = 1;
    //
    //   for( j = 0; j < inner_n; ++j ) {
    //
    //     Rcpp::NumericMatrix nm = inner_list[ j ];
    //     R_xlen_t n_row = nm.nrow();
    //     inner_total_rows = inner_total_rows + n_row;
    //     inner_res[ j ] = sfheaders::df::matrix_to_list( nm, n_row, inner_id );
    //     ++inner_id;
    //   }
    //
    //   res[ i ] = sfheaders::df::collapse_list( inner_res, inner_total_rows );
    //   total_rows = total_rows + inner_total_rows;
    // }
    // sfg_rows = sfg_rows + total_rows;
    // //return res;
    // return sfheaders::df::collapse_list( res, total_rows, id );
  // }

  // inline Rcpp::List mat_to_listListMat( Rcpp::NumericMatrix& sfg, R_xlen_t& sfg_rows, double& id ) {
  //
  //   R_xlen_t n_row = sfg.nrow();
  //   R_xlen_t n_col = sfg.ncol();
  //   R_xlen_t i;
  //   Rcpp::List res( n_col + 3 );  // MATRIX_ID + LIST_MAT_ID + LIST_LIST_MAT_ID
  //   Rcpp::NumericVector id_column = Rcpp::rep( id, n_row );
  //   ++id;
  //
  //   res[ 0 ] = id_column;
  //   res[ 1 ] = id_column;
  //   res[ 2 ] = id_column;
  //   for( i = 0; i < n_col; ++i ) {
  //     res[ i + 3 ] = sfg( Rcpp::_, i );
  //   }
  //
  //   return res;
  // }
  //
  // inline Rcpp::List vec_to_listListMat( Rcpp::NumericVector& sfg, R_xlen_t& sfg_rows, double& id ) {
  //   Rcpp::NumericMatrix nm( 1, sfg.size() );
  //   nm( 0, Rcpp::_ ) = sfg;
  //   return mat_to_listListMat( nm, sfg_rows, id );
  // }
  //
  // // e.g. polygon to multipolygon
  // // each list[[ matrix ]] gets nested one-deeper with the 'id' value
  // inline Rcpp::List listMat_to_listListMat( Rcpp::List& sfg, R_xlen_t& sfg_rows, double& id ) {
  //   R_xlen_t i;
  //   R_xlen_t n = sfg.size();
  //   Rcpp::List res( n );
  //   double inner_id = 1;
  //   R_xlen_t total_rows = 0;
  //
  //   for( i = 0; i < n; ++i ) {
  //     Rcpp::NumericMatrix nm = sfg[ i ];
  //     R_xlen_t inner_rows = nm.nrow();
  //
  //     res[ i ] = sfheaders::df::matrix_to_list( nm, inner_rows, inner_id );
  //     ++inner_id;
  //     total_rows = total_rows + inner_rows;
  //
  //   }
  //
  //   sfg_rows = sfg_rows + total_rows;
  //
  //   double list_id = 1;
  //   Rcpp::List inner_res = sfheaders::df::infuse_list( res, total_rows, list_id );
  //   Rcpp::List outer_res( inner_res.size() + 1 );
  //   for( i = 0; i < inner_res.size(); ++i ) {
  //     outer_res[ i + 1 ] = inner_res[ i ];
  //   }
  //   Rcpp::NumericVector id_column = Rcpp::rep( id, total_rows );
  //   ++id;
  //   outer_res[ 0 ] = id_column;
  //   return outer_res;
  // }
  //
  // // multipolygon to multipolygon
  // //
  // inline Rcpp::List listListMat_to_listListMat( Rcpp::List& sfg, R_xlen_t& sfg_rows, double& id ) {
  //
  //   R_xlen_t i;
  //   R_xlen_t total_rows = 0;
  //   Rcpp::List res = sfheaders::df::sfg_multipolygon_coordinates( sfg, total_rows );
  //
  //   sfg_rows = sfg_rows + total_rows;
  //
  //   double list_id = 1;
  //   Rcpp::List outer_res( res.size() + 1 );
  //   for( i = 0; i < res.size(); ++i ) {
  //     outer_res[ i + 1 ] = res[ i ];
  //   }
  //   Rcpp::NumericVector id_column = Rcpp::rep( id, total_rows );
  //   ++id;
  //   outer_res[ 0 ] = id_column;
  //   return outer_res;
  //
  // }

  inline Rcpp::NumericVector count_new_sfc_objects( Rcpp::List& sfc, std::string& cast_to ) {
    R_xlen_t n = sfc.size();
    Rcpp::NumericVector res( n );
    R_xlen_t i;
    for( i = 0; i < n; ++i ) {
      SEXP sfg = sfc[ i ];
      res[ i ] = sfheaders::cast::count_new_objects( sfg, cast_to );
    }
    return res;
  }

  // returns CAST_UP or CAST_DOWN
  // given the from & to
  // casting to the same geometry will be counted as 'DOWN'
  inline int cast_type( std::string& cast ) {
    if( cast == "POINT" ) {
      return sfheaders::sfg::VECTOR;
    } else if ( cast == "MULTIPOINT" ) {
      return sfheaders::sfg::MATRIX;
    } else if ( cast == "LINESTRING" ) {
      return sfheaders::sfg::MATRIX;
    } else if ( cast == "MULTILINESTRING" ) {
      return sfheaders::sfg::LIST_MATRIX;
    } else if ( cast == "POLYGON" ) {
      return sfheaders::sfg::LIST_MATRIX;
    } else if ( cast == "MULTIPOLYGON" ) {
      return sfheaders::sfg::LIST_LIST_MATRIX;
    } else {
      Rcpp::stop("sfheders - unknown geometry type to cast to");  // #nocov
    }
    return -1;
  }


  // TODO: keep / calculate the bbox, z_range and m_range
  // these shouldn't change; because the coordinates aren't changing,right?
  inline Rcpp::List cast_sfc(
      Rcpp::List& sfc,
      Rcpp::NumericVector& n_results,
      std::string& cast_to,
      bool close = true
  ) {

    int casting_to = cast_type( cast_to );

    Rcpp::List crs = sfc.attr("crs");
    sfheaders::sfc::update_crs( crs );

    double precision = sfc.attr("precision");
    Rcpp::NumericVector bbox = sfc.attr("bbox");

    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range(); // = sfc.attr("z_range");
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range(); // = sfc.attr("m_range");

    if( sfc.hasAttribute("z_range") ) {
      z_range = sfc.attr("z_range");
    }

    if( sfc.hasAttribute("m_range") ) {
      m_range = sfc.attr("m_range");
    }

    int n_empty = sfc.attr("n_empty");
    std::unordered_set< std::string > geometry_types{ cast_to };

    std::string cast_from;
    std::string xyzm;

    R_xlen_t i, j;

    R_xlen_t total_results = Rcpp::sum( n_results );
    Rcpp::List res( total_results );

    // loop over reach sfg and convert and fill teh resutl list
    R_xlen_t result_counter = 0;  // for indexing into the res( ) list

    // IFF the input is not a list, this loop won't work
    // so only use this list loop iff the casting_from >= LIST_MATRIX !! done

    R_xlen_t n = sfc.size();

    for( i = 0; i < n; ++i ) {

      // the value at n_results[ i ] tells us the size of the returning object
      R_xlen_t returned_size = n_results[ i ];

      SEXP sfg = sfc[ i ];

      Rcpp::CharacterVector cls = sfheaders::utils::getSfgClass( sfg );
      cast_from = cls[1];
      xyzm = cls[0];

      int casting_from = cast_type( cast_from );

      SEXP new_res = sfheaders::cast::cast_to( sfg, cast_from, cast_to, xyzm, close );

      if( casting_from <= casting_to ) {
        res[ result_counter ] = new_res;
        ++result_counter;
      } else {
        for( j = 0; j < returned_size; ++j ) {
          Rcpp::List new_lst = Rcpp::as< Rcpp::List >( new_res );
          res[ result_counter ] = new_lst[ j ];
          ++result_counter;
        }
      }

    }
    sfheaders::sfc::attach_sfc_attributes(
      res, cast_to, geometry_types, bbox, z_range, m_range, crs, n_empty, precision
      );
    return res;
  }

  inline Rcpp::List cast_sfc(
      Rcpp::List& sfc,
      std::string& cast_to,
      bool close = true
  ) {

    Rcpp::NumericVector n_results = count_new_sfc_objects( sfc, cast_to );
    return cast_sfc( sfc, n_results, cast_to, close );
  }


} // cast
} // sfheaders


#endif
