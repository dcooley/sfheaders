context("to_df")

test_that("sfc_to_df constructs data.frames",{

  x <- matrix( c(11:16), ncol = 2 )
  pt <- sfc_point( x )
  df_pt <- sfheaders:::rcpp_sfc_to_df( pt )

  expect_true( ncol( df_pt ) == 4 )
  expect_equal( df_pt$x, x[,1] )
  expect_equal( df_pt$y, x[,2] )

  x <- matrix( c(1:8), ncol = 2 )
  mpt <- sfc_multipoint( x )
  df_mpt <- sfheaders:::rcpp_sfc_to_df( mpt )

  expect_equal( names( df_mpt ), c("sfg_id", "multipoint_id", "x", "y" ) )
  expect_equal( df_mpt$x, x[,1] )
  expect_equal( df_mpt$y, x[,2] )


  x <- data.frame( id = c(1,1,1,2,2), x = 1:5, y = 5:1 )
  ls <- sfc_linestring( x, linestring_id = "id" )
  df_ls <- sfheaders:::rcpp_sfc_to_df( ls )

  expect_equal( names( df_ls ), c("sfg_id", "linestring_id", "x", "y" ) )
  expect_equal( df_ls$x, x$x )
  expect_equal( df_ls$y, x$y )

  x <- data.frame(
    ml_id = c(1,1,1,1,1,1,1,1,2,2,2,2,2)
    , l_id = c(1,1,1,2,2,3,3,3,1,1,1,2,2)
    , x = rnorm(13)
    , y = rnorm(13)
    , z = rnorm(13)
    , m = rnorm(13)
  )

  mls <- sfc_multilinestring( obj = x, x = "x", y = "y")
  df_mls <- sfc_to_df( mls )

  expect_equal( names( df_mls ), c("sfg_id", "multilinestring_id", "linestring_id", "x", "y" ) )
  expect_equal( df_mls$x, x$x )
  expect_equal( df_mls$y, x$y )

  x <- data.frame(
    ml_id = c(1,1,1,1,1,1,1,1,1,2,2,2,2,2,2)
    , l_id = c(1,1,1,2,2,2,3,3,3,1,1,1,2,2,2)
    , x = rnorm(15)
    , y = rnorm(15)
    , z = rnorm(15)
    , m = rnorm(15)
  )

  p <- sfc_polygon( obj = x, x = "x", y = "y", close = FALSE)
  df_p <- sfc_to_df( p )

  expect_equal( names( df_p ), c("sfg_id", "polygon_id", "linestring_id", "x", "y" ) )
  expect_equal( df_p$x, x$x )
  expect_equal( df_p$y, x$y )

  x <- data.frame(
    id1 = c(1,1,1,1,1,1,1,1,1,1)
    , id2 = c(1,1,1,1,1,2,2,2,2,2)
    , x = c(0,0,1,1,0,1,1,2,2,1)
    , y = c(0,1,1,0,0,1,2,2,1,1)
  )

  mp <- sfc_multipolygon( x, multipolygon_id = "id1", polygon_id = "id2")
  df_mp <- sfc_to_df( mp )

  expect_equal( names( df_mp ), c("sfg_id", "multipolygon_id", "polygon_id", "linestring_id", "x", "y" ) )
  expect_equal( df_mp$x, x$x )
  expect_equal( df_mp$y, x$y )

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


  mpz <- sfg_multipolygon(
    df2, x = "x", y = "y", z = "z"
    , polygon_id = "polygon_id", linestring_id = "line_id"
  )

  mpzm <- sfg_multipolygon(
    df2, x = "x", y = "y", z = "z", m = "m"
    , polygon_id = "polygon_id", linestring_id = "line_id"
    )

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

  df_mp <- sfheaders::sfg_to_df( mpz )
  expect_equal( df_mp$x, df2$x )
  expect_equal( df_mp$y, df2$y )

  df_mpzm <- sfheaders::sfg_to_df( mpzm )
  expect_equal( df_mpzm$z, df2$z )
  expect_equal( df_mpzm$m, df2$m )

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

  expect_equal( mpz, res )

})

test_that("different data.frame columns supported",{

  df <- data.frame(
    id = 1L
    , dte = as.Date("2020-01-01")
    , psx = as.POSIXct("2020-01-01 00:00:01")
    , fct = "a"
    , num = 1.5
    , int = 1L
    , cplx = as.complex(1.0)
    , rw = as.raw(1.0)
    , lgl = as.logical(T)
    , x = 1
    , y = 2
    , stringsAsFactors = F
  )

  sf <- sfheaders::sf_point( obj = df, x = "x", y = "y" )
  sf$id <- 1L
  sf <- merge(
    x = sf
    , y = df[, setdiff(names(df), c("x","y"))]
    , by = "id"
  )

  ## needs 'sf' unattached for this to work
  expect_error(
    sfheaders::sf_to_df( sf, fill = TRUE )
    , "sfheaders - sf_column not found"
  )

  attr(sf, "class") <- c("sf", "data.frame")
  attr(sf, "sf_column") <- "geometry"

  res <- sfheaders::sf_to_df( sf, fill = TRUE )

  test_cols <- names( df )

  expect_equal(
    res[, test_cols ]
    , df[, test_cols ]
  )

  sf <- sf_point( obj = 1:2 )
  sf$id <- 1L
  sf$geometry2 <- sfc_point( obj = 3:4 )

  expect_error(
    sf_to_df( sf, fill = TRUE )
    , "sfheaders - unsupported column type using fill = TRUE"
  )

})


