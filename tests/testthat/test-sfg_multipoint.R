context("sfg_multipoint")

test_that("sfg_MULTIPOINTS returned from various R objects from src", {

  x <- 1L:2L
  pt <- sfheaders:::rcpp_sfg_multipoint( x, NULL, "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "MULTIPOINT", "sfg") )
  r_pt <- sfg_multipoint(x)
  expect_equal( pt, r_pt )

  x <- c(1.2, 2.2)
  pt <- sfheaders:::rcpp_sfg_multipoint( x, NULL, "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "MULTIPOINT", "sfg") )
  r_pt <- sfg_multipoint(x)
  expect_equal( pt, r_pt )

  ## matrix
  x <- matrix(c(0,0), ncol = 2 )
  pt <- sfheaders:::rcpp_sfg_multipoint( x, NULL, "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "MULTIPOINT", "sfg") )
  r_pt <- sfg_multipoint(x)
  expect_equal( pt, r_pt )

  x <- matrix(c(0,0,0), ncol = 3 )
  pt <- sfheaders:::rcpp_sfg_multipoint( x, NULL, "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XYZ", "MULTIPOINT", "sfg") )
  r_pt <- sfg_multipoint(x)
  expect_equal( pt, r_pt )

  x <- matrix(c(0L,0L,0L,0L), ncol = 4 )
  pt <- sfheaders:::rcpp_sfg_multipoint( x, NULL, "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XYZM", "MULTIPOINT", "sfg") )
  r_pt <- sfg_multipoint(x)
  expect_equal( pt, r_pt )

  x <- matrix(c(0,0,0,0), ncol = 2 )
  pt <- sfheaders:::rcpp_sfg_multipoint( x, NULL, "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "MULTIPOINT", "sfg") )
  r_pt <- sfg_multipoint(x)
  expect_equal( pt, r_pt )

  x <- data.frame(x = 0L, y = 0L)
  x <- as.matrix(x)
  pt <- sfheaders:::rcpp_sfg_multipoint( x, c("x","y"), "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "MULTIPOINT", "sfg") )
  r_pt <- sfg_multipoint(obj = x, x = "x", y = "y")
  expect_equal( pt, r_pt )

  x <- data.frame(x = 1.2, y = 2.2)
  x <- as.matrix(x)
  pt <- sfheaders:::rcpp_sfg_multipoint( x, c("x","y"), "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "MULTIPOINT", "sfg") )
  r_pt <- sfg_multipoint(obj = x, x = "x", y = "y")
  expect_equal( pt, r_pt )

  ## data.frame
  x <- data.frame( x = 0, y = 0 )
  pt <- sfheaders:::rcpp_sfg_multipoint( x, NULL, "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "MULTIPOINT", "sfg") )
  r_pt <- sfg_multipoint(x)
  expect_equal( pt, r_pt )

  x <- data.frame( x = 0, y = 0, z = 0 )
  pt <- sfheaders:::rcpp_sfg_multipoint( x, NULL, "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XYZ", "MULTIPOINT", "sfg") )
  r_pt <- sfg_multipoint(x)
  expect_equal( pt, r_pt )

  x <- data.frame( x = 0, y = 0, z = 0, m = 0 )
  pt <- sfheaders:::rcpp_sfg_multipoint( x, NULL, "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XYZM", "MULTIPOINT", "sfg") )
  r_pt <- sfg_multipoint(x)
  expect_equal( pt, r_pt )

  x <- data.frame( x = c(0,0), y = c(0,0) )
  pt <- sfheaders:::rcpp_sfg_multipoint( x, NULL, "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "MULTIPOINT", "sfg"))
  r_pt <- sfg_multipoint(x)
  expect_equal( pt, r_pt )

  x <- data.frame( x = c(0,0), y = c(0,0) )
  pt <- sfheaders:::rcpp_sfg_multipoint( x, c("x","y"), "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "MULTIPOINT", "sfg"))
  r_pt <- sfg_multipoint(obj = x, x = "x", y = "y")
  expect_equal( pt, r_pt )

  x <- data.frame( x = c(0,0), y = c(0,0) )
  x <- as.matrix( x )
  pt <- sfheaders:::rcpp_sfg_multipoint( x, c("x","y"), "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "MULTIPOINT", "sfg"))
  r_pt <- sfg_multipoint(obj = x, x = "x", y = "y")
  expect_equal( pt, r_pt )

  x <- data.frame( x = c(0L), y = c(0L) )
  x <- as.matrix( x )
  pt <- sfheaders:::rcpp_sfg_multipoint( x, c("x","y"), "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "MULTIPOINT", "sfg"))
  r_pt <- sfg_multipoint(obj = x, x = "x", y = "y")
  expect_equal( pt, r_pt )

  x <- data.frame( x = c(0,0), y = c(0,0) )
  pt <- sfheaders:::rcpp_sfg_multipoint( x, c(0,1), "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "MULTIPOINT", "sfg"))
  r_pt <- sfg_multipoint(obj = x, x = 1, y = 2)
  expect_equal( pt, r_pt )

  x <- data.frame( x = c(0,0), y = c(0,0) )
  x <- as.matrix( x )
  pt <- sfheaders:::rcpp_sfg_multipoint( x, c(0,1), "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "MULTIPOINT", "sfg"))
  r_pt <- sfg_multipoint(obj = x, x = 1, y = 2)
  expect_equal( pt, r_pt )

  x <- data.frame( x = c(0L), y = c(0L) )
  x <- as.matrix( x )
  pt <- sfheaders:::rcpp_sfg_multipoint( x, c(0,1), "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "MULTIPOINT", "sfg"))
  r_pt <- sfg_multipoint(obj = x, x = 1, y = 2)
  expect_equal( pt, r_pt )

})

test_that("vectorised version works",{

  is_multipoint <- function(x) {
    y <- is.matrix(unclass(x))
    z <- attr( x, "class")[2] == "MULTIPOINT"
    return( all(y) & all(z))
  }

  m1 <- matrix(1:3, ncol = 3)
  m2 <- matrix(1:3, ncol = 3)
  lst <- list( m1, m2 )
  res <- sfheaders:::rcpp_sfg_multipoints( lst, "" )
  expect_true( all( sapply( res, is_multipoint ) ) )

})



