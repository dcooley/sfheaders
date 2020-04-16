context("boxes")

## issue 77
test_that("boxes created",{

  df <- data.frame(
   id1 = c(1,1,1,1,1,1,1,1,2,2,2,2)
   , id2 = c(1,1,1,1,2,2,2,2,1,1,1,1)
   , x = c(0,0,1,1,1,1,2,2,3,4,4,3)
   , y = c(0,1,1,0,1,2,2,1,3,3,4,4)
  )

  sf_line <- sfheaders::sf_linestring(
    obj = df
    , x = "x"
    , y = "y"
    , linestring_id = "id1"
  )

  sf <- sf_boxes( sf_line )
  sfc <- sf_boxes( sf_line$geometry )
  bbox <- sf_bbox( df, x = "x", y = "y" )

  expect_equal(
    sf$geometry
    , sfc
  )

  expect_equal(
    attr( sfc, "bbox" )
    , bbox
  )

  expect_equal(
    sf_bbox( sfc[1] )
    , sf_bbox( df[ df$id1 == 1, ], x = "x", y = "y" )
  )

  expect_equal(
    sf_bbox( sfc[2] )
    , sf_bbox( df[ df$id1 == 2, ], x = "x", y = "y" )
  )

})
