context("errorhandling")


test_that("errors and crashes are handled and fixed",{

  ## not supplying enough columns
  df <- data.frame(x = 1:5)
  expect_error( sfheaders::sf_linestring(obj = df, x = "x", y = "y"), "sfheaders - number of columns requested is greater than those available" )
  expect_error( sfheaders::sf_linestring(obj = df, x = "x", y = 2 ), "sfheaders - number of columns requested is greater than those available" )
  expect_error( sfheaders::sf_linestring(obj = df, x = 1, y = 2 ), 'sfheaders - number of columns requested is greater than those available' )

  df <- data.frame(x = 1:5, y = 1:5)
  expect_error( sfheaders::sf_linestring(obj = df, x = 3, y = 2 ), 'sfheaders - invalid geometry column index' )

  m <- matrix(1:2, ncol = 2)
  expect_error( sfheaders::sf_linestring(obj = m, x = 3, y = 2 ), 'sfheaders - invalid geometry column index' )


  m <- matrix(1)
  expect_error( sfheaders::sf_linestring(obj = m, x = "x", y = "y"), 'sfheaders - number of columns requested is greater than those available' )
  expect_error( sfheaders::sf_linestring(obj = m, x = "x", y = 2 ), 'sfheaders - number of columns requested is greater than those available' )
  expect_error( sfheaders::sf_linestring(obj = m, x = 1, y = 2 ), 'sfheaders - number of columns requested is greater than those available' )

  ## indexing incorrect id columns
  df <- data.frame(x = 1, y = 2 )
  expect_error( sfheaders:::rcpp_sfc_multipoint(df, c(0L,1L), 2L, ""), "sfheaders - id column index doesn't exist")
  expect_error( sfheaders:::rcpp_sfc_linestring(df, c(0L,1L), 2L, ""), "sfheaders - id column index doesn't exist")
  expect_error( sfheaders:::rcpp_sfc_multilinestring(df, c(0L,1L), 2L, NULL, "" ), "sfheaders - id column index doesn't exist")
  expect_error( sfheaders:::rcpp_sfc_multilinestring(df, c(0L,1L), NULL, 2L, "" ), "sfheaders - id column index doesn't exist")
  expect_error( sfheaders:::rcpp_sfc_multilinestring(df, c(0L,1L), 2L, 2L, ""), "sfheaders - id column index doesn't exist")

  expect_error( sfheaders:::rcpp_sfc_polygon(df, c(0L,1L), 2L, NULL, FALSE, "" ), "sfheaders - id column index doesn't exist")
  expect_error( sfheaders:::rcpp_sfc_polygon(df, c(0L,1L), NULL, 2L, FALSE, "" ), "sfheaders - id column index doesn't exist")
  expect_error( sfheaders:::rcpp_sfc_polygon(df, c(0L,1L), 2L, 2L, FALSE, "" ), "sfheaders - id column index doesn't exist")

  expect_error( sfheaders:::rcpp_sfc_multipolygon(df, c(0L,1L), 2L, NULL, NULL, FALSE, "" ), "sfheaders - id column index doesn't exist")
  expect_error( sfheaders:::rcpp_sfc_multipolygon(df, c(0L,1L), NULL, 2L, NULL, FALSE, "" ), "sfheaders - id column index doesn't exist")
  expect_error( sfheaders:::rcpp_sfc_multipolygon(df, c(0L,1L), NULL, NULL, 2L, FALSE, "" ), "sfheaders - id column index doesn't exist")

  expect_error( sfheaders:::rcpp_sfc_multipolygon(df, c(0L,1L), 2L, 2L, NULL, FALSE, "" ), "sfheaders - id column index doesn't exist")
  expect_error( sfheaders:::rcpp_sfc_multipolygon(df, c(0L,1L), NULL, 2L, 2L, FALSE, "" ), "sfheaders - id column index doesn't exist")
  expect_error( sfheaders:::rcpp_sfc_multipolygon(df, c(0L,1L), 2L, NULL, 2L, FALSE, "" ), "sfheaders - id column index doesn't exist")

  expect_error( sfheaders:::rcpp_sfc_multipolygon(df, c(0L,1L), 2L, 2L, 2L, FALSE, "" ), "sfheaders - id column index doesn't exist")

  m <- matrix( 1:2, ncol = 2)
  expect_error( sfheaders:::rcpp_sfc_multipoint(m, c(0L,1L), 2L, ""), "sfheaders - id column index doesn't exist")
  expect_error( sfheaders:::rcpp_sfc_linestring(m, c(0L,1L), 2L, ""), "sfheaders - id column index doesn't exist")
  expect_error( sfheaders:::rcpp_sfc_multilinestring(m, c(0L,1L), 2L, NULL, "" ), "sfheaders - id column index doesn't exist")
  expect_error( sfheaders:::rcpp_sfc_multilinestring(m, c(0L,1L), NULL, 2L, "" ), "sfheaders - id column index doesn't exist")
  expect_error( sfheaders:::rcpp_sfc_multilinestring(m, c(0L,1L), 2L, 2L, "" ), "sfheaders - id column index doesn't exist")

  expect_error( sfheaders:::rcpp_sfc_polygon(m, c(0L,1L), 2L, NULL, FALSE, "" ), "sfheaders - id column index doesn't exist")
  expect_error( sfheaders:::rcpp_sfc_polygon(m, c(0L,1L), NULL, 2L, FALSE, "" ), "sfheaders - id column index doesn't exist")
  expect_error( sfheaders:::rcpp_sfc_polygon(m, c(0L,1L), 2L, 2L, FALSE, "" ), "sfheaders - id column index doesn't exist")

  expect_error( sfheaders:::rcpp_sfc_multipolygon(m, c(0L,1L), 2L, NULL, NULL, FALSE, "" ), "sfheaders - id column index doesn't exist")
  expect_error( sfheaders:::rcpp_sfc_multipolygon(m, c(0L,1L), NULL, 2L, NULL, FALSE, "" ), "sfheaders - id column index doesn't exist")
  expect_error( sfheaders:::rcpp_sfc_multipolygon(m, c(0L,1L), NULL, NULL, 2L, FALSE, "" ), "sfheaders - id column index doesn't exist")

  expect_error( sfheaders:::rcpp_sfc_multipolygon(m, c(0L,1L), 2L, 2L, NULL, FALSE, "" ), "sfheaders - id column index doesn't exist")
  expect_error( sfheaders:::rcpp_sfc_multipolygon(m, c(0L,1L), NULL, 2L, 2L, FALSE, "" ), "sfheaders - id column index doesn't exist")
  expect_error( sfheaders:::rcpp_sfc_multipolygon(m, c(0L,1L), 2L, NULL, 2L, FALSE, "" ), "sfheaders - id column index doesn't exist")

  expect_error( sfheaders:::rcpp_sfc_multipolygon(m, c(0L,1L), 2L, 2L, 2L, FALSE, "" ), "sfheaders - id column index doesn't exist")


  df <- data.frame(x = 1, y = 2 )
  expect_error( sfheaders:::rcpp_sfg_multilinestring(m, c(0L,1L), 2L, "" ), "sfheaders - id column index doesn't exist")

  expect_error( sfheaders:::rcpp_sfg_polygon(m, c(0L,1L), 2L, FALSE, "" ), "sfheaders - id column index doesn't exist")

  expect_error( sfheaders:::rcpp_sfg_multipolygon(m, c(0L,1L), 2L, NULL, FALSE, "" ), "sfheaders - id column index doesn't exist")
  expect_error( sfheaders:::rcpp_sfg_multipolygon(m, c(0L,1L), NULL, 2L, FALSE, "" ), "sfheaders - id column index doesn't exist")
  expect_error( sfheaders:::rcpp_sfg_multipolygon(m, c(0L,1L), 2L, 2L, FALSE, "" ), "sfheaders - id column index doesn't exist")

  m <- matrix( 1:2, ncol = 2)
  expect_error( sfheaders:::rcpp_sfg_multilinestring(m, c(0L,1L), 2L, "" ), "sfheaders - id column index doesn't exist")

  expect_error( sfheaders:::rcpp_sfg_polygon(m, c(0L,1L), 2L, FALSE, "" ), "sfheaders - id column index doesn't exist")

  expect_error( sfheaders:::rcpp_sfg_multipolygon(m, c(0L,1L), 2L, NULL, FALSE, "" ), "sfheaders - id column index doesn't exist")
  expect_error( sfheaders:::rcpp_sfg_multipolygon(m, c(0L,1L), NULL, 2L, FALSE, "" ), "sfheaders - id column index doesn't exist")
  expect_error( sfheaders:::rcpp_sfg_multipolygon(m, c(0L,1L), 2L, 2L, FALSE, "" ), "sfheaders - id column index doesn't exist")


})

