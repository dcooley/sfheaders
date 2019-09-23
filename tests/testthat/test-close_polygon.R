context("close_polygon")

test_that("sfg_polygons closed",{

  x <- data.frame(
    x = 1:2
    , y = 1:2
  )
  expect_error(
    sfheaders::sfg_polygon( x )
    , "sfheaders - closed polygons must have at least 4 rows"
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
    , "sfheaders - closed polygons must have at least 4 rows"
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
    , "sfheaders - closed polygons must have at least 4 rows"
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

})
