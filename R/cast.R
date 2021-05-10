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
#' @param list_columns vector of column names or indexes. List columns are columns
#' of data where there is a value corresponding to each coordinate in the geometry (sfc).
#' List columns get cast with the geometries.
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
#' ## List Columns
#'
#' df <- data.frame(
#'  id1 = c(1,1,1,1,1,1,1,1,2,2,2,2)
#'  , id2 = c(1,1,1,1,2,2,2,2,1,1,1,1)
#'  , x = c(0,0,1,1,1,1,2,2,3,4,4,3)
#'  , y = c(0,1,1,0,1,2,2,1,3,3,4,4)
#' )
#'
#' ## Add a column where each value is an attribute of each coordinate
#' df$val <- letters[1:nrow(df)]
#'
#' ## Make a multipolygon, and specify `val` as a list_column
#' mp <- sf_multipolygon(
#'   obj = df
#'   , x = "x"
#'   , y = "y"
#'   , multipolygon_id = "id1"
#'   , linestring_id = "id2"
#'   , list_column = "val"
#'   , keep = TRUE
#'   , close = FALSE
#'   )
#'
#' ## The 'val' attributes follow the same structure as the geometry column
#' ## So each 'val' corresponds to a single coordinate in the geometry
#' str( mp )
#'
#' ## specifying `list_columns = "val"` when casting will retain the association
#' ## between the 'val' attribute and each coordinate.
#' res <- sf_cast( mp, "LINESTRING", list_columns = "val" )
#'
#' ## The 'val' attribute still follows the same structure as the geometry column
#' str( res )
#'
#' @export
sf_cast <- function( sf, to, close = TRUE, list_columns = NULL ) {
  to <- toupper( to )
  list_columns <- index_correct( list_columns )
  return( rcpp_cast_sf( sf, to, list_columns, close ) )
}

