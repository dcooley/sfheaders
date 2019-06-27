
#' to POINTS
#'
#' constructs sfc of POINT objects
#'
#' @export
to_points <- function( obj ) {
  rcpp_to_points( obj )
}
