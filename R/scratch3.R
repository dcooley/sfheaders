#
# library(mapdeck)
# library(sf)
#
# sf <- mapdeck::roads
#
# df <- sfheaders::sf_to_df( sf, fill = TRUE )
#
# res <- sfheaders::sf_linestring(
#   df
#   , x = "x"
#   , y = "y"
#   , linestring_id = "linestring_id"
#   , keep = TRUE
#   )
# res
#
# res <- sfheaders::sf_linestring(
#   df
#   , x = 18
#   , y = 19
#   , linestring_id = 17
#   , keep = TRUE
# )
# res
#
# m <- as.matrix( df[, c("sfg_id", "linestring_id", "x", "y")])
#
# res <- sfheaders::sf_linestring(
#   m
#   , x = 3
#   , y = 4
#   , linestring_id = 2
#   , keep = TRUE
# )
# res
#
# res <- sfheaders::sf_linestring(
#   m
#   , x = "x"
#   , y = "y"
#   , linestring_id = "linestring_id"
#   , keep = TRUE
# )
# res
