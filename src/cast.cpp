#include <Rcpp.h>
#include "sfheaders/cast/sfg.hpp"
#include "sfheaders/cast/sfc.hpp"

#include "sfheaders/sfc/sfc.hpp"

// // [[Rcpp::export]]
// SEXP rcpp_sfg_cast_df( SEXP sfg ) {
//   return sfheaders::cast::sfg_to_cast_df( sfg );
// }
//
//
// // [[Rcpp::export]]
// SEXP rcpp_sfc_cast_df( Rcpp::List sfc ) {
//   return sfheaders::cast::sfc_to_cast_df( sfc );
// }

// [[Rcpp::export]]
SEXP rcpp_vec_to_vec( Rcpp::NumericVector sfg ) {
  double id = 1;
  R_xlen_t sfg_rows = 0;
  return sfheaders::cast::vec_to_vec( sfg, sfg_rows, id );
}

// [[Rcpp::export]]
SEXP rcpp_mat_to_vec( Rcpp::NumericMatrix sfg ) {
  double id = 1;
  R_xlen_t sfg_rows = 0;
  return sfheaders::cast::mat_to_vec( sfg, sfg_rows, id );
}

// [[Rcpp::export]]
SEXP rcpp_listMat_to_vec( Rcpp::List sfg ) {
  double id = 1;
  R_xlen_t sfg_rows = 0;
  return sfheaders::cast::listMat_to_vec( sfg, sfg_rows, id );
}

// [[Rcpp::export]]
SEXP rcpp_listListMat_to_vec( Rcpp::List sfg ) {
  double id = 1;
  R_xlen_t sfg_rows = 0;
  return sfheaders::cast::listListMat_to_vec( sfg, sfg_rows, id );
}

// [[Rcpp::export]]
SEXP rcpp_vec_to_mat( Rcpp::NumericVector sfg ) {
  double id = 1;
  R_xlen_t sfg_rows = 0;
  return sfheaders::cast::vec_to_mat( sfg, sfg_rows, id );
}

// [[Rcpp::export]]
SEXP rcpp_mat_to_mat( Rcpp::NumericMatrix sfg ) {
  double id = 1;
  R_xlen_t sfg_rows = 0;
  return sfheaders::cast::mat_to_mat( sfg, sfg_rows, id );
}


// [[Rcpp::export]]
SEXP rcpp_listMat_to_mat( Rcpp::List sfg ) {
  double id = 1;
  R_xlen_t sfg_rows = 0;
  return sfheaders::cast::listMat_to_mat( sfg, sfg_rows, id );
}


// [[Rcpp::export]]
SEXP rcpp_listListMat_to_mat( Rcpp::List sfg ) {
  double id = 1;
  R_xlen_t sfg_rows = 0;
  return sfheaders::cast::listListMat_to_mat( sfg, sfg_rows, id );
}

// [[Rcpp::export]]
SEXP rcpp_vec_to_listMat( Rcpp::NumericVector sfg ) {
  double id = 1;
  R_xlen_t sfg_rows = 0;
  return sfheaders::cast::vec_to_listMat( sfg, sfg_rows, id );
}

// [[Rcpp::export]]
SEXP rcpp_mat_to_listMat( Rcpp::NumericMatrix sfg ) {
  double id = 1;
  R_xlen_t sfg_rows = 0;
  return sfheaders::cast::mat_to_listMat( sfg, sfg_rows, id );
}

// [[Rcpp::export]]
SEXP rcpp_listMat_to_listMat( Rcpp::List sfg ) {
  double id = 1;
  R_xlen_t sfg_rows = 0;
  return sfheaders::cast::listMat_to_listMat( sfg, sfg_rows, id );
}


// [[Rcpp::export]]
SEXP rcpp_listListMat_to_listMat( Rcpp::List sfg ) {
  double id = 1;
  R_xlen_t sfg_rows = 0;
  return sfheaders::cast::listListMat_to_listMat( sfg, sfg_rows, id );
}

// [[Rcpp::export]]
SEXP rcpp_vec_to_listListMat( Rcpp::NumericVector sfg ) {
  double id = 1;
  R_xlen_t sfg_rows = 0;
  return sfheaders::cast::vec_to_listListMat( sfg, sfg_rows, id );
}

// [[Rcpp::export]]
SEXP rcpp_mat_to_listListMat( Rcpp::NumericMatrix sfg ) {
  double id = 1;
  R_xlen_t sfg_rows = 0;
  return sfheaders::cast::mat_to_listListMat( sfg, sfg_rows, id );
}

// [[Rcpp::export]]
SEXP rcpp_listMat_to_listListMat( Rcpp::List sfg ) {
  double id = 1;
  R_xlen_t sfg_rows = 0;
  return sfheaders::cast::listMat_to_listListMat( sfg, sfg_rows, id );
}

// [[Rcpp::export]]
SEXP rcpp_listListMat_to_listListMat( Rcpp::List sfg ) {
  double id = 1;
  R_xlen_t sfg_rows = 0;
  return sfheaders::cast::listListMat_to_listListMat( sfg, sfg_rows, id );
}

// [[Rcpp::export]]
SEXP rcpp_sfc_polygon_to_sfc_multipolygon( Rcpp::List sfc ) {
  double id = 1;
  R_xlen_t sfg_rows = 0;
  R_xlen_t i;
  R_xlen_t n = sfc.size();
  Rcpp::List res( n );
  for( i = 0; i < n; ++i ) {
    Rcpp::List sfg = sfc[ i ];
    res[ i ] = sfheaders::cast::listMat_to_listListMat( sfg, sfg_rows, id );
  }

  // make res a sfc_multipolygon
  return sfheaders::df::collapse_list( res, sfg_rows );

  // Rcpp::List res2 = sfheaders::df::collapse_list( res, sfg_rows );
  //
  // Rcpp::DataFrame df = Rcpp::DataFrame::create(
  //   Rcpp::_["x"] = res2[ 4 ],
  //   Rcpp::_["y"] = res2[ 5 ],
  //   Rcpp::_["mp_id"] = res2[ 1 ],
  //   Rcpp::_["p_id"] = res2[ 2 ],
  //   Rcpp::_["l_id"] = res2[ 3 ]
  // );
  //
  // Rcpp::IntegerVector geometry_cols({0,2});
  // int mpid = 2;
  // int pid = 3;
  // int lid = 4;
  //
  //
  // return sfheaders::sfc::sfc_multipolygon(
  //   df, geometry_cols, mpid, pid, lid
  // );
  // //return df;
}
