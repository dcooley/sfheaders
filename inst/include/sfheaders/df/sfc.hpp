#ifndef R_SFHEADERS_DF_SFC_H
#define R_SFHEADERS_DF_SFC_H

#include "sfheaders/df/sfg.hpp"
#include "sfheaders/df/utils.hpp"

#include <Rcpp.h>

namespace sfheaders {
namespace df {

  inline void column_index_check( Rcpp::IntegerVector& sfg_cols, R_xlen_t& n_col ) {
    if( sfg_cols.length() != n_col ) {
      Rcpp::stop("sfheaders - column indexing error - please report this issue at github.com/dcooley/sfheaders");
    }
  }
  inline Rcpp::List setup_result( R_xlen_t& total_coordinates ) {

    Rcpp::NumericVector sfc_id_res( total_coordinates, Rcpp::NumericVector::get_na() );
    Rcpp::NumericVector sfg_id_res( total_coordinates, Rcpp::NumericVector::get_na() );
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

  inline void dim_error() {
    Rcpp::stop("sfheaders - unknown geometry dimension");
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
    } else if ( dim == "XYM" ) {
      return Rcpp::IntegerVector({ X_COLUMN, Y_COLUMN, M_COLUMN });
    } else {
      dim_error();
    }
    }
    case SFG_MULTIPOINT: {
      if( dim == "XY" ) {
      return Rcpp::IntegerVector({ X_COLUMN, Y_COLUMN });
    } else if( dim == "XYZM" ) {
      return Rcpp::IntegerVector({ X_COLUMN, Y_COLUMN, Z_COLUMN, M_COLUMN });
    } else if ( dim == "XYZ" ) {
      return Rcpp::IntegerVector({ X_COLUMN, Y_COLUMN, Z_COLUMN });
    } else if ( dim == "XYM" ) {
      return Rcpp::IntegerVector({ X_COLUMN, Y_COLUMN, M_COLUMN });
    } else {
      dim_error();
    }
    }
    case SFG_LINESTRING: {
      if( dim == "XY" ) {
      return Rcpp::IntegerVector({ X_COLUMN, Y_COLUMN });
    } else if( dim == "XYZM" ) {
      return Rcpp::IntegerVector({ X_COLUMN, Y_COLUMN, Z_COLUMN, M_COLUMN });
    } else if ( dim == "XYZ" ) {
      return Rcpp::IntegerVector({ X_COLUMN, Y_COLUMN, Z_COLUMN });
    } else if ( dim == "XYM" ) {
      return Rcpp::IntegerVector({ X_COLUMN, Y_COLUMN, M_COLUMN });
    } else {
      dim_error();
    }
    }
    case SFG_MULTILINESTRING: {
      if( dim == "XY" ) {
      return Rcpp::IntegerVector({ LINESTRING_COLUMN, X_COLUMN, Y_COLUMN });
    } else if( dim == "XYZM" ) {
      return Rcpp::IntegerVector({ LINESTRING_COLUMN, X_COLUMN, Y_COLUMN, Z_COLUMN, M_COLUMN });
    } else if ( dim == "XYZ" ) {
      return Rcpp::IntegerVector({ LINESTRING_COLUMN, X_COLUMN, Y_COLUMN, Z_COLUMN });
    } else if ( dim == "XYM" ) {
      return Rcpp::IntegerVector({ LINESTRING_COLUMN, X_COLUMN, Y_COLUMN, M_COLUMN });
    } else {
      dim_error();
    }
    }
    case SFG_POLYGON: {
      if( dim == "XY" ) {
      return Rcpp::IntegerVector({ LINESTRING_COLUMN, X_COLUMN, Y_COLUMN });
    } else if( dim == "XYZM" ) {
      return Rcpp::IntegerVector({ LINESTRING_COLUMN, X_COLUMN, Y_COLUMN, Z_COLUMN, M_COLUMN });
    } else if ( dim == "XYZ" ) {
      return Rcpp::IntegerVector({ LINESTRING_COLUMN, X_COLUMN, Y_COLUMN, Z_COLUMN });
    } else if ( dim == "XYM" ) {
      return Rcpp::IntegerVector({ LINESTRING_COLUMN, X_COLUMN, Y_COLUMN, M_COLUMN });
    } else {
      dim_error();
    }
    }
    case SFG_MULTIPOLYGON: {
      if( dim == "XY" ) {
      return Rcpp::IntegerVector({ LINESTRING_COLUMN, POLYGON_COLUMN, X_COLUMN, Y_COLUMN });
    } else if( dim == "XYZM" ) {
      return Rcpp::IntegerVector({ LINESTRING_COLUMN, POLYGON_COLUMN, X_COLUMN, Y_COLUMN, Z_COLUMN, M_COLUMN });
    } else if ( dim == "XYZ" ) {
      return Rcpp::IntegerVector({ LINESTRING_COLUMN, POLYGON_COLUMN, X_COLUMN, Y_COLUMN, Z_COLUMN });
    } else if ( dim == "XYM" ) {
      return Rcpp::IntegerVector({ LINESTRING_COLUMN, POLYGON_COLUMN, X_COLUMN, Y_COLUMN, M_COLUMN });
    } else {
      dim_error();
    }

    }
    default: {
      Rcpp::stop("sfheaders - unknown geometry type");
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
        Rcpp::stop("sfheaders - unsupported coordinate type");
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
      Rcpp::stop("sfheaders - unsupported coordinate type");
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

  Rcpp::List get_sfg_coordinates( SEXP& sfg, R_xlen_t& sfc_rows, int SFG_TYPE ) {
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
      Rcpp::stop("sfheaders - unknown sfg type");
    }
    }
    return Rcpp::List::create(); // #nocov never reaches
  }

