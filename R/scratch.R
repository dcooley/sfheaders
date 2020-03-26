#
# library(Rcpp)
#
#
# ## collapsing into a list based on the number of coordinates in the
# ## given SFC
#
# df <- data.frame(
#   id = c(1,1,2,2)
#   , x = 1:4
#   , y = 1:4
#   , val = letters[1:4]
# )
#
# res <- sf_linestring(df, x = "x", y = "y", keep = T, linestring_id = "id")
#
# res <- sfheaders:::rcpp_sf_to_df2(
#   df
#   , c("x","y")
#   , NULL
#   , NULL
#   , "id"
#   , NULL
#   , NULL
#   , NULL
#   , "val" ## list columns
#   , FALSE
#   , TRUE
#   , "LINESTRING"
# )
#
# str( res )
#
# ## can I add an attribute to an SEXP?
#
# library(Rcpp)
#
# cppFunction(
#   code = '
#     void attach_attribute( SEXP x, SEXP n, SEXP attr ) {
#       Rf_setAttrib( x, n, attr );
#     }
#   '
# )
#
# x <- 1:5
# n <- c("hello","world")
# a <- "world"
#
# attach_attribute(x, n, a)
# x
#
# str( x )
#
