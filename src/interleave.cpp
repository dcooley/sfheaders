#include <Rcpp.h>
#include "sfheaders/df/sfc.hpp"
#include "sfheaders/interleave/interleave.hpp"


void interleave_geometry(SEXP& sfg, Rcpp::NumericVector& res, R_xlen_t& coordinate_counter ) {

}

// [[Rcpp::export]]
SEXP rcpp_interleave( Rcpp::List sfc ) {

  // the input will be a long data.frame
  // or an sf object
  // if it's a data.frame, it needs id columns and geometry columns
  // can probably do this one later?
  // and focus on the 'sf', because it doesn't need any extra headers / thought / logic

  Rcpp::NumericMatrix sfc_coordinates = sfheaders::df::sfc_n_coordinates( sfc );
  Rcpp::Rcout << "sfc_coordinates: " << sfc_coordinates << std::endl;

  //return sfc_coordinates;

  // the STRIDE depends on the dimension being the same for every pair of coordinates


  Rcpp::CharacterVector cls;
  std::string dim_expected;
  std::string dim;

  R_xlen_t n = sfc.length();
  R_xlen_t i;
  Rcpp::IntegerVector n_coordinates( n );
  R_xlen_t sfg_count = 0;   // move outside loop so it's cumulative

  for( i = 0; i < n; ++i ) {
    SEXP sfg = sfc[ i ];

    cls = sfheaders::utils::getSfgClass( sfg );
    if( i == 0 ) {
      dim_expected = cls[0];
    } else {
      dim = cls[0];
      if ( dim != dim_expected ) {
        Rcpp::stop("sfheaders - interleaving only works when all geometries have the same dimension (XY(Z(M)))");
      }
    }
    n_coordinates[ i ] = sfg_count;
    sfheaders::df::sfg_n_coordinates( sfg, sfg_count );
  }
  // the last iteration gives the total number of coordinates
  // which will be the length of the vector (* stride (dim) );
  Rcpp::Rcout << "total coordinates: " << sfg_count << std::endl;

  int stride = ( dim_expected == "XYZ" || dim_expected == "XYM" ? 3 : ( dim_expected == "XYZM" ? 4 : 2 )  );
  R_xlen_t total_coordinates = sfg_count * stride;
  Rcpp::NumericVector res( total_coordinates );
  R_xlen_t coordinate_counter = 0;
  Rcpp::List res_list( sfc.size() );
  Rcpp::List res_indices( sfc.size() );

  //R_xlen_t total_coordinates = 0;

  // now fill this vector with all the coorinates from the coordinates
  for( i = 0; i < n; ++i ) {
    SEXP sfg = sfc[ i ];

    Rcpp::NumericMatrix coords = sfheaders::df::sfg_n_coordinates( sfg );
    Rcpp::Rcout << "sfg_coordinates: " << coords << std::endl;
    R_xlen_t n_geometries = coords.nrow();
    R_xlen_t n_coordinates = coords( n_geometries - 1, 1 );
    n_coordinates = n_coordinates + 1;
    Rcpp::NumericVector start_indices = coords( Rcpp::_, 0 );
    start_indices = start_indices + coordinate_counter;
    res_indices[ i ] = start_indices;
    coordinate_counter = coordinate_counter + n_coordinates;

    // and do I need to account for stride?
    // i.e., does Deck.GL think the start index is for the number of PAIRS, or individual coordinates?

    // and the start_indices need to be cumulatively_summed

     // depending on the GEOMETRY
     // get each coordinate
     // do I iterate each row?
     // Rcpp::NumericVector interleaved = sfheaders::interleave::interleave( sfg );
     // sfheaders::utils::fill_vector( res, interleaved, coordinate_counter );
     // coordinate_counter = coordinate_counter + interleaved.length();

     //sfheaders::df::sfg_n_coordinates( sfg, coordinate_counter );
     //Rcpp::Rcout << "sfg_coordinates " << coordinate_counter << std::endl;

     res_list[ i ] = sfheaders::interleave::interleave( sfg );
     // this interleaved can be a vector, or a list of vectors

     // Need to keep a list of start_indices for each sfg
  }

  return Rcpp::List::create(
    Rcpp::_["coordinates"] = res_list,
    Rcpp::_["start_indices"] = res_indices
  );

  //return res_list;
}


