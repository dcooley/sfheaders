context("geojson")

test_that("to_geojson always returns a Feature, even if ther aren't any properties", {

  sf <- structure(list(geometry = structure(list(structure(c(0, 0), class = c("XY",
  "POINT", "sfg"))), class = c("sfc_POINT", "sfc"), precision = 0, bbox = structure(c(xmin = 0,
  ymin = 0, xmax = 0, ymax = 0), class = "bbox"), crs = structure(list(
  epsg = NA_integer_, proj4string = NA_character_), class = "crs"), n_empty = 0L)), row.names = 1L, class = c("sf",
  "data.frame"), sf_column = "geometry", agr = structure(integer(0), class = "factor", .Label = c("constant",
  "aggregate", "identity"), .Names = character(0)))

  geo <- spatialwidget:::rcpp_geojson_sf(sf, "geometry")
  expect_true(jsonify::validate_json(geo))
  expect_equal( as.character(geo), '[{\"type\":\"Feature\",\"properties\":{},\"geometry\":{\"geometry\":{\"type\":\"Point\",\"coordinates\":[0.0,0.0]}}}]')

  df <- data.frame(lon = 0, lat = 0)
  geo <- spatialwidget:::rcpp_geojson_df(df, list(geometry = c("lon", "lat")))
  expect_true(jsonify::validate_json(geo))
  expect_equal( as.character(geo), '[{\"type\":\"Feature\",\"properties\":{},\"geometry\":{\"geometry\":{\"type\":\"Point\",\"coordinates\":[0.0,0.0]}}}]')

  df <- data.frame(lon = 0, lat = 0)
  expect_error(
    spatialwidget:::rcpp_geojson_df(df, list("lon", "lat"))
    , 'Expecting a list of geometries, each element is named and contains the lon and lat columns'
  )


})

test_that("geometry field changes with user input", {

  df <- data.frame(lon = 0, lat = 0)
  geo <- spatialwidget:::rcpp_geojson_df(df, list(mygeometryproperty = c("lon", "lat")))
  expect_true(jsonify::validate_json(geo))
  expect_equal( as.character(geo), '[{\"type\":\"Feature\",\"properties\":{},\"geometry\":{\"mygeometryproperty\":{\"type\":\"Point\",\"coordinates\":[0.0,0.0]}}}]')

})

test_that("data.frame with z elevation converted", {

  df <- data.frame( id = 1:2, lon = c(0,0), lat = c(0,0), z = c(1,1) )
  expected <- '[{"type":"Feature","properties":{"id":1},"geometry":{"geometry":{"type":"Point","coordinates":[0.0,0.0,1.0]}}},{"type":"Feature","properties":{"id":2},"geometry":{"geometry":{"type":"Point","coordinates":[0.0,0.0,1.0]}}}]'
  res <- spatialwidget:::rcpp_geojson_dfz( df, list( geometry = c( "lon","lat","z" ) ) )
  expect_equal( expected, as.character( res ) )

  df <- data.frame(id = 1:2, lon = c(0,0), lat = c(0,0), z = c(1,1) )
  expect_error(
    spatialwidget:::rcpp_geojson_dfz(df, c("lon","lat","z"))
    , 'Expecting a list of geometries, each element is named and contains the lon, lat and z columns'
  )

  df <- data.frame(id = 1:2, lon = c(0,0), lat = c(0,0), z = c(1,1) )
  expect_error(
    spatialwidget:::rcpp_geojson_dfz(df, c(lon = "lon", lat = "lat", z = "z"))
    , 'Expecting a list of geometries, each element is named and contains the lon, lat and z columns'
  )

})

