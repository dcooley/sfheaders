#ifndef R_SFHEADERS_SFG_MULTILINESTRING_H
#define R_SFHEADERS_SFG_MULTILINESTRING_H

#include "sfheaders/utils.hpp"
#include "sfheaders/sfg/sfg_dimension.hpp"
#include "sfheaders/sfg/sfg_attributes.hpp"
#include "sfheaders/shapes/shapes.hpp"

namespace sfheaders {
namespace sfg {

  // multilinestring is a list of linestrings (matrices)
  // but can also be a single matrix

  // inline SEXP to_multilinestring(
  //   Rcpp::IntegerMatrix& im
  // ) {
  //   Rcpp::List mls( 1 );
  //   mls[0] = im;
  //   size_t n_col = im.ncol();
  //   std::string dim = sfheaders::sfg::sfg_dimension( n_col );
  //
  //   std::string geom_type = "MULTILINESTRING";
  //   mls.attr("class") = sfheaders::sfg::sfg_attributes( dim, geom_type );
  //
  //   return mls;
  // }
  //
  // inline SEXP to_multilinestring(
  //     Rcpp::NumericMatrix& nm
  // ) {
  //   Rcpp::List mls( 1 );
  //   mls[0] = nm;
  //   size_t n_col = nm.ncol();
  //   std::string dim = sfheaders::sfg::sfg_dimension( n_col );
  //
  //   std::string geom_type = "MULTILINESTRING";
  //   mls.attr("class") = sfheaders::sfg::sfg_attributes( dim, geom_type );
  //
  //   return mls;
  // }
  //
  //
  // inline SEXP to_multilinestring(
  //   Rcpp::List& lst
  // ) {
  //
  //   size_t n = lst.size();
  //   size_t i;
  //   size_t n_col;
  //   for( i = 0; i < n; i++ ) {
  //     SEXP this_line = lst[ i ];
  //     if( !Rf_isMatrix( this_line ) ) {
  //       Rcpp::stop("sfheaders - multilinestring list must be a list of matrices");
  //     }
  //     size_t this_n_col = sfheaders::utils::get_sexp_n_col( this_line );
  //
  //     if( i == 0 ){
  //       n_col = this_n_col;
  //     }
  //     if( n_col != this_n_col ) {
  //       Rcpp::stop("sfheaders - multiple dimensions found for MULTILINESTRING");
  //     }
  //   }
  //   std::string dim = sfheaders::sfg::sfg_dimension( n_col );
  //
  //   std::string geom_type = "MULTILINESTRING";
  //   lst.attr("class") = sfheaders::sfg::sfg_attributes( dim, geom_type );
  //
  //   return lst;
  // }
  //
  // // cols will already be sorted x, y, z, m
  // inline SEXP to_multilinestring(
  //     Rcpp::DataFrame& df,
  //     Rcpp::String line_id,
  //     Rcpp::StringVector& geometry_cols
  // ) {
  //
  //   // line_id is an index, so we can assume it's an integer?
  //   Rcpp::IntegerVector line_ids = df[ line_id ];
  //   Rcpp::List mls = sfheaders::shapes::get_lines( df, geometry_cols, line_ids );
  //
  //   return to_multilinestring( mls );
  // }
  //
  // inline SEXP to_multilinestring(
  //     SEXP& x
  // ) {
  //   // switch on type of x
  //   switch ( TYPEOF( x ) ) {
  //   case INTSXP: {
  //     Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
  //     return to_multilinestring( im );
  //   }
  //   case REALSXP: {
  //     Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
  //     return to_multilinestring( nm );
  //   }
  //   case VECSXP: { // data.frame && list?
  //     //   if( Rf_isNewList( x ) ) {
  //     //   Rcpp::stop("sfheaders - lists not supported for sfg_POINT");
  //     // }
  //     // TODO - rather than Rf_isNewList - need to check the class is not data.frame
  //     //Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
  //     Rcpp::List lst = Rcpp::as< Rcpp::List >( x );
  //     return to_multilinestring( x );
  //   }
  //   default: {
  //     Rcpp::stop("sfheaders - unsupported sfg_MULTILINESTRING type");
  //   }
  //   }
  //
  //   return x; // never reaches
  // }


} // sfg
} // sfheaders

#endif
