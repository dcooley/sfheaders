#ifndef R_SFHEADERS_CAST_SFG_H
#define R_SFHEADERS_CAST_SFG_H

#include "sfheaders/utils/utils.hpp"
#include "sfheaders/df/sfc.hpp"
#include "sfheaders/sfg/sfg.hpp"
//#include "sfheaders/sfg/sfg_types.hpp"
// #include "sfheaders/utils/sexp/sexp.hpp"
// #include "sfheaders/df/sfg.hpp"
// #include "sfheaders/df/utils.hpp"

#include <Rcpp.h>

// #define M_COLUMN_CAST                9
// #define Z_COLUMN_CAST                8
// #define Y_COLUMN_CAST                7
// #define X_COLUMN_CAST                6
// #define VECTOR_ID                    5
// #define MATRIX_ID                    4
// #define LIST_MATRIX_ID               3
// #define LIST_LIST_MATRIX_ID          2
// #define SFG_COLUMN_CAST              1
// #define SFC_COLUMN_CAST              0
//
// #define MAX_COLUMNS_CAST             10

namespace sfheaders {
namespace cast {


  // count number of sfc objects will be returned from the CAST function
  // only applies to donw-casting
  // as up-casting the objects either stay as-is, or get wrapped in an outer-list
  //
  // will return a vector the same lenght as n_row( sf ) / length( sfc )
  // the sum of this vector will allocate the result list
  // and be used to index the `sf` so properties are repeated.
  //
  // the listMat_to_listListMat functions can stay. I will need to use them
  // for down-casting (i.e. I need to use the id's.).
  // - may need to update the `sfg_()` functions to accept lists?
  //
  //
  // MULTIPOLYGON - to - POLYGON / MULTILINESTRING
  // - n == number of inner lists
  // MULTIPOLYGON - to - LINESTRING / MULTIPOING
  // - n == number of inner of inner lists

  // get_sfc_n_objects
  // (rather than get_sfc_n_coordinates)
  //

  // if( geometry == "POINT" ) {
  //   // going from POINT to POLYGON
  //   // (does this even make sense?)
  // } else if ( geometry == "MULTIPOINT") {
  //
  // } else if ( geometry == "LINESTRING" ) {
  //
  // } else if ( geometry == "MULTILINESTRING" ) {
  //
  // } else if ( geometry == "POLYGON" ) {
  //
  // } else if ( geometry == "MULTIPOLYGON" ) {
  //
  // } else {
  //   Rcpp::stop("sfheaders - I can't cast this type of object");
  // }


  inline R_xlen_t count_listMatrices( Rcpp::List& lst ) {
    return lst.size();
  }

  inline R_xlen_t count_listListMatrices( Rcpp::List& lst ) {
    // counts all the matrices inside a listList object
    R_xlen_t i, j, n;
    R_xlen_t res = 0;
    n = lst.size();
    // Rcpp::Rcout << "n: " << n << std::endl;
    for( i = 0; i < n; ++i ) {
      // Rcpp::Rcout << "res: " << res << std::endl;
      Rcpp::List inner_lst = lst[ i ];
      res = res + inner_lst.size();
      // Rcpp::Rcout << "res: " << res << std::endl;
    }
    return res;
  }

  inline R_xlen_t count_new_point_objects( SEXP& sfg, std::string& geometry ) {
    R_xlen_t n_coords = 0;
    sfheaders::df::sfg_n_coordinates( sfg, n_coords );
    return n_coords;
  }


  inline R_xlen_t count_new_multipoint_objects( SEXP& sfg, std::string& geometry ) {
    if( geometry == "POINT" ) {
      return 1;
    } else if ( geometry == "MULTIPOINT") {
      return 1;
    } else if ( geometry == "LINESTRING" ) {
      return 1;
    } else if ( geometry == "MULTILINESTRING" ) {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      return lst.size();
    } else if ( geometry == "POLYGON" ) {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      return count_listMatrices( lst );
    } else if ( geometry == "MULTIPOLYGON" ) {
      // count the size of the inner-inner-lists
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      return count_listListMatrices( lst );
    } else {
      Rcpp::stop("sfheaders - I can't cast this type of object");
    }
  }

  inline R_xlen_t count_new_linestring_objects( SEXP& sfg, std::string& geometry ) {
    if( geometry == "POINT" ) {
      return 1;
    } else if ( geometry == "MULTIPOINT") {
      return 1;
    } else if ( geometry == "LINESTRING" ) {
      return 1;
    } else if ( geometry == "MULTILINESTRING" ) {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      return lst.size();
    } else if ( geometry == "POLYGON" ) {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      return count_listMatrices( lst );
    } else if ( geometry == "MULTIPOLYGON" ) {
      // count the size of the inner-inner-lists
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      return count_listListMatrices( lst );
    } else {
      Rcpp::stop("sfheaders - I can't cast this type of object");
    }
  }

