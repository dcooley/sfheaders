#' sfg_to_df
#'
#' Converts an sfg object to a data.frame
#'
#' @param sfg sfg object
#'
#' @export
sfg_to_df <- function( sfg ) return( rcpp_sfg_to_df( sfg ) )


#' sfc_to_df
#'
#' Converts an sfc object a to data.frame
#'
#' @param sfc sfc object
#'
#' @export
sfc_to_df <- function( sfc ) return( rcpp_sfc_to_df( sfc ) )


