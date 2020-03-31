context("wrf_grid")
wrf1 <- paste(system.file("extdata", package = "eixport"),
                          "/wrfinput_d02", sep="")
gwrf1  <- wrf_grid(wrf1)
gwrf2 <- readRDS(paste0(system.file("extdata", package = "eixport"),
                      "/gwrf1.rds"))

# test_that("wrf_grid works", {
#   expect_equal(gwrf1[1], gwrf2[1])
# })


test_that("wrf_grid works", {
  expect_equal( wrf_grid(wrf1, matrix = TRUE)[1], 0)
})

