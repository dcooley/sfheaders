context("to_as4wrf")
data(gCO)
df <- to_as4wrf(sdf = gCO, dmyhm = "29-04-2018 00:00",
                tz = "America/Sao_Paulo", islist = FALSE)[1,]
row.names(df) <- NULL

df2 <- to_as4wrf(sdf = list(co = gCO, pm = gCO), dmyhm = "29-04-2018 00:00",
                tz = "America/Sao_Paulo", islist = TRUE)[1,]
row.names(df) <- NULL

test_that("to_as4wrf works", {
  expect_equal(df,
               data.frame(
                 id = 1,
                 long =  -46.8066,
                 lat = -23.62,
                 pollutant = 8391.2824346044,
                 time_lt = as.POSIXct(x = "2018-04-29", tz = "America/Sao_Paulo"),
                 time_utc = as.POSIXct(x = "2018-04-29 03:00:00", tz = "Etc/UTC"),
                 dutch = as.numeric(
                   paste0(
                     strftime(as.POSIXct(x = "2018-04-29 03:00:00", tz = "Etc/UTC"),
                              timezone = tz, format = "%d"),
                     strftime(as.POSIXct(x = "2018-04-29 03:00:00", tz = "Etc/UTC"),
                              timezone = tz, format = "%H")
                   ))
               ))
})

test_that("to_as4wrf works", {
  expect_equal(df2,
               data.frame(
                 id = 1,
                 long =  -46.8066,
                 lat = -23.62,
                 co = 8391.2824346044,
                 pm = 8391.2824346044,
                 time_lt = as.POSIXct(x = "2018-04-29", tz = "America/Sao_Paulo"),
                 time_utc = as.POSIXct(x = "2018-04-29 03:00:00", tz = "Etc/UTC"),
                 dutch = as.numeric(
                   paste0(
                     strftime(as.POSIXct(x = "2018-04-29 03:00:00", tz = "Etc/UTC"),
                              timezone = tz, format = "%d"),
                     strftime(as.POSIXct(x = "2018-04-29 03:00:00", tz = "Etc/UTC"),
                              timezone = tz, format = "%H")
                   ))
               ))
})
