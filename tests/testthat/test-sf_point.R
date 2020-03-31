context("sf point")

test_that("sf_points works for various objects",{

  x <- c(1:3)
  res <- sfheaders:::rcpp_sf_point( x, NULL, FALSE, "" )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  x <- c(1:10)
  expect_error( sfheaders:::rcpp_sf_point( x, NULL, FALSE, "" ), "sfheaders - can't work out the dimension" )

  x <- matrix( c(1:10) , ncol = 2 )
  res <- sfheaders:::rcpp_sf_point( x, NULL, FALSE, "" )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  x <- matrix( c(1:12) , ncol = 3 )
  res <- sfheaders:::rcpp_sf_point( x, NULL, FALSE, "" )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  x <- matrix( c(1:12) , ncol = 4 )
  res <- sfheaders:::rcpp_sf_point( x, NULL, FALSE, "" )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  x <- c(1:3)
  res <- sfheaders:::rcpp_sf_point( x, NULL, FALSE, "" )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  x <- matrix( c(1:10) , ncol = 2 )
  res <- sfheaders:::rcpp_sf_point( x, c(0,1), TRUE, "" )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  x <- as.matrix( as.data.frame( matrix( c(1:10) , ncol = 2 ) ) )
  res <- sfheaders:::rcpp_sf_point( x, c("V1","V2"), TRUE, "" )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  x <- as.matrix( as.data.frame( matrix( c(1:10) , ncol = 2 ) ) )
  x[1,1] <- 1.1
  res <- sfheaders:::rcpp_sf_point( x, c("V1","V2"), TRUE, "" )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  x <- matrix( c(1:12) , ncol = 3 )
  res <- sfheaders:::rcpp_sf_point( x, c(0,1), TRUE, "" )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  x <- as.data.frame( matrix( c(1:12) , ncol = 3 ) )
  res <- sfheaders:::rcpp_sf_point( x, c(0L,1L), TRUE, "" )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  x <- matrix( c(1:12) , ncol = 4 )
  x[1,1] <- 1.1
  res <- sfheaders:::rcpp_sf_point( x, c(0,1), TRUE, "" )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )


})
