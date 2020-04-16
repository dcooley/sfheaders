#ifndef R_SFHEADERS_DF_SFG_H
#define R_SFHEADERS_DF_SFG_H

#include "sfheaders/utils/sexp/sexp.hpp"
#include "sfheaders/sfg/sfg_types.hpp"
#include "sfheaders/df/utils.hpp"

#include <Rcpp.h>

#define M_COLUMN                  12
#define Z_COLUMN                  11
#define Y_COLUMN                  10
#define X_COLUMN                  9
#define POINT_COLUMN              8
#define MULTIPOINT_COLUMN         7
#define LINESTRING_COLUMN         6
#define MULTILINESTRING_COLUMN    5
#define POLYGON_COLUMN            4
#define MULTIPOLYGON_COLUMN       3
#define GEOMETRYCOLLECTION_COLUMN 2
#define SFG_COLUMN                1
#define SFC_COLUMN                0

#define MAX_COLUMNS               13

namespace sfheaders {
namespace df {

  const Rcpp::CharacterVector column_names = {
    "sfc_id", "sfg_id", "geometrycollection_id", "multipolygon_id", "polygon_id", "multilinestring_id",
    "linestring_id", "multipoint_id", "point_id", "x","y","z","m"
  };

  inline Rcpp::CharacterVector make_names( Rcpp::CharacterVector& cls ) {

    std::string dim;
    std::string geometry;

    Rcpp::LogicalVector columns( column_names.length() );

    dim = cls[0];
    geometry = cls[1];

    if ( dim == "XYZM" ) {
      columns[ Z_COLUMN ] = true;
      columns[ M_COLUMN ] = true;
    } else if ( dim == "XYZ" ) {
      columns[ Z_COLUMN ] = true;
    } else if ( dim == "XYM" ) {
      columns[ M_COLUMN ] = true;
    }

    columns[ X_COLUMN ] = true;
    columns[ Y_COLUMN ] = true;

    if( geometry == "POINT" ) {
    } else if ( geometry == "MULTIPOINT" ) {

    } else if ( geometry == "LINESTRING" ) {

    } else if ( geometry == "MULTILINESTRING" ) {
      columns[ LINESTRING_COLUMN ] = true;

    } else if ( geometry == "POLYGON" ) {
      columns[ LINESTRING_COLUMN ] = true;

    } else if ( geometry == "MULTIPOLYGON" ) {
      columns[ LINESTRING_COLUMN ] = true;
      columns[ POLYGON_COLUMN ] = true;
    }
    return column_names[ columns ];
  }

  inline Rcpp::List matrix_to_list( Rcpp::NumericMatrix& mat, R_xlen_t& sfg_rows ) {

    R_xlen_t n_col = mat.ncol();
    Rcpp::List res( n_col );
    R_xlen_t i;
    for( i = 0; i < n_col; ++i ) {
      res[ i ] = mat( Rcpp::_, i );
    }
    sfg_rows = mat.nrow();
    return res;
  }

  // this will put an 'id' directly onto the matrix
  inline Rcpp::List matrix_to_list( Rcpp::NumericMatrix& mat, R_xlen_t& sfg_rows, double& id ) {
    R_xlen_t n_col = mat.ncol();
    R_xlen_t n_row = mat.nrow();
    Rcpp::NumericVector id_vector = Rcpp::rep( id, n_row );
    Rcpp::List res( n_col + 1);  // for the id
    res[ 0 ] = id_vector;

    R_xlen_t i;

    for( i = 0; i < n_col; ++i ) {
      res[ i + 1 ] = mat( Rcpp::_, i );
    }
    sfg_rows = mat.nrow();
    return res;
  }

  template< int RTYPE >
  inline Rcpp::List vector_to_list( Rcpp::Vector< RTYPE >& v, R_xlen_t& sfg_rows ) {
    R_xlen_t n = v.length();
    Rcpp::List res( n );
    R_xlen_t i;
    for( i = 0; i < n; ++i ) {
      res[ i ] = v[ i ];
    }
    sfg_rows = 1; // TODO??
    return res;
  }

