#ifndef R_SFHEADERS_CAST_SFC_H
#define R_SFHEADERS_CAST_SFC_H

#include "sfheaders/df/sfc.hpp"
#include "sfheaders/cast/sfg.hpp"
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

  inline Rcpp::List vec_to_vec( Rcpp::NumericVector& sfg, R_xlen_t& sfg_rows, double& id ) {
    return sfheaders::df::vector_to_list( sfg, sfg_rows, id );
  }

  inline Rcpp::List mat_to_vec( Rcpp::NumericMatrix& sfg, R_xlen_t& sfg_rows, double& id ) {
    // add an id to each row of the matrix
    R_xlen_t n_row = sfg.nrow();
    Rcpp::NumericMatrix id_mat( n_row, 1 );
    Rcpp::IntegerVector id_vec = Rcpp::seq( id, id + n_row );
    id_mat( Rcpp::_, 0 ) = id_vec;
    Rcpp::NumericMatrix mat =  Rcpp::cbind( id_mat, sfg );
    Rcpp::List res = sfheaders::df::matrix_to_list( mat, n_row );
    sfg_rows = n_row;
    id = id + n_row;    // each vector (row of matrix) gets an incremented id
    return res;
  }

  inline Rcpp::List listMat_to_vec( Rcpp::List& sfg, R_xlen_t& sfg_rows, double& id ) {
    // each matrix gets a sequential id
    // then they get put into a list
    // and the list collapsed
    R_xlen_t n = sfg.size();
    R_xlen_t i;
    Rcpp::List res( n );
    R_xlen_t total_rows = 0;
    for( i = 0; i < n; ++i ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( sfg [ i ] );
      R_xlen_t n_row = nm.nrow();
      total_rows = total_rows + n_row;
      res[ i ] = mat_to_vec( nm, n_row, id );
    }
    sfg_rows = total_rows;
    return sfheaders::df::collapse_list( res, total_rows );
  }

  inline Rcpp::List listListMat_to_vec( Rcpp::List& sfg, R_xlen_t& sfg_rows, double& id ) {

    R_xlen_t n = sfg.size();
    R_xlen_t i;
    Rcpp::List res( n );
    R_xlen_t total_rows = 0;
    for( i = 0; i < n; ++i ) {
      Rcpp::List inner_list = sfg[ i ];
      R_xlen_t inner_n = inner_list.size();
      R_xlen_t inner_total_rows = 0;
      res[ i ] = listMat_to_vec( inner_list, inner_total_rows, id );
      //++id; // increment id for inner matrices
      // the id is incremented by-reference inside matrix_to_list
      total_rows = total_rows + inner_total_rows;
    }

    sfg_rows = total_rows;
    return sfheaders::df::collapse_list( res, sfg_rows );
  }

  inline Rcpp::List vec_to_mat( Rcpp::NumericVector& sfg, R_xlen_t& sfg_rows, double& id ) {
    return sfheaders::df::vector_to_list( sfg, sfg_rows, id );
  }

  inline Rcpp::List mat_to_mat( Rcpp::NumericMatrix& sfg, R_xlen_t& sfg_rows, double& id ) {
    // put an id column on and return it as a list
    return sfheaders::df::matrix_to_list( sfg, sfg_rows, id );
  }

  // e.g. polygon to linestring
  inline Rcpp::List listMat_to_mat( Rcpp::List& sfg, R_xlen_t& sfg_rows, double& id ) {
    // a polygon is a list[[ matrix ]] structure
    // give each matrix an 'id', and increment the id each iteration
    // and store in a final list

    R_xlen_t n = sfg.size();
    R_xlen_t i, j;
    Rcpp::List res( n );
    R_xlen_t total_rows = 0;

    for( i = 0; i < n; ++i ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( sfg[ i ] );
      R_xlen_t n_row = nm.nrow();
      total_rows = total_rows + n_row;
      res[i] = sfheaders::df::matrix_to_list( nm, n_row, id );  // does not increment 'id'
      ++id;
    }

    sfg_rows = total_rows;
    return sfheaders::df::collapse_list( res, total_rows );
  }

  // e.g. multipolygon to linestring
  inline Rcpp::List listListMat_to_mat( Rcpp::List& sfg, R_xlen_t& sfg_rows, double& id ) {

    R_xlen_t n = sfg.size();
    R_xlen_t i;
    R_xlen_t total_rows = 0;
    Rcpp::List res( n );

    // Rcpp::Rcout << "looping" << std::endl;

    for( i = 0; i < n; ++i ) {
      Rcpp::List inner_list = sfg[ i ];
      R_xlen_t inner_n = inner_list.size();
      R_xlen_t inner_total_rows = 0;
      res[ i ] = listMat_to_mat( inner_list, inner_total_rows, id );
      //++id; // increment id for inner matrices
      // the id is incremented by-reference inside matrix_to_list
      total_rows = total_rows + inner_total_rows;
    }

    sfg_rows = total_rows;
    return sfheaders::df::collapse_list( res, sfg_rows );
  }

  // every list-element has the id incremented
  inline Rcpp::List mat_to_listMat( Rcpp::NumericMatrix& sfg, R_xlen_t& sfg_rows, double& id ) {
    // does this need 2x id columns?
    R_xlen_t n_row = sfg.nrow();
    R_xlen_t n_col = sfg.ncol();
    R_xlen_t i;
    Rcpp::List res( n_col + 2 );  // MATRIX_ID + LIST_MAT_ID
    Rcpp::NumericVector id_column = Rcpp::rep( id, n_row );
    ++id;

    res[ 0 ] = id_column;
    res[ 1 ] = id_column;
    for( i = 0; i < n_col; ++i ) {
      res[ i + 2 ] = sfg( Rcpp::_, i );
    }

    return res;
  }

  // e.g. polygon to polygon
  inline Rcpp::List listMat_to_listMat( Rcpp::List& sfg, R_xlen_t& sfg_rows, double& id ) {
    // each internal matrix needs an id
    R_xlen_t n = sfg.size();
    R_xlen_t i;
    Rcpp::List res( n );
    R_xlen_t total_rows = 0;
    for( i = 0; i < n; ++i ) {
      Rcpp::NumericMatrix nm = sfg[ i ];
      R_xlen_t n_row = nm.nrow();
      total_rows = total_rows + n_row;
      res[ i ] = sfheaders::df::matrix_to_list( nm, n_row, id );
      ++id;
    }
    sfg_rows = total_rows;
    return sfheaders::df::collapse_list( res, total_rows );

  }

  // don't call other cast functions inside any other cast function
  // this way I can control when & where the 'id' is placed?
  inline Rcpp::List listListMat_to_listMat( Rcpp::List& sfg, R_xlen_t& sfg_rows, double& id ) {
    R_xlen_t n = sfg.size();
    R_xlen_t i;
    Rcpp::List res( n );
    R_xlen_t total_rows = 0;
    for( i = 0; i < n; ++i ) {
      Rcpp::List inner_list = sfg[ i ];
      R_xlen_t inner_n = inner_list.size();
      R_xlen_t inner_total_rows = 0;
      // the id shouldn't be incremented for each internal ring of each polygon
      // They should all be under the same id and only increment each time we get a new
      // polygon (inside the nultipolygon)
      res[ i ] = listMat_to_listMat( inner_list, inner_total_rows, id );
      total_rows = total_rows + inner_total_rows;
    }
    sfg_rows = total_rows;
    return sfheaders::df::collapse_list( res, total_rows );
  }

  // e.g. polygon to multipolygon
  inline Rcpp::List listMat_to_listListMat( Rcpp::List& sfg, double& id ) {
    // give each internal matrix the same id
    // and an extra 'id' column to denote the multipolygon_id
    // and return a even nested list?
    // then use 'collapse_list
  }




