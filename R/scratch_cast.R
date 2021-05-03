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
# sf_l <- sfheaders::sf_linestring(
#   obj = df
#   , x = "x"
#   , y = "y"
#   , linestring_id = "id2"
#   , keep = TRUE
#   , list_columns = "val"
# )
#
#
# #library(sf)
#
# sf <- rbind( sf_mp[, "val"], sf_p[, c("val")], sf_l[, c("val")] )
#
# res <- sfheaders::sf_cast( sf, "POLYGON", list_columns = c("val") )
#
# str( sf )
# str( res )
#
# geometries:::gm_dimensions( sf[1, ]$geometry )
# unclass( sf[1, ][['geometry']] )
# unclass( sf[1, ][['geometry']][[1]] )
# unclass( sf[1, ][['geometry']][[1]][[1]] )
# unclass( sf[1, ][['geometry']][[1]][[1]][[1]] )
#
# geometries:::gm_dimensions( sf[2, ]$geometry )
# unclass( sf[2, ][['geometry']] )
# unclass( sf[2, ][['geometry']][[1]] )
# unclass( sf[2, ][['geometry']][[1]][[1]] )
#
#
#
# geometries:::gm_dimensions( sf[1, ][['geometry']] )
# geometries:::gm_dimensions( sf[1, ][['val']] )
# ## MULTIPOLYGON: 4
# ## POLYGON: 2
# ## LINESTRING: 1
#
# ## MLUTIPOLYGON -> LINESTRING
#
# ## 4 --> 2
# str( sf[1, ]$val ) ## MULTIPOLYGON
# str( sf[2, ]$val ) ## POLYGON
#
# ## MULTIPOLYGON -> LINESTRING
# geometries:::rcpp_nest( sf[1, ]$val, 2 )  ## need to go down 2 levels
#
# ## POLYGON -> LINESTRING
# geometries:::gm_dimensions( sf[2, ][['geometry']] )
# geometries:::gm_dimensions( sf[2, ][['val']] )
# geometries:::gm_dimensions( sf[2, ]$val )
#
# ## 2 --> 1
# str( sf[2, ]$val )
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
