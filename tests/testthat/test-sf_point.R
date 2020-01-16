context("sf point")

test_that("sf_points works for various objects",{

  x <- c(1:3)
  res <- sfheaders:::rcpp_sf_point( x, NULL, FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  x <- c(1:10)
  expect_error( sfheaders:::rcpp_sf_point( x, NULL, FALSE ), "sfheaders - invalid dimension" )

  x <- matrix( c(1:10) , ncol = 2 )
  res <- sfheaders:::rcpp_sf_point( x, NULL, FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  x <- matrix( c(1:12) , ncol = 3 )
  res <- sfheaders:::rcpp_sf_point( x, NULL, FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  x <- matrix( c(1:12) , ncol = 4 )
  res <- sfheaders:::rcpp_sf_point( x, NULL, FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

})
