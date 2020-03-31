context("sfc_MULTILINESTRING")

test_that("various objects converted to sfc_multilinestring",{


  is_multilinestring <- function(x) {
    y <- sapply( x, function(y) is.list( unclass( y ) ) )
    z <- sapply( x, function(y) attr( y, "class")[2] == "MULTILINESTRING")
    return( all(y) & all(z))
  }

  v <- 1:3
  expect_error( sfheaders:::rcpp_sfc_multilinestring(v, NULL, NULL, NULL, ""), "sfheaders - unsupported object")

  m <- matrix(1:4, ncol = 2)
  res <- sfheaders:::rcpp_sfc_multilinestring(m, NULL, NULL, NULL, "")
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )
  expect_true( is_multilinestring( res ) )

  m <- matrix(c(1.2,3,4,5), ncol = 2)
  res <- sfheaders:::rcpp_sfc_multilinestring(m, NULL, NULL, NULL, "")
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )
  expect_true( is_multilinestring( res ) )

  m <- matrix(1:4, ncol = 2)
  res <- sfheaders:::rcpp_sfc_multilinestring(m, c(0,1), NULL, NULL, "")
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )
  expect_true( is_multilinestring( res ) )

  m <- matrix(c(1.2,3,4,5), ncol = 2)
  res <- sfheaders:::rcpp_sfc_multilinestring(m, c(0,1), NULL, NULL, "")
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )
  expect_true( is_multilinestring( res ) )

  m <- matrix(1:4, ncol = 2)
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_multilinestring(df, NULL, NULL, NULL, "")
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )
  expect_true( is_multilinestring( res ) )

  m <- matrix(1:4, ncol = 2)
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_multilinestring(df, c(0,1), NULL, NULL, "")
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )
  expect_true( is_multilinestring( res ) )

  m <- matrix(1:4, ncol = 2)
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfc_multilinestring(df, c("V1","V2"), NULL, NULL, "")
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )
  expect_true( is_multilinestring( res ) )

  m <- matrix(c(1.2,3,4,5), ncol = 2)
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfc_multilinestring(df, c("V1","V2"), NULL, NULL, "")
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )
  expect_true( is_multilinestring( res ) )


  m <- matrix(1:4, ncol = 2)
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_multilinestring(df, c("V1","V2"), NULL, NULL, "")
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )
  expect_true( is_multilinestring( res ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  res <- sfheaders:::rcpp_sfc_multilinestring(m, NULL, 2, NULL, "")
  expect_true( is_multilinestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  res <- sfheaders:::rcpp_sfc_multilinestring(m, c(0,1), 2, NULL, "")
  expect_true( is_multilinestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_multilinestring(df, NULL, 2, NULL, "")
  expect_true( is_multilinestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1L,1L,2L,2L))
  res <- sfheaders:::rcpp_sfc_multilinestring(m, c(0L,1L), 2L, NULL, "")
  expect_true( is_multilinestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  res <- sfheaders:::rcpp_sfc_multilinestring(m, c(0L,1L), 2L, NULL, "")
  expect_true( is_multilinestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )

  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1))
  res <- sfheaders:::rcpp_sfc_multilinestring(m, c(0L,1L), 2L, NULL, "")
  expect_true( is_multilinestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_multilinestring(df, c(0,1), 2, NULL, "")
  expect_true( is_multilinestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1L,1L,2L,2L) )
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfc_multilinestring(m, c("V1","V2"), NULL, NULL, "")
  expect_true( is_multilinestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2) )
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfc_multilinestring(m, c("V1","V2"), NULL, NULL, "")
  expect_true( is_multilinestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )

  m <- matrix(c(1.2,2:8), ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_multilinestring(df, c("V1","V2"), NULL, NULL, "")
  expect_true( is_multilinestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2) )
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfc_multilinestring(m, c("V1","V2"), "V3", NULL, "")
  expect_true( is_multilinestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1L,1L,2L,2L) )
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfc_multilinestring(m, c("V1","V2"), "V3", "V3", "")
  expect_true( is_multilinestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2) )
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfc_multilinestring(m, c("V1","V2"), "V3", "V3", "")
  expect_true( is_multilinestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )

  m <- matrix(c(1.2,2:8), ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_multilinestring(df, c("V1","V2"), "V3", NULL, "")
  expect_true( is_multilinestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )



  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_multilinestring(df, c("V1","V2"), c("V3"), NULL, "")
  expect_true( is_multilinestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )

  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_multilinestring(df, c("V1","V2"), c("V3"), NULL, "")
  expect_true( is_multilinestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )


  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_multilinestring(df, c(0L,1L), 2L, NULL, "")
  expect_true( is_multilinestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )

  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1L))
  res <- sfheaders:::rcpp_sfc_multilinestring(m, c(0L,1L), NULL, 2L, "")
  expect_true( is_multilinestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )

  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1))
  res <- sfheaders:::rcpp_sfc_multilinestring(m, c(0L,1L), NULL, 2L, "")
  expect_true( is_multilinestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )

  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1L))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_multilinestring(df, c(0L,1L), NULL, 2L, "")
  expect_true( is_multilinestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )

  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_multilinestring(df, c(0L,1L), NULL, 2L, "")
  expect_true( is_multilinestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )

  m <- matrix(1:4, ncol = 2)
  expect_error( sfheaders:::rcpp_sfc_multilinestring(m, NULL, 0, NULL, ""), "sfheaders - incorrect number of geometry columns")

})

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

  res <- sfheaders:::rcpp_sfc_multilinestring( df, NULL, NULL, NULL, "" )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )
  expect_true( is_multilinestring( res ) )

  res <- sfheaders:::rcpp_sfc_multilinestring( df, NULL, NULL, c(0), "" )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )
  expect_true( is_multilinestring( res ) )

  res <- sfheaders:::rcpp_sfc_multilinestring( df, NULL, c(0), NULL, "" )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )
  expect_true( is_multilinestring( res ) )

  res <- sfheaders:::rcpp_sfc_multilinestring( df, c("x","y"), NULL, NULL, "" )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )
  expect_true( is_multilinestring( res ) )

  res <- sfheaders:::rcpp_sfc_multilinestring( df, c(2,3), NULL, NULL, "" )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )
  expect_true( is_multilinestring( res ) )

  res <- sfheaders:::rcpp_sfc_multilinestring( df, NULL, 0, 1, "" )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )
  expect_true( is_multilinestring( res ) )

  res <- sfheaders:::rcpp_sfc_multilinestring( df, c(2,3), 0, NULL, "" )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )
  expect_true( is_multilinestring( res ) )

  res <- sfheaders:::rcpp_sfc_multilinestring( df, c(2,3), NULL, 1, "" )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )
  expect_true( is_multilinestring( res ) )

  res <- sfheaders:::rcpp_sfc_multilinestring( df, c(2,3), c(0), c(1), "" )
  expect_equal( attr( res, "class" ), c("sfc_MULTILINESTRING", "sfc") )
  expect_true( is_multilinestring( res ) )

  m <- as.matrix( df )
  m <- matrix( as.integer( m ), ncol = 4 )
  res <- sfheaders:::rcpp_sfc_multilinestring( m, c(2,3), c(0), c(1), "" )
  expect_true( is_multilinestring( res ) )

  res <- sfheaders:::rcpp_sfc_multilinestring( df, c("x","y"),c("p_id"),c("l_id"), "")
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
  res <- sfheaders:::rcpp_sfc_multilinestrings( lst, "" )
  expect_true( all( sapply( res, is_multilinestring ) ) )

})