  template< int RTYPE >
  inline Rcpp::List vector_to_list( Rcpp::Vector< RTYPE >& v, R_xlen_t& sfg_rows, double& id ) {
    R_xlen_t n = v.length();
    Rcpp::List res( n + 1 );
    //Rcpp::NumericVector id_vector = Rcpp::seq( id, id + n );
    res[ 0 ] = id;
    ++id;
    R_xlen_t i;
    for( i = 0; i < n; ++i ) {
      res[ i + 1 ] = v[ i ];
    }
    sfg_rows = 1; // TODO??
    return res;
  }


  /*
   * collapses a list of list of vectors
   *
   * list(
   *   list(
   *     x = c(),
   *     y = c(),
   *     z = c()
   *   ),
   *   list(
   *     x = c(),
   *     y = c(),
   *     z = c()
   *   )
   * )
   *
   * and adds an 'id' column
   */
  inline Rcpp::List collapse_list( Rcpp::List& lst, R_xlen_t& total_rows ) {

    R_xlen_t lst_size = lst.size();
    // each list must have the same number of columns.
    if( lst_size == 0 ) {
      return lst; // #nocov
    }

    R_xlen_t i;
    R_xlen_t j;

    Rcpp::List first_list = lst[ 0 ];
    R_xlen_t n_vectors = first_list.length() + 1; // vector for each matrix column, and an id column

    Rcpp::List lst_res( n_vectors );

    for( i = 0; i < n_vectors; ++i ) {
      lst_res[ i ] = Rcpp::NumericVector( total_rows, Rcpp::NumericVector::get_na() );
    }

    R_xlen_t row_counter = 0;
    R_xlen_t vector_size = 0;

    for( i = 0; i < lst_size; ++i ) {
      Rcpp::List inner_list = lst[ i ];
      R_xlen_t n_col = inner_list.size();

      if( n_vectors - 1 != n_col ) {
        Rcpp::stop("sfheaders - unknown issue - please report this, along with an example, at www.github.com/dcooley/sfheaders/issues"); // #nocov
      }

      for( j = 0; j < n_col; ++j ) {

        SEXP s = inner_list[ j ];
        Rcpp::NumericVector new_vector = Rcpp::as< Rcpp::NumericVector >( s );
        vector_size = new_vector.length();

        Rcpp::NumericVector current_vector = lst_res[ j + 1 ];
        lst_res[ j + 1 ] = sfheaders::utils::fill_vector( current_vector, new_vector, row_counter );;
      }

      // id column
      double id = i + 1;
      SEXP s2 = lst_res[ 0 ];
      Rcpp::NumericVector current_id_vector = Rcpp::as< Rcpp::NumericVector >( s2 );
      Rcpp::NumericVector new_id_vector = Rcpp::rep( id, vector_size );

      lst_res[ 0 ] = sfheaders::utils::fill_vector( current_id_vector, new_id_vector, row_counter );

      row_counter = row_counter + vector_size;
    }
    return lst_res;
  }

