#ifndef R_SFHEADERS_DF_SFC_H
#define R_SFHEADERS_DF_SFC_H

#include "sfheaders/df/sfg.hpp"
#include "sfheaders/df/utils.hpp"

#include <Rcpp.h>

namespace sfheaders {
namespace df {

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

    // first column is start_index
    // second column is end_index // cumulative_total
    // 4th column is the sfg type??
    // 5th column is the dim? (XYZM)

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
      //res( i, 1 ) = sfg_counter - 1;
    }
    return res;
  }

  // sfcs are a list of sfgs.
  // they can be mixed, or individual.
  // if indiidual, loop over each one and extract the sfgs, list by list, then collapse the lists??

  // inline Rcpp::NumericVector concatenate_coordinates( Rcpp::NumericVector& vec_1, Rcpp::NumericVector& vec_2 ) {
  //
  //   R_xlen_t n_1 = vec_1.length();
  //   R_xlen_t n_2 = vec_2.length();
  //   R_xlen_t n = n_1 + n_2;
  //   R_xlen_t i;
  //   Rcpp::NumericVector nv( n );
  //
  //   if( n_1 == 1 ) {
  //     nv[0] = vec_1[0];
  //   } else {
  //     for( i = 0; i < n_1; i++ ) {
  //       nv[i] = vec_1[i];
  //     }
  //   }
  //
  //   if( n_2 == 1 ) {
  //     nv[ n_1 ] = vec_2[0];
  //   } else {
  //     R_xlen_t idx = 0;
  //     for( i = n_1; i < n; i++ ) {
  //       nv[i] = vec_2[ idx ];
  //       idx++;
  //     }
  //   }
  //   return nv;
  // }

  inline Rcpp::List sfc_linestring_coordinates( Rcpp::List& sfc ) {

    R_xlen_t n_sfg = sfc.size();
    R_xlen_t i;
    R_xlen_t j;
    R_xlen_t n_col;
    Rcpp::List sfgs( n_sfg );
    R_xlen_t sfc_rows = 0;
    R_xlen_t total_rows = 0;

    Rcpp::NumericMatrix sfc_coordinates = sfc_n_coordinates( sfc );
    //Rcpp::Rcout << "sfc_n_coordinates: " << std::endl;
    //Rcpp::Rcout << sfc_coordinates << std::endl;

    // rather than collapsing the list, can I fill it directly as I go?
    R_xlen_t n_geometries = sfc_coordinates.nrow();
    R_xlen_t total_coordinates = sfc_coordinates( n_geometries - 1 , 1 );

    Rcpp::NumericVector linestring_id_res( total_coordinates, Rcpp::NumericVector::get_na() );
    Rcpp::NumericVector x_res( total_coordinates, Rcpp::NumericVector::get_na() );
    Rcpp::NumericVector y_res( total_coordinates, Rcpp::NumericVector::get_na() );
    Rcpp::NumericVector m_res( total_coordinates, Rcpp::NumericVector::get_na() );
    Rcpp::NumericVector z_res( total_coordinates, Rcpp::NumericVector::get_na() );

    // internal geometry id columns are created during teh sfg_coordinates step
    // now we need an id for each sfc geometry as well.
    Rcpp::List res = Rcpp::List::create(
      Rcpp::_["linestring_id"] = linestring_id_res,
      Rcpp::_["x"] = x_res,
      Rcpp::_["y"] = y_res,
      Rcpp::_["z"] = z_res,
      Rcpp::_["m"] = m_res
    );

    for( i = 0; i < n_sfg; ++i ) {
      Rcpp::NumericMatrix mat = Rcpp::as< Rcpp::NumericMatrix >( sfc[ i ] );
      //sfgs[ i ] = sfheaders::df::sfg_linestring_coordinates( mat, sfc_rows );

      Rcpp::List sfg = sfheaders::df::sfg_linestring_coordinates( mat, sfc_rows );
      n_col = sfg.size();

      for( j = 0; j < n_col; ++j ) {
        Rcpp::NumericVector col = sfg[ j ];
        Rcpp::NumericVector v = res[ j + 1 ];
        res[ j + 1 ] = sfheaders::utils::fill_vector( v, col, total_rows );
      }

      double id = i + 1;
      Rcpp::NumericVector id_column = Rcpp::rep( id, sfc_rows );
      Rcpp::NumericVector id_to_fill = res[ 0 ];

      res[ 0 ] = sfheaders::utils::fill_vector( id_to_fill, id_column, total_rows );
      total_rows = total_rows + sfc_rows;
    }

    //Rcpp::Rcout << "sfc_coordinates; " << total_coordinates << std::endl;
    return res;
    //return sfgs;
    //return sfheaders::df::collapse_list( sfgs, total_rows );
  }

} // df
} // sfheaders


#endif