inline Rcpp::List setup_result( R_xlen_t& total_coordinates ) {

  Rcpp::NumericVector sfc_id_res( total_coordinates, Rcpp::NumericVector::get_na() );
  Rcpp::NumericVector sfg_id_res( total_coordinates, Rcpp::NumericVector::get_na() );
  Rcpp::NumericVector list_list_matrix_id( total_coordinates, Rcpp::NumericVector::get_na() );
  Rcpp::NumericVector list_matrix_id( total_coordinates, Rcpp::NumericVector::get_na() );
  Rcpp::NumericVector matrix_id( total_coordinates, Rcpp::NumericVector::get_na() );
  Rcpp::NumericVector x_res( total_coordinates, Rcpp::NumericVector::get_na() );
  Rcpp::NumericVector y_res( total_coordinates, Rcpp::NumericVector::get_na() );
  Rcpp::NumericVector m_res( total_coordinates, Rcpp::NumericVector::get_na() );
  Rcpp::NumericVector z_res( total_coordinates, Rcpp::NumericVector::get_na() );

  Rcpp::List res = Rcpp::List::create(
    Rcpp::_["sfc_id"] = sfc_id_res,
    Rcpp::_["sfg_id"] = sfg_id_res,
    Rcpp::_["list_list_matrix_id"] = list_list_matrix_id,
    Rcpp::_["list_matrix_id"] = list_matrix_id,
    Rcpp::_["matrix_id"] = matrix_id,
    Rcpp::_["x"] = x_res,
    Rcpp::_["y"] = y_res,
    Rcpp::_["z"] = z_res,
    Rcpp::_["m"] = m_res
  );
  return res;
}

