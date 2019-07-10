context("sfg_multilinestring")

test_that("sfg multilinestring", {

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
