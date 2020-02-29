#ifndef R_SFHEADERS_CAST_SFC_H
#define R_SFHEADERS_CAST_SFC_H

#include "sfheaders/sf/sf_utils.hpp"
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
      Rcpp::stop("sfheders - unknown geometry type to cast to");
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

    // get bbox, z_range, m_range;
    Rcpp::List crs = sfc.attr("crs");
    double precision = sfc.attr("precision");
    Rcpp::NumericVector bbox = sfc.attr("bbox");

    Rcpp::NumericVector z_range = sfheaders::zm::start_z_range(); // = sfc.attr("z_range");
    Rcpp::NumericVector m_range = sfheaders::zm::start_m_range(); // = sfc.attr("m_range");

    if( sfc.hasAttribute("z_range") ) {
      z_range = sfc.attr("z_range");
      m_range = sfc.attr("m_range");
    }

    int n_empty = sfc.attr("n_empty");
    std::unordered_set< std::string > geometry_types{ cast_to };

    int epsg = crs[0];
    Rcpp::String proj4string = crs[1];

    std::string cast_from;

    R_xlen_t i, j;

    // Rcpp::Rcout << "n_results: " << n_results << std::endl;

    R_xlen_t total_results = Rcpp::sum( n_results );
    Rcpp::List res( total_results );

    //return res;

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

      int casting_from = cast_type( cast_from );

      SEXP new_res = sfheaders::cast::cast_to( sfg, cast_from, cast_to, close );

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
      res, cast_to, geometry_types, bbox, z_range, m_range, epsg, proj4string, n_empty, precision
      );
    return res;
  }

  Rcpp::List cast_sfc(
      Rcpp::List& sfc,
      std::string& cast_to,
      bool close = true
  ) {
    Rcpp::NumericVector n_results = count_new_sfc_objects( sfc, cast_to );
    return cast_sfc( sfc, n_results, cast_to, close );
  }


  Rcpp::List cast_sf(
      Rcpp::DataFrame& sf,
      std::string& cast_to,
      bool close = true
  ) {
    if( !sf.hasAttribute("sf_column") ) {
      Rcpp::stop("sfheaders - sf_column not found");
    }


    Rcpp::StringVector df_names = sf.names();
    R_xlen_t n_names = df_names.length();
    R_xlen_t i;
    R_xlen_t n_row = sf.nrow();

    std::string geom_column = sf.attr("sf_column");
    Rcpp::List sfc = sf[ geom_column ];
    Rcpp::NumericVector n_results = count_new_sfc_objects( sfc, cast_to );

    // other than the sfc column, expand all the other columsn by 'n_reuslts'
    Rcpp::List casted_sfc = cast_sfc( sfc, n_results, cast_to, close );

    Rcpp::List sf_res( n_names );
    // loop over each of the df_names which aren't the geometry
    // then add on the created_sfc;
    R_xlen_t column_counter = 0;
    for( i = 0; i < n_names; ++i ) {
      // iff this_name != geom_column, expand the vector and doene.
      Rcpp::String this_name = df_names[ i ];
      std::string str_name = this_name;
      if( str_name != geom_column ) {
        Rcpp::Rcout << "this_name: " << str_name << std::endl;
        SEXP v = sf[ i ];
        sfheaders::df::expand_vector( sf_res, v, n_results, column_counter );
        ++column_counter;
      }
    }

    sf_res[ column_counter ] = casted_sfc;
    sf_res.names() = df_names;
    sfheaders::sf::attach_dataframe_attributes( sf_res, n_row, geom_column );
    return sf_res;

  }



