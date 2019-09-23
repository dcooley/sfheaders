context("close_polygon")

test_that("sfg_polygons closed",{

  x <- data.frame(
    x = 1:2
    , y = 1:2
  )
  expect_error(
    sfheaders::sfg_polygon( x )
    , "sfheaders - closed polygons must have at least 4 rows. Use close = FALSE to bypass this check"
  )

  x <- data.frame(
    x = 1:3
    , y = 1:3
  )
  res <- sfheaders::sfg_polygon( x )
  expect_equal( res[[1]][1, ], res[[1]][4, ] )

  x <- as.matrix( x )
  res <- sfheaders::sfg_polygon( x )
  expect_equal( res[[1]][1, ], res[[1]][4, ] )

})

test_that("sfc_polygons closed",{

  x <- data.frame(
    x = 1:2
    , y = 1:2
  )
  expect_error(
    sfheaders::sfc_polygon( x )
    , "sfheaders - closed polygons must have at least 4 rows. Use close = FALSE to bypass this check"
  )

  x <- data.frame(
    x = 1:3
    , y = 1:3
  )
  res <- sfheaders::sfc_polygon( x )
  expect_equal( res[[1]][[1]][1, ], res[[1]][[1]][4, ] )

  x <- as.matrix( x )
  res <- sfheaders::sfc_polygon( x )
  expect_equal( res[[1]][[1]][1, ], res[[1]][[1]][4, ] )

})

test_that("sf_polygons closed",{
  x <- data.frame(
    x = 1:2
    , y = 1:2
  )

  expect_error(
    sfheaders::sf_polygon( x )
    , "sfheaders - closed polygons must have at least 4 rows. Use close = FALSE to bypass this check"
  )

  x <- data.frame(
    x = 1:3
    , y = 1:3
  )
  res <- sfheaders::sf_polygon( x )
  expect_equal( res$geometry[[1]][[1]][1, ], res$geometry[[1]][[1]][4, ] )

  x <- as.matrix( x )
  res <- sfheaders::sf_polygon( x )
  expect_equal( res$geometry[[1]][[1]][1, ], res$geometry[[1]][[1]][4, ] )

  df <- data.frame(
    x = c(1,1,2,1,1,2)
    , y = c(1,1,2,1,1,2)
    , id = c(1,1,1,2,2,2)
  )

  res <- sfheaders::sf_polygon(
    obj = df
    , x = "x"
    , y = "y"
    , polygon_id = "id"
  )
  expect_equal( res[1, ]$geometry[[1]][[1]][1, ], res[1, ]$geometry[[1]][[1]][4, ] )
  expect_equal( res[2, ]$geometry[[1]][[1]][1, ], res[2, ]$geometry[[1]][[1]][4, ] )

})


### --- MULTIPOLYGON

test_that("sfg_multipolygons closed",{

  x <- data.frame(
    x = 1:2
    , y = 1:2
  )
  expect_error(
    sfheaders::sfg_multipolygon( x )
    , "sfheaders - closed polygons must have at least 4 rows. Use close = FALSE to bypass this check"
  )

  x <- data.frame(
    x = 1:3
    , y = 1:3
  )
  res <- sfheaders::sfg_multipolygon( x )
  expect_equal( res[[1]][[1]][1, ], res[[1]][[1]][4, ] )

  x <- as.matrix( x )
  res <- sfheaders::sfg_multipolygon( x )
  expect_equal( res[[1]][[1]][1, ], res[[1]][[1]][4, ] )

})

test_that("sfc_multipolygons closed",{

  x <- data.frame(
    x = 1:2
    , y = 1:2
  )
  expect_error(
    sfheaders::sfc_multipolygon( x )
    , "sfheaders - closed polygons must have at least 4 rows. Use close = FALSE to bypass this check"
  )

  x <- data.frame(
    x = 1:3
    , y = 1:3
  )
  res <- sfheaders::sfc_multipolygon( x )
  expect_equal( res[[1]][[1]][[1]][1, ], res[[1]][[1]][[1]][4, ] )

  x <- as.matrix( x )
  res <- sfheaders::sfc_multipolygon( x )
  expect_equal( res[[1]][[1]][[1]][1, ], res[[1]][[1]][[1]][4, ] )

})

test_that("sf_multipolygons closed",{
  x <- data.frame(
    x = 1:2
    , y = 1:2
  )

  expect_error(
    sfheaders::sf_multipolygon( x )
    , "sfheaders - closed polygons must have at least 4 rows. Use close = FALSE to bypass this check"
  )

  x <- data.frame(
    x = 1:3
    , y = 1:3
  )
  res <- sfheaders::sf_multipolygon( x )
  expect_equal( res$geometry[[1]][[1]][[1]][1, ], res$geometry[[1]][[1]][[1]][4, ] )

  x <- as.matrix( x )
  res <- sfheaders::sf_multipolygon( x )
  expect_equal( res$geometry[[1]][[1]][[1]][1, ], res$geometry[[1]][[1]][[1]][4, ] )

  df <- data.frame(
    x = c(1,1,2,1,1,2)
    , y = c(1,1,2,1,1,2)
    , id = c(1,1,1,2,2,2)
  )

  res <- sfheaders::sf_multipolygon(
    obj = df
    , x = "x"
    , y = "y"
    , multipolygon_id = "id"
  )

  expect_equal( res[1, ]$geometry[[1]][[1]][[1]][1, ], res[1, ]$geometry[[1]][[1]][[1]][4, ] )
  expect_equal( res[2, ]$geometry[[1]][[1]][[1]][1, ], res[2, ]$geometry[[1]][[1]][[1]][4, ] )

})

