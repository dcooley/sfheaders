#ifndef R_SFHEADERS_DF_SFG_H
#define R_SFHEADERS_DF_SFG_H

#include "sfheaders/utils/sexp/sexp.hpp"
//#include "sfheaders/df/utils.hpp"

#include <Rcpp.h>

namespace sfheaders {
namespace df {

  inline Rcpp::NumericMatrix add_id_column( Rcpp::NumericMatrix& mat, double id ) {
    // expands a matrix by one-column and adds the id value

    R_xlen_t n_col = mat.ncol();
    R_xlen_t n_row = mat.nrow();
    Rcpp::NumericVector id_column = Rcpp::rep( id, n_row );

    Rcpp::NumericMatrix res( n_row, n_col + 1 ); // to store id column

    res( Rcpp::_, 0 ) = id_column;

    // then put the geometries in the remaining columns
    R_xlen_t i;
    for( i = 0; i < n_col; ++i ) {
      res( Rcpp::_, i + 1 ) = mat( Rcpp::_, i );
    }
    return res;
  }


  template < int RTYPE >
  inline Rcpp::NumericMatrix vector_to_matrix( Rcpp::Vector< RTYPE >& v ) {
    R_xlen_t n_col = v.length();
    v.attr("class") = R_NilValue;
    v.attr("dim") = Rcpp::Dimension( 1, n_col );
    return Rcpp::as< Rcpp::NumericMatrix >( v );
  }


  inline Rcpp::NumericMatrix list_to_matrix( Rcpp::List& lst ) {
    // only works with a list where each element is a matrix, no sub-lists.
    R_xlen_t i, j;
    R_xlen_t n = lst.size();

    Rcpp::Rcout << "n: " << n << std::endl;

    if( n == 0 ) {
      // TODO:
      // return empty?
    }
    R_xlen_t total_rows = 0;
    for( i = 0; i < n; ++i ) {
      SEXP sfg = lst[ i ];
      total_rows += sfheaders::utils::sexp_n_row( sfg );
    }

    Rcpp::Rcout << "total_rows: " << total_rows << std::endl;

    // can now create a vector (matrix) based on the number of rows, and teh number of columns.
    Rcpp::NumericMatrix first_mat = lst[ 0 ];
    R_xlen_t n_col = first_mat.ncol();

    Rcpp::Rcout << "n_col: " << n_col << std::endl;

    Rcpp::List lst_res( n_col ); // vector for each matrix column.
    Rcpp::NumericVector to_fill = Rcpp::NumericVector( total_rows, Rcpp::NumericVector::get_na() );
    //Rcpp::Rcout << "to_fill: " << to_fill << std::endl;
    for( i = 0; i < n_col; ++i ) {
      lst_res[ i ] = to_fill;
    }

    Rcpp::NumericMatrix res( total_rows, n_col );
    R_xlen_t row_counter = 0;

    for( i = 0; i < n; ++i ) {
      Rcpp::NumericMatrix inner_mat = lst[ i ];
      //Rcpp::Rcout << "inner_mat: " << inner_mat << std::endl;

      for( j = 0; j < n_col; ++j ) {
        Rcpp::NumericVector v = inner_mat( Rcpp::_, j );
        Rcpp::Rcout << "v: " << v << std::endl;
        Rcpp::Rcout << "row_counter: " << row_counter << std::endl;

        Rcpp::NumericVector res_vec = lst_res[ j ];
        Rcpp::Rcout << "res_vec size: " << res_vec.length() << std::endl;
        std::copy( v.begin(), v.end(), res_vec.begin() + row_counter );
        Rcpp::Rcout << "res_vec: " << res_vec << std::endl;
        lst_res[ j ] = res_vec;
      }

      row_counter = row_counter + inner_mat.nrow();

    }

    // fill final matrix.
    for( i = 0; i < n_col; ++i ) {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( lst_res[ i ] );
      Rcpp::Rcout << "nv: " << nv << std::endl;
      res( Rcpp::_, i ) = nv;
    }

    return res;
  }

