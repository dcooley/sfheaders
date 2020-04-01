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
paste_index <- function(x) paste0(sort(x), collapse = "")
gtype_matcher <- function(x) {
  elements <- c("multipolygon_id", "polygon_id",
                "multilinestring_id", "linestring_id",
                "multipoint_id")


  # if (!any(elements %in% x)) {
  #   return("POINT")
  # }
  if (all(elements[c(1, 2, 4)] %in% x)) {
    return("MULTIPOLYGON")
  }
  if (all(elements[c(2, 4)] %in% x)) {
    return("POLYGON")
  }
  if (all(elements[c(3, 4)] %in% x)) {
    return("MULTILINESTRING")
  }
  if ("linestring_id" %in% x) {
    return("LINESTRING")
  }

  ## not sure, preference this or not? (probably not, put this last)
  if ("multipoint_id" %in% x) {
    return("MULTIPOINT")
  }
  ## only need x,y for POINT
  if (all(c("x", "y") %in% x)) {
    return("POINT")
  }
  stop(sprintf("cannot determine geometry type from %s", sort(x)))
}
gdim_matcher <- function(x) {
  elements <- c("x", "y", "z", "m")
  enc <- paste_index(match(unique(x), elements))
  err <- "need at least columns x, y"
  if (nchar(enc) < 1) stop(err)
  switch(enc,
         "12" = "XY",
         "123" = "XYZ",
         "1234" = "XYZM",
         "124" = "XYM",
         "1" = stop(err), "2" = stop(err), "3" = stop(err), "4" = stop(err), "34" = stop(err),
         stop(err))
}
construct_matcher <- function(x) {
  switch(x,
         "MULTIPOLYGON" = sf_mpoly,
         "POLYGON" = sf_poly,
         "MULTILINESTRING" = sf_mline,
         "LINESTRING" = sf_line,
         "MULTIPOINT" = sf_mpt,
         "POINT" = sf_pt
  )
}


#' Construct sf object
#'
#' Construct sf based on presence of column names.
#'
#' The geometric type (XY, XYZ, XYZM, XYM) is taken from the presence
#' of "x", "y" (mandatory), and  "z" and/or "m".
#'
#' The sf column-vector type is taken from the presence of "multipolygon_id",
#' "polygon_id", "multilinestring_id", "linestring_id", "multipoint_id".
#' If none of these are present "POINT" is chosen.
#' @param x data frame
#' @param debug
#'
#' @return sf data frame
#' @export
#'
#' @examples
#' df <- data.frame(
#'   ml_id = c(1,1,1,1,1,1,1,1,2,2,2,2,2)
#'   , l_id = c(1,1,1,2,2,3,3,3,1,1,1,2,2)
#'   , lon = rnorm(13)
#'   , lat = rnorm(13)
#'   , zz = rnorm(13)
#'   , mm = rnorm(13)
#' )
#'
#' library(dplyr); library(sf)
#' ## specify multlinestring
#' df %>% transmute(x = lon, y = lat, m = mm,
#'                 multilinestring_id = ml_id,
#'                 linestring_id = l_id) %>% to_sf()
#'
#' ## round trip
#' sf_to_df(silicate::minimal_mesh) %>% to_sf()
#'
#' ## linestring (have to hack, it's not realistic)
#' sf_to_df(silicate::minimal_mesh) %>%
#' transmute(m = 1, y, x, linestring_id) %>%
#'  arrange(linestring_id) %>% ## needed because we are hacking mpoly, not realistic necessarily
#' to_sf()
#'
#' ## we get POINT
#' sf_to_df(silicate::minimal_mesh) %>% transmute(y, x) %>%
#' to_sf()
#'
#' ## MULTIPOINT
#' sf_to_df(silicate::minimal_mesh) %>%
#'  transmute(x, y, multipoint_id = row_number() > 3, polygon_id) %>% ## need linestring also to get polygon
#'  to_sf()
#'
#'
to_sf <- function(x, debug = TRUE) {
  gtype <- gtype_matcher(names(x))
  if (debug) {
    print(gtype)
    print(gdim_matcher(names(x)))

  }
  constructor <- construct_matcher(gtype)
  constructor(x)
}


