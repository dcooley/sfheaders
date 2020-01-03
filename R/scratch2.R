
# x <- data.frame(id = c(rep(1, 5), rep(2, 5) ) , x = 1:10, y = 10:1 )
#
# ls <- sfc_linestring( x, linestring_id = "id", x = "x", y = "y")
#
# sfheaders:::rcpp_sfc_linestring_coordinates( ls )

# library(mapdeck)
# library(sf)
#
#
# sfc <- mapdeck::roads[1:15000, ]$geometry
#
# res <- sfheaders:::rcpp_sfc_linestring_coordinates( sfc )
# coords <- sf::st_coordinates( sfc )
#
#
# library(microbenchmark)
#
# microbenchmark(
#   sfh = { res <- sfheaders:::rcpp_sfc_linestring_coordinates( sfc ) },
#   sf = { coords <- sf::st_coordinates( sfc ) },
#   times = 5
# )

# m <-   cbind(
#   c(
#     rep(1, 1e6 / 8)
#     , rep(2, 1e6 / 8)
#     , rep(3, 1e6 / 8)
#     , rep(4, 1e6 / 8)
#   )
#   , matrix(1:1e6, ncol = 2)
# )
#
# mls <- sfc_multilinestring(
#   obj = m
#   , linestring_id = 1
# )
#
# res <- sfheaders:::rcpp_sfc_multilinestring_coordinates( mls )

# df <- data.frame( x = 1:12, y = 1:12, z = 13:24, id = c(rep(1,6), rep(2,6)))
# sfg_multilinestring( df, x = "x", y = "y" )
# mls <- sfg_multilinestring( df, x = "x", y = "y", linestring_id = "id" )
#
# sfheaders:::rcpp_sfg_multilinestring_coordinates( mls )
#
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
# res <- sfheaders:::rcpp_sfg_multipolygon_coordinates( mp )
#
# df <- sfheaders:::rcpp_sfg_to_df( mp )
