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

  res <- sfheaders:::rcpp_sf_polygon( df, c(2:3), 0L, 1L, close = F )
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

  expect_error( sfheaders:::rcpp_sf_polygon( df, c(2:3), 0L, 1L ), "sfheaders - error indexing lines, perhaps caused by un-ordered data?" ) ## because the id2 is out of order
  expect_error( sfheaders:::rcpp_sf_linestring( df, c(2:3), 1L ), "sfheaders - error indexing lines, perhaps caused by un-ordered data?" )
  expect_error( sfheaders:::rcpp_sf_linestring( df, c(2:3), 0 ), "sfheaders - linestring columns types are different")

})

test_that("unordered ids cause issues",{

  df <- data.frame(
    id1 = c(2,2,2,2,2,1,1,1,1,1)
    , x = 1:10
    , y = 1:10
    , z = 1:10
    , m = 1:10
  )

  res <- sfheaders::sf_linestring(df, linestring_id = "id1")
  #expect_true( !any( res$id == unique( df$id1 ) ) )
  expect_true( all( res$id == unique( df$id1 ) ) )

  ## sub-group order works
  df <- data.frame(
    id1 = c(1,1,1,1,1,2,2,2,2,2)
    , id2 = c(2,2,3,3,3,1,1,1,2,2)
    , x = 1:10
    , y = 1:10
    , z = 1:10
    , m = 1:10
  )

  res <- sfheaders::sf_polygon(df, polygon_id = "id1", linestring_id = "id2", close = FALSE)
  expect_true( all( res$id == unique( df$id1 ) ) )
  m1 <- res$geometry[[1]][[1]]
  m2 <- res$geometry[[1]][[2]]
  m3 <- res$geometry[[2]][[1]]
  m4 <- res$geometry[[2]][[2]]

  expect_equal( m1, unname( as.matrix( df[ df$id1 == 1 & df$id2 == 2, 3:6 ] ) ) )
  expect_equal( m2, unname( as.matrix( df[ df$id1 == 1 & df$id2 == 3, 3:6 ] ) ) )
  expect_equal( m3, unname( as.matrix( df[ df$id1 == 2 & df$id2 == 1, 3:6 ] ) ) )
  expect_equal( m4, unname( as.matrix( df[ df$id1 == 2 & df$id2 == 2, 3:6 ] ) ) )

  ## sub-group order doesn't work
  df <- data.frame(
    id1 = c(1,1,1,1,1,2,2,2,2,2)
    , id2 = c(2,2,3,3,3,3,3,1,2,2)
    , x = 1:10
    , y = 1:10
    , z = 1:10
    , m = 1:10
  )

  res <- sfheaders::sf_polygon(df, polygon_id = "id1", linestring_id = "id2", close = FALSE )
  expect_true( all( res$id == unique( df$id1 ) ) )
  m1 <- res$geometry[[1]][[1]]
  m2 <- res$geometry[[1]][[2]]
  m3 <- res$geometry[[2]][[1]]
  m4 <- res$geometry[[2]][[2]]
  m5 <- res$geometry[[2]][[3]]


  ## these tests will pass, but the coordinates will be wronge, becase the ID order is wrong
  expect_equal( m1, unname( as.matrix( df[ df$id1 == 1 & df$id2 == 2, 3:6 ] ) ) )
  expect_equal( m2, unname( as.matrix( df[ df$id1 == 1 & df$id2 == 3, 3:6 ] ) ) )
  expect_equal( m3, unname( as.matrix( df[ df$id1 == 2 & df$id2 == 3, 3:6 ] ) ) )
  expect_equal( m4, unname( as.matrix( df[ df$id1 == 2 & df$id2 == 1, 3:6 ] ) ) )
  expect_equal( m5, unname( as.matrix( df[ df$id1 == 2 & df$id2 == 2, 3:6 ] ) ) )




  df <- data.frame(
    id1 = c(1,1,1,1,1,2,2,2,2,2)
    , id2 = c(2,2,3,3,3,3,3,1,2,2)
    , id3 = c(1,2,1,1,1,1,2,2,1,2)
    , x = 1:10
    , y = 1:10
    , z = 1:10
    , m = 1:10
  )

  res <- sfheaders::sf_multipolygon(df, multipolygon_id = "id1", polygon_id = "id2", linestring_id = "id3", close = FALSE )
  expect_true( all( res$id == unique( df$id1 ) ) )

  m1 <- res$geometry[[1]][[1]][[1]]
  m2 <- res$geometry[[1]][[1]][[2]]
  m3 <- res$geometry[[1]][[2]][[1]]


  m4 <- res$geometry[[2]][[1]][[1]]
  m5 <- res$geometry[[2]][[1]][[2]]

  m6 <- res$geometry[[2]][[2]][[1]]

  m7 <- res$geometry[[2]][[3]][[1]]
  m8 <- res$geometry[[2]][[3]][[2]]


  ## these tests will pass, but the coordinates will be wronge, becase the ID order is wrong
  expect_equal( m1, unname( as.matrix( df[ df$id1 == 1 & df$id2 == 2 & df$id3 == 1, 4:7 ] ) ) )
  expect_equal( m2, unname( as.matrix( df[ df$id1 == 1 & df$id2 == 2 & df$id3 == 2, 4:7 ] ) ) )
  expect_equal( m3, unname( as.matrix( df[ df$id1 == 1 & df$id2 == 3 & df$id3 == 1, 4:7 ] ) ) )

  expect_equal( m4, unname( as.matrix( df[ df$id1 == 2 & df$id2 == 3 & df$id3 == 1, 4:7 ] ) ) )
  expect_equal( m5, unname( as.matrix( df[ df$id1 == 2 & df$id2 == 3 & df$id3 == 2, 4:7 ] ) ) )
  expect_equal( m6, unname( as.matrix( df[ df$id1 == 2 & df$id2 == 1 & df$id3 == 2, 4:7 ] ) ) )
  expect_equal( m7, unname( as.matrix( df[ df$id1 == 2 & df$id2 == 2 & df$id3 == 1, 4:7 ] ) ) )
  expect_equal( m8, unname( as.matrix( df[ df$id1 == 2 & df$id2 == 2 & df$id3 == 2, 4:7 ] ) ) )


})


