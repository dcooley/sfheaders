#
#
# df <- data.frame(
#   id1 = c(1,1,1,1,1,1,1)
#   , id2 = c(1,1,2,2,2,2,2)
#   , x = c(1,0,1,1,2,2,1)
#   , y = c(0,0,1,2,2,1,1)
# )
#
# sfc_pt <- sfheaders::sfc_point( df, x= "x", y = "y" )
# sfc_ls <- sfheaders::sfc_linestring(
#   df
#   , x = "x"
#   , y = "y"
#   , linestring_id = "id2"
#   )
#
# sf <- sf::st_sf( geometry = c( sfc_pt, sfc_ls ) )
#
# df <- sfheaders::sfc_to_df( sf$geometry )
#
