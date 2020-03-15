context("sf_creator-helpers")

test_that("sf_mpoly works",{

  m <- matrix(c(0, 0, 1, 1, 0,
              0, 1, 1, 0, 0), ncol = 2, dimnames = list(NULL, c("x", "y")))
  mat <- cbind(m, multipolygon_id = 1, polygon_id = 1, linestring_id = 1)
  ## why does this work
  expect_equal(sf_multipolygon(mat, x = "x", y = "y", multipolygon_id = "multipolygon_id", polygon_id = "polygon_id", linestring_id = "linestring_id")
  , res <- sf_mpoly(mat))

  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )
})
