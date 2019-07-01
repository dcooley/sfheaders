context("sfc_POINTS")

test_that("sfc_sfc_points works for various objects",{

  x <- c(1:3)
  res <- sfheaders:::rcpp_sfc_point( x, NULL )
  expect_true( all( attr(res, "class") == c("sfc_POINT", "sfc") ) )

  x <- c(1:10)
  expect_error( sfheaders:::rcpp_sfc_point( x, NULL ), "sfheaders - invalid dimension" )

  x <- matrix( c(1:10) , ncol = 2 )
  res <- sfheaders:::rcpp_sfc_point( x, NULL )
  expect_true( all( attr(res, "class") == c("sfc_POINT", "sfc") ) )

})
