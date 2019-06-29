context("shapes_get_vec")

test_that("points extracted from different objects", {

  ### integer vector
  x <- 1L:2L
  res <- sfheaders:::rcpp_get_vec(x, NULL)
  expect_equal( x, res )

  ## numeric vector
  x <- 1:2
  res <- sfheaders:::rcpp_get_vec(x, NULL)
  expect_equal( x, res )

  ## integer matrix
  x <- matrix(1L:2L, ncol = 2)
  res <- sfheaders:::rcpp_get_vec(x, NULL)
  expect_equal( as.vector( x ), res )

  ## numeric matrix
  x <- matrix(1:2, ncol = 2)
  res <- sfheaders:::rcpp_get_vec(x, NULL)
  expect_equal( as.vector( x ), res )

  ## data.frame
  x <- data.frame(x = 1L, y = 2L)
  res <- sfheaders:::rcpp_get_vec( x, c(0,1) )  ## c++ indexing
  expect_equal( as.vector( c(x$x, x$y) ), res )


  ## integer matrix with numeric cols
  df <- data.frame(x = 1L, y = 2L)
  x <- as.matrix( df )
  res <- sfheaders:::rcpp_get_vec( x, c(0,1) )  ## c++ indexing
  expect_equal( as.vector( x ), res )

  ## numeric matrix with numeric cols
  df <- data.frame(x = 1, y = 2)
  x <- as.matrix( df )
  res <- sfheaders:::rcpp_get_vec( x, c(0,1) )  ## c++ indexing
  expect_equal( as.vector( x ), res )

  ## integer matrix with str cols
  df <- data.frame(x = 1L, y = 2L)
  x <- as.matrix( df )
  res <- sfheaders:::rcpp_get_vec( x, c("x","y") )
  expect_equal( as.vector( x ), res )

  ## numeric matrix with str cols
  df <- data.frame(x = 1, y = 2)
  x <- as.matrix( df )
  res <- sfheaders:::rcpp_get_vec( x, c("x","y") )
  expect_equal( as.vector( x ), res )

  ## data.frame with numeric cols
  x <- data.frame(x = 1L, y = 2L)
  res <- sfheaders:::rcpp_get_vec( x, c(0,1) )  ## c++ indexing
  expect_equal( c(x$x, x$y), res )

  ## data.frame with str cols
  x <- data.frame(x = 1L, y = 2L)
  res <- sfheaders:::rcpp_get_vec( x, c("x","y") )
  expect_equal( c(x$x, x$y), res )

  ## matrix with cols in different order
  df <- data.frame(y = 1, x = 2)
  x <- as.matrix( df )
  res <- sfheaders:::rcpp_get_vec( x, c("x","y") )
  expect_equal( rev( as.vector( x ) ), res )

  ## data.frame with cols in different order
  x <- data.frame(y = 1, x = 2)
  res <- sfheaders:::rcpp_get_vec( x, c("x","y") )
  expect_equal( c(x$x, x$y), res )

  ## errors
  ## - too many rows
  ## - columns don't exist
  df <- data.frame( x = 1:2, y = 1:2 )
  expect_error(
    sfheaders:::rcpp_get_vec( df, NULL )
    , "sfheaders - expecting single-row data.frame"
  )

  m <- as.matrix( df )
  expect_error(
    sfheaders:::rcpp_get_vec( m, NULL )
    , "sfheaders - expecting single-row matrix"
  )



})
