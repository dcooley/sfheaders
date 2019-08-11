context("sfg_point")

test_that("sfg_POINTS returned from various R objects from src", {

  ## vectors
  x <- c(0L,0L)
  pt <- sfheaders:::rcpp_sfg_point( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "POINT", "sfg") )
  r_pt <- sfg_point(x)
  expect_equal( pt, r_pt )

  x <- c(0,0,0)
  pt <- sfheaders:::rcpp_sfg_point( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XYZ", "POINT", "sfg") )
  r_pt <- sfg_point(x)
  expect_equal( pt, r_pt )

  x <- c(0,0,0,0)
  pt <- sfheaders:::rcpp_sfg_point( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XYZM", "POINT", "sfg") )
  r_pt <- sfg_point(x)
  expect_equal( pt, r_pt )

  ## matrix
  x <- matrix(c(0,0), ncol = 2 )
  pt <- sfheaders:::rcpp_sfg_point( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "POINT", "sfg") )
  r_pt <- sfg_point(x)
  expect_equal( pt, r_pt )

  x <- matrix(c(0,0,0), ncol = 3 )
  pt <- sfheaders:::rcpp_sfg_point( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XYZ", "POINT", "sfg") )
  r_pt <- sfg_point(x)
  expect_equal( pt, r_pt )

  x <- matrix(c(0L,0L,0L,0L), ncol = 4 )
  pt <- sfheaders:::rcpp_sfg_point( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XYZM", "POINT", "sfg") )
  r_pt <- sfg_point(x)
  expect_equal( pt, r_pt )

  x <- matrix(c(0,0,0,0), ncol = 2 )
  expect_error( sfheaders:::rcpp_sfg_point( x, NULL ) )

  ## data.frame
  x <- data.frame( x = 0, y = 0 )
  pt <- sfheaders:::rcpp_sfg_point( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "POINT", "sfg") )
  r_pt <- sfg_point(x)
  expect_equal( pt, r_pt )

  x <- data.frame( x = 0, y = 0 )
  pt <- sfheaders:::rcpp_sfg_point( x, c(0L,1L) )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "POINT", "sfg") )
  r_pt <- sfg_point(x)
  expect_equal( pt, r_pt )

  x <- data.frame( x = 0, y = 0 )
  pt <- sfheaders:::rcpp_sfg_point( x, c("x","y") )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "POINT", "sfg") )
  r_pt <- sfg_point(x)
  expect_equal( pt, r_pt )

  x <- data.frame( x = 0, y = 0, z = 0 )
  pt <- sfheaders:::rcpp_sfg_point( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XYZ", "POINT", "sfg") )
  r_pt <- sfg_point(x)
  expect_equal( pt, r_pt )

  x <- data.frame( x = 0, y = 0, z = 0, m = 0 )
  pt <- sfheaders:::rcpp_sfg_point( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XYZM", "POINT", "sfg") )
  r_pt <- sfg_point(x)
  expect_equal( pt, r_pt )


  x <- matrix(1:2, ncol = 2)
  pt <- sfheaders:::rcpp_sfg_point( x, c(0L,1L) )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "POINT", "sfg") )
  r_pt <- sfg_point(x)
  expect_equal( pt, r_pt )

  x <- matrix(c(1.2,2), ncol = 2)
  pt <- sfheaders:::rcpp_sfg_point( x, c(0L,1L) )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "POINT", "sfg") )
  r_pt <- sfg_point(x)
  expect_equal( pt, r_pt )

  x <- data.frame( x = c(0,0), y = c(0,0) )
  expect_error( sfheaders:::rcpp_sfg_point( x, NULL ) )

})


test_that("vectorised version works",{

  is_point <- function(x) {
    y <- is.vector(unclass(x))
    z <- attr( x, "class")[2] == "POINT"
    return( all(y) & all(z) )
  }

  m1 <- matrix(1:3, ncol = 3)
  m2 <- matrix(1:3, ncol = 3)
  lst <- list( m1, m2 )
  res <- sfheaders:::rcpp_sfg_points( lst )
  expect_true( all( sapply( res, is_point ) ) )

})




