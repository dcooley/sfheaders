context("sfg_multilinestring")

test_that("sfg multilinestring", {

  x <- 1L:2L
  res <- sfheaders:::rcpp_sfg_multilinestring( x, NULL, NULL )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  r_res <- sfg_multilinestring(x)
  expect_equal( res, r_res )

  x <- c(1.3, 2.2)
  res <- sfheaders:::rcpp_sfg_multilinestring( x, NULL, NULL )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  r_res <- sfg_multilinestring(x)
  expect_equal( res, r_res )

  ## matrix
  x <- matrix(c(1:24), ncol = 2)
  res <- sfheaders:::rcpp_sfg_multilinestring( x, NULL, NULL )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  r_res <- sfg_multilinestring(x)
  expect_equal( res, r_res )

  x <- matrix(c(1:24), ncol = 3)
  res <- sfheaders:::rcpp_sfg_multilinestring( x, NULL, NULL )
  expect_equal( attr(res, "class"), c("XYZ", "MULTILINESTRING","sfg"))
  r_res <- sfg_multilinestring(x)
  expect_equal( res, r_res )

  x <- matrix(c(1:24), ncol = 4)
  res <- sfheaders:::rcpp_sfg_multilinestring( x, NULL, NULL )
  expect_equal( attr(res, "class"), c("XYZM", "MULTILINESTRING","sfg"))
  r_res <- sfg_multilinestring(x)
  expect_equal( res, r_res )

  x <- matrix(c(1:24), ncol = 4)
  res <- sfheaders:::rcpp_sfg_multilinestring( x, c(0,1), NULL )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  r_res <- sfg_multilinestring(x, x = 1, y = 2)
  expect_equal( res, r_res )

  df <- data.frame(
    x = 1,
    y = 2
  )
  x <- as.matrix( df )
  res <- sfheaders:::rcpp_sfg_multilinestring( x, c(0,1), NULL )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  r_res <- sfg_multilinestring(x, x = 1, y = 2)
  expect_equal( res, r_res )

  df <- data.frame(
    x = 1L,
    y = 2L
  )
  x <- as.matrix( df )
  res <- sfheaders:::rcpp_sfg_multilinestring( x, c(0,1), NULL )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  r_res <- sfg_multilinestring(x, x = 1, y = 2)
  expect_equal( res, r_res )

  df <- data.frame(
    x = 1,
    y = 2
  )
  x <- as.matrix( df )
  res <- sfheaders:::rcpp_sfg_multilinestring( x, c("x","y"), NULL )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  r_res <- sfg_multilinestring(x, x = "x", y = "y")
  expect_equal( res, r_res )

  df <- data.frame(
    x = 1L,
    y = 2L
  )
  x <- as.matrix( df )
  res <- sfheaders:::rcpp_sfg_multilinestring( x, c("x","y"), NULL )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  r_res <- sfg_multilinestring(x, x = "x", y = "y")
  expect_equal( res, r_res )


  df <- data.frame(
    id = 1,
    x = 1,
    y = 2
  )
  x <- as.matrix( df )
  res <- sfheaders:::rcpp_sfg_multilinestring( x, c("x","y"), "id" )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  r_res <- sfg_multilinestring(x, x = "x", y = "y", linestring_id = "id")
  expect_equal( res, r_res )

  df <- data.frame(
    id = 1,
    x = 1L,
    y = 2L
  )
  x <- as.matrix( df )
  res <- sfheaders:::rcpp_sfg_multilinestring( x, c("x","y"), "id" )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  r_res <- sfg_multilinestring(x, x = "x", y = "y", linestring_id = "id")
  expect_equal( res, r_res )

  df <- data.frame(
    id = 1,
    x = 1,
    y = 2
  )
  x <- as.matrix( df )
  res <- sfheaders:::rcpp_sfg_multilinestring( x, c(1,2), 0 )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  #r_res <- sfg_multilinestring(x, x = "x", y = "y", linestring_id = "id")
  #expect_equal( res, r_res )

  df <- data.frame(
    id = 1,
    x = 1L,
    y = 2L
  )
  x <- as.matrix( df )
  res <- sfheaders:::rcpp_sfg_multilinestring( x, c(1,2), 0 )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))
  # r_res <- sfg_multilinestring(x, x = "x", y = "y", linestring_id = "id")
  # expect_equal( res, r_res )


  ## data.frame
  ids <- c( rep(1,5), rep(2,3), rep(3,6) )
  df <- data.frame(
    x = c(rep(0, length(ids))),
    y = c(rep(0, length(ids))),
    z = c(rep(0, length(ids))),
    m = c(rep(0, length(ids)))
  )

  res <- sfheaders:::rcpp_sfg_multilinestring( df, NULL, NULL )
  expect_equal( attr(res, "class"), c("XYZM", "MULTILINESTRING", "sfg"))
  r_res <- sfg_multilinestring(df)
  expect_equal( res, r_res )

})