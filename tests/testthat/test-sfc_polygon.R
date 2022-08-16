context("sfc_POLYGON")

test_that("various objects converted to sfc_polygon",{

  is_polygon <- function(x) {
    y <- sapply( x, function(y) is.list( unclass( y ) ) )
    z <- sapply( x, function(y) attr( y, "class")[2] == "POLYGON")
    return( all(y) & all(z))
  }

  # v <- 1:3
  # expect_error( sfheaders:::rcpp_sfc_polygon(v, NULL, NULL, NULL, "", close = FALSE), "geometries - unsupported object")

  m <- matrix(1:4, ncol = 2)
  res <- sfheaders:::rcpp_sfc_polygon(m, NULL, NULL, NULL, "", close = FALSE)
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

  m <- matrix(c(1.2,3,4,5), ncol = 2)
  res <- sfheaders:::rcpp_sfc_polygon(m, NULL, NULL, NULL, "", close = FALSE)
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

  m <- matrix(1:4, ncol = 2)
  res <- sfheaders:::rcpp_sfc_polygon(m, c(0L,1L), NULL, NULL, "", close = FALSE)
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

  m <- matrix(c(1.2,3,4,5), ncol = 2)
  res <- sfheaders:::rcpp_sfc_polygon(m, c(0L,1L), NULL, NULL, "", close = FALSE)
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

  m <- matrix(1:4, ncol = 2)
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_polygon(df, NULL, NULL, NULL, "", close = FALSE)
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

  m <- matrix(1:4, ncol = 2)
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_polygon(df, c(0L,1L), NULL, NULL, "", close = FALSE)
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

  m <- matrix(1:4, ncol = 2)
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfc_polygon(df, c("V1","V2"), NULL, NULL, "", close = FALSE)
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

  m <- matrix(c(1.2,3,4,5), ncol = 2)
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfc_polygon(df, c("V1","V2"), NULL, NULL, "", close = FALSE)
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )


  m <- matrix(1:4, ncol = 2)
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_polygon(df, c("V1","V2"), NULL, NULL, "", close = FALSE)
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  res <- sfheaders:::rcpp_sfc_polygon(m, NULL, 2L, NULL, "", close = FALSE)
  expect_true( is_polygon( res ) )
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  res <- sfheaders:::rcpp_sfc_polygon(m, c(0L,1L), 2L, NULL, "", close = FALSE)
  expect_true( is_polygon( res ) )
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_polygon(df, NULL, 2L, NULL, "", close = FALSE)
  expect_true( is_polygon( res ) )
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1L,1L,2L,2L))
  res <- sfheaders:::rcpp_sfc_polygon(m, c(0L,1L), 2L, NULL, "", close = FALSE)
  expect_true( is_polygon( res ) )
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  res <- sfheaders:::rcpp_sfc_polygon(m, c(0L,1L), 2L, NULL, "", close = FALSE)
  expect_true( is_polygon( res ) )
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )

  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1))
  res <- sfheaders:::rcpp_sfc_polygon(m, c(0L,1L), 2L, NULL, "", close = FALSE)
  expect_true( is_polygon( res ) )
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_polygon(df, c(0L,1L), 2L, NULL, "", close = FALSE)
  expect_true( is_polygon( res ) )
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1L,1L,2L,2L) )
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfc_polygon(m, c("V1","V2"), NULL, NULL, "", close = FALSE)
  expect_true( is_polygon( res ) )
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2) )
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfc_polygon(m, c("V1","V2"), NULL, NULL, "", close = FALSE)
  expect_true( is_polygon( res ) )
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )

  m <- matrix(c(1.2,2:8), ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_polygon(df, c("V1","V2"), NULL, NULL, "", close = FALSE)
  expect_true( is_polygon( res ) )
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2) )
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfc_polygon(m, c("V1","V2"), "V3", NULL, "", close = FALSE)
  expect_true( is_polygon( res ) )
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1L,1L,2L,2L) )
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfc_polygon(m, c("V1","V2"), "V3", "V3", "", close = FALSE)
  expect_true( is_polygon( res ) )
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2) )
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfc_polygon(m, c("V1","V2"), "V3", "V3", "", close = FALSE)
  expect_true( is_polygon( res ) )
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )

  m <- matrix(c(1.2,2:8), ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_polygon(df, c("V1","V2"), "V3", NULL, "", close = FALSE)
  expect_true( is_polygon( res ) )
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_polygon(df, c("V1","V2"), c("V3"), NULL, "", close = FALSE)
  expect_true( is_polygon( res ) )
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )

  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_polygon(df, c("V1","V2"), c("V3"), NULL, "", close = FALSE)
  expect_true( is_polygon( res ) )
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )


  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_polygon(df, c(0L,1L), 2L, NULL, "", close = FALSE)
  expect_true( is_polygon( res ) )
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )

  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1L))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_polygon(df, c(0L,1L), NULL, 2L, "", close = FALSE)
  expect_true( is_polygon( res ) )
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )

  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sfc_polygon(df, c("V1","V2"), NULL, "V3", "", close = FALSE)
  expect_true( is_polygon( res ) )
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )

  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1))
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfc_polygon(m, c("V1","V2"), NULL, "V3", "", close = FALSE)
  expect_true( is_polygon( res ) )
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )

  m <- matrix(1:4, ncol = 2)
  expect_error( sfheaders:::rcpp_sfc_polygon(m, NULL, 0L, NULL, "", close = FALSE), "sfheaders - can't work out the dimension")

})

