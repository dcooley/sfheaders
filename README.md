
[![R build
status](https://github.com/dcooley/sfheaders/workflows/R-CMD-check/badge.svg)](https://github.com/dcooley/sfheaders/actions)
[![Coverage
status](https://codecov.io/gh/dcooley/sfheaders/branch/master/graph/badge.svg)](https://codecov.io/github/dcooley/sfheaders?branch=master)
![downloads](http://cranlogs.r-pkg.org/badges/grand-total/sfheaders)
[![CRAN RStudio mirror
downloads](http://cranlogs.r-pkg.org/badges/sfheaders)](https://CRAN.R-project.org/package=sfheaders)

<a href="https://www.buymeacoffee.com/davecooley" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/default-yellow.png" alt="Buy Me A Coffee" style="height: 51px !important;width: 217px !important;" ></a>

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

Yes. Your data has to be ordered before coverting to `sf`.

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

df$val <- letters[df$id]

sfheaders::sf_linestring( df, x = "x", y = "y", linestring_id = "id", keep = TRUE )

# Simple feature collection with 2 features and 2 fields
# geometry type:  LINESTRING
# dimension:      XY
# bbox:           xmin: 1 ymin: 1 xmax: 4 ymax: 4
# z_range:        zmin: NA zmax: NA
# m_range:        mmin: NA mmax: NA
# epsg (SRID):    NA
# proj4string:    NA
#   id val                       geometry
# 1  1   a LINESTRING (1 1, 2 1, 2 2, ...
# 2  2   b LINESTRING (3 3, 4 3, 4 4, ...

sfheaders::sf_polygon( df, x = "x", y = "y", polygon_id = "id" , keep = TRUE )

# Simple feature collection with 2 features and 2 fields
# geometry type:  POLYGON
# dimension:      XY
# bbox:           xmin: 1 ymin: 1 xmax: 4 ymax: 4
# z_range:        zmin: NA zmax: NA
# m_range:        mmin: NA mmax: NA
# epsg (SRID):    NA
# proj4string:    NA
#   id val                       geometry
# 1  1   a POLYGON ((1 1, 2 1, 2 2, 1 ...
# 2  2   b POLYGON ((3 3, 4 3, 4 4, 3 ...
```
