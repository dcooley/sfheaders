context("sfheaders")

test_that("index_correct works",{

  x <- 1:4
  res <- sfheaders:::index_correct( x )
  expect_equal( x - 1, res )

})
