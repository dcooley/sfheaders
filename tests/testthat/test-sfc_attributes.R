context("sfc_attributes")

test_that("crs_input and crs_wkt are strings",{

  ## Issue 33 - superseded issue 49
  df <- data.frame(x = 1, y = 2)
  sf <- sfheaders::sf_point(df)
  a <- attributes( sf$geometry )
  expect_true( is.character( a$crs$input ) )
  expect_true( is.character( a$crs$wkt ) )
})

test_that("issue 44 is fixed",{

  df <- data.frame(
    ml_id = c(1,1,1,1,1,1,1,1,1,2,2)
    , l_id = c(1,1,1,2,2,2,3,3,3,1,1)
    , x = seq(0.5,5.5, by = 0.5 )
    , y = seq(0.5,5.5, by = 0.5 )
    , z = seq(0.5,5.5, by = 0.5 )
    , m = seq(1.5,6.5, by = 0.5 )
  )

  sf <- sf_polygon(
    obj = df
    , x = "x"
    , y = "y"
    , z = "z"
    , m = "m"
    , polygon_id = "ml_id"
    , linestring_id = "l_id"
    , close = F
  )

  expect_true( all( unname( attr( sf$geometry, "z_range" ) ) == c(0.5, 5.5 ) ) )
  expect_true( all( unname( attr( sf$geometry, "m_range" ) ) == c(1.5, 6.5 ) ) )

})
