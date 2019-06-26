context("shapes_get_lines")

#
# url <- "https://raw.githubusercontent.com/SymbolixAU/data/master/geojson/SA1_2016_VIC.json"
# library(sf)
# library(data.table)
# sf <- geojsonsf::geojson_sf( url )
#
# coords <- sf::st_coordinates( sf )
# dt <- data.table::as.data.table( coords )
#
# setnames(dt, c("lon","lat","line_id","polygon_id","multipolygon_id"))
# x <- dt[ multipolygon_id %in% c(13895) ]
#
# #res <- sfheaders:::rcpp_get_polygon(x, c("lon","lat"), "polygon_id", "line_id")
#
#
# # # ## this is the logic for getting multipolygons
# # ids <- c( rep(1,5), rep(2,3), rep(3,6) )
# # x <- data.frame(
# #   polygon_id = c( rep(1, 5+3), rep(2,6) )
# #   , line_id = ids
# #   , x = seq(1, length(ids))
# #   , y = seq(length(ids), 1)
# # )
#
# # mpl <- sfheaders:::rcpp_get_polygon(x, c("x","y"), "polygon_id",  "line_id" )

l1 <- matrix(c(0,0,0,1,1,1,1,0,0,0), ncol = 2, byrow = T)
l2 <- matrix(c(2,2,2,5,5,5,5,2,2,2), ncol = 2, byrow = T)
l3 <- matrix(c(3,3,3,4,4,4,4,3,3,3), ncol = 2, byrow = T)

p1 <- list(l1)
p2 <- list(l2, l3)

mp <- list(p1, p2)
sf <- sf::st_sf( geometry = sf::st_sfc( sf::st_multipolygon( x = mp ) ) )

coords <- sf::st_coordinates( sf )
dt <- data.table::as.data.table( coords )

data.table::setnames(dt, c("lon","lat","line_id","polygon_id","multipolygon_id"))

res <- sfheaders:::rcpp_get_polygons(dt, c("lon","lat"), "polygon_id", "line_id")
res2 <- sfheaders:::rcpp_get_polygons2(dt, c(0,1), 3, 2)


x <- dt

polygon_ids <- x$polygon_id
line_ids <- x$line_id
## need to find the line_ids which correspond to each polygon_id
unique_polygon_ids <- sort( unique( polygon_ids ) )
polygons <- sfheaders:::rcpp_line_ids( polygon_ids, unique_polygon_ids )
## loop over the rows
lst_mpl <- list()

for( i in 1:nrow( polygons ) ) {

  polygon_line_ids <- line_ids[ polygons[i,1]:polygons[i,2] + 1 ]
  unique_polygon_line_ids <- sort( unique( polygon_line_ids ) )
  polygon_lines <- sfheaders:::rcpp_line_ids( polygon_ids, unique_polygon_line_ids )

  lst_pl <- list()
  df_subset <- sfheaders:::rcpp_subset_dataframe( x, c( "line_id", "lon", "lat"), polygons[i, 1], polygons[i, 2] )
  lst_mpl[[i]] <- sfheaders:::rcpp_get_lines( df_subset, c("lon","lat"), "line_id")
}





