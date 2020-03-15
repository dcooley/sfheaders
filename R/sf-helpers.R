
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
               multipoint_id = "multipoint_id",
               point_id = "point_id")
  ## return the list args that make sense for this data frame
  args[base::intersect(colnames(x), names(args))]
}


#' Helper functions to make sf
#'
#' These are simpler versions of the sfheaders creators:
#'
#' less strict about arguments
#' assuming default argument names
#' using z, m if present
#' using `close = FALSE` as default
#' using `keep = FALSE` same as proper creators
#' we don't allow partial name matching
sf_mpoly <- function(obj, close = FALSE, keep = FALSE, ...) {
  ## determine minimum names required
  stopifnot(all(c("x", "y", "multipolygon_id", "polygon_id", "linestring_id") %in% colnames(obj)))
  call_args <- name_matcher(obj)
  call_args[c("obj", "keep", "close")] <- list(obj, keep, close)
  ## needs rethinking
  call_args[c("multipoint_id")] <- NULL

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
sf_pt <- function(obj, keep = FALSE, ...) {
  stopifnot(all(c("x", "y") %in% colnames(obj)))
  call_args <- name_matcher(obj)
  call_args[c("obj", "keep")] <- list(obj, keep)
  ## needs rethinking
  call_args[c("multipolygon_id", "polygon_id", "multilinestring_id", "linestring_id", "multipoint_id")] <- NULL
  do.call(sfheaders::sf_point, call_args)
}