  // returns the coordinates of an sfg object as a single matrix
  inline Rcpp::NumericMatrix sfg_coordinates( SEXP& sfg ) {

    Rcpp::NumericMatrix res;
    double id;

    switch( TYPEOF( sfg ) ) {
    case INTSXP: {}
    case REALSXP: {}
      if( Rf_isMatrix( sfg ) ) {
        res = Rcpp::as< Rcpp::NumericMatrix >( sfg );
      } else {
        // it's a vector
        Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( sfg );
        res = vector_to_matrix( nv );
      }
      break;
    case VECSXP: {
      if( Rf_inherits( sfg, "data.frame" ) ) {
      Rcpp::stop("sfheaders - expecting either a vector, matrix or list");
    } else {
      // list
      // multilinestring; will need a linestring_id column
      // polygon; will need a linestring_id column
      // multipolygon; will need a polygon_id and a linestring_id column
      // but how...???
      // the depth of the list tells you how many id columns
      // and teh sfg class tells you the names of those columns.
      // right??
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      R_xlen_t n = lst.size();
      R_xlen_t i;
      // create a lsit of matrices, then collapse them
      Rcpp::List lst_res( n );

      for( i = 0; i < n; i++ ) {
        SEXP inner_sfg = lst[i];
        Rcpp::NumericMatrix inner_mat = sfg_coordinates( inner_sfg );
        id = i;
        add_id_column( inner_mat, id );
        lst_res[i] = inner_mat;
      }

      // collapse list to matrices
      // add id column
      res = list_to_matrix( lst_res );
      id = 1;
      add_id_column( res, id );

    }
    break;
    }
    }

    // attach an sfg_id
    id = 1;
    return add_id_column( res, id );
  }


// template < int RTYPE >
// inline Rcpp::DataFrame sfg_point_to_df(
//     Rcpp::Vector< RTYPE >& sfg
// ) {
//
//   // sfg_POINT is a vector
//   // return data.frame
//   R_xlen_t n_col = sfg.length();
//
//   sfg.attr("class") = R_NilValue;
//   sfg.attr("dim") = Rcpp::Dimension( 1, n_col );
//
//   Rcpp::NumericMatrix mat = Rcpp::as< Rcpp::NumericMatrix >( sfg );
//   Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( mat );
//   sfheaders::df::make_names( df );
//   return df;
// }
//
// template< int RTYPE >
// inline Rcpp::DataFrame sfg_multipoint_to_df(
//     Rcpp::Matrix< RTYPE >& sfg
// ) {
//   sfg.attr("class") = R_NilValue;
//   //Rcpp::NumericMatrix mat = Rcpp::as< Rcpp::NumericMatrix >( sfg );
//   Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( sfg );
//   sfheaders::df::make_names( df );
//   return df;
// }
//
// template< int RTYPE >
// inline Rcpp::DataFrame sfg_linestring_to_df(
//     Rcpp::Matrix< RTYPE > sfg
// ) {
//   return sfg_multipoint_to_df( sfg );
// }
//
// inline void has_zm(
//     Rcpp::LogicalVector& columns,
//     bool& has_z,
//     bool& has_m,
//     std::string& dim
// ) {
//   if( dim == "XYZM" ) {
//     has_z = true;
//     has_m = true;
//   } else if( dim == "XYZ" || dim == "XYM") {
//     has_z = true;
//   }
//
//   if( has_m ) {
//     columns[ sfheaders::utils::z_column ] = true;
//     columns[ sfheaders::utils::m_column ] = true;
//   } else if( has_z ) {
//     columns[ sfheaders::utils::z_column ] = true;
//   }
// }
//
// inline Rcpp::DataFrame sfg_multilinestring_to_df(
//     Rcpp::List& sfg
// ) {
//
//   //bool has_z = false;
//   //bool has_m = false;
//   // Rcpp::LogicalVector columns( sfheaders::utils::max_columns ); // keeping track of which to subset
//
//   // Rcpp::CharacterVector cls = sfg.attr("class");
//   // std::string dim;
//   // dim = cls[0];
//
//   // has_zm( columns, has_z, has_m, dim );
//
//   // columns[ sfheaders::utils::x_column ] = true;
//   // columns[ sfheaders::utils::y_column ] = true;  // x & y always true.
//   // columns[ sfheaders::utils::linestring_column ] = true;
//
//   // need to combine the matrices in each list
//   Rcpp::NumericMatrix mat = sfheaders::utils::sfg_multilinestring_coordinates( sfg );
//   Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( mat );
//
//   return df;
//
//   // start with everthing, then down-select
//   // df.names() = sfheaders::utils::column_names;
//
//   // return df[ columns ];
// }
//
// inline Rcpp::DataFrame sfg_polygon_to_df(
//     Rcpp::List& sfg
// ) {
//   bool has_z = false;
//   bool has_m = false;
//   Rcpp::LogicalVector columns( sfheaders::utils::max_columns ); // keeping track of which to subset
//
//   Rcpp::CharacterVector cls = sfg.attr("class");
//   std::string dim;
//   dim = cls[0];
//
//   has_zm( columns, has_z, has_m, dim );
//
//   columns[ sfheaders::utils::x_column ] = true;
//   columns[ sfheaders::utils::y_column ] = true;  // x & y always true.
//   columns[ sfheaders::utils::linestring_column ] = true;
//
//   // need to combine the matrices in each list
//   Rcpp::NumericMatrix mat = sfheaders::utils::sfg_polygon_coordinates( sfg );
//   Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( mat );
//
//   // start with everthing, then down-select
//   df.names() = sfheaders::utils::column_names;
//
//   return df[ columns ];
// }
//
// inline Rcpp::DataFrame sfg_multipolygon_to_df(
//     Rcpp::List& sfg
// ) {
//   bool has_z = false;
//   bool has_m = false;
//   Rcpp::LogicalVector columns( sfheaders::utils::max_columns ); // keeping track of which to subset
//
//   Rcpp::CharacterVector cls = sfg.attr("class");
//   std::string dim;
//   dim = cls[0];
//
//   has_zm( columns, has_z, has_m, dim );
//
//   columns[ sfheaders::utils::x_column ] = true;
//   columns[ sfheaders::utils::y_column ] = true;  // x & y always true.
//   columns[ sfheaders::utils::linestring_column ] = true;
//   columns[ sfheaders::utils::polygon_column ] = true;
//
//   // need to combine the matrices in each list
//   Rcpp::NumericMatrix mat = sfheaders::utils::sfg_multipolygon_coordinates( sfg );
//   Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( mat );
//
//   // start with everthing, then down-select
//   df.names() = sfheaders::utils::column_names;
//
//   return df[ columns ];
// }

} // df
} // sfheaders

#endif
