context("sf")

test_that("sf objects are created",{

  is_sf <- function(x) {
    a <- attributes(x)
    all( a$class == c("sf", "data.frame") ) & a$sf_column == "geometry"
  }

  df <- data.frame(
    id = c(1,1,1,1,1,2,2,2,2,2)
    , x = 1:10
    , y = 1:10
    , z = 1:10
    , m = 1:10
  )

  res <- sfheaders:::rcpp_sf_point(df, 1:4 )
  expect_true( is_sf( res ) )

  res <- sfheaders:::rcpp_sf_point(df, 1:2 )
  expect_true( is_sf( res ) )

  res <- sfheaders:::rcpp_sf_multipoint(df, 1:4, NULL )
  expect_true( is_sf( res ) )

  res <- sfheaders:::rcpp_sf_linestring(df, 1:4, NULL )
  expect_true( is_sf( res ) )

  res <- sfheaders:::rcpp_sf_multilinestring(df, 1:4, NULL, NULL )
  expect_true( is_sf( res ) )

  res <- sfheaders:::rcpp_sf_polygon(df, 1:4, NULL, NULL )
  expect_true( is_sf( res ) )

  res <- sfheaders:::rcpp_sf_multipolygon(df, 1:4, NULL, NULL, NULL )
  expect_true( is_sf( res ) )
})

test_that("correct number of rows returned",{

  is_sf <- function(x) {
    a <- attributes(x)
    all( a$class == c("sf", "data.frame") ) & a$sf_column == "geometry"
  }

  df <- data.frame(
    id1 = c(1,1,1,1,1,2,2,2,2,2)
    , id2 = c(1,1,2,2,1,1,2,2,3,3)
    , x = 1:10
    , y = 1:10
    , z = 1:10
    , m = 1:10
  )

  res <- sfheaders:::rcpp_sf_point( df, c(2:3) )
  expect_true( nrow(res) == nrow( df ) )

  res <- sfheaders:::rcpp_sf_multipoint( df, c(2:3), 0L )
  expect_true( nrow(res) == length( unique( df$id1 ) ) )
  expect_true( all( res$id == unique( df$id1 ) ) )

  res <- sfheaders:::rcpp_sf_linestring( df, c(2:3), 0L )
  expect_true( nrow(res) == length( unique( df$id1 ) ) )
  expect_true( all( res$id == unique( df$id1 ) ) )

  res <- sfheaders:::rcpp_sf_multilinestring( df, c(2:3), 0L, NULL )
  expect_true( nrow(res) == length( unique( df$id1 ) ) )
  expect_true( all( res$id == unique( df$id1 ) ) )

  res <- sfheaders:::rcpp_sf_polygon( df, c(2:3), 0L, NULL )
  expect_true( nrow(res) == length( unique( df$id1 ) ) )
  expect_true( all( res$id == unique( df$id1 ) ) )

  res <- sfheaders:::rcpp_sf_multipolygon( df, c(2:3), 0L, NULL, NULL )
  expect_true( nrow(res) == length( unique( df$id1 ) ) )
  expect_true( all( res$id == unique( df$id1 ) ) )

})




test_that("ID order maintained",{

  is_sf <- function(x) {
    a <- attributes(x)
    all( a$class == c("sf", "data.frame") ) & a$sf_column == "geometry"
  }

  df <- data.frame(
    id1 = c(1,1,1,1,1,2,2,2,2,2)
    , id2 = c(1,1,2,2,2,1,2,2,3,3)
    , x = 1:10
    , y = 1:10
    , z = 1:10
    , m = 1:10
  )

  res <- sfheaders:::rcpp_sf_point( df, c(2:3) )
  m1 <- unclass( res$geometry[[1]] )
  expect_equal( m1[1], df[1, "x"] )
  expect_equal( m1[2], df[1, "y"] )

  m7 <- unclass( res$geometry[[7]] )
  expect_equal( m7[1], df[7, "x"] )
  expect_equal( m7[2], df[7, "y"] )


  res <- sfheaders:::rcpp_sf_multipoint( df, c(2:3), 0L )
  m1 <- unclass( res$geometry[[1]] )
  m2 <- unclass( res$geometry[[2]] )

  expect_equal( m1[, 1], df[ df$id1 == 1, "x" ] )
  expect_equal( m1[, 2], df[ df$id1 == 1, "y" ] )

  expect_equal( m2[, 1], df[ df$id1 == 2, "x" ] )
  expect_equal( m2[, 2], df[ df$id1 == 2, "y" ] )

  res <- sfheaders:::rcpp_sf_polygon( df, c(2:3), 0L, 1L )
  m1 <- res$geometry[[1]][[1]]
  m2 <- res$geometry[[1]][[2]]

  m3 <- res$geometry[[2]][[1]]
  m4 <- res$geometry[[2]][[2]]
  m5 <- res$geometry[[2]][[3]]

  expect_equal( m1[, 1], df[ df$id1 == 1 & df$id2 == 1, "x"] )
  expect_equal( m1[, 2], df[ df$id1 == 1 & df$id2 == 1, "y"] )

  expect_equal( m2[, 1], df[ df$id1 == 1 & df$id2 == 2, "x"] )
  expect_equal( m2[, 2], df[ df$id1 == 1 & df$id2 == 2, "y"] )

  expect_equal( m3[, 1], df[ df$id1 == 2 & df$id2 == 1, "x"] )
  expect_equal( m3[, 2], df[ df$id1 == 2 & df$id2 == 1, "y"] )

  expect_equal( m4[, 1], df[ df$id1 == 2 & df$id2 == 2, "x"] )
  expect_equal( m4[, 2], df[ df$id1 == 2 & df$id2 == 2, "y"] )

  expect_equal( m5[, 1], df[ df$id1 == 2 & df$id2 == 3, "x"] )
  expect_equal( m5[, 2], df[ df$id1 == 2 & df$id2 == 3, "y"] )

  df <- data.frame(
    id1 = c(1,1,1,1,1,2,2,2,2,2)
    , id2 = c(1,1,2,2,1,1,2,2,3,3) ## this errored in sf_polygon
    , x = 1:10
    , y = 1:10
    , z = 1:10
    , m = 1:10
  )

  # #res <- sfheaders:::rcpp_sf_polygon( df, c(2:3), 0L, 1L )
  #
  # res$geometry[[1]]
  # res$geometry[[2]]

  expect_error( sfheaders:::rcpp_sf_polygon( df, c(2:3), 0L, 1L ), "Not a matrix." ) ## because the id2 is out of order

})


