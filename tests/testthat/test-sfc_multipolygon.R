context("sfc_multipolygon")

test_that("sfc_multipolygon works after refactoring issue14",{

  is_multipolygon <- function(x) {
    y <- sapply( x, function(y) is.list( unclass( y ) ) )
    z <- sapply( x, function(y) attr( y, "class")[2] == "MULTIPOLYGON")
    return( all(y) & all(z))
  }

  m <- matrix(1:9, ncol = 3)
  res <- sfheaders:::rcpp_sfc_multipolygon( m , c(0L, 1L), NULL, NULL, NULL )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )

  m <- matrix(1:9, ncol = 3)
  m <- cbind(m, c(1L,1L,2L))
  res <- sfheaders:::rcpp_sfc_multipolygon( m , c(0L, 1L), 3L, NULL, NULL, close = FALSE )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )


  m <- matrix(1:9, ncol = 3)
  m <- cbind(m, c(1L,1L,2L))
  m <- cbind(m, c(1L,1L,1L))
  res <- sfheaders:::rcpp_sfc_multipolygon( m , c(0L, 1L), 3L, 4L, NULL, close = FALSE )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )

  m <- matrix(1:9, ncol = 3)
  m <- cbind(m, c(1L,1L,2L))
  m <- cbind(m, c(1L,1L,1L))
  m <- cbind(m, c(1L,1L,1L))
  res <- sfheaders:::rcpp_sfc_multipolygon( m , c(0L, 1L), 3L, 4L, 5L, close = FALSE )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )

  m <- matrix(1:9, ncol = 3)
  m <- cbind(m, c(1,1,2))
  m <- cbind(m, c(1,1,1))
  m <- cbind(m, c(1,1,1))
  res <- sfheaders:::rcpp_sfc_multipolygon( m , c(0L, 1L), 3L, 4L, 5L, close = FALSE )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )


  m <- matrix(1:9, ncol = 3)
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfc_multipolygon( m , c("V1","V2"), NULL, NULL, NULL )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )

  m <- matrix(1:9, ncol = 3)
  m <- cbind(m, c(1L,1L,2L))
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfc_multipolygon( m , c("V1","V2"), "V4", NULL, NULL, close = FALSE )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )

  m <- matrix(1:9, ncol = 3)
  m <- cbind(m, c(1,1,2))
  m <- cbind(m, c(1,1,1))
  m <- cbind(m, c(1,1,1))
  df <- as.data.frame(m)
  m <- as.matrix(m)
  res <- sfheaders:::rcpp_sfc_multipolygon( m , c("V1", "V2"), "V3","V4","V5", close = FALSE )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )


  df <- data.frame(
    mp_id = c(1,1,1,1,2,2,2,2)
    #, p_id = c(1,1,1,1,2,2,2,2)
    , l_id = c(1,1,1,1,1,1,1,1)
    , x = c(1,2,3,1,4,5,6,4)
    , y = c(1,2,3,1,4,5,6,4)
  )

  res <- sfheaders:::rcpp_sfc_multipolygon( df, NULL, NULL, NULL, NULL )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )

  df <- data.frame(
    mp_id = c(1,1,1,1,2,2,2,2)
    , p_id = c(1,1,1,1,2,2,2,2)
    , l_id = c(1,1,1,1,1,1,1,1)
    , x = c(1.1,2,3,1,4,5,6,4)
    , y = c(1,2,3,1,4,5,6,4)
  )

  res <- sfheaders:::rcpp_sfc_multipolygon( df, c(3,4), NULL, NULL, NULL )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )
  expect_true( length( res ) == 1 )

  res <- sfheaders:::rcpp_sfc_multipolygon( df, c(3,4), 0, NULL, NULL )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )
  expect_true( length( res ) == 2 )

  res <- sfheaders:::rcpp_sfc_multipolygon( df, c(3,4), NULL, 1, NULL )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )
  expect_true( length( res ) == 1 )

  res <- sfheaders:::rcpp_sfc_multipolygon( df, c(3,4), NULL, NULL, 2 )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )
  expect_true( length( res ) == 1 )

  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfc_multipolygon( m, c(3,4), NULL, NULL, 2 )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )
  expect_true( length( res ) == 1 )

  res <- sfheaders:::rcpp_sfc_multipolygon( df, c(3,4), 0, NULL, 2 )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )
  expect_true( length( res ) == 2 )

  res <- sfheaders:::rcpp_sfc_multipolygon( df, c(3,4), NULL, 1, 2 )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )
  expect_true( length( res ) == 1 )

  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfc_multipolygon( m, c(3,4), NULL, 1, 2 )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )
  expect_true( length( res ) == 1 )

  res <- sfheaders:::rcpp_sfc_multipolygon( df, c(3,4), 0, 1, 2 )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )
  expect_true( length( res ) == 2 )

  res <- sfheaders:::rcpp_sfc_multipolygon( df, c(3,4), c(2), c(0), c(1))
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )
  expect_true( length( res ) == 1 )

})

