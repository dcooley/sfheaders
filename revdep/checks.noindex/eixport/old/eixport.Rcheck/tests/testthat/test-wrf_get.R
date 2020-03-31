context("wrf_get")

wrf_create(wrfinput_dir         = system.file("extdata", package = "eixport"),
           wrfchemi_dir         = file.path(tempdir()),
           domains              = 2,
           frames_per_auxinput5 = 1,
           auxinput5_interval_m = 60,
           day_offset           = 1,
           verbose              = FALSE)

f1 <- list.files(path = file.path(tempdir()),pattern = "wrfchemi",
                 full.names = TRUE)


f2 <- unzip(zipfile = paste0(system.file("extdata", package = "eixport"),
                             "/wrfchemi_d02_2011-08-02.zip"),
            exdir = file.path(tempdir()))

co <- wrf_get(file = f1, name = "E_CO")

test_that("wrf_get works", {
  expect_equal(wrf_get(file = f1, name = "E_CO"),
               wrf_get(file = f2, name = "E_CO"))
})
test_that("wrf_get works", {
  expect_equal(wrf_get(file = f1, name = "E_CO", as_raster = TRUE),
               wrf_get(file = f2, name = "E_CO", as_raster = TRUE))
})
test_that("wrf_get works", {
  expect_equal(wrf_get(file = f1, name = "E_CO", as_raster = TRUE,
                       raster_crs = "+init=epsg:4326"),
               wrf_get(file = f2, name = "E_CO", as_raster = TRUE,
                       raster_crs = "+init=epsg:4326"))
})
test_that("wrf_get works", {
  expect_equal(wrf_get(file = f1, name = "E_NO2", as_raster = TRUE),
               wrf_get(file = f2, name = "E_NO2", as_raster = TRUE))
})
test_that("wrf_get works", {
  expect_equal(wrf_get(file = f1, name = "E_XYL"),
               wrf_get(file = f2, name = "E_XYL"))
})
test_that("wrf_get works", {
  expect_equal(wrf_get(file = f1, name = "E_ETH", as_raster = TRUE),
               wrf_get(file = f2, name = "E_ETH", as_raster = TRUE))
})

