
name_matcher <- function(x, ...) {
  args <- list(
    obj = NULL
    , x = "x"
    , y = "y"
    , z = "z"
    , m = "m"
    , multipolygon_id = "multipolygon_id"
    , polygon_id = "polygon_id"
    , multilinestring_id = "multilinestring_id"
    , linestring_id = "linestring_id"
    , multipoint_id = "multipoint_id"
    )

  ## return the list args that make sense for this data frame
  args[base::intersect(colnames(x), names(args))]
}
## ensure constructor has access to all required columns for this type
check_columns <- function(x, req_names, fun_name) {
  found <- req_names %in% colnames(x)
  if (sum(found) < length(req_names)) {
    stop(sprintf("'%s()' requires columns:  %s", fun_name,
                 paste(req_names, collapse = ", ")), call. = FALSE)
  }
  invisible(NULL)
}

#' Helper for sf POINT
#'
#' Constructs sf of POINT objects, a helper for [sf_point()] with a simpler
#' syntax.
#'
#' @section Helpers:
#' These are simpler versions of the main functions [sf_point()],
#' [sf_multipoint()], [sf_linestring()], [sf_multilinestring()], [sf_polygon()],
#' and [sf_multipolygon()] for input data frame or matrix that contains columns
#' appropriately of 'x', 'y', 'z', 'm', ' multipolygon_id', polygon_id',
#' 'multilinestring_id', 'linestring_id', 'multipoint_id'.
#'
#' This puts the onus of the naming and identification of entities onto the
#' input data set, rather than when calling the creator function. This has pros
#' and cons, so is not necessarily always 'simpler'. Please choose the
#' appropriate constructor for the context you have. For examples a data frame
#' from the real world with columns 'lon', 'lat', 'line' will be best used with
#'
#' `sf_linestring(df, x = "lon", y = "lat", linestring_id = "line")`
#'
#' whereas a heavy user of sfheaders might always create a data frame with 'x',
#' 'y', 'linestring_id' precisely because they are expecting to call
#' `sf_line(df)` and no further work is required. These are very different
#' contexts and both equally valid.
#'
#' Some columns are mandatory, such as 'x' and 'y' (always), while others depend
#' on the output type where each column for that type is mandatory. The 'z'
#' and/or 'm' values are included for 'XYZ', 'XYM', or 'XYZM' geometry types if
#' and as they are present.
#'
#' In summary these helpers:
#'
#' * do not require arguments declaring column names.
#' * use assumed default column names, with no variation or absence allowed for
#'  a given type.
#' * use `z`, and/or `m` if present.
#' * use `close = FALSE` and `keep = FALSE` same as proper constructors.
#' * unlike [sf_point()] [sf_pt()] does not accept a flat vector for a single
#'  point.
#' * require a matrix or data frame with complete column names.
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
#' x <- matrix( c(1:10) , ncol = 2 , dimnames = list(NULL, c("x", "y")))
#' sf_pt( x )
#'
#' x <- setNames( as.data.frame( x ), c("x","y") )
#' sf_pt( x )
#'
#' # keeping properties
#' x$val <- letters[1:5]
#' (sfx <- sf_pt( x, keep = TRUE ))
#'
#' ## we trivially round-trip with sf_pt()
#' sf_pt(sf_to_df(sfx, fill = TRUE), keep = TRUE)
#' @export
sf_pt <- function(obj, keep = FALSE) {
  check_columns(obj, c("x", "y"), "sf_pt")
  call_args <- name_matcher(obj)
  call_args[c("obj", "keep")] <- list(obj, keep)

  call_args[c("multipolygon_id", "polygon_id",
              "multilinestring_id", "linestring_id", "multipoint_id")] <- NULL
  do.call(sfheaders::sf_point, call_args)
}

#' Helper for sf MULTIPOINT
#'
#' Constructs sf of MULTIPOINT objects, a helper for [sf_multipoint()] with a
#' simpler syntax.
#'
#' @inheritParams sf_point
#' @inheritParams sf_multipoint
#' @inheritSection sf_pt Helpers
#' @inheritSection sfc_point notes
#' @inheritSection sf_point Keeping Properties
#' @return \code{sf} object of MULTIPOINT geometries
#' @examples
#'
#' x <- cbind(x = 1:2, y = 3:4, multipoint_id = 1, ncol = 2 )
#' sf_mpt( x )
#'
#' x <- data.frame( id = 1:2, x = 1:2, y = 2:1, multipoint_id = 1)
#' sf_mpt( x )
#' sf_mpt( x, keep = TRUE)
#' x <- data.frame(multipoint_id = 1:2, id = 1:2, x = 1:2, y = 2:1 )
#' (sfx <- sf_mpt(x))
#'
#' ## we trivially round-trip with sf_mpt()
#' sf_mpt(sf_to_df(sfx))
#' @export
sf_mpt <- function(obj, keep = FALSE, list_columns = NULL) {
  check_columns(obj, c("x", "y", "multipoint_id"), "sf_mpt")
  call_args <- name_matcher(obj)
  call_args[c("obj", "keep","list_columns")] <- list(obj, keep, list_columns)

  call_args[c("multipolygon_id", "polygon_id", "multilinestring_id",
              "linestring_id")] <- NULL
  do.call(sfheaders::sf_multipoint, call_args)
}




