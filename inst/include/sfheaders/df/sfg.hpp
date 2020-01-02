#ifndef R_SFHEADERS_DF_SFG_H
#define R_SFHEADERS_DF_SFG_H

#include "sfheaders/utils/sexp/sexp.hpp"
//#include "sfheaders/df/utils.hpp"

#include <Rcpp.h>

namespace sfheaders {
namespace df {

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

    if( n == 0 ) {
      // TODO:
      // return empty?
    }
    R_xlen_t total_rows = 0;
    for( i = 0; i < n; ++i ) {
      SEXP sfg = lst[ i ];
      total_rows += sfheaders::utils::sexp_n_row( sfg );
    }
    // can now create a vector (matrix) based on the number of rows, and teh number of columns.
    Rcpp::NumericMatrix first_mat = lst[ 0 ];
    R_xlen_t n_col = first_mat.ncol();

    Rcpp::List lst_res( n_col ); // vector for each matrix column.
    Rcpp::NumericVector to_fill = Rcpp::NumericVector( total_rows, Rcpp::NumericVector::get_na() );

    for( i = 0; i < n_col; ++i ) {
      lst_res[ i ] = to_fill;
    }

    Rcpp::NumericMatrix res( total_rows, n_col );
    R_xlen_t row_counter = 0;

    for( i = 0; i < n; ++i ) {
      Rcpp::NumericMatrix inner_mat = lst[ i ];

      for( j = 0; j < n_col; ++j ) {
        Rcpp::NumericVector v = inner_mat( Rcpp::_, j );

        Rcpp::NumericVector res_vec = lst_res[ j ];
        std::copy( v.begin(), v.end(), res_vec.begin() + row_counter );
        lst_res[ j ] = Rcpp::clone( res_vec );  // these are pointers, not the actual vectors.
      }
      row_counter = row_counter + inner_mat.nrow();
    }

    // fill final matrix.
    for( i = 0; i < n_col; ++i ) {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( lst_res[ i ] );
      res( Rcpp::_, i ) = nv;
    }

    return res;
  }

  inline Rcpp::List matrix_to_list( Rcpp::NumericMatrix& mat ) {
    //R_xlen_t n_row = mat.nrow();
    R_xlen_t n_col = mat.ncol();
    Rcpp::List res( n_col );
    R_xlen_t i;
    for( i = 0; i < n_col; ++i ) {
      res[ i ] = mat( Rcpp::_, i );
    }
    return res;
  }

  template< int RTYPE >
  inline Rcpp::List vector_to_list( Rcpp::Vector< RTYPE >& v ) {
    R_xlen_t n = v.length();
    Rcpp::List res( n );
    R_xlen_t i;
    for( i = 0; i < n; ++i ) {
      res[ i ] = v[ i ];
    }
    return res;
  }

  // collapses a list of matrices only
  inline Rcpp::List collapse_list( Rcpp::List& lst, R_xlen_t& total_rows ) {

    // if it's a MULTIPOLYGON it's a list of lists
    // so need to go one-level deeper...

    // each list must have the same number of columns.
    if( lst.size() == 0 ) {
      return lst;
    }

    // if the inner-list is another list, around we go.
    R_xlen_t lst_size = lst.size();
    R_xlen_t i;
    R_xlen_t j;

    Rcpp::List first_list = lst[ 0 ];
    R_xlen_t n_vectors = first_list.length();

    Rcpp::List lst_res( n_vectors ); // vector for each matrix column.
    Rcpp::NumericVector to_fill = Rcpp::NumericVector( total_rows, Rcpp::NumericVector::get_na() );
    //Rcpp::Rcout << "to_fill: " << to_fill << std::endl;

    for( i = 0; i < n_vectors; ++i ) {
      lst_res[ i ] = to_fill;
    }

    R_xlen_t row_counter = 0;
    R_xlen_t vector_size = 0;

    for( i = 0; i < n_vectors; ++i ) {
      Rcpp::List inner_list = lst[ i ];
      R_xlen_t n_col = inner_list.size();

      for( j = 0; j < n_col; ++j ) {
        Rcpp::NumericVector v = inner_list[ j ];
        vector_size = v.length();

        Rcpp::NumericVector res_vec = lst_res[ j ];
        std::copy( v.begin(), v.end(), res_vec.begin() + row_counter );
        lst_res[ j ] = Rcpp::clone( res_vec );  // these are pointers, not the actual vectors.
      }
      row_counter = row_counter + vector_size;
    }

    return lst_res;
  }

