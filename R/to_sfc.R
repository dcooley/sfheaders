
#' to POINTS
#'
#' constructs sfc of POINT objects
#'
#' @examples
#'
#' x <- c(1:3)
#' to_points( x )
#'
#' x <- matrix( c(1:10) , ncol = 2 )
#' to_points( x )
#'
#' x <- setNames( as.data.frame( x ), c("x","y") )
#' to_points( x )
#' to_points( obj = x, x = "x", y = "y" )
#' to_points( obj = x, x = "y", y = "x" )
#'
#' @export
to_points <- function( obj, x = NULL, y = NULL, z = NULL, m = NULL ) {
  geometry_columns <- c(x,y,z,m)
  rcpp_to_points( obj, index_correct( geometry_columns ) )
}
