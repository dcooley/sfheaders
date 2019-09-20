context("sfc_attributes")

test_that("crs is int, proj4string is string",{

  ## Issue 33
  df <- data.frame(x = 1, y = 2)
  sf <- sfheaders::sf_point(df)
  a <- attributes( sf$geometry )
  expect_true( is.integer( a$crs$epsg ) )
  expect_true( is.character( a$crs$proj4string ) )
})
