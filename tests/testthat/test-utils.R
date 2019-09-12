context("sfheaders")

test_that("index_correct works",{

  x <- 1:4
  res <- sfheaders:::index_correct( x )
  expect_equal( x - 1, res )

})

test_that("sfheaders::utils::subset subsets a data.frame",{

  x <- data.frame(
    id = c(1,1,1,2,2,2)
    , x = c(1:6)
    , y = c(6:1)
    , z = letters[1:6]
    , a = c(TRUE,FALSE,TRUE,FALSE,TRUE,FALSE)
    , stringsAsFactors = FALSE
  )
  idx <- c(0,1)
  res <- sfheaders:::rcpp_subset_dataframe(x, c("x","y"), idx[1], idx[2] )
  expect_equal( x[ idx+1, c("x","y") ], res )

  idx <- c(0,1)
  res <- sfheaders:::rcpp_subset_dataframe(x, c("id","x","y","z"), idx[1], idx[2] )
  ## TODO
  # expect_equal( x[idx+1, ], res )

  idx <- c(0,1)
  res <- sfheaders:::rcpp_subset_dataframe(x, c("a"), idx[1], idx[2] )
  expect_equal( x[idx+1, "a", drop = F], res )
})


test_that("sfheaders::utils::id_positions returns correct positions",{

  line_ids <- c(1,1,1,1,1)
  unique_ids <- sort( unique( line_ids ) )
  expected <- matrix(c(0,4), ncol = 2)
  res <- sfheaders:::rcpp_id_positions( line_ids, unique_ids )
  expect_equal( res, expected )

  line_ids <- c(1.1, 1.1)
  unique_ids <- sort( unique( line_ids ) )
  expected <- matrix(c(0,1), ncol = 2)
  res <- sfheaders:::rcpp_id_positions( line_ids, unique_ids )
  expect_equal( res, expected )

  line_ids <- c("a")
  unique_ids <- sort( unique( line_ids ) )
  expected <- matrix(c(0,0), ncol = 2)
  res <- sfheaders:::rcpp_id_positions( line_ids, unique_ids )
  expect_equal( res, expected )

  line_ids <- c("a","a")
  unique_ids <- sort( unique( line_ids ) )
  expected <- matrix(c(0,1), ncol = 2)
  res <- sfheaders:::rcpp_id_positions( line_ids, unique_ids )
  expect_equal( res, expected )

  line_ids <- c(1,1,1,1,2,2,3,3,3,3)
  unique_ids <- sort( unique( line_ids ) )
  expected <- matrix(c(0,3,4,5,6,9), ncol = 2, byrow = T)
  res <- sfheaders:::rcpp_id_positions( line_ids, unique_ids )
  expect_equal( res, expected )

  line_ids <- as.integer( c(1,1,1,1,2,2,1,3) )
  unique_ids <- as.integer( sort( unique( line_ids ) ) )
  expect_error( sfheaders:::rcpp_id_positions( line_ids, unique_ids ), "sfheaders - error indexing lines, perhaps caused by un-ordered data?")

  line_ids <- c(1.1,1.1,1.1,2,2,1.1,3.1)
  unique_ids <- sort( unique( line_ids ) )
  expect_error( sfheaders:::rcpp_id_positions( line_ids, unique_ids ), "sfheaders - error indexing lines, perhaps caused by un-ordered data?")



})

