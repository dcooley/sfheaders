context("sfheaders")

test_that("sfheaders::utils::subset subsets a data.frame",{

  x <- data.frame(
    id = c(1,1,1,2,2,2)
    , x = c(1:6)
    , y = c(6:1)
    , z = letters[1:6]
    , stringsAsFactors = FALSE
  )
  idx <- c(0,1)
  res <- sfheaders:::rcpp_subset_dataframe(x, c("x","y"), idx[1], idx[2] )
  expect_equal( x[ idx+1, c("x","y") ], res )

  idx <- c(0,1)
  res <- sfheaders:::rcpp_subset_dataframe(x, c("id","x","y","z"), idx[1], idx[2] )
  expect_equal( x[idx+1, ], res )

})


test_that("sfheaders::utils::line_ids returns correct positions",{

  line_ids <- c(1,1,1,1,1)
  unique_ids <- sort( unique( line_ids ) )
  expected <- matrix(c(0,4), ncol = 2)
  res <- sfheaders:::rcpp_line_ids( line_ids, unique_ids )
  expect_equal( res, expected )

  line_ids <- c(1,1,1,1,2,2,3,3,3,3)
  unique_ids <- sort( unique( line_ids ) )
  expected <- matrix(c(0,3,4,5,6,9), ncol = 2, byrow = T)
  res <- sfheaders:::rcpp_line_ids( line_ids, unique_ids )
  expect_equal( res, expected )

})

test_that("sfheaders::utils::other_columns works for various data types",{

  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c(2)  ## c++ index
  other_cols <- sfheaders:::rcpp_other_columns( df, id, NULL )
  expect_equal( other_cols, c(0,1) )

  m <- matrix( 1:24, ncol = 3 )
  id <- c(2)
  other_cols <- sfheaders:::rcpp_other_columns( m, id, NULL )
  expect_equal( other_cols, c(0,1))


  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c(0,2)  ## c++ index
  other_cols <- sfheaders:::rcpp_other_columns( df, id, NULL )
  expect_equal( other_cols, c(1) )

  m <- matrix( 1:24, ncol = 3 )
  id <- c(0,2)
  other_cols <- sfheaders:::rcpp_other_columns( m, id, NULL )
  expect_equal( other_cols, c(1))

  ## using names / strings
  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c("z")
  other_cols <- sfheaders:::rcpp_other_columns( df, id, NULL )
  expect_equal( other_cols, c("x","y") )

  m <- matrix( 1:24, ncol = 3 )
  dimnames(m) <- list(NULL, c("x","y","z") )
  id <- c("z")
  other_cols <- sfheaders:::rcpp_other_columns( m, id, NULL )
  expect_equal( other_cols, c("x","y"))

  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c("z","x")
  other_cols <- sfheaders:::rcpp_other_columns( df, id, NULL )
  expect_equal( other_cols, c("y") )

  m <- matrix( 1:24, ncol = 3 )
  dimnames(m) <- list(NULL, c("x","y","z") )
  id <- c("z","x")
  other_cols <- sfheaders:::rcpp_other_columns( m, id, NULL )
  expect_equal( other_cols, c("y"))

  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c("z")
  id2 <- c("y")
  other_cols <- sfheaders:::rcpp_other_columns( df, id, id2 )
  expect_equal( other_cols, c("x") )

  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c("z")
  id2 <- c("y","x")
  other_cols <- sfheaders:::rcpp_other_columns( df, id, id2 )
  expect_equal( other_cols, character() )

  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c(0)
  id2 <- c(1,2)
  other_cols <- sfheaders:::rcpp_other_columns( df, id, id2 )
  expect_equal( other_cols, numeric() )

})
