context("sfg_polygon")

test_that("sfg polygon", {

  # expect_error( sfheaders:::rcpp_sfg_polygon( 1L:2L, NULL, NULL, "", close = FALSE ), "sfheaders - expecting a matrix" )
  # expect_error( sfheaders:::rcpp_sfg_polygon( c(1.2,2), NULL, NULL, "", close = FALSE ), "sfheaders - expecting a matrix" )
  #
  # expect_error( sfheaders:::rcpp_sfg_polygon( 1L:2L, c(0L,1L), NULL, "", close = FALSE ), "sfheaders - expecting a matrix" )
  # expect_error( sfheaders:::rcpp_sfg_polygon( c(1.2,2), c(0L,1L), NULL, "", close = FALSE ), "sfheaders - expecting a matrix" )

  expect_error( sfheaders:::rcpp_sfg_polygon( 1L:2L, c(0L,1L), 2L, "", close = FALSE ), "geometries - column index doesn't exist" )
  expect_error( sfheaders:::rcpp_sfg_polygon( c(1.2,2), c(0L,1L), 2L, "", close = FALSE ), "geometries - column index doesn't exist" )

  expect_error( sfheaders:::rcpp_sfg_polygon( 1L:2L, c("x","y"), NULL, "", close = FALSE ), "geometries - object does not have names" )
  expect_error( sfheaders:::rcpp_sfg_polygon( c(1.2,2), c("x","y"), NULL, "", close = FALSE ), "geometries - object does not have names" )

  expect_error( sfheaders:::rcpp_sfg_polygon( 1L:2L, c("x","y"), "z", "", close = FALSE ), "geometries - object does not have names" )
  expect_error( sfheaders:::rcpp_sfg_polygon( c(1.2,2), c("x","y"), "z", "", close = FALSE ), "geometries - object does not have names" )

  ## matrix
  x <- matrix(c(1:24), ncol = 2)
  res <- sfheaders:::rcpp_sfg_polygon( x, NULL, NULL, "", close = TRUE )
  expect_equal( attr(res, "class"), c("XY", "POLYGON","sfg"))
  r_res <- sfg_polygon(x)
  expect_equal( res, r_res )

  x <- matrix(c(1:24), ncol = 3)
  res <- sfheaders:::rcpp_sfg_polygon( x, NULL, NULL, "", close = TRUE )
  expect_equal( attr(res, "class"), c("XYZ", "POLYGON","sfg"))
  r_res <- sfg_polygon(x)
  expect_equal( res, r_res )

  x <- matrix(c(1:24), ncol = 4)
  res <- sfheaders:::rcpp_sfg_polygon( x, NULL, NULL, "", close = TRUE )
  expect_equal( attr(res, "class"), c("XYZM", "POLYGON","sfg"))
  r_res <- sfg_polygon(x)
  expect_equal( res, r_res )

  x <- matrix(c(1:24), ncol = 2)
  res <- sfheaders:::rcpp_sfg_polygon( x, c(0L,1L), NULL, "", close = TRUE )
  expect_equal( attr(res, "class"), c("XY", "POLYGON","sfg"))
  r_res <- sfg_polygon(x)
  expect_equal( res, r_res )

  x <- matrix(c(1.2,2), ncol = 2)
  res <- sfheaders:::rcpp_sfg_polygon( x, c(0L,1L), NULL, "", close = FALSE )
  expect_equal( attr(res, "class"), c("XY", "POLYGON","sfg"))
  r_res <- sfg_polygon(x, close = FALSE)
  expect_equal( res, r_res )

  x <- matrix(c(1,2), ncol = 2)
  expect_error(
    sfheaders:::rcpp_sfg_polygon( x, c(0L,1L), NULL, "", close = TRUE )
    , "geometries - closed shapes must have at least 4 rows"
    )

  x <- matrix(c(1:8), ncol = 2)
  res <- sfheaders:::rcpp_sfg_polygon( x, c(0L,1L), NULL, "", close = TRUE )
  expect_equal( attr(res, "class"), c("XY", "POLYGON","sfg"))

  x <- matrix(c(1:24), ncol = 3)
  res <- sfheaders:::rcpp_sfg_polygon( x, c(0L,1L,2L), NULL, "", close = TRUE )
  expect_equal( attr(res, "class"), c("XYZ", "POLYGON","sfg"))
  r_res <- sfg_polygon(x)
  expect_equal( res, r_res )

  x <- matrix(c(1:24), ncol = 4)
  res <- sfheaders:::rcpp_sfg_polygon( x, c(0L,1L,2L,3L), NULL, "", close = TRUE )
  expect_equal( attr(res, "class"), c("XYZM", "POLYGON","sfg"))
  r_res <- sfg_polygon(x)
  expect_equal( res, r_res )

  x <- matrix(c(1:4), ncol = 4)
  res <- sfheaders:::rcpp_sfg_polygon( x, c(0L,1L,2L), 3L, "", close = FALSE )
  expect_equal( attr(res, "class"), c("XYZ", "POLYGON","sfg"))
  r_res <- sfg_polygon(x, linestring_id = 4L, close = FALSE)
  expect_equal( res, r_res )

  x <- matrix(c(1.2,2,3,4), ncol = 4)
  res <- sfheaders:::rcpp_sfg_polygon( x, c(0L,1L,2L), 3L, "", close = FALSE )
  expect_equal( attr(res, "class"), c("XYZ", "POLYGON","sfg"))
  r_res <- sfg_polygon(x, linestring_id = 4L, close = FALSE)
  expect_equal( res, r_res )

  x <- matrix(c(1:2), ncol = 2)
  df <- as.data.frame( x )
  x <- as.matrix( df )
  res <- sfheaders:::rcpp_sfg_polygon( x, c("V1","V2"), NULL, "", close = FALSE )
  expect_equal( attr(res, "class"), c("XY", "POLYGON","sfg"))
  ## TODO names??
  # r_res <- sfg_polygon(x)
  # expect_equal( res, r_res )

  x <- matrix(c(1.2,2), ncol = 2)
  df <- as.data.frame( x )
  x <- as.matrix( df )
  res <- sfheaders:::rcpp_sfg_polygon( x, c("V1","V2"), NULL, "", close = FALSE )
  expect_equal( attr(res, "class"), c("XY", "POLYGON","sfg"))
  ## TODO names??
  # r_res <- sfg_polygon(x)
  # expect_equal( res, r_res )

  x <- matrix(c(1:3), ncol = 3)
  df <- as.data.frame( x )
  x <- as.matrix( df )
  res <- sfheaders:::rcpp_sfg_polygon( x, c("V1","V2"), "V3", "", close = FALSE )
  expect_equal( attr(res, "class"), c("XY", "POLYGON","sfg"))
  ## TODO names??
  # r_res <- sfg_polygon(x)
  # expect_equal( res, r_res )

  x <- matrix(c(1.2,2,3), ncol = 3)
  df <- as.data.frame( x )
  x <- as.matrix( df )
  res <- sfheaders:::rcpp_sfg_polygon( x, c("V1","V2"), "V3", "", close = FALSE )
  expect_equal( attr(res, "class"), c("XY", "POLYGON","sfg"))
  ## TODO names??
  # r_res <- sfg_polygon(x)
  # expect_equal( res, r_res )

  ## data.frame
  ids <- c( rep(1,5), rep(2,3), rep(3,6) )
  df <- data.frame(
    x = c(rep(0, length(ids))),
    y = c(rep(0, length(ids))),
    z = c(rep(0, length(ids))),
    m = c(rep(0, length(ids)))
  )

  res <- sfheaders:::rcpp_sfg_polygon( df, NULL, NULL, "", close = FALSE )
  expect_equal( attr(res, "class"), c("XYZM", "POLYGON", "sfg"))
  r_res <- sfg_polygon(df)
  expect_equal( res, r_res )

  res <- sfheaders:::rcpp_sfg_polygon( df, c("x","y"), NULL, "", close = FALSE )
  expect_equal( attr(res, "class"), c("XY", "POLYGON", "sfg"))
  r_res <- sfg_polygon(df, x = "x", y = "y")
  expect_equal( res, r_res )

})

test_that("vectorised version works",{

  is_polygon <- function(x) {
    y <- is.list(unclass(x))
    z <- attr( x, "class")[2] == "POLYGON"
    return( all(y) & all(z))
  }

  m1 <- matrix(1:3, ncol = 3)
  m2 <- matrix(1:3, ncol = 3)
  lst <- list( m1, m2 )
  res <- sfheaders:::rcpp_sfg_polygons( lst, "", close = FALSE )
  expect_true( all( sapply( res, is_polygon ) ) )

})
