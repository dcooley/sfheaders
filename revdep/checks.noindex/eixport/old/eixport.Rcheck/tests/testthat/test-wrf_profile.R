context("wrf_profile")

data(rawprofile)
rawprofile  <- matrix(rawprofile, nrow = 24, byrow = TRUE)
rawprofile <- as.data.frame(rawprofile)
names(rawprofile) <- c("Sunday","Monday","Tuesday","Wednesday","Thursday",
                      "Friday","Saturday")
row.names(rawprofile) <- c("00:00","01:00","02:00","03:00","04:00","05:00",
                          "06:00","07:00","08:00","09:00","10:00","11:00",
                          "12:00","13:00","14:00","15:00","16:00","17:00",
                          "18:00","19:00","20:00","21:00","22:00","23:00")

# create the folder and emission file
f1 <- unzip(zipfile = paste0(system.file("extdata", package = "eixport"),
                             "/wrfchemi_d02_2011-08-02.zip"),
            exdir = file.path(tempdir()))
prof <- wrf_profile(rawprofile, f1[1])
test_that("multiplication works", {
  expect_equal(prof,
               0.1755673 + 4e-08)
})