  // collapse_list - user-supplied 'id', incremented for each list element.
  inline Rcpp::List collapse_list( Rcpp::List& lst, R_xlen_t& total_rows, double& id ) {

    R_xlen_t lst_size = lst.size();
    // each list must have the same number of columns.
    if( lst_size == 0 ) {
      return lst; // #nocov
    }

    R_xlen_t i;
    R_xlen_t j;

    Rcpp::List first_list = lst[ 0 ];
    R_xlen_t n_vectors = first_list.length() + 1; // vector for each matrix column, and an id column

    Rcpp::List lst_res( n_vectors );

    for( i = 0; i < n_vectors; ++i ) {
      lst_res[ i ] = Rcpp::NumericVector( total_rows, Rcpp::NumericVector::get_na() );
    }

    R_xlen_t row_counter = 0;
    R_xlen_t vector_size = 0;

    for( i = 0; i < lst_size; ++i ) {
      Rcpp::List inner_list = lst[ i ];
      R_xlen_t n_col = inner_list.size();

      if( n_vectors - 1 != n_col ) {
        Rcpp::stop("sfheaders - unknown issue - please report this, along with an example, at www.github.com/dcooley/sfheaders/issues"); // #nocov
      }

      for( j = 0; j < n_col; ++j ) {

        SEXP s = inner_list[ j ];
        Rcpp::NumericVector new_vector = Rcpp::as< Rcpp::NumericVector >( s );
        vector_size = new_vector.length();

        Rcpp::NumericVector current_vector = lst_res[ j + 1 ];
        lst_res[ j + 1 ] = sfheaders::utils::fill_vector( current_vector, new_vector, row_counter );;
      }

      // id column
      //double id = i + 1;
      SEXP s2 = lst_res[ 0 ];
      Rcpp::NumericVector current_id_vector = Rcpp::as< Rcpp::NumericVector >( s2 );
      Rcpp::NumericVector new_id_vector = Rcpp::rep( id, vector_size );

      lst_res[ 0 ] = sfheaders::utils::fill_vector( current_id_vector, new_id_vector, row_counter );

      row_counter = row_counter + vector_size;
      ++id;
    }
    return lst_res;
  }

  // similar to 'collapse_list()', but gives all
  // list elements the same 'id'
  inline Rcpp::List infuse_list( Rcpp::List& lst, R_xlen_t& total_rows, double& id ) {

    R_xlen_t lst_size = lst.size();
    // each list must have the same number of columns.
    if( lst_size == 0 ) {
      return lst; // #nocov
    }

    R_xlen_t i;
    R_xlen_t j;

    Rcpp::List first_list = lst[ 0 ];
    R_xlen_t n_vectors = first_list.length() + 1; // vector for each matrix column, and an id column

    Rcpp::List lst_res( n_vectors );

    for( i = 0; i < n_vectors; ++i ) {
      lst_res[ i ] = Rcpp::NumericVector( total_rows, Rcpp::NumericVector::get_na() );
    }

    R_xlen_t row_counter = 0;
    R_xlen_t vector_size = 0;

    for( i = 0; i < lst_size; ++i ) {
      Rcpp::List inner_list = lst[ i ];
      R_xlen_t n_col = inner_list.size();

      if( n_vectors - 1 != n_col ) {
        Rcpp::stop("sfheaders - unknown issue - please report this, along with an example, at www.github.com/dcooley/sfheaders/issues"); // #nocov
      }

      for( j = 0; j < n_col; ++j ) {

        SEXP s = inner_list[ j ];
        Rcpp::NumericVector new_vector = Rcpp::as< Rcpp::NumericVector >( s );
        vector_size = new_vector.length();

        Rcpp::NumericVector current_vector = lst_res[ j + 1 ];
        lst_res[ j + 1 ] = sfheaders::utils::fill_vector( current_vector, new_vector, row_counter );;
      }

      // id column
      //double id = i + 1;
      SEXP s2 = lst_res[ 0 ];
      Rcpp::NumericVector current_id_vector = Rcpp::as< Rcpp::NumericVector >( s2 );
      Rcpp::NumericVector new_id_vector = Rcpp::rep( id, vector_size );

      lst_res[ 0 ] = sfheaders::utils::fill_vector( current_id_vector, new_id_vector, row_counter );

      row_counter = row_counter + vector_size;
    }
    return lst_res;
  }

  template < int RTYPE >
  inline Rcpp::List sfg_point_coordinates( Rcpp::Vector< RTYPE >& sfg, R_xlen_t& sfg_rows ) {
    Rcpp::List res = vector_to_list( sfg, sfg_rows );
    return res;
  }

