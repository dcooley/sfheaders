context("sfg_to_multilinestring")

test_that("sfg multilinestring", {

  ids <- c(1,1,1,2,2,2,2,3,3)
  df <- data.frame(
    id = ids,
    x = c(rep(0, length(ids))),
    y = c(rep(0, length(ids))),
    z = c(rep(0, length(ids))),
    m = c(rep(0, length(ids)))
  )

  res <- sfheaders:::rcpp_to_multilinestring(df, c("id","x","y"))
  expect_equal( attr(res, "class"), c("XY", "MULTILINESTRING", "sfg"))

  res <- sfheaders:::rcpp_to_multilinestring(df, c("id","x","y","z"))
  expect_equal( attr(res, "class"), c("XYZ", "MULTILINESTRING", "sfg"))

  res <- sfheaders:::rcpp_to_multilinestring(df, c("id","x","y","z","m"))
  expect_equal( attr(res, "class"), c("XYZM", "MULTILINESTRING", "sfg"))

})
