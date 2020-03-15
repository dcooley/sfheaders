
name_matcher <- function(x, close = FALSE, keep = FALSE, ...) {
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
               point_id = "point_id",
               close = close,
               keep = keep)
  ## return the list args that make sense for this data frame
  args[base::intersect(names(x), names(args))]
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
  ## multipolygon, polygon, linestring
  stopifnot(all(c("x", "y", "multipolygon_id", "polygon_id", "linestring_id") %in% names(obj)))
  call_args <- name_matcher(obj)
  call_args[["obj"]] <- obj
  do.call(sfheaders::sf_multipolygon, call_args)
}
sf_poly <- function(obj, ...) {
  sfheaders::sf_polygon(x,
                        x = "x", y = "y",
                        linestring_id = "linestring_id",
                        polygon_id = "polygon_id")
}
sf_mline <- function(obj, ...) {
  sfheaders::sf_multilinestring(x,
                                x = "x", y = "y",
                                linestring_id = "linestring_id",
                                multilinestring_id = "multilinestring_id")
}
sf_line <- function(obj, ...) {
  sfheaders::sf_linestring(x,
                           x = "x", y = "y",
                           linestring_id = "linestring_id")
}
sf_mpt <- function(obj, ...) {
  sfheaders::sf_multipoint(x,
                           x = "x", y = "y",
                           point_id = "point_id",
                           multipoint_id = "multipoint_id")
}
sf_p <- function(obj, ...) {
  sfheaders::sf_point(x,
                      x = "x", y = "y",
                      point_id = "point_id")
}
