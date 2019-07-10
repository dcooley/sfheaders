context("sfg_linestring")

test_that("sfg_LINESTRINGS returned from various R objects from src", {

  ## matrix
  x <- matrix(c(0,0), ncol = 2 )
  pt <- sfheaders:::rcpp_sfg_linestring( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "LINESTRING", "sfg") )
  r_pt <- sfg_linestring(x)
  expect_equal( pt, r_pt )

  x <- matrix(c(0,0,0), ncol = 3 )
  pt <- sfheaders:::rcpp_sfg_linestring( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XYZ", "LINESTRING", "sfg") )
  r_pt <- sfg_linestring(x)
  expect_equal( pt, r_pt )

  x <- matrix(c(0L,0L,0L,0L), ncol = 4 )
  pt <- sfheaders:::rcpp_sfg_linestring( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XYZM", "LINESTRING", "sfg") )
  r_pt <- sfg_linestring(x)
  expect_equal( pt, r_pt )

  x <- matrix(c(0,0,0,0), ncol = 2 )
  pt <- sfheaders:::rcpp_sfg_linestring( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "LINESTRING", "sfg") )
  r_pt <- sfg_linestring(x)
  expect_equal( pt, r_pt )

  ## data.frame
  x <- data.frame( x = 0, y = 0 )
  pt <- sfheaders:::rcpp_sfg_linestring( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "LINESTRING", "sfg") )
  r_pt <- sfg_linestring(x)
  expect_equal( pt, r_pt )

  x <- data.frame( x = 0, y = 0, z = 0 )
  pt <- sfheaders:::rcpp_sfg_linestring( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XYZ", "LINESTRING", "sfg") )
  r_pt <- sfg_linestring(x)
  expect_equal( pt, r_pt )

  x <- data.frame( x = 0, y = 0, z = 0, m = 0 )
  pt <- sfheaders:::rcpp_sfg_linestring( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XYZM", "LINESTRING", "sfg") )
  r_pt <- sfg_linestring(x)
  expect_equal( pt, r_pt )

  x <- data.frame( x = c(0,0), y = c(0,0) )
  pt <- sfheaders:::rcpp_sfg_linestring( x, NULL )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "LINESTRING", "sfg"))
  r_pt <- sfg_linestring(x)
  expect_equal( pt, r_pt )

  ## using column names
  x <- data.frame( x = c(0,0), y = c(0,0) )
  pt <- sfheaders:::rcpp_sfg_linestring( x, c("x","y") )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "LINESTRING", "sfg"))
  ## TODO
  ## - names??
  # r_pt <- sfg_linestring( x )
  # expect_equal( pt, r_pt )

  x <- matrix(c(0L,1L,2L,3L), ncol = 4 )
  pt <- sfheaders:::rcpp_sfg_linestring( x, c(0,2) )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "LINESTRING", "sfg") )
  # r_pt <- sfg_linestring(x)
  # expect_equal( pt, r_pt )

  expect_equal( pt[,1], 0 )
  expect_equal( pt[,2], 2 )

})