inline void dim_error() { // #nocov
  Rcpp::stop("sfheaders - unknown geometry dimension");    // #nocov
}

inline Rcpp::IntegerVector get_sfg_cols( R_xlen_t& n_col, int geometry, std::string& dim ) {

  switch( geometry ) {
  case SFG_POINT: {
    if( dim == "XY" ) {
    return Rcpp::IntegerVector({ VECTOR_ID, X_COLUMN_CAST, Y_COLUMN_CAST });
  } else if( dim == "XYZM" ) {
    return Rcpp::IntegerVector({ VECTOR_ID, X_COLUMN_CAST, Y_COLUMN_CAST, Z_COLUMN_CAST, M_COLUMN_CAST });
  } else if ( dim == "XYZ" ) {
    return Rcpp::IntegerVector({ VECTOR_ID, X_COLUMN_CAST, Y_COLUMN_CAST, Z_COLUMN_CAST });
  } else if ( dim == "XYM" ) {  // #nocov
    return Rcpp::IntegerVector({ VECTOR_ID, X_COLUMN_CAST, Y_COLUMN_CAST, M_COLUMN_CAST }); // #nocov
  } else {
    dim_error();  // #nocov
  }
  }
  case SFG_MULTIPOINT: {}
  case SFG_LINESTRING: {
    if( dim == "XY" ) {
    return Rcpp::IntegerVector({ X_COLUMN_CAST, Y_COLUMN_CAST });
  } else if( dim == "XYZM" ) {
    return Rcpp::IntegerVector({ X_COLUMN_CAST, Y_COLUMN_CAST, Z_COLUMN_CAST, M_COLUMN_CAST });
  } else if ( dim == "XYZ" ) {
    return Rcpp::IntegerVector({ X_COLUMN_CAST, Y_COLUMN_CAST, Z_COLUMN_CAST });
  } else if ( dim == "XYM" ) {  // #nocov
    return Rcpp::IntegerVector({ X_COLUMN_CAST, Y_COLUMN_CAST, M_COLUMN_CAST }); // #nocov
  } else {
    dim_error();  // #nocov
  }
  }
  case SFG_MULTILINESTRING: {}
  case SFG_POLYGON: {
    if( dim == "XY" ) {
    return Rcpp::IntegerVector({ MATRIX_ID, X_COLUMN_CAST, Y_COLUMN_CAST });
  } else if( dim == "XYZM" ) {
    return Rcpp::IntegerVector({ MATRIX_ID, X_COLUMN_CAST, Y_COLUMN_CAST, Z_COLUMN_CAST, M_COLUMN_CAST });
  } else if ( dim == "XYZ" ) {
    return Rcpp::IntegerVector({ MATRIX_ID, X_COLUMN_CAST, Y_COLUMN_CAST, Z_COLUMN_CAST });
  } else if ( dim == "XYM" ) {  // #nocov
    return Rcpp::IntegerVector({ MATRIX_ID, X_COLUMN_CAST, Y_COLUMN_CAST, M_COLUMN_CAST });  // #nocov
  } else {
    dim_error();  // #nocov
  }
  }
  case SFG_MULTIPOLYGON: {
    if( dim == "XY" ) {
    return Rcpp::IntegerVector({ MATRIX_ID, LIST_MATRIX_ID, X_COLUMN_CAST, Y_COLUMN_CAST });
  } else if( dim == "XYZM" ) {
    return Rcpp::IntegerVector({ MATRIX_ID, LIST_MATRIX_ID, X_COLUMN_CAST, Y_COLUMN_CAST, Z_COLUMN_CAST, M_COLUMN_CAST });
  } else if ( dim == "XYZ" ) {
    return Rcpp::IntegerVector({ MATRIX_ID, LIST_MATRIX_ID, X_COLUMN_CAST, Y_COLUMN_CAST, Z_COLUMN_CAST });
  } else if ( dim == "XYM" ) {  // #nocov
    return Rcpp::IntegerVector({ MATRIX_ID, LIST_MATRIX_ID, X_COLUMN_CAST, Y_COLUMN_CAST, M_COLUMN });  // #nocov
  } else {
    dim_error(); // #nocov
  }

  }
  default: {
    Rcpp::stop("sfheaders - unknown geometry type");  // #nocov
  }
  }

  return Rcpp::IntegerVector(); // #nocov never reached
}

