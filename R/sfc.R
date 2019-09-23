
#' sfc POINT
#'
#' constructs sfc of POINT objects
#'
#' @param obj sorted vector, matrix or data.frame
#' @param x x geometry column
#' @param y y geometry column
#' @param z z geometry column
#' @param m m geometry column
#'
#' @section notes:
#' sfheaders functions do not perform any validity checks on the geometries.
#' Nor do they set Coordinate Reference Systems, EPSG, PROJ4 or precision attributes.
#'
#' The data.frame and matrices you send into the sfheader functions must be ordered.
#'
#' @return \code{sfc} object of POINT geometries
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

#' sfc MULTIPOINT
#'
#' constructs sfc of MULTIPOINT objects
#'
#' @inheritParams sfc_point
#' @param obj sorted matrix or data.frame
#' @inheritSection sfc_point notes
#' @param multipoint_id column of ids for multipoints
#'
#' @return \code{sfc} object of MULTIPOINT geometries
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
#' @inheritParams sfc_multipoint
#' @inheritSection sfc_point notes
#' @param linestring_id column of ids for linestrings
#'
#' @return \code{sfc} object of LINESTRING geometries
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
sfc_linestring <- function( obj = NULL, x = NULL, y = NULL, z = NULL, m = NULL, linestring_id = NULL ) {
  geometry_columns <- c(x,y,z,m)
  rcpp_sfc_linestring( obj, index_correct( geometry_columns ),  index_correct( linestring_id ) )
}


#' sfc MULTILINESTRING
#'
#' constructs an sfc of MULTILINESTRING objects
#'
#' @inheritParams sfc_linestring
#' @param multilinestring_id column of ids for multilinestrings
#' @param linestring_id column of ids for linestrings (within multilinestrings)
#'
#' @inheritSection sfc_point notes
#'
#' @return \code{sfc} object of MULTILINESTRING geometries
#'
#' @examples
#'
#' m <- matrix(c(0,0,0,0,1,1), ncol = 3 )
#' sfc_multilinestring( m )
#'
#' m <- matrix(c(0,0,0,0,0,1,0,1,1,1,2,2,1,2,3), ncol = 3, byrow = TRUE)
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
sfc_multilinestring <- function( obj = NULL, x = NULL, y = NULL, z = NULL, m = NULL, multilinestring_id = NULL, linestring_id = NULL ) {
  geometry_columns <- c(x,y,z,m)
  rcpp_sfc_multilinestring( obj, index_correct( geometry_columns ), index_correct( multilinestring_id ), index_correct( linestring_id ) )
}



#' sfc POLYGON
#'
#' constructs an sfc of POLYGON objects
#'
#' @inheritParams sfc_linestring
#' @param polygon_id column of ids for polygons
#' @param linestring_id column of ids for lines (within polygons)
#' @param close logical indicating whether polygons should be closed. If \code{TRUE},
#' all polygons will be checked and force closed if possible
#' @inheritSection sfc_point notes
#'
#' @return \code{sfc} object of POLYGON geometries
#'
#' @examples
#'
#' m <- matrix(c(0,0,0,0,1,1), ncol = 2 )
#' sfc_polygon( m )
#'
#' m <- matrix(c(0,0,0,0,0,1,0,1,1,1,2,2,1,2,3,1,3,2), ncol = 3, byrow = TRUE)
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
#'   ml_id = c(1,1,1,1,1,1,1,1,1,2,2,2,2,2,2)
#'   , l_id = c(1,1,1,2,2,2,3,3,3,1,1,1,2,2,2)
#'   , x = rnorm(15)
#'   , y = rnorm(15)
#'   , z = rnorm(15)
#'   , m = rnorm(15)
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
sfc_polygon <- function( obj = NULL, x = NULL, y = NULL, z = NULL, m = NULL, polygon_id = NULL, linestring_id = NULL, close = TRUE ) {
  geometry_columns <- c(x,y,z,m)
  rcpp_sfc_polygon( obj, index_correct( geometry_columns ), index_correct( polygon_id ), index_correct( linestring_id ), close )
}