  // inline void x() {
  //   R_xlen_t n_sfg = sfc.size();
  //   R_xlen_t i;
  //   R_xlen_t j;
  //   R_xlen_t n_col;
  //   Rcpp::List sfgs( n_sfg );
  //   R_xlen_t sfc_rows = 0;
  //   R_xlen_t total_rows = 0;
  //
  //   Rcpp::CharacterVector cls;
  //   std::string dim;
  //
  //   Rcpp::NumericMatrix sfc_coordinates = sfc_n_coordinates( sfc );
  //
  //   R_xlen_t n_geometries = sfc_coordinates.nrow();
  //   R_xlen_t total_coordinates = sfc_coordinates( n_geometries - 1 , 1 );
  //
  //   Rcpp::List res = setup_result( total_coordinates );
  //
  //   for( i = 0; i < n_sfg; ++i ) {
  //     Rcpp::NumericVector vec = Rcpp::as< Rcpp::NumericVector >( sfc[ i ] );
  //
  //     Rcpp::List sfg = sfheaders::df::sfg_point_coordinates( vec, sfc_rows );
  //     cls = sfg.attr("sfg_class");
  //     dim = cls[0];
  //
  //     n_col = sfg.size();
  //
  //     Rcpp::IntegerVector sfg_cols = get_sfg_cols( n_col, SFG_POINT, dim );
  //     column_index_check( sfg_cols, n_col );
  //
  //     for( j = 0; j < n_col; ++j ) {
  //       Rcpp::NumericVector col = sfg[ j ];
  //       Rcpp::NumericVector v = res[ j + 1 ];
  //       res[ j + 1 ] = sfheaders::utils::fill_vector( v, col, total_rows );
  //     }
  //
  //     double id = i + 1;
  //     Rcpp::NumericVector id_column = Rcpp::rep( id, sfc_rows );
  //     Rcpp::NumericVector id_to_fill = res[ SFG_POINT ];
  //
  //     res[ SFG_POINT ] = sfheaders::utils::fill_vector( id_to_fill, id_column, total_rows );
  //     total_rows = total_rows + sfc_rows;
  //   }
  // }

