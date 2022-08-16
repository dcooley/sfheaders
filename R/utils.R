
## convert R-index to c++-index
index_correct <- function( geometry_columns ) {
  if( is.numeric( geometry_columns ) ) {
    return( as.integer( geometry_columns ) - 1L )
  }

  return( geometry_columns )
}

xyzm <- function(x,y,z,m) {
  if(is.null(x) & is.null(y) & is.null(z) & is.null(m)) {
    return("") ## TODO: need to 'guess' what this is when in C++
  }
  if(!is.null(x) & !is.null(y) & is.null(z) & is.null(m) ) {
    return("XY")
  }
  if(!is.null(x) & !is.null(y) & !is.null(z) & is.null(m) ) {
    return("XYZ")
  }
  if(!is.null(x) & !is.null(y) & is.null(z) & !is.null(m) ) {
    return("XYM")
  }
  if(!is.null(x) & !is.null(y) & !is.null(z) & !is.null(m) ) {
    return("XYZM")
  }
  stop("sfheaders - unknown combination of x, y, z and m arguments")
}


#' remove holes
#'
#' Removes holes from polygons and multipolygons. Points and linestrings are unaffected.
#'
#' @param obj sfg, sfc or sf object.
#' @inheritParams sfc_polygon
#'
#' @examples
#' df <- data.frame(
#'   ml_id = c(1,1,1,1,1,1,1,1,1,2,2,2,2,2,2)
#'   , l_id = c(1,1,1,2,2,2,3,3,3,1,1,1,2,2,2)
#'   , x = rnorm(15)
#'   , y = rnorm(15)
#'   , z = rnorm(15)
#'   , m = rnorm(15)
#' )
#'
#' sfg <- sfg_polygon( obj = df, x = "x", y = "y", linestring_id = "ml_id" )
#' sfc <- sfc_polygon( obj = df, x = "x", y = "y", polygon_id = "ml_id", linestring_id = "l_id" )
#' sf <- sf_polygon( obj = df, x = "x", y = "y", polygon_id = "ml_id", linestring_id = "l_id" )
#'
#' sf_remove_holes( sfg )
#' sf_remove_holes( sfc )
#' sf_remove_holes( sf )
#'
#' @export
sf_remove_holes <- function( obj, close = TRUE ) remove_holes( obj, close )

remove_holes <- function( obj, close = TRUE ) UseMethod("remove_holes")

#' @export
remove_holes.sfg <- function( obj, close = TRUE ) {
  return( rcpp_sfg_remove_holes( obj, close ) )
}

#' @export
remove_holes.sfc <- function( obj, close = TRUE ) {
  return( rcpp_sfc_remove_holes( obj, close ) )
}

#' @export
remove_holes.sf <- function( obj, close = TRUE ) {
  geom_col <- attr(obj, "sf_column")
  obj[[ geom_col ]] <- remove_holes( obj[[ geom_col ]], close )
  return( obj )
}

#' @export
remove_holes.default <- function( obj, close = TRUE ) stop("only sfg, sfc and sf objects are supported")

