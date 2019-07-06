#
# library(sfheaders)
# library(data.table)
# library(sf)
#
# coords <- sf::st_coordinates( mapdeck::roads )
#
# head( coords )
#
# df <- as.data.frame( coords )
# dt <- as.data.table( coords )
#
# head( df )
#
# sfheaders::sfc_linestring( obj = dt, linestring_id = "L1")
#
# library(dplyr)
#
# sfheaders::sfc_linestring(obj = dt, x = "X", y = "Y", linestring_id = "L1")
#
# dt[
#   , .(geometry = sfheaders::sfc_linestring(.SD, x = "X", y = "Y", linestring_id = "L1") )
# ]
#
# df <- df[ df$L1 %in% c(1,2), ]
#
# df %>%
#   summarise( geometry = sfheaders::sfc_linestring(obj = ., x = "X", y = "Y", linestring_id = "L1") )
#
#
# mp1 <- sf::st_multipoint( x = matrix(1:4, ncol = 2))
# mp2 <- sf::st_multipoint( x = matrix(4:1, ncol = 2))
#
# sfc <- sf::st_sfc( list( mp1, mp2 ) )
#
#
# str( sfc )
# sfc[[1]]
#
# attributes( sfc ) <- NULL
# sfc[[1]]
#
#
# m <- matrix(c(0,0,0,0,1,1), ncol = 3, byrow = T)
# sfheaders:::rcpp_to_multipoints( m, c(1,2), c(0) )
#
# m <- matrix(c(0,0,0,0,1,1,1,1,1), ncol = 3, byrow = T)
# sfheaders:::rcpp_sfc_multipoint( m, c(1,2), c(0) )
#
#
# m <- matrix(c(0,0,0,0,1,1,1,1,1), ncol = 3, byrow = T)
# sfheaders:::rcpp_sfc_multilinestring( m, c(1,2), c(0), 0 )
#
# ml1 <- sf::st_multilinestring(
#   x = list(
#     matrix(c(0,0,1,1), ncol = 2)
#   )
# )
#
# ml2 <- sf::st_multilinestring(
#   x = list(
#     matrix(c(1,1), ncol = 2)
#   )
# )
#
# sfc <- sf::st_sfc( list(ml1, ml2) )
#
# str( sfc )
#
#