test_that("data.frame with non-numeric id columns work",{


  is_multipolygon <- function(x) {
    y <- sapply( x, function(y) is.list( unclass( y ) ) )
    z <- sapply( x, function(y) attr( y, "class")[2] == "MULTIPOLYGON")
    return( all(y) & all(z))
  }

  df <- data.frame(
    p_id = letters[c(1,1,1,1,2,2,2,2)]
    , l_id = c(1,1,1,1,1,1,1,1)
    , x = c(1,2,3,1,4,5,6,4)
    , y = c(1,2,3,1,4,5,6,4)
    , stringsAsFactors = F
  )

  res <- sfheaders::sfc_multipolygon(
    obj = df
    , x = "x"
    , y = "y"
    , multipolygon_id = "p_id"
  )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )

  df <- data.frame(
    mp_id = letters[c(1,1,2,2,3,3,3,3)]
    , p_id = letters[c(1,1,1,1,2,2,2,2)]
    , l_id = letters[c(1,1,1,1,1,1,1,1)]
    , x = c(1,2,3,1,4,5,6,4)
    , y = c(1,2,3,1,4,5,6,4)
    , stringsAsFactors = F
  )

  res <- sfheaders::sfc_multipolygon(
    obj = df
    , x = "x"
    , y = "y"
    , multipolygon_id = "mp_id"
    , polygon_id = "p_id"
    , close = FALSE
  )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )

  df <- data.frame(
    mp_id = letters[c(1,1,2,2,3,3,3,3)]
    , p_id = letters[c(1,1,1,1,2,2,2,2)]
    , l_id = letters[c(1,2,1,1,1,1,2,2)]
    , x = c(1,2,3,1,4,5,6,4)
    , y = c(1,2,3,1,4,5,6,4)
    , stringsAsFactors = F
  )

  res <- sfheaders::sfc_multipolygon(
    obj = df
    , x = "x"
    , y = "y"
    , multipolygon_id = "mp_id"
    , polygon_id = "p_id"
    , linestring_id = "l_id"
    , close = FALSE
  )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )

})

## issue 61
test_that("correct columsn returned - issue 61",{

  df <- data.frame(
    mp_id = c( rep(1, 14), rep(2, 5) )
    , p_id = c( rep(1, 19 ) )
    , l_id = c( rep(1, 8), rep(2, 6), rep(1, 5))
    , x = c(0,0,0.75,1,0.5,0.8,0.69,0,0.2,0.5,0.5,0.3,0.2,0.2,0.69,0.8,1.1,1.23,0.69)
    , y = c(0,1,1,0.8,0.7,0.6,0,0,0.2,0.2,0.4,0.6,0.4,0.2,0,0.6,0.63,0.3,0)
  )

  sf <- sf_multipolygon(
    obj = df,
    multipolygon_id = "mp_id",
    polygon_id = "p_id",
    linestring_id = "l_id",
    x = "x",
    y = "y"
    )

  res <- sf_to_df( sf )
  expect_equal( res$multipolygon_id, df$mp_id )
  expect_equal( res$polygon_id, df$p_id )
  expect_equal( res$linestring_id, df$l_id )

})


test_that("vectorised version works",{

  is_multipolygon <- function(x) {
    y <- sapply( x, function(y) is.list( unclass( y ) ) )
    z <- sapply( x, function(y) attr( y, "class")[2] == "MULTIPOLYGON")
    return( all(y) & all(z))
  }

  m1 <- matrix(1:12, ncol = 3)
  m2 <- matrix(1:12, ncol = 3)
  lst <- list( m1, m2 )
  res <- sfheaders:::rcpp_sfc_multipolygons( lst )
  expect_true( all( sapply( res, is_multipolygon ) ) )

})

