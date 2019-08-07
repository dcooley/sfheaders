context("shapes_get_line")


test_that("line matrices returend from various R objects",{

  x <- c(1:4)
  expect_error(
    sfheaders:::rcpp_get_mat( x , NULL )
    , "sfheaders - lines need to be matrices or data.frames"
  )

  x <- matrix(c(1L:4L), ncol = 2)
  res <- sfheaders:::rcpp_get_mat( x, NULL )
  expect_equal( x, res )

  x <- matrix(c(1:4), ncol = 2)
  res <- sfheaders:::rcpp_get_mat( x, NULL )
  expect_equal( x, res )

  x <- data.frame(y = 1, x = 2)
  res <- sfheaders:::rcpp_get_mat( x, NULL )
  expect_equal( as.matrix( x ), res )

  x <- data.frame( y = 1:2, x = 3:4 )
  res <- sfheaders:::rcpp_get_mat( x, NULL )
  expect_equal( as.matrix( x ), res )


  x <- matrix(c(1L:4L), ncol = 2)
  res <- sfheaders:::rcpp_get_mat( x, c(1,0) )  ## c++ indexed
  expect_equal( x[, c(2,1)], res )

  x <- matrix(c(1:4), ncol = 2)
  res <- sfheaders:::rcpp_get_mat( x, c(0,1) )
  expect_equal( x, res )

  x <- data.frame(y = 1, x = 2)
  res <- sfheaders:::rcpp_get_mat( x, c("x","y") )
  expect_equal( matrix( c(x$x, x$y), ncol = 2 ), res )

  x <- data.frame( y = 1:2, x = 3:4 )
  res <- sfheaders:::rcpp_get_mat( x, c("y","x") )
  expect_equal( matrix( c(x$y, x$x), ncol = 2 ), res )

  x <- data.frame(y = 1L, x = 2L)
  x <- as.matrix( x )
  res <- sfheaders:::rcpp_get_mat( x, c("x","y") )
  expect_equal( matrix( unname( x[, c(2,1) ] ), ncol = 2 ), res )

  x <- data.frame( y = 1L:2L, x = 3L:4L )
  x <- as.matrix( x )
  res <- sfheaders:::rcpp_get_mat( x, c("y","x") )
  expect_equal( unname( x ), res )

  x <- data.frame(y = 1, x = 2)
  x <- as.matrix( x )
  res <- sfheaders:::rcpp_get_mat( x, c("x","y") )
  expect_equal( matrix( unname( x[, c(2,1) ] ), ncol = 2 ), res )

  x <- data.frame( y = 1:2, x = 3:4 )
  x <- as.matrix( x )
  res <- sfheaders:::rcpp_get_mat( x, c("y","x") )
  expect_equal( unname( x ), res )

  x <- data.frame( y = 1:2, x = 3:4 )
  res <- sfheaders:::rcpp_get_mat( x, c(1,0) )
  expect_equal( as.matrix( x[, c(2,1)] ) , res )

})
