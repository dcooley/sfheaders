context("bbox")

test_that("bounding box correctly calculated", {


  bb <- function( x ) {
    sfheaders:::rcpp_calculate_bbox( x )
  }

  bbox <- bb( 1:2 )
  expect_equal( bbox, c(1,2,1,2) )

  x <- matrix(c(0,0,0,1), ncol = 2 )
  bbox <- bb( x )
  expect_equal( bbox, c(0,0,0,1) )

  x <- matrix( c( 1, 2, 3, 4 ), ncol = 2 )
  bbox <- bb( x )
  expect_equal( bbox, c(1,3,2,4) )

  x <- matrix( c( 1, 2, 3, 4 ), ncol = 2, byrow = T )
  bbox <- bb( x )
  expect_equal( bbox, c(1,2,3,4) )

  x <- matrix( c( 1L:4L ), ncol = 2, byrow = T )
  bbox <- bb( x )
  expect_equal( bbox, c(1,2,3,4) )


  x <- data.frame( x = 1:5, y = 2:6 )
  bbox <- bb( x )
  expect_equal( bbox, c(1,2,5,6) )
})


test_that("z_range correctly calculated", {


  zr <- function( x ) {
    sfheaders:::rcpp_calculate_z_range( x )
  }

  err <- "sfheaders - incorrect size of z_range"

  expect_error( zr( 1:2 ), err )

  expect_equal( zr(1:3), c(3,3) )

  x <- matrix(c(0,0,0,1), ncol = 2 )
  expect_error( zr( x ), err )

  x <- matrix( c( 1, 2, 3, 4 ), ncol = 2 )
  expect_error( zr( x ), err )

  x <- matrix( c( 1, 2, 3, 4 ), ncol = 2, byrow = T )
  expect_error( zr( x ), err )

  x <- matrix( c( 1L:4L ), ncol = 2, byrow = T )
  expect_error( zr( x ), err )

  x <- data.frame( x = 1:5, y = 2:6 )
  expect_error( zr( x ), err )


  expect_equal( zr(1:3), c(3,3) )

  x <- matrix(c(1L:6L), ncol = 3)
  expect_equal( zr(x), c(5L,6L))

  x <- as.data.frame( matrix(c(1L:6L), ncol = 3) )
  expect_equal( zr(x), c(5L,6L))

})


test_that("m_range correctly calculated", {


  mr <- function( x ) {
    sfheaders:::rcpp_calculate_m_range( x )
  }

  err <- "sfheaders - incorrect size of m_range"

  expect_error( mr( 1:2 ), err )
  expect_error( mr( 1:3 ), err )

  expect_equal( mr(1:4), c(4,4) )

  x <- matrix(c(0,0,0,0,0,0), ncol = 3 )
  expect_error( mr( x ), err )

  x <- matrix( c( 1, 2, 3, 4 ), ncol = 2 )
  expect_error( mr( x ), err )

  x <- matrix( c( 1, 2, 3, 4 ), ncol = 2, byrow = T )
  expect_error( mr( x ), err )

  x <- matrix( c( 1L:4L ), ncol = 2, byrow = T )
  expect_error( mr( x ), err )

  x <- data.frame( x = 1:5, y = 2:6 )
  expect_error( mr( x ), err )


  expect_equal( mr(1:4), c(4,4) )

  x <- matrix(c(1L:8L), ncol = 4)
  expect_equal( mr(x), c(7L,8L))

  x <- as.data.frame( matrix(c(1L:8L), ncol = 4) )
  expect_equal( mr(x), c(7,8))

})

