context("sfg_to_multipolygon")

test_that("sfg multipolygon",{

  is_multipolygon <- function(x){
    cls <- attr( x, "class")
    cls[2] == "MULTIPOLYGON" & cls[3] == "sfg"
  }

  l1 <- matrix(c(0,0,0,1,1,1,1,0,0,0), ncol = 2, byrow = T)
  l2 <- matrix(c(2,2,2,5,5,5,5,2,2,2), ncol = 2, byrow = T)
  l3 <- matrix(c(3,3,3,4,4,4,4,3,3,3), ncol = 2, byrow = T)
  l1 <- cbind(1, l1)
  l2 <- cbind(1, l2)
  l3 <- cbind(2, l3)
  l1 <- cbind(1, l1)
  l2 <- cbind(2, l2)
  l3 <- cbind(2, l3)

  m <- rbind(l1, l2)
  m <- rbind(m, l3)

  mp <- sfheaders:::rcpp_sfg_multipolygon( m,  NULL, polygon_id = 0, line_id = 1, close = FALSE)
  res <- attr( mp, "class" )
  expect_equal( res, c("XY", "MULTIPOLYGON", "sfg") )
  r_res <- sfg_multipolygon(mp)

  expect_equal( mp[[1]][[1]], r_res[[1]][[1]] )
  expect_equal( mp[[2]][[1]], r_res[[2]][[1]] )
  expect_equal( mp[[2]][[2]], r_res[[2]][[2]] )

  mp <- sfheaders:::rcpp_sfg_multipolygon( m, c(2,3), polygon_id = 0, line_id = 1, close = FALSE)
  res <- attr( mp, "class" )
  expect_equal( res, c("XY", "MULTIPOLYGON", "sfg") )
  r_res <- sfg_multipolygon(mp)

  expect_equal( mp[[1]][[1]], r_res[[1]][[1]] )
  expect_equal( mp[[2]][[1]], r_res[[2]][[1]] )
  expect_equal( mp[[2]][[2]], r_res[[2]][[2]] )

  expect_true( all( lengths( mp ) == lengths( r_res ) ) )

  res <- sfheaders:::rcpp_sfg_multipolygon( m, c(2,3), NULL, 1, close = FALSE )

  m <- matrix(1L:4L, ncol = 2)
  res <- sfheaders:::rcpp_sfg_multipolygon(m, NULL, NULL, NULL, close = FALSE)
  expect_true( is_multipolygon( res ) )

  m <- matrix(c(1.2,2.2,3.2,4.2), ncol = 2)
  res <- sfheaders:::rcpp_sfg_multipolygon(m, NULL, NULL, NULL, close = FALSE )
  expect_true( is_multipolygon( res ) )

  m <- matrix(1L:4L, ncol = 2)
  res <- sfheaders:::rcpp_sfg_multipolygon(m, c(0,1), NULL, NULL, close = FALSE )
  expect_true( is_multipolygon( res ) )

  m <- matrix(c(1.2,2.2,3.2,4.2), ncol = 2)
  res <- sfheaders:::rcpp_sfg_multipolygon(m, c(0,1), NULL, NULL, close = FALSE )
  expect_true( is_multipolygon( res ) )

  m <- matrix(1L:4L, ncol = 2)
  res <- sfheaders:::rcpp_sfg_multipolygon(m, c(0L, 1L), NULL, NULL, close = FALSE )
  expect_true( is_multipolygon( res ) )

  m <- matrix(c(1.2,2.2,3.2,4.2), ncol = 2)
  res <- sfheaders:::rcpp_sfg_multipolygon(m, c(0L, 1L), NULL, NULL, close = FALSE )
  expect_true( is_multipolygon( res ) )

  df <- data.frame(
    x = 1L
    , y = 2L
  )
  res <- sfheaders:::rcpp_sfg_multipolygon(df, NULL, NULL, NULL, close = FALSE )
  expect_true( is_multipolygon( res ) )

  res <- sfheaders:::rcpp_sfg_multipolygon(df, c(0,1), NULL, NULL, close = FALSE )
  expect_true( is_multipolygon( res ) )

  res <- sfheaders:::rcpp_sfg_multipolygon(df, c("x","y"), NULL, NULL, close = FALSE )
  expect_true( is_multipolygon( res ) )

  df <- data.frame(
    x = 1L
    , y = 2L
  )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfg_multipolygon(m, NULL, NULL, NULL, close = FALSE )
  expect_true( is_multipolygon( res ) )

  res <- sfheaders:::rcpp_sfg_multipolygon(m, c(0,1), NULL, NULL, close = FALSE )
  expect_true( is_multipolygon( res ) )

  res <- sfheaders:::rcpp_sfg_multipolygon(m, c("x","y"), NULL, NULL, close = FALSE )
  expect_true( is_multipolygon( res ) )


  df <- data.frame(
    x = 1L
    , y = 2L
    , id = 3L
  )
  m <- as.matrix( df )
  expect_error( sfheaders:::rcpp_sfg_multipolygon(m, c(0L,1L), "id", NULL, close = FALSE ), "sfheaders - unknown column types" )

  df <- data.frame(
    x = 1L
    , y = 2L
    , id = 1L
  )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfg_multipolygon(m, c("x","y"), c("id"), c("id"), close = FALSE )
  expect_true( is_multipolygon( res ) )

  df <- data.frame(
    x = 1.1
    , y = 2.2
    , id = 1.2
  )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfg_multipolygon(m, c("x","y"), c("id"), c("id"), close = FALSE )
  expect_true( is_multipolygon( res ) )

  df <- data.frame(
    x = 1.1
    , y = 2.2
    , id = 1.2
  )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sfg_multipolygon(m, c("x","y"), NULL, NULL, close = FALSE )
  expect_true( is_multipolygon( res ) )

})

