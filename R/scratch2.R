#
# library(mapdeck)
#
# sf <- mapdeck::roads
# df <- sfheaders::sf_to_df( sf, fill = T )
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
#
