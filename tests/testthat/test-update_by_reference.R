context("udpate_by_reference")

test_that("input objects are unchanged",{

  ## POINT
  ### sfg
  x <- 1:2
  res <- sfheaders::sfg_point( x )
  expect_equal( attr( x, "class" ), NULL )

  x <- matrix(1:2, ncol = 2)
  res <- sfheaders::sfg_point( x )
  expect_equal( attr( x, "class" ), NULL )

  x <- data.frame( x = 1, y = 2 )
  res <- sfheaders::sfg_point( x )
  expect_equal( attr( x, "class" ), "data.frame" )

  ### sfc
  x <- 1:2
  res <- sfheaders::sfc_point( x )
  expect_equal( attr( x, "class" ), NULL )

  x <- matrix(1:2, ncol = 2)
  res <- sfheaders::sfc_point( x )
  expect_equal( attr( x, "class" ), NULL )

  x <- data.frame( x = 1, y = 2 )
  res <- sfheaders::sfc_point( x )
  expect_equal( attr( x, "class" ), "data.frame" )

  ## MULTIPOINT
  ### sfg
  x <- 1:2
  res <- sfheaders::sfg_multipoint( x )
  expect_equal( attr( x, "class" ), NULL )

  x <- matrix(1:2, ncol = 2)
  res <- sfheaders::sfg_multipoint( x )
  expect_equal( attr( x, "class" ), NULL )

  x <- data.frame( x = 1, y = 2 )
  res <- sfheaders::sfg_multipoint( x )
  expect_equal( attr( x, "class" ), "data.frame" )

  ### sfc
  x <- 1:2
  res <- sfheaders::sfc_multipoint( x )
  expect_equal( attr( x, "class" ), NULL )

  x <- matrix(1:2, ncol = 2)
  res <- sfheaders::sfc_multipoint( x )
  expect_equal( attr( x, "class" ), NULL )

  x <- data.frame( x = 1, y = 2 )
  res <- sfheaders::sfc_multipoint( x )
  expect_equal( attr( x, "class" ), "data.frame" )

  ## LINESTRING
  ### sfg
  x <- 1:2
  res <- sfheaders::sfg_linestring( x )
  expect_equal( attr( x, "class" ), NULL )

  x <- matrix(1:2, ncol = 2)
  res <- sfheaders::sfg_linestring( x )
  expect_equal( attr( x, "class" ), NULL )

  x <- data.frame( x = 1, y = 2 )
  res <- sfheaders::sfg_linestring( x )
  expect_equal( attr( x, "class" ), "data.frame" )

  ### sfc
  x <- 1:2
  res <- sfheaders::sfc_linestring( x )
  expect_equal( attr( x, "class" ), NULL )

  x <- matrix(1:2, ncol = 2)
  res <- sfheaders::sfc_linestring( x )
  expect_equal( attr( x, "class" ), NULL )

  x <- data.frame( x = 1, y = 2 )
  res <- sfheaders::sfc_linestring( x )
  expect_equal( attr( x, "class" ), "data.frame" )

  ## MULTILINESTRING
  ### sfg
  x <- 1:2
  res <- sfheaders::sfg_multilinestring( x )
  expect_equal( attr( x, "class" ), NULL )

  x <- matrix(1:2, ncol = 2)
  res <- sfheaders::sfg_multilinestring( x )
  expect_equal( attr( x, "class" ), NULL )

  x <- data.frame( x = 1, y = 2 )
  res <- sfheaders::sfg_multilinestring( x )
  expect_equal( attr( x, "class" ), "data.frame" )

  ### sfc
  # x <- 1:2
  # res <- sfheaders::sfc_multilinestring( x )
  # expect_equal( attr( x, "class" ), NULL )

  x <- matrix(1:2, ncol = 2)
  res <- sfheaders::sfc_multilinestring( x )
  expect_equal( attr( x, "class" ), NULL )

  x <- data.frame( x = 1, y = 2 )
  res <- sfheaders::sfc_multilinestring( x )
  expect_equal( attr( x, "class" ), "data.frame" )

  ## POLYGON
  ### sfg
  # x <- 1:2
  # res <- sfheaders::sfg_polygon( x )
  # expect_equal( attr( x, "class" ), NULL )

  x <- matrix(1:2, ncol = 2)
  res <- sfheaders::sfg_polygon( x, close = FALSE )
  expect_equal( attr( x, "class" ), NULL )

  x <- data.frame( x = 1, y = 2 )
  res <- sfheaders::sfg_polygon( x, close = FALSE )
  expect_equal( attr( x, "class" ), "data.frame" )

  ### sfc
  # x <- 1:2
  # res <- sfheaders::sfc_polygon( x )
  # expect_equal( attr( x, "class" ), NULL )

  x <- matrix(1:2, ncol = 2)
  res <- sfheaders::sfc_polygon( x, close = FALSE )
  expect_equal( attr( x, "class" ), NULL )

  x <- data.frame( x = 1, y = 2 )
  res <- sfheaders::sfc_polygon( x, close = FALSE )
  expect_equal( attr( x, "class" ), "data.frame" )


  ## MULTIPOLYGON
  ### sfg
  # x <- 1:2
  # res <- sfheaders::sfg_multipolygon( x )
  # expect_equal( attr( x, "class" ), NULL )

  x <- matrix(1:2, ncol = 2)
  res <- sfheaders::sfg_multipolygon( x, close = FALSE )
  expect_equal( attr( x, "class" ), NULL )

  x <- data.frame( x = 1, y = 2 )
  res <- sfheaders::sfg_multipolygon( x, close = FALSE )
  expect_equal( attr( x, "class" ), "data.frame" )

  ### sfc
  # x <- 1:2
  # res <- sfheaders::sfc_multipolygon( x )
  # expect_equal( attr( x, "class" ), NULL )

  x <- matrix(1:2, ncol = 2)
  res <- sfheaders::sfc_multipolygon( x, close = FALSE )
  expect_equal( attr( x, "class" ), NULL )

  x <- data.frame( x = 1, y = 2 )
  res <- sfheaders::sfc_multipolygon( x, close = FALSE )
  expect_equal( attr( x, "class" ), "data.frame" )

})