inline void sfg_n_coordinates(
    SEXP& sfg,
    R_xlen_t& sfg_count
) {

  switch( TYPEOF( sfg ) ) {
  case INTSXP: {}
  case REALSXP: {
    if( !Rf_isMatrix( sfg ) ) {
    //Rcpp::stop("sfheaders - unsupported coordinate type");
    // it's a vector, right?
    sfg_count += 1;
  } else {
    sfg_count += sfheaders::utils::sexp_n_row( sfg );
  }
  break;
  }
  case VECSXP: {
    if( Rf_inherits( sfg, "data.frame" ) ) {
    Rcpp::stop("sfheaders - unsupported coordinate type");  // #nocov
  }
    Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
    //if (lst.size() == 0 ) {
    //return 0; // ?
    //}
    R_xlen_t n = lst.size();
    R_xlen_t i;
    Rcpp::IntegerVector res( n );
    for( i = 0; i < n; ++i ) {
      SEXP tmp_sfg = lst[i];
      sfg_n_coordinates( tmp_sfg, sfg_count );  // recurse
    }
    break;
  }
  default: {
    Rcpp::stop("sfheaders - unsupported coordinate type");  // #nocov
  }
  }

  //return sfg_count;
}

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
inline



inline int get_sfg_column_index( std::string& sfg ) {
  if( sfg == "POINT" ) {
    return MATRIX_ID;
  } else if ( sfg == "MULTIPOINT" ) {
    return MATRIX_ID;
  } else if ( sfg == "LINESTRING" ) {
    return MATRIX_ID;
  } else if ( sfg == "MULTILINESTRING" ) {
    return LIST_MATRIX_ID;
  } else if ( sfg == "POLYGON" ) {
    return LIST_MATRIX_ID;
  } else if ( sfg == "MULTIPOLYGON" ) {
    return LIST_LIST_MATRIX_ID;
  } else {
    Rcpp::stop("sfheaders - unknown sfg type");  // #nocov
  }
}

