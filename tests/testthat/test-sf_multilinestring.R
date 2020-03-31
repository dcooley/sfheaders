context("sf_multilinestring")

test_that("various objects converted to sf_multilinestring",{

  m <- matrix(1:4, ncol = 2)
  res <- sfheaders:::rcpp_sf_multilinestring(m, c(0,1), NULL, NULL, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(c(1.2,3,4,5), ncol = 2)
  res <- sfheaders:::rcpp_sf_multilinestring(m, c(0,1), NULL, NULL, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:4, ncol = 2)
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sf_multilinestring(df, c(0,1), NULL, NULL, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:4, ncol = 2)
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sf_multilinestring(df, c("V1","V2"), NULL, NULL, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(c(1.2,3,4,5), ncol = 2)
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sf_multilinestring(df, c("V1","V2"), NULL, NULL, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )


  m <- matrix(1:4, ncol = 2)
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sf_multilinestring(df, c("V1","V2"), NULL, NULL, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  res <- sfheaders:::rcpp_sf_multilinestring(m, c(0,1), 2, NULL, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )


  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1L,1L,2L,2L))
  res <- sfheaders:::rcpp_sf_multilinestring(m, c(0L,1L), 2L, NULL, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  res <- sfheaders:::rcpp_sf_multilinestring(m, c(0L,1L), 2L, NULL, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1))
  res <- sfheaders:::rcpp_sf_multilinestring(m, c(0L,1L), 2L, NULL, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sf_multilinestring(df, c(0,1), 2, NULL, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1L,1L,2L,2L) )
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sf_multilinestring(m, c("V1","V2"), NULL, NULL, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2) )
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sf_multilinestring(m, c("V1","V2"), NULL, NULL, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(c(1.2,2:8), ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sf_multilinestring(df, c("V1","V2"), NULL, NULL, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2) )
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sf_multilinestring(m, c("V1","V2"), "V3", NULL, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1L,1L,2L,2L) )
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sf_multilinestring(m, c("V1","V2"), "V3", "V3", TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2) )
  df <- as.data.frame( m )
  m <- as.matrix( df )
  res <- sfheaders:::rcpp_sf_multilinestring(m, c("V1","V2"), "V3", "V3", TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(c(1.2,2:8), ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sf_multilinestring(df, c("V1","V2"), "V3", NULL, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:8, ncol = 2)
  m <- cbind(m, c(1,1,2,2))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sf_multilinestring(df, c("V1","V2"), c("V3"), NULL, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sf_multilinestring(df, c("V1","V2"), c("V3"), NULL, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )


  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sf_multilinestring(df, c(0L,1L), 2L, NULL, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1L))
  res <- sfheaders:::rcpp_sf_multilinestring(m, c(0L,1L), NULL, 2L, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1))
  res <- sfheaders:::rcpp_sf_multilinestring(m, c(0L,1L), NULL, 2L, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1L))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sf_multilinestring(df, c(0L,1L), NULL, 2L, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

  m <- matrix(1:2, ncol = 2)
  m <- cbind(m, c(1))
  df <- as.data.frame( m )
  res <- sfheaders:::rcpp_sf_multilinestring(df, c(0L,1L), NULL, 2L, TRUE, "")
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )

})