test_that("single-row objects",{

  is_sf <- function(x) "sf" %in% attr(x, "class")

  df <- data.frame(x =1:3, y =2:4)
  expect_true( is_sf( sfheaders::sf_point( df ) ) )
  expect_true( is_sf( sfheaders::sf_multipoint( df ) ) )
  expect_true( is_sf( sfheaders::sf_linestring( df ) ) )
  expect_true( is_sf( sfheaders::sf_multilinestring( df ) ) )
  expect_true( is_sf( sfheaders::sf_polygon( df ) ) )
  expect_true( is_sf( sfheaders::sf_multipolygon( df ) ) )

  m <- matrix(1:6, ncol = 2)
  expect_true( is_sf( sfheaders::sf_point( m[1, ] ) ) )
  expect_true( is_sf( sfheaders::sf_multipoint( m ) ) )
  expect_true( is_sf( sfheaders::sf_linestring( m ) ) )
  expect_true( is_sf( sfheaders::sf_multilinestring( m ) ) )
  expect_true( is_sf( sfheaders::sf_polygon( m ) ) )
  expect_true( is_sf( sfheaders::sf_multipolygon( m ) ) )

  is_sfc <- function(x) "sfc" %in% attr( x, "class" )

  df <- data.frame(x =1:3, y =2:4)
  expect_true( is_sfc( sfheaders::sfc_point( df ) ) )
  expect_true( is_sfc( sfheaders::sfc_multipoint( df ) ) )
  expect_true( is_sfc( sfheaders::sfc_linestring( df ) ) )
  expect_true( is_sfc( sfheaders::sfc_multilinestring( df ) ) )
  expect_true( is_sfc( sfheaders::sfc_polygon( df ) ) )
  expect_true( is_sfc( sfheaders::sfc_multipolygon( df ) ) )

  m <- matrix(1:6, ncol = 2)
  expect_true( is_sfc( sfheaders::sfc_point( m ) ) )
  expect_true( is_sfc( sfheaders::sfc_multipoint( m ) ) )
  expect_true( is_sfc( sfheaders::sfc_linestring( m ) ) )
  expect_true( is_sfc( sfheaders::sfc_multilinestring( m ) ) )
  expect_true( is_sfc( sfheaders::sfc_polygon( m ) ) )
  expect_true( is_sfc( sfheaders::sfc_multipolygon( m ) ) )

  is_sfg <- function(x) "sfg" %in% attr( x, "class" )

  df <- data.frame(x =1:3, y =2:4)
  expect_true( is_sfg( sfheaders::sfg_point( df[1,] ) ) )
  expect_true( is_sfg( sfheaders::sfg_multipoint( df ) ) )
  expect_true( is_sfg( sfheaders::sfg_linestring( df ) ) )
  expect_true( is_sfg( sfheaders::sfg_multilinestring( df ) ) )
  expect_true( is_sfg( sfheaders::sfg_polygon( df ) ) )
  expect_true( is_sfg( sfheaders::sfg_multipolygon( df ) ) )

  m <- matrix(1:6, ncol = 2)
  expect_true( is_sfg( sfheaders::sfg_point( m[1,] ) ) )
  expect_true( is_sfg( sfheaders::sfg_multipoint( m ) ) )
  expect_true( is_sfg( sfheaders::sfg_linestring( m ) ) )
  expect_true( is_sfg( sfheaders::sfg_multilinestring( m ) ) )
  expect_true( is_sfg( sfheaders::sfg_polygon( m ) ) )
  expect_true( is_sfg( sfheaders::sfg_multipolygon( m ) ) )

})


