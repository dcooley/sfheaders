## build functions to take a data.frame and convert to 'sf'
## and / or GeoJSON

# df <- data.frame(myId = c(1,1,1,1,1,1,2,2,2),
#                  lineId = c(1,1,1,2,2,2,1,1,1),
#                  y = c(26.774, 18.466, 32.321, 28.745, 29.570, 27.339, 22, 23, 22),
#                  x = c(-80.190, -66.118, -64.757, -70.579, -67.514, -66.668, -50, -49, -51),
#                  colour = c(rep("#00FF0F", 6), rep("#FF00FF", 3)),
#                  stringsAsFactors = FALSE)
#
#
# df

## design philosophy
## - given R objects; it creates the required sfg object
## - then sfc
## - then sf
## ------
## functions to_sfg()
## -

## each loop will get the Range() of indexes which correspond to the point/line/poly
## then we just subset the columns & rows into the requried vec/matrix/list
## then attach attrs/get bbox, etc.

## design
## MULTIPOLYGON (the most complex)
## - requires mp_id, p_id, l_id

## POLYGON
## - requires p_id, l_id

## MULTILINESTRING
## - requires ml_id, l_id

## LINESTRING
## - requires l_id

## MULTIPOINNT
## - requires mpt_id, pt_id

## POINT
## - requires pt_id

## do they need a pt_sequence_order value, or should the input assume the data is ordered?
## - probably best to assume it's ordered
## Then given the type of geometry, it finds the indices which start new points/lines/polygons/multi*
## so multipolygon will be a multi-loop, and checking if previous_id != next_id
## then filling a list/matrix/vector accordingly

## then we can hae a set of header functions to do the construction, taking examples / code from
## geojsonsf - maybe creating a new package - sfheaders ??

## the R api will dispatch given the arguments used

## to convert to an 'sf' object, need to keep the first row of the data.frame which corresponds
## to each new geometry


#' to sfc
#'
#' converts a data.frame to an sfc object
#'
#' @export
to_sfc <- function(
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
  ## TODO
  ## rather than checking which of the parameters are is.null
  ## collect all the parameters into a list, then in C++ work out
  ## which sfg types are required
  ## e.g., similar to
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

  if( !is.null( multipolygon_id ) ) {
    ## must be a multi-polygon
    if(is.null( polygon_id ) | is.null( linestring_id ) ) {
      stop("MULTIPOLYGONs must also define polygon and linestring ids")
    }
    return( obj_to_multipolygon( obj, x, y, z, m, multipolygon_id, polygon_id, linestring_id ) )
  }

  if( !is.null( polygon_id ) ) {
    if( is.null( linestring_id ) ) {
      stop("POLYGONs must also define linestring id")
    }
    return( obj_to_polygon( obj, x, y, z, m, polygon_id, linestring_id ) )
  }

  if( !is.null( multilinestring_id ) ) {
    if( is.null( linestring_id ) ) {
      stop("MULTILINESTRINGs must also define linestring id")
    }
    return( obj_to_multilinestring(obj, x, y, z, m, multilinestring_id, linestring_id ) )
  }

  if( !is.null( linestring_id ) ) {
    return( obj_to_linestring( obj, x, y, z, m, linestring_id ) )
  }

  if( !is.null( multipoint_id ) ) {
    if( is.null( point_id ) ) {
      stop("MULTIPOINTs must also define point_id")
    }
    return( obj_to_multipoint(obj, x, y, z, m, multipoint_id, point_id ) )
  }

}

obj_to_multipolygon <- function(
  obj,
  x,
  y,
  z,
  m,
  multipolygon_id,
  polygon_id,
  line_id
) {

}

obj_to_polygon <- function(
  obj,
  x,
  y,
  z,
  m,
  polygon_id,
  line_id
) {

}

obj_to_multilinestring <- function(
  obj,
  x,
  y,
  z,
  m,
  multiline_id,
  line_id
) {

}

obj_to_linestring <- function(
  obj,
  x,
  y,
  z,
  m,
  line_id
) {

}

obj_to_multipoint <- function(
  obj,
  x,
  y,
  z,
  m,
  multipoint_id,
  point_id
) {

}

obj_to_point <- function(
  obj,
  x,
  y,
  z,
  m,
  point_id
) {

}
