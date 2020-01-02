#ifndef R_SFHEADERS_DF_SFG_H
#define R_SFHEADERS_DF_SFG_H

#include "sfheaders/utils/sexp/sexp.hpp"
//#include "sfheaders/df/utils.hpp"

#include <Rcpp.h>

namespace sfheaders {
namespace df {

  template <int RTYPE>
  inline Rcpp::CharacterVector sfgClass( Rcpp::Vector<RTYPE> v ) {
    return v.attr("class");
  }

  inline Rcpp::CharacterVector getSfgClass( SEXP sfg ) {

    switch( TYPEOF( sfg ) ) {
    case REALSXP:
      return sfgClass<REALSXP>( sfg );
    case VECSXP:
      return sfgClass<VECSXP>( sfg );
    case INTSXP:
      return sfgClass<INTSXP>( sfg );
    default: Rcpp::stop("unknown sf type");
    }
    return Rcpp::CharacterVector();
  }

  inline Rcpp::NumericMatrix add_id_column( Rcpp::NumericMatrix& mat, double id ) {
    // expands a matrix by one-column and adds the id value

    R_xlen_t n_col = mat.ncol();
    R_xlen_t n_row = mat.nrow();
    Rcpp::NumericVector id_column = Rcpp::rep( id, n_row );

    Rcpp::NumericMatrix res( n_row, n_col + 1 ); // to store id column

    // Rcpp::Rcout << "id_column: " << id_column << std::endl;
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

    //Rcpp::Rcout << "n: " << n << std::endl;

    if( n == 0 ) {
      // TODO:
      // return empty?
    }
    R_xlen_t total_rows = 0;
    for( i = 0; i < n; ++i ) {
      SEXP sfg = lst[ i ];
      total_rows += sfheaders::utils::sexp_n_row( sfg );
    }

    //Rcpp::Rcout << "total_rows: " << total_rows << std::endl;

    // can now create a vector (matrix) based on the number of rows, and teh number of columns.
    Rcpp::NumericMatrix first_mat = lst[ 0 ];
    R_xlen_t n_col = first_mat.ncol();

    //Rcpp::Rcout << "n_col: " << n_col << std::endl;

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
        //::Rcout << "v: " << v << std::endl;

        Rcpp::NumericVector res_vec = lst_res[ j ];
        std::copy( v.begin(), v.end(), res_vec.begin() + row_counter );
        //Rcpp::Rcout << "res_vec: " << res_vec << std::endl;
        lst_res[ j ] = Rcpp::clone( res_vec );  // these are pointers, not the actual vectors.
      }
      row_counter = row_counter + inner_mat.nrow();
    }

    // fill final matrix.
    for( i = 0; i < n_col; ++i ) {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( lst_res[ i ] );
      //Rcpp::Rcout << "nv: " << nv << std::endl;
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
        Rcpp::NumericMatrix res2 = Rcpp::clone( res );
        res2.attr("class") = R_NilValue;
        return res2;
      } else {
        // it's a vector
        Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( sfg );
        Rcpp::NumericVector nv2 = Rcpp::clone( nv );
        res = vector_to_matrix( nv2 );
        return res;
      }
      break;
    case VECSXP: {
      if( Rf_inherits( sfg, "data.frame" ) ) {
        Rcpp::stop("sfheaders - expecting either a vector, matrix or list");
      } else {

        Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
        R_xlen_t n = lst.size();
        R_xlen_t i;
        // create a lsit of matrices, then collapse them
        Rcpp::List lst_res( n );

        for( i = 0; i < n; i++ ) {
          SEXP inner_sfg = lst[i];
          Rcpp::NumericMatrix inner_mat = sfg_coordinates( inner_sfg );
          id = i + 1;
          inner_mat = add_id_column( inner_mat, id );

          lst_res[i] = inner_mat;
        }

        res = list_to_matrix( lst_res );
      }
      break;
      }
    }
    return res;
  }

  const Rcpp::CharacterVector column_names = {
    "sfc_id", "sfg_id", "multipolygon_id", "polygon_id", "multilinestring_id",
    "linestring_id", "multipoint_id", "point_id", "x","y","z","m"
  };

  const int m_column               = 11;
  const int z_column               = 10;
  const int y_column               = 9;
  const int x_column               = 8;
  const int point_column           = 7;
  const int multipoint_column      = 6;
  const int linestring_column      = 5;
  const int multilinestring_column = 4;
  const int polygon_column         = 3;
  const int multipolygon_column    = 2;
  const int sfg_column             = 1;
  const int sfc_column             = 0;

  inline Rcpp::CharacterVector make_names( SEXP& sfg ) {
    Rcpp::CharacterVector cls = getSfgClass( sfg );

    std::string dim;
    std::string geometry;

    Rcpp::LogicalVector columns( column_names.length() );

    dim = cls[0];
    geometry = cls[1];

    if ( dim == "XYZM" ) {
      columns[ z_column ] = true;
      columns[ m_column ] = true;
    } else if ( dim == "XYZ" ) {
      columns[ z_column ] = true;
    } else if ( dim == "XYM" ) {
      columns[ m_column ] = true;
    }

    columns[ x_column ] = true;
    columns[ y_column ] = true;

    if( geometry == "POINT" ) {
      // nothing
    } else if ( geometry == "MULTIPOINT" ) {
      // columns[ point_column ] = true;
      // nothing??
    } else if ( geometry == "LINESTRING" ) {
      // nothing
    } else if ( geometry == "MULTILINESTRING" ) {
      columns[ linestring_column ] = true;
    } else if ( geometry == "POLYGON" ) {
      columns[ linestring_column ] = true;
    } else if ( geometry == "MULTIPOLYGON" ) {
      columns[ linestring_column ] = true;
      columns[ polygon_column ] = true;
    }

    return column_names[ columns ];

  }

  // to data.frame
  // we know the geometry type from the class
  // so we know which id columns are required
  // so the remainder must be x, y, z, m
  inline SEXP sfg_to_df( SEXP& sfg ) {

    Rcpp::NumericMatrix mat = sfg_coordinates( sfg );
    R_xlen_t n_row = mat.nrow();
    R_xlen_t n_col = mat.ncol();
    R_xlen_t i;

    Rcpp::CharacterVector df_names = make_names( sfg );

    Rcpp::List df( n_col );
    for( i = 0; i < n_col; ++i ) {
      df[ i ] = mat( Rcpp::_, i );
    }

    df.attr("class") = Rcpp::CharacterVector("data.frame");

    if( n_row > 0 ) {
      Rcpp::IntegerVector rownames = Rcpp::seq( 1, n_row );
      df.attr("row.names") = rownames;
    } else {
      df.attr("row.names") = Rcpp::IntegerVector(0);
    }

    df.names() = df_names;

    //Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( mat );
    //sfheaders::df::make_names( df );
    return df;
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
