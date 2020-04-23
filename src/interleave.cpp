#include <Rcpp.h>
#include "sfheaders/df/sfc.hpp"
#include "sfheaders/interleave/interleave.hpp"


void interleave_geometry(SEXP& sfg, Rcpp::NumericVector& res, R_xlen_t& coordinate_counter ) {

}

// [[Rcpp::export]]
SEXP rcpp_interleave_sfc( Rcpp::List sfc ) {
  return sfheaders::interleave::interleave( sfc );
}

// [[Rcpp::export]]
SEXP rcpp_interleave_sf( Rcpp::DataFrame sf ) {
  return sfheaders::interleave::interleave( sf );
}

// SEXP rcpp_interleave( Rcpp::List sfc ) {
//
//   // the input will be a long data.frame
//   // or an sf object
//   // if it's a data.frame, it needs id columns and geometry columns
//   // can probably do this one later?
//   // and focus on the 'sf', because it doesn't need any extra headers / thought / logic
//
//   // the STRIDE depends on the dimension being the same for every pair of coordinates
//   Rcpp::CharacterVector cls;
//   std::string dim_expected;
//   std::string dim;
//
//   R_xlen_t n = sfc.length();
//   R_xlen_t i;
//
//   int stride = ( dim_expected == "XYZ" || dim_expected == "XYM" ? 3 : ( dim_expected == "XYZM" ? 4 : 2 ) );
//
//   R_xlen_t coordinate_counter = 0;
//   Rcpp::List res_list( sfc.size() );
//   Rcpp::List res_indices( sfc.size() );
//
//   for( i = 0; i < n; ++i ) {
//
//     SEXP sfg = sfc[ i ];
//
//     cls = sfheaders::utils::getSfgClass( sfg );
//     if( i == 0 ) {
//       dim_expected = cls[0];
//     } else {
//       dim = cls[0];
//       if ( dim != dim_expected ) {
//         Rcpp::stop("sfheaders - interleaving only works when all geometries have the same dimension (XY(Z(M)))");
//       }
//     }
//
//     Rcpp::IntegerMatrix coords = sfheaders::df::sfg_n_coordinates( sfg );
//
//     R_xlen_t n_geometries = coords.nrow();
//     R_xlen_t n_coordinates = coords( n_geometries - 1, 1 );
//     n_coordinates = n_coordinates + 1;
//     Rcpp::IntegerVector start_indices = coords( Rcpp::_, 0 );
//     start_indices = start_indices + coordinate_counter;
//
//     res_indices[ i ] = start_indices;
//     res_list[ i ] = sfheaders::interleave::interleave( sfg );
//
//     coordinate_counter = coordinate_counter + n_coordinates;
//   }
//
//   return Rcpp::List::create(
//     Rcpp::_["coordinates"] = sfheaders::utils::unlist_list( res_list ),
//     Rcpp::_["start_indices"] = sfheaders::utils::unlist_list( res_indices ),
//     Rcpp::_["stride"] = stride
//   );
// }


