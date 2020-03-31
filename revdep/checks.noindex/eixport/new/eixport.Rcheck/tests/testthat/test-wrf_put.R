context("wrf_put")

wrf_create(wrfinput_dir          = system.file("extdata", package = "eixport"),
           wrfchemi_dir         = file.path(tempdir()),
           domains              = 2,
           frames_per_auxinput5 = 1,
           auxinput5_interval_m = 60,
           day_offset           = 1,
           verbose              = FALSE)

f1 <- list.files(path = file.path(tempdir()),pattern = "wrfchemi",
                 full.names = TRUE)

CO <- wrf_get(file = f1, name = "E_CO")
CO[] = 1:length(CO)
wrf_put(file = f1, name = "E_CO", POL = CO)

wrf_add(file = f1, name = "E_CO", POL = CO)

f2 <- unzip(zipfile = paste0(system.file("extdata", package = "eixport"),
                             "/wrfchemi_d02_2011-08-02.zip"),
            exdir = file.path(tempdir()))
CO <- wrf_get(file = f2, name = "E_CO")
CO[] = 1:length(CO)
wrf_put(file = f2, name = "E_CO", POL = CO)
wrf_add(file = f2, name = "E_CO", POL = CO)

nc1 <- ncdf4::nc_open(f1)
nc2 <- ncdf4::nc_open(f2)

test_that("wrf_put works", {
  expect_equal(ncdf4::ncvar_get(nc1, "E_CO"),
               ncdf4::ncvar_get(nc2, "E_CO")
  )
})
