context("sfg_polygon")

test_that("sfg polygon", {

  ## matrix
  x <- matrix(c(1:24), ncol = 2)
  res <- sfheaders:::rcpp_sfg_polygon( x, NULL, NULL )
  expect_equal( attr(res, "class"), c("XY", "POLYGON","sfg"))
  r_res <- sfg_polygon(x)
  expect_equal( res, r_res )

  x <- matrix(c(1:24), ncol = 3)
  res <- sfheaders:::rcpp_sfg_polygon( x, NULL, NULL )
  expect_equal( attr(res, "class"), c("XYZ", "POLYGON","sfg"))
  r_res <- sfg_polygon(x)
  expect_equal( res, r_res )

  x <- matrix(c(1:24), ncol = 4)
  res <- sfheaders:::rcpp_sfg_polygon( x, NULL, NULL )
  expect_equal( attr(res, "class"), c("XYZM", "POLYGON","sfg"))
  r_res <- sfg_polygon(x)
  expect_equal( res, r_res )

  ## data.frame
  ids <- c( rep(1,5), rep(2,3), rep(3,6) )
  df <- data.frame(
    x = c(rep(0, length(ids))),
    y = c(rep(0, length(ids))),
    z = c(rep(0, length(ids))),
    m = c(rep(0, length(ids)))
  )

  res <- sfheaders:::rcpp_sfg_polygon( df, NULL, NULL )
  expect_equal( attr(res, "class"), c("XYZM", "POLYGON", "sfg"))
  r_res <- sfg_polygon(df)
  expect_equal( res, r_res )

})
