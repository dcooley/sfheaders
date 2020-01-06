
#
# library(microbenchmark)
#
# roads <- mapdeck::roads
#
# microbenchmark(
#   sf = { coords <- sf::st_coordinates( roads ) },
#   sfh1 = { df1 <- sfheaders::sf_to_df( roads ) },
#   sfh2 = { df2 <- sfheaders::sf_to_df( roads, fill = TRUE ) },
#   times = 5
# )

# Unit: milliseconds
# expr      min       lq     mean   median       uq       max neval
# sf   75.97844 78.66116 82.20135 79.41222 86.19913  90.75579     5
# sfh1 29.86396 30.03754 48.84383 31.88453 32.77615 119.65698     5
# sfh2 35.61506 41.33124 42.70384 42.73622 45.17970  48.65700     5





#
# sf[ sf$EZI_RDNAME == "MAIN YARRA TRAIL", ]
#
# mapdeck(
#   style = mapdeck_style("dark")
# ) %>%
#   add_sf(
#     data = sf[ sf$EZI_RDNAME == "MAIN YARRA TRAIL", ]
#   )
#
#
# library(mapdeck)
#
# sf <- mapdeck::roads
# df <- sfheaders::sf_to_df( sf[1:250, ], fill = T )
#
# head( df )
#
# nrow( df )
#
# mapdeck(
#   style = mapdeck_style("dark")
# ) %>%
#   add_scatterplot(
#     data = df
#     , lon = "x"
#     , lat = "y"
#     , fill_colour = "EZI_RDNAME"
#     , tooltip = "EZI_RDNAME"
#     , radius = 25
#   )
#
# df[ df$EZI_RDNAME == "MAIN YARRA TRAIL", ]
#
#
#
#
#



# df <- data.frame(
#   id = c(1,1,2,2,2)
#   , val = as.POSIXct( c("2020-01-01 00:00:01") )
#   , x = c(1:5)
#   , y = c(5:1)
# )
#
# sf <- sfheaders::sf_linestring(obj = df, linestring_id = "id", x = "x", y = "y")
#
# sf <- merge( sf, unique( df[, c("id","val")] ), by = "id" )
#
# df <- sfheaders::sf_to_df( sf, fill = TRUE )
#
# str( df )
