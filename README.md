# sfheaders


## Another spatial library?

Yep. In a few of my other libraries I've made use of `sf` objects, but without importing the `sf` library itself. This is by design because `sf` is quite a 'heavy' library. 

Therefore I've written / copied these methods for constructing the `sf` objects across a few different libraries. 

So I thought it would be useful to have these in one place. And here they are (or will be, when it's finished).



## Can I use these methods too?

Yep

TODO: how to use.


### sfg

#### from R

```r

df <- data.frame(
  x = 1:5
  , y = 5:1
)

to_polygon( df )
# POLYGON ((1 5, 2 4, 3 3, 4 2, 5 1))
```

#### from C++

there are various `sfheaders::sfg::to_polygon()` overloaded functions you can call

```r
library(Rcpp)
library(sf) ## for print

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

```r
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

```r
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


```r

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






