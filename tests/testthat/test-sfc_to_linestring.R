context("sfc_linestring")

test_that("various objects converted to sfc_LINESTRING",{

  is_linestring <- function(x) {
    y <- sapply( x, function(y) is.matrix(unclass(y)))
    z <- sapply( x, function(y) attr( y, "class")[2] == "LINESTRING")
    return( all(y) & all(z))
  }

  v <- 1:3
  res <- sfheaders:::rcpp_sfc_linestring(v, NULL, NULL)
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )
  expect_true( is_linestring( res ) )

  m <- matrix(1:4, ncol = 2)
  res <- sfheaders:::rcpp_sfc_linestring(m, NULL, NULL)
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )
  expect_true( is_linestring( res ) )

  m <- matrix(1:4, ncol = 2)
  res <- sfheaders:::rcpp_sfc_linestring(m, c(0,1), NULL)
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )
  expect_true( is_linestring( res ) )

  m <- matrix(1:4, ncol = 2)
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_linestring(df, NULL, NULL)
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )
  expect_true( is_linestring( res ) )

  m <- matrix(1:4, ncol = 2)
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_linestring(df, c(0,1), NULL)
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )
  expect_true( is_linestring( res ) )

  m <- matrix(1:4, ncol = 2)
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_linestring(df, c("V1","V2"), NULL)
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )
  expect_true( is_linestring( res ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  res <- sfheaders:::rcpp_sfc_linestring(m, NULL, 2)
  expect_true( is_linestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  res <- sfheaders:::rcpp_sfc_linestring(m, c(0,1), 2)
  expect_true( is_linestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_linestring(df, NULL, 2)
  expect_true( is_linestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_linestring(df, c(0,1), 2)
  expect_true( is_linestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_linestring(df, c("V1","V2"), c("V3"))
  expect_true( is_linestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )

  m <- matrix(1:4, ncol = 2)
  expect_error( sfheaders:::rcpp_sfc_linestring(m, NULL, 0), "sfheaders - incorrect number of geometry columns")

})

test_that("data.frame with non-numeric id columns work",{

  is_linestring <- function(x) {
    y <- sapply( x, function(y) is.matrix(unclass(y)))
    z <- sapply( x, function(y) attr( y, "class")[2] == "LINESTRING")
    return( all(y) & all(z))
  }

  df <- data.frame(
    p_id = letters[c(1,1,1,1,2,2,2,2)]
    , l_id = c(1,1,1,1,1,1,1,1)
    , x = c(1,2,3,1,4,5,6,4)
    , y = c(1,2,3,1,4,5,6,4)
  )

  res <- sfheaders::sfc_linestring(
    obj = df
    , x = "x"
    , y = "y"
    , linestring_id = "p_id"
  )
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )
  expect_true( is_linestring( res ) )

})
