

#' sfc cast
#'
#'
#' @export
sfc_cast <- function( sfc, to, close = TRUE ) {
  to <- toupper( to )
  return( sfheaders:::rcpp_cast_sfc( sfc, to, close ) )
}