  inline Rcpp::List get_sfc_coordinates( Rcpp::List& sfc, int SFG_TYPE, int SFG_COLUMN_INDEX ) {
    R_xlen_t n_sfg = sfc.size();
    R_xlen_t i;
    R_xlen_t j;
    R_xlen_t k;
    R_xlen_t n_col;
    //Rcpp::List sfgs( n_sfg );
    R_xlen_t sfc_rows = 0;
    R_xlen_t total_rows = 0;

    double id;

    Rcpp::CharacterVector cls;
    std::string dim;

    Rcpp::NumericMatrix sfc_coordinates = sfc_n_coordinates( sfc );

    // Rcpp::Rcout << "sfc_coordinates: " << std::endl;
    // Rcpp::Rcout << sfc_coordinates << std::endl;

    R_xlen_t n_geometries = sfc_coordinates.nrow();
    // Rcpp::Rcout << "n_geometries: " << n_geometries << std::endl;
    R_xlen_t total_coordinates = sfc_coordinates( n_geometries - 1 , 1 );
    total_coordinates = total_coordinates + 1;

    // Rcpp::Rcout << "total_coordinates: " << total_coordinates << std::endl;
    Rcpp::List res = setup_result( total_coordinates );

    Rcpp::NumericVector result_vector;
    Rcpp::NumericVector current_values_vector;


    for( i = 0; i < n_sfg; ++i ) {
      // Rcpp::Rcout << "i: " << i << std::endl;

      // for( j = 0; j < res.size(); ++j ) {
      //   Rcpp::NumericVector nv = res[ j ];
      //   Rcpp::Rcout << "res[ " << j << " ]: " << nv << std::endl;
      // }

      SEXP sfci = sfc[ i ];
      Rcpp::List sfg = get_sfg_coordinates( sfci, sfc_rows, SFG_TYPE );

      // Rcpp::Rcout << "sfc_rows: " << sfc_rows << std::endl;

      // for( j = 0; j < sfg.size(); ++j ) {
      //   Rcpp::NumericVector nv = sfg[ j ];
      //   Rcpp::Rcout << "sfg[ " << j << " ]: " << nv << std::endl;
      // }

      cls = sfg.attr("sfg_class");
      dim = cls[0];

      n_col = sfg.size();

      Rcpp::IntegerVector sfg_cols = get_sfg_cols( n_col, SFG_TYPE, dim );
      // Rcpp::Rcout << "sfg_cols; " << sfg_cols << std::endl;
      // Rcpp::Rcout << "sfg_cols.length(): " << sfg_cols.length() << std::endl;
      //column_index_check( sfg_cols, n_col );

      for( j = 0; j < sfg_cols.length(); ++j ) {

        // Rcpp::Rcout << "j: " << j << std::endl;
        current_values_vector = sfg[ j ];
        // Rcpp::Rcout << "sfg_vector: " << sfg_vector << std::endl;
        int col_idx = sfg_cols[ j ];
        result_vector = res[ col_idx ];

        //Rcpp::Rcout << "result_vector: " << result_vector << std::endl;

        //Rcpp::NumericVector v = res[ col_idx ];
        // Rcpp::Rcout << "col_idx: " << col_idx << std::endl;
        // Rcpp::Rcout << "v: " << v << std::endl;
        //Rcpp::NumericVector v2 = sfheaders::utils::fill_vector( v, col, total_rows );
        //Rcpp::Rcout << "v2: " << v2 << std::endl;
        //R_xlen_t start_idx = total_rows - 1;
        //Rcpp::NumericVector filled_result = sfheaders::utils::fill_vector( result_vector, sfg_vector, total_rows );
        sfheaders::utils::fill_vector( result_vector, current_values_vector, total_rows );
        //res[ col_idx ] = filled_result;

        //res[ col_idx ] = sfheaders::utils::fill_vector( result_vector, sfg_vector, total_rows );

        // for( k = 0; k < res.size(); ++k ) {
        //   Rcpp::NumericVector nv = res[ k ];
        //   Rcpp::Rcout << "res[ " << k << " ]: " << nv << std::endl;
        // }

      }

      // for( j = 0; j < res.size(); ++j ) {
      //   Rcpp::NumericVector nv = res[ j ];
      //   Rcpp::Rcout << "res[ " << j << " ]: " << nv << std::endl;
      // }

      id = i + 1;
      result_vector = Rcpp::rep( id, sfc_rows );
      current_values_vector = res[ SFG_COLUMN_INDEX ];
      sfheaders::utils::fill_vector( current_values_vector, result_vector, total_rows );
      //Rcpp::Rcout << "id_to_fill: " << id_to_fill << std::endl;
      //Rcpp::Rcout << "id_to_fill_2: " <<  id_to_fill_2 << std::endl;
      //Rcpp::NumericVector id_to_fill_2 = sfheaders::utils::fill_vector( id_to_fill, id_column, total_rows );
      // Rcpp::Rcout << "id_to_fill: " << id_to_fill << std::endl;
      //Rcpp::Rcout << "id_to_fill_2: " <<  id_to_fill_2 << std::endl;
      // //res[ SFG_COLUMN_INDEX ] = id_to_fill_2;
      // Rcpp::Rcout << "SFG_COLUMN_INDEX: " << SFG_COLUMN_INDEX << std::endl;
      //res[ SFG_COLUMN_INDEX ] = sfheaders::utils::fill_vector( id_to_fill, id_column, total_rows );;

      total_rows = total_rows + sfc_rows;
    }
    return res;
  }

  inline Rcpp::List sfc_point_coordinates( Rcpp::List& sfc ) {
    return get_sfc_coordinates( sfc, SFG_POINT, POINT_COLUMN );
  }

