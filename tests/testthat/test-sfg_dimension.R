context("sfg")

test_that("sfg dimensions", {

  expect_error( sfheaders:::rcpp_sfg_dimension( 1, FALSE ), "sfheaders - invalid dimension" )
  expect_equal( sfheaders:::rcpp_sfg_dimension( 1:2, FALSE ), "XY" )
  expect_equal( sfheaders:::rcpp_sfg_dimension( 1:3, FALSE ), "XYZ" )
  expect_equal( sfheaders:::rcpp_sfg_dimension( 1:4, FALSE ), "XYZM" )
  expect_error( sfheaders:::rcpp_sfg_dimension( 1:5, FALSE ), "sfheaders - invalid dimension" )

  m <- matrix(1:2, ncol = 2 )
  expect_equal( sfheaders:::rcpp_sfg_dimension( m, FALSE ), "XY" )
  m <- matrix(1:3, ncol = 3 )
  expect_equal( sfheaders:::rcpp_sfg_dimension( m, FALSE ), "XYZ" )
  m <- matrix(1:4, ncol = 4 )
  expect_equal( sfheaders:::rcpp_sfg_dimension( m, FALSE ), "XYZM" )

  df <- data.frame(lon = 1, lat = 1)
  expect_equal( sfheaders:::rcpp_sfg_dimension( df, FALSE ), "XY" )
  df <- data.frame(lon = 1, lat = 1, z = 1)
  expect_equal( sfheaders:::rcpp_sfg_dimension( df, FALSE ), "XYZ" )
  df <- data.frame(lon = 1, lat = 1, z = 1, m = 1)
  expect_equal( sfheaders:::rcpp_sfg_dimension( df, FALSE ), "XYZM" )

  l <- list( 1, 2 )
  expect_error( sfheaders:::rcpp_sfg_dimension( l, FALSE ), "sfheaders - invalid dimension" )


})