  template < int RTYPE >
  inline Rcpp::List sfg_point_coordinates( Rcpp::Vector< RTYPE >& sfg ) {
    return vector_to_list( sfg );
  }

  inline Rcpp::List sfg_multipoint_coordinates( Rcpp::NumericMatrix& sfg ) {
    return matrix_to_list( sfg );
  }

  inline Rcpp::List sfg_linestring_coordinates( Rcpp::NumericMatrix& sfg ) {
    return matrix_to_list( sfg );
  }

  inline Rcpp::List sfg_multilinestring_coordinates( Rcpp::List& sfg ) {
    R_xlen_t i;
    R_xlen_t n = sfg.size();
    Rcpp::List res( n );
    R_xlen_t total_rows = 0;
    for( i = 0; i < n; ++i ) {
      Rcpp::NumericMatrix mat = sfg[i];
      total_rows = total_rows + mat.nrow();
      res[i] = matrix_to_list( mat );
    }
    //return res;
    return collapse_list( res, total_rows );
  }

  inline Rcpp::List sfg_polygon_coordinates( Rcpp::List& sfg ) {
    return sfg_multilinestring_coordinates( sfg );
  }

  inline Rcpp::List sfg_multipolygon_coordinates( Rcpp::List& sfg ) {
    R_xlen_t i;
    R_xlen_t j;
    R_xlen_t n = sfg.size();
    Rcpp::List res( n );
    //R_xlent_t
    for( i = 0; i < n; ++i ) {
      Rcpp::List lst = sfg[ i ];
      res[ i ] = sfg_polygon_coordinates( lst );
    }
    //return collapse_list( res, total_rows );
    return res;
  }

