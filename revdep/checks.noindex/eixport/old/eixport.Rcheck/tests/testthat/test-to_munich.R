context("to_munich")

test_that("to_munich works", {

  data(emisco)
  dfco <- emisco[1:1000,"V8"]
  etm  <- to_munich(sdf = dfco)

  expect_equal(dim(etm[[1]]),
               c(1000,8))
})
