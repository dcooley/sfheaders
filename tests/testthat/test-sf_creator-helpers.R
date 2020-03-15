context("sf_creator-helpers")

test_that("sf_mpoly works",{
  m <- matrix(c(0, 0, 1, 1, 0,
              0, 1, 1, 0, 0), ncol = 2, dimnames = list(NULL, c("x", "y")))
  mat <- cbind(m, multipolygon_id = 1, polygon_id = 1, linestring_id = 1)
  res <- sf_mpoly(mat)
  ans <- sf_multipolygon(mat, x = "x", y = "y", multipolygon_id = "multipolygon_id", polygon_id = "polygon_id", linestring_id = "linestring_id")
  expect_equal(res,
               ans)
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )


  ## z works
  expect_true(dim(sf_mpoly(cbind(mat, z = 1))[["geometry"]][[1L]][[1L]][[1L]])[2L] == 3L)
  ## m works
  expect_true(dim(sf_mpoly(cbind(mat, m = 0))[["geometry"]][[1L]][[1L]][[1L]])[2L] == 3L)
  ## zm works
  expect_true(dim(sf_mpoly(cbind(mat, z = 2, m = 0))[["geometry"]][[1L]][[1L]][[1L]])[2L] == 4L)
  ## keep works
  expect_equal(dim(sf_mpoly(cbind(mat, m = 0, cactus = 1:5))), c(1L, 2L))
  kept <- sf_mpoly(cbind(mat, m = 0, cactus = 1:5), keep = TRUE)
  expect_equal(dim(kept), c(1L, 3L))

  kept2 <- sf_mpoly(cbind(mat, m = 0, cactus = 1:5, keepmetoo = 2), keep = TRUE)
  expect_equal(dim(kept2), c(1L, 4L))

})
