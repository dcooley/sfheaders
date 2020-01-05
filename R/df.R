#' sfg to df
#'
#' Converts an sfg object to a data.frame
#'
#' @param sfg sfg object
#'
#' @export
sfg_to_df <- function( sfg ) return( rcpp_sfg_to_df( sfg ) )


#' sfc to df
#'
#' Converts an sfc object a to data.frame
#'
#' @param sfc sfc object
#'
#' @export
sfc_to_df <- function( sfc ) return( rcpp_sfc_to_df( sfc ) )


#' sf to df
#'
#' Converts an sf object ot a data.frame
#'
#' @param sf sf object
#'
#' @export
sf_to_df <- function( sf ) return( rcpp_sf_to_df( sf ) )