//
// inline Rcpp::List setup_result( R_xlen_t& total_coordinates ) {
//
//   Rcpp::NumericVector sfc_id_res( total_coordinates, Rcpp::NumericVector::get_na() );
//   Rcpp::NumericVector sfg_id_res( total_coordinates, Rcpp::NumericVector::get_na() );
//   Rcpp::NumericVector list_list_matrix_id( total_coordinates, Rcpp::NumericVector::get_na() );
//   Rcpp::NumericVector list_matrix_id( total_coordinates, Rcpp::NumericVector::get_na() );
//   Rcpp::NumericVector matrix_id( total_coordinates, Rcpp::NumericVector::get_na() );
//   Rcpp::NumericVector x_res( total_coordinates, Rcpp::NumericVector::get_na() );
//   Rcpp::NumericVector y_res( total_coordinates, Rcpp::NumericVector::get_na() );
//   Rcpp::NumericVector m_res( total_coordinates, Rcpp::NumericVector::get_na() );
//   Rcpp::NumericVector z_res( total_coordinates, Rcpp::NumericVector::get_na() );
//
//   Rcpp::List res = Rcpp::List::create(
//     Rcpp::_["sfc_id"] = sfc_id_res,
//     Rcpp::_["sfg_id"] = sfg_id_res,
//     Rcpp::_["list_list_matrix_id"] = list_list_matrix_id,
//     Rcpp::_["list_matrix_id"] = list_matrix_id,
//     Rcpp::_["matrix_id"] = matrix_id,
//     Rcpp::_["x"] = x_res,
//     Rcpp::_["y"] = y_res,
//     Rcpp::_["z"] = z_res,
//     Rcpp::_["m"] = m_res
//   );
//   return res;
// }
//
// inline void dim_error() { // #nocov
//   Rcpp::stop("sfheaders - unknown geometry dimension");    // #nocov
// }
//
// inline Rcpp::IntegerVector get_sfg_cols( R_xlen_t& n_col, int geometry, std::string& dim ) {
//
//   switch( geometry ) {
//   case sfheaders::sfg::SFG_POINT: {
//     if( dim == "XY" ) {
//     return Rcpp::IntegerVector({ VECTOR_ID, X_COLUMN_CAST, Y_COLUMN_CAST });
//   } else if( dim == "XYZM" ) {
//     return Rcpp::IntegerVector({ VECTOR_ID, X_COLUMN_CAST, Y_COLUMN_CAST, Z_COLUMN_CAST, M_COLUMN_CAST });
//   } else if ( dim == "XYZ" ) {
//     return Rcpp::IntegerVector({ VECTOR_ID, X_COLUMN_CAST, Y_COLUMN_CAST, Z_COLUMN_CAST });
//   } else if ( dim == "XYM" ) {  // #nocov
//     return Rcpp::IntegerVector({ VECTOR_ID, X_COLUMN_CAST, Y_COLUMN_CAST, M_COLUMN_CAST }); // #nocov
//   } else {
//     dim_error();  // #nocov
//   }
//   }
//   case sfheaders::sfg::SFG_MULTIPOINT: {}
//   case sfheaders::sfg::SFG_LINESTRING: {
//     if( dim == "XY" ) {
//     return Rcpp::IntegerVector({ X_COLUMN_CAST, Y_COLUMN_CAST });
//   } else if( dim == "XYZM" ) {
//     return Rcpp::IntegerVector({ X_COLUMN_CAST, Y_COLUMN_CAST, Z_COLUMN_CAST, M_COLUMN_CAST });
//   } else if ( dim == "XYZ" ) {
//     return Rcpp::IntegerVector({ X_COLUMN_CAST, Y_COLUMN_CAST, Z_COLUMN_CAST });
//   } else if ( dim == "XYM" ) {  // #nocov
//     return Rcpp::IntegerVector({ X_COLUMN_CAST, Y_COLUMN_CAST, M_COLUMN_CAST }); // #nocov
//   } else {
//     dim_error();  // #nocov
//   }
//   }
//   case sfheaders::sfg::SFG_MULTILINESTRING: {}
//   case sfheaders::sfg::SFG_POLYGON: {
//     if( dim == "XY" ) {
//     return Rcpp::IntegerVector({ MATRIX_ID, X_COLUMN_CAST, Y_COLUMN_CAST });
//   } else if( dim == "XYZM" ) {
//     return Rcpp::IntegerVector({ MATRIX_ID, X_COLUMN_CAST, Y_COLUMN_CAST, Z_COLUMN_CAST, M_COLUMN_CAST });
//   } else if ( dim == "XYZ" ) {
//     return Rcpp::IntegerVector({ MATRIX_ID, X_COLUMN_CAST, Y_COLUMN_CAST, Z_COLUMN_CAST });
//   } else if ( dim == "XYM" ) {  // #nocov
//     return Rcpp::IntegerVector({ MATRIX_ID, X_COLUMN_CAST, Y_COLUMN_CAST, M_COLUMN_CAST });  // #nocov
//   } else {
//     dim_error();  // #nocov
//   }
//   }
//   case sfheaders::sfg::SFG_MULTIPOLYGON: {
//     if( dim == "XY" ) {
//     return Rcpp::IntegerVector({ MATRIX_ID, LIST_MATRIX_ID, X_COLUMN_CAST, Y_COLUMN_CAST });
//   } else if( dim == "XYZM" ) {
//     return Rcpp::IntegerVector({ MATRIX_ID, LIST_MATRIX_ID, X_COLUMN_CAST, Y_COLUMN_CAST, Z_COLUMN_CAST, M_COLUMN_CAST });
//   } else if ( dim == "XYZ" ) {
//     return Rcpp::IntegerVector({ MATRIX_ID, LIST_MATRIX_ID, X_COLUMN_CAST, Y_COLUMN_CAST, Z_COLUMN_CAST });
//   } else if ( dim == "XYM" ) {  // #nocov
//     return Rcpp::IntegerVector({ MATRIX_ID, LIST_MATRIX_ID, X_COLUMN_CAST, Y_COLUMN_CAST, M_COLUMN });  // #nocov
//   } else {
//     dim_error(); // #nocov
//   }
//
//   }
//   default: {
//     Rcpp::stop("sfheaders - unknown geometry type");  // #nocov
//   }
//   }
//
//   return Rcpp::IntegerVector(); // #nocov never reached
// }
//
// inline void sfg_n_coordinates(
//     SEXP& sfg,
//     R_xlen_t& sfg_count
// ) {
//
//   switch( TYPEOF( sfg ) ) {
//   case INTSXP: {}
//   case REALSXP: {
//     if( !Rf_isMatrix( sfg ) ) {
//     //Rcpp::stop("sfheaders - unsupported coordinate type");
//     // it's a vector, right?
//     sfg_count += 1;
//   } else {
//     sfg_count += sfheaders::utils::sexp_n_row( sfg );
//   }
//   break;
//   }
//   case VECSXP: {
//     if( Rf_inherits( sfg, "data.frame" ) ) {
//     Rcpp::stop("sfheaders - unsupported coordinate type");  // #nocov
//   }
//     Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
//     //if (lst.size() == 0 ) {
//     //return 0; // ?
//     //}
//     R_xlen_t n = lst.size();
//     R_xlen_t i;
//     Rcpp::IntegerVector res( n );
//     for( i = 0; i < n; ++i ) {
//       SEXP tmp_sfg = lst[i];
//       sfg_n_coordinates( tmp_sfg, sfg_count );  // recurse
//     }
//     break;
//   }
//   default: {
//     Rcpp::stop("sfheaders - unsupported coordinate type");  // #nocov
//   }
//   }
//
//   //return sfg_count;
// }

