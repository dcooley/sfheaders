context("sfg_to_multilinestring")

test_that("sfg multilinestring", {

  ## matrix
  x <- matrix(c(1:24), ncol = 2)
  res <- sfheaders:::rcpp_to_multilinestring( x )
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING","sfg"))

  x <- matrix(c(1:24), ncol = 3)
  res <- sfheaders:::rcpp_to_multilinestring( x )
  expect_equal( attr(res, "class"), c("XYZ", "MULTILINESTRING","sfg"))

  x <- matrix(c(1:24), ncol = 4)
  res <- sfheaders:::rcpp_to_multilinestring( x )
  expect_equal( attr(res, "class"), c("XYZM", "MULTILINESTRING","sfg"))

  ## data.frame
  ids <- c( rep(1,5), rep(2,3), rep(3,6) )
  df <- data.frame(
    x = c(rep(0, length(ids))),
    y = c(rep(0, length(ids))),
    z = c(rep(0, length(ids))),
    m = c(rep(0, length(ids)))
  )

  res <- sfheaders:::rcpp_to_multilinestring( df )
  expect_equal( attr(res, "class"), c("XYMZ", "MULTILINESTRING", "sfg"))

})
