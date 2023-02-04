context("sfg")

test_that("sfg dimensions", {

  expect_error( sfheaders:::rcpp_sfg_dimension( 1, "" ), "sfheaders - invalid dimension" )
  expect_equal( sfheaders:::rcpp_sfg_dimension( 1:2, "" ), "XY" )
  expect_equal( sfheaders:::rcpp_sfg_dimension( 1:3, "" ), "XYZ" )
  expect_equal( sfheaders:::rcpp_sfg_dimension( 1:4, "" ), "XYZM" )
  expect_error( sfheaders:::rcpp_sfg_dimension( 1:5, "" ), "sfheaders - invalid dimension" )

  expect_equal( sfheaders:::rcpp_sfg_dimension( c(NA_real_, NA_real_), "" ), "XY" ) ## geojsonsf issue 91
  # expect_error( sfheaders:::rcpp_sfg_dimension( c(NA_real_, NA_real_), "" ), "XY" ) ## geojsonsf issue 91

  m <- matrix(1:2, ncol = 2 )
  expect_equal( sfheaders:::rcpp_sfg_dimension( m, "" ), "XY" )
  m <- matrix(1:3, ncol = 3 )
  expect_equal( sfheaders:::rcpp_sfg_dimension( m, "" ), "XYZ" )
  m <- matrix(1:4, ncol = 4 )
  expect_equal( sfheaders:::rcpp_sfg_dimension( m, "" ), "XYZM" )

  df <- data.frame(lon = 1, lat = 1)
  expect_equal( sfheaders:::rcpp_sfg_dimension( df, "" ), "XY" )
  df <- data.frame(lon = 1, lat = 1, z = 1)
  expect_equal( sfheaders:::rcpp_sfg_dimension( df, "" ), "XYZ" )
  df <- data.frame(lon = 1, lat = 1, z = 1, m = 1)
  expect_equal( sfheaders:::rcpp_sfg_dimension( df, "" ), "XYZM" )

  l <- list( 1, 2 )
  expect_error( sfheaders:::rcpp_sfg_dimension( l, "" ), "sfheaders - invalid dimension" )



  expect_error( sfheaders:::rcpp_sfg_dimension( 1, "" ), "sfheaders - invalid dimension" )
  expect_equal( sfheaders:::rcpp_sfg_dimension( 1:2, "XY" ), "XY" )
  expect_equal( sfheaders:::rcpp_sfg_dimension( 1:3, "XYZ" ), "XYZ" )
  expect_equal( sfheaders:::rcpp_sfg_dimension( 1:4, "XYZM" ), "XYZM" )
  expect_error( sfheaders:::rcpp_sfg_dimension( 1:5, "" ), "sfheaders - invalid dimension" )

  m <- matrix(1:2, ncol = 2 )
  expect_equal( sfheaders:::rcpp_sfg_dimension( m, "XY" ), "XY" )
  m <- matrix(1:3, ncol = 3 )
  expect_equal( sfheaders:::rcpp_sfg_dimension( m, "XYZ" ), "XYZ" )
  m <- matrix(1:4, ncol = 4 )
  expect_equal( sfheaders:::rcpp_sfg_dimension( m, "XYZM" ), "XYZM" )

  df <- data.frame(lon = 1, lat = 1)
  expect_equal( sfheaders:::rcpp_sfg_dimension( df, "XY" ), "XY" )
  df <- data.frame(lon = 1, lat = 1, z = 1)
  expect_equal( sfheaders:::rcpp_sfg_dimension( df, "XYZ" ), "XYZ" )
  df <- data.frame(lon = 1, lat = 1, z = 1, m = 1)
  expect_equal( sfheaders:::rcpp_sfg_dimension( df, "XYZM" ), "XYZM" )

  l <- list( 1, 2 )
  expect_error( sfheaders:::rcpp_sfg_dimension( l, "" ), "sfheaders - invalid dimension" )

})

test_that("R-API geometry columns tested for dimension",{
  df <- data.frame(
    x = 1:4
    , y = 1:4
    , z = 1:4
    , m = 1:4
    , id1 = 1
    , id2 = 1
    , val = 1:4
  )

  expect_error(
    sfc_linestring(obj = df, x = "x")
    , "sfheaders - unknown combination of x, y, z and m arguments"
  )

  expect_error(
    sfc_linestring(obj = df, y = "x")
    , "sfheaders - unknown combination of x, y, z and m arguments"
  )

  expect_error(
    sfc_linestring(obj = df, z = "x")
    , "sfheaders - unknown combination of x, y, z and m arguments"
  )

  expect_error(
    sfc_linestring(obj = df, z = "x")
    , "sfheaders - unknown combination of x, y, z and m arguments"
  )

  expect_error(
    sfc_linestring(obj = df, x = "x", z = "y")
    , "sfheaders - unknown combination of x, y, z and m arguments"
  )

  expect_error(
    sfc_linestring(obj = df, x = "x", m = "y")
    , "sfheaders - unknown combination of x, y, z and m arguments"
  )

  expect_error(
    sfc_linestring(obj = df, y = "x", z = "y")
    , "sfheaders - unknown combination of x, y, z and m arguments"
  )

  expect_error(
    sfc_linestring(obj = df, y = "x", m = "y")
    , "sfheaders - unknown combination of x, y, z and m arguments"
  )


})

