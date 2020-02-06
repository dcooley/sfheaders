context("sfc_columns_attributes")


## issue 50
test_that("sfc_columns attribute added and column names uniquified",{

  df <- data.frame(
    x = 1:5
    , y = 1:5
  )

  sf <- sfheaders::sf_point(df)
  sf$x <- letters[1:5]

  df <- sfheaders::sf_to_df(sf, fill = TRUE )
  expect_equal(
    names(df)
    , c("x", "sfg_id","point_id","x..1","y")
  )

  expect_equal(
    attr(df, "sfc_columns")
    , c("x..1","y")
  )

  df <- data.frame(
    x = 1:5
    , y = 1:5
    , z = 1:5
  )

  sf <- sfheaders::sf_linestring(df)
  sf$y <- "a"

  df <- sfheaders::sf_to_df(sf, fill = TRUE )

  expect_equal(
    names(df)
    , c("id", "y", "sfg_id","linestring_id","x","y..1","z")
  )

  expect_equal(
    attr(df, "sfc_columns")
    , c("x","y..1","z")
  )

})
