

#' sfc cast
#'
#'
#' @export
sfc_cast <- function( sfc, to, close = TRUE ) {
  to <- toupper( to )
  return( rcpp_cast_sfc( sfc, to, close ) )
}


#' sf cast
#'
#'
#' @export
sf_cast <- function( sf, to, close = TRUE ) {
  to <- toupper( to )
  return( rcpp_cast_sf( sf, to, close ) )
}