  inline R_xlen_t count_new_multilinestring_objects( SEXP& sfg, std::string& geometry ) {
    // going to polygon

    if( geometry == "POINT" ) {
      // going from POINT to POLYGON
      // (does this even make sense?)
      return 1;
    } else if ( geometry == "MULTIPOINT") {
      return 1;
    } else if ( geometry == "LINESTRING" ) {
      return 1;
    } else if ( geometry == "MULTILINESTRING" ) {
      return 1;
    } else if ( geometry == "POLYGON" ) {
      return 1;
    } else if ( geometry == "MULTIPOLYGON" ) {
      // count the size of the inner-lists
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      return lst.size();
    } else {
      Rcpp::stop("sfheaders - I can't cast this type of object");
    }
  }

  inline R_xlen_t count_new_polygon_objects( SEXP& sfg, std::string& geometry ) {
    // going to polygon

    if( geometry == "POINT" ) {
      // going from POINT to POLYGON
      // (does this even make sense?)
      return 1;
    } else if ( geometry == "MULTIPOINT") {
      return 1;
    } else if ( geometry == "LINESTRING" ) {
      return 1;
    } else if ( geometry == "MULTILINESTRING" ) {
      return 1;
    } else if ( geometry == "POLYGON" ) {
      return 1;
    } else if ( geometry == "MULTIPOLYGON" ) {
      // count the size of the inner-list
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      return lst.size();
    } else {
      Rcpp::stop("sfheaders - I can't cast this type of object");
    }
  }

  inline R_xlen_t count_new_multipolygon_objects( SEXP& sfg, std::string& geometry ) {
    // going to multipolygon
    return 1;
  }


  inline R_xlen_t count_new_objects( SEXP& sfg, std::string cast_to ) {

    Rcpp::CharacterVector cls = sfheaders::utils::getSfgClass( sfg );
    std::string geometry;
    geometry = cls[1];

    if( cast_to == "POINT" ) {
      return count_new_point_objects( sfg, geometry );
    } else if ( cast_to == "MULTIPOINT" ) {
      return count_new_multipoint_objects( sfg, geometry );
    } else if ( cast_to == "LINESTRING" ) {
      return count_new_linestring_objects( sfg, geometry );
    } else if ( cast_to == "MULTILINESTRING" ) {
      return count_new_multilinestring_objects( sfg, geometry );
    } else if ( cast_to == "POLYGON" ) {
      return count_new_polygon_objects( sfg, geometry );
    } else if ( cast_to == "MULTIPOLYGON" ) {
      return count_new_multipolygon_objects( sfg, geometry );
    } else {
      Rcpp::stop("sfheaders - I don't know the type of object you're trying to cast to");
    }

  }

  inline Rcpp::List listListMat_to_mat( Rcpp::List& sfg, std::string& cast_to ) {

    // need an extra list-level to store results?
    // but it has to be returned in a one-level deep list
    // ...
    // ...


    R_xlen_t n = sfg.size();
    R_xlen_t i;
    Rcpp::List res( n );
    return res;
    // for( i = 0; i < n; ++i ) {
    //   Rcpp::List lst = sfg[ i ];
    //
    //   if( cast_to == "LINESTRING" ) {
    //     res[ i ] = sfheaders::sfg::sfg_linestrings( sfg );
    //   } else if ( cast_to == "MULTIPOINT" ) {
    //     res[ i ] = sfheaders::sfg::sfg_multipoints( sfg );
    //   }
    // }

    // now un-pack the res[] list to a single-level list


  }

  inline Rcpp::List listListMat_to_listMat( Rcpp::List& sfg, std::string& cast_to ) {
    if( cast_to == "MULTILINESTRING" ) {
      return sfheaders::sfg::sfg_multilinestrings( sfg );
    } else if ( cast_to == "POLYGON" ) {
      return sfheaders::sfg::sfg_polygons( sfg );
    }
  }

