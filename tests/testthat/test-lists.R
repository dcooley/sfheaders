context("lists")

test_that("lists types are correct",{

  lst <- list(T)
  expect_equal( sfheaders:::rcpp_list_type( lst ), 10 )

  lst <- list(1L)
  expect_equal( sfheaders:::rcpp_list_type( lst ), 13 )

  lst <- list(1L,2)
  expect_equal( sfheaders:::rcpp_list_type( lst ), 14 )

  lst <- list(1L,2,"3")
  expect_equal( sfheaders:::rcpp_list_type( lst ), 16 )

  lst <- list(1L,2,as.raw(3))
  expect_equal( sfheaders:::rcpp_list_type( lst ), 16 )

  lst <- list(1L,2,as.complex(3))
  expect_equal( sfheaders:::rcpp_list_type( lst ), 16 )
})

test_that("list sizes are correct",{

  lst <- list(T)
  res <- sfheaders:::rcpp_list_sizes( lst )
  expect_equal( res$total, length( unlist( lst ) ) )
  expect_equal( res$elements[[1]], res$total )

  lst <- list(c(1,2,3),c(1,2),c(1))
  res <- sfheaders:::rcpp_list_sizes( lst )
  expect_equal( res$total, length( unlist( lst ) ) )
  expect_equal( unlist( res$elements ), lengths( lst ) )

  lst <- list(c(1,2,3),c(1,2),c(1), list(c(1,2,3),c(1,2),c(1)))
  res <- sfheaders:::rcpp_list_sizes( lst )
  expect_equal( res$total, length( unlist( lst ) ) )
  expect_equal( length( res ), 2 )
  expect_equal( unlist( res$elements[[1]] ), length( lst[[1]] ) )
  expect_equal( unlist( res$elements[[2]] ), length( lst[[2]] ) )
  expect_equal( unlist( res$elements[[3]] ), length( lst[[3]] ) )
  expect_equal( unlist( res$elements[[4]] ), lengths( lst[[4]] ) )

})

test_that("lists are unlist",{

  lst <- list(T)
  res <- sfheaders:::rcpp_unlist_list( lst )
  expect_equal( unlist( lst ), res )

  lst <- list(1L)
  res <- sfheaders:::rcpp_unlist_list( lst )
  expect_equal( unlist( lst ), res )

  lst <- list(1.5)
  res <- sfheaders:::rcpp_unlist_list( lst )
  expect_equal( unlist( lst ), res )

  lst <- list("a")
  res <- sfheaders:::rcpp_unlist_list( lst )
  expect_equal( unlist( lst ), res )

  lst <- list(1L,2.3)
  res <- sfheaders:::rcpp_unlist_list( lst )
  expect_equal( unlist( lst ), res )

  lst <- list(1L,2.3,"a")
  res <- sfheaders:::rcpp_unlist_list( lst )
  expect_equal( unlist( lst ), res )

  lst <- list(1L,2.3,"a",list(1,2,3, list("a","b","c")))
  res <- sfheaders:::rcpp_unlist_list( lst )
  expect_equal( unlist( lst ), res )

})


test_that("sf with list columns are unlist",{

  df <- data.frame(
    x = 1:4
    , y = 1:4
  )

  sf <- sf_linestring(
    obj = df
  )

  sf$l <- list(letters[1:4])

  res <- sfheaders:::rcpp_sf_to_df_unlist( sf, TRUE, unlist = "l" )

  expect_true( nrow( res ) == 4 )
  expect_equal( res$l, letters[1:4] )

  df <- data.frame(
    x = 1:4
    , y = 1:4
  )

  sf <- sf_linestring(
    obj = df
  )

  sf$l <- list(letters[1:5])

  expect_error(
    sfheaders::sf_to_df( sf, TRUE, unlist = "l" )
    , "sfheaders - unlisted column doesn't have the correct number of rows"
  )

  sf$l <- list(letters[1:3])

  expect_error(
    sfheaders::sf_to_df( sf, TRUE, unlist = "l" )
    , "sfheaders - unlisted column doesn't have the correct number of rows"
  )

})

test_that("list_columns are kept",{

   df <- data.frame(
     x = 1:26
     , y = 1:26
     , val = letters
     , line_id = c(rep(1:5,each=5),6)
     , stringsAsFactors = FALSE
   )


   sf_mpt1 <- sf_multipoint(obj = df, x = "x", y = "y", keep = TRUE)
   sf_mpt2 <- sf_multipoint(obj = df, x = "x", y = "y", keep = TRUE, list_columns = "val")
   sf_mpt1 <- sf_multipoint(obj = df, x = "x", y = "y", multipoint_id = "line_id", keep = TRUE)
   sf_mpt2 <- sf_multipoint(obj = df, x = "x", y = "y", multipoint_id = "line_id", keep = TRUE, list_columns = "val")
   sf_ls <- sf_linestring(obj = df, x = "x", y = "y", keep = TRUE)


})