#' sfc MULTIPOLYGON
#'
#' constructs an sfc of MULTIPOLYGON objects
#'
#'
#' @inheritParams sfc_polygon
#' @param multipolygon_id column of ids for multipolygons
#' @inheritSection sfc_point notes
#'
#' @return \code{sfc} object of MULTIPOLYGON geometries
#'
#' @examples
#'
#' m <- matrix(c(0,0,0,0,1,0,0,1,1,0,0,1,0,0,0), ncol = 3, byrow = TRUE )
#' sfc_multipolygon( m )
#'
#' df <- data.frame(
#'   id = c(1,1,1,1,1)
#'   , x = c(0,0,1,1,0)
#'   , y = c(0,1,1,0,0)
#' )
#'
#' sfc_multipolygon( df, x = "x", y = "y" )
#'
#' df <- data.frame(
#'   id = c(1,1,1,1,1,2,2,2,2,2)
#'   , x = c(0,0,1,1,0,1,1,2,2,1)
#'   , y = c(0,1,1,0,0,1,2,2,1,1)
#' )
#'
#' sfc_multipolygon( df, multipolygon_id = "id", polygon_id = "id", linestring_id = "id")
#'
#' df <- data.frame(
#'   id1 = c(1,1,1,1,1,1,1,1,1,1)
#'   , id2 = c(1,1,1,1,1,2,2,2,2,2)
#'   , x = c(0,0,1,1,0,1,1,2,2,1)
#'   , y = c(0,1,1,0,0,1,2,2,1,1)
#' )
#'
#' sfc_multipolygon( df, multipolygon_id = "id1", polygon_id = "id2")
#'
#' df <- data.frame(
#'   id1 = c(1,1,1,1,1,1,1,1,1,1,2,2,2,2,2)
#'   , id2 = c(1,1,1,1,1,2,2,2,2,2,1,1,1,1,1)
#'   , x = c(0,0,1,1,0,1,1,2,2,1,3,3,4,4,3)
#'   , y = c(0,1,1,0,0,1,2,2,1,1,3,4,4,3,3)
#' )
#'
#' sfc_multipolygon( df, multipolygon_id = "id1", polygon_id = "id2")
#'
#' df <- data.frame(
#'   id1 = c(1,1,1,1,1,2,2,2,2,2)
#'   , id2 = c(1,1,1,1,1,1,1,1,1,1)
#'   , x = c(0,0,1,1,0,1,1,2,2,1)
#'   , y = c(0,1,1,0,0,1,2,2,1,1)
#' )
#'
#' sfc_multipolygon( df, multipolygon_id = "id1", polygon_id = "id2" )
#' sfc_multipolygon( df, polygon_id = "id1", linestring_id = "id2" )
#' sfc_multipolygon( df, x = "x", y = "y", polygon_id = "id1")
#' sfc_multipolygon( df, x = "x", y = "y", polygon_id = "id1", linestring_id =)
#' sfc_multipolygon( df, x = "x", y = "y", linestring_id = "id1")
#' sfc_multipolygon( df, x = "x", y = "y", linestring_id = "id2")
#'
#' df <- data.frame(
#'   id1 = c('a','a','a','a','a','b','b','b','b','b')
#'   , id2 = c(1,1,1,1,1,1,1,1,1,1)
#'   , x = c(0,0,1,1,0,1,1,2,2,1)
#'   , y = c(0,1,1,0,0,1,2,2,1,1)
#' )
#'
#' sfc_multipolygon( df, x = "x", y = "y", polygon_id = "id1")
#'
#' @export
sfc_multipolygon <- function( obj = NULL, x = NULL, y = NULL, z = NULL, m = NULL, multipolygon_id = NULL, polygon_id = NULL, linestring_id = NULL, close = TRUE ) {
  geometry_columns <- c(x,y,z,m)
  rcpp_sfc_multipolygon( obj, index_correct( geometry_columns ), index_correct( multipolygon_id ), index_correct( polygon_id ), index_correct( linestring_id ), close )
}
