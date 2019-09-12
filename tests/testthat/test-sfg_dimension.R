context("sfg")

test_that("sfg dimensions", {

  expect_error( sfheaders:::rcpp_sfg_dimension( 1 ), "sfheaders - invalid dimension" )
  expect_equal( sfheaders:::rcpp_sfg_dimension( 1:2 ), "XY" )
  expect_equal( sfheaders:::rcpp_sfg_dimension( 1:3 ), "XYZ" )
  expect_equal( sfheaders:::rcpp_sfg_dimension( 1:4 ), "XYZM" )
  expect_error( sfheaders:::rcpp_sfg_dimension( 1:5 ), "sfheaders - invalid dimension" )

  m <- matrix(1:2, ncol = 2 )
  expect_equal( sfheaders:::rcpp_sfg_dimension( m ), "XY" )
  m <- matrix(1:3, ncol = 3 )
  expect_equal( sfheaders:::rcpp_sfg_dimension( m ), "XYZ" )
  m <- matrix(1:4, ncol = 4 )
  expect_equal( sfheaders:::rcpp_sfg_dimension( m ), "XYZM" )

  df <- data.frame(lon = 1, lat = 1)
  expect_equal( sfheaders:::rcpp_sfg_dimension( df ), "XY" )
  df <- data.frame(lon = 1, lat = 1, z = 1)
  expect_equal( sfheaders:::rcpp_sfg_dimension( df ), "XYZ" )
  df <- data.frame(lon = 1, lat = 1, z = 1, m = 1)
  expect_equal( sfheaders:::rcpp_sfg_dimension( df ), "XYZM" )

  l <- list( 1, 2 )
  expect_error( sfheaders:::rcpp_sfg_dimension( l ), "sfheaders - invalid dimension" )


})
