#' sfc cast
#'
#' convert the input \code{sfc} to a different geometry
#'
#' @param sfc geometry object to convert to a different geometry
#' @param to the geometry to convert to.
#' @param close logical indicating if polygons should be closed
#'
#' @examples
#' df <- data.frame(
#'  id1 = c(1,1,1,1,1,1,1,1,2,2,2,2)
#'  , id2 = c(1,1,1,1,2,2,2,2,1,1,1,1)
#'  , x = c(0,0,1,1,1,1,2,2,3,4,4,3)
#'  , y = c(0,1,1,0,1,2,2,1,3,3,4,4)
#' )
#'
#' pt <- sfc_point(obj = df, x = "x", y = "y", z = "id1")
#' mpt <- sfc_multipoint(obj = df, x = "x", y = "y", multipoint_id = "id1")
#' ls <- sfc_linestring(obj = df, x = "x", y = "y", linestring_id = "id1")
#' mls <- sfc_multilinestring(obj = df, x = "x", y = "y", multilinestring_id = "id1")
#' p <- sfc_polygon(
#'   obj = df
#'   , x = "x"
#'   , y = "y"
#'   , polygon_id = "id1"
#'   , linestring_id = "id2"
#'   , close = FALSE
#'   )
#' mp <- sfc_multipolygon(
#'   obj = df
#'   , x = "x"
#'   , y = "y"
#'   , multipolygon_id = "id1"
#'   , linestring_id = "id2"
#'   , close = FALSE
#' )
#'
#' sfc_cast( pt, "LINESTRING" )
#' sfc_cast( mpt, "POLYGON" )
#' sfc_cast( ls, "POINT" )
#' sfc_cast( mls, "MULTIPOLYGON" )
#' sfc_cast( p, "POINT" )
#' sfc_cast( mp, "LINESTRING" )
#'
#' @export
sfc_cast <- function( sfc, to, close = TRUE ) {
  to <- toupper( to )
  return( rcpp_cast_sfc( sfc, to, close ) )
}


#' sf cast
#'
#'  convert the input \code{sf} to a different geometry
#'
#' @inheritParams sfc_cast
#' @param sf object to convert
#'
#' @examples
#'
#' df <- data.frame(
#'  id1 = c(1,1,1,1,1,1,1,1,2,2,2,2)
#'  , id2 = c(1,1,1,1,2,2,2,2,1,1,1,1)
#'  , x = c(0,0,1,1,1,1,2,2,3,4,4,3)
#'  , y = c(0,1,1,0,1,2,2,1,3,3,4,4)
#' )
#'
#' pt <- sf_point(obj = df, x = "x", y = "y", z = "id1")
#' mpt <- sf_multipoint(obj = df, x = "x", y = "y", multipoint_id = "id1")
#' ls <- sf_linestring(obj = df, x = "x", y = "y", linestring_id = "id1")
#' mls <- sf_multilinestring(obj = df, x = "x", y = "y", multilinestring_id = "id1")
#' p <- sf_polygon(
#'   obj = df
#'   , x = "x"
#'   , y = "y"
#'   , polygon_id = "id1"
#'   , linestring_id = "id2"
#'   , close = FALSE
#'   )
#' mp <- sf_multipolygon(
#'   obj = df
#'   , x = "x"
#'   , y = "y"
#'   , multipolygon_id = "id1"
#'   , linestring_id = "id2"
#'   , close = FALSE
#'   )
#'
#' sf_cast( pt, "LINESTRING" )
#' sf_cast( mpt, "POLYGON" )
#' sf_cast( ls, "POINT" )
#' sf_cast( mls, "MULTIPOLYGON" )
#' sf_cast( p, "POINT" )
#' sf_cast( mp, "LINESTRING" )
#'
#'
#' @export
sf_cast <- function( sf, to, close = TRUE ) {
  to <- toupper( to )
  return( rcpp_cast_sf( sf, to, close ) )
}

