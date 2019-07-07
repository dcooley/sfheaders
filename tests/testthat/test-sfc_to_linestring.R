context("sfc_linestring")

test_that("various objects converted to sfc_LINESTRING",{

  expect_error(sfheaders:::rcpp_sfc_linestring(1:3, NULL, NULL), "sfheaders - lines need to be matrices or data.frames")

  m <- matrix(1:4, ncol = 2)
  res <- sfheaders:::rcpp_sfc_linestring(m, NULL, NULL)
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )


  m <- matrix(1:4, ncol = 2)
  res <- sfheaders:::rcpp_sfc_linestring(m, c(0,1), NULL)
  expect_equal( attr( res, "class" ), c("sfc_LINESTRING", "sfc") )

  m <- matrix(1:4, ncol = 2)
  expect_error( sfheaders:::rcpp_sfc_linestring(m, NULL, 0), "sfheaders - incorrect number of geometry columns")

})
