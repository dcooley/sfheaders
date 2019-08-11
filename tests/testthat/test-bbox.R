context("bbox")

test_that("bounding box correctly calculated", {


  bb <- function( x, cols = NULL ) {
    sfheaders:::rcpp_calculate_bbox( x, cols )
  }

  expect_error( bb( 1L ), "sfheaders - incorrect size of bounding box")
  expect_error( bb( "a" ) )
  expect_error( bb( matrix(1L) ), "sfheaders - incorrect size of bounding box")
  expect_error( bb( matrix(1.2) ), "sfheaders - incorrect size of bounding box")

  bbox <- bb( 1L:2L )
  expect_equal( bbox, c(1,2,1,2) )

  bbox <- bb( c(1.0, 2.0) )
  expect_equal( bbox, c(1,2,1,2) )

  bbox <- bb( 1L:2L, c(1L,2L) )
  expect_equal( bbox, c(1,2,1,2) )

  bbox <- bb( c(1.0, 2.0), c(1,2) )
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

  x <- matrix( c( 1.2, 2, 3, 4 ), ncol = 2, byrow = T )
  bbox <- bb( x, c(0,1) )
  expect_equal( bbox, c(1.2,2,3,4) )

  x <- matrix( c( 1L:4L ), ncol = 2, byrow = T )
  bbox <- bb( x, c(0L,1L) )
  expect_equal( bbox, c(1,2,3,4) )

  x <- matrix( c( 1L:4L ), ncol = 2, byrow = T )
  x <- as.data.frame( x )
  x <- as.matrix( x )
  bbox <- bb( x, c("V1","V2") )
  expect_equal( bbox, c(1,2,3,4) )

  x <- matrix( c( 1.2,2,3,4 ), ncol = 2, byrow = T )
  x <- as.data.frame( x )
  x <- as.matrix( x )
  bbox <- bb( x, c("V1","V2") )
  expect_equal( bbox, c(1.2,2,3,4) )

  x <- 1:2
  bbox <- bb( x, c("x","y") )
  expect_equal( bbox, c(1,2,1,2) )

  x <- c(1.1, 2)
  bbox <- bb( x, c("x","y") )
  expect_equal( bbox, c(1.1,2,1.1,2) )

  x <- data.frame( x = 1:5, y = 2:6 )
  bbox <- bb( x )
  expect_equal( bbox, c(1,2,5,6) )

  x <- 1
  expect_error( bb( x ), "sfheaders - incorrect size of bounding box")
  x <- matrix(1)
  expect_error( bb( x ), "sfheaders - incorrect size of bounding box")
  x <- matrix(1.1)
  expect_error( bb( x ), "sfheaders - incorrect size of bounding box")

})


test_that("z_range correctly calculated", {


  zr <- function( x ) {
    sfheaders:::rcpp_calculate_z_range( x )
  }

  err <- "sfheaders - incorrect size of z_range"

  expect_error( zr( 1L:2L ), err )
  expect_error( zr( c(1.2,2) ), err )

  expect_equal( zr(1:3), c(3,3) )
  expect_equal( zr(c(1.2,2,3)), c(3,3) )

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
  expect_error( mr( c(1.2,2.2) ), err )
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
  expect_equal( mr(c(1.2,2:4)), c(4,4) )

  x <- matrix(c(1L:8L), ncol = 4)
  expect_equal( mr(x), c(7L,8L))

  x <- matrix(c(1.1,2,3,4), ncol = 4)
  expect_equal( mr(x), c(4,4))

  x <- as.data.frame( matrix(c(1L:8L), ncol = 4) )
  expect_equal( mr(x), c(7,8))

})

