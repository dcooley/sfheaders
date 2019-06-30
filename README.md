
# sfheaders

## Another spatial library?

Yep. In a few of my other libraries I’ve made use of `sf` objects, but
without importing the `sf` library itself. This is by design because
`sf` is quite a ‘heavy’ library.

Therefore I’ve written / copied these methods for constructing the `sf`
objects across a few different libraries.

So I thought it would be useful to have these in one place. And here
they are (or will be, when it’s finished).

## Can I use these methods too?

Yep

TODO: how to use.

### sfg

#### from R

``` r

df <- data.frame(
  x = 1:5
  , y = 5:1
)

to_polygon( df )
# [[1]]
#      x y
# [1,] 1 5
# [2,] 2 4
# [3,] 3 3
# [4,] 4 2
# [5,] 5 1
# 
# attr(,"class")
# [1] "XY"      "POLYGON" "sfg"
```

#### from C++

there are various overloaded functions for each `sfg` type

  - `sfheaders::sfg::to_point()`
  - `sfheaders::sfg::to_multipoint()`
  - `sfheaders::sfg::to_linestring()`
  - `sfheaders::sfg::to_multilinestring()`
  - `sfheaders::sfg::to_polygon()`
  - `sfheaders::sfg::to_multipolygon()`

<!-- end list -->

``` r
library(Rcpp)
# Warning: package 'Rcpp' was built under R version 3.5.2
library(sf) ## for print
# Warning: package 'sf' was built under R version 3.5.2
# Linking to GEOS 3.6.1, GDAL 2.1.3, PROJ 4.9.3

cppFunction(
  includes = '
    #include "sfheaders/sfg/sfg.hpp"
  ',
  code = '
    SEXP a_polygon( Rcpp::DataFrame df ) {
      return sfheaders::sfg::to_polygon( df );
    }
  ',
  depends = "sfheaders"
)

a_polygon( df )
# POLYGON ((1 5, 2 4, 3 3, 4 2, 5 1))
```

``` r
cppFunction(
  includes = '
    #include "sfheaders/sfg/sfg.hpp"
  ',
  code = '
    SEXP a_polygon( Rcpp::DataFrame df, Rcpp::StringVector geometry_columns ) {
      return sfheaders::sfg::to_polygon( df, geometry_columns );
    }
  ',
  depends = "sfheaders"
)

a_polygon( df, c("x","y") )
# POLYGON ((1 5, 2 4, 3 3, 4 2, 5 1))

a_polygon( df, c("y", "x") )
# POLYGON ((5 1, 4 2, 3 3, 2 4, 1 5))
```

``` r
cppFunction(
  includes = '
    #include "sfheaders/sfg/sfg.hpp"
  ',
  code = '
    SEXP a_polygon( SEXP x, SEXP geometry_columns ) {
      return sfheaders::sfg::to_polygon( x, geometry_columns );
    }
  ',
  depends = "sfheaders"
)

a_polygon( df, c("x","y") )
# POLYGON ((1 5, 2 4, 3 3, 4 2, 5 1))

a_polygon( df, c("y", "x") )
# POLYGON ((5 1, 4 2, 3 3, 2 4, 1 5))
```

``` r

cppFunction(
  includes = '
    #include "sfheaders/sfg/sfg.hpp"
  ',
  code = '
    SEXP a_polygon( SEXP df, std::string geom_type ) {
      return sfheaders::sfg::to_sfg( df, geom_type );
    }
  ',
  depends = "sfheaders"
)

a_polygon( df, "POLYGON" )
# POLYGON ((1 5, 2 4, 3 3, 4 2, 5 1))
```

### sfc

``` r
to_points( matrix(c(0,1,2,3,4,5), ncol = 2 ) )
# Geometry set for 3 features 
# geometry type:  POINT
# dimension:      XY
# bbox:           xmin: 0 ymin: 3 xmax: 2 ymax: 5
# epsg (SRID):    NA
# proj4string:    NA
# POINT (0 3)
# POINT (1 4)
# POINT (2 5)

to_multipoints( matrix(c(0,1,2,3,4,5), ncol = 2 ) )
# Geometry set for 1 feature 
# geometry type:  MULTIPOINT
# dimension:      XY
# bbox:           xmin: 0 ymin: 3 xmax: 2 ymax: 5
# epsg (SRID):    NA
# proj4string:    NA
# MULTIPOINT (0 3, 1 4, 2 5)

# n <- 1e7
# df <- data.frame(
#   id = rep(1:(n / 2), each = 2),
#   x = rnorm( n ),
#   y = rnorm( n ),
#   z = rnorm( n )
# )
# 
# system.time({
#   res <- to_linestrings( df, linestring_id = "id" )
# })
# 
# res
# 
# 
# 
# to_multipoints( df )
# to_multipoints( df, x = "x", y = "y", multipoint_id = "id" )
```