// if I make this cumulative, it gives me a vector where the last element
// is the size of any result, and each element
// is the row index where a new element starts
// inline Rcpp::NumericMatrix sfc_n_coordinates(
//     Rcpp::List& sfc
// ) {
//
//   R_xlen_t cumulative_coords = 0;
//   R_xlen_t n = sfc.size();
//   Rcpp::NumericMatrix res( n, 2 );
//   R_xlen_t i;
//
//   for( i = 0; i < n; ++i ) {
//     R_xlen_t sfg_counter = 0;
//     SEXP sfg = sfc[i];
//     sfg_n_coordinates( sfg, sfg_counter );
//
//     res( i, 0 ) = cumulative_coords;
//     cumulative_coords += sfg_counter;
//     res( i, 1 ) = cumulative_coords - 1;
//   }
//   return res;
// }

// sfcs are a list of sfgs.
// they can be mixed, or individual.
// if indiidual, loop over each one and extract the sfgs, list by list, then collapse the lists??

// inline Rcpp::List get_sfg_coordinates( SEXP& sfg, R_xlen_t& sfc_rows, int SFG_TYPE ) {
//
//   switch( SFG_TYPE ) {
//   case SFG_POINT: {
//     Rcpp::NumericVector vec = Rcpp::as< Rcpp::NumericVector >( sfg );
//     return sfheaders::df::sfg_point_coordinates( vec, sfc_rows );
//   }
//   case SFG_MULTIPOINT: {
//     Rcpp::NumericMatrix mat = Rcpp::as< Rcpp::NumericMatrix >( sfg );
//     return sfheaders::df::sfg_multipoint_coordinates( mat, sfc_rows );
//   }
//   case SFG_LINESTRING: {
//     Rcpp::NumericMatrix mat = Rcpp::as< Rcpp::NumericMatrix >( sfg );
//     return sfheaders::df::sfg_linestring_coordinates( mat, sfc_rows );
//   }
//   case SFG_MULTILINESTRING: {
//     Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
//     return sfheaders::df::sfg_multilinestring_coordinates( lst, sfc_rows );
//   }
//   case SFG_POLYGON: {
//     Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
//     return sfheaders::df::sfg_polygon_coordinates( lst, sfc_rows );
//   }
//   case SFG_MULTIPOLYGON: {
//     Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
//     return sfheaders::df::sfg_multipolygon_coordinates( lst, sfc_rows );
//   }
//   default: {
//     Rcpp::stop("sfheaders - unknown sfg type");  // #nocov
//   }
//   }
//   return Rcpp::List::create(); // #nocov never reaches
// }

