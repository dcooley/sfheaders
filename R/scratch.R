#
# df <- data.frame( x = 1:12, y = 1:12, z = 13:24, id = c(rep(1,6), rep(2,6)))
#
# sfg_pt <- sfg_point( obj = df[1, ], x = "x", y = "y" )
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
# sfheaders:::rcpp_count_new_objects( sfg_pt, cast_to = "POINT" )
# sfheaders:::rcpp_count_new_objects( sfg_pt, cast_to = "MULTIPOINT" )
# sfheaders:::rcpp_count_new_objects( sfg_pt, cast_to = "LINESTRING" )
# sfheaders:::rcpp_count_new_objects( sfg_pt, cast_to = "MULTILINESTRING" )
# sfheaders:::rcpp_count_new_objects( sfg_pt, cast_to = "POLYGON" )
# sfheaders:::rcpp_count_new_objects( sfg_pt, cast_to = "MULTIPOLYGON" )
#
# sfheaders:::rcpp_count_new_objects( sfg_line, cast_to = "POINT" )
# sfheaders:::rcpp_count_new_objects( sfg_line, cast_to = "MULTIPOINT" )
# sfheaders:::rcpp_count_new_objects( sfg_line, cast_to = "LINESTRING" )
# sfheaders:::rcpp_count_new_objects( sfg_line, cast_to = "MULTILINESTRING" )
# sfheaders:::rcpp_count_new_objects( sfg_line, cast_to = "POLYGON" )
# sfheaders:::rcpp_count_new_objects( sfg_line, cast_to = "MULTIPOLYGON" )
#
# sfheaders:::rcpp_count_new_objects( sfg_poly, cast_to = "POINT" )
# sfheaders:::rcpp_count_new_objects( sfg_poly, cast_to = "MULTIPOINT" )
# sfheaders:::rcpp_count_new_objects( sfg_poly, cast_to = "LINESTRING" )
# sfheaders:::rcpp_count_new_objects( sfg_poly, cast_to = "MULTILINESTRING" )
# sfheaders:::rcpp_count_new_objects( sfg_poly, cast_to = "POLYGON" )
# sfheaders:::rcpp_count_new_objects( sfg_poly, cast_to = "MULTIPOLYGON" )
#
# sfheaders:::rcpp_count_new_objects( sfg_multipoly, cast_to = "POINT" )
# sfheaders:::rcpp_count_new_objects( sfg_multipoly, cast_to = "MULTIPOINT" )
# sfheaders:::rcpp_count_new_objects( sfg_multipoly, cast_to = "LINESTRING" )
# sfheaders:::rcpp_count_new_objects( sfg_multipoly, cast_to = "MULTILINESTRING" )
# sfheaders:::rcpp_count_new_objects( sfg_multipoly, cast_to = "POLYGON" )
# sfheaders:::rcpp_count_new_objects( sfg_multipoly, cast_to = "MULTIPOLYGON" )

#
# sfheaders:::rcpp_vec_to_vec( sfg_pt )
# sfheaders:::rcpp_mat_to_vec( sfg_line )
# sfheaders:::rcpp_listMat_to_vec( sfg_poly )
# sfheaders:::rcpp_listListMat_to_vec( sfg_multipoly )
#
# sfheaders:::rcpp_vec_to_mat( sfg_pt )
# sfheaders:::rcpp_mat_to_mat( sfg_line )     ## adds an 'id' vector
# sfheaders:::rcpp_listMat_to_mat( sfg_poly ) ## adds two 'id' vectors - the inner-most is the unique-per-matrix one
# sfheaders:::rcpp_listListMat_to_mat( sfg_multipoly ) ## adds three 'id' vectors. The inner-most is the unique-per-matrix one
# ## and the outer-most is the polygon_id, and the second one is the line_id
#
# sfheaders:::rcpp_vec_to_listMat( sfg_pt )
# sfheaders:::rcpp_mat_to_listMat( sfg_line )
# sfheaders:::rcpp_listMat_to_listMat( sfg_poly )
# sfheaders:::rcpp_listListMat_to_listMat( sfg_multipoly )
#
#
# sfheaders:::rcpp_vec_to_listListMat( sfg_pt )
# sfheaders:::rcpp_mat_to_listListMat( sfg_line )
# sfheaders:::rcpp_listMat_to_listListMat( sfg_poly )
# sfheaders:::rcpp_listListMat_to_listListMat( sfg_multipoly )
#
#
#
# ## using this sort of id-ing we can use the MATRIX_ID, LIST_MATRIX_ID and LIST_LIST_MATRIX_ID columns
# ## like what I've set up.
#

# df <- data.frame(
#   ml_id = c(1,1,1,1,1,1,1,1,1,2,2,2,2,2,2)
#   , l_id = c(1,1,1,2,2,2,3,3,3,1,1,1,2,2,2)
#   , x = rnorm(15)
#   , y = rnorm(15)
#   , z = rnorm(15)
#   , m = rnorm(15)
# )
#
# sfc <- sfc_polygon( obj = df, polygon_id = "ml_id", linestring_id = "l_id" )

# library(sf)
#
# nc <- sf::st_read( system.file("./shape/nc.shp", package = "sf"))
#
# sfc <- sf::st_cast( nc$geometry , "POLYGON" )

# df <- data.frame(
#   x = res[[5]]
#   , y = res[[6]]
#   , multipolygon_id = res[[2]]
#   , polygon_id = res[[3]]
#   , linestring_id = res[[4]]
# )
#

#res <- sfheaders:::rcpp_sfc_polygon_to_sfc_multipolygon( sfc )



# nc <- sf::st_read( system.file("./shape/nc.shp", package = "sf"))
#
# sfheaders:::rcpp_cast_sfc( nc$geometry, "POLYGON" )

# nc <- rbind( nc, nc, nc, nc, nc )
# nc <- rbind( nc )
# nc <- rbind( nc, nc, nc, nc, nc, nc, nc, nc, nc, nc )
# nc <- rbind( nc, nc, nc, nc, nc, nc, nc, nc, nc, nc )

# ## 50,000 MULTIPOLYGONS
# microbenchmark::microbenchmark(
#   sfh = {
#     sfh_res <- sfheaders:::rcpp_cast_sfc( nc$geometry, "POLYGON" )
#   },
#   sf = {
#     temp <- sf::st_cast( nc$geometry, "POLYGON" )
#     # sf_res <- sf::st_cast( temp, "LINESTRING" )
#   },
#   times = 10
# )

# Unit: milliseconds
# expr        min        lq      mean    median        uq       max neval
#  sfh   96.51165  102.3138  168.2939  121.3337  263.2627  280.1679    10
#   sf 2971.71354 3094.8000 3217.7323 3143.0750 3386.4805 3523.9355    10


