context("holes")

test_that("holes are removed from polygons",{

  df <- data.frame(
    ml_id = c(1,1,1,1,1,1,1,1,1,2,2,2,2,2,2)
    , l_id = c(1,1,1,2,2,2,3,3,3,1,1,1,2,2,2)
    , x = rnorm(15)
    , y = rnorm(15)
    , z = rnorm(15)
    , m = rnorm(15)
  )

  expect_error(
    sf_remove_holes(df)
    , "only sfg, sfc and sf objects are supported"
  )

  sfg <- sfg_polygon( obj = df, x = "x", y = "y", linestring_id = "ml_id", close = FALSE)
  sfc <- sfc_polygon( obj = df, x = "x", y = "y", polygon_id = "ml_id", linestring_id = "l_id", close = FALSE)
  sf <- sf_polygon( obj = df, x = "x", y = "y", polygon_id = "ml_id", linestring_id = "l_id", close = FALSE )

  sfg_res <- sf_remove_holes( sfg, close = FALSE )
  sfc_res <- sf_remove_holes( sfc, close = FALSE )
  sf_res <- sf_remove_holes( sf, close = FALSE )

  expect_true( length( sfg ) == 2 & length( sfg_res ) == 1 )
  expect_equal( sfg_res[[1]][, 1], df[ df$ml_id == 1, "x"] )
  expect_equal( sfg_res[[1]][, 2], df[ df$ml_id == 1, "y"] )

  expect_true( length( sfc[[1]] ) == 3 & length( sfc_res[[1]] ) == 1 )
  expect_equal( sfc_res[[1]][[1]][, 1], df[ df$ml_id == 1 & df$l_id == 1, "x"] )
  expect_equal( sfc_res[[1]][[1]][, 2], df[ df$ml_id == 1 & df$l_id == 1, "y"] )

  expect_true( length( sfc[[2]] ) == 2 & length( sfc_res[[2]] ) == 1 )
  expect_equal( sfc_res[[2]][[1]][, 1], df[ df$ml_id == 2 & df$l_id == 1, "x"] )
  expect_equal( sfc_res[[2]][[1]][, 2], df[ df$ml_id == 2 & df$l_id == 1, "y"] )

  expect_true( length( sf$geometry[[1]] ) == 3 & length( sf_res$geometry[[1]] ) == 1 )
  expect_equal( sf_res$geometry[[1]][[1]][, 1], df[ df$ml_id == 1 & df$l_id == 1, "x"] )
  expect_equal( sf_res$geometry[[1]][[1]][, 2], df[ df$ml_id == 1 & df$l_id == 1, "y"] )

  expect_true( length( sf$geometry[[2]] ) == 2 & length( sf_res$geometry[[2]] ) == 1 )
  expect_equal( sf_res$geometry[[2]][[1]][, 1], df[ df$ml_id == 2 & df$l_id == 1, "x"] )
  expect_equal( sf_res$geometry[[2]][[1]][, 2], df[ df$ml_id == 2 & df$l_id == 1, "y"] )

  sfg <- sfg_multipolygon( obj = df, x = "x", y = "y", polygon_id = "ml_id", linestring_id = "l_id", close = FALSE)
  sfc <- sfc_multipolygon( obj = df, x = "x", y = "y", polygon_id = "ml_id", linestring_id = "l_id", close = FALSE)
  sf <- sf_multipolygon( obj = df, x = "x", y = "y", polygon_id = "ml_id", linestring_id = "l_id", close = FALSE )

  sfg_res <- sf_remove_holes( sfg, close = FALSE )
  sfc_res <- sf_remove_holes( sfc, close = FALSE )
  sf_res <- sf_remove_holes( sf, close = FALSE )

  expect_true( length( sfg[[1]] ) == 3 & length( sfg_res[[1]] ) == 1 )
  expect_equal( sfg_res[[1]][[1]][, 1], df[ df$ml_id == 1 & df$l_id == 1, "x"] )
  expect_equal( sfg_res[[1]][[1]][, 2], df[ df$ml_id == 1 & df$l_id == 1, "y"] )

  expect_true( length( sfc[[1]][[1]] ) == 3 & length( sfc_res[[1]][[1]] ) == 1 )
  expect_equal( sfc_res[[1]][[1]][[1]][, 1], df[ df$ml_id == 1 & df$l_id == 1, "x"] )
  expect_equal( sfc_res[[1]][[1]][[1]][, 2], df[ df$ml_id == 1 & df$l_id == 1, "y"] )

  expect_true( length( sfc[[1]][[2]] ) == 2 & length( sfc_res[[1]][[1]] ) == 1 )
  expect_equal( sfc_res[[1]][[2]][[1]][, 1], df[ df$ml_id == 2 & df$l_id == 1, "x"] )
  expect_equal( sfc_res[[1]][[2]][[1]][, 2], df[ df$ml_id == 2 & df$l_id == 1, "y"] )

  expect_equal( sf_res$geometry, sfc_res )

})
