context("sfc_POLYGON")

test_that("sfc_polygon works", {

  is_polygon <- function(x) {
    y <- sapply( x, function(y) is.list( unclass( y ) ) )
    z <- sapply( x, function(y) attr( y, "class")[2] == "POLYGON")
    return( all(y) & all(z))
  }

  df <- data.frame(
    p_id = c(1,1,1,1,2,2,2,2)
    , l_id = c(1,1,1,1,1,1,1,1)
    , x = c(1,2,3,1,4,5,6,4)
    , y = c(1,2,3,1,4,5,6,4)
  )

  res <- sfheaders:::rcpp_sfc_polygon( df, NULL, NULL, NULL )
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

  res <- sfheaders:::rcpp_sfc_polygon( df, NULL, NULL, c(0) )
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

  res <- sfheaders:::rcpp_sfc_polygon( df, NULL, c(0), NULL )
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

  res <- sfheaders:::rcpp_sfc_polygon( df, c("x","y"), NULL, NULL )
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

  res <- sfheaders:::rcpp_sfc_polygon( df, c(2,3), NULL, NULL )
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

  res <- sfheaders:::rcpp_sfc_polygon( df, NULL, 0, 1)
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

  res <- sfheaders:::rcpp_sfc_polygon( df, c(2,3), 0, NULL )
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

  res <- sfheaders:::rcpp_sfc_polygon( df, c(2,3), NULL, 1 )
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

  res <- sfheaders:::rcpp_sfc_polygon( df, c(2,3), c(0), c(1))
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

  m <- as.matrix( df )
  m <- matrix( as.integer( m ), ncol = 4 )
  res <- sfheaders:::rcpp_sfc_polygon( m, c(2,3), c(0), c(1))
  expect_true( is_polygon( res ) )

  res <- sfheaders:::rcpp_sfc_polygon( df, c("x","y"),c("p_id"),c("l_id"))
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

})

test_that("data.frame with non-numeric id columns work",{


  is_polygon <- function(x) {
    y <- sapply( x, function(y) is.list( unclass( y ) ) )
    z <- sapply( x, function(y) attr( y, "class")[2] == "POLYGON")
    return( all(y) & all(z))
  }

  df <- data.frame(
    p_id = letters[c(1,1,1,1,2,2,2,2)]
    , l_id = c(1,1,1,1,1,1,1,1)
    , x = c(1,2,3,1,4,5,6,4)
    , y = c(1,2,3,1,4,5,6,4)
    , stringsAsFactors = F
  )

  res <- sfheaders::sfc_polygon(
    obj = df
    , x = "x"
    , y = "y"
    , polygon_id = "p_id"
    , linestring_id = "l_id"
    )
  expect_equal( attr( res, "class" ), c("sfc_POLYGON", "sfc") )
  expect_true( is_polygon( res ) )

})
