
[![Travis build
status](https://travis-ci.com/dcooley/sfheaders.svg?branch=master)](https://travis-ci.com/dcooley/sfheaders)
[![Coverage
status](https://codecov.io/gh/dcooley/sfheaders/branch/master/graph/badge.svg)](https://codecov.io/github/dcooley/sfheaders?branch=master)
![downloads](http://cranlogs.r-pkg.org/badges/grand-total/sfheaders)
[![CRAN RStudio mirror
downloads](http://cranlogs.r-pkg.org/badges/sfheaders)](https://CRAN.R-project.org/package=sfheaders)

## Another spatial library?

Yep. In a few of my other libraries I’ve made use of `sf` objects, but
without importing the `sf` library itself. This is by design because
`sf` is quite a ‘heavy’ library.

Therefore I’ve written / copied these methods for constructing the `sf`
objects across a few different libraries.

So I thought it would be useful to have these in one place. And here
they are.

## Does it really make `sf` objects?

Yes and No. 

These functions do not perform any validity checks on the geometries.
Nor do they set Coordinate Reference Systems, EPSG, PROJ4 or precision
attributes.

What they do is convert R and Rcpp objects (vectors, matrices and
data.frames) into the correct `sf` class structure, so you can then
assign these values yourself.

## Are there any catches?

Yes. Your data has to be ordered before using these functions.

## Where are the examples?

They’re on the
[website](https://dcooley.github.io/sfheaders/articles/examples.html).
GO NOW\!

(however, here’s a taster)

``` r

df <- data.frame(
  id = c(1,1,1,1,1,2,2,2,2,2)
  , x = c(1,2,2,1,1,3,4,4,3,3)
  , y = c(1,1,2,2,1,3,3,4,4,3)
)

sfheaders::sf_linestring( df, linestring_id = "id" )

# Simple feature collection with 2 features and 1 field
# geometry type:  LINESTRING
# dimension:      XY
# bbox:           xmin: 1 ymin: 1 xmax: 4 ymax: 4
# epsg (SRID):    NA
# proj4string:    NA
#   id                       geometry
# 1  1 LINESTRING (1 1, 2 1, 2 2, ...
# 2  2 LINESTRING (3 3, 4 3, 4 4, ...

sfheaders::sf_polygon( df, polygon_id = "id" )

# Simple feature collection with 2 features and 1 field
# geometry type:  POLYGON
# dimension:      XY
# bbox:           xmin: 1 ymin: 1 xmax: 4 ymax: 4
# epsg (SRID):    NA
# proj4string:    NA
#   id                       geometry
# 1  1 POLYGON ((1 1, 2 1, 2 2, 1 ...
# 2  2 POLYGON ((3 3, 4 3, 4 4, 3 ...
```
