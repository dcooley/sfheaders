#
#
#
# df <- data.frame( x = 1:12, y = 1:12, z = 13:24, id = c(rep(1,6), rep(2,6)))
#
# sfg_line <- sfg_linestring( obj = df, x = "x", y = "y" )
# sfg_poly <- sfg_polygon( df, x = "x", y = "y", linestring_id = "id" )
#
#
# df <- data.frame(
#   polygon_id = c(rep(1, 5), rep(2, 10))
#   , line_id = c(rep(1, 10), rep(2, 5))
#   , x = c(0,0,1,1,0,2,2,5,5,2,3,3,4,4,3)
#   , y = c(0,1,1,0,0,2,5,5,2,2,3,4,4,3,3)
#   , z = c(1)
#   , m = c(1)
# )
#
# sfg_multipoly <- sfg_multipolygon(
#   df, x = "x", y = "y", polygon_id = "polygon_id", linestring_id = "line_id"
# )
#
# sfheaders:::rcpp_mat_to_mat( sfg_line )     ## adds an 'id' vector
# sfheaders:::rcpp_listMat_to_mat( sfg_poly ) ## adds two 'id' vectors - the inner-most is the unique-per-matrix one
# sfheaders:::rcpp_listListMat_to_mat( sfg_multipoly ) ## adds three 'id' vectors. The inner-most is the unique-per-matrix one
# ## and the outer-most is the polygon_id, and the second one is the line_id
#
# ## using this sort of id-ing we can use the MATRIX_ID, LIST_MATRIX_ID and LIST_LIST_MATRIX_ID columns
# ## like what I've set up.
#
#
#
#
