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

# df <- data.frame(
#   x = NA_real_
#   , y = NA_real_
# )
#
# m <- as.matrix( df )
#
# sfheaders::sfc_point( df )
# sfheaders::sfc_point( m )
#
# sfheaders::sfc_linestring( df )
# sfheaders::sfc_linestring( m )
#
# sf::st_sfc( sf::st_linestring( x = m ) )
#
# df <- data.frame(
#   x = NA_real_
#   , y = 1
# )
#
# m <- as.matrix( df )
#
# sfheaders::sfc_point( df )
# sfheaders::sfc_point( m )
#
# sfheaders::sfc_linestring( df )
# sfheaders::sfc_linestring( m )  ## updating by reference
#
# m <- as.matrix( df )
#
# sf::st_sfc( sf::st_point( x = m[1, ] ) )
# sf::st_sfc( sf::st_linestring( x = m ) )




