
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
#' to_point( data.frame( x = 1, y = 2, z = 3 ), geometry_columns = c("x","y") )
#' to_point( data.frame( x = 1, y = 2, z = 3 ), geometry_columns = c(1,2) )
#'
#'
#' ## will error
#' # to_point( matrix( 1:4, ncol = 2 ) )
#'
#' @export
to_point <- function( x, geometry_columns = NULL ) {
  rcpp_to_point( x, index_correct( geometry_columns ) )
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
#' to_multipoint( matrix( 1:24, ncol = 4, byrow = T ), geometry_columns = c(1,2) )
#' to_multipoint( matrix( 1:24, ncol = 4, byrow = T ), geometry_columns = c(1:3) )
#' to_multipoint( matrix( 1:24, ncol = 4, byrow = T ), geometry_columns = c(3,4) )
#'
#' to_multipoint( data.frame( x = 1:5, y = 1:5, z = 11:15, m = 11:15 ), geometry_columns = c("x","y") )
#' to_multipoint( data.frame( x = 1:5, y = 1:5, z = 11:15, m = 11:15 ), geometry_columns = c("x","y","z") )
#' to_multipoint( data.frame( x = 1:5, y = 1:5, z = 11:15, m = 11:15 ), geometry_columns = c("x","y","z","m") )
#'
#' @export
to_multipoint <- function( x, geometry_columns = NULL ) {
  ## numeric columns need to be zero-indexed
  rcpp_to_multipoint( x, index_correct( geometry_columns ) )
}

#' to LINESTRING
#'
#' @export
to_linestring <- function( x, geometry_columns = NULL ) {
  rcpp_to_linestring( x, index_correct( geometry_columns ) )
}

#' to MULTILINESTRING
#'
#' @export
to_multilinestring <- function( x, geometry_columns = NULL ) {
  rcpp_to_multilinestring( x, index_correct( geometry_columns ) )
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