test_that("R-API supplying x, y, z, m columns gives correct dimension",{

  df <- data.frame(
    x = 1:4
    , y = 1:4
    , z = 1:4
    , m = 1:4
    , id1 = 1
    , id2 = 1
    , val = 1:4
  )

  ## sfg
  res <- sfg_point(obj = df[1, ], x = "x", y = "y", z = "m")
  expect_true( attr(res, "class")[1] == "XYZ" )
  res <- sfg_point(obj = df[1, ], x = "x", y = "y", m = "m")
  expect_true( attr(res, "class")[1] == "XYM" )
  res <- sfg_point(obj = df[1, ], x = "x", y = "y", z = "z", m = "m")
  expect_true( attr(res, "class")[1] == "XYZM" )

  res <- sfg_multipoint(obj = df, x = "x", y = "y", z = "m")
  expect_true( attr(res, "class")[1] == "XYZ" )
  res <- sfg_multipoint(obj = df, x = "x", y = "y", m = "m")
  expect_true( attr(res, "class")[1] == "XYM" )
  res <- sfg_multipoint(obj = df, x = "x", y = "y", z = "z", m = "m")
  expect_true( attr(res, "class")[1] == "XYZM" )

  res <- sfg_linestring(obj = df, x = "x", y = "y", z = "m")
  expect_true( attr(res, "class")[1] == "XYZ" )
  res <- sfg_linestring(obj = df, x = "x", y = "y", m = "m")
  expect_true( attr(res, "class")[1] == "XYM" )
  res <- sfg_linestring(obj = df, x = "x", y = "y", z = "z", m = "m")
  expect_true( attr(res, "class")[1] == "XYZM" )

  res <- sfg_multilinestring(obj = df, x = "x", y = "y", z = "m")
  expect_true( attr(res, "class")[1] == "XYZ" )
  res <- sfg_multilinestring(obj = df, x = "x", y = "y", m = "m")
  expect_true( attr(res, "class")[1] == "XYM" )
  res <- sfg_multilinestring(obj = df, x = "x", y = "y", z = "z", m = "m")
  expect_true( attr(res, "class")[1] == "XYZM" )

  res <- sfg_polygon(obj = df, x = "x", y = "y", z = "m")
  expect_true( attr(res, "class")[1] == "XYZ" )
  res <- sfg_polygon(obj = df, x = "x", y = "y", m = "m")
  expect_true( attr(res, "class")[1] == "XYM" )
  res <- sfg_polygon(obj = df, x = "x", y = "y", z = "z", m = "m")
  expect_true( attr(res, "class")[1] == "XYZM" )

  res <- sfg_multipolygon(obj = df, x = "x", y = "y", z = "m")
  expect_true( attr(res, "class")[1] == "XYZ" )
  res <- sfg_multipolygon(obj = df, x = "x", y = "y", m = "m")
  expect_true( attr(res, "class")[1] == "XYM" )
  res <- sfg_multipolygon(obj = df, x = "x", y = "y", z = "z", m = "m")
  expect_true( attr(res, "class")[1] == "XYZM" )


  ## sfc
  res <- sfc_point(obj = df[1, ], x = "x", y = "y", z = "m")
  expect_true( attr(res[[1]], "class")[1] == "XYZ" )
  res <- sfc_point(obj = df[1, ], x = "x", y = "y", m = "m")
  expect_true( attr(res[[1]], "class")[1] == "XYM" )
  res <- sfc_point(obj = df[1, ], x = "x", y = "y", z = "z", m = "m")
  expect_true( attr(res[[1]], "class")[1] == "XYZM" )

  res <- sfc_multipoint(obj = df, x = "x", y = "y", z = "m")
  expect_true( attr(res[[1]], "class")[1] == "XYZ" )
  res <- sfc_multipoint(obj = df, x = "x", y = "y", m = "m")
  expect_true( attr(res[[1]], "class")[1] == "XYM" )
  res <- sfc_multipoint(obj = df, x = "x", y = "y", z = "z", m = "m")
  expect_true( attr(res[[1]], "class")[1] == "XYZM" )

  res <- sfc_linestring(obj = df, x = "x", y = "y", z = "m")
  expect_true( attr(res[[1]], "class")[1] == "XYZ" )
  res <- sfc_linestring(obj = df, x = "x", y = "y", m = "m")
  expect_true( attr(res[[1]], "class")[1] == "XYM" )
  res <- sfc_linestring(obj = df, x = "x", y = "y", z = "z", m = "m")
  expect_true( attr(res[[1]], "class")[1] == "XYZM" )

  res <- sfc_multilinestring(obj = df, x = "x", y = "y", z = "m")
  expect_true( attr(res[[1]], "class")[1] == "XYZ" )
  res <- sfc_multilinestring(obj = df, x = "x", y = "y", m = "m")
  expect_true( attr(res[[1]], "class")[1] == "XYM" )
  res <- sfc_multilinestring(obj = df, x = "x", y = "y", z = "z", m = "m")
  expect_true( attr(res[[1]], "class")[1] == "XYZM" )

  res <- sfc_polygon(obj = df, x = "x", y = "y", z = "m")
  expect_true( attr(res[[1]], "class")[1] == "XYZ" )
  res <- sfc_polygon(obj = df, x = "x", y = "y", m = "m")
  expect_true( attr(res[[1]], "class")[1] == "XYM" )
  res <- sfc_polygon(obj = df, x = "x", y = "y", z = "z", m = "m")
  expect_true( attr(res[[1]], "class")[1] == "XYZM" )

  res <- sfc_multipolygon(obj = df, x = "x", y = "y", z = "m")
  expect_true( attr(res[[1]], "class")[1] == "XYZ" )
  res <- sfc_multipolygon(obj = df, x = "x", y = "y", m = "m")
  expect_true( attr(res[[1]], "class")[1] == "XYM" )
  res <- sfc_multipolygon(obj = df, x = "x", y = "y", z = "z", m = "m")
  expect_true( attr(res[[1]], "class")[1] == "XYZM" )

  ## sf
  res <- sf_point(obj = df, x = "x", y = "y", z = "m")
  expect_true( attr(res[[1]][[1]], "class")[1] == "XYZ" )
  res <- sf_point(obj = df, x = "x", y = "y", m = "m")
  expect_true( attr(res[[1]][[1]], "class")[1] == "XYM" )
  res <- sf_point(obj = df, x = "x", y = "y", z = "z", m = "m")
  expect_true( attr(res[[1]][[1]], "class")[1] == "XYZM" )

  res <- sf_multipoint(obj = df, x = "x", y = "y", z = "m")
  expect_true( attr(res$geometry[[1]], "class")[1] == "XYZ" )
  res <- sf_multipoint(obj = df, x = "x", y = "y", m = "m")
  expect_true( attr(res$geometry[[1]], "class")[1] == "XYM" )
  res <- sf_multipoint(obj = df, x = "x", y = "y", z = "z", m = "m")
  expect_true( attr(res$geometry[[1]], "class")[1] == "XYZM" )

  res <- sf_linestring(obj = df, x = "x", y = "y", z = "m")
  expect_true( attr(res$geometry[[1]], "class")[1] == "XYZ" )
  res <- sf_linestring(obj = df, x = "x", y = "y", m = "m")
  expect_true( attr(res$geometry[[1]], "class")[1] == "XYM" )
  res <- sf_linestring(obj = df, x = "x", y = "y", z = "z", m = "m")
  expect_true( attr(res$geometry[[1]], "class")[1] == "XYZM" )

  res <- sf_multilinestring(obj = df, x = "x", y = "y", z = "m")
  expect_true( attr(res$geometry[[1]], "class")[1] == "XYZ" )
  res <- sf_multilinestring(obj = df, x = "x", y = "y", m = "m")
  expect_true( attr(res$geometry[[1]], "class")[1] == "XYM" )
  res <- sf_multilinestring(obj = df, x = "x", y = "y", z = "z", m = "m")
  expect_true( attr(res$geometry[[1]], "class")[1] == "XYZM" )

  res <- sf_polygon(obj = df, x = "x", y = "y", z = "m")
  expect_true( attr(res$geometry[[1]], "class")[1] == "XYZ" )
  res <- sf_polygon(obj = df, x = "x", y = "y", m = "m")
  expect_true( attr(res$geometry[[1]], "class")[1] == "XYM" )
  res <- sf_polygon(obj = df, x = "x", y = "y", z = "z", m = "m")
  expect_true( attr(res$geometry[[1]], "class")[1] == "XYZM" )

  res <- sf_multipolygon(obj = df, x = "x", y = "y", z = "m")
  expect_true( attr(res$geometry[[1]], "class")[1] == "XYZ" )
  res <- sf_multipolygon(obj = df, x = "x", y = "y", m = "m")
  expect_true( attr(res$geometry[[1]], "class")[1] == "XYM" )
  res <- sf_multipolygon(obj = df, x = "x", y = "y", z = "z", m = "m")
  expect_true( attr(res$geometry[[1]], "class")[1] == "XYZM" )


})






