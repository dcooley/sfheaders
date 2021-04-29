#
#
#
# df <- data.frame(
#   x = 1:20
#   , y = 1:20
#   , val = 1:20
#   , id1 = rep(1,20)
#   , id2 = c(rep(1,10),rep(2,10))
#   , id3 = c(rep(1,5), rep(2,5), rep(1,5), rep(2,5))
# )
#
# df
#
# sf_mp <- sfheaders::sf_multipolygon(
#   obj = df
#   , x = "x"
#   , y = "y"
#   , multipolygon_id = "id1"
#   , polygon_id = "id2"
#   , linestring_id = "id3"
#   , keep = TRUE
#   , list_columns = "val"
# )
#
# sf_p <- sfheaders::sf_polygon(
#   obj = df
#   , x = "x"
#   , y = "y"
#   #  , multipolygon_id = "id1"
#   , polygon_id = "id2"
#   , linestring_id = "id3"
#   , keep = TRUE
#   , list_columns = "val"
# )
#
# library(sf)
#
# sf <- rbind( sf_mp, sf_p[, c("id1","val")] )
#
# sfheaders::sf_cast( sf, "LINESTRING", list_columns = c("val") )
#
# ## Multipolygon -> LINESTRING
# geometries:::rcpp_nest( sf[1, ]$val, 2 )  ## need to go down 2 levels
#
# ## Polygon -> LINESTRING
# geometries:::rcpp_nest( sf[2, ]$val, 1 )  ## need to go down 1 level
# geometries:::rcpp_nest( sf[2, ]$val, 1 )
#
#
# ## can do all columns at once?
# geometries:::rcpp_nest( sf[2:3, ]$val, 1 )
#
# sfheaders::sf_cast( sf[1, ], "LINESTRING" , list_columns = "val")
#
#
# lst_element <- sf[1, ]$val
#
# geometries:::rcpp_nest( lst_element, 2 )
#
#
#
#
#
