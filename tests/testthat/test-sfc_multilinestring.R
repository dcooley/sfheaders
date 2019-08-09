context("sfc_MULTILINESTRING")

test_that("sfc_multilinestring works", {

  is_multilinestring <- function(x) {
    y <- sapply( x, function(y) is.list( unclass( y ) ) )
    z <- sapply( x, function(y) attr( y, "class")[2] == "MULTILINESTRING")
    return( all(y) & all(z))
  }

  df <- data.frame(
    p_id = c(1,1,1,1,2,2,2,2)
    , l_id = c(1,1,1,1,1,1,1,1)
    , x = c(1,2,3,1,4,5,6,4)
    , y = c(1,2,3,1,4,5,6,4)
  )

  res <- sfheaders:::rcpp_sfc_multilinestring( df, NULL, NULL, NULL )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )
  expect_true( is_multilinestring( res ) )

  res <- sfheaders:::rcpp_sfc_multilinestring( df, NULL, NULL, c(0) )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )
  expect_true( is_multilinestring( res ) )

  res <- sfheaders:::rcpp_sfc_multilinestring( df, NULL, c(0), NULL )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )
  expect_true( is_multilinestring( res ) )

  res <- sfheaders:::rcpp_sfc_multilinestring( df, c("x","y"), NULL, NULL )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )
  expect_true( is_multilinestring( res ) )

  res <- sfheaders:::rcpp_sfc_multilinestring( df, c(2,3), NULL, NULL )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )
  expect_true( is_multilinestring( res ) )

  res <- sfheaders:::rcpp_sfc_multilinestring( df, NULL, 0, 1)
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )
  expect_true( is_multilinestring( res ) )

  res <- sfheaders:::rcpp_sfc_multilinestring( df, c(2,3), 0, NULL )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )
  expect_true( is_multilinestring( res ) )

  res <- sfheaders:::rcpp_sfc_multilinestring( df, c(2,3), NULL, 1 )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )
  expect_true( is_multilinestring( res ) )

  res <- sfheaders:::rcpp_sfc_multilinestring( df, c(2,3), c(0), c(1))
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )
  expect_true( is_multilinestring( res ) )

  m <- as.matrix( df )
  m <- matrix( as.integer( m ), ncol = 4 )
  res <- sfheaders:::rcpp_sfc_multilinestring( m, c(2,3), c(0), c(1))
  expect_true( is_multilinestring( res ) )

  res <- sfheaders:::rcpp_sfc_multilinestring( df, c("x","y"),c("p_id"),c("l_id"))
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )
  expect_true( is_multilinestring( res ) )

})

test_that("data.frame with non-numeric id columns work",{


  is_multilinestring <- function(x) {
    y <- sapply( x, function(y) is.list( unclass( y ) ) )
    z <- sapply( x, function(y) attr( y, "class")[2] == "MULTILINESTRING")
    return( all(y) & all(z))
  }

  df <- data.frame(
    p_id = letters[c(1,1,1,1,2,2,2,2)]
    , l_id = c(1,1,1,1,1,1,1,1)
    , x = c(1,2,3,1,4,5,6,4)
    , y = c(1,2,3,1,4,5,6,4)
    , stringsAsFactors = F
  )

  res <- sfheaders::sfc_multilinestring(
    obj = df
    , x = "x"
    , y = "y"
    , multilinestring_id = "p_id"
    , linestring_id = "l_id"
  )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )
  expect_true( is_multilinestring( res ) )


  df <- data.frame(
    p_id = letters[c(1,1,1,1,2,2,2,2)]
    , l_id = letters[c(1,1,1,1,1,1,1,1)]
    , x = c(1,2,3,1,4,5,6,4)
    , y = c(1,2,3,1,4,5,6,4)
    , stringsAsFactors = F
  )

  res <- sfheaders::sfc_multilinestring(
    obj = df
    , x = "x"
    , y = "y"
    , multilinestring_id = "p_id"
    , linestring_id = "l_id"
  )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )
  expect_true( is_multilinestring( res ) )

})

test_that("vectorised version works",{

  is_multilinestring <- function(x) {
    y <- sapply( x, function(y) is.list( unclass( y ) ) )
    z <- sapply( x, function(y) attr( y, "class")[2] == "MULTILINESTRING")
    return( all(y) & all(z))
  }

  m1 <- matrix(1:12, ncol = 3)
  m2 <- matrix(1:12, ncol = 3)
  lst <- list( m1, m2 )
  res <- sfheaders:::rcpp_sfc_multilinestrings( lst )
  expect_true( all( sapply( res, is_multilinestring ) ) )

})
