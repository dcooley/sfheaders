context("wrf_create")

dir.create(file.path(tempdir(), "EMISS"))
wrf_create(wrfinput_dir          = system.file("extdata", package = "eixport"),
            wrfchemi_dir         = file.path(tempdir(), "EMISS"),
            domains              = 2,
            frames_per_auxinput5 = 1,
            verbose              = TRUE)

f1 <- dir(path = file.path(tempdir(), "EMISS"), pattern = "wrfchemi_d02", full.names = T)

f2 <- unzip(zipfile = paste0(system.file("extdata", package = "eixport"),
                             "/wrfchemi_d02_2011-08-02.zip"),
            exdir = file.path(tempdir()))

nc1 <- ncdf4::nc_open(f1)
nc2 <- ncdf4::nc_open(f2)

test_that("wrf_create works", {
  expect_equal(nc1$nvars,
               nc2$nvars
  )
})
