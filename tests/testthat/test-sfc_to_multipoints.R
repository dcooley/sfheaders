context( "sfc_multipoints " )

test_that("various objects converted to sfc_MULTIPOINT objects",{

  m <- matrix()
  expect_error( sfheaders:::rcpp_sfc_multipoint( m, NULL, NULL ), "sfheaders - lines need to be matrices or data.frames")

  m <- matrix(c(0,0), ncol = 2)
  res <- sfheaders:::rcpp_sfc_multipoint( m, NULL, NULL )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOINT", "sfc") )

  m <- matrix(c(0,0,1,1), ncol = 2, byrow = T)
  res <- sfheaders:::rcpp_sfc_multipoint( m, NULL, NULL )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOINT", "sfc") )

  m <- matrix(c(0,0,0,0,1,1), ncol = 3, byrow = T)
  res <- sfheaders:::rcpp_sfc_multipoint( m, NULL, NULL )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOINT", "sfc") )

  m <- matrix(c(0,0,1,1), ncol = 2, byrow = T)
  res <- sfheaders:::rcpp_sfc_multipoint( m, c(0,1), NULL )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOINT", "sfc") )

  m <- matrix(c(0,0,1,1), ncol = 2, byrow = T)
  expect_error( sfheaders:::rcpp_sfc_multipoint( m, NULL, c(0) ), "sfheaders - different column types detected")

  m <- matrix(c(0,0,0,0,1,1,1,1,1), ncol = 3, byrow = T)
  res <- sfheaders:::rcpp_sfc_multipoint( m, c(1,2), c(0) )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOINT", "sfc") )


  df <- data.frame(x = 1, y = 1)
  res <- sfheaders:::rcpp_sfc_multipoint(df, NULL, NULL)
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOINT", "sfc") )

  df <- data.frame(id = 1, x = 1, y = 1)
  res <- sfheaders:::rcpp_sfc_multipoint(df, c("x","y"), c("id") )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOINT", "sfc") )

  df <- data.frame(id = 1:2, x = 1:2, y = 1:2)
  res <- sfheaders:::rcpp_sfc_multipoint(df, c("x","y"), c("id") )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOINT", "sfc") )

  df <- data.frame(id = 1, x = 1:2, y = 1:2)
  res <- sfheaders:::rcpp_sfc_multipoint(df, c("x","y"), c("id") )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOINT", "sfc") )

})