test_that("data.frame with non-numeric id columns work",{

  is_polygon <- function(x) {
    y <- sapply( x, function(y) is.list( unclass( y ) ) )
    z <- sapply( x, function(y) attr( y, "class")[2] == "POLYGON")
    return( all(y) & all(z))
  }

  df <- data.frame(
    p_id = letters[c(1,1,1,1,2,2,2,2)]
    , l_id = c(1,1,1,1,1,1,1,1)
    , x = c(1,2,3,1,4,5,6,4)
    , y = c(1,2,3,1,4,5,6,4)
  )

  res <- sfheaders::sfc_polygon(
    obj = df
    , x = "x"
    , y = "y"
    , linestring_id = "p_id"
    , close = FALSE
  )
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

})



test_that("sfc_polygon works", {

  is_polygon <- function(x) {
    y <- sapply( x, function(y) is.list( unclass( y ) ) )
    z <- sapply( x, function(y) attr( y, "class")[2] == "POLYGON")
    return( all(y) & all(z))
  }

  df <- data.frame(
    p_id = c(1,1,1,1,2,2,2,2)
    , l_id = c(1,1,1,1,1,1,1,1)
    , x = c(1,2,3,1,4,5,6,4)
    , y = c(1,2,3,1,4,5,6,4)
  )

  res <- sfheaders:::rcpp_sfc_polygon( df, NULL, NULL, NULL, "", close = FALSE)
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

  res <- sfheaders:::rcpp_sfc_polygon( df, NULL, NULL, c(0L), "", close = FALSE)
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

  res <- sfheaders:::rcpp_sfc_polygon( df, NULL, c(0L), NULL, "", close = FALSE)
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

  res <- sfheaders:::rcpp_sfc_polygon( df, c("x","y"), NULL, NULL, "", close = FALSE)
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

  res <- sfheaders:::rcpp_sfc_polygon( df, c(2L,3L), NULL, NULL, "", close = FALSE)
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

  res <- sfheaders:::rcpp_sfc_polygon( df, NULL, 0L, 1L, "", close = FALSE)
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

  res <- sfheaders:::rcpp_sfc_polygon( df, c(2L,3L), 0L, NULL, "", close = FALSE)
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

  res <- sfheaders:::rcpp_sfc_polygon( df, c(2L,3L), NULL, 1L, "", close = FALSE)
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

  res <- sfheaders:::rcpp_sfc_polygon( df, c(2L,3L), c(0L), c(1L), "", close = FALSE)
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

  m <- as.matrix( df )
  m <- matrix( as.integer( m ), ncol = 4 )
  res <- sfheaders:::rcpp_sfc_polygon( m, c(2L,3L), c(0L), c(1L), "", close = FALSE)
  expect_true( is_polygon( res ) )

  res <- sfheaders:::rcpp_sfc_polygon( df, c("x","y"),c("p_id"),c("l_id"), "", close = FALSE)
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

})

test_that("data.frame with non-numeric id columns work",{


  is_polygon <- function(x) {
    y <- sapply( x, function(y) is.list( unclass( y ) ) )
    z <- sapply( x, function(y) attr( y, "class")[2] == "POLYGON")
    return( all(y) & all(z))
  }

  df <- data.frame(
    p_id = letters[c(1,1,1,1,2,2,2,2)]
    , l_id = c(1,1,1,1,1,1,1,1)
    , x = c(1,2,3,1,4,5,6,4)
    , y = c(1,2,3,1,4,5,6,4)
    , stringsAsFactors = F
  )

  res <- sfheaders::sfc_polygon(
    obj = df
    , x = "x"
    , y = "y"
    , polygon_id = "p_id"
    , linestring_id = "l_id"
    , close = FALSE
    )
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

  df <- data.frame(
    p_id = letters[c(1,1,1,1,2,2,2,2)]
    , l_id = letters[c(1,1,1,1,1,1,1,1)]
    , x = c(1,2,3,1,4,5,6,4)
    , y = c(1,2,3,1,4,5,6,4)
    , stringsAsFactors = F
  )

  res <- sfheaders::sfc_polygon(
    obj = df
    , x = "x"
    , y = "y"
    , polygon_id = "p_id"
    , linestring_id = "l_id"
    , close = FALSE
  )
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

})


test_that("vectorised version works",{

  is_polygon <- function(x) {
    y <- sapply( x, function(y) is.list( unclass( y ) ) )
    z <- sapply( x, function(y) attr( y, "class")[2] == "POLYGON")
    return( all(y) & all(z))
  }

  m1 <- matrix(1:12, ncol = 3)
  m2 <- matrix(1:12, ncol = 3)
  lst <- list( m1, m2 )
  res <- sfheaders:::rcpp_sfc_polygons( lst, "", close = FALSE )
  expect_true( all( sapply( res, is_polygon ) ) )

})
