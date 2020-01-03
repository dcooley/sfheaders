
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