test_that("lines lists returend",{

  ids <- c( rep(1,5), rep(2,3), rep(3,6) )
  x <- data.frame(
    id = ids
    , x = seq(1, length(ids))
    , y = seq(length(ids), 1)
  )

  res <- sfheaders:::rcpp_get_lines( x, c("x","y"), "id")
  expect_true( is.list( res ) )
  expect_true( is.matrix( res[[1]] ) )
  expect_true( is.matrix( res[[2]] ) )
  expect_true( is.matrix( res[[3]] ) )
  m1 <- res[[1]]; m2 <- res[[2]]; m3 <- res[[3]]

  expect_equal( m1[,1], 1:5 )
  expect_equal( m1[,2], 14:10 )
  expect_equal( m2[,1], 6:8 )
  expect_equal( m2[,2], 9:7 )
  expect_equal( m3[,1], 9:14 )
  expect_equal( m3[,2], 6:1 )

  res <- sfheaders:::rcpp_get_lines( x, c(2,1), 0)
  expect_true( is.list( res ) )
  expect_true( is.matrix( res[[1]] ) )
  expect_true( is.matrix( res[[2]] ) )
  expect_true( is.matrix( res[[3]] ) )
  m1 <- res[[1]]; m2 <- res[[2]]; m3 <- res[[3]]

  expect_equal( m1[,2], 1:5 )
  expect_equal( m1[,1], 14:10 )
  expect_equal( m2[,2], 6:8 )
  expect_equal( m2[,1], 9:7 )
  expect_equal( m3[,2], 9:14 )
  expect_equal( m3[,1], 6:1 )

  ids <- c( rep(1,5), rep(2,3), rep(3,6) )
  x <- data.frame(
    id = ids
    , x = seq(1, length(ids))
    , y = seq(length(ids), 1)
  )
  x <- as.matrix( x )

  res <- sfheaders:::rcpp_get_lines( x, c("x","y"), "id")
  expect_true( is.list( res ) )
  expect_true( is.matrix( res[[1]] ) )
  expect_true( is.matrix( res[[2]] ) )
  expect_true( is.matrix( res[[3]] ) )
  m1 <- res[[1]]; m2 <- res[[2]]; m3 <- res[[3]]

  expect_equal( m1[,1], 1:5 )
  expect_equal( m1[,2], 14:10 )
  expect_equal( m2[,1], 6:8 )
  expect_equal( m2[,2], 9:7 )
  expect_equal( m3[,1], 9:14 )
  expect_equal( m3[,2], 6:1 )

  res <- sfheaders:::rcpp_get_lines( x, c(2,1), 0)
  expect_true( is.list( res ) )
  expect_true( is.matrix( res[[1]] ) )
  expect_true( is.matrix( res[[2]] ) )
  expect_true( is.matrix( res[[3]] ) )
  m1 <- res[[1]]; m2 <- res[[2]]; m3 <- res[[3]]

  expect_equal( m1[,2], 1:5 )
  expect_equal( m1[,1], 14:10 )
  expect_equal( m2[,2], 6:8 )
  expect_equal( m2[,1], 9:7 )
  expect_equal( m3[,2], 9:14 )
  expect_equal( m3[,1], 6:1 )

  ids <- c( rep(1L,5L), rep(2L,3L), rep(3L,6L) )
  x <- data.frame(
    id = ids
    , x = seq(1L, length(ids))
    , y = seq(length(ids), 1L)
  )

  x <- as.matrix( x )
  res <- sfheaders:::rcpp_get_lines( x, c("x","y"), "id")
  expect_true( is.list( res ) )
  expect_true( is.matrix( res[[1]] ) )
  expect_true( is.matrix( res[[2]] ) )
  expect_true( is.matrix( res[[3]] ) )
  m1 <- res[[1]]; m2 <- res[[2]]; m3 <- res[[3]]

  expect_equal( m1[,1], 1:5 )
  expect_equal( m1[,2], 14:10 )
  expect_equal( m2[,1], 6:8 )
  expect_equal( m2[,2], 9:7 )
  expect_equal( m3[,1], 9:14 )
  expect_equal( m3[,2], 6:1 )

  res <- sfheaders:::rcpp_get_lines( x, c(2,1), 0)
  expect_true( is.list( res ) )
  expect_true( is.matrix( res[[1]] ) )
  expect_true( is.matrix( res[[2]] ) )
  expect_true( is.matrix( res[[3]] ) )
  m1 <- res[[1]]; m2 <- res[[2]]; m3 <- res[[3]]

  expect_equal( m1[,2], 1:5 )
  expect_equal( m1[,1], 14:10 )
  expect_equal( m2[,2], 6:8 )
  expect_equal( m2[,1], 9:7 )
  expect_equal( m3[,2], 9:14 )
  expect_equal( m3[,1], 6:1 )


})