test_that("sfheaders::utils::other_columns works for various data types",{

  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  other_cols <- sfheaders:::rcpp_other_columns( df, NULL, NULL, NULL )
  expect_equal( other_cols, c("x","y","z") )

  m <- matrix( 1:24, ncol = 3 )
  other_cols <- sfheaders:::rcpp_other_columns( m, NULL, NULL, NULL )
  expect_equal( other_cols, c(0,1,2))


  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c(2)  ## c++ index
  other_cols <- sfheaders:::rcpp_other_columns( df, id, NULL, NULL )
  expect_equal( other_cols, c(0,1) )

  m <- matrix( 1:24, ncol = 3 )
  id <- c(2)
  other_cols <- sfheaders:::rcpp_other_columns( m, id, NULL, NULL )
  expect_equal( other_cols, c(0,1))


  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c(0,2)  ## c++ index
  other_cols <- sfheaders:::rcpp_other_columns( df, id, NULL, NULL )
  expect_equal( other_cols, c(1) )

  m <- matrix( 1:24, ncol = 3 )
  id <- c(0,2)
  other_cols <- sfheaders:::rcpp_other_columns( m, id, NULL, NULL )
  expect_equal( other_cols, c(1))

  ## using names / strings
  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c("z")
  other_cols <- sfheaders:::rcpp_other_columns( df, id, NULL, NULL )
  expect_equal( other_cols, c("x","y") )

  m <- matrix( 1:24, ncol = 3 )
  dimnames(m) <- list(NULL, c("x","y","z") )
  id <- c("z")
  other_cols <- sfheaders:::rcpp_other_columns( m, id, NULL, NULL )
  expect_equal( other_cols, c("x","y"))

  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c("z","x")
  other_cols <- sfheaders:::rcpp_other_columns( df, id, NULL, NULL )
  expect_equal( other_cols, c("y") )

  m <- matrix( 1:24, ncol = 3 )
  dimnames(m) <- list(NULL, c("x","y","z") )
  id <- c("z","x")
  other_cols <- sfheaders:::rcpp_other_columns( m, id, NULL, NULL )
  expect_equal( other_cols, c("y"))




  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c(2)  ## c++ index
  other_cols <- sfheaders:::rcpp_other_columns( df, NULL, id, NULL )
  expect_equal( other_cols, c(0,1) )

  m <- matrix( 1:24, ncol = 3 )
  id <- c(2)
  other_cols <- sfheaders:::rcpp_other_columns( m, NULL, id, NULL )
  expect_equal( other_cols, c(0,1))


  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c(0,2)  ## c++ index
  other_cols <- sfheaders:::rcpp_other_columns( df, NULL, id, NULL )
  expect_equal( other_cols, c(1) )

  m <- matrix( 1:24, ncol = 3 )
  id <- c(0,2)
  other_cols <- sfheaders:::rcpp_other_columns( m, NULL, id, NULL )
  expect_equal( other_cols, c(1))

  ## using names / strings
  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c("z")
  other_cols <- sfheaders:::rcpp_other_columns( df, NULL, id, NULL )
  expect_equal( other_cols, c("x","y") )

  m <- matrix( 1:24, ncol = 3 )
  dimnames(m) <- list(NULL, c("x","y","z") )
  id <- c("z")
  other_cols <- sfheaders:::rcpp_other_columns( m, NULL, id, NULL )
  expect_equal( other_cols, c("x","y"))

  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c("z","x")
  other_cols <- sfheaders:::rcpp_other_columns( df, NULL, id, NULL )
  expect_equal( other_cols, c("y") )

  m <- matrix( 1:24, ncol = 3 )
  dimnames(m) <- list(NULL, c("x","y","z") )
  id <- c("z","x")
  other_cols <- sfheaders:::rcpp_other_columns( m, NULL, id, NULL )
  expect_equal( other_cols, c("y"))



  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c(2)  ## c++ index
  other_cols <- sfheaders:::rcpp_other_columns( df, NULL, NULL, id )
  expect_equal( other_cols, c(0,1) )

  m <- matrix( 1:24, ncol = 3 )
  id <- c(2)
  other_cols <- sfheaders:::rcpp_other_columns( m, NULL, NULL, id )
  expect_equal( other_cols, c(0,1))


  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c(0,2)  ## c++ index
  other_cols <- sfheaders:::rcpp_other_columns( df, NULL, NULL, id )
  expect_equal( other_cols, c(1) )

  m <- matrix( 1:24, ncol = 3 )
  id <- c(0,2)
  other_cols <- sfheaders:::rcpp_other_columns( m, NULL, NULL, id )
  expect_equal( other_cols, c(1))

  ## using names / strings
  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c("z")
  other_cols <- sfheaders:::rcpp_other_columns( df, NULL, NULL, id )
  expect_equal( other_cols, c("x","y") )

  m <- matrix( 1:24, ncol = 3 )
  dimnames(m) <- list(NULL, c("x","y","z") )
  id <- c("z")
  other_cols <- sfheaders:::rcpp_other_columns( m, NULL, NULL, id )
  expect_equal( other_cols, c("x","y"))

  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c("z","x")
  other_cols <- sfheaders:::rcpp_other_columns( df, NULL, NULL, id )
  expect_equal( other_cols, c("y") )

  m <- matrix( 1:24, ncol = 3 )
  dimnames(m) <- list(NULL, c("x","y","z") )
  id <- c("z","x")
  other_cols <- sfheaders:::rcpp_other_columns( m, NULL, NULL, id )
  expect_equal( other_cols, c("y"))



  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c("z")
  id2 <- c("y")
  other_cols <- sfheaders:::rcpp_other_columns( df, id, id2, NULL )
  expect_equal( other_cols, c("x") )

  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c("z")
  id2 <- c("y","x")
  other_cols <- sfheaders:::rcpp_other_columns( df, id, id2, NULL )
  expect_equal( other_cols, character() )

  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c(0)
  id2 <- c(1,2)
  other_cols <- sfheaders:::rcpp_other_columns( df, id, id2, NULL )
  expect_equal( other_cols, numeric() )



  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c("z")
  id2 <- c("y")
  other_cols <- sfheaders:::rcpp_other_columns( df, NULL, id, id2 )
  expect_equal( other_cols, c("x") )

  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c("z")
  id2 <- c("y","x")
  other_cols <- sfheaders:::rcpp_other_columns( df, NULL, id, id2 )
  expect_equal( other_cols, character() )

  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c(0)
  id2 <- c(1,2)
  other_cols <- sfheaders:::rcpp_other_columns( df, NULL, id, id2 )
  expect_equal( other_cols, numeric() )




  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c("z")
  id2 <- c("y")
  other_cols <- sfheaders:::rcpp_other_columns( df, id, NULL, id2 )
  expect_equal( other_cols, c("x") )

  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c("z")
  id2 <- c("y","x")
  other_cols <- sfheaders:::rcpp_other_columns( df, id, NULL, id2 )
  expect_equal( other_cols, character() )

  df <- data.frame(x = 1:2, y = 3:4, z = 5:6 )
  id <- c(0)
  id2 <- c(1,2)
  other_cols <- sfheaders:::rcpp_other_columns( df, id, NULL, id2 )
  expect_equal( other_cols, numeric() )




  df <- data.frame(x = 1:2, y = 3:4, z = 5:6, m = 7:8 )
  id <- c(0)
  id2 <- c(1,2)
  id3 <- c(3)
  other_cols <- sfheaders:::rcpp_other_columns( df, id, id2, id3 )
  expect_equal( other_cols, numeric() )

  df <- data.frame(x = 1:2, y = 3:4, z = 5:6, m = 7:8, id = 1:2 )
  id <- c(0)
  id2 <- c(1,2)
  id3 <- c(3)
  other_cols <- sfheaders:::rcpp_other_columns( df, id, id2, id3 )
  expect_equal( other_cols, c(4) )

  df <- data.frame(x = 1:2, y = 3:4, z = 5:6, m = 7:8, id = 1:2 )
  id <- c(0)
  id2 <- c(0)
  id3 <- c(0)
  other_cols <- sfheaders:::rcpp_other_columns( df, id, id2, id3 )
  expect_equal( other_cols, c(1,2,3,4) )





})