#' Helper for sf LINESTRING
#'
#' Constructs sf of LINESTRING objects, a helper for [sf_linestring()] with a
#' simpler syntax.
#'
#' @inheritParams sf_linestring
#' @inheritSection sf_pt Helpers
#' @inheritSection sfc_point notes
#' @inheritSection sf_point Keeping Properties
#' @return \code{sf} object of LINESTRING geometries
#' @examples
#'
#' x <- cbind(x = 1:2, y = 3:4, linestring_id = 1)
#' sf_line( x )
#'
#' x <- data.frame( linestring_id = rep(1:2, each = 2), x = 1:4, y = 4:1 )
#' (sfx <- sf_line( x ))
#'
#' ## we trivially round-trip with sf_line()
#' sf_line(sf_to_df(sfx))
#' @export
sf_line <- function(obj, keep = FALSE, list_columns = NULL ) {
  check_columns(obj, c("x", "y", "linestring_id"), "sf_line")
  call_args <- name_matcher(obj)
  call_args[c("obj", "keep", "list_columns")] <- list(obj, keep, list_columns)

  call_args[c("multipolygon_id", "polygon_id", "multilinestring_id",
              "multipoint_id")] <- NULL
  do.call(sfheaders::sf_linestring, call_args)
}


#' Helper for sf MULTILINESTRING
#'
#' Constructs sf of MULTILINESTRING objects, a helper for [sf_multilinestring()]
#' with a simpler syntax.
#'
#' @inheritParams sf_line
#' @inheritSection sf_pt Helpers
#' @inheritSection sfc_point notes
#' @inheritSection sf_point Keeping Properties
#' @return \code{sf} object of MULTILINESTRING geometries
#' @examples
#'
#' m <- cbind(x = 0, y = 0, multilinestring_id = c(1, 1, 1), linestring_id = 1)
#' sf_mline( m )
#'
#' df <- data.frame(
#'   multilinestring_id = c(1,1,1,1,1,1,1,1,2,2,2,2,2)
#'   ,    linestring_id = c(1,1,1,2,2,3,3,3,1,1,1,2,2)
#'   , x = rnorm(13)
#'   , y = rnorm(13)
#'   , z = rnorm(13)
#'   , m = rnorm(13)
#' )
#'
#' sf_mline( obj = df)
#' sf_mline( obj = df[-6])
#' ## this gives XYZ, not XYM see #64
#' (sfx <- sf_mline( obj = df[-5]))
#'
#' ## we trivially round-trip with sf_mline()
#' sf_mline(sf_to_df(sfx))
#'
#' ## to round-trip with all fields use `fill`, then `keep`
#' sf_mline(sf_to_df(sfx, fill = TRUE), keep = TRUE)
#'
#' @export
sf_mline <- function(obj, keep = FALSE, list_columns = NULL ) {
  check_columns(obj, c("x", "y", "multilinestring_id",
                       "linestring_id"), "sf_mline")
  call_args <- name_matcher(obj)
  call_args[c("obj", "keep", "list_columns")] <- list(obj, keep, list_columns)

  call_args[c("multipolygon_id", "polygon_id", "multipoint_id")] <- NULL
  do.call(sfheaders::sf_multilinestring, call_args)

}

#'Helper for sf POLYGON
#'
#'Constructs sf of POLYGON objects, a helper for [sf_polygon()] with a simpler
#'syntax.
#'
#'@inheritParams sf_polygon
#'@inheritSection sf_pt Helpers
#'@inheritSection sfc_point notes
#'@inheritSection sf_point Keeping Properties
#'@return \code{sf} object of POLYGON geometries
#'
#'@examples
#'
#' m <- matrix(c(0,0,0,0,1,0,0,1,1,0,0,1,0,0,0), ncol = 3, byrow = TRUE,
#'       dimnames = list(NULL, c("x", "y", "z")))
#' m <- cbind(m, polygon_id = 1, linestring_id = 1)
#' sf_poly( m )
#'
#' df <- as.data.frame(m)
#'
#' sf_poly( df)
#'
#' ## order doesn't matter, only the names are used
#' sf_poly(df[c(5, 3, 4, 1, 2)])
#'
#'@export
sf_poly <- function(obj, close = TRUE, keep = FALSE, list_columns = NULL ) {
  check_columns(obj, c("x", "y", "polygon_id", "linestring_id"), "sf_poly")
  call_args <- name_matcher(obj)
  call_args[c("obj", "keep", "close", "list_columns")] <- list(obj, keep, close, list_columns)

  call_args[c("multipolygon_id", "multilinestring_id", "multipoint_id")] <- NULL
  do.call(sfheaders::sf_polygon, call_args)
}


#' Helper for sf MULTIPOLYGON
#'
#' Constructs sf of MULTIPOLYGON objects, a helper for [sf_multipolygon()] with
#' a simpler syntax.
#'
#' @inheritParams sf_polygon
#' @inheritSection sf_pt Helpers
#' @inheritSection sfc_point notes
#' @inheritSection sf_point Keeping Properties
#' @return \code{sf} object of MULTIPOLYGON geometries
#'
#'@examples
#'
#' m <- matrix(c(0,0,0,0,1,0,0,1,1,0,0,1,0,0,0), ncol = 3, byrow = TRUE,
#'       dimnames = list(NULL, c("x", "y", "z")))
#' m <- cbind(m, multipolygon_id = 1, polygon_id = 1, linestring_id = 1)
#' sf_mpoly( m )
#'
#' df <- as.data.frame(m)
#'
#' sf_mpoly( df)
#'
#' ## order doesn't matter, only the names are used
#' sf_mpoly(df[c(6, 5, 3, 4, 1, 2)])
#'
#' @export
sf_mpoly <- function(obj, close = TRUE, keep = FALSE, list_columns = NULL ) {
  check_columns(obj, c("x", "y", "multipolygon_id",
                       "polygon_id", "linestring_id"), "sf_mpoly")
  call_args <- name_matcher(obj)
  call_args[c("obj", "keep", "close", "list_columns")] <- list(obj, keep, close, list_columns)

  call_args[c("multilinestring_id", "multipoint_id")] <- NULL

  do.call(sfheaders::sf_multipolygon, call_args)
}
