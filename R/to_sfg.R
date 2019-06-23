
## TODO
## - if defining column names, or numbers for matrix, the R function
## - needs to put them in order c(x, y, z, m)

#' to POINT
#'
#' @examples
#'
#' to_point( 1:2 )
#' to_point( 1:3 )
#' to_point( 1:4 )
#'
#' to_point( matrix( 1:3, ncol = 3 ) )
#' to_point( data.frame( x = 1, y = 2, z = 3 )  )
#'
#' to_point( data.frame( x = 1, y = 2, z = 3 ), x = "x", y = "y" )
#' to_point( data.frame( x = 1, y = 2, z = 3 ), x = 1, y = 3  )
#'
#' @export
to_point <- function( obj, x = NULL, y = NULL, z = NULL, m = NULL ) {
  geometry_columns <- c(x,y,z,m)
  rcpp_to_point( obj, index_correct( geometry_columns ) )
}


#' to MULTIPOINT
#'
#' @examples
#'
#' to_multipoint( 1:2 )
#' to_multipoint( 1:3 )
#' to_multipoint( 1:4 )
#'
#' to_multipoint( matrix( 1:3, ncol = 3 ) )
#' to_multipoint( data.frame( x = 1, y = 2, z = 3 )  )
#'
#' to_multipoint( matrix( 1:4, ncol = 2 ) )
#' to_multipoint( matrix( 1:24, ncol = 2, byrow = T ) )
#' to_multipoint( matrix( 1:24, ncol = 3, byrow = T ) )
#' to_multipoint( matrix( 1:24, ncol = 4, byrow = T ) )
#'
#' to_multipoint( data.frame( x = 1:5, y = 1:5 ) )
#'
#' ## using columns
#'
#' to_multipoint( matrix( 1:24, ncol = 4, byrow = T ), x = 1, y = 2 )
#' to_multipoint( matrix( 1:24, ncol = 4, byrow = T ), x = 1, y = 2, z = 3 )
#' to_multipoint( matrix( 1:24, ncol = 4, byrow = T ), x = 3, y = 4 )
#'
#' to_multipoint( data.frame( x = 1:5, y = 1:5, z = 11:15, m = 11:15 ), x = "x", y = "y" )
#' to_multipoint( data.frame( x = 1:5, y = 1:5, z = 11:15, m = 11:15 ), x = "x", y = "y", z = "z" )
#' to_multipoint( data.frame( x = 1:5, y = 1:5, z = 11:15, m = 11:15 ), x = "x", y = "y", z = "z", m = "m" )
#'
#' @export
to_multipoint <- function( obj, x = NULL, y = NULL, z = NULL, m = NULL ) {
  geometry_columns <- c(x,y,z,m)
  rcpp_to_multipoint( obj, index_correct( geometry_columns ) )
}

#' to LINESTRING
#'
#' @examples
#'
#' to_linestring( matrix( 1:24, ncol = 2 ) )
#' to_linestring( matrix( 1:24, ncol = 3 ) )
#' to_linestring( matrix( 1:24, ncol = 4 ) )
#'
#' to_linestring( matrix( 1:24, ncol = 4 ), x = 3, y = 2, z = 3)
#'
#' to_linestring( data.frame( x = 1:10, y = 11:20 ) )
#' to_linestring( data.frame( x = 1:10, y = 11:20, z = 21:30 ) )
#' to_linestring( data.frame( x = 1:10, y = 11:20, z = 21:30 ), x = "x", y = "z" )
#'
#'
#' @export
to_linestring <- function( obj, x = NULL, y = NULL, z = NULL, m = NULL ) {
  geometry_columns <- c(x,y,z,m)
  rcpp_to_linestring( obj, index_correct( geometry_columns ) )
}

#' to MULTILINESTRING
#'
#' @examples
#'
#' to_multilinestring( matrix( 1:24, ncol = 2 ) )
#' to_multilinestring( matrix( 1:24, ncol = 3 ) )
#' to_multilinestring( matrix( 1:24, ncol = 4 ) )
#'
#' ## different lines
#' m <- cbind( matrix( 1:24, ncol = 2 ), c(rep(1, 6), rep(2, 6) ) )
#' to_multilinestring( obj = m, x = 1, y = 2, line_id = 3 )
#'
#' ## just specifying line_id will use all others as the geometries
#' to_multilinestring( obj = m, line_id = 3 )
#'
#' df <- data.frame( x = 1:12, y = 1:12, z = 13:24, id = c(rep(1,6), rep(2,6)))
#' to_multilinestring( df, x = "x", y = "y" )
#' to_multilinestring( df, x = "x", y = "y", line_id = "id" )
#'
#' to_multilinestring( df, line_id = "id" )
#'
#'
#' @export
to_multilinestring <- function( obj, x = NULL, y = NULL, z = NULL, m = NULL, line_id = NULL ) {
  geometry_columns <- c(x,y,z,m)
  rcpp_to_multilinestring( obj, index_correct( geometry_columns ),  index_correct( line_id ) )
}


#' to MULTILINESTRING
#'
#' @examples
#'
#' to_polygon( matrix( 1:24, ncol = 2 ) )
#' to_polygon( matrix( 1:24, ncol = 3 ) )
#' to_polygon( matrix( 1:24, ncol = 4 ) )
#'
#' ## different lines
#' m <- cbind( matrix( 1:24, ncol = 2 ), c(rep(1, 6), rep(2, 6) ) )
#' to_polygon( obj = m, x = 1, y = 2, line_id = 3 )
#'
#' ## just specifying line_id will use all others as the geometries
#' to_polygon( obj = m, line_id = 3 )
#'
#' df <- data.frame( x = 1:12, y = 1:12, z = 13:24, id = c(rep(1,6), rep(2,6)))
#' to_polygon( df, x = "x", y = "y" )
#' to_polygon( df, x = "x", y = "y", line_id = "id" )
#'
#' to_polygon( df, line_id = "id" )
#'
#'
#' @export
to_polygon <- function( obj, x = NULL, y = NULL, z = NULL, m = NULL, line_id = NULL ) {
  geometry_columns <- c(x,y,z,m)
  rcpp_to_polygon( obj, index_correct( geometry_columns ),  index_correct( line_id ) )
}



#' to sfc
#'
#' converts a data.frame to an sfc object
#'
#'
#' @examples
#'
#' df <- data.frame(
#'   id = rep(1,5),
#'   x = 1:5,
#'   y = 6:10,
#'   z = 11:15
#' )
#'
#' @export
to_sfg <- function(
  obj,
  x,
  y,
  z = NULL,
  m = NULL,
  point_id = NULL,
  multipoint_id = NULL,
  linestring_id = NULL,
  multilinestring_id = NULL,
  polygon_id = NULL,
  multipolygon_id = NULL
) {

  l <- list()
  l[["x"]] <- force( x )
  l[["y"]] <- force( y )
  l[["z"]] <- force( z )
  l[["m"]] <- force( m )
  l[["point_id"]] <- force( point_id )
  l[["multipoint_id"]] <- force( multiponit_id )
  l[["linestring_id"]] <- force( linestring_id )
  l[["multilinestring_id"]] <- force( multilinestring_id )
  l[["polygon_id"]] <- force( polygon_id )
  l[["multipolygon_id"]] <- force( multipolygon_id )



}