test_that("vectorised version works",{

  is_multipolygon <- function(x) {
    y <- is.list(unclass(x))
    z <- attr( x, "class")[2] == "MULTIPOLYGON"
    return( all(y) & all(z))
  }

  m1 <- matrix(1:3, ncol = 3)
  m2 <- matrix(1:3, ncol = 3)
  lst <- list( m1, m2 )
  res <- sfheaders:::rcpp_sfg_multipolygons( lst, close = FALSE )
  expect_true( all( sapply( res, is_multipolygon ) ) )

})

test_that("issue 39 is fixed", {

  df <- data.frame(
    polygon_id = c(rep(1, 5), rep(2, 10))
    , line_id = c(rep(1, 10), rep(2, 5))
    , x = c(0,0,1,1,0,2,2,5,5,2,3,3,4,4,3)
    , y = c(0,1,1,0,0,2,5,5,2,2,3,4,4,3,3)
    , z = c(1)
    , m = c(1)
  )

  mp <- sfg_multipolygon( df, polygon_id = "polygon_id", linestring_id = "line_id" )

  expect_equal(
    unname( as.matrix( df[ df$polygon_id == 1 & df$line_id == 1, c("x","y","z","m")] ) )
    , mp[[1]][[1]]
  )

  expect_equal(
    unname( as.matrix( df[ df$polygon_id == 2 & df$line_id == 1, c("x","y","z","m")] ) )
    , mp[[2]][[1]]
  )

  expect_equal(
    unname( as.matrix( df[ df$polygon_id == 2 & df$line_id == 2, c("x","y","z","m")] ) )
    , mp[[2]][[2]]
  )


})


## issue 57
test_that("specifying one or no geometry columns works", {

  df <- data.frame(
    polygon_id = c(rep(1, 5), rep(2, 10))
    , line_id = c(rep(1, 10), rep(2, 5))
    , x = c(0,0,1,1,0,2,2,5,5,2,3,3,4,4,3)
    , y = c(0,1,1,0,0,2,5,5,2,2,3,4,4,3,3)
    , z = c(1)
    , m = c(1)
  )

  res1 <- sfg_polygon(
    obj = df[, c("x","y")]
  )

  res2 <- sfg_polygon(
    obj = df
    , x = "x"
    , y = "y"
  )

  expect_equal( res1, res2 )

  res1 <- sfg_polygon(
    df[, c("x","y","line_id")]
    #, polygon_id = "line_id"
    , x = "x"
    , y = "y"
    , linestring_id = "line_id"
  )

  res2 <- sfg_polygon(
    df[, c("x","y","line_id")]
    #, polygon_id = "line_id"
    #, x = "x"
    #, y = "y"
    , linestring_id = "line_id"
  )

  expect_equal( res1, res2 )


  res1 <- sfg_multipolygon(
    df[, c("x","y","line_id")]
    , polygon_id = "line_id"
    , linestring_id = "line_id"
  )

  res2 <- sfg_multipolygon(
    df[, c("x","y","line_id")]
    , polygon_id = "line_id"
    #, linestring_id = "line_id"
  )

  expect_equal( res1, res2 )

})
