context("cast")

test_that("cast to sfc_POINT", {

  df <- data.frame(
    id1 = c(1,1,1,1,1,1,1,1,2,2,2,2)
    , id2 = c(1,1,1,1,2,2,2,2,1,1,1,1)
    , x = c(0,0,1,1,1,1,2,2,3,4,4,3)
    , y = c(0,1,1,0,1,2,2,1,3,3,4,4)
  )

  pt <- sfc_point(obj = df, x = "x", y = "y", z = "id1")
  mpt <- sfc_multipoint(obj = df, x = "x", y = "y", multipoint_id = "id1")
  ls <- sfc_linestring(obj = df, x = "x", y = "y", linestring_id = "id1")
  mls <- sfc_multilinestring(obj = df, x = "x", y = "y", multilinestring_id = "id1")
  p <- sfc_polygon(obj = df, x = "x", y = "y", polygon_id = "id1", linestring_id = "id2", close = FALSE )
  mp <- sfc_multipolygon(obj = df, x = "x", y = "y", multipolygon_id = "id1", linestring_id = "id2", close = FALSE )

  sfc_casted <- function( sfc, cast_to ) {
    cls <- attr( sfc, "class")
    return( cls[1] == paste0("sfc_", cast_to) )
  }

  sfg_casted <- function( sfc, cast_to ) {
    res <- unique( sapply( sfc, function(x) attr(x, "class")[2] ) )
    return( length( res ) == 1 & cast_to == res )
  }

  has_round_tripped <- function( df_orig, df_res ) {
    all( df_res[["x"]] == df_orig[["x"]] ) &
      all( df_res[["y"]] == df_orig[["y"]] )
  }

  cast_to <- "POINT"
  res <- sfc_cast( pt, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

  res <- sfc_cast( mpt, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

  res <- sfc_cast( ls, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

  res <- sfc_cast( mls, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

  res <- sfc_cast( p, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

  res <- sfc_cast( mp, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

})


test_that("cast to sfc_MULTIPOINT", {

  df <- data.frame(
    id1 = c(1,1,1,1,1,1,1,1,2,2,2,2)
    , id2 = c(1,1,1,1,2,2,2,2,1,1,1,1)
    , x = c(0,0,1,1,1,1,2,2,3,4,4,3)
    , y = c(0,1,1,0,1,2,2,1,3,3,4,4)
  )

  pt <- sfc_point(obj = df, x = "x", y = "y")
  mpt <- sfc_multipoint(obj = df, x = "x", y = "y", multipoint_id = "id1")
  ls <- sfc_linestring(obj = df, x = "x", y = "y", linestring_id = "id1")
  mls <- sfc_multilinestring(obj = df, x = "x", y = "y", multilinestring_id = "id1")
  p <- sfc_polygon(obj = df, x = "x", y = "y", polygon_id = "id1", linestring_id = "id2", close = FALSE )
  mp <- sfc_multipolygon(obj = df, x = "x", y = "y", multipolygon_id = "id1", linestring_id = "id2", close = FALSE )

  sfc_casted <- function( sfc, cast_to ) {
    cls <- attr( sfc, "class")
    return( cls[1] == paste0("sfc_", cast_to) )
  }

  sfg_casted <- function( sfc, cast_to ) {
    res <- unique( sapply( sfc, function(x) attr(x, "class")[2] ) )
    return( length( res ) == 1 & cast_to == res )
  }

  has_round_tripped <- function( df_orig, df_res ) {
    all( df_res[["x"]] == df_orig[["x"]] ) &
      all( df_res[["y"]] == df_orig[["y"]] )
  }

  cast_to <- "MULTIPOINT"
  res <- sfc_cast( pt, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

  res <- sfc_cast( mpt, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

  res <- sfc_cast( ls, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

  res <- sfc_cast( mls, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

  res <- sfc_cast( p, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

  res <- sfc_cast( mp, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

})


test_that("cast to sfc_LINESTRING", {

  df <- data.frame(
    id1 = c(1,1,1,1,1,1,1,1,2,2,2,2)
    , id2 = c(1,1,1,1,2,2,2,2,1,1,1,1)
    , x = c(0,0,1,1,1,1,2,2,3,4,4,3)
    , y = c(0,1,1,0,1,2,2,1,3,3,4,4)
  )

  pt <- sfc_point(obj = df, x = "x", y = "y")
  mpt <- sfc_multipoint(obj = df, x = "x", y = "y", multipoint_id = "id1")
  ls <- sfc_linestring(obj = df, x = "x", y = "y", linestring_id = "id1")
  mls <- sfc_multilinestring(obj = df, x = "x", y = "y", multilinestring_id = "id1")
  p <- sfc_polygon(obj = df, x = "x", y = "y", polygon_id = "id1", linestring_id = "id2", close = FALSE )
  mp <- sfc_multipolygon(obj = df, x = "x", y = "y", multipolygon_id = "id1", linestring_id = "id2", close = FALSE )

  sfc_casted <- function( sfc, cast_to ) {
    cls <- attr( sfc, "class")
    return( cls[1] == paste0("sfc_", cast_to) )
  }

  sfg_casted <- function( sfc, cast_to ) {
    res <- unique( sapply( sfc, function(x) attr(x, "class")[2] ) )
    return( length( res ) == 1 & cast_to == res )
  }

  has_round_tripped <- function( df_orig, df_res ) {
    all( df_res[["x"]] == df_orig[["x"]] ) &
      all( df_res[["y"]] == df_orig[["y"]] )
  }

  cast_to <- "LINESTRING"
  res <- sfc_cast( pt, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

  res <- sfc_cast( mpt, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

  res <- sfc_cast( ls, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

  res <- sfc_cast( mls, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

  res <- sfc_cast( p, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

  res <- sfc_cast( mp, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

})


test_that("cast to sfc_MULTILINESTRING", {

  df <- data.frame(
    id1 = c(1,1,1,1,1,1,1,1,2,2,2,2)
    , id2 = c(1,1,1,1,2,2,2,2,1,1,1,1)
    , x = c(0,0,1,1,1,1,2,2,3,4,4,3)
    , y = c(0,1,1,0,1,2,2,1,3,3,4,4)
  )

  pt <- sfc_point(obj = df, x = "x", y = "y")
  mpt <- sfc_multipoint(obj = df, x = "x", y = "y", multipoint_id = "id1")
  ls <- sfc_linestring(obj = df, x = "x", y = "y", linestring_id = "id1")
  mls <- sfc_multilinestring(obj = df, x = "x", y = "y", multilinestring_id = "id1")
  p <- sfc_polygon(obj = df, x = "x", y = "y", polygon_id = "id1", linestring_id = "id2", close = FALSE )
  mp <- sfc_multipolygon(obj = df, x = "x", y = "y", multipolygon_id = "id1", linestring_id = "id2", close = FALSE )

  sfc_casted <- function( sfc, cast_to ) {
    cls <- attr( sfc, "class")
    return( cls[1] == paste0("sfc_", cast_to) )
  }

  sfg_casted <- function( sfc, cast_to ) {
    res <- unique( sapply( sfc, function(x) attr(x, "class")[2] ) )
    return( length( res ) == 1 & cast_to == res )
  }

  has_round_tripped <- function( df_orig, df_res ) {
    all( df_res[["x"]] == df_orig[["x"]] ) &
      all( df_res[["y"]] == df_orig[["y"]] )
  }

  cast_to <- "MULTILINESTRING"
  res <- sfc_cast( pt, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

  res <- sfc_cast( mpt, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

  res <- sfc_cast( ls, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

  res <- sfc_cast( mls, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

  res <- sfc_cast( p, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

  res <- sfc_cast( mp, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

})


test_that("cast to sfc_POLYGON", {

  df <- data.frame(
    id1 = c(1,1,1,1,1,1,1,1,2,2,2,2)
    , id2 = c(1,1,1,1,2,2,2,2,1,1,1,1)
    , x = c(0,0,1,1,1,1,2,2,3,4,4,3)
    , y = c(0,1,1,0,1,2,2,1,3,3,4,4)
  )

  pt <- sfc_point(obj = df, x = "x", y = "y")
  mpt <- sfc_multipoint(obj = df, x = "x", y = "y", multipoint_id = "id1")
  ls <- sfc_linestring(obj = df, x = "x", y = "y", linestring_id = "id1")
  mls <- sfc_multilinestring(obj = df, x = "x", y = "y", multilinestring_id = "id1")
  p <- sfc_polygon(obj = df, x = "x", y = "y", polygon_id = "id1", linestring_id = "id2", close = FALSE )
  mp <- sfc_multipolygon(obj = df, x = "x", y = "y", multipolygon_id = "id1", linestring_id = "id2", close = FALSE )

  sfc_casted <- function( sfc, cast_to ) {
    cls <- attr( sfc, "class")
    return( cls[1] == paste0("sfc_", cast_to) )
  }

  sfg_casted <- function( sfc, cast_to ) {
    res <- unique( sapply( sfc, function(x) attr(x, "class")[2] ) )
    return( length( res ) == 1 & cast_to == res )
  }

  has_round_tripped <- function( df_orig, df_res ) {
    all( df_res[["x"]] == df_orig[["x"]] ) &
      all( df_res[["y"]] == df_orig[["y"]] )
  }

  cast_to <- "POLYGON"
  expect_error(
    sfc_cast( pt, cast_to, close = FALSE )
    , "sfheaders - can't cast from POINT to POLYGON"
  )

  res <- sfc_cast( mpt, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

  res <- sfc_cast( ls, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

  res <- sfc_cast( mls, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

  res <- sfc_cast( p, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

  res <- sfc_cast( mp, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

})


test_that("cast to sfc_MULTIPOLYGON", {

  df <- data.frame(
    id1 = c(1,1,1,1,1,1,1,1,2,2,2,2)
    , id2 = c(1,1,1,1,2,2,2,2,1,1,1,1)
    , x = c(0,0,1,1,1,1,2,2,3,4,4,3)
    , y = c(0,1,1,0,1,2,2,1,3,3,4,4)
  )

  pt <- sfc_point(obj = df, x = "x", y = "y")
  mpt <- sfc_multipoint(obj = df, x = "x", y = "y", multipoint_id = "id1")
  ls <- sfc_linestring(obj = df, x = "x", y = "y", linestring_id = "id1")
  mls <- sfc_multilinestring(obj = df, x = "x", y = "y", multilinestring_id = "id1")
  p <- sfc_polygon(obj = df, x = "x", y = "y", polygon_id = "id1", linestring_id = "id2", close = FALSE )
  mp <- sfc_multipolygon(obj = df, x = "x", y = "y", multipolygon_id = "id1", linestring_id = "id2", close = FALSE )

  sfc_casted <- function( sfc, cast_to ) {
    cls <- attr( sfc, "class")
    return( cls[1] == paste0("sfc_", cast_to) )
  }

  sfg_casted <- function( sfc, cast_to ) {
    res <- unique( sapply( sfc, function(x) attr(x, "class")[2] ) )
    return( length( res ) == 1 & cast_to == res )
  }

  has_round_tripped <- function( df_orig, df_res ) {
    all( df_res[["x"]] == df_orig[["x"]] ) &
      all( df_res[["y"]] == df_orig[["y"]] )
  }

  cast_to <- "MULTIPOLYGON"
  expect_error(
    sfc_cast( pt, cast_to, close = FALSE )
    , "sfheaders - can't cast from POINT to MULTIPOLYGON"
  )

  res <- sfc_cast( mpt, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

  res <- sfc_cast( ls, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

  res <- sfc_cast( mls, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

  res <- sfc_cast( p, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

  res <- sfc_cast( mp, cast_to, close = FALSE )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

})


test_that("mixed sfc_GEOMETRY is casted",{

  df <- data.frame(
    id1 = c(1,1,1,1,1,1,1,1,2,2,2,2)
    , id2 = c(1,1,1,1,2,2,2,2,1,1,1,1)
    , x = c(0,0,1,1,1,1,2,2,3,4,4,3)
    , y = c(0,1,1,0,1,2,2,1,3,3,4,4)
  )

  # pt <- sf_point(obj = df, x = "x", y = "y")
  mpt <- sf_multipoint(obj = df, x = "x", y = "y", multipoint_id = "id1")
  ls <- sf_linestring(obj = df, x = "x", y = "y", linestring_id = "id1")
  mls <- sf_multilinestring(obj = df, x = "x", y = "y", multilinestring_id = "id1")
  # p <- sf_polygon(obj = df, x = "x", y = "y", polygon_id = "id1", linestring_id = "id2", close = FALSE )
  # mp <- sf_multipolygon(obj = df, x = "x", y = "y", multipolygon_id = "id1", linestring_id = "id2", close = FALSE )

  sf <- rbind( mpt, ls, mls )

  sfc_casted <- function( sfc, cast_to ) {
    cls <- attr( sfc, "class")
    return( cls[1] == paste0("sfc_", cast_to) )
  }

  sfg_casted <- function( sfc, cast_to ) {
    res <- unique( sapply( sfc, function(x) attr(x, "class")[2] ) )
    return( length( res ) == 1 & cast_to == res )
  }

  has_round_tripped <- function( df_orig, df_res ) {
    all( df_res[["x"]] == df_orig[["x"]] ) &
      all( df_res[["y"]] == df_orig[["y"]] )
  }

  cast_to <- "POINT"
  res <- sfc_cast( sf$geometry, cast_to )
  df_res <- sfheaders::sfc_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res, cast_to ) )
  expect_true( sfg_casted( res, cast_to ) )

})

test_that("sf objects are casted",{

  df <- data.frame(
    id1 = c(1,1,1,1,1,1,1,1,2,2,2,2)
    , id2 = c(1,1,1,1,2,2,2,2,1,1,1,1)
    , x = c(0,0,1,1,1,1,2,2,3,4,4,3)
    , y = c(0,1,1,0,1,2,2,1,3,3,4,4)
  )

  # pt <- sf_point(obj = df, x = "x", y = "y")
  mpt <- sf_multipoint(obj = df, x = "x", y = "y", multipoint_id = "id1")
  ls <- sf_linestring(obj = df, x = "x", y = "y", linestring_id = "id1")
  mls <- sf_multilinestring(obj = df, x = "x", y = "y", multilinestring_id = "id1")
  # p <- sf_polygon(obj = df, x = "x", y = "y", polygon_id = "id1", linestring_id = "id2", close = FALSE )
  # mp <- sf_multipolygon(obj = df, x = "x", y = "y", multipolygon_id = "id1", linestring_id = "id2", close = FALSE )

  sf <- rbind( mpt, ls, mls )

  sfc_casted <- function( sfc, cast_to ) {
    cls <- attr( sfc, "class")
    return( cls[1] == paste0("sfc_", cast_to) )
  }

  sfg_casted <- function( sfc, cast_to ) {
    res <- unique( sapply( sfc, function(x) attr(x, "class")[2] ) )
    return( length( res ) == 1 & cast_to == res )
  }

  has_round_tripped <- function( df_orig, df_res ) {
    all( df_res[["x"]] == df_orig[["x"]] ) &
      all( df_res[["y"]] == df_orig[["y"]] )
  }

  cast_to <- "POINT"
  res <- sf_cast( sf, cast_to )
  df_res <- sfheaders::sf_to_df( res )
  expect_true( has_round_tripped( df, df_res ))
  expect_true( sfc_casted( res$geometry, cast_to ) )
  expect_true( sfg_casted( res$geometry, cast_to ) )

  new_coords <- sfheaders:::rcpp_count_new_sfc_objects( sf$geometry, cast_to )

  expect_true( nrow( res ) == sum( new_coords ) )


})