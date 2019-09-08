context("empty")

test_that("n_empty set for POINT", {

  x <- c(NA_real_, NA_real_)
  res <- sfheaders::sfc_point( x )
  expect_equal( attr(res, "n_empty"), 1 )

  x <- c(NA_real_, 1)
  res <- sfheaders::sfc_point( x )
  expect_equal( attr(res, "n_empty"), 1 )

  x <- c(NA_integer_, NA_integer_)
  res <- sfheaders::sfc_point( x )
  expect_equal( attr(res, "n_empty"), 1 )

})
