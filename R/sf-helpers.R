
name_matcher <- function(x, ...) {
  args <- list(obj = NULL,
               x = "x",
               y = "y",
               z = "z",
               m = "m",
               multipolygon_id = "multipolygon_id",
               polygon_id = "polygon_id",
               multilinestring_id = "multilinestring_id",
               linestring_id = "linestring_id",
               multipoint_id = "multipoint_id")
  ## return the list args that make sense for this data frame
  args[base::intersect(colnames(x), names(args))]
}


#' Helper for sf POINT
#'
#' Constructs sf of POINT objects, a helper for [sf_point()] with a simpler syntax.
#'
#' These are simpler versions of the main functions [sf_point()], [sf_multipoint()],
#' [sf_linestring()], [sf_multilinestring()], [sf_polygon()], and [sf_multipolygon()] for
#' input data frame or matrix that contains columns appropriately of 'x', 'y', 'z', 'm',
#' ' multipolygon_id', polygon_id', 'multilinestring_id', 'linestring_id', 'multipoint_id'.
#' Some columns are mandatory, such as 'x' and 'y' (always), while others depend on the output
#' type where each column for that type is mandatory. The 'z' and/or 'm' values are included
#' for 'XYZ', 'XYM', or 'XYZM' geometry types if and as they are present.
#'
#' In summary these helpers:
#'
#' * not strict about arguments for column names.
#' * use assumed default column names, with no variation or absence allowed for a given type.
#' * use `z`, and/or `m` if present.
#' * use `close = FALSE` as default
#' * use `keep = FALSE` same as proper creators
#' * unlike [sf_point()] [sf_pt()] does not accept a flat vector
#' * require a matrix or data frame with complete column names
#'
#' None of the helpers allow partial name matching for column names.
#'
#' @inheritParams sf_point
#' @inheritSection sfc_point notes
#' @inheritSection sf_point Keeping Properties
#' @return \code{sf} object of POINT geometries
#' @examples
#'
#' x <- cbind(x = 1, y= 3)
#' sf_pt( x )
#' sf_pt(cbind(x, z = 2))
#'
#' x <- matrix( c(1:10) , ncol = 2 )
#' sf_pt( x )
#'
#' x <- setNames( as.data.frame( x ), c("x","y") )
#' sf_point( x )
#' sf_point( obj = x, x = "x", y = "y" )
#' sf_point( obj = x, x = "y", y = "x" )
#'
#' # keeping properties
#' x$val <- letters[1:5]
#' sf_point( x, x = "x", y = "y", keep = TRUE )
#'
#' @export
sf_pt <- function(obj, keep = FALSE, ...) {
  stopifnot(all(c("x", "y") %in% colnames(obj)))
  call_args <- name_matcher(obj)
  call_args[c("obj", "keep")] <- list(obj, keep)
  ## needs rethinking
  call_args[c("multipolygon_id", "polygon_id", "multilinestring_id", "linestring_id", "multipoint_id")] <- NULL
  do.call(sfheaders::sf_point, call_args)
}


sf_mpoly <- function(obj, close = FALSE, keep = FALSE, ...) {
  ## determine minimum names required
  stopifnot(all(c("x", "y", "multipolygon_id", "polygon_id", "linestring_id") %in% colnames(obj)))
  call_args <- name_matcher(obj)
  call_args[c("obj", "keep", "close")] <- list(obj, keep, close)
  ## needs rethinking
  call_args[c("multilinestring_id", "multipoint_id")] <- NULL

  do.call(sfheaders::sf_multipolygon, call_args)
}
sf_poly <- function(obj, close = FALSE, keep = FALSE, ...) {
  stopifnot(all(c("x", "y", "polygon_id", "linestring_id") %in% colnames(obj)))
  call_args <- name_matcher(obj)
  call_args[c("obj", "keep", "close")] <- list(obj, keep, close)
  ## needs rethinking
  call_args[c("multipolygon_id", "multilinestring_id", "multipoint_id")] <- NULL
  do.call(sfheaders::sf_polygon, call_args)
}
sf_mline <- function(obj, keep = FALSE, ...) {
  stopifnot(all(c("x", "y", "multilinestring_id", "linestring_id") %in% colnames(obj)))
  call_args <- name_matcher(obj)
  call_args[c("obj", "keep")] <- list(obj, keep)
  ## needs rethinking
  call_args[c("multipolygon_id", "polygon_id", "multipoint_id")] <- NULL
  do.call(sfheaders::sf_multilinestring, call_args)

}
sf_line <- function(obj, keep = FALSE, ...) {
  stopifnot(all(c("x", "y", "linestring_id") %in% colnames(obj)))
  call_args <- name_matcher(obj)
  call_args[c("obj", "keep")] <- list(obj, keep)
  ## needs rethinking
  call_args[c("multipolygon_id", "polygon_id", "multilinestring_id", "multipoint_id")] <- NULL
  do.call(sfheaders::sf_linestring, call_args)
}
sf_mpt <- function(obj, keep = FALSE, ...) {
  stopifnot(all(c("x", "y", "multipoint_id") %in% colnames(obj)))
  call_args <- name_matcher(obj)
  call_args[c("obj", "keep")] <- list(obj, keep)
  ## needs rethinking
  call_args[c("multipolygon_id", "polygon_id", "multilinestring_id", "linestring_id")] <- NULL
  do.call(sfheaders::sf_multipoint, call_args)
}

