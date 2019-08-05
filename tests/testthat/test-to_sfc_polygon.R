context("sfc_POLYGON")

test_that("sfc_polygon works", {

  is_polygon <- function(x) {
    y <- sapply( x, function(y) is.list( unclass( y ) ) )
    z <- sapply( x, function(y) attr( y, "class")[2] == "POLYGON")
    return( all(y) & all(z))
  }

  df <- data.frame(
    p_id = c(1,1,1,1,2,2,2,2)
    , l_id = c(1,1,1,1,1,1,1,1)
    , x = c(1,2,3,1,4,5,6,4)
    , y = c(1,2,3,1,4,5,6,4)
  )

  res <- sfheaders:::rcpp_sfc_polygon( df, c(2,3), c(0), c(1))
  expect_true( is_polygon( res ) )


  res <- sfheaders:::rcpp_sfc_polygon( df, c("x","y"),c("p_id"),c("l_id"))
  expect_true( is_polygon( res ) )

  df <- data.frame(
    p_id = c(1,1,1,1,1,1,1,1)
    , l_id = c(1,1,1,1,1,1,1,1)
    , x = c(1,2,3,1,4,5,6,4)
    , y = c(1,2,3,1,4,5,6,4)
  )

  res <- sfheaders:::rcpp_sfc_polygon( df, c(2,3), c(0), c(1))
  expect_true( is_polygon( res ) )
})
