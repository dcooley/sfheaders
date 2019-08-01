context( "sfc_multipoints " )

test_that("various objects converted to sfc_MULTIPOINT objects",{

  m <- matrix()
  expect_error( sfheaders:::rcpp_sfc_multipoint( m, NULL, NULL ), "sfheaders - unsupported multipoint type")

  m <- matrix(c(0,0), ncol = 2)
  res <- sfheaders:::rcpp_sfc_multipoint( m, NULL, NULL )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOINT", "sfc") )
  expect_true( all( is.na( attr( res, "z_range" ) ) ) )

  m <- matrix(c(0,0,1,1), ncol = 2, byrow = T)
  res <- sfheaders:::rcpp_sfc_multipoint( m, NULL, NULL )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOINT", "sfc") )

  m <- matrix(c(0,0,0,0,1,1), ncol = 3, byrow = T)
  res <- sfheaders:::rcpp_sfc_multipoint( m, NULL, NULL )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOINT", "sfc") )
  expect_true( all( attr( res, "z_range") == c(0,1) ) )

  m <- matrix(c(0,0,1,1), ncol = 2, byrow = T)
  res <- sfheaders:::rcpp_sfc_multipoint( m, c(0,1), NULL )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOINT", "sfc") )

  m <- matrix(c(0,0,1,1), ncol = 2, byrow = T)
  expect_error( sfheaders:::rcpp_sfc_multipoint( m, NULL, 0 ), "sfheaders - incorrect number of geometry columns" )

  m <- matrix(c(0,0,1,1), ncol = 2, byrow = T)
  res <- sfheaders:::rcpp_sfc_multipoint( m, c(0,1), 0 )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOINT", "sfc") )

  m <- matrix(c(0,0,1,1), ncol = 2, byrow = T)
  expect_error( sfheaders:::rcpp_sfc_multipoint( m, NULL, c(0) ), "sfheaders - incorrect number of geometry columns")

  m <- matrix(c(0,0,0,0,1,1,1,1,1), ncol = 3, byrow = T)
  res <- sfheaders:::rcpp_sfc_multipoint( m, c(1,2), c(0) )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOINT", "sfc") )


  df <- data.frame(x = 1, y = 1)
  res <- sfheaders:::rcpp_sfc_multipoint(df, NULL, NULL)
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOINT", "sfc") )

  df <- data.frame(id = 1, x = 1, y = 1)
  res <- sfheaders:::rcpp_sfc_multipoint(df, c("x","y"), c("id") )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOINT", "sfc") )

  df <- data.frame(id = 1:2, x = 1:2, y = 1:2)
  res <- sfheaders:::rcpp_sfc_multipoint(df, c("x","y"), c("id") )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOINT", "sfc") )

  df <- data.frame(id = 1, x = 1:2, y = 1:2)
  res <- sfheaders:::rcpp_sfc_multipoint(df, c("x","y"), c("id") )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOINT", "sfc") )

})

test_that("after refactoring issue14 I haven't lost anything",{

  is_multipoint <- function(x) {
    y <- sapply( x, function(y) is.matrix(unclass(y)))
    z <- sapply( x, function(y) attr( y, "class")[2] == "MULTIPOINT")
    return( all(y) & all(z))
  }

  v <- 1:3
  res <- sfheaders:::rcpp_sfc_multipoint(v, NULL, NULL)
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOINT", "sfc") )
  expect_true( is_multipoint( res ) )

  m <- matrix(1:4, ncol = 2)
  res <- sfheaders:::rcpp_sfc_multipoint(m, NULL, NULL)
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOINT", "sfc") )
  expect_true( is_multipoint( res ) )

  m <- matrix(1:4, ncol = 2)
  res <- sfheaders:::rcpp_sfc_multipoint(m, c(0,1), NULL)
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOINT", "sfc") )
  expect_true( is_multipoint( res ) )

  m <- matrix(1:4, ncol = 2)
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_multipoint(df, NULL, NULL)
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOINT", "sfc") )
  expect_true( is_multipoint( res ) )

  m <- matrix(1:4, ncol = 2)
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_multipoint(df, c(0,1), NULL)
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOINT", "sfc") )
  expect_true( is_multipoint( res ) )

  m <- matrix(1:4, ncol = 2)
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_multipoint(df, c("V1","V2"), NULL)
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOINT", "sfc") )
  expect_true( is_multipoint( res ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  res <- sfheaders:::rcpp_sfc_multipoint(m, NULL, 2)
  expect_true( is_multipoint( res ) )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOINT", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  res <- sfheaders:::rcpp_sfc_multipoint(m, c(0,1), 2)
  expect_true( is_multipoint( res ) )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOINT", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_multipoint(df, NULL, 2)
  expect_true( is_multipoint( res ) )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOINT", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_multipoint(df, c(0,1), 2)
  expect_true( is_multipoint( res ) )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOINT", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_multipoint(df, c("V1","V2"), c("V3"))
  expect_true( is_multipoint( res ) )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOINT", "sfc") )

  m <- matrix(1:4, ncol = 2)
  expect_error( sfheaders:::rcpp_sfc_multipoint(m, NULL, 0), "sfheaders - incorrect number of geometry columns")


})