test_that("concatenate_vectors works",{


  expect_equal( sfheaders:::rcpp_concatenate_vectors(1L,5L), c(1L,5L))
  expect_equal( sfheaders:::rcpp_concatenate_vectors(1,5), c(1,5))
  expect_equal( sfheaders:::rcpp_concatenate_vectors(1.2,5), c(1.2,5))
  expect_equal( sfheaders:::rcpp_concatenate_vectors("a","b"), c("a","b"))
  expect_error( sfheaders:::rcpp_concatenate_vectors(1,"a"), "sfheaders - different vector types found")

  expect_equal( sfheaders:::rcpp_concatenate_vectors(c(1L,2L), c(3L)), c(1L:3L))
  expect_equal( sfheaders:::rcpp_concatenate_vectors(c(1L,2L), c(3L,4L)), c(1L:4L))
  expect_equal( sfheaders:::rcpp_concatenate_vectors(c("a","b"), c("c","d")), c("a","b","c","d"))

})


test_that("column positions returned",{

  df <- data.frame(
    a = 1L:3L
    , b = 4L:6
  )
  m <- as.matrix( df )
  expect_equal( sfheaders:::rcpp_column_positions( m, c("a") ), c(0) )
  expect_equal( sfheaders:::rcpp_column_positions( m, c("a","b") ), c(0,1) )

  df <- data.frame(
    a = 1.3
    , b = 4.6
  )
  m <- as.matrix( df )
  expect_equal( sfheaders:::rcpp_column_positions( m, c("a") ), c(0) )
  expect_equal( sfheaders:::rcpp_column_positions( m, c("a","b") ), c(0,1) )

})

test_that("where_is finds the correct position",{

  sv <- c("hello", "world")
  expect_equal( sfheaders:::rcpp_where_is( "hello" , sv ), 0L )
  expect_equal( sfheaders:::rcpp_where_is( "world" , sv ), 1L )
  expect_equal( sfheaders:::rcpp_where_is( "foo" , sv ), -1L )

})

test_that("unique ids are retrieved from column",{

  m <- matrix(1L:4L, ncol = 2)
  expect_equal( sfheaders:::rcpp_get_ids( m, 0 ), c(1L:2L) )

  m <- matrix(c(1.2, 2,3,4), ncol = 2)
  expect_equal( sfheaders:::rcpp_get_ids( m, 0 ), c(1.2,2) )

  m <- matrix(1L:4L, ncol = 2)
  df <- as.data.frame(m)
  m <- as.matrix(m)
  expect_equal( sfheaders:::rcpp_get_ids( m, 0 ), c(1L:2L) )
  expect_equal( sfheaders:::rcpp_get_ids( m, "V1" ), c(1L:2L) )

  m <- matrix(c(1.2, 2,3,4), ncol = 2)
  df <- as.data.frame(m)
  m <- as.matrix(m)
  expect_equal( sfheaders:::rcpp_get_ids( m, 0 ), c(1.2,2) )
  expect_equal( sfheaders:::rcpp_get_ids( m, "V1" ), c(1.2,2) )

})