inline Rcpp::List get_sfc_coordinates( Rcpp::List& sfc, R_xlen_t& total_coordinates ) {

  Rcpp::LogicalVector columns( MAX_COLUMNS_CAST ); // keeping track of which to subset
  columns[ X_COLUMN_CAST ] = true;
  columns[ Y_COLUMN_CAST ] = true;
  columns[ SFG_COLUMN_CAST ] = true;
  columns[ MATRIX_ID ] = true;
  columns[ LIST_MATRIX_ID ] = true;
  columns[ LIST_LIST_MATRIX_ID ] = true;

  R_xlen_t n_sfg = sfc.size();
  R_xlen_t i;
  R_xlen_t j;
  R_xlen_t n_col;

  Rcpp::CharacterVector cls;
  std::string dim;
  std::string sfg_class;
  int sfg_type;
  int sfg_column_idx;

  R_xlen_t sfc_rows = 0;
  R_xlen_t total_rows = 0;

  double id;

  Rcpp::List res = setup_result( total_coordinates );

  for( i = 0; i < n_sfg; ++i ) {

    SEXP sfci = sfc[ i ];

    cls = sfheaders::utils::getSfgClass( sfci );

    dim = cls[0];

    if( dim == "XYZ" ) {
      columns[ Z_COLUMN ] = true;
    } else if ( dim == "XYZM" ) {
      columns[ M_COLUMN ] = true;
    }

    sfg_class = cls[1];
    sfg_type = sfheaders::df::get_sfg_type( sfg_class );
    //sfg_column_idx = get_sfg_column_index( sfg_class );
    //columns[ sfg_column_idx ] = true;

    Rcpp::List sfg = sfheaders::df::get_sfg_coordinates( sfci, sfc_rows, sfg_type );

    n_col = sfg.size();

    Rcpp::IntegerVector sfg_cols = get_sfg_cols( n_col, sfg_type, dim );
    column_index_check( sfg_cols, n_col );

    for( j = 0; j < n_col; ++j ) {

      Rcpp::NumericVector new_values_vector = sfg[ j ];
      int col_idx = sfg_cols[ j ];
      columns[ col_idx ] = true;
      Rcpp::NumericVector current_values_vector = res[ col_idx ];
      Rcpp::NumericVector result_vector = sfheaders::utils::fill_vector( current_values_vector, new_values_vector, total_rows );
      res[ col_idx ] = result_vector;
    }

    id = i + 1;
    Rcpp::NumericVector new_id_vector = Rcpp::rep( id, sfc_rows );
    Rcpp::NumericVector current_id_vector = res[ SFG_COLUMN_CAST ];
    Rcpp::NumericVector filled = sfheaders::utils::fill_vector( current_id_vector, new_id_vector, total_rows );
    res[ SFG_COLUMN_CAST ] = filled;

    Rcpp::NumericVector current_sfg_id_vector = res[ SFC_COLUMN_CAST ];
    filled = sfheaders::utils::fill_vector( current_sfg_id_vector, new_id_vector, total_rows );

    res[ SFC_COLUMN_CAST ] = filled;

    total_rows = total_rows + sfc_rows;
  }

  //Rcpp::Rcout << "columns: " << columns << std::endl;

  // make data.frame
  res = res[ columns ];
  res.attr("class") = Rcpp::CharacterVector("data.frame");

  if( total_coordinates > 0 ) {
    Rcpp::IntegerVector rownames = Rcpp::seq( 1, total_coordinates );
    res.attr("row.names") = rownames;
  } else {
    res.attr("row.names") = Rcpp::IntegerVector(0);  // #nocov
  }

  res.attr("names") = column_names[ columns ];
  return res;
}

inline Rcpp::List sfc_to_cast_df(
    Rcpp::List& sfc,
    Rcpp::NumericMatrix& sfc_coordinates
) {
  R_xlen_t n_geometries = sfc_coordinates.nrow();
  R_xlen_t total_coordinates = sfc_coordinates( n_geometries - 1 , 1 );
  total_coordinates = total_coordinates + 1;

  return get_sfc_coordinates( sfc, total_coordinates );
}

inline Rcpp::List sfc_to_cast_df( Rcpp::List& sfc ) {
  // seprated this so it's independant / not called twice from `sf_to_df()`
  Rcpp::NumericMatrix sfc_coordinates = sfheaders::df::sfc_n_coordinates( sfc );
  return sfc_to_cast_df( sfc, sfc_coordinates );
}


} // cast
} // sfheaders


#endif
