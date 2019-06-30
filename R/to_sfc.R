
#' to POINTS
#'
#' constructs sfc of POINT objects
#'
#' @examples
#'
#' x <- c(1:3)
#' to_points( x )
#'
#' x <- matrix( c(1:10) , ncol = 2 )
#' to_points( x )
#'
#' x <- setNames( as.data.frame( x ), c("x","y") )
#' to_points( x )
#' to_points( obj = x, x = "x", y = "y" )
#' to_points( obj = x, x = "y", y = "x" )
#'
#' @export
to_points <- function( obj, x = NULL, y = NULL, z = NULL, m = NULL ) {
  geometry_columns <- c(x,y,z,m)
  rcpp_to_points( obj, index_correct( geometry_columns ) )
}

#' to MULTIPOINTS
#'
#' constructs sfc of MULTIPOINT objects
#'
#' @examples
#'
#' x <- matrix( c(1:4), ncol = 2 )
#' to_multipoints( x )
#'
#' x <- data.frame( id = 1:2, x = 1:2, y = 2:1 )
#' to_multipoints( x )
#' to_multipoints( x, x = "x", y = "y" )
#' to_multipoints( x, x = "y", y = "x" )
#' to_multipoints( x, multipoint_id = "id", x = "x", y = "y")
#'
#' @export
to_multipoints <- function( obj, x = NULL, y = NULL, z = NULL, m = NULL, multipoint_id = NULL ) {
  geometry_columns <- c(x,y,z,m)
  rcpp_to_multipoints( obj, index_correct( geometry_columns ),  index_correct( multipoint_id ) )
}


#' to MULTIPOINTS
#'
#' constructs sfc of MULTIPOINT objects
#'
#' @examples
#'
#' x <- matrix( c(1:4), ncol = 2 )
#' to_linestrings( x )
#'
#' x <- data.frame( id = 1:2, x = 1:2, y = 2:1 )
#' to_linestrings( x )
#' to_linestrings( x, x = "x", y = "y" )
#' to_linestrings( x, x = "y", y = "x" )
#' to_linestrings( x, linestring_id = "id", x = "x", y = "y")
#'
#' @export
to_linestrings <- function( obj, x = NULL, y = NULL, z = NULL, m = NULL, linestring_id = NULL ) {
  geometry_columns <- c(x,y,z,m)
  rcpp_to_linestrings( obj, index_correct( geometry_columns ),  index_correct( linestring_id ) )
}
