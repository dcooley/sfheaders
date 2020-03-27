#ifndef R_SFHEADERS_DF_LIST_H
#define R_SFHEADERS_DF_LIST_H

// adapted from colourvalues

#include <Rcpp.h>

/* unlisting a list
#
 * - follow: https://stackoverflow.com/questions/30175104/how-to-effectively-combine-a-list-of-numericvectors-into-one-large-numericvector
 * - get size of vector
 * - get type of each element
 * - get overal type
 * - create vector of overall type
 * - coerce other types to that overall type
 * - fill vector
 * - pass into colouring function
 * - CHECK: the order of values in the vector is maintained from the original list
 */

namespace sfheaders {
namespace utils {

  inline int vector_type( int new_type, int existing_type ) {

    // can't change from STRSXP
    if( existing_type == 16 ) {
      return existing_type;
    }

    std::vector< int > valid_types{10, 13, 14, 16};
    bool new_is_valid = ( std::find( valid_types.begin(), valid_types.end(), new_type ) != valid_types.end() );
    bool existing_is_valid = ( std::find( valid_types.begin(), valid_types.end(), existing_type ) != valid_types.end() );

    if( new_type == existing_type && new_is_valid ) {
      return existing_type;
    }

    // convert new type up to existing type
    if( new_type < existing_type && existing_is_valid ) {
      return existing_type;
    }

    if( new_type > existing_type && new_is_valid ) {
      return new_type;
    }

    if( new_type > existing_type && !new_is_valid ) {
      return 16;
    }

    if( existing_is_valid ) {
      return existing_type;
    }

    return 16;
  }

  inline Rcpp::List list_size(
    const Rcpp::List& lst,
    int& total_size,
    int& existing_type
  ) {
    R_xlen_t n = lst.size();
    Rcpp::List res( n ); // create a list to store the size corresponding to each list element
    R_xlen_t i;
    for( i = 0; i < n; i++ ) {
      switch( TYPEOF( lst[i] ) ) {
      case VECSXP: {
        res[ i ] = list_size( lst[i], total_size, existing_type );
        break;
      }
      default: {
        int n_elements = Rf_length( lst[i] );
        int new_type = TYPEOF( lst[i] );
        existing_type = vector_type( new_type, existing_type );
        res[i] = n_elements;
        total_size += n_elements;
      }
      }
    }
    return res;
  }

  // collapse a vector into a list
  // where line_ids gives the start and end indexes of v to use
  template < int RTYPE >
  inline Rcpp::List fill_list(
    Rcpp::Vector< RTYPE >& v,
    Rcpp::IntegerMatrix& line_positions
  ) {
    R_xlen_t n = line_positions.nrow();  // nrow should also be the row of the final sf object we are creating
    Rcpp::List res( n );
    R_xlen_t i;

    // Rcpp::Rcout << "n: " << n << std::endl;
    // Rcpp::Rcout << "line_positions: " << line_positions << std::endl;

    for( i = 0; i < n; ++i ) {
      //Rcpp::Rcout << "i: " << i << std::endl;
      R_xlen_t start = line_positions(i, 0);
      R_xlen_t end = line_positions(i, 1);
      Rcpp::IntegerVector elements = Rcpp::seq( start, end );
      //Rcpp::Rcout << "elements: " << elements << std::endl;
      res[ i ] = v[ elements ];
    }
    return res;
  }

  // TODO - handle dates and factors??
  inline Rcpp::List fill_list(
    SEXP& v,
    Rcpp::IntegerMatrix& line_positions
  ) {
    switch( TYPEOF( v ) ) {
    case LGLSXP: {
      Rcpp::LogicalVector lv = Rcpp::as< Rcpp::LogicalVector >( v );
      return fill_list( lv, line_positions );
    }
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( v );
      return fill_list( iv, line_positions );
    }
    case REALSXP: {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( v );
      return fill_list( nv, line_positions );
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( v );
      return fill_list( sv, line_positions );
    }
    default: {
      Rcpp::stop("sfheaders - unknown column type");
    }
    }
    return Rcpp::List::create(); // #nocov
  }


  /*
   * @param lst - the original input list
   * @param lst_sizes - the dimensions of the list
   * @param values - vector of values to be unlist
   */
  inline void unlist_list(
      const Rcpp::List& lst,
      const Rcpp::List& lst_sizes,
      Rcpp::LogicalVector& values,
      int& list_position
  ) {
    // - iterate through original list
    // - extract each element and insert into 'values'
    R_xlen_t n = lst.size();
    Rcpp::List res( n );
    R_xlen_t i;
    for( i = 0; i < n; ++i ) {
      switch( TYPEOF( lst[ i ] ) ) {
      case VECSXP: {
        unlist_list( lst[ i ], lst_sizes[ i ], values, list_position );
        break;
      }
      default: {
        Rcpp::IntegerVector n_elements = Rcpp::as< Rcpp::IntegerVector >( lst_sizes[ i ] );
        int end_position = list_position + n_elements[0] - 1;
        Rcpp::IntegerVector elements = Rcpp::seq( list_position, end_position );
        values[ elements ] = Rcpp::as< Rcpp::LogicalVector >( lst[ i ] );

        list_position = end_position + 1;
        break;
      }
      }
    }
  }

