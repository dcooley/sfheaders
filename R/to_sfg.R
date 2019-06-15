
## TODO
## - if defining column names, or numbers for matrix, the R function
## - needs to put them in order c(x, y, z, m)


#' to sfc
#'
#' converts a data.frame to an sfc object
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
