context('sfg_type')

test_that("correct sfg type is returned",{

  expect_error( sfheaders:::rcpp_get_sfg_type(0), "sfheaders - unknown sfg type" )

  expect_equal( sfheaders:::rcpp_get_sfg_type(1), "POINT" )
  expect_equal( sfheaders:::rcpp_get_sfg_type(2), "MULTIPOINT" )
  expect_equal( sfheaders:::rcpp_get_sfg_type(3), "LINESTRING" )
  expect_equal( sfheaders:::rcpp_get_sfg_type(4), "MULTILINESTRING" )
  expect_equal( sfheaders:::rcpp_get_sfg_type(5), "POLYGON" )
  expect_equal( sfheaders:::rcpp_get_sfg_type(6), "MULTIPOLYGON" )

})
