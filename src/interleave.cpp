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

  //Rcpp::NumericMatrix sfc_coordinates = sfheaders::df::sfc_n_coordinates( sfc );

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
  // now fill this vector with all the coorinates from the coordinates
  for( i = 0; i < n; ++i ) {
    SEXP sfg = sfc[ i ];
     // depending on the GEOMETRY
     // get each coordinate
     // do I iterate each row?
     SEXP temp = sfheaders::interleave::interleave( sfg );
  }

  return res;
}


