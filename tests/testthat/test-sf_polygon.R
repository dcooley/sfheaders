context("sf_polygon")

test_that("various objects converted to sf_polygon",{

  m <- matrix(1:4, ncol = 2)
  res <- sfheaders:::rcpp_sf_polygon(m, c(0L,1L), NULL, NULL, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(c(1.2,3,4,5), ncol = 2)
  res <- sfheaders:::rcpp_sf_polygon(m, c(0L,1L), NULL, NULL, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:4, ncol = 2)
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sf_polygon(df, c(0L,1L), NULL, NULL, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:4, ncol = 2)
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sf_polygon(df, c("V1","V2"), NULL, NULL, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(c(1.2,3,4,5), ncol = 2)
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sf_polygon(df, c("V1","V2"), NULL, NULL, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )


  m <- matrix(1:4, ncol = 2)
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sf_polygon(df, c("V1","V2"), NULL, NULL, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  res <- sfheaders:::rcpp_sf_polygon(m, c(0L,1L), 2L, NULL, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1L,1L,2L,2L))
  res <- sfheaders:::rcpp_sf_polygon(m, c(0L,1L), 2L, NULL, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  res <- sfheaders:::rcpp_sf_polygon(m, c(0L,1L), 2L, NULL, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1))
  res <- sfheaders:::rcpp_sf_polygon(m, c(0L,1L), 2L, NULL, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sf_polygon(df, c(0L,1L), 2L, NULL, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1L,1L,2L,2L) )
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sf_polygon(m, c("V1","V2"), NULL, NULL, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2) )
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sf_polygon(m, c("V1","V2"), NULL, NULL, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(c(1.2,2:8), ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sf_polygon(df, c("V1","V2"), NULL, NULL, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2) )
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sf_polygon(m, c("V1","V2"), "V3", NULL, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1L,1L,2L,2L) )
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sf_polygon(m, c("V1","V2"), "V3", "V3", xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2) )
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sf_polygon(m, c("V1","V2"), "V3", "V3", xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(c(1.2,2:8), ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sf_polygon(df, c("V1","V2"), "V3", NULL, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sf_polygon(df, c("V1","V2"), c("V3"), NULL, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sf_polygon(df, c("V1","V2"), c("V3"), NULL, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sf_polygon(df, c(0L,1L), 2L, NULL, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1L))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sf_polygon(df, c(0L,1L), NULL, 2L, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sf_polygon(df, c("V1","V2"), NULL, "V3", xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1))
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sf_polygon(m, c("V1","V2"), NULL, "V3", xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )
})


test_that("polygons are closed and list-column properties follow the same structure as geometires, and first row is repeated where closed",{

  df <- data.frame(
    multi_id = c(1,1,1,1, 1,1,1,1,1, 1,1,1,1)
    , poly_id = c(1,1,1,1, 1,1,1,1,1, 2,2,2,2)
    , line_id = c(1,1,1,1, 2,2,2,2,2, 1,1,1,1)
    , x = c(0,0,1,1, 2,2,3,3,2, 10,10,12,12)
    , y = c(0,1,1,0, 2,3,3,2,2, 10,12,12,10)
    , z = c(1,2,2,2, 2,3,3,3,2, 3,2,2,3)
    , prop = letters[1:13]
  )

  ## In this test:
  ## - polygon 1 has two rings, the first needs closing, the 2nd is OK.
  ## - polygon 2 has one ring, it needs closing

  sf_poly <- sfheaders::sf_polygon(
    obj = df
    , x = "x"
    , y = "y"
    , z = "z"
    , polygon_id = "poly_id"
    , linestring_id = "line_id"
    , list_columns = "prop"
    , keep = T
    , close = TRUE
  )

  expect_true( attr(sf_poly[1, ]$geometry[[1]][[1]], "closed" ) == "has_been_closed" )
  expect_true( is.null( attr(sf_poly[1, ]$geometry[[1]][[2]], "closed" ) ) )
  expect_true( attr(sf_poly[2, ]$geometry[[1]][[1]], "closed" ) == "has_been_closed" )

  expect_equal( sf_poly[1, ]$prop[[1]][[1]], c( letters[1:4], letters[1] ) )
  expect_equal( sf_poly[1, ]$prop[[1]][[2]], letters[5:9] )
  expect_equal( sf_poly[2, ]$prop[[1]][[1]], c( letters[10:13], letters[10] ) )

  ## In this test we're not closing the polygon
  sf_poly <- sfheaders::sf_polygon(
    obj = df
    , x = "x"
    , y = "y"
    , z = "z"
    , polygon_id = "poly_id"
    , linestring_id = "line_id"
    , list_columns = "prop"
    , keep = T
    , close = FALSE
  )

  expect_true( is.null( attr(sf_poly[1, ]$geometry[[1]][[1]], "closed" ) ) )
  expect_true( is.null( attr(sf_poly[1, ]$geometry[[1]][[2]], "closed" ) ) )
  expect_true( is.null( attr(sf_poly[2, ]$geometry[[1]][[1]], "closed" ) ) )

  expect_equal( sf_poly[1, ]$prop[[1]][[1]], letters[1:4] )
  expect_equal( sf_poly[1, ]$prop[[1]][[2]], letters[5:9] )
  expect_equal( sf_poly[2, ]$prop[[1]][[1]], letters[10:13] )

  ## In this test the rings of each polygon are the same as for sf_poly
  ## but they are all contained inside a MULTIPOLYGON
  sf_multi <- sfheaders::sf_multipolygon(
    obj = df
    , x = "x"
    , y = "y"
    , z = "z"
    , multipolygon_id = "multi_id"
    , polygon_id = "poly_id"
    , linestring_id = "line_id"
    , list_columns = "prop"
    , keep = T
    , close = TRUE
  )

  expect_true( attr(sf_multi[1, ]$geometry[[1]][[1]][[1]], "closed" ) == "has_been_closed" )
  expect_true( is.null( attr(sf_multi[1, ]$geometry[[1]][[1]][[2]], "closed" ) ) )
  expect_true( attr(sf_multi[1, ]$geometry[[1]][[2]][[1]], "closed" ) == "has_been_closed" )

  expect_equal( sf_multi[1, ]$prop[[1]][[1]][[1]], c( letters[1:4], letters[1] ) )
  expect_equal( sf_multi[1, ]$prop[[1]][[1]][[2]], letters[5:9] )
  expect_equal( sf_multi[1, ]$prop[[1]][[2]][[1]], c( letters[10:13], letters[10] ) )


})

