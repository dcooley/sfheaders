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
# # res
#
#
# library(sf)
#
# df <- data.frame(
#   ml_id = c(1,1,1,1,1,1,1,1,2,2,2,2,2)
#   , l_id = c(1,1,1,2,2,3,3,3,1,1,1,2,2)
#   , x = rnorm(13)
#   , y = rnorm(13)
#   , z = rnorm(13)
#   , m = rnorm(13)
# )
#
#
# sf_multilinestring( obj = df, x = "x", y = "y", multilinestring_id = "ml_id", linestring_id = "x", keep = T)
# sf_multilinestring( obj = df, x = "x", y = "y", z = "z", linestring_id = "x")
# sf_multilinestring( obj = df, x = "x", y = "y", z = "z", m = "m")
#
# sf_multilinestring( obj = df, x = 3, y = 4)
# sf_multilinestring( obj = df, x = 3, y = 4, z = 5)
# sf_multilinestring(
#   obj = df
#   , x = 3
#   , y = 4
#   , z = 5
#   , m = 6
#   , keep = T
#   , multilinestring_id = 1
#   , linestring_id = 2
#   )

#
# sf_multilinestring( obj = df, multilinestring_id = "ml_id", linestring_id = "l_id" )
# sf_multilinestring( obj = df, multilinestring_id = 1, linestring_id = 2 )

#
# df <- data.frame(
#   ml_id = c(1,1,1,1,1,1,1,1,2,2,2,2,2)
#   , l_id = c(1,1,1,2,2,3,3,3,1,1,1,2,2)
#   , x = rnorm(13)
#   , y = rnorm(13)
#   , z = rnorm(13)
#   , m = rnorm(13)
# )
#
# sf_multilinestring(
#   obj = df
#   , x = 2
#   , y = 3
#   , z = 4
#   , m = 5
#   , multilinestring_id = 1
#   , linestring_id = 2
#   , keep = T
#   )

# df <- data.frame(
#   ml_id = c(1,1,1,1,1,1,1,1,1,2,2,2,2,2,2)
#   , l_id = c(1,1,1,2,2,2,3,3,3,1,1,1,2,2,2)
#   , x = rnorm(15)
#   , y = rnorm(15)
#   , z = rnorm(15)
#   , m = rnorm(15)
# )
#
# sf_polygon(
#   obj = df
#   , x = "x"
#   , y = "y"
#   , z = "z"
#   , polygon_id = "ml_id"
#   , linestring_id = "l_id"
#   , keep = TRUE
#   )

# df <- data.frame(
#   id1 = c(1,1,1,1,1,2,2,2,2,2)
#   , id2 = c(1,1,1,1,1,1,1,1,1,1)
#   , x = c(0,0,1,1,0,1,1,2,2,1)
#   , y = c(0,1,1,0,0,1,2,2,1,1)
# )
#
# df$val <- rnorm( nrow(df ) )
#
# sf_multipolygon( df, x = "x", y = "y", polygon_id = "id1", linestring_id = "id1", keep = TRUE)
