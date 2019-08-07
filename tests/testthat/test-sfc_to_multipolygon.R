context("sfc_multipolygon")

test_that("sfc_multipolygon works after refactoring issue14",{

  is_multipolygon <- function(x) {
    y <- sapply( x, function(y) is.list( unclass( y ) ) )
    z <- sapply( x, function(y) attr( y, "class")[2] == "MULTIPOLYGON")
    return( all(y) & all(z))
  }

  df <- data.frame(
    mp_id = c(1,1,1,1,2,2,2,2)
    #, p_id = c(1,1,1,1,2,2,2,2)
    , l_id = c(1,1,1,1,1,1,1,1)
    , x = c(1,2,3,1,4,5,6,4)
    , y = c(1,2,3,1,4,5,6,4)
  )

  res <- sfheaders:::rcpp_sfc_multipolygon( df, NULL, NULL, NULL, NULL )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )

  df <- data.frame(
    mp_id = c(1,1,1,1,2,2,2,2)
    , p_id = c(1,1,1,1,2,2,2,2)
    , l_id = c(1,1,1,1,1,1,1,1)
    , x = c(1,2,3,1,4,5,6,4)
    , y = c(1,2,3,1,4,5,6,4)
  )

  res <- sfheaders:::rcpp_sfc_multipolygon( df, c(3,4), NULL, NULL, NULL )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )
  expect_true( length( res ) == 1 )

  res <- sfheaders:::rcpp_sfc_multipolygon( df, c(3,4), 0, NULL, NULL )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )
  expect_true( length( res ) == 2 )

  res <- sfheaders:::rcpp_sfc_multipolygon( df, c(3,4), NULL, 1, NULL )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )
  expect_true( length( res ) == 1 )

  res <- sfheaders:::rcpp_sfc_multipolygon( df, c(3,4), NULL, NULL, 2 )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )
  expect_true( length( res ) == 1 )

  res <- sfheaders:::rcpp_sfc_multipolygon( df, c(3,4), 0, NULL, 2 )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )
  expect_true( length( res ) == 2 )

  res <- sfheaders:::rcpp_sfc_multipolygon( df, c(3,4), NULL, 1, 2 )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )
  expect_true( length( res ) == 1 )

  res <- sfheaders:::rcpp_sfc_multipolygon( df, c(3,4), 0, 1, 2 )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )
  expect_true( length( res ) == 2 )

  res <- sfheaders:::rcpp_sfc_multipolygon( df, c(3,4), c(2), c(0), c(1))
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )
  expect_true( length( res ) == 1 )

})

test_that("data.frame with non-numeric id columns work",{


  is_multipolygon <- function(x) {
    y <- sapply( x, function(y) is.list( unclass( y ) ) )
    z <- sapply( x, function(y) attr( y, "class")[2] == "MULTIPOLYGON")
    return( all(y) & all(z))
  }

  df <- data.frame(
    p_id = letters[c(1,1,1,1,2,2,2,2)]
    , l_id = c(1,1,1,1,1,1,1,1)
    , x = c(1,2,3,1,4,5,6,4)
    , y = c(1,2,3,1,4,5,6,4)
    , stringsAsFactors = F
  )

  res <- sfheaders::sfc_multipolygon(
    obj = df
    , x = "x"
    , y = "y"
    , multipolygon_id = "p_id"
  )
  expect_equal( attr( res, "class" ), c("sfc_MULTIPOLYGON", "sfc") )
  expect_true( is_multipolygon( res ) )

})
