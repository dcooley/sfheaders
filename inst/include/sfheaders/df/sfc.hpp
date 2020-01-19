#ifndef R_SFHEADERS_DF_SFC_H
#define R_SFHEADERS_DF_SFC_H

#include "sfheaders/df/sfg.hpp"
#include "sfheaders/df/utils.hpp"

#include <Rcpp.h>

namespace sfheaders {
namespace df {

  inline void column_index_check( Rcpp::IntegerVector& sfg_cols, R_xlen_t& n_col ) {
    if( sfg_cols.length() != n_col ) {
      Rcpp::stop("sfheaders - column indexing error - please report this issue, along with an example, at github.com/dcooley/sfheaders");  // #nocov
    }
  }
  inline Rcpp::List setup_result( R_xlen_t& total_coordinates ) {

    Rcpp::NumericVector sfc_id_res( total_coordinates, Rcpp::NumericVector::get_na() );
    Rcpp::NumericVector sfg_id_res( total_coordinates, Rcpp::NumericVector::get_na() );
    Rcpp::NumericVector geometrycollection_id_res( total_coordinates, Rcpp::NumericVector::get_na() );
    Rcpp::NumericVector multipolygon_id_res( total_coordinates, Rcpp::NumericVector::get_na() );
    Rcpp::NumericVector polygon_id_res( total_coordinates, Rcpp::NumericVector::get_na() );
    Rcpp::NumericVector multilinestring_id_res( total_coordinates, Rcpp::NumericVector::get_na() );
    Rcpp::NumericVector linestring_id_res( total_coordinates, Rcpp::NumericVector::get_na() );
    Rcpp::NumericVector multipoint_id_res( total_coordinates, Rcpp::NumericVector::get_na() );
    Rcpp::NumericVector point_id_res( total_coordinates, Rcpp::NumericVector::get_na() );
    Rcpp::NumericVector x_res( total_coordinates, Rcpp::NumericVector::get_na() );
    Rcpp::NumericVector y_res( total_coordinates, Rcpp::NumericVector::get_na() );
    Rcpp::NumericVector m_res( total_coordinates, Rcpp::NumericVector::get_na() );
    Rcpp::NumericVector z_res( total_coordinates, Rcpp::NumericVector::get_na() );

    Rcpp::List res = Rcpp::List::create(
      Rcpp::_["sfc_id"] = sfc_id_res,
      Rcpp::_["sfg_id"] = sfg_id_res,
      Rcpp::_["geometrycollection_id"] = geometrycollection_id_res,
      Rcpp::_["multipolygon_id"] = multipolygon_id_res,
      Rcpp::_["polygon_id"] = polygon_id_res,
      Rcpp::_["multilinestring_id"] = multilinestring_id_res,
      Rcpp::_["linestring_id"] = linestring_id_res,
      Rcpp::_["multipoint_id"] = multipoint_id_res,
      Rcpp::_["point_id"] = point_id_res,
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
      return Rcpp::IntegerVector({ X_COLUMN, Y_COLUMN });
    } else if( dim == "XYZM" ) {
      return Rcpp::IntegerVector({ X_COLUMN, Y_COLUMN, Z_COLUMN, M_COLUMN });
    } else if ( dim == "XYZ" ) {
      return Rcpp::IntegerVector({ X_COLUMN, Y_COLUMN, Z_COLUMN });
    } else if ( dim == "XYM" ) {  // #nocov
      return Rcpp::IntegerVector({ X_COLUMN, Y_COLUMN, M_COLUMN });  // #nocov
    } else {
      dim_error(); // #nocov
    }
    }
    case SFG_MULTIPOINT: {
      if( dim == "XY" ) {
      return Rcpp::IntegerVector({ X_COLUMN, Y_COLUMN });
    } else if( dim == "XYZM" ) {
      return Rcpp::IntegerVector({ X_COLUMN, Y_COLUMN, Z_COLUMN, M_COLUMN });
    } else if ( dim == "XYZ" ) {
      return Rcpp::IntegerVector({ X_COLUMN, Y_COLUMN, Z_COLUMN });
    } else if ( dim == "XYM" ) {  // #nocov
      return Rcpp::IntegerVector({ X_COLUMN, Y_COLUMN, M_COLUMN });    // #nocov
    } else {
      dim_error(); // #nocov
    }
    }
    case SFG_LINESTRING: {
      if( dim == "XY" ) {
      return Rcpp::IntegerVector({ X_COLUMN, Y_COLUMN });
    } else if( dim == "XYZM" ) {
      return Rcpp::IntegerVector({ X_COLUMN, Y_COLUMN, Z_COLUMN, M_COLUMN });
    } else if ( dim == "XYZ" ) {
      return Rcpp::IntegerVector({ X_COLUMN, Y_COLUMN, Z_COLUMN });
    } else if ( dim == "XYM" ) {  // #nocov
      return Rcpp::IntegerVector({ X_COLUMN, Y_COLUMN, M_COLUMN }); // #nocov
    } else {
      dim_error();  // #nocov
    }
    }
    case SFG_MULTILINESTRING: {
      if( dim == "XY" ) {
      return Rcpp::IntegerVector({ LINESTRING_COLUMN, X_COLUMN, Y_COLUMN });
    } else if( dim == "XYZM" ) {
      return Rcpp::IntegerVector({ LINESTRING_COLUMN, X_COLUMN, Y_COLUMN, Z_COLUMN, M_COLUMN });
    } else if ( dim == "XYZ" ) {
      return Rcpp::IntegerVector({ LINESTRING_COLUMN, X_COLUMN, Y_COLUMN, Z_COLUMN });
    } else if ( dim == "XYM" ) {  // #nocov
      return Rcpp::IntegerVector({ LINESTRING_COLUMN, X_COLUMN, Y_COLUMN, M_COLUMN });  // #nocov
    } else {
      dim_error();  // #nocov
    }
    }
    case SFG_POLYGON: {
      if( dim == "XY" ) {
      return Rcpp::IntegerVector({ LINESTRING_COLUMN, X_COLUMN, Y_COLUMN });
    } else if( dim == "XYZM" ) {
      return Rcpp::IntegerVector({ LINESTRING_COLUMN, X_COLUMN, Y_COLUMN, Z_COLUMN, M_COLUMN });
    } else if ( dim == "XYZ" ) {
      return Rcpp::IntegerVector({ LINESTRING_COLUMN, X_COLUMN, Y_COLUMN, Z_COLUMN });
    } else if ( dim == "XYM" ) {  // #nocov
      return Rcpp::IntegerVector({ LINESTRING_COLUMN, X_COLUMN, Y_COLUMN, M_COLUMN });  // #nocov
    } else {
      dim_error();  // #nocov
    }
    }
    case SFG_MULTIPOLYGON: {
      if( dim == "XY" ) {
      return Rcpp::IntegerVector({ LINESTRING_COLUMN, POLYGON_COLUMN, X_COLUMN, Y_COLUMN });
    } else if( dim == "XYZM" ) {
      return Rcpp::IntegerVector({ LINESTRING_COLUMN, POLYGON_COLUMN, X_COLUMN, Y_COLUMN, Z_COLUMN, M_COLUMN });
    } else if ( dim == "XYZ" ) {
      return Rcpp::IntegerVector({ LINESTRING_COLUMN, POLYGON_COLUMN, X_COLUMN, Y_COLUMN, Z_COLUMN });
    } else if ( dim == "XYM" ) {  // #nocov
      return Rcpp::IntegerVector({ LINESTRING_COLUMN, POLYGON_COLUMN, X_COLUMN, Y_COLUMN, M_COLUMN });  // #nocov
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
  inline Rcpp::NumericMatrix sfc_n_coordinates(
      Rcpp::List& sfc
  ) {

    R_xlen_t cumulative_coords = 0;
    R_xlen_t n = sfc.size();
    Rcpp::NumericMatrix res( n, 2 );
    R_xlen_t i;

    for( i = 0; i < n; ++i ) {
      R_xlen_t sfg_counter = 0;
      SEXP sfg = sfc[i];
      sfg_n_coordinates( sfg, sfg_counter );

      res( i, 0 ) = cumulative_coords;
      cumulative_coords += sfg_counter;
      res( i, 1 ) = cumulative_coords - 1;
    }
    return res;
  }

  // sfcs are a list of sfgs.
  // they can be mixed, or individual.
  // if indiidual, loop over each one and extract the sfgs, list by list, then collapse the lists??

  inline Rcpp::List get_sfg_coordinates( SEXP& sfg, R_xlen_t& sfc_rows, int SFG_TYPE ) {

    switch( SFG_TYPE ) {
    case SFG_POINT: {
      Rcpp::NumericVector vec = Rcpp::as< Rcpp::NumericVector >( sfg );
      return sfheaders::df::sfg_point_coordinates( vec, sfc_rows );
    }
    case SFG_MULTIPOINT: {
      Rcpp::NumericMatrix mat = Rcpp::as< Rcpp::NumericMatrix >( sfg );
      return sfheaders::df::sfg_multipoint_coordinates( mat, sfc_rows );
    }
    case SFG_LINESTRING: {
      Rcpp::NumericMatrix mat = Rcpp::as< Rcpp::NumericMatrix >( sfg );
      return sfheaders::df::sfg_linestring_coordinates( mat, sfc_rows );
    }
    case SFG_MULTILINESTRING: {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      return sfheaders::df::sfg_multilinestring_coordinates( lst, sfc_rows );
    }
    case SFG_POLYGON: {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      return sfheaders::df::sfg_polygon_coordinates( lst, sfc_rows );
    }
    case SFG_MULTIPOLYGON: {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      return sfheaders::df::sfg_multipolygon_coordinates( lst, sfc_rows );
    }
    default: {
      Rcpp::stop("sfheaders - unknown sfg type");  // #nocov
    }
    }
    return Rcpp::List::create(); // #nocov never reaches
  }

  inline int get_sfg_type( std::string& sfg ) {
    if( sfg == "POINT" ) {
      return SFG_POINT;
    } else if ( sfg == "MULTIPOINT" ) {
      return SFG_MULTIPOINT;
    } else if ( sfg == "LINESTRING" ) {
      return SFG_LINESTRING;
    } else if ( sfg == "MULTILINESTRING" ) {
      return SFG_MULTILINESTRING;
    } else if ( sfg == "POLYGON" ) {
      return SFG_POLYGON;
    } else if ( sfg == "MULTIPOLYGON" ) {
      return SFG_MULTIPOLYGON;
    } else {
      Rcpp::stop("sfheaders - unknown sfg type");  // #nocov
    }
  }

  inline int get_sfg_column_index( std::string& sfg ) {
    if( sfg == "POINT" ) {
      return POINT_COLUMN;
    } else if ( sfg == "MULTIPOINT" ) {
      return MULTIPOINT_COLUMN;
    } else if ( sfg == "LINESTRING" ) {
      return LINESTRING_COLUMN;
    } else if ( sfg == "MULTILINESTRING" ) {
      return MULTILINESTRING_COLUMN;
    } else if ( sfg == "POLYGON" ) {
      return POLYGON_COLUMN;
    } else if ( sfg == "MULTIPOLYGON" ) {
      return MULTIPOLYGON_COLUMN;
    } else {
      Rcpp::stop("sfheaders - unknown sfg type");  // #nocov
    }
  }

  inline Rcpp::List get_sfc_coordinates( Rcpp::List& sfc, R_xlen_t& total_coordinates ) {

    Rcpp::LogicalVector columns( MAX_COLUMNS ); // keeping track of which to subset
    columns[ X_COLUMN ] = true;
    columns[ Y_COLUMN ] = true;
    columns[ SFG_COLUMN ] = true;

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

      cls = sfheaders::df::getSfgClass( sfci );

      dim = cls[0];

      if( dim == "XYZ" ) {
        columns[ Z_COLUMN ] = true;
      } else if ( dim == "XYZM" ) {
        columns[ M_COLUMN ] = true;
      }

      sfg_class = cls[1];
      sfg_type = get_sfg_type( sfg_class );
      sfg_column_idx = get_sfg_column_index( sfg_class );
      columns[ sfg_column_idx ] = true;

      Rcpp::List sfg = get_sfg_coordinates( sfci, sfc_rows, sfg_type );

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
      Rcpp::NumericVector current_id_vector = res[ sfg_column_idx ];
      Rcpp::NumericVector filled = sfheaders::utils::fill_vector( current_id_vector, new_id_vector, total_rows );
      res[ sfg_column_idx ] = filled;

      Rcpp::NumericVector current_sfg_id_vector = res[ SFG_COLUMN ];
      filled = sfheaders::utils::fill_vector( current_sfg_id_vector, new_id_vector, total_rows );

      res[ SFG_COLUMN ] = filled;

      total_rows = total_rows + sfc_rows;
    }

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

  inline Rcpp::List sfc_to_df( Rcpp::List& sfc ) {

    // seprated this so it's independant / not called twice from `sf_to_df()`
    Rcpp::NumericMatrix sfc_coordinates = sfc_n_coordinates( sfc );

    R_xlen_t n_geometries = sfc_coordinates.nrow();
    R_xlen_t total_coordinates = sfc_coordinates( n_geometries - 1 , 1 );
    total_coordinates = total_coordinates + 1;

    return get_sfc_coordinates( sfc, total_coordinates );
  }


} // df
} // sfheaders


#endif
