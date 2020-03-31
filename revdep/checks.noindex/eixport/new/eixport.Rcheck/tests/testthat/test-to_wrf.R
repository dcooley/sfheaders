context("to_wrf")

wrf_create(wrfinput_dir          = system.file("extdata", package = "eixport"),
           wrfchemi_dir         = file.path(tempdir()),
           domains              = 2,
           frames_per_auxinput5 = 1,
           auxinput5_interval_m = 60,
           day_offset           = 1,
           verbose              = FALSE)

f1 <- list.files(path = file.path(tempdir()),pattern = "wrfchemi",
                    full.names = TRUE)

perfil <- c(0.010760058, 0.005280596, 0.002883553, 0.002666932,
            0.005781312, 0.018412838, 0.051900411, 0.077834636,
            0.067919758, 0.060831614, 0.055852868, 0.052468599,
            0.050938043, 0.051921718, 0.052756244, 0.052820165,
            0.058388406, 0.072855890, 0.075267137, 0.063246412,
            0.042713523, 0.029108975, 0.022091855, 0.015298458)
data(Lights)
to_wrf(Lights[1:63, 1:51], f1[1], total = 1521983, profile = perfil[1], name = "E_CO")

f2 <- unzip(zipfile = paste0(system.file("extdata", package = "eixport"),
                             "/wrfchemi_d02_2011-08-02.zip"),
            exdir = file.path(tempdir()))

to_wrf(Lights[1:63, 1:51], f2, total = 1521983, profile = perfil[1], name = "E_CO")

nc1 <- ncdf4::nc_open(f1)
nc2 <- ncdf4::nc_open(f2)

test_that("to_wrf works", {
expect_equal(ncdf4::ncvar_get(nc1, "E_CO")[1,1],
             ncdf4::ncvar_get(nc2, "E_CO")[1,1]
  )
})

