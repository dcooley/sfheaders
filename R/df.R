#' sfg_to_df
#'
#' Converts sfg objects to data.frames
#'
#' @export
#'
sfg_to_df <- function( sfg ) return( rcpp_sfg_to_df( sfg ) )
