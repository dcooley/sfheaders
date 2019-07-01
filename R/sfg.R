#' to POINT
#'
#' @examples
#'
#' sfg_point( 1:2 )
#' sfg_point( 1:3 )
#' sfg_point( 1:4 )
#'
#' sfg_point( matrix( 1:3, ncol = 3 ) )
#' sfg_point( data.frame( x = 1, y = 2, z = 3 )  )
#'
#' sfg_point( data.frame( x = 1, y = 2, z = 3 ), x = "x", y = "y" )
#' sfg_point( data.frame( x = 1, y = 2, z = 3 ), x = 1, y = 3  )
#'
#' @export
sfg_point <- function( obj, x = NULL, y = NULL, z = NULL, m = NULL ) {
  geometry_columns <- c(x,y,z,m)
  rcpp_sfg_point( obj, index_correct( geometry_columns ) )
}


#' to MULTIPOINT
#'
#' @examples
#'
#' sfg_multipoint( 1:2 )
#' sfg_multipoint( 1:3 )
#' sfg_multipoint( 1:4 )
#'
#' sfg_multipoint( matrix( 1:3, ncol = 3 ) )
#' sfg_multipoint( data.frame( x = 1, y = 2, z = 3 )  )
#'
#' sfg_multipoint( matrix( 1:4, ncol = 2 ) )
#' sfg_multipoint( matrix( 1:24, ncol = 2, byrow = T ) )
#' sfg_multipoint( matrix( 1:24, ncol = 3, byrow = T ) )
#' sfg_multipoint( matrix( 1:24, ncol = 4, byrow = T ) )
#'
#' sfg_multipoint( data.frame( x = 1:5, y = 1:5 ) )
#'
#' ## using columns
#'
#' sfg_multipoint( matrix( 1:24, ncol = 4, byrow = T ), x = 1, y = 2 )
#' sfg_multipoint( matrix( 1:24, ncol = 4, byrow = T ), x = 1, y = 2, z = 3 )
#' sfg_multipoint( matrix( 1:24, ncol = 4, byrow = T ), x = 3, y = 4 )
#'
#' sfg_multipoint( data.frame( x = 1:5, y = 1:5, z = 11:15, m = 11:15 ), x = "x", y = "y" )
#' sfg_multipoint( data.frame( x = 1:5, y = 1:5, z = 11:15, m = 11:15 ), x = "x", y = "y", z = "z" )
#' sfg_multipoint( data.frame( x = 1:5, y = 1:5, z = 11:15, m = 11:15 ), x = "x", y = "y", z = "z", m = "m" )
#'
#' @export
sfg_multipoint <- function( obj, x = NULL, y = NULL, z = NULL, m = NULL ) {
  geometry_columns <- c(x,y,z,m)
  rcpp_sfg_multipoint( obj, index_correct( geometry_columns ) )
}

#' to LINESTRING
#'
#' @examples
#'
#' sfg_linestring( matrix( 1:24, ncol = 2 ) )
#' sfg_linestring( matrix( 1:24, ncol = 3 ) )
#' sfg_linestring( matrix( 1:24, ncol = 4 ) )
#'
#' sfg_linestring( matrix( 1:24, ncol = 4 ), x = 3, y = 2, z = 3)
#'
#' sfg_linestring( data.frame( x = 1:10, y = 11:20 ) )
#' sfg_linestring( data.frame( x = 1:10, y = 11:20, z = 21:30 ) )
#' sfg_linestring( data.frame( x = 1:10, y = 11:20, z = 21:30 ), x = "x", y = "z" )
#'
#'
#' @export
sfg_linestring <- function( obj, x = NULL, y = NULL, z = NULL, m = NULL ) {
  geometry_columns <- c(x,y,z,m)
  rcpp_sfg_linestring( obj, index_correct( geometry_columns ) )
}

