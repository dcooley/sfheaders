context("sfg_multilinestring")

test_that("sfg multilinestring", {

  x <- 1L:2L
  res <- sfheaders:::rcpp_sfg_multilinestring( x, NULL, NULL, "" )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  r_res <- sfg_multilinestring(x)
  expect_equal( res, r_res )

  x <- c(1.3, 2.2)
  res <- sfheaders:::rcpp_sfg_multilinestring( x, NULL, NULL, "" )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  r_res <- sfg_multilinestring(x)
  expect_equal( res, r_res )

  ## matrix
  x <- matrix(c(1:24), ncol = 2)
  res <- sfheaders:::rcpp_sfg_multilinestring( x, NULL, NULL, "" )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  r_res <- sfg_multilinestring(x)
  expect_equal( res, r_res )

  x <- matrix(c(1.2,3), ncol = 2)
  res <- sfheaders:::rcpp_sfg_multilinestring( x, NULL, NULL, "" )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  r_res <- sfg_multilinestring(x)
  expect_equal( res, r_res )

  x <- matrix(c(1:24), ncol = 3)
  res <- sfheaders:::rcpp_sfg_multilinestring( x, NULL, NULL, "" )
  expect_equal( attr(res, "class"), c("XYZ", "MULTILINESTRING","sfg"))
  r_res <- sfg_multilinestring(x)
  expect_equal( res, r_res )

  x <- matrix(c(1:24), ncol = 4)
  res <- sfheaders:::rcpp_sfg_multilinestring( x, NULL, NULL, "" )
  expect_equal( attr(res, "class"), c("XYZM", "MULTILINESTRING","sfg"))
  r_res <- sfg_multilinestring(x)
  expect_equal( res, r_res )

  x <- matrix(c(1:24), ncol = 4)
  res <- sfheaders:::rcpp_sfg_multilinestring( x, c(0L,1L), NULL, "" )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  r_res <- sfg_multilinestring(obj = x, x = 1, y = 2)
  expect_equal( res, r_res )

  df <- data.frame(
    x = 1,
    y = 2
  )
  x <- as.matrix( df )
  res <- sfheaders:::rcpp_sfg_multilinestring( x, c(0L,1L), NULL, "" )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  r_res <- sfg_multilinestring(obj = x, x = 1, y = 2)
  expect_equal( res, r_res )

  df <- data.frame(
    x = 1L,
    y = 2L
  )
  x <- as.matrix( df )
  res <- sfheaders:::rcpp_sfg_multilinestring( x, c(0L,1L), NULL, "" )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  r_res <- sfg_multilinestring(obj = x, x = 1, y = 2)
  expect_equal( res, r_res )

  df <- data.frame(
    x = 1,
    y = 2
  )
  x <- as.matrix( df )
  res <- sfheaders:::rcpp_sfg_multilinestring( x, c("x","y"), NULL, "" )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  r_res <- sfg_multilinestring(x, x = "x", y = "y")
  expect_equal( res, r_res )

  df <- data.frame(
    x = 1L,
    y = 2L
  )
  x <- as.matrix( df )
  res <- sfheaders:::rcpp_sfg_multilinestring( x, c("x","y"), NULL, "" )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  r_res <- sfg_multilinestring(x, x = "x", y = "y")
  expect_equal( res, r_res )


  df <- data.frame(
    x = 1L,
    y = 2L,
    id = 1L
  )
  x <- as.matrix( df )
  res <- sfheaders:::rcpp_sfg_multilinestring( x, NULL, "id", "" )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  r_res <- sfg_multilinestring(x, x = "x", y = "y")
  expect_equal( res, r_res )

  df <- data.frame(
    x = 1L,
    y = 2L,
    id = 1L
  )
  res <- sfheaders:::rcpp_sfg_multilinestring( df, c(0L,1L),2L, "" )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  r_res <- sfg_multilinestring(x, x = "x", y = "y")
  expect_equal( res, r_res )

  df <- data.frame(
    x = 1L,
    y = 2L
  )
  res <- sfheaders:::rcpp_sfg_multilinestring( df, c(0L,1L) , NULL, "" )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  ## TODO names??
  # r_res <- sfg_multilinestring(df, x = "x", y = "y")
  # expect_equal( res, r_res )

  df <- data.frame(
    x = 1L,
    y = 2L
  )
  res <- sfheaders:::rcpp_sfg_multilinestring( df, c("x","y") , NULL, "" )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  r_res <- sfg_multilinestring(df, x = "x", y = "y")
  expect_equal( res, r_res )


  df <- data.frame(
    id = 1,
    x = 1,
    y = 2
  )
  x <- as.matrix( df )
  res <- sfheaders:::rcpp_sfg_multilinestring( x, c("x","y"), "id", "" )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  r_res <- sfg_multilinestring(x, x = "x", y = "y", linestring_id = "id")
  expect_equal( res, r_res )

  df <- data.frame(
    id = 1,
    x = 1L,
    y = 2L
  )
  x <- as.matrix( df )
  res <- sfheaders:::rcpp_sfg_multilinestring( x, c("x","y"), "id", "" )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  r_res <- sfg_multilinestring(x, x = "x", y = "y", linestring_id = "id")
  expect_equal( res, r_res )

  df <- data.frame(
    id = 1,
    x = 1,
    y = 2
  )
  x <- as.matrix( df )
  res <- sfheaders:::rcpp_sfg_multilinestring( x, c(1L,2L), 0L, "" )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  #r_res <- sfg_multilinestring(x, x = "x", y = "y", linestring_id = "id")
  #expect_equal( res, r_res )

  df <- data.frame(
    id = 1,
    x = 1L,
    y = 2L
  )
  x <- as.matrix( df )
  res <- sfheaders:::rcpp_sfg_multilinestring( x, c(1L,2L), 0L, "" )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  # r_res <- sfg_multilinestring(x, x = "x", y = "y", linestring_id = "id")
  # expect_equal( res, r_res )

  df <- data.frame(
    id = 1,
    x = 1L,
    y = 2L
  )
  x <- as.matrix( df )
  res <- sfheaders:::rcpp_sfg_multilinestring( x, c("x","y"), "id", "" )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  r_res <- sfg_multilinestring(x, x = "x", y = "y", linestring_id = "id")
  expect_equal( res, r_res )

  df <- data.frame(
    id = 1,
    x = 1L,
    y = 2L
  )
  x <- as.matrix( df )
  res <- sfheaders:::rcpp_sfg_multilinestring( x, c(1L, 2L), 0L, "" )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  r_res <- sfg_multilinestring(x, x = 2, y = 3, linestring_id = 1 )
  expect_equal( res, r_res )

  x <- data.frame(
    id = 1,
    x = 1L,
    y = 2L
  )
  res <- sfheaders:::rcpp_sfg_multilinestring( x, c("x","y"), "id", "")
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  r_res <- sfg_multilinestring(x, x = "x", y = "y", linestring_id = "id")
  expect_equal( res, r_res )


  ## data.frame
  ids <- c( rep(1,5), rep(2,3), rep(3,6) )
  df <- data.frame(
    x = c(rep(0, length(ids))),
    y = c(rep(0, length(ids))),
    z = c(rep(0, length(ids))),
    m = c(rep(0, length(ids)))
  )

  res <- sfheaders:::rcpp_sfg_multilinestring( df, NULL, NULL, "" )
  expect_equal( attr(res, "class"), c("XYZM", "MULTILINESTRING", "sfg"))
  r_res <- sfg_multilinestring(df)
  expect_equal( res, r_res )

})

test_that("vectorised version works",{

  is_multilinestring <- function(x) {
    y <- is.list(unclass(x))
    z <- attr( x, "class")[2] == "MULTILINESTRING"
    return( all(y) & all(z))
  }

  m1 <- matrix(1:3, ncol = 3)
  m2 <- matrix(1:3, ncol = 3)
  lst <- list( m1, m2 )
  res <- sfheaders:::rcpp_sfg_multilinestrings( lst, "" )
  expect_true( all( sapply( res, is_multilinestring ) ) )

})
