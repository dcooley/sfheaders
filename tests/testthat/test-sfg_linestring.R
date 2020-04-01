context("sfg_linestring")

test_that("sfg_LINESTRINGS returned from various R objects from src", {

  ## vector
  x <- 1L:2L
  pt <- sfheaders:::rcpp_sfg_linestring( x, NULL, "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "LINESTRING", "sfg") )

  x <- c(1.2, 1.3)
  pt <- sfheaders:::rcpp_sfg_linestring( x, NULL, "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "LINESTRING", "sfg") )

  ## matrix
  x <- matrix(c(0,0), ncol = 2 )
  pt <- sfheaders:::rcpp_sfg_linestring( x, NULL, "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "LINESTRING", "sfg") )
  r_pt <- sfg_linestring(x)
  expect_equal( pt, r_pt )

  x <- matrix(c(0,0,0), ncol = 3 )
  pt <- sfheaders:::rcpp_sfg_linestring( x, NULL, "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XYZ", "LINESTRING", "sfg") )
  r_pt <- sfg_linestring(x)
  expect_equal( pt, r_pt )

  x <- matrix(c(0L,0L,0L,0L), ncol = 4 )
  pt <- sfheaders:::rcpp_sfg_linestring( x, NULL, "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XYZM", "LINESTRING", "sfg") )
  r_pt <- sfg_linestring(x)
  expect_equal( pt, r_pt )

  x <- matrix(c(0,0,0,0), ncol = 2 )
  pt <- sfheaders:::rcpp_sfg_linestring( x, NULL, "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "LINESTRING", "sfg") )
  r_pt <- sfg_linestring(x)
  expect_equal( pt, r_pt )

  x <- matrix(c(0,0,0,0), ncol = 2 )
  pt <- sfheaders:::rcpp_sfg_linestring( x, c(0L, 1L), "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "LINESTRING", "sfg") )
  r_pt <- sfg_linestring(x)
  expect_equal( pt, r_pt )

  x <- data.frame( x = 0L, y = 0L )
  x <- as.matrix( x )
  pt <- sfheaders:::rcpp_sfg_linestring( x, NULL, "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "LINESTRING", "sfg") )
  r_pt <- sfg_linestring( x )
  expect_equal( pt, r_pt )

  x <- data.frame( x = 0L, y = 0L )
  x <- as.matrix( x )
  pt <- sfheaders:::rcpp_sfg_linestring( x, c("x","y"), "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "LINESTRING", "sfg") )
  r_pt <- sfg_linestring( x )
  ## shapes::get_mat( x, cols ); strips matrix attributes
  ## hence this unclass test
  expect_equal( attributes( r_pt )[["dimnames"]][[2]], c("x","y") )

  x <- data.frame( x = 0.1, y = 0.1 )
  x <- as.matrix( x )
  pt <- sfheaders:::rcpp_sfg_linestring( x, c("x","y"), "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "LINESTRING", "sfg") )
  r_pt <- sfg_linestring( x )
  ## shapes::get_mat( x, cols ); strips matrix attributes
  ## hence this unclass test
  expect_equal( attributes( r_pt )[["dimnames"]][[2]], c("x","y") )

  ## data.frame
  x <- data.frame( x = 0, y = 0 )
  pt <- sfheaders:::rcpp_sfg_linestring( x, NULL, "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "LINESTRING", "sfg") )
  r_pt <- sfg_linestring(x)
  expect_equal( pt, r_pt )

  x <- data.frame( x = 0, y = 0, z = 0 )
  pt <- sfheaders:::rcpp_sfg_linestring( x, NULL, "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XYZ", "LINESTRING", "sfg") )
  r_pt <- sfg_linestring(x)
  expect_equal( pt, r_pt )

  x <- data.frame( x = 0, y = 0, z = 0, m = 0 )
  pt <- sfheaders:::rcpp_sfg_linestring( x, NULL, "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XYZM", "LINESTRING", "sfg") )
  r_pt <- sfg_linestring(x)
  expect_equal( pt, r_pt )

  x <- data.frame( x = c(0,0), y = c(0,0) )
  pt <- sfheaders:::rcpp_sfg_linestring( x, NULL, "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "LINESTRING", "sfg"))
  r_pt <- sfg_linestring(x)
  expect_equal( pt, r_pt )

  x <- data.frame( x = c(0,0), y = c(0,0) )
  pt <- sfheaders:::rcpp_sfg_linestring( x, c(0L, 1L), "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "LINESTRING", "sfg"))

  ## using column names
  x <- data.frame( x = c(0,0), y = c(0,0) )
  pt <- sfheaders:::rcpp_sfg_linestring( x, c("x","y"), "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "LINESTRING", "sfg"))
  ## TODO names??
  # r_pt <- sfg_linestring( x )
  # expect_equal( pt, r_pt )

  x <- matrix(c(0L,1L,2L,3L), ncol = 4 )
  pt <- sfheaders:::rcpp_sfg_linestring( x, c(0,2), "" )
  res <- attr( pt, "class" )
  expect_equal( res, c("XY", "LINESTRING", "sfg") )
  # r_pt <- sfg_linestring(x)
  # expect_equal( pt, r_pt )

  expect_equal( pt[,1], 0 )
  expect_equal( pt[,2], 2 )

})

test_that("errors are found and handled", {

  expect_error( sfheaders:::rcpp_sfg_linestring( 1L, NULL, "" ), "sfheaders - invalid dimension" )
  x <- list(x = 1)
  expect_error( sfheaders:::rcpp_sfg_linestring( x, NULL, "" ), "sfheaders - unsupported sfg_LINESTRING type" )

  x <- matrix(1:4, ncol = 2)
  expect_error( sfheaders:::rcpp_sfg_linestring( x, c(1,2), "" ) )

  expect_error( sfheaders:::rcpp_sfg_linestring( x, as.factor( c(0,1), "" ) ) )

})

test_that("vectorised version works",{

  is_linestring <- function(x) {
    y <- is.matrix(unclass(x))
    z <- attr( x, "class")[2] == "LINESTRING"
    return( all(y) & all(z))
  }

  m1 <- matrix(1:3, ncol = 3)
  m2 <- matrix(1:3, ncol = 3)
  lst <- list( m1, m2 )
  res <- sfheaders:::rcpp_sfg_linestrings( lst, "" )
  expect_true( all( sapply( res, is_linestring ) ) )

})