// inline int get_sfg_type( std::string& sfg ) {
//   if( sfg == "POINT" ) {
//     return SFG_POINT;
//   } else if ( sfg == "MULTIPOINT" ) {
//     return SFG_MULTIPOINT;
//   } else if ( sfg == "LINESTRING" ) {
//     return SFG_LINESTRING;
//   } else if ( sfg == "MULTILINESTRING" ) {
//     return SFG_MULTILINESTRING;
//   } else if ( sfg == "POLYGON" ) {
//     return SFG_POLYGON;
//   } else if ( sfg == "MULTIPOLYGON" ) {
//     return SFG_MULTIPOLYGON;
//   } else {
//     Rcpp::stop("sfheaders - unknown sfg type");  // #nocov
//   }
// }

// defines which column will store the unique counter
// based on which geometry is being CAST TO




// inline int get_sfg_column_index( std::string& sfg ) {
//   if( sfg == "POINT" ) {
//     return MATRIX_ID;
//   } else if ( sfg == "MULTIPOINT" ) {
//     return MATRIX_ID;
//   } else if ( sfg == "LINESTRING" ) {
//     return MATRIX_ID;
//   } else if ( sfg == "MULTILINESTRING" ) {
//     return LIST_MATRIX_ID;
//   } else if ( sfg == "POLYGON" ) {
//     return LIST_MATRIX_ID;
//   } else if ( sfg == "MULTIPOLYGON" ) {
//     return LIST_LIST_MATRIX_ID;
//   } else {
//     Rcpp::stop("sfheaders - unknown sfg type");  // #nocov
//   }
// }
//
// inline Rcpp::List get_sfc_coordinates( Rcpp::List& sfc, R_xlen_t& total_coordinates ) {
//
//   Rcpp::LogicalVector columns( MAX_COLUMNS_CAST ); // keeping track of which to subset
//   columns[ X_COLUMN_CAST ] = true;
//   columns[ Y_COLUMN_CAST ] = true;
//   columns[ SFG_COLUMN_CAST ] = true;
//   columns[ MATRIX_ID ] = true;
//   columns[ LIST_MATRIX_ID ] = true;
//   columns[ LIST_LIST_MATRIX_ID ] = true;
//
//   R_xlen_t n_sfg = sfc.size();
//   R_xlen_t i;
//   R_xlen_t j;
//   R_xlen_t n_col;
//
//   Rcpp::CharacterVector cls;
//   std::string dim;
//   std::string sfg_class;
//   int sfg_type;
//   int sfg_column_idx;
//
//   R_xlen_t sfc_rows = 0;
//   R_xlen_t total_rows = 0;
//
//   double id;
//
//   Rcpp::List res = setup_result( total_coordinates );
//
//   for( i = 0; i < n_sfg; ++i ) {
//
//     SEXP sfci = sfc[ i ];
//
//     cls = sfheaders::utils::getSfgClass( sfci );
//
//     dim = cls[0];
//
//     if( dim == "XYZ" ) {
//       columns[ Z_COLUMN ] = true;
//     } else if ( dim == "XYZM" ) {
//       columns[ M_COLUMN ] = true;
//     }
//
//     sfg_class = cls[1];
//     sfg_type = sfheaders::df::get_sfg_type( sfg_class );
//     //sfg_column_idx = get_sfg_column_index( sfg_class );
//     //columns[ sfg_column_idx ] = true;
//
//     Rcpp::List sfg = sfheaders::df::get_sfg_coordinates( sfci, sfc_rows, sfg_type );
//
//     n_col = sfg.size();
//
//     Rcpp::IntegerVector sfg_cols = get_sfg_cols( n_col, sfg_type, dim );
//     column_index_check( sfg_cols, n_col );
//
//     for( j = 0; j < n_col; ++j ) {
//
//       Rcpp::NumericVector new_values_vector = sfg[ j ];
//       int col_idx = sfg_cols[ j ];
//       columns[ col_idx ] = true;
//       Rcpp::NumericVector current_values_vector = res[ col_idx ];
//       Rcpp::NumericVector result_vector = sfheaders::utils::fill_vector( current_values_vector, new_values_vector, total_rows );
//       res[ col_idx ] = result_vector;
//     }
//
//     id = i + 1;
//     Rcpp::NumericVector new_id_vector = Rcpp::rep( id, sfc_rows );
//     Rcpp::NumericVector current_id_vector = res[ SFG_COLUMN_CAST ];
//     Rcpp::NumericVector filled = sfheaders::utils::fill_vector( current_id_vector, new_id_vector, total_rows );
//     res[ SFG_COLUMN_CAST ] = filled;
//
//     Rcpp::NumericVector current_sfg_id_vector = res[ SFC_COLUMN_CAST ];
//     filled = sfheaders::utils::fill_vector( current_sfg_id_vector, new_id_vector, total_rows );
//
//     res[ SFC_COLUMN_CAST ] = filled;
//
//     total_rows = total_rows + sfc_rows;
//   }
//
//   //Rcpp::Rcout << "columns: " << columns << std::endl;
//
//   // make data.frame
//   res = res[ columns ];
//   res.attr("class") = Rcpp::CharacterVector("data.frame");
//
//   if( total_coordinates > 0 ) {
//     Rcpp::IntegerVector rownames = Rcpp::seq( 1, total_coordinates );
//     res.attr("row.names") = rownames;
//   } else {
//     res.attr("row.names") = Rcpp::IntegerVector(0);  // #nocov
//   }
//
//   res.attr("names") = column_names[ columns ];
//   return res;
// }
//
// inline Rcpp::List sfc_to_cast_df(
//     Rcpp::List& sfc,
//     Rcpp::NumericMatrix& sfc_coordinates
// ) {
//   R_xlen_t n_geometries = sfc_coordinates.nrow();
//   R_xlen_t total_coordinates = sfc_coordinates( n_geometries - 1 , 1 );
//   total_coordinates = total_coordinates + 1;
//
//   return get_sfc_coordinates( sfc, total_coordinates );
// }
//
// inline Rcpp::List sfc_to_cast_df( Rcpp::List& sfc ) {
//   // seprated this so it's independant / not called twice from `sf_to_df()`
//   Rcpp::NumericMatrix sfc_coordinates = sfheaders::df::sfc_n_coordinates( sfc );
//   return sfc_to_cast_df( sfc, sfc_coordinates );
// }


} // cast
} // sfheaders


#endif
