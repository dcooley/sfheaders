#ifndef R_SFHEADERS_SFG_ATTRIBUTES_H
#define R_SFHEADERS_SFG_ATTRIBUTES_H

#include <Rcpp.h>

namespace sfheaders {
namespace sfg {

  inline Rcpp::CharacterVector sfg_attributes( std::string& dimension, std::string& geom_type ) {
    return Rcpp::CharacterVector::create( dimension, geom_type, "sfg" );
  }

} // sfg
} // sfheaders


#endif
