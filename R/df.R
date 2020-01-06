#' sfg to df
#'
#' Converts an sfg object to a data.frame
#'
#' @param sfg sfg object
#'
#' @examples
#' sfg <- sfg_point( obj = c(1,2) )
#' df <- sfg_to_df( sfg )
#'
#' m <- cbind( matrix( 1:24, ncol = 2 ), c(rep(1, 6), rep(2, 6) ) )
#' sfg <- sfg_polygon( obj = m, x = 1, y = 2, linestring_id = 3 )
#' df <- sfg_to_df( sfg )
#'
#'
#' @export
sfg_to_df <- function( sfg ) return( rcpp_sfg_to_df( sfg ) )


#' sfc to df
#'
#' Converts an sfc object a to data.frame
#'
#' @param sfc sfc object
#'
#' @examples
#'
#' x <- matrix( c(1:16), ncol = 2 )
#' sfc <- sfc_linestring( x )
#' df <- sfc_to_df( sfc )
#'
#' df <- data.frame(
#' ml_id = c(1,1,1,1,1,1,1,1,2,2,2,2,2)
#' , l_id = c(1,1,1,2,2,3,3,3,1,1,1,2,2)
#' , x = rnorm(13)
#' , y = rnorm(13)
#' , z = rnorm(13)
#' , m = rnorm(13)
#' )
#' sfc <- sfc_multilinestring( obj = df, multilinestring_id = "ml_id", linestring_id = "l_id" )
#'
#' df <- sfc_to_df( sfc )
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
#' @examples
#'
#' df <- data.frame(
#' ml_id = c(1,1,1,1,1,1,1,1,1,2,2,2,2,2,2)
#' , l_id = c(1,1,1,2,2,2,3,3,3,1,1,1,2,2,2)
#' , x = rnorm(15)
#' , y = rnorm(15)
#' , z = rnorm(15)
#' , m = rnorm(15)
#' )
#'
#' sf <- sf_polygon( obj = df, polygon_id = "ml_id", linestring_id = "l_id" )
#' df <- sf_to_df( sf )
#'
#' ## with associated ata
#' sf$val1 <- c("a","b")
#' sf$val2 <- c(1L, 2L)
#'
#' df <- sf_to_df( sf, fill = TRUE )
#'
#' @export
sf_to_df <- function( sf, fill = FALSE ) return( rcpp_sf_to_df( sf, fill ) )
