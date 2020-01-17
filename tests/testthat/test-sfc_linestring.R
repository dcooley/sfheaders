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

  v <- c(1.2,3)
  res <- sfheaders:::rcpp_sfc_linestring(v, NULL, NULL)
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )
  expect_true( is_linestring( res ) )

  m <- matrix(1:4, ncol = 2)
  m <- cbind(c(1L,1L), m)
  res <- sfheaders:::rcpp_sfc_linestring(m, c(1L,2L), 0L)
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )
  expect_true( is_linestring( res ) )

  m <- matrix(1:4, ncol = 2)
  res <- sfheaders:::rcpp_sfc_linestring(m, NULL, NULL)
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )
  expect_true( is_linestring( res ) )

  m <- matrix(c(1.2,3,4,5), ncol = 2)
  res <- sfheaders:::rcpp_sfc_linestring(m, NULL, NULL)
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )
  expect_true( is_linestring( res ) )

  m <- matrix(1:4, ncol = 2)
  res <- sfheaders:::rcpp_sfc_linestring(m, c(0,1), NULL)
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )
  expect_true( is_linestring( res ) )

  m <- matrix(c(1.2,3,4,5), ncol = 2)
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
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfc_linestring(df, c("V1","V2"), NULL)
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )
  expect_true( is_linestring( res ) )

  m <- matrix(c(1.2,3,4,5), ncol = 2)
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfc_linestring(df, c("V1","V2"), NULL)
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
  m <- cbind(m, c(1L,1L,2L,2L))
  res <- sfheaders:::rcpp_sfc_linestring(m, c(0L,1L), 2L)
  expect_true( is_linestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  res <- sfheaders:::rcpp_sfc_linestring(m, c(0L,1L), 2L)
  expect_true( is_linestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )

  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1))
  res <- sfheaders:::rcpp_sfc_linestring(m, c(0L,1L), 2L)
  expect_true( is_linestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_linestring(df, c(0,1), 2)
  expect_true( is_linestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1L,1L,2L,2L) )
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfc_linestring(m, c("V1","V2"), NULL )
  expect_true( is_linestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2) )
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfc_linestring(m, c("V1","V2"), NULL )
  expect_true( is_linestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )

  m <- matrix(c(1.2,2:8), ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_linestring(df, c("V1","V2"), NULL )
  expect_true( is_linestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )

  m <- matrix(1L:4L, ncol = 2)
  m <- cbind(c(1L,1L), m)
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfc_linestring(m, c("V1","V2"), "V3")
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )
  expect_true( is_linestring( res ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2) )
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfc_linestring(m, c("V1","V2"), "V3" )
  expect_true( is_linestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )

  m <- matrix(c(1.2,2:8), ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_linestring(df, c("V1","V2"), "V3" )
  expect_true( is_linestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )



  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_linestring(df, c("V1","V2"), c("V3"))
  expect_true( is_linestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )

  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_linestring(df, c("V1","V2"), c("V3"))
  expect_true( is_linestring( res ) )
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )


  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_linestring(df, c(0L,1L), 2L )
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

test_that("vectorised version works",{

  is_linestring <- function(x) {
    y <- sapply( x, function(y) is.matrix(unclass(y)))
    z <- sapply( x, function(y) attr( y, "class")[2] == "LINESTRING")
    return( all(y) & all(z))
  }

  m1 <- matrix(1:12, ncol = 3)
  m2 <- matrix(1:12, ncol = 3)
  lst <- list( m1, m2 )
  res <- sfheaders:::rcpp_sfc_linestrings( lst )
  expect_true( all( sapply( res, is_linestring ) ) )

})

test_that("issue 38 is fixed", {

  df <- data.frame(
    x = 1:10
    , y = 1:10
    , z = 1:10
    # , m = 1:10
    , id = c(1,1,1,1,1,2,2,2,2,2)
  )

  sfc <- sfheaders::sfc_linestring(df, linestring_id = "id")
  expect_true( all( unclass( attr( sfc, "z_range" ) ) == c(1, 10) ) )
  expect_true( all( is.na( unclass( attr( sfc, "m_range" ) ) ) ) )
})
