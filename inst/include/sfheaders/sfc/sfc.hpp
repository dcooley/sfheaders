#ifndef R_SFHEADERS_SFC_H
#define R_SFHEADERS_SFC_H

namespace sfheaders {
namespace sfc {

  inline SEXP to_sfc( SEXP& x, Rcpp::List params ) {

    if( params.containsElementNamed("multipolygon_id") ) {
      if( !params.containsElementNamed("polygon_id") || !params.containsElementNamed("line_id") ) {
        Rcpp::stop("MULTIPOLYGONs require polygon_id and line_id arguments" );
        // return to_multipolygon( ) ;
      }
    }

    if( params.containsElementNamed("point_id") ) {
      SEXP point_id = params["point_id"];
      // can be a char giving column of data.frame, or numeric / int for column of matrix
      switch( TYPEOF( point_id ) ) {
      case INTSXP: {}
      case REALSXP: {
        // the parameters should be column indices, so int should be fine?
        Rcpp::IntegerVector pt_id = Rcpp::as< Rcpp::IntegerVector >( point_id );
        // if the point_id column has been supplied,
        // we need to loop on those values and create sfc objects
        // because sfg is a single object, not a collection?

        //return sfheaders::sfg::to_multipoint( x, pt_id );
      }
      }
    }

    return Rcpp::List::create(); // never reaches
  }

} // sfc
} // sfheaders

#endif
