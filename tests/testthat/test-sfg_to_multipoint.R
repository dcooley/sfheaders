context("sfg_multipoint")

test_that("sfg_MULTIPOINTS returned from various R objects from src", {

  ## matrix
  x <- matrix(c(0,0), ncol = 2 )
  pt <- sfheaders:::rcpp_sfg_multipoint( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "MULTIPOINT", "sfg") )
  r_pt <- sfg_multipoint(x)
  expect_equal( pt, r_pt )

  x <- matrix(c(0,0,0), ncol = 3 )
  pt <- sfheaders:::rcpp_sfg_multipoint( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XYZ", "MULTIPOINT", "sfg") )
  r_pt <- sfg_multipoint(x)
  expect_equal( pt, r_pt )

  x <- matrix(c(0L,0L,0L,0L), ncol = 4 )
  pt <- sfheaders:::rcpp_sfg_multipoint( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XYZM", "MULTIPOINT", "sfg") )
  r_pt <- sfg_multipoint(x)
  expect_equal( pt, r_pt )

  x <- matrix(c(0,0,0,0), ncol = 2 )
  pt <- sfheaders:::rcpp_sfg_multipoint( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "MULTIPOINT", "sfg") )
  r_pt <- sfg_multipoint(x)
  expect_equal( pt, r_pt )

  ## data.frame
  x <- data.frame( x = 0, y = 0 )
  pt <- sfheaders:::rcpp_sfg_multipoint( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "MULTIPOINT", "sfg") )
  r_pt <- sfg_multipoint(x)
  expect_equal( pt, r_pt )

  x <- data.frame( x = 0, y = 0, z = 0 )
  pt <- sfheaders:::rcpp_sfg_multipoint( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XYZ", "MULTIPOINT", "sfg") )
  r_pt <- sfg_multipoint(x)
  expect_equal( pt, r_pt )

  x <- data.frame( x = 0, y = 0, z = 0, m = 0 )
  pt <- sfheaders:::rcpp_sfg_multipoint( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XYZM", "MULTIPOINT", "sfg") )
  r_pt <- sfg_multipoint(x)
  expect_equal( pt, r_pt )

  x <- data.frame( x = c(0,0), y = c(0,0) )
  pt <- sfheaders:::rcpp_sfg_multipoint( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "MULTIPOINT", "sfg"))
  r_pt <- sfg_multipoint(x)
  expect_equal( pt, r_pt )

})





