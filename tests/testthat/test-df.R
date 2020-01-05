context("to_df")

test_that("sfc_coordinates constructs a 'max_column' list ",{

  x <- matrix( c(11:16), ncol = 2 )
  pt <- sfc_point( x )
  df_pt <- sfheaders:::rcpp_sfc_to_df( pt )

  expect_true( ncol( df_pt ) == 4 )
  expect_equal( df_pt$x, x[,1] )
  expect_equal( df_pt$y, x[,2] )

  x <- matrix( c(1:8), ncol = 2 )
  mpt <- sfc_multipoint( x )
  df_mpt <- sfheaders:::rcpp_sfc_to_df( mpt )

  expect_true( ncol( df_mpt ) == 4 )
  expect_equal( names( df_mpt ), c("sfg_id", "multipoint_id", "x", "y" ) )
  expect_equal( df_mpt$x, x[,1] )
  expect_equal( df_mpt$y, x[,2] )

  x <- data.frame( id = c(1,1,1,2,2), x = 1:5, y = 5:1 )
  ls <- sfc_linestring( x, linestring_id = "id" )
  df_ls <- sfheaders:::rcpp_sfc_to_df( ls )

  expect_true( ncol( df_ls ) == 4 )
  expect_equal( names( df_ls ), c("sfg_id", "linestring_id", "x", "y" ) )
  expect_equal( df_ls$x, x$x )
  expect_equal( df_ls$y, x$y )

})

test_that("sfg objectse convereted to data.frames", {

  df1 <- data.frame(
    id = c(1,1,1,2,2,2)
    , x = c(1,1,1,2,2,2)
    , y = c(3,3,3,4,4,4)
  )

  pt <- sfheaders:::sfg_point(c(1,2))
  mpt <- sfheaders:::sfg_multipoint( df1, x = "x", y = "y" )
  ls <- sfheaders::sfg_linestring(df1, x = "x", y = "y")
  mls <- sfheaders::sfg_multilinestring(obj = df1, linestring_id = "id")

  m <- cbind( matrix( 1:24, ncol = 2 ), c(rep(1, 6), rep(2, 6) ) )
  p <- sfg_polygon( obj = m, x = 1, y = 2, linestring_id = 3, close = FALSE )

  df2 <- data.frame(
    polygon_id = c(rep(1, 5), rep(2, 10))
    , line_id = c(rep(1, 10), rep(2, 5))
    , x = c(0,0,1,1,0,2,2,5,5,2,3,3,4,4,3)
    , y = c(0,1,1,0,0,2,5,5,2,2,3,4,4,3,3)
    , z = c(1)
    , m = c(1)
  )

  mp <- sfg_multipolygon( df2, x = "x", y = "y", z = "z", polygon_id = "polygon_id", linestring_id = "line_id" )

  df_pt <- sfheaders::sfg_to_df( pt )
  expect_equal( df_pt$x, 1 )
  expect_equal( df_pt$y, 2 )

  df_mpt <- sfheaders::sfg_to_df( mpt )
  expect_equal( df_mpt$x, df1$x )
  expect_equal( df_mpt$y, df1$y )

  df_ls <- sfheaders::sfg_to_df( ls )
  expect_equal( df_ls$x, df1$x )
  expect_equal( df_ls$y, df1$y )

  df_mls <- sfheaders::sfg_to_df( mls )
  expect_equal( df_mls$x, df1$x )
  expect_equal( df_mls$y, df1$y )

  df_p <- sfheaders::sfg_to_df( p )
  expect_equal( df_p$x, m[,1] )
  expect_equal( df_p$y, m[,2] )

  df_mp <- sfheaders::sfg_to_df( mp )
  expect_equal( df_mp$x, df2$x )
  expect_equal( df_mp$y, df2$y )

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
