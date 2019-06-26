context("sfg_to_multipolygon")

testthat("sfg multipolygon",{

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

  res <- sfheaders:::rcpp_to_multipolygon( m, c(2,3), polygon_id = 0, line_id = 1)

})