  inline Rcpp::List sfc_multipoint_coordinates( Rcpp::List& sfc ) {
    return get_sfc_coordinates( sfc, SFG_MULTIPOINT, MULTIPOINT_COLUMN );
  }

  inline Rcpp::List sfc_linestring_coordinates( Rcpp::List& sfc ) {
    return get_sfc_coordinates( sfc, SFG_LINESTRING, LINESTRING_COLUMN );
  }

  inline Rcpp::List sfc_multilinestring_coordinates( Rcpp::List& sfc ) {
    return get_sfc_coordinates( sfc, SFG_MULTILINESTRING, MULTILINESTRING_COLUMN );
  }

  inline Rcpp::List sfc_polygon_coordinates( Rcpp::List& sfc ) {
    return get_sfc_coordinates( sfc, SFG_POLYGON, POLYGON_COLUMN );
  }

  inline Rcpp::List sfc_multipolygon_coordinates( Rcpp::List& sfc ) {
    return get_sfc_coordinates( sfc, SFG_MULTIPOLYGON, MULTIPOLYGON_COLUMN );
  }


  // inline Rcpp::List sfc_to_df( Rcpp::List& sfc ) {
  //
  //   R_xlen_t n = sfc.length();
  //
  //   Rcpp::NumericMatrix sfc_coordinates = sfc_n_coordinates( sfc );
  //
  //   R_xlen_t n_geometries = sfc_coordinates.nrow();
  //   R_xlen_t total_coordinates = sfc_coordinates( n_geometries - 1 , 1 );
  //
  //   Rcpp::List res = setup_result( total_coordinates );
  //
  //   Rcpp::LogicalVector columns( MAX_COLUMNS ); // keeping track of which to subset
  //   columns[ X_COLUMN ] = true;
  //   columns[ Y_COLUMN ] = true;
  //   columns[ SFG_COLUMN ] = true;
  //
  //   R_xlen_t i;
  //   double id;
  //   std::string dim;
  //
  //   for( i = 0; i < n; ++i ) {
  //     SEXP s = sfc[i];
  //     Rcpp::CharacterVector cls = sfheaders::df::getSfgClass( s );
  //     std::string sfc_type;
  //
  //     dim = cls[0];
  //     sfc_type = cls[1];
  //     id = i + 1;
  //
  //     if( dim == "XYZ" ) {
  //       columns[ Z_COLUMN ] = true;
  //     } else if ( dim == "XYZM" ) {
  //       columns[ M_COLUMN ] = true;
  //     }
  //
  //     if( sfc_type == "POINT" ) {
  //       Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( s );
  //       res[i] = sfg_point_coordinates( nv, id );
  //       columns[ POINT_COLUMN ] = true;
  //
  //     } else if ( sfc_type == "MULTIPOINT" ) {
  //       Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( s );
  //       res[i] = sfg_multipoint_coordinates( nm, id );
  //       columns[ MULTIPOINT_COLUMN ] = true;
  //
  //     } else if ( sfc_type == "LINESTRING" ) {
  //       Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( s );
  //       res[i] = sfg_linestring_coordinates( nm, id );
  //       columns[ LINESTRING_COLUMN ] = true;
  //
  //     } else if ( sfc_type == "MULTILINESTRING" ) {
  //       Rcpp::List l = Rcpp::as< Rcpp::List >( s );
  //       res[i] = sfg_multilinestring_coordinates( s, id );
  //       columns[ LINESTRING_COLUMN ] = true;
  //       columns[ MULTILINESTRING_COLUMN ] = true;
  //
  //     } else if ( sfc_type == "POLYGON" ) {
  //       Rcpp::List l = Rcpp::as< Rcpp::List >( s );
  //       res[i] = sfg_polygon_coordinates( l, id );
  //       columns[ LINESTRING_COLUMN ] = true;
  //       columns[ POLYGON_COLUMN ] = true;
  //
  //     } else if ( sfc_type == "MULTIPOLYGON" ) {
  //       Rcpp::List l = Rcpp::as< Rcpp::List >( s );
  //       res[i] = sfg_multipolygon_coordinates( l, id );
  //       columns[ LINESTRING_COLUMN ] = true;
  //       columns[ POLYGON_COLUMN ] = true;
  //       columns[ MULTIPOLYGON_COLUMN ] = true;
  //
  //     } else {
  //       Rcpp::stop("sfheaders - unknown sfc type");
  //     }
  //
  //
  //   }
  //
  //   return res;
  //
  // }


} // df
} // sfheaders


#endif