test_that("0-row & empty objects",{

  is_sf <- function(x) "sf" %in% attr(x, "class")

  df <- data.frame()
  expect_error( sfheaders::sf_point( df ) )
  expect_error( sfheaders::sf_multipoint( df ) )
  expect_error( sfheaders::sf_linestring( df ) )
  expect_error( sfheaders::sf_multilinestring( df ) )
  expect_error( sfheaders::sf_polygon( df ) )
  expect_error( sfheaders::sf_multipolygon( df ) )

  m <- matrix()
  expect_error( sfheaders::sf_point( m ) )
  expect_error( sfheaders::sf_multipoint( m ) )
  expect_error( sfheaders::sf_linestring( m ) )
  expect_error( sfheaders::sf_multilinestring( m ) )
  expect_error( sfheaders::sf_polygon( m ) )
  expect_error( sfheaders::sf_multipolygon( m ) )


  df <- data.frame()
  expect_error( sfheaders::sfc_point( df ) )
  expect_error( sfheaders::sfc_multipoint( df ) )
  expect_error( sfheaders::sfc_linestring( df ) )
  expect_error( sfheaders::sfc_multilinestring( df ) )
  expect_error( sfheaders::sfc_polygon( df ) )
  expect_error( sfheaders::sfc_multipolygon( df ) )

  m <- matrix()
  expect_error( sfheaders::sfc_point( m ) )
  expect_error( sfheaders::sfc_multipoint( m ) )
  expect_error( sfheaders::sfc_linestring( m ) )
  expect_error( sfheaders::sfc_multilinestring( m ) )
  expect_error( sfheaders::sfc_polygon( m ) )
  expect_error( sfheaders::sfc_multipolygon( m ) )

  df <- data.frame()
  expect_error( sfheaders::sfg_point( df ) )
  expect_error( sfheaders::sfg_multipoint( df ) )
  expect_error( sfheaders::sfg_linestring( df ) )
  expect_error( sfheaders::sfg_multilinestring( df ) )
  expect_error( sfheaders::sfg_polygon( df ) )
  expect_error( sfheaders::sfg_multipolygon( df ) )

  m <- matrix()
  expect_error( sfheaders::sfg_point( m ) )
  expect_error( sfheaders::sfg_multipoint( m ) )
  expect_error( sfheaders::sfg_linestring( m ) )
  expect_error( sfheaders::sfg_multilinestring( m ) )
  expect_error( sfheaders::sfg_polygon( m ) )
  expect_error( sfheaders::sfg_multipolygon( m ) )

})

test_that("other misc errors are caught",{

  x <- data.frame( x = c(0,0), y = c(0,0) )
  expect_error( sfheaders:::rcpp_sfg_linestring( x, c(1L, 2L), "" ), "sfheaders - invalid column index")

})
