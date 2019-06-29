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

  x <- data.frame( x = 1:5, y = 2:6 )
  bbox <- bb( x )
  expect_equal( bbox, c(1,2,5,6) )
})