  // inline Rcpp::List cast_to_linestring( SEXP& sfg, std::string& geometry, std::string& cast_to ) {
  //
  //   R_xlen_t count = count_new_objects( sfg, cast_to );
  //   Rcpp::Rcout << "new_objects: " << count << std::endl;
  //
  //   if( geometry == "POINT") {
  //
  //   } else if ( geometry == "MULTIPOINT" ) {
  //
  //   } else if ( geometry == "LINESTRING" ) {
  //
  //   } else if ( geometry == "MULTILINESTRING" ) {
  //
  //   } else if ( geometry == "POLYGON" ) {
  //     // Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
  //     // return lst;
  //   } else if ( geometry == "MULTIPOLYGON" ) {
  //     Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
  //     return listListMat_to_mat( lst, cast_to );
  //   } else {
  //     Rcpp::stop("sfheaders - I don't know how to convert this objet to a POLYGON");
  //   }
  // }

  inline Rcpp::List multipolygon_to_linestring( Rcpp::List& lst ) {
    // will return more than 1 list
    R_xlen_t n = lst.size();
    Rcpp::List lines( n );
    R_xlen_t n_linestrings = 0; // will update each iteration
    R_xlen_t i, j;
    for( i = 0; i < n; ++i ) {
      Rcpp::List inner_lst = lst[ i ];
      n_linestrings = n_linestrings + inner_lst.size();
      lines[ i ] = sfheaders::sfg::sfg_linestrings( inner_lst );
    }

    // unpack
    Rcpp::List res( n_linestrings );
    R_xlen_t counter = 0;
    for( i = 0; i < n; ++i ) {
      Rcpp::List sfg = lines[ i ];
      for( j = 0; j < sfg.size(); ++j ) {
        res[ counter ] = sfg[ j ];
        ++counter;
      }
    }
    return res;
  }

  inline Rcpp::List polygon_to_multipolygon( Rcpp::List& lst ) {
    lst.attr("class") = R_NilValue;
    Rcpp::List mpl(1);
    mpl[0] = lst;
    return lst;
    return sfheaders::sfg::sfg_multipolygon( mpl );
  }

  inline Rcpp::List multipolygon_to_multilinestring( Rcpp::List& lst ) {
    return sfheaders::sfg::sfg_multilinestrings( lst );
  }

  inline Rcpp::List multipolygon_to_polygon( Rcpp::List& lst ) {
    return sfheaders::sfg::sfg_polygons( lst );
  }

  inline Rcpp::List cast_to_linestring( SEXP& sfg, std::string& geometry, std::string& cast_to ) {

    if( geometry == "POINT") {

    } else if ( geometry == "MULTIPOINT" ) {

    } else if ( geometry == "LINESTRING" ) {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      return lst;
    } else if ( geometry == "MULTILINESTRING" ) {
    } else if ( geometry == "POLYGON" ) {
    } else if ( geometry == "MULTIPOLYGON" ) {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      return multipolygon_to_linestring( lst );
    } else {
      Rcpp::stop("sfheaders - I don't know how to convert this objet to a POLYGON");
    }
  }

  inline Rcpp::List cast_to_polygon( SEXP& sfg, std::string& geometry, std::string& cast_to ) {

    if( geometry == "POINT") {
    } else if ( geometry == "MULTIPOINT" ) {
    } else if ( geometry == "LINESTRING" ) {
    } else if ( geometry == "MULTILINESTRING" ) {
    } else if ( geometry == "POLYGON" ) {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      return lst;
    } else if ( geometry == "MULTIPOLYGON" ) {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      return multipolygon_to_polygon( lst );
    } else {
      Rcpp::stop("sfheaders - I don't know how to convert this objet to a POLYGON");
    }
  }

  inline Rcpp::List cast_to_multipolygon( SEXP& sfg, std::string& geometry, std::string& cast_to ) {

    if( geometry == "POINT") {
    } else if ( geometry == "MULTIPOINT" ) {
    } else if ( geometry == "LINESTRING" ) {
    } else if ( geometry == "MULTILINESTRING" ) {
    } else if ( geometry == "POLYGON" ) {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      return polygon_to_multipolygon( lst );
    } else if ( geometry == "MULTIPOLYGON" ) {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      return lst;
    } else {
      Rcpp::stop("sfheaders - I don't know how to convert this objet to a POLYGON");
    }
  }

  inline SEXP cast_to( SEXP& sfg, std::string cast_to ) {

    Rcpp::CharacterVector cls = sfheaders::utils::getSfgClass( sfg );
    std::string geometry;
    geometry = cls[1];

    if( cast_to == "POINT" ) {
      // return cast_to_point( sfg, geometry );
    } else if ( cast_to == "MULTIPOINT" ) {
      // return cast_to_multipoint( sfg, geometry );
    } else if ( cast_to == "LINESTRING" ) {
      return cast_to_linestring( sfg, geometry, cast_to );
    } else if ( cast_to == "MULTILINESTRING" ) {
      // return cast_to_multilinestring( sfg, geometry );
    } else if ( cast_to == "POLYGON" ) {
      return cast_to_polygon( sfg, geometry, cast_to );
    } else if ( cast_to == "MULTIPOLYGON" ) {
      return cast_to_multipolygon( sfg, geometry, cast_to );
    } else {
      Rcpp::stop("sfheaders - I don't know the type of object you're trying to cast to");
    }

  }



