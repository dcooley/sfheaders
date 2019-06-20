context("sfheaders")

test_that("sfheaders::utils::other_columns works for various data types",{

  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c(2)  ## c++ index
  other_cols <- sfheaders:::rcpp_other_columns( df, id )
  expect_equal( other_cols, c(0,1) )

  m <- matrix( 1:24, ncol = 3 )
  id <- c(2)
  other_cols <- sfheaders:::rcpp_other_columns( m, id )
  expect_equal( other_cols, c(0,1))


  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c(0,2)  ## c++ index
  other_cols <- sfheaders:::rcpp_other_columns( df, id )
  expect_equal( other_cols, c(1) )

  m <- matrix( 1:24, ncol = 3 )
  id <- c(0,2)
  other_cols <- sfheaders:::rcpp_other_columns( m, id )
  expect_equal( other_cols, c(1))

  ## using names / strings
  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c("z")
  other_cols <- sfheaders:::rcpp_other_columns( df, id )
  expect_equal( other_cols, c("x","y") )

  m <- matrix( 1:24, ncol = 3 )
  dimnames(m) <- list(NULL, c("x","y","z") )
  id <- c("z")
  other_cols <- sfheaders:::rcpp_other_columns( m, id )
  expect_equal( other_cols, c("x","y"))

  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c("z","x")
  other_cols <- sfheaders:::rcpp_other_columns( df, id )
  expect_equal( other_cols, c("y") )

  m <- matrix( 1:24, ncol = 3 )
  dimnames(m) <- list(NULL, c("x","y","z") )
  id <- c("z","x")
  other_cols <- sfheaders:::rcpp_other_columns( m, id )
  expect_equal( other_cols, c("y"))



})
