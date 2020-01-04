context("to_df")

test_that("sfc_coordinates constructs a 'max_column' list ",{


  check <- function( lst, non_na ) {
    all( names( which( sapply( lst, function(x) !all(is.na(x) ) ) ) ) %in% non_na )
  }

  x <- matrix( c(11:16), ncol = 2 )
  pt <- sfc_point( x )
  lst_pt <- sfheaders:::rcpp_sfc_point_coordinates( pt ); str( lst_pt )

  x <- matrix( c(1:8), ncol = 2 )
  mpt <- sfc_multipoint( x )
  lst_mpt <- sfheaders:::rcpp_sfc_multipoint_coordinates( mpt ); str( lst_mpt )

  x <- data.frame( id = c(1,1,1,2,2), x = 1:5, y = 5:1 )
  ls <- sfc_linestring( x, linestring_id = "id" )
  lst_ls <- sfheaders:::rcpp_sfc_linestring_coordinates( ls ); str( lst_ls )


  expect_true( length( lst_pt ) == 12 )
  check( lst_pt, c("point_id", "x", "y") )

})

test_that("sfg_coordinate functions get attributes",{

  df <- data.frame(
    id = c(1,1,1,2,2,2)
    , x = c(1,1,1,2,2,2)
    , y = c(3,3,3,4,4,4)
  )

  pt <- sfheaders:::sfg_point(c(1,2))
  mpt <- sfheaders:::sfg_multipoint( df )
  ls <- sfheaders::sfg_linestring(df, x = "x", y = "y")
  mls <- sfheaders::sfg_multilinestring(obj = df, linestring_id = "id")

  m <- cbind( matrix( 1:24, ncol = 2 ), c(rep(1, 6), rep(2, 6) ) )
  p <- sfg_polygon( obj = m, x = 1, y = 2, linestring_id = 3 )

  df <- data.frame(
    polygon_id = c(rep(1, 5), rep(2, 10))
    , line_id = c(rep(1, 10), rep(2, 5))
    , x = c(0,0,1,1,0,2,2,5,5,2,3,3,4,4,3)
    , y = c(0,1,1,0,0,2,5,5,2,2,3,4,4,3,3)
    , z = c(1)
    , m = c(1)
  )

  mp <- sfg_multipolygon( df, x = "x", y = "y", z = "z", polygon_id = "polygon_id", linestring_id = "line_id" )

  res <- sfheaders:::rcpp_sfg_point_coordinates( pt )
  expect_true( attr( res, "sfg_class")[1] == "XY" )
  res <- sfheaders:::rcpp_sfg_multipoint_coordinates( mpt )
  expect_true( attr( res, "sfg_class")[1] == "XYZ" )
  res <- sfheaders:::rcpp_sfg_linestring_coordinates( ls )
  expect_true( attr( res, "sfg_class")[1] == "XY" )
  res <- sfheaders:::rcpp_sfg_multilinestring_coordinates( mls )
  expect_true( attr( res, "sfg_class")[1] == "XY" )
  res <- sfheaders:::rcpp_sfg_polygon_coordinates( p )
  expect_true( attr( res, "sfg_class")[1] == "XY" )
  res <- sfheaders:::rcpp_sfg_multipolygon_coordinates( mp )
  expect_true( attr( res, "sfg_class")[1] == "XYZ" )

})

test_that("sfg objectse convereted to data.frames", {

  df <- data.frame(
    id = c(1,1,1,2,2,2)
    , x = c(1,1,1,2,2,2)
    , y = c(3,3,3,4,4,4)
  )

  pt <- sfheaders:::sfg_point(c(1,2))
  mpt <- sfheaders:::sfg_multipoint( df )
  ls <- sfheaders::sfg_linestring(df, x = "x", y = "y")
  mls <- sfheaders::sfg_multilinestring(obj = df, linestring_id = "id")

  m <- cbind( matrix( 1:24, ncol = 2 ), c(rep(1, 6), rep(2, 6) ) )
  p <- sfg_polygon( obj = m, x = 1, y = 2, linestring_id = 3 )

  df <- data.frame(
    polygon_id = c(rep(1, 5), rep(2, 10))
    , line_id = c(rep(1, 10), rep(2, 5))
    , x = c(0,0,1,1,0,2,2,5,5,2,3,3,4,4,3)
    , y = c(0,1,1,0,0,2,5,5,2,2,3,4,4,3,3)
    , z = c(1)
    , m = c(1)
  )

  mp <- sfg_multipolygon( df, x = "x", y = "y", z = "z", polygon_id = "polygon_id", linestring_id = "line_id" )

  df_pt <- sfheaders::sfg_to_df( pt )
  df_mpt <- sfheaders::sfg_to_df( mpt )
  df_ls <- sfheaders::sfg_to_df( ls )
  df_mls <- sfheaders::sfg_to_df( mls )
  df_p <- sfheaders::sfg_to_df( p )
  df_mp <- sfheaders::sfg_to_df( mp )

  expect_true( inherits( df_pt, "data.frame") )
  expect_true( inherits( df_mpt, "data.frame") )
  expect_true( inherits( df_ls, "data.frame") )
  expect_true( inherits( df_mls, "data.frame") )
  expect_true( inherits( df_p, "data.frame") )
  expect_true( inherits( df_mp, "data.frame") )

  ## x,y,z names
  expect_equal( names( df_mp ), c("polygon_id", "linestring_id", "x", "y", "z") )

  ## round-trip
  res <- sfheaders::sfg_multipolygon(
    df_mp
    , x = "x"
    , y = "y"
    , z = "z"
    , polygon_id = "polygon_id"
    , linestring_id = "linestring_id"
    )

  expect_equal( mp, res )

})
