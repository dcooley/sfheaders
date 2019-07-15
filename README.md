
[![Travis build
status](https://travis-ci.com/dcooley/sfheaders.svg?branch=master)](https://travis-ci.com/dcooley/sfheaders)
[![Coverage
status](https://codecov.io/gh/dcooley/sfheaders/branch/master/graph/badge.svg)](https://codecov.io/github/dcooley/sfheaders?branch=master)

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

### sfg

#### from R

``` r

df <- data.frame(
  x = 1:5
  , y = 5:1
)

sfg_polygon( df )
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

there are various overloaded functions for each `sfg` and `sfc` type

  - `sfheaders::sfg::sfg_point()`

  - `sfheaders::sfg::sfg_multipoint()`

  - `sfheaders::sfg::sfg_linestring()`

  - `sfheaders::sfg::sfg_multilinestring()`

  - `sfheaders::sfg::sfg_polygon()`

  - `sfheaders::sfg::sfg_multipolygon()`

  - `sfheaders::sfc::sfc_point()`

  - `sfheaders::sfc::sfc_multipoint()`

  - `sfheaders::sfc::sfc_linestring()`

  - `sfheaders::sfc::sfc_multilinestring()`

  - `sfheaders::sfc::sfc_polygon()`

  - `sfheaders::sfc::sfc_multipolygon()`

<!-- end list -->

``` r
library(Rcpp)
# Warning: package 'Rcpp' was built under R version 3.5.2
library(sfheaders)
# library(sf) ## for print

cppFunction(
  includes = '
    #include "sfheaders/sfg/sfg.hpp"
  ',
  code = '
    SEXP a_polygon( Rcpp::DataFrame df ) {
      return sfheaders::sfg::sfg_polygon( df );
    }
  ',
  depends = "sfheaders"
)

a_polygon( df )
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

``` r
cppFunction(
  includes = '
    #include "sfheaders/sfg/sfg.hpp"
  ',
  code = '
    SEXP a_polygon( Rcpp::DataFrame df, Rcpp::StringVector geometry_columns ) {
      return sfheaders::sfg::sfg_polygon( df, geometry_columns );
    }
  ',
  depends = "sfheaders"
)

a_polygon( df, c("x","y") )
# [[1]]
#      [,1] [,2]
# [1,]    1    5
# [2,]    2    4
# [3,]    3    3
# [4,]    4    2
# [5,]    5    1
# 
# attr(,"class")
# [1] "XY"      "POLYGON" "sfg"

a_polygon( df, c("y", "x") )
# [[1]]
#      [,1] [,2]
# [1,]    5    1
# [2,]    4    2
# [3,]    3    3
# [4,]    2    4
# [5,]    1    5
# 
# attr(,"class")
# [1] "XY"      "POLYGON" "sfg"
```

``` r
cppFunction(
  includes = '
    #include "sfheaders/sfg/sfg.hpp"
  ',
  code = '
    SEXP a_polygon( SEXP x, SEXP geometry_columns ) {
      return sfheaders::sfg::sfg_polygon( x, geometry_columns );
    }
  ',
  depends = "sfheaders"
)

a_polygon( df, c("x","y") )
# [[1]]
#      [,1] [,2]
# [1,]    1    5
# [2,]    2    4
# [3,]    3    3
# [4,]    4    2
# [5,]    5    1
# 
# attr(,"class")
# [1] "XY"      "POLYGON" "sfg"

a_polygon( df, c("y", "x") )
# [[1]]
#      [,1] [,2]
# [1,]    5    1
# [2,]    4    2
# [3,]    3    3
# [4,]    2    4
# [5,]    1    5
# 
# attr(,"class")
# [1] "XY"      "POLYGON" "sfg"
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

### sfc

``` r
sfc_point( df )
# [[1]]
# [1] 1 5
# attr(,"class")
# [1] "XY"    "POINT" "sfg"  
# 
# [[2]]
# [1] 2 4
# attr(,"class")
# [1] "XY"    "POINT" "sfg"  
# 
# [[3]]
# [1] 3 3
# attr(,"class")
# [1] "XY"    "POINT" "sfg"  
# 
# [[4]]
# [1] 4 2
# attr(,"class")
# [1] "XY"    "POINT" "sfg"  
# 
# [[5]]
# [1] 5 1
# attr(,"class")
# [1] "XY"    "POINT" "sfg"  
# 
# attr(,"class")
# [1] "sfc_POINT" "sfc"      
# attr(,"crs")
# $epsg
# [1] NA
# 
# $proj4string
# [1] NA
# 
# attr(,"class")
# [1] "crs"
# attr(,"precision")
# [1] 0
# attr(,"n_empty")
# [1] 0
# attr(,"bbox")
# xmin ymin xmax ymax 
#    1    1    5    5 
# attr(,"class")
# [1] "bbox"

sfc_multipoint( df )
# [[1]]
#      x y
# [1,] 1 5
# [2,] 2 4
# [3,] 3 3
# [4,] 4 2
# [5,] 5 1
# attr(,"class")
# [1] "XY"         "MULTIPOINT" "sfg"       
# 
# attr(,"class")
# [1] "sfc_MULTIPOINT" "sfc"           
# attr(,"crs")
# $epsg
# [1] NA
# 
# $proj4string
# [1] NA
# 
# attr(,"class")
# [1] "crs"
# attr(,"precision")
# [1] 0
# attr(,"n_empty")
# [1] 0
# attr(,"bbox")
# xmin ymin xmax ymax 
#    1    1    5    5 
# attr(,"class")
# [1] "bbox"

sfc_polygon( df )
# [[1]]
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
# 
# attr(,"class")
# [1] "sfc_POLYGON" "sfc"        
# attr(,"crs")
# $epsg
# [1] NA
# 
# $proj4string
# [1] NA
# 
# attr(,"class")
# [1] "crs"
# attr(,"precision")
# [1] 0
# attr(,"n_empty")
# [1] 0
# attr(,"bbox")
# xmin ymin xmax ymax 
#    1    1    5    5 
# attr(,"class")
# [1] "bbox"
```

``` r

cppFunction(
  includes = '
    #include "sfheaders/sfc/sfc.hpp"
  ',
  code = '
    SEXP a_polygon( SEXP df ) {
      return sfheaders::sfc::sfc_polygon( df );
    }
  ',
  depends = "sfheaders",
  plugins = "cpp11"
)

a_polygon( df )
# [[1]]
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
# 
# attr(,"class")
# [1] "sfc_POLYGON" "sfc"        
# attr(,"crs")
# $epsg
# [1] NA
# 
# $proj4string
# [1] NA
# 
# attr(,"class")
# [1] "crs"
# attr(,"precision")
# [1] 0
# attr(,"n_empty")
# [1] 0
# attr(,"bbox")
# xmin ymin xmax ymax 
#    1    1    5    5 
# attr(,"class")
# [1] "bbox"
```

``` r

cppFunction(
  includes = '
    #include "sfheaders/sfc/sfc.hpp"
  ',
  code = '
    SEXP a_polygon( SEXP df, SEXP geometry_columns ) {
      return sfheaders::sfc::sfc_polygon( df, geometry_columns );
    }
  ',
  depends = "sfheaders",
  plugins = "cpp11"
)

a_polygon( df, c("x","y") )
# [[1]]
# [[1]]
#      [,1] [,2]
# [1,]    1    5
# [2,]    2    4
# [3,]    3    3
# [4,]    4    2
# [5,]    5    1
# 
# attr(,"class")
# [1] "XY"      "POLYGON" "sfg"    
# 
# attr(,"class")
# [1] "sfc_POLYGON" "sfc"        
# attr(,"crs")
# $epsg
# [1] NA
# 
# $proj4string
# [1] NA
# 
# attr(,"class")
# [1] "crs"
# attr(,"precision")
# [1] 0
# attr(,"n_empty")
# [1] 0
# attr(,"bbox")
# xmin ymin xmax ymax 
#    1    1    5    5 
# attr(,"class")
# [1] "bbox"
```

``` r

df <- data.frame(
  id = c( rep(1, 5), rep(2, 5) )
  , x = 1:10
  , y = 1:10
)

cppFunction(
  includes = '
    #include "sfheaders/sfc/sfc.hpp"
  ',
  code = '
    SEXP a_polygon( SEXP df, SEXP geometry_columns ) {
      return sfheaders::sfc::sfc_polygon( df, geometry_columns );
    }
  ',
  depends = "sfheaders",
  plugins = "cpp11"
)

a_polygon( df, c("x","y") )
# [[1]]
# [[1]]
#       [,1] [,2]
#  [1,]    1    1
#  [2,]    2    2
#  [3,]    3    3
#  [4,]    4    4
#  [5,]    5    5
#  [6,]    6    6
#  [7,]    7    7
#  [8,]    8    8
#  [9,]    9    9
# [10,]   10   10
# 
# attr(,"class")
# [1] "XY"      "POLYGON" "sfg"    
# 
# attr(,"class")
# [1] "sfc_POLYGON" "sfc"        
# attr(,"crs")
# $epsg
# [1] NA
# 
# $proj4string
# [1] NA
# 
# attr(,"class")
# [1] "crs"
# attr(,"precision")
# [1] 0
# attr(,"n_empty")
# [1] 0
# attr(,"bbox")
# xmin ymin xmax ymax 
#    1    1   10   10 
# attr(,"class")
# [1] "bbox"
```

``` r

cppFunction(
  includes = '
    #include "sfheaders/sfc/sfc.hpp"
  ',
  code = '
    SEXP a_polygon( SEXP df, SEXP geometry_columns, SEXP polygon_id, SEXP linestring_id ) {
      return sfheaders::sfc::sfc_polygon( df, geometry_columns, polygon_id, linestring_id );
    }
  ',
  depends = "sfheaders",
  plugins = "cpp11"
)

a_polygon( df, c("x","y"), "id", NULL )
# [[1]]
# [[1]]
#      [,1] [,2]
# [1,]    1    1
# [2,]    2    2
# [3,]    3    3
# [4,]    4    4
# [5,]    5    5
# 
# [[2]]
#      [,1] [,2]
# [1,]    6    6
# [2,]    7    7
# [3,]    8    8
# [4,]    9    9
# [5,]   10   10
# 
# attr(,"class")
# [1] "XY"      "POLYGON" "sfg"    
# 
# attr(,"class")
# [1] "sfc_POLYGON" "sfc"        
# attr(,"crs")
# $epsg
# [1] NA
# 
# $proj4string
# [1] NA
# 
# attr(,"class")
# [1] "crs"
# attr(,"precision")
# [1] 0
# attr(,"n_empty")
# [1] 0
# attr(,"bbox")
# xmin ymin xmax ymax 
#    1    1   10   10 
# attr(,"class")
# [1] "bbox"
```

``` r
# n <- 1e7
# df <- data.frame(
#   id = rep(1:(n / 2), each = 2),
#   x = rnorm( n ),
#   y = rnorm( n ),
#   z = rnorm( n )
# )
# 
# system.time({
#   res <- sfc_linestring( df, linestring_id = "id" )
# })
# 
# res
# 
# 
# 
# sfc_multipoint( df )
# sfc_multipoint( df, x = "x", y = "y", multipoint_id = "id" )
```