  inline Rcpp::List sfg_multipoint_coordinates( Rcpp::NumericMatrix& sfg, R_xlen_t& sfg_rows) {
    Rcpp::List res = matrix_to_list( sfg, sfg_rows );
    return res;
  }

  inline Rcpp::List sfg_linestring_coordinates( Rcpp::NumericMatrix& sfg, R_xlen_t& sfg_rows ) {
    Rcpp::List res = matrix_to_list( sfg, sfg_rows );
    return res;
  }

  inline Rcpp::List sfg_multilinestring_coordinates( Rcpp::List& sfg, R_xlen_t& sfg_rows ) {
    R_xlen_t i;
    R_xlen_t n = sfg.size();
    Rcpp::List res( n );
    R_xlen_t total_rows = 0;
    for( i = 0; i < n; ++i ) {
      Rcpp::NumericMatrix mat = sfg[ i ];
      total_rows = total_rows + mat.nrow();
      res[ i ] = matrix_to_list( mat, sfg_rows );
    }
    sfg_rows = total_rows;
    res = collapse_list( res, total_rows );
    return res;
  }

  inline Rcpp::List sfg_polygon_coordinates( Rcpp::List& sfg, R_xlen_t& sfg_rows ) {
    return sfg_multilinestring_coordinates( sfg, sfg_rows );
  }

  inline Rcpp::List sfg_multipolygon_coordinates( Rcpp::List& sfg, R_xlen_t& sfg_rows ) {
    R_xlen_t i;

    R_xlen_t n = sfg.size();
    Rcpp::List res( n );
    R_xlen_t total_rows = 0;
    R_xlen_t inner_total_rows;

    sfheaders::utils::getSfgClass( sfg );

    for( i = 0; i < n; ++i ) {
      Rcpp::List lst = sfg[ i ];

      R_xlen_t inner_n = lst.size();
      inner_total_rows = 0;
      Rcpp::List inner_res( inner_n );

      res[ i ] = sfg_polygon_coordinates( lst, inner_total_rows );
      total_rows = total_rows + inner_total_rows;
    }

    sfg_rows = total_rows;
    res = collapse_list( res, total_rows );
    return res;
  }

  inline Rcpp::List sfg_to_df( SEXP& sfg ) {

    Rcpp::List res;

    Rcpp::CharacterVector cls = sfheaders::utils::getSfgClass( sfg );

    //std::string dim;
    std::string geometry;

    Rcpp::LogicalVector columns( column_names.length() );

    //dim = cls[0];
    geometry = cls[1];

    R_xlen_t sfg_rows = 0;

    if( geometry == "POINT" ) {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( sfg );
      res = sfg_point_coordinates( nv, sfg_rows );

    } else if ( geometry == "MULTIPOINT" ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( sfg );
      res = sfg_multipoint_coordinates( nm, sfg_rows );

    } else if ( geometry == "LINESTRING" ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( sfg );
      res = sfg_linestring_coordinates( nm, sfg_rows );

    } else if ( geometry == "MULTILINESTRING" ) {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      res = sfg_multilinestring_coordinates( lst, sfg_rows );

    } else if ( geometry == "POLYGON" ) {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      res = sfg_polygon_coordinates( lst, sfg_rows );

    } else if ( geometry == "MULTIPOLYGON" ) {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      res = sfg_multipolygon_coordinates( lst, sfg_rows );

    } else {
      Rcpp::stop("sfheaders - unknown geometry type"); // #nocov
    }

    Rcpp::CharacterVector df_names = make_names( cls );

    res.attr("class") = Rcpp::CharacterVector("data.frame");

    if( sfg_rows > 0 ) {
      Rcpp::IntegerVector rownames = Rcpp::seq( 1, sfg_rows );
      res.attr("row.names") = rownames;
    } else {
      res.attr("row.names") = Rcpp::IntegerVector(0); // #nocov
    }

    res.attr("names") = df_names;
    return res;
  }

} // df
} // sfheaders

#endif
