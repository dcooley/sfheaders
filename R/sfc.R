
#' sfc POINTS
#'
#' constructs sfc of POINT objects
#'
#' @examples
#'
#' x <- c(1:3)
#' sfc_point( x )
#'
#' x <- matrix( c(1:10) , ncol = 2 )
#' sfc_point( x )
#'
#' x <- setNames( as.data.frame( x ), c("x","y") )
#' sfc_point( x )
#' sfc_point( obj = x, x = "x", y = "y" )
#' sfc_point( obj = x, x = "y", y = "x" )
#'
#' @export
sfc_point <- function( obj, x = NULL, y = NULL, z = NULL, m = NULL ) {
  geometry_columns <- c(x,y,z,m)
  rcpp_sfc_point( obj, index_correct( geometry_columns ) )
}

#' sfc MULTIPOINTS
#'
#' constructs sfc of MULTIPOINT objects
#'
#' @examples
#'
#' x <- matrix( c(1:4), ncol = 2 )
#' sfc_multipoint( x )
#'
#' x <- data.frame( id = 1:2, x = 1:2, y = 2:1 )
#' sfc_multipoint( x )
#' sfc_multipoint( x, x = "x", y = "y" )
#' sfc_multipoint( x, x = "y", y = "x" )
#' sfc_multipoint( x, multipoint_id = "id", x = "x", y = "y")
#'
#' @export
sfc_multipoint <- function( obj, x = NULL, y = NULL, z = NULL, m = NULL, multipoint_id = NULL ) {
  geometry_columns <- c(x,y,z,m)
  rcpp_sfc_multipoint( obj, index_correct( geometry_columns ),  index_correct( multipoint_id ) )
}


#' sfc LINESTRING
#'
#' constructs sfc of MULTIPOINT objects
#'
#' @examples
#'
#' x <- matrix( c(1:4), ncol = 2 )
#' sfc_linestring( x )
#'
#' x <- data.frame( id = 1:2, x = 1:2, y = 2:1 )
#' sfc_linestring( x )
#' sfc_linestring( x, x = "x", y = "y" )
#' sfc_linestring( x, x = "y", y = "x" )
#' sfc_linestring( x, linestring_id = "id", x = "x", y = "y")
#'
#' @export
sfc_linestring <- function( obj, x = NULL, y = NULL, z = NULL, m = NULL, linestring_id = NULL ) {
  geometry_columns <- c(x,y,z,m)
  rcpp_sfc_linestring( obj, index_correct( geometry_columns ),  index_correct( linestring_id ) )
}


#' sfc MULTILINESTRING
#'
#' @examples
#'
#' m <- matrix(c(0,0,0,0,1,1), ncol = 3 )
#' sfc_multilinestring( m )
#'
#' m <- matrix(c(0,0,0,0,0,1,0,1,1,1,2,2,1,2,3), ncol = 3, byrow = T)
#' sfc_multilinestring( obj = m )
#' sfc_multilinestring( obj = m, multilinestring_id = 1 )
#' sfc_multilinestring( obj = m, linestring_id = 1 )
#'
#' sfc_multilinestring( obj = m, linestring_id = 1, multilinestring_id = 1 )
#'
#' sfc_multilinestring( obj = m, x = 2, y = 3 )
#' sfc_multilinestring( obj = m, x = 1, y = 2, z = 3 )
#' sfc_multilinestring( obj = m, x = 2, y = 3, linestring_id = 1, multilinestring_id = 1 )
#'
#' df <- data.frame(
#'   ml_id = c(1,1,1,1,1,1,1,1,2,2,2,2,2)
#'   , l_id = c(1,1,1,2,2,3,3,3,1,1,1,2,2)
#'   , x = rnorm(13)
#'   , y = rnorm(13)
#'   , z = rnorm(13)
#'   , m = rnorm(13)
#' )
#'
#' sfc_multilinestring( obj = df, x = "x", y = "y")
#' sfc_multilinestring( obj = df, x = "x", y = "y", z = "z")
#' sfc_multilinestring( obj = df, x = "x", y = "y", z = "z", m = "m")
#'
#' sfc_multilinestring( obj = df, x = 2, y = 3)
#' sfc_multilinestring( obj = df, x = 2, y = 3, z = 4)
#' sfc_multilinestring( obj = df, x = 2, y = 3, z = 4, m = 5)
#'
#' sfc_multilinestring( obj = df, multilinestring_id = "ml_id", linestring_id = "l_id" )
#' sfc_multilinestring( obj = df, multilinestring_id = 1, linestring_id = 2 )
#'
#'
#'
#' @export
sfc_multilinestring <- function( obj, x = NULL, y = NULL, z = NULL, m = NULL, multilinestring_id = NULL, linestring_id = NULL ) {
  geometry_columns <- c(x,y,z,m)
  rcpp_sfc_multilinestring( obj, index_correct( geometry_columns ), index_correct( multilinestring_id ), index_correct( linestring_id ) )
}



#' sfc POLYGON
#'
#' @examples
#'
#' m <- matrix(c(0,0,0,0,1,1), ncol = 3 )
#' sfc_polygon( m )
#'
#' m <- matrix(c(0,0,0,0,0,1,0,1,1,1,2,2,1,2,3), ncol = 3, byrow = T)
#' sfc_polygon( obj = m )
#' sfc_polygon( obj = m, polygon_id = 1 )
#' sfc_polygon( obj = m, linestring_id = 1 )
#'
#' sfc_polygon( obj = m, linestring_id = 1, polygon_id = 1 )
#'
#' sfc_polygon( obj = m, x = 2, y = 3 )
#' sfc_polygon( obj = m, x = 1, y = 2, z = 3 )
#' sfc_polygon( obj = m, x = 2, y = 3, linestring_id = 1, polygon_id = 1 )
#'
#' df <- data.frame(
#'   ml_id = c(1,1,1,1,1,1,1,1,2,2,2,2,2)
#'   , l_id = c(1,1,1,2,2,3,3,3,1,1,1,2,2)
#'   , x = rnorm(13)
#'   , y = rnorm(13)
#'   , z = rnorm(13)
#'   , m = rnorm(13)
#' )
#'
#' sfc_polygon( obj = df, x = "x", y = "y")
#' sfc_polygon( obj = df, x = "x", y = "y", z = "z")
#' sfc_polygon( obj = df, x = "x", y = "y", z = "z", m = "m")
#'
#' sfc_polygon( obj = df, x = 2, y = 3)
#' sfc_polygon( obj = df, x = 2, y = 3, z = 4)
#' sfc_polygon( obj = df, x = 2, y = 3, z = 4, m = 5)
#'
#' sfc_polygon( obj = df, polygon_id = "ml_id", linestring_id = "l_id" )
#' sfc_polygon( obj = df, polygon_id = 1, linestring_id = 2 )
#'
#'
#'
#' @export
sfc_polygon <- function( obj, x = NULL, y = NULL, z = NULL, m = NULL, polygon_id = NULL, linestring_id = NULL ) {
  geometry_columns <- c(x,y,z,m)
  rcpp_sfc_polygon( obj, index_correct( geometry_columns ), index_correct( polygon_id ), index_correct( linestring_id ) )
}