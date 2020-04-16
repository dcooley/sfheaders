context("sf multipoint")

test_that("various objects converted to sf_multipoint",{

  m <- matrix(1:4, ncol = 2)
  m <- cbind(c(1L,1L), m)
  res <- sfheaders:::rcpp_sf_multipoint(m, c(1L,2L), 0L, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:4, ncol = 2)
  res <- sfheaders:::rcpp_sf_multipoint(m, c(0,1), NULL, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(c(1.2,3,4,5), ncol = 2)
  res <- sfheaders:::rcpp_sf_multipoint(m, c(0,1), NULL, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:4, ncol = 2)
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sf_multipoint(df, c(0,1), NULL, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:4, ncol = 2)
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sf_multipoint(df, c("V1","V2"), NULL, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(c(1.2,3,4,5), ncol = 2)
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sf_multipoint(df, c("V1","V2"), NULL, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )


  m <- matrix(1:4, ncol = 2)
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sf_multipoint(df, c("V1","V2"), NULL, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  res <- sfheaders:::rcpp_sf_multipoint(m, c(0,1), 2, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1L,1L,2L,2L))
  res <- sfheaders:::rcpp_sf_multipoint(m, c(0L,1L), 2L, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  res <- sfheaders:::rcpp_sf_multipoint(m, c(0L,1L), 2L, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1))
  res <- sfheaders:::rcpp_sf_multipoint(m, c(0L,1L), 2L, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sf_multipoint(df, c(0,1), 2, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1L,1L,2L,2L) )
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sf_multipoint(m, c("V1","V2"), NULL, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2) )
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sf_multipoint(m, c("V1","V2"), NULL, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(c(1.2,2:8), ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sf_multipoint(df, c("V1","V2"), NULL, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1L:4L, ncol = 2)
  m <- cbind(c(1L,1L), m)
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sf_multipoint(m, c("V1","V2"), "V3", TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2) )
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sf_multipoint(m, c("V1","V2"), "V3", TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(c(1.2,2:8), ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sf_multipoint(df, c("V1","V2"), "V3", TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sf_multipoint(df, c("V1","V2"), c("V3"), TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sf_multipoint(df, c("V1","V2"), c("V3"), TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )


  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sf_multipoint(df, c(0L,1L), 2L, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

})