  // const Rcpp::CharacterVector column_names = {
  //   "sfc_id", "sfg_id", "list_list_matrix_id", "list_matrix_id", "matrix_id", "vector_id",
  //   "x","y","z","m"
  // };
  //
  // inline Rcpp::CharacterVector make_names( Rcpp::CharacterVector& cls ) {
  //
  //   std::string dim;
  //   std::string geometry;
  //
  //   Rcpp::LogicalVector columns( column_names.length() );
  //
  //   dim = cls[0];
  //   geometry = cls[1];
  //
  //   if ( dim == "XYZM" ) {
  //     columns[ Z_COLUMN_CAST ] = true;
  //     columns[ M_COLUMN_CAST ] = true;
  //   } else if ( dim == "XYZ" ) {
  //     columns[ Z_COLUMN_CAST ] = true;
  //   } else if ( dim == "XYM" ) {
  //     columns[ M_COLUMN_CAST ] = true;  // #nocov
  //   }
  //
  //   columns[ X_COLUMN_CAST ] = true;
  //   columns[ Y_COLUMN_CAST ] = true;
  //
  //   if( geometry == "POINT" ) {
  //   } else if ( geometry == "MULTIPOINT" ) {
  //
  //   } else if ( geometry == "LINESTRING" ) {
  //
  //   } else if ( geometry == "MULTILINESTRING" ) {
  //     columns[ MATRIX_ID ] = true;
  //
  //   } else if ( geometry == "POLYGON" ) {
  //     columns[ MATRIX_ID ] = true;
  //
  //   } else if ( geometry == "MULTIPOLYGON" ) {
  //     columns[ MATRIX_ID ] = true;
  //     columns[ LIST_MATRIX_ID ] = true;
  //   }
  //   return column_names[ columns ];
  // }
  //
  //
  // inline Rcpp::List sfg_to_cast_df( SEXP& sfg ) {
  //
  //   Rcpp::List res;
  //
  //   Rcpp::CharacterVector cls = sfheaders::utils::getSfgClass( sfg );
  //
  //   std::string dim;
  //   std::string geometry;
  //
  //   Rcpp::LogicalVector columns( column_names.length() );
  //
  //   dim = cls[0];
  //   geometry = cls[1];
  //
  //   R_xlen_t sfg_rows = 0;
  //
  //   if( geometry == "POINT" ) {
  //     Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( sfg );
  //     res = sfheaders::df::sfg_point_coordinates( nv, sfg_rows );
  //
  //   } else if ( geometry == "MULTIPOINT" ) {
  //     Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( sfg );
  //     res = sfheaders::df::sfg_multipoint_coordinates( nm, sfg_rows );
  //
  //   } else if ( geometry == "LINESTRING" ) {
  //     Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( sfg );
  //     res = sfheaders::df::sfg_linestring_coordinates( nm, sfg_rows );
  //
  //   } else if ( geometry == "MULTILINESTRING" ) {
  //     Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
  //     res = sfheaders::df::sfg_multilinestring_coordinates( lst, sfg_rows );
  //
  //   } else if ( geometry == "POLYGON" ) {
  //     Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
  //     res = sfheaders::df::sfg_polygon_coordinates( lst, sfg_rows );
  //
  //   } else if ( geometry == "MULTIPOLYGON" ) {
  //     Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
  //     res = sfheaders::df::sfg_multipolygon_coordinates( lst, sfg_rows );
  //
  //   } else {
  //     Rcpp::stop("sfheaders - unknown geometry type"); // #nocov
  //   }
  //
  //   Rcpp::CharacterVector df_names = make_names( cls );
  //
  //   res.attr("class") = Rcpp::CharacterVector("data.frame");
  //
  //   if( sfg_rows > 0 ) {
  //     Rcpp::IntegerVector rownames = Rcpp::seq( 1, sfg_rows );
  //     res.attr("row.names") = rownames;
  //   } else {
  //     res.attr("row.names") = Rcpp::IntegerVector(0); // #nocov
  //   }
  //
  //   res.attr("names") = df_names;
  //   return res;
  //
  // }

} // cast
} // sfheaders

#endif
