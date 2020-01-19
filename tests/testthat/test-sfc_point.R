context("sfc_POINTS")

test_that("sfc_points works for various objects",{

  x <- c(1:3)
  res <- sfheaders:::rcpp_sfc_point( x, NULL )
  expect_true( all( attr(res, "class") == c("sfc_POINT", "sfc") ) )
  expect_true( all( attr(res, "z_range") == c(3,3) ) )

  x <- c(1:10)
  expect_error( sfheaders:::rcpp_sfc_point( x, NULL ), "sfheaders - invalid dimension" )

  x <- matrix( c(1:10) , ncol = 2 )
  res <- sfheaders:::rcpp_sfc_point( x, NULL )
  expect_true( all( attr(res, "class") == c("sfc_POINT", "sfc") ) )
  expect_true( all( is.na( unclass( attr(res, "z_range") ) ) ) )

  x <- matrix( c(1:12) , ncol = 3 )
  res <- sfheaders:::rcpp_sfc_point( x, NULL )
  expect_true( all( attr(res, "class") == c("sfc_POINT", "sfc") ) )
  expect_true( all( attr(res, "z_range") == c(9, 12) ) )

  x <- matrix( c(1:12) , ncol = 4 )
  res <- sfheaders:::rcpp_sfc_point( x, NULL )
  expect_true( all( attr(res, "class") == c("sfc_POINT", "sfc") ) )
  expect_true( all( attr(res, "z_range") == c(7,9) ) )
  expect_true( all( attr(res, "m_range") == c(10,12) ) )

})

test_that("sfc_points works from R",{

  x <- c(1:3)
  res <- sfc_point(x)
  expect_true( length( res ) == 1 )
  expect_equal( unlist( res ), x)

  x <- matrix(1:4, ncol = 2)
  res <- sfc_point( x )
  expect_equal( unclass( res[[1]] ), c(1,3) )

})

test_that("after refactoring issue14 I haven't lost anything",{

  is_point <- function(x) {
    y <- sapply( x, function(y) is.vector(unclass(y)))
    z <- sapply( x, function(y) attr( y, "class")[2] == "POINT")
    return( all(y) & all(z))
  }

  v <- 1:4
  res <- sfheaders:::rcpp_sfc_point( v, NULL )
  expect_equal( attr( res, "class" ), c("sfc_POINT", "sfc") )
  expect_true( is_point( res ) )

  v <- c(1.2,2,3,4)
  res <- sfheaders:::rcpp_sfc_point( v, NULL )
  expect_equal( attr( res, "class" ), c("sfc_POINT", "sfc") )
  expect_true( is_point( res ) )

  m <- matrix(1:4, ncol = 2)
  res <- sfheaders:::rcpp_sfc_point(m, NULL )
  expect_equal( attr( res, "class" ), c("sfc_POINT", "sfc") )
  expect_true( is_point( res ) )

  m <- matrix(c(1.2,2:4), ncol = 2)
  res <- sfheaders:::rcpp_sfc_point(m, NULL )
  expect_equal( attr( res, "class" ), c("sfc_POINT", "sfc") )
  expect_true( is_point( res ) )

  m <- matrix(1:4, ncol = 2)
  res <- sfheaders:::rcpp_sfc_point(m, c(0,1) )
  expect_equal( attr( res, "class" ), c("sfc_POINT", "sfc") )
  expect_true( is_point( res ) )

  m <- matrix(c(1.2,2,3,4), ncol = 2)
  res <- sfheaders:::rcpp_sfc_point(m, c(0,1) )
  expect_equal( attr( res, "class" ), c("sfc_POINT", "sfc") )
  expect_true( is_point( res ) )

  m <- matrix(1:4, ncol = 2)
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_point(df, NULL )
  expect_equal( attr( res, "class" ), c("sfc_POINT", "sfc") )
  expect_true( is_point( res ) )

  m <- matrix(1:4, ncol = 2)
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_point(df, c(0,1) )
  expect_equal( attr( res, "class" ), c("sfc_POINT", "sfc") )
  expect_true( is_point( res ) )

  m <- matrix(1:4, ncol = 2)
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_point(df, c("V1","V2") )
  expect_equal( attr( res, "class" ), c("sfc_POINT", "sfc") )
  expect_true( is_point( res ) )

  m <- matrix(1L:4L, ncol = 2)
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfc_point(m, c("V1","V2") )
  expect_equal( attr( res, "class" ), c("sfc_POINT", "sfc") )
  expect_true( is_point( res ) )

  m <- matrix(1:4, ncol = 2)
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfc_point(m, c("V1","V2") )
  expect_equal( attr( res, "class" ), c("sfc_POINT", "sfc") )
  expect_true( is_point( res ) )

  m <- matrix(c(1.2,2,3,4), ncol = 2)
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfc_point(m, c("V1","V2") )
  expect_equal( attr( res, "class" ), c("sfc_POINT", "sfc") )
  expect_true( is_point( res ) )


  df <- data.frame(x=1,y=2)
  res <- sfc_point( df[0,] )
  expect_equal( attr( res, "class" ), c("sfc_POINT", "sfc") )
  expect_true( is_point( res ) )

  m <- matrix(c(1.1,2), ncol = 2)
  res <- sfc_point( m[0,] )
  expect_equal( attr( res, "class" ), c("sfc_POINT", "sfc") )
  expect_true( is_point( res ) )

  m <- matrix(as.integer( c(1,2) ), ncol = 2)
  res <- sfc_point( m[0,] )
  expect_equal( attr( res, "class" ), c("sfc_POINT", "sfc") )
  expect_true( is_point( res ) )

  m <- matrix(c(1.1,2), ncol = 2)
  res <- sfc_point( m[0,], x = 1, y = 2 )
  expect_equal( attr( res, "class" ), c("sfc_POINT", "sfc") )
  expect_true( is_point( res ) )

  m <- matrix(as.integer( c(1,2) ), ncol = 2)
  res <- sfc_point( m[0,], x = 1, y = 2)
  expect_equal( attr( res, "class" ), c("sfc_POINT", "sfc") )
  expect_true( is_point( res ) )

})

test_that("vectorised version works",{

  is_point <- function(x) {
    y <- sapply( x, function(y) is.vector(unclass(y)))
    z <- sapply( x, function(y) attr( y, "class")[2] == "POINT")
    return( all(y) & all(z))
  }

  m1 <- matrix(1:3, ncol = 3)
  m2 <- matrix(1:3, ncol = 3)
  lst <- list( m1, m2 )
  res <- sfheaders:::rcpp_sfc_points( lst )
  expect_true( all( sapply( res, is_point ) ) )

})

