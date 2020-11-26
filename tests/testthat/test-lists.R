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

  df <- data.frame(
    id = c(1,1,2,2)
    , x = 1:4
    , y = 1:4
  )

  sf <- sf_linestring(
    obj = df
    , linestring_id = "id"
  )

  sf$l <- list(c("a","b"),c("d","e"))

  res <- sf_to_df(sf = sf, unlist = "l")
  expect_true(inherits( res , "data.frame" ) )
  expect_equal( res$l, c("a","b","d","e"))

  res <- sf_to_df(sf = sf, fill = TRUE)
  expect_true(inherits( res , "data.frame" ) )
  expect_equal( res$l, list(c("a","b"),c("a","b"),c("d","e"),c("d","e"))  )


})

# test_that("calling unlist on a non-list column doesn't error",{
#
#   df <- data.frame(
#     x = 1:4
#     , y = 1:4
#   )
#
#   sf <- sf_linestring(
#     obj = df
#   )
#
#   sf_to_df( sf, fill = TRUE, unlist = "id" )
#
# })


test_that("list_columns are kept",{

   df <- data.frame(
     x = 1:26
     , y = 1:26
     , val = letters
     , line_id = c(rep(1:5,each=5),6)
     , stringsAsFactors = FALSE
   )

   df2 <- df
   df2$val <- 1:26
   m <- as.matrix(df2)

   ## test list colum kept
   l1 <- list(letters)
   l2 <- list(letters[1:5], letters[6:10], letters[11:15], letters[16:20],letters[21:25], letters[26])
   lm1 <- list(1:26)
   lm2 <- list(c(1:5), c(6:10), c(11:15), c(16:20), c(21:25),26)

   ## POINTs - nothing to do
   sf <- sf_multipoint(obj = df, x = "x", y = "y", keep = TRUE, list_columns = "val")
   expect_equal( sf$val, l1 )
   sf <- sf_multipoint(obj = df, x = "x", y = "y", multipoint_id = "line_id", keep = TRUE, list_columns = "val")
   expect_equal( sf$val, l2 )
   sf <- sf_multipoint(obj = df, x = 1, y = 2, keep = TRUE, list_columns = 3)
   expect_equal( sf$val, l1 )
   sf <- sf_multipoint(obj = df, x = 1, y = 2, multipoint_id = 4, keep = TRUE, list_columns = 3)
   expect_equal( sf$val, l2 )

   sf <- sf_multipoint(obj = m, x = "x", y = "y", keep = TRUE, list_columns = "val")
   expect_equal( sf$val, lm1 )
   sf <- sf_multipoint(obj = m, x = "x", y = "y", multipoint_id = "line_id", keep = TRUE, list_columns = "val")
   expect_equal( sf$val, lm2 )
   sf <- sf_multipoint(obj = m, x = 1, y = 2, keep = TRUE, list_columns = 3)
   expect_equal( sf$val, lm1 )
   sf <- sf_multipoint(obj = m, x = 1, y = 2, multipoint_id = 4, keep = TRUE, list_columns = 3)
   expect_equal( sf$val, lm2 )


   sf <- sf_linestring(obj = df, x = "x", y = "y", keep = TRUE, list_columns = "val")
   expect_equal( sf$val, l1 )
   sf <- sf_linestring(obj = df, x = "x", y = "y", linestring_id = "line_id", keep = TRUE, list_columns = "val")
   expect_equal( sf$val, l2 )
   sf <- sf_linestring(obj = df, x = 1, y = 2, keep = TRUE, list_columns = 3)
   expect_equal( sf$val, l1 )
   sf <- sf_linestring(obj = df, x = 1, y = 2, linestring_id = 4, keep = TRUE, list_columns = 3)
   expect_equal( sf$val, l2 )

   sf <- sf_linestring(obj = m, x = "x", y = "y", keep = TRUE, list_columns = "val")
   expect_equal( sf$val, lm1 )
   sf <- sf_linestring(obj = m, x = "x", y = "y", linestring_id = "line_id", keep = TRUE, list_columns = "val")
   expect_equal( sf$val, lm2 )
   sf <- sf_linestring(obj = m, x = 1, y = 2, keep = TRUE, list_columns = 3)
   expect_equal( sf$val, lm1 )
   sf <- sf_linestring(obj = m, x = 1, y = 2, linestring_id = 4, keep = TRUE, list_columns = 3)
   expect_equal( sf$val, lm2 )


   ## nested-geometry types
   ## the list-column is returned in the same list-nesting-structure as the geometry
   sf <- sf_multilinestring(obj = df, x = "x", y = "y", keep = TRUE, list_columns = "val")
   expect_equal( sf$val, lapply( l1, list ) )
   sf <- sf_multilinestring(obj = df, x = "x", y = "y", multilinestring_id = "line_id", keep = TRUE, list_columns = "val")
   expect_equal( sf$val, lapply( l2, list ) )
   sf <- sf_multilinestring(obj = df, x = 1, y = 2, keep = TRUE, list_columns = 3)
   expect_equal( sf$val, lapply( l1, list ) )
   sf <- sf_multilinestring(obj = df, x = 1, y = 2, multilinestring_id = 4, keep = TRUE, list_columns = 3)
   expect_equal( sf$val, lapply( l2, list ) )

   sf <- sf_multilinestring(obj = m, x = "x", y = "y", keep = TRUE, list_columns = "val")
   expect_equal( sf$val, lapply( lm1, list ) )
   sf <- sf_multilinestring(obj = m, x = "x", y = "y", multilinestring_id = "line_id", keep = TRUE, list_columns = "val")
   expect_equal( sf$val, lapply( lm2, list ) )
   sf <- sf_multilinestring(obj = m, x = 1, y = 2, keep = TRUE, list_columns = 3)
   expect_equal( sf$val, lapply( lm1, list ) )
   sf <- sf_multilinestring(obj = m, x = 1, y = 2, multilinestring_id = 4, keep = TRUE, list_columns = 3)
   expect_equal( sf$val, lapply( lm2, list ) )

   sf <- sf_polygon(obj = df, x = "x", y = "y", keep = TRUE, list_columns = "val", close = FALSE )
   expect_equal( sf$val, lapply( l1, list ) )
   sf <- sf_polygon(obj = df, x = "x", y = "y", polygon_id = "line_id", keep = TRUE, list_columns = "val", close = FALSE)
   expect_equal( sf$val, lapply( l2, list ) )
   sf <- sf_polygon(obj = df, x = 1, y = 2, keep = TRUE, list_columns = 3, close = FALSE )
   expect_equal( sf$val, lapply( l1, list ) )
   sf <- sf_polygon(obj = df, x = 1, y = 2, polygon_id = 4, keep = TRUE, list_columns = 3, close = FALSE)
   expect_equal( sf$val, lapply( l2, list ) )

   sf <- sf_polygon(obj = m, x = "x", y = "y", keep = TRUE, list_columns = "val", close = FALSE )
   expect_equal( sf$val, lapply( lm1, list ) )
   sf <- sf_polygon(obj = m, x = "x", y = "y", polygon_id = "line_id", keep = TRUE, list_columns = "val", close = FALSE)
   expect_equal( sf$val, lapply( lm2, list ) )
   sf <- sf_polygon(obj = m, x = 1, y = 2, keep = TRUE, list_columns = 3, close = FALSE )
   expect_equal( sf$val, lapply( lm1, list ) )
   sf <- sf_polygon(obj = m, x = 1, y = 2, polygon_id = 4, keep = TRUE, list_columns = 3, close = FALSE)
   expect_equal( sf$val, lapply( lm2, list ) )


   nest <- function( x ) lapply( x, function( y ) list( list( y ) ) )
   sf <- sf_multipolygon(obj = df, x = "x", y = "y", keep = TRUE, list_columns = "val", close = FALSE )
   expect_equal( sf$val, nest( l1 ) )
   sf <- sf_multipolygon(obj = df, x = "x", y = "y", multipolygon_id = "line_id", keep = TRUE, list_columns = "val", close = FALSE)
   expect_equal( sf$val, nest( l2 ) )
   sf <- sf_multipolygon(obj = df, x = 1, y = 2, keep = TRUE, list_columns = 3, close = FALSE)
   expect_equal( sf$val, nest( l1 ) )
   sf <- sf_multipolygon(obj = df, x = 1, y = 2, multipolygon_id = 4, keep = TRUE, list_columns = 3, close = FALSE)
   expect_equal( sf$val, nest( l2 ) )

   sf <- sf_multipolygon(obj = m, x = "x", y = "y", keep = TRUE, list_columns = "val", close = FALSE )
   expect_equal( sf$val, nest( lm1 ) )
   sf <- sf_multipolygon(obj = m, x = "x", y = "y", multipolygon_id = "line_id", keep = TRUE, list_columns = "val", close = FALSE)
   expect_equal( sf$val, nest( lm2 ) )
   sf <- sf_multipolygon(obj = m, x = 1, y = 2, keep = TRUE, list_columns = 3, close = FALSE )
   expect_equal( sf$val, nest( lm1 ) )
   sf <- sf_multipolygon(obj = m, x = 1, y = 2, multipolygon_id = 4, keep = TRUE, list_columns = 3, close = FALSE)
   expect_equal( sf$val, nest( lm2 ) )

   ## two id_columns
   df <- data.frame(
     x = 1:26
     , y = 1:26
     , val = letters
     , poly_id = c(rep(1:2,each=12),3,3)
     , line_id = c(rep(1:5,each=5),6)
     , stringsAsFactors = FALSE
   )

   ## l2 is a list element per 'ring'
   l2 <- list(
      list( letters[1:5], letters[6:10], letters[11:12] )
      , list( letters[13:15], letters[16:20], letters[21:24] )
      , list( letters[25], letters[26] )
   )

   sf <- sf_polygon(obj = df, x = "x", y = "y", polygon_id = "poly_id", linestring_id = "line_id", keep = TRUE, list_columns = "val", close = FALSE)
   expect_equal( sf$val, l2 )
   sf <- sf_polygon(obj = df, x = 1, y = 2, polygon_id = 4, linestring_id = 5, keep = TRUE, list_columns = 3, close = FALSE)
   expect_equal( sf$val, l2 )
})

## issue 75
test_that("non-existant list-columns are ignored",{

   df <- data.frame(
      x = 1:4
      , y = 1:4
      , val = 1:4
   )

   sf <- sf_linestring(
      obj = df
      , x = "x"
      , y = "y"
   )

   res <- sf_to_df(sf = sf, unlist = "val")
   expect_true( !"val" %in% names(res))

})

## issue 76
test_that("ignore unlist columns if they aren't lists",{

   ## waht if we try to unlist a column which isn't a list?

   df <- data.frame(
      x = 1:4
      , y = 1:4
      , val = 1:4
      , ix = c(1,1,2,2)
   )

   sf <- sf_linestring(
      obj = df
      , x = "x"
      , y = "y"
      , linestring_id = "ix"
      , keep = T
   )

   res <- sf_to_df( sf = sf, fill = TRUE, unlist = "val")
   expect_equal( res$val, c(1,1,3,3) )#sf$val )

})