#' to MULTILINESTRING
#'
#' @examples
#'
#' sfg_multilinestring( matrix( 1:24, ncol = 2 ) )
#' sfg_multilinestring( matrix( 1:24, ncol = 3 ) )
#' sfg_multilinestring( matrix( 1:24, ncol = 4 ) )
#'
#' ## different lines
#' m <- cbind( matrix( 1:24, ncol = 2 ), c(rep(1, 6), rep(2, 6) ) )
#' sfg_multilinestring( obj = m, x = 1, y = 2, line_id = 3 )
#'
#' ## just specifying line_id will use all others as the geometries
#' sfg_multilinestring( obj = m, line_id = 3 )
#'
#' df <- data.frame( x = 1:12, y = 1:12, z = 13:24, id = c(rep(1,6), rep(2,6)))
#' sfg_multilinestring( df, x = "x", y = "y" )
#' sfg_multilinestring( df, x = "x", y = "y", line_id = "id" )
#'
#' sfg_multilinestring( df, line_id = "id" )
#'
#'
#' @export
sfg_multilinestring <- function( obj, x = NULL, y = NULL, z = NULL, m = NULL, line_id = NULL ) {
  geometry_columns <- c(x,y,z,m)
  rcpp_sfg_multilinestring( obj, index_correct( geometry_columns ),  index_correct( line_id ) )
}


#' to MULTILINESTRING
#'
#' @examples
#'
#' sfg_polygon( matrix( 1:24, ncol = 2 ) )
#' sfg_polygon( matrix( 1:24, ncol = 3 ) )
#' sfg_polygon( matrix( 1:24, ncol = 4 ) )
#'
#' ## different lines
#' m <- cbind( matrix( 1:24, ncol = 2 ), c(rep(1, 6), rep(2, 6) ) )
#' sfg_polygon( obj = m, x = 1, y = 2, line_id = 3 )
#'
#' ## just specifying line_id will use all others as the geometries
#' sfg_polygon( obj = m, line_id = 3 )
#'
#' df <- data.frame( x = 1:12, y = 1:12, z = 13:24, id = c(rep(1,6), rep(2,6)))
#' sfg_polygon( df, x = "x", y = "y" )
#' sfg_polygon( df, x = "x", y = "y", line_id = "id" )
#'
#' sfg_polygon( df, line_id = "id" )
#'
#'
#' @export
sfg_polygon <- function( obj, x = NULL, y = NULL, z = NULL, m = NULL, line_id = NULL ) {
  geometry_columns <- c(x,y,z,m)
  rcpp_sfg_polygon( obj, index_correct( geometry_columns ),  index_correct( line_id ) )
}


#' to MULTIPOLYGON
#'
#' @examples
#'
#' df <- data.frame(
#'   polygon_id = c(rep(1, 5), rep(2, 10))
#'   , line_id = c(rep(1, 10), rep(2, 5))
#'   , x = c(0,0,1,1,0,2,2,5,5,2,3,3,4,4,3)
#'   , y = c(0,1,1,0,0,2,5,5,2,2,3,4,4,3,3)
#'   , z = c(1)
#'   , m = c(1)
#' )
#'
#' m <- as.matrix( df )
#'
#' sfg_multipolygon( df[, c("x","y") ] )
#'
#' sfg_multipolygon( df, x = "x", y = "y", polygon_id = "polygon_id", line_id = "line_id" )
#' sfg_multipolygon( df, x = "x", y = "y", z = "z", polygon_id = "polygon_id", line_id = "line_id" )
#' sfg_multipolygon( df, x = "x", y = "y", z = "z", m = "m", polygon_id = "polygon_id", line_id = "line_id" )
#'
#'
#' sfg_multipolygon( m[, c("x","y") ] )
#'
#' sfg_multipolygon( m, x = "x", y = "y", polygon_id = "polygon_id", line_id = "line_id" )
#' sfg_multipolygon( m, x = "x", y = "y", z = "z", polygon_id = "polygon_id", line_id = "line_id" )
#' sfg_multipolygon( m, x = "x", y = "y", z = "z", m = "m", polygon_id = "polygon_id", line_id = "line_id" )
#'
#' @export
sfg_multipolygon <- function( obj, x = NULL, y = NULL, z = NULL, m = NULL, polygon_id = NULL, line_id = NULL ) {
  geometry_columns <- c(x,y,z,m)
  rcpp_sfg_multipolygon( obj, index_correct( geometry_columns ), index_correct( polygon_id ), index_correct( line_id ) )
}