  inline void unlist_list(
      const Rcpp::List& lst,
      const Rcpp::List& lst_sizes,
      Rcpp::IntegerVector& values,
      int& list_position
  ) {
    // - iterate through original list
    // - extract each element and insert into 'values'
    R_xlen_t n = lst.size();
    Rcpp::List res( n );
    R_xlen_t i;
    for( i = 0; i < n; ++i ) {
      switch( TYPEOF( lst[ i ] ) ) {
      case VECSXP: {
        unlist_list( lst[ i ], lst_sizes[ i ], values, list_position );
        break;
      }
      default: {
        Rcpp::IntegerVector n_elements = Rcpp::as< Rcpp::IntegerVector >( lst_sizes[ i ] );
        int end_position = list_position + n_elements[0] - 1;
        Rcpp::IntegerVector elements = Rcpp::seq( list_position, end_position );
        values[ elements ] = Rcpp::as< Rcpp::IntegerVector >( lst[ i ] );

        list_position = end_position + 1;
        break;
      }
      }
    }
  }

  inline void unlist_list(
      const Rcpp::List& lst,
      const Rcpp::List& lst_sizes,
      Rcpp::NumericVector& values,
      int& list_position
  ) {
    // - iterate through original list
    // - extract each element and insert into 'values'
    R_xlen_t n = lst.size();
    Rcpp::List res( n );
    R_xlen_t i;
    for( i = 0; i < n; ++i ) {
      switch( TYPEOF( lst[ i ] ) ) {
      case VECSXP: {
        unlist_list( lst[ i ], lst_sizes[ i ], values, list_position );
        break;
      }
      default: {
        Rcpp::IntegerVector n_elements = Rcpp::as< Rcpp::IntegerVector >( lst_sizes[ i ] );
        int end_position = list_position + n_elements[0] - 1;
        Rcpp::IntegerVector elements = Rcpp::seq( list_position, end_position );
        values[ elements ] = Rcpp::as< Rcpp::NumericVector >( lst[ i ] );

        list_position = end_position + 1;
        break;
      }
      }
    }
  }

  inline void unlist_list(
      const Rcpp::List& lst,
      const Rcpp::List& lst_sizes,
      Rcpp::StringVector& values,
      int& list_position
  ) {
    // - iterate through original list
    // - extract each element and insert into 'values'
    R_xlen_t n = lst.size();
    Rcpp::List res( n );
    R_xlen_t i;
    for( i = 0; i < n; i++ ) {
      switch( TYPEOF( lst[i] ) ) {
      case VECSXP: {
        unlist_list( lst[ i ], lst_sizes[ i ], values, list_position );
        break;
      }
      default: {
        Rcpp::IntegerVector n_elements = Rcpp::as< Rcpp::IntegerVector >( lst_sizes[ i ] );
        int end_position = list_position + n_elements[0] - 1;
        Rcpp::IntegerVector elements = Rcpp::seq( list_position, end_position );
        values[ elements ] = Rcpp::as< Rcpp::StringVector >( lst[ i ] );

        list_position = end_position + 1;
        break;
      }
      }
    }
  }

 inline SEXP unlist_list( Rcpp::List& lst ) {

    int total_size = 0;
    int existing_type = 10;
    int position = 0;
    Rcpp::List lst_sizes = list_size( lst, total_size, existing_type );

    switch( existing_type ) {
    case LGLSXP: {
      Rcpp::LogicalVector lv( total_size );
      unlist_list( lst, lst_sizes, lv, position );
      return lv;
    }
    case INTSXP: {
      Rcpp::IntegerVector iv( total_size );
      unlist_list( lst, lst_sizes, iv, position );
      return iv;
    }
    case REALSXP: {
      Rcpp::NumericVector nv( total_size );
      unlist_list( lst, lst_sizes, nv, position );
      return nv;
    }
    default: {
      Rcpp::StringVector sv( total_size );
      unlist_list( lst, lst_sizes, sv, position );
      return sv;
    }
    }

    Rcpp::stop("sfheaders - couldn't unlist this object");
    return lst; // #nocov - never reaches

  }

} // utils
} // sfheaders

#endif

