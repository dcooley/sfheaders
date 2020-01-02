# df <- data.frame(
#   id = c(1,1,1,2,2,2)
#   , x = c(1,1,1,2,2,2)
#   , y = c(3,3,3,4,4,4)
# )
#
# pt <- sfheaders:::sfg_point(c(1,2))
# mpt <- sfheaders:::sfg_multipoint( df )
# ls <- sfheaders::sfg_linestring(df, x = "x", y = "y")
# mls <- sfheaders::sfg_multilinestring(obj = df, linestring_id = "id")
#
# m <- cbind( matrix( 1:24, ncol = 2 ), c(rep(1, 6), rep(2, 6) ) )
# p <- sfg_polygon( obj = m, x = 1, y = 2, linestring_id = 3 )
#
# df <- data.frame(
#   polygon_id = c(rep(1, 5), rep(2, 10))
#   , line_id = c(rep(1, 10), rep(2, 5))
#   , x = c(0,0,1,1,0,2,2,5,5,2,3,3,4,4,3)
#   , y = c(0,1,1,0,0,2,5,5,2,2,3,4,4,3,3)
#   , z = c(1)
#   , m = c(1)
# )
#
# mp <- sfg_multipolygon( df, x = "x", y = "y", polygon_id = "polygon_id", linestring_id = "line_id" )
#
# mp
# sfheaders:::rcpp_sfg_multipolygon_coordinates( mp )
# # sfheaders:::rcpp_sfg_coordinate_lists( mp )
# sfheaders:::rcpp_sfg_to_df( mp )
# mp
#
#
# pt
# sfheaders:::rcpp_sfg_point_coordinates( pt )
# # sfheaders:::rcpp_sfg_coordinate_lists( pt )
# sfheaders:::rcpp_sfg_to_df( pt )
# pt
#
# mpt
# sfheaders:::rcpp_sfg_multipoint_coordinates( mpt )
# # sfheaders:::rcpp_sfg_coordinate_lists( mpt )
# sfheaders:::rcpp_sfg_to_df( mpt )
# mpt
#
# ls
# sfheaders:::rcpp_sfg_linestring_coordinates( ls )
# # sfheaders:::rcpp_sfg_coordinate_lists( ls )
# sfheaders:::rcpp_sfg_to_df( ls )
# ls
#
# mls
# sfheaders:::rcpp_sfg_multilinestring_coordinates( mls )
# # sfheaders:::rcpp_sfg_coordinate_lists( mls )
# sfheaders:::rcpp_sfg_to_df( mls )
# mls
#
# p
# sfheaders:::rcpp_sfg_polygon_coordinates( p )
# # sfheaders:::rcpp_sfg_coordinate_lists( p )
# sfheaders:::rcpp_sfg_to_df( p )
# p

#
#
# ls <- sfg_linestring( matrix(1:1e7, ncol = 2) )
#
# res <- sfheaders:::rcpp_sfg_linestring_coordinates( ls )
#
# library(microbenchmark)
#
# microbenchmark(
#   sf = { coords <- sf::st_coordinates( ls ) },
#   sfh = { lst <- sfheaders:::rcpp_sfg_linestring_coordinates( ls ) },
#   #sfh = { df <- sfheaders:::rcpp_sfg_to_df( ls ) },
#   #sfh_c = { res <- sfheaders:::rcpp_sfg_coordinates( ls ) },
#   #sfh2 = { res <- sfheaders:::rcpp_sfg_coordinates( ls ); df2 <- as.data.frame( res ) },
#   times = 5
# )
#
# mls <- sfg_multilinestring(
#   cbind(
#     c(
#       rep(1, 1e6 / 8)
#       , rep(2, 1e6 / 8)
#       , rep(3, 1e6 / 8)
#       , rep(4, 1e6 / 8)
#       )
#     , matrix(1:1e6, ncol = 2)
#     )
#   , linestring_id = 1
#   )
#
# res <- sfheaders:::rcpp_sfg_multilinestring_coordinates( mls )
#
# library(microbenchmark)
# #
# microbenchmark(
#   sf = { sf::st_coordinates( mls ) },
#   sfh = { sfheaders:::rcpp_sfg_multilinestring_coordinates( mls ) },
#   # sfh = { sfheaders:::rcpp_sfg_to_df( mls ) },
#   # sfh_c = { sfheaders:::rcpp_sfg_coordinates( mls ) },
#   times = 5
# )


# sfheaders:::rcpp_sfg_to_df( p )

# n <- 1e5
# df <- data.frame(
#   polygon_id = c(rep(1, n / 5), rep(2, n / 5), rep(3, n / 5), rep(4, n / 5), rep(5, n / 5))
#   , line_id = c( rep(1, n / 10), rep(2, n / 10) )
#   , x = rnorm(n)
#   , y = rnorm(n)
# )
#
# mp <- sfg_multipolygon(
#   df, x = "x", y = "y"
#   , polygon_id = "polygon_id"
#   , linestring_id = "line_id"
#   , close = F
# )
#
# #res <- sfheaders:::rcpp_sfg_multipolygon_coordinates( mp )
# library(microbenchmark)
#
# microbenchmark(
#   sf = { coords <- sf::st_coordinates( mp ) },
#   sf_df = { sdf <- as.data.frame( sf::st_coordinates( mp )) },
#   sfh = { lst <- sfheaders:::rcpp_sfg_multipolygon_coordinates( mp ) },
#   #sfh = { df <- sfheaders:::rcpp_sfg_to_df( mp ) },
#   #sfh_c = { mat <- sfheaders:::rcpp_sfg_coordinates( mp ) },
#   #sfh_l = { lst <- sfheaders:::rcpp_sfg_coordinate_lists( mp ) },
#   times = 5
# )