test_that("R API to sf works",{

  is_sf <- function(x) {
    a <- attributes(x)
    all( a$class == c("sf", "data.frame") ) & a$sf_column == "geometry"
  }

  df <- data.frame(
    multi_poly_id = rep(1,10)
    , poly_id = c(1,1,1,1,1,1,1,2,2,2)
    , line_id = rep(1,10)
    , x = 1:10
    , y = 1:10
  )

  res <- sf_point(obj = df, x = "x", y = "y")
  expect_true( is_sf( res ) )
  expect_true( nrow( res ) == nrow( df ) )

  res <- sf_multipoint(obj = df, x = "x", y = "y", multipoint_id = "poly_id")
  expect_true( is_sf( res ) )
  expect_true( nrow( res ) == length(unique( df$poly_id ) ) )

  res <- sf_linestring(obj = df, x = "x", y = "y", linestring_id = "poly_id")
  expect_true( is_sf( res ) )
  expect_true( nrow( res ) == length(unique( df$poly_id ) ) )

  res <- sf_multilinestring(obj = df, x = "x", y = "y", multilinestring_id = "poly_id")
  expect_true( is_sf( res ) )
  expect_true( nrow( res ) == length(unique( df$poly_id ) ) )

  res <- sf_polygon(obj = df, x = "x", y = "y", polygon_id = "poly_id")
  expect_true( is_sf( res ) )
  expect_true( nrow( res ) == length(unique( df$poly_id ) ) )

  res <- sf_multipolygon(obj = df, x = "x", y = "y", multipolygon_id = "poly_id")
  expect_true( is_sf( res ) )
  expect_true( nrow( res ) == length(unique( df$poly_id ) ) )

})

test_that("string ids work",{

  is_sf <- function(x) {
    a <- attributes(x)
    all( a$class == c("sf", "data.frame") ) & a$sf_column == "geometry"
  }

  df <- data.frame(
    id = letters[1:5]
    , x = 1:5
    , y = 1:5
    , stringsAsFactors = FALSE
  )
  res <- sfheaders:::sf_linestring(
    obj = df
    , x = "x"
    , y = "y"
    , linestring_id = "id"
  )
  expect_true( is_sf( res ) )
  expect_true( nrow( res ) == length(unique( df$id ) ) )

  ## and NULL ids
  res <- sfheaders:::sf_linestring(
    obj = df
    , x = "x"
    , y = "y"
    , linestring_id = NULL
  )

  expect_true( is_sf( res ) )
  expect_true( nrow( res ) == 1 )

  ## logical ids
  df <- data.frame(
    id = c(T,T,T,F,F)
    , x = 1:5
    , y = 1:5
    , stringsAsFactors = FALSE
  )

  res <- sfheaders:::sf_linestring(
    obj = df
    , x = "x"
    , y = "y"
    , linestring_id = "id"
  )
  expect_true( is_sf( res ) )
  expect_true( nrow( res ) == length(unique( df$id ) ) )

})