  // inline Rcpp::List sfg_coordinate_lists( SEXP& sfg, R_xlen_t& total_rows ) {
  //   // returns the coordinates, where each coordinate is an element of a list.
  //   Rcpp::Rcout << "total_rows - start: " << total_rows << std::endl;
  //
  //   switch( TYPEOF( sfg ) ) {
  //   case INTSXP: {}
  //   case REALSXP: {
  //     total_rows += sfheaders::utils::sexp_n_row( sfg );
  //     if( Rf_isMatrix( sfg ) ) {
  //       Rcpp::NumericMatrix mat = Rcpp::as< Rcpp::NumericMatrix >( sfg );
  //       return matrix_to_list( mat );
  //     } else {
  //       Rcpp::NumericVector v = Rcpp::as< Rcpp::NumericVector >( sfg );
  //       return vector_to_list( v );
  //     }
  //   }
  //   case VECSXP: {
  //     if( Rf_inherits( sfg, "data.frame" ) ) {
  //       Rcpp::stop("sfheaders - expecting either a vector, matrix or list");
  //     } else {
  //
  //       //depth = depth + 1;
  //
  //       // list is for multilinestring, polygon,
  //       // list of list is for multipolygon
  //       Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
  //       R_xlen_t n = lst.size();
  //       R_xlen_t i;
  //
  //       // create a lsit of lists, then collapse them
  //       Rcpp::List lst_res( n );
  //       R_xlen_t inner_total_rows = 0;
  //       Rcpp::Rcout << "inner_total_rows - in: " << inner_total_rows << std::endl;
  //
  //       for( i = 0; i < n; i++ ) {
  //         SEXP inner_sfg = lst[i];
  //
  //         Rcpp::List inner_list = sfg_coordinate_lists( inner_sfg, inner_total_rows );
  //         //id = i + 1;
  //         //inner_mat = add_id_column( inner_mat, id );
  //         lst_res[ i ] = inner_list;
  //       }
  //
  //       // now collapse the list of lists, into a single list...
  //       Rcpp::Rcout << "inner_total_rows - out: " << inner_total_rows << std::endl;
  //
  //       //Rcpp::Rcout << "depth: " << depth << std::endl;
  //       // if( depth > 0 ) {
  //       //   Rcpp::List mp = lst_res[0];
  //       //   res = collapse_lists( mp, inner_total_rows );
  //       // } else {
  //       //   res = collapse_lists( lst_res, inner_total_rows );
  //       // }
  //
  //       //return collapse_lists( lst_res, inner_total_rows );
  //       //lst_res = collapse_lists( lst_res, inner_total_rows );
  //
  //       //break;
  //       return lst_res;
  //
  //       //if( inner_total_rows > 0 ) {
  //         // it's a geometry
  //         // (otherwise it's another list )
  //         //Rcpp::List collapsed_list = collapse_lists( lst_res, inner_total_rows );
  //         //return collapsed_list;
  //       //}
  //
  //     }
  //   }
  //   }
  //   return Rcpp::List();
  //   //return res;
  // }
  //
  // // returns the coordinates of an sfg object as a single matrix
  // inline Rcpp::NumericMatrix sfg_coordinates( SEXP& sfg ) {
  //
  //   Rcpp::NumericMatrix res;
  //   double id;
  //
  //   switch( TYPEOF( sfg ) ) {
  //   case INTSXP: {}
  //   case REALSXP: {}
  //     if( Rf_isMatrix( sfg ) ) {
  //       res = Rcpp::as< Rcpp::NumericMatrix >( sfg );
  //       Rcpp::NumericMatrix res2 = Rcpp::clone( res );
  //       res2.attr("class") = R_NilValue;
  //       return res2;
  //     } else {
  //       // it's a vector
  //       Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( sfg );
  //       Rcpp::NumericVector nv2 = Rcpp::clone( nv );
  //       res = vector_to_matrix( nv2 );
  //       return res;
  //     }
  //     break;
  //   case VECSXP: {
  //     if( Rf_inherits( sfg, "data.frame" ) ) {
  //       Rcpp::stop("sfheaders - expecting either a vector, matrix or list");
  //     } else {
  //
  //       Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
  //       R_xlen_t n = lst.size();
  //       R_xlen_t i;
  //
  //       // create a lsit of matrices, then collapse them
  //       Rcpp::List lst_res( n );
  //
  //       for( i = 0; i < n; i++ ) {
  //         SEXP inner_sfg = lst[i];
  //
  //         Rcpp::NumericMatrix inner_mat = sfg_coordinates( inner_sfg );
  //         id = i + 1;
  //         inner_mat = add_id_column( inner_mat, id );
  //
  //         lst_res[i] = inner_mat;
  //       }
  //       res = list_to_matrix( lst_res );
  //     }
  //     break;
  //     }
  //   }
  //   return res;
  // }
  //
  // inline SEXP sfg_to_df( SEXP& sfg ) {
  //
  //   Rcpp::CharacterVector df_names = make_names( sfg );
  //   Rcpp::NumericMatrix mat = sfg_coordinates( sfg );
  //
  //   R_xlen_t n_row = mat.nrow();
  //   R_xlen_t n_col = mat.ncol();
  //   R_xlen_t i;
  //
  //   Rcpp::List df( n_col );
  //
  //   for( i = 0; i < n_col; ++i ) {
  //     df[ i ] = mat( Rcpp::_, i );
  //   }
  //
  //   df.attr("class") = Rcpp::CharacterVector("data.frame");
  //
  //   if( n_row > 0 ) {
  //     Rcpp::IntegerVector rownames = Rcpp::seq( 1, n_row );
  //     df.attr("row.names") = rownames;
  //   } else {
  //     df.attr("row.names") = Rcpp::IntegerVector(0);
  //   }
  //
  //   df.names() = df_names;
  //
  //   //Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( mat );
  //   //sfheaders::df::make_names( df );
  //   return df;
  // }

} // df
} // sfheaders

#endif
