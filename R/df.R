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
#' @param fill logical indicating if the resulting data.frame should be filled
#' with the data columns from the sf object. If \code{TRUE}, each row of data will
#' be replicated for every coordiante in every geometry.
#'
#' @export
sf_to_df <- function( sf, fill = FALSE ) return( rcpp_sf_to_df( sf, fill ) )
