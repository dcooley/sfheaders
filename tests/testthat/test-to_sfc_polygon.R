context("sfc_POLYGON")

test_that("sfc_polygon works", {

  df <- data.frame(
    p_id = c(1,1,1,1,2,2,2,2)
    , l_id = c(1,1,1,1,1,1,1,1)
    , x = c(1,2,3,1,4,5,6,4)
    , y = c(1,2,3,1,4,5,6,4)
  )

  res <- sfheaders:::rcpp_sfc_polygon( df, c(2,3), c(0), c(1))

})