test_that("different XYZM dimensions work",{

  x <- matrix( c(1:16), ncol = 4 )
  sfc <- sfc_point( x, x = 1, y = 2, z = 3  )
  res <- sfheaders:::rcpp_sfc_to_df( sfc )

  expect_true( ncol( res ) == 5 )
  expect_true( "z" %in% names(res) )
  expect_false( "m" %in% names(res) )

  x <- matrix( c(1:16), ncol = 4 )
  sfc <- sfc_point( x, x = 1, y = 2, z = 3, m = 4 )
  res <- sfheaders:::rcpp_sfc_to_df( sfc )

  expect_true( ncol( res ) == 6 )
  expect_true( "z" %in% names(res) )
  expect_true( "m" %in% names(res) )


  x <- matrix( c(1:16), ncol = 4 )
  x[1,1] <- 1.1
  sfc <- sfc_point( x, x = 1, y = 2, z = 3  )
  res <- sfheaders:::rcpp_sfc_to_df( sfc )

  expect_true( ncol( res ) == 5 )
  expect_true( "z" %in% names(res) )
  expect_false( "m" %in% names(res) )

  x <- matrix( c(1:16), ncol = 4 )
  x[1,1] <- 1.1
  sfc <- sfc_point( x, x = 1, y = 2, z = 3, m = 4 )
  res <- sfheaders:::rcpp_sfc_to_df( sfc )

  expect_true( ncol( res ) == 6 )
  expect_true( "z" %in% names(res) )
  expect_true( "m" %in% names(res) )


  x <- matrix( c(1:16), ncol = 4 )
  sfc <- sfc_multipoint( x, x = 1, y = 2, z = 3  )
  res <- sfheaders:::rcpp_sfc_to_df( sfc )

  expect_true( ncol( res ) == 5 )
  expect_true( "z" %in% names(res) )
  expect_false( "m" %in% names(res) )

  x <- matrix( c(1:16), ncol = 4 )
  sfc <- sfc_multipoint( x, x = 1, y = 2, z = 3, m = 4 )
  res <- sfheaders:::rcpp_sfc_to_df( sfc )

  expect_true( ncol( res ) == 6 )
  expect_true( "z" %in% names(res) )
  expect_true( "m" %in% names(res) )


  x <- matrix( c(1:16), ncol = 4 )
  sfc <- sfc_linestring( x, x = 1, y = 2, z = 3  )
  res <- sfheaders:::rcpp_sfc_to_df( sfc )

  expect_true( ncol( res ) == 5 )
  expect_true( "z" %in% names(res) )
  expect_false( "m" %in% names(res) )

  x <- matrix( c(1:16), ncol = 4 )
  sfc <- sfc_linestring( x, x = 1, y = 2, z = 3, m = 4 )
  res <- sfheaders:::rcpp_sfc_to_df( sfc )

  expect_true( ncol( res ) == 6 )
  expect_true( "z" %in% names(res) )
  expect_true( "m" %in% names(res) )


  x <- matrix( c(1:16), ncol = 4 )
  sfc <- sfc_multilinestring( x, x = 1, y = 2, z = 3  )
  res <- sfheaders:::rcpp_sfc_to_df( sfc )

  expect_true( ncol( res ) == 6 )
  expect_true( "z" %in% names(res) )
  expect_false( "m" %in% names(res) )

  x <- matrix( c(1:16), ncol = 4 )
  sfc <- sfc_multilinestring( x, x = 1, y = 2, z = 3, m = 4 )
  res <- sfheaders:::rcpp_sfc_to_df( sfc )

  expect_true( ncol( res ) == 7 )
  expect_true( "z" %in% names(res) )
  expect_true( "m" %in% names(res) )

  x <- matrix( c(1:16), ncol = 4 )
  sfc <- sfc_polygon( x, x = 1, y = 2, z = 3  )
  res <- sfheaders:::rcpp_sfc_to_df( sfc )

  expect_true( ncol( res ) == 6 )
  expect_true( "z" %in% names(res) )
  expect_false( "m" %in% names(res) )

  x <- matrix( c(1:16), ncol = 4 )
  sfc <- sfc_polygon( x, x = 1, y = 2, z = 3, m = 4 )
  res <- sfheaders:::rcpp_sfc_to_df( sfc )

  expect_true( ncol( res ) == 7 )
  expect_true( "z" %in% names(res) )
  expect_true( "m" %in% names(res) )


  x <- matrix( c(1:16), ncol = 4 )
  sfc <- sfc_multipolygon( x, x = 1, y = 2, z = 3  )
  res <- sfheaders:::rcpp_sfc_to_df( sfc )

  expect_true( ncol( res ) == 7 )
  expect_true( "z" %in% names(res) )
  expect_false( "m" %in% names(res) )

  x <- matrix( c(1:16), ncol = 4 )
  sfc <- sfc_multipolygon( x, x = 1, y = 2, z = 3, m = 4 )
  res <- sfheaders:::rcpp_sfc_to_df( sfc )

  expect_true( ncol( res ) == 8 )
  expect_true( "z" %in% names(res) )
  expect_true( "m" %in% names(res) )

})
