context("empty")

test_that("n_empty set for POINT", {

  x <- c(NA_integer_, NA_integer_)
  res <- sfheaders::sfc_point( x )
  expect_equal( attr(res, "n_empty"), 1 )

  x <- c(NA_integer_, 1)
  res <- sfheaders::sfc_point( x )
  expect_equal( attr(res, "n_empty"), 1 )

  x <- c(1, NA_integer_)
  res <- sfheaders::sfc_point( x )
  expect_equal( attr(res, "n_empty"), 1 )

  x <- c(NA_real_, NA_real_)
  res <- sfheaders::sfc_point( x )
  expect_equal( attr(res, "n_empty"), 1 )

  x <- c(NA_real_, 1)
  res <- sfheaders::sfc_point( x )
  expect_equal( attr(res, "n_empty"), 1 )

  x <- c(1,NA_real_)
  res <- sfheaders::sfc_point( x )
  expect_equal( attr(res, "n_empty"), 1 )

  x <- matrix(c(NA_integer_, NA_integer_, 1, 1), ncol = 2)
  res <- sfheaders::sfc_point( x )
  expect_equal( attr(res, "n_empty"), 2 )

  x <- as.data.frame( x )
  res <- sfheaders::sfc_point( x )
  expect_equal( attr(res, "n_empty"), 2 )

  x <- matrix(c(NA_integer_, NA_integer_, 1, 1, 1, 1), ncol = 3)
  res <- sfheaders::sfc_point( x, x = 1L, y = 2L )
  expect_equal( attr(res, "n_empty"), 2 )

  x <- matrix(c(NA_real_, NA_real_, 1.1, 1, 1, 1), ncol = 3)
  res <- sfheaders::sfc_point( x, x = 1, y = 2 )
  expect_equal( attr(res, "n_empty"), 2 )


})
