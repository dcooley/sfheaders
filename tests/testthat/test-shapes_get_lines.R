context("get_lines")

test_that("lines lists returend",{

  ids <- c( rep(1,5), rep(2,3), rep(3,6) )
  x <- data.frame(
    id = ids
    , x = seq(1, length(ids))
    , y = seq(length(ids), 1)
  )

  res <- sfheaders:::rcpp_get_list_mat( x, c("x","y"), "id")
  expect_true( is.list( res ) )
  expect_true( is.matrix( res[[1]] ) )
  expect_true( is.matrix( res[[2]] ) )
  expect_true( is.matrix( res[[3]] ) )
  m1 <- res[[1]]; m2 <- res[[2]]; m3 <- res[[3]]

  expect_equal( m1[,1], 1:5 )
  expect_equal( m1[,2], 14:10 )
  expect_equal( m2[,1], 6:8 )
  expect_equal( m2[,2], 9:7 )
  expect_equal( m3[,1], 9:14 )
  expect_equal( m3[,2], 6:1 )

  res <- sfheaders:::rcpp_get_list_mat( x, c(2,1), 0)
  expect_true( is.list( res ) )
  expect_true( is.matrix( res[[1]] ) )
  expect_true( is.matrix( res[[2]] ) )
  expect_true( is.matrix( res[[3]] ) )
  m1 <- res[[1]]; m2 <- res[[2]]; m3 <- res[[3]]

  expect_equal( m1[,2], 1:5 )
  expect_equal( m1[,1], 14:10 )
  expect_equal( m2[,2], 6:8 )
  expect_equal( m2[,1], 9:7 )
  expect_equal( m3[,2], 9:14 )
  expect_equal( m3[,1], 6:1 )

  ids <- c( rep(1,5), rep(2,3), rep(3,6) )
  x <- data.frame(
    id = ids
    , x = seq(1, length(ids))
    , y = seq(length(ids), 1)
  )
  x <- as.matrix( x )

  res <- sfheaders:::rcpp_get_list_mat( x, c("x","y"), "id")
  expect_true( is.list( res ) )
  expect_true( is.matrix( res[[1]] ) )
  expect_true( is.matrix( res[[2]] ) )
  expect_true( is.matrix( res[[3]] ) )
  m1 <- res[[1]]; m2 <- res[[2]]; m3 <- res[[3]]

  expect_equal( m1[,1], 1:5 )
  expect_equal( m1[,2], 14:10 )
  expect_equal( m2[,1], 6:8 )
  expect_equal( m2[,2], 9:7 )
  expect_equal( m3[,1], 9:14 )
  expect_equal( m3[,2], 6:1 )

  res <- sfheaders:::rcpp_get_list_mat( x, c(2,1), 0)
  expect_true( is.list( res ) )
  expect_true( is.matrix( res[[1]] ) )
  expect_true( is.matrix( res[[2]] ) )
  expect_true( is.matrix( res[[3]] ) )
  m1 <- res[[1]]; m2 <- res[[2]]; m3 <- res[[3]]

  expect_equal( m1[,2], 1:5 )
  expect_equal( m1[,1], 14:10 )
  expect_equal( m2[,2], 6:8 )
  expect_equal( m2[,1], 9:7 )
  expect_equal( m3[,2], 9:14 )
  expect_equal( m3[,1], 6:1 )

  ids <- c( rep(1L,5L), rep(2L,3L), rep(3L,6L) )
  x <- data.frame(
    id = ids
    , x = seq(1L, length(ids))
    , y = seq(length(ids), 1L)
  )

  x <- as.matrix( x )
  res <- sfheaders:::rcpp_get_list_mat( x, c("x","y"), "id")
  expect_true( is.list( res ) )
  expect_true( is.matrix( res[[1]] ) )
  expect_true( is.matrix( res[[2]] ) )
  expect_true( is.matrix( res[[3]] ) )
  m1 <- res[[1]]; m2 <- res[[2]]; m3 <- res[[3]]

  expect_equal( m1[,1], 1:5 )
  expect_equal( m1[,2], 14:10 )
  expect_equal( m2[,1], 6:8 )
  expect_equal( m2[,2], 9:7 )
  expect_equal( m3[,1], 9:14 )
  expect_equal( m3[,2], 6:1 )

  res <- sfheaders:::rcpp_get_list_mat( x, c(2,1), 0)
  expect_true( is.list( res ) )
  expect_true( is.matrix( res[[1]] ) )
  expect_true( is.matrix( res[[2]] ) )
  expect_true( is.matrix( res[[3]] ) )
  m1 <- res[[1]]; m2 <- res[[2]]; m3 <- res[[3]]

  expect_equal( m1[,2], 1:5 )
  expect_equal( m1[,1], 14:10 )
  expect_equal( m2[,2], 6:8 )
  expect_equal( m2[,1], 9:7 )
  expect_equal( m3[,2], 9:14 )
  expect_equal( m3[,1], 6:1 )


})
