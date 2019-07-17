context("sfc_POINTS")

test_that("sfc_points works for various objects",{

  x <- c(1:3)
  res <- sfheaders:::rcpp_sfc_point( x, NULL )
  expect_true( all( attr(res, "class") == c("sfc_POINT", "sfc") ) )
  expect_true( all( attr(res, "z_range") == c(3,3) ) )

  x <- c(1:10)
  expect_error( sfheaders:::rcpp_sfc_point( x, NULL ), "sfheaders - invalid dimension" )

  x <- matrix( c(1:10) , ncol = 2 )
  res <- sfheaders:::rcpp_sfc_point( x, NULL )
  expect_true( all( attr(res, "class") == c("sfc_POINT", "sfc") ) )
  expect_true( all( is.na( attr(res, "z_range") ) ) )

  x <- matrix( c(1:12) , ncol = 3 )
  res <- sfheaders:::rcpp_sfc_point( x, NULL )
  expect_true( all( attr(res, "class") == c("sfc_POINT", "sfc") ) )
  expect_true( all( attr(res, "z_range") == c(9, 12) ) )

  x <- matrix( c(1:12) , ncol = 4 )
  res <- sfheaders:::rcpp_sfc_point( x, NULL )
  expect_true( all( attr(res, "class") == c("sfc_POINT", "sfc") ) )
  expect_true( all( attr(res, "z_range") == c(7,9) ) )
  expect_true( all( attr(res, "m_range") == c(10,12) ) )

})

test_that("sfc_points works from R",{

  x <- c(1:3)
  res <- sfc_point(x)
  expect_true( length( res ) == 1 )
  expect_equal( unlist( res ), x)

  x <- matrix(1:4, ncol = 2)
  res <- sfc_point( x )
  expect_equal( unclass( res[[1]] ), c(1,3) )

})
