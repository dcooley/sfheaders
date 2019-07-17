context("sfg_to_multipolygon")

test_that("sfg multipolygon",{

  l1 <- matrix(c(0,0,0,1,1,1,1,0,0,0), ncol = 2, byrow = T)
  l2 <- matrix(c(2,2,2,5,5,5,5,2,2,2), ncol = 2, byrow = T)
  l3 <- matrix(c(3,3,3,4,4,4,4,3,3,3), ncol = 2, byrow = T)
  l1 <- cbind(1, l1)
  l2 <- cbind(1, l2)
  l3 <- cbind(2, l3)
  l1 <- cbind(1, l1)
  l2 <- cbind(2, l2)
  l3 <- cbind(2, l3)

  m <- rbind(l1, l2)
  m <- rbind(m, l3)

  mp <- sfheaders:::rcpp_sfg_multipolygon( m, c(2,3), polygon_id = 0, line_id = 1)
  res <- attr( mp, "class" )
  expect_equal( res, c("XY", "MULTIPOLYGON", "sfg") )
  r_res <- sfg_multipolygon(mp)

  expect_equal( mp[[1]][[1]], r_res[[1]][[1]] )
  expect_equal( mp[[2]][[1]], r_res[[2]][[1]] )
  expect_equal( mp[[2]][[2]], r_res[[2]][[2]] )

  expect_true( all( lengths( mp ) == lengths( r_res ) ) )

})
