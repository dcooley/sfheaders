context("sf_multipolygon")

test_that("sf_multipolygon works on various objects",{

  m <- matrix(1:9, ncol = 3)
  res <- sfheaders:::rcpp_sf_multipolygon( m , c(0L, 1L), NULL, NULL, NULL, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:9, ncol = 3)
  m <- cbind(m, c(1L,1L,2L))
  res <- sfheaders:::rcpp_sf_multipolygon( m , c(0L, 1L), 3L, NULL, NULL, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:9, ncol = 3)
  m <- cbind(m, c(1L,1L,2L))
  m <- cbind(m, c(1L,1L,1L))
  res <- sfheaders:::rcpp_sf_multipolygon( m , c(0L, 1L), 3L, 4L, NULL, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:9, ncol = 3)
  m <- cbind(m, c(1L,1L,2L))
  m <- cbind(m, c(1L,1L,1L))
  m <- cbind(m, c(1L,1L,1L))
  res <- sfheaders:::rcpp_sf_multipolygon( m , c(0L, 1L), 3L, 4L, 5L, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:9, ncol = 3)
  m <- cbind(m, c(1,1,2))
  m <- cbind(m, c(1,1,1))
  m <- cbind(m, c(1,1,1))
  res <- sfheaders:::rcpp_sf_multipolygon( m , c(0L, 1L), 3L, 4L, 5L, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )


  m <- matrix(1:9, ncol = 3)
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sf_multipolygon( m , c("V1","V2"), NULL, NULL, NULL, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:9, ncol = 3)
  m <- cbind(m, c(1L,1L,2L))
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sf_multipolygon( m , c("V1","V2"), "V4", NULL, NULL, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:9, ncol = 3)
  m <- cbind(m, c(1,1,2))
  m <- cbind(m, c(1,1,1))
  m <- cbind(m, c(1,1,1))
  df <- as.data.frame(m)
  m <- as.matrix(df)
  res <- sfheaders:::rcpp_sf_multipolygon( m , c("V1", "V2"), "V3","V4","V5", xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  df <- data.frame(
    mp_id = c(1,1,1,1,2,2,2,2)
    , p_id = c(1,1,1,1,2,2,2,2)
    , l_id = c(1,1,1,1,1,1,1,1)
    , x = c(1.1,2,3,1,4,5,6,4)
    , y = c(1,2,3,1,4,5,6,4)
  )

  res <- sfheaders:::rcpp_sf_multipolygon( df, c(3L,4L), NULL, NULL, NULL, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  res <- sfheaders:::rcpp_sf_multipolygon( df, c(3L,4L), 0L, NULL, NULL, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  res <- sfheaders:::rcpp_sf_multipolygon( df, c(3L,4L), NULL, 1L, NULL, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  res <- sfheaders:::rcpp_sf_multipolygon( df, c(3L,4L), NULL, NULL, 2L, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sf_multipolygon( m, c(3L,4L), NULL, NULL, 2L, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  res <- sfheaders:::rcpp_sf_multipolygon( df, c(3L,4L), 0L, NULL, 2L, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  res <- sfheaders:::rcpp_sf_multipolygon( df, c(3L,4L), NULL, 1L, 2L, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sf_multipolygon( m, c(3L,4L), NULL, 1L, 2L, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  res <- sfheaders:::rcpp_sf_multipolygon( df, c(3L,4L), 0L, 1L, 2L, xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  res <- sfheaders:::rcpp_sf_multipolygon( df, c(3L,4L), c(2L), c(0L), c(1L), xyzm = "", keep = TRUE, close = FALSE )
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

})

test_that("issue 47 is fixed",{

  ## issue 47
  m <- matrix(1:9, ncol = 3)
  m <- cbind(m, c(1,1,2))
  m <- cbind(m, c(1,1,1))
  m <- cbind(m, c(1,1,1))
  expect_error(
    sfheaders:::rcpp_sf_multipolygon( m , c("V1", "V2"), "V3","V4","V5", xyzm = "", keep = TRUE, close = FALSE )
    , "geometries - could not find matrix names. Perhaps your matrix does not have names"
  )

})
