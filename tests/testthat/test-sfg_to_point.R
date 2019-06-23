context("sfg_to_point")

test_that("sfg_POINTS returned from various R objects from src", {

  ## vectors
  x <- c(0,0)
  pt <- sfheaders:::rcpp_to_point( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "POINT", "sfg") )

  x <- c(0,0,0)
  pt <- sfheaders:::rcpp_to_point( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XYZ", "POINT", "sfg") )

  x <- c(0,0,0,0)
  pt <- sfheaders:::rcpp_to_point( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XYZM", "POINT", "sfg") )

  ## matrix
  x <- matrix(c(0,0), ncol = 2 )
  pt <- sfheaders:::rcpp_to_point( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "POINT", "sfg") )

  x <- matrix(c(0,0,0), ncol = 3 )
  pt <- sfheaders:::rcpp_to_point( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XYZ", "POINT", "sfg") )

  x <- matrix(c(0L,0L,0L,0L), ncol = 4 )
  pt <- sfheaders:::rcpp_to_point( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XYZM", "POINT", "sfg") )

  x <- matrix(c(0,0,0,0), ncol = 2 )
  expect_error( sfheaders:::rcpp_to_point( x, NULL ) )

  ## data.frame
  x <- data.frame( x = 0, y = 0 )
  pt <- sfheaders:::rcpp_to_point( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "POINT", "sfg") )

  x <- data.frame( x = 0, y = 0, z = 0 )
  pt <- sfheaders:::rcpp_to_point( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XYZ", "POINT", "sfg") )

  x <- data.frame( x = 0, y = 0, z = 0, m = 0 )
  pt <- sfheaders:::rcpp_to_point( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XYZM", "POINT", "sfg") )

  x <- data.frame( x = c(0,0), y = c(0,0) )
  expect_error( sfheaders:::rcpp_to_point( x, NULL ) )

})







