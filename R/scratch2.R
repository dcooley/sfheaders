# df <- data.frame(
#   id = c(1,1,1,2,2,2)
#   , x = c(1,1,1,2,2,2)
#   , y = c(3,3,3,4,4,4)
# )
#
#
# pt <- sfheaders:::sfg_point(c(1,2))
# mp <- sfheaders:::sfg_multipoint( df )
# ls <- sfheaders::sfg_linestring(df, x = "x", y = "y")
# mls <- sfheaders::sfg_multilinestring(obj = df, linestring_id = "id")
#
# m <- cbind( matrix( 1:24, ncol = 2 ), c(rep(1, 6), rep(2, 6) ) )
# p <- sfg_polygon( obj = m, x = 1, y = 2, linestring_id = 3 )
#
# sfheaders:::rcpp_sfg_coordinates( pt )
# sfheaders:::rcpp_sfg_coordinates( mp )
# sfheaders:::rcpp_sfg_coordinates( ls )
# sfheaders:::rcpp_sfg_coordinates( mls )
# sfheaders:::rcpp_sfg_coordinates( p )
