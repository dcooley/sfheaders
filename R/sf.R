#' sf POINT
#'
#' constructs sf of POINT objects
#'
#' @param obj sorted vector, matrix or data.frame
#' @param x x geometry column
#' @param y y geometry column
#' @param z z geometry column
#' @param m m geometry column
#' @param keep logical indicating if the non-geometry and non-id columns should be kept.
#' if TRUE you must supply the geometry and id columns, and only the first row of
#' each geometry is kept. See Keeping Properties.
#' @inheritSection sfc_point notes
#'
#' @section Keeping Properties:
#'
#' Setting \code{keep = TRUE} will retain the first row of any columns not specified as a
#' coordinate (x, y, z, m) or an id (e.g., linestring_id, polygon_id) of the input \code{obj}.
#'
#' The \code{sf_*} functions assume the input \code{obj} is a long data.frame / matrix,
#' where any properties are repeated down the table for the same geometry.
#'
#'
#' @return \code{sf} object of POINT geometries
#'
#' @examples
#'
#' x <- c(1:3)
#' sf_point( x )
#'
#' x <- matrix( c(1:10) , ncol = 2 )
#' sf_point( x )
#'
#' x <- setNames( as.data.frame( x ), c("x","y") )
#' sf_point( x )
#' sf_point( obj = x, x = "x", y = "y" )
#' sf_point( obj = x, x = "y", y = "x" )
#'
#' # keeping properties
#' x$val <- letters[1:5]
#' sf_point( x, x = "x", y = "y", keep = TRUE )
#'
#' @export
sf_point <- function(
  obj,
  x = NULL,
  y = NULL,
  z = NULL,
  m = NULL,
  keep = FALSE
  ) {
  geometry_columns <- c(x,y,z,m)
  return( rcpp_sf_point( obj, index_correct( geometry_columns ), keep ) )
}

#' sf MULTIPOINT
#'
#' constructs sf of MULTIPOINT objects
#'
#' @inheritParams sf_point
#' @param obj sorted matrix or data.frame
#' @inheritSection sfc_point notes
#' @inheritSection sf_point Keeping Properties
#' @param multipoint_id column of ids for multipoints
#'
#' @return \code{sf} object of MULTIPOINT geometries
#' @examples
#'
#' x <- matrix( c(1:4), ncol = 2 )
#' sf_multipoint( x )
#'
#' x <- data.frame( id = 1:2, x = 1:2, y = 2:1 )
#' sf_multipoint( x )
#' sf_multipoint( x, x = "x", y = "y" )
#' sf_multipoint( x, x = "y", y = "x" )
#' sf_multipoint( x, multipoint_id = "id", x = "x", y = "y")
#'
#' @export
sf_multipoint <- function(
  obj,
  x = NULL,
  y = NULL,
  z = NULL,
  m = NULL,
  multipoint_id = NULL,
  keep = FALSE
  ) {
  geometry_columns <- c(x,y,z,m)
  res <- rcpp_sf_multipoint(
    obj
    , index_correct( geometry_columns )
    , index_correct( multipoint_id )
    , keep
    )
  return( replace_id( res, multipoint_id ) )
}


#' sf LINESTRING
#'
#' constructs sf of LINESTRING objects
#'
#' @inheritParams sf_multipoint
#' @inheritSection sfc_point notes
#' @inheritSection sf_point Keeping Properties
#' @param linestring_id column of ids for linestrings
#'
#' @return \code{sf} object of LINESTRING geometries
#'
#' @examples
#'
#' x <- matrix( c(1:4), ncol = 2 )
#' sf_linestring( x )
#'
#' x <- data.frame( id = 1:2, x = 1:2, y = 2:1 )
#' sf_linestring( x )
#' sf_linestring( x, x = "x", y = "y" )
#' sf_linestring( x, x = "y", y = "x" )
#' sf_linestring( x, linestring_id = "id", x = "x", y = "y")
#'
#' @export
sf_linestring <- function(
  obj = NULL,
  x = NULL,
  y = NULL,
  z = NULL,
  m = NULL,
  linestring_id = NULL,
  keep = FALSE
  ) {
  geometry_columns <- c(x,y,z,m)
  res <- rcpp_sf_linestring(
    obj
    , index_correct( geometry_columns )
    ,  index_correct( linestring_id )
    , keep
    )
  return( replace_id( res, linestring_id ) )
}


#' sf MULTILINESTRING
#'
#' constructs an sf of MULTILINESTRING objects
#'
#' @inheritParams sf_linestring
#' @param multilinestring_id column of ids for multilinestrings
#' @param linestring_id column of ids for linestrings (within multilinestrings)
#'
#' @inheritSection sfc_point notes
#' @inheritSection sf_point Keeping Properties
#'
#' @return \code{sf} object of MULTILINESTRING geometries
#'
#' @examples
#'
#' m <- matrix(c(0,0,0,0,1,1), ncol = 3 )
#' sf_multilinestring( m )
#'
#' m <- matrix(c(0,0,0,0,0,1,0,1,1,1,2,2,1,2,3), ncol = 3, byrow = TRUE)
#' sf_multilinestring( obj = m )
#' sf_multilinestring( obj = m, multilinestring_id = 1 )
#' sf_multilinestring( obj = m, linestring_id = 1 )
#'
#' sf_multilinestring( obj = m, linestring_id = 1, multilinestring_id = 1 )
#'
#' sf_multilinestring( obj = m, x = 2, y = 3 )
#' sf_multilinestring( obj = m, x = 1, y = 2, z = 3 )
#' sf_multilinestring( obj = m, x = 2, y = 3, linestring_id = 1, multilinestring_id = 1 )
#'
#' df <- data.frame(
#'   ml_id = c(1,1,1,1,1,1,1,1,2,2,2,2,2)
#'   , l_id = c(1,1,1,2,2,3,3,3,1,1,1,2,2)
#'   , x = rnorm(13)
#'   , y = rnorm(13)
#'   , z = rnorm(13)
#'   , m = rnorm(13)
#' )
#'
#' sf_multilinestring( obj = df, x = "x", y = "y")
#' sf_multilinestring( obj = df, x = "x", y = "y", z = "z")
#' sf_multilinestring( obj = df, x = "x", y = "y", z = "z", m = "m")
#'
#' sf_multilinestring( obj = df, x = 3, y = 4)
#' sf_multilinestring( obj = df, x = 3, y = 4, z = 5)
#' sf_multilinestring( obj = df, x = 3, y = 4, z = 5, m = 6 )
#'
#' sf_multilinestring( obj = df, multilinestring_id = "ml_id", linestring_id = "l_id" )
#' sf_multilinestring( obj = df, multilinestring_id = 1, linestring_id = 2 )
#'
#'
#'
#' @export
sf_multilinestring <- function(
  obj = NULL,
  x = NULL,
  y = NULL,
  z = NULL,
  m = NULL,
  multilinestring_id = NULL,
  linestring_id = NULL,
  keep = FALSE
  ) {
  geometry_columns <- c(x,y,z,m)
  res <- rcpp_sf_multilinestring(
    obj
    , index_correct( geometry_columns )
    , index_correct( multilinestring_id )
    , index_correct( linestring_id )
    , keep
  )
  return( replace_id( res, multilinestring_id ) )
}



#' sf POLYGON
#'
#' constructs an sf of POLYGON objects
#'
#' @inheritParams sf_linestring
#' @param polygon_id column of ids for polygons
#' @param linestring_id column of ids for lines (within polygons)
#' @param close logical indicating whether polygons should be closed. If \code{TRUE},
#' all polygons will be checked and force closed if possible
#' @inheritSection sfc_point notes
#' @inheritSection sf_point Keeping Properties
#'
#' @return \code{sf} object of POLYGON geometries
#'
#' @examples
#'
#' m <- matrix(c(0,0,0,0,1,1), ncol = 2 )
#' sf_polygon( m )
#'
#' m <- matrix(c(0,0,0,0,0,1,0,1,1,1,2,2,1,2,3,1,3,4), ncol = 3, byrow = TRUE)
#' sf_polygon( obj = m )
#' sf_polygon( obj = m, polygon_id = 1 )
#' sf_polygon( obj = m, linestring_id = 1 )
#'
#' sf_polygon( obj = m, linestring_id = 1, polygon_id = 1 )
#'
#' sf_polygon( obj = m, x = 2, y = 3 )
#' sf_polygon( obj = m, x = 1, y = 2, z = 3 )
#' sf_polygon( obj = m, x = 2, y = 3, linestring_id = 1, polygon_id = 1 )
#'
#' df <- data.frame(
#'   ml_id = c(1,1,1,1,1,1,1,1,1,2,2,2,2,2,2)
#'   , l_id = c(1,1,1,2,2,2,3,3,3,1,1,1,2,2,2)
#'   , x = rnorm(15)
#'   , y = rnorm(15)
#'   , z = rnorm(15)
#'   , m = rnorm(15)
#' )
#'
#' sf_polygon( obj = df, x = "x", y = "y")
#' sf_polygon( obj = df, x = "x", y = "y", z = "z")
#' sf_polygon( obj = df, x = "x", y = "y", z = "z", m = "m")
#'
#' sf_polygon( obj = df, x = 2, y = 3)
#' sf_polygon( obj = df, x = 2, y = 3, z = 4)
#' sf_polygon( obj = df, x = 2, y = 3, z = 4, m = 5)
#'
#' sf_polygon( obj = df, polygon_id = "ml_id", linestring_id = "l_id" )
#' sf_polygon( obj = df, polygon_id = 1, linestring_id = 2 )
#'
#'
#'
#' @export
sf_polygon <- function(
  obj = NULL,
  x = NULL,
  y = NULL,
  z = NULL,
  m = NULL,
  polygon_id = NULL,
  linestring_id = NULL,
  close = TRUE,
  keep = FALSE
  ) {
  geometry_columns <- c(x,y,z,m)
  res <- rcpp_sf_polygon(
    obj
    , index_correct( geometry_columns )
    , index_correct( polygon_id )
    , index_correct( linestring_id )
    , close
    , keep
    )
  return( replace_id( res, polygon_id ) )
}


#' sf MULTIPOLYGON
#'
#' constructs an sf of MULTIPOLYGON objects
#'
#'
#' @inheritParams sf_polygon
#' @param multipolygon_id column of ids for multipolygons
#' @inheritSection sfc_point notes
#' @inheritSection sf_point Keeping Properties
#'
#' @return \code{sf} object of MULTIPOLYGON geometries
#'
#' @examples
#'
#' m <- matrix(c(0,0,0,0,1,0,0,1,1,0,0,1,0,0,0), ncol = 3, byrow = TRUE )
#' sf_multipolygon( m )
#'
#' df <- data.frame(
#'   id = c(1,1,1,1,1)
#'   , x = c(0,0,1,1,0)
#'   , y = c(0,1,1,0,0)
#' )
#'
#' sf_multipolygon( df, x = "x", y = "y" )
#'
#' df <- data.frame(
#'   id = c(1,1,1,1,1,2,2,2,2,2)
#'   , x = c(0,0,1,1,0,1,1,2,2,1)
#'   , y = c(0,1,1,0,0,1,2,2,1,1)
#' )
#'
#' sf_multipolygon( df, multipolygon_id = "id", polygon_id = "id", linestring_id = "id")
#'
#' df <- data.frame(
#'   id1 = c(1,1,1,1,1,1,1,1,1,1)
#'   , id2 = c(1,1,1,1,1,2,2,2,2,2)
#'   , x = c(0,0,1,1,0,1,1,2,2,1)
#'   , y = c(0,1,1,0,0,1,2,2,1,1)
#' )
#'
#' sf_multipolygon( df, multipolygon_id = "id1", polygon_id = "id2")
#'
#' df <- data.frame(
#'   id1 = c(1,1,1,1,1,1,1,1,1,1,2,2,2,2,2)
#'   , id2 = c(1,1,1,1,1,2,2,2,2,2,1,1,1,1,1)
#'   , x = c(0,0,1,1,0,1,1,2,2,1,3,3,4,4,3)
#'   , y = c(0,1,1,0,0,1,2,2,1,1,3,4,4,3,3)
#' )
#'
#' sf_multipolygon( df, multipolygon_id = "id1", polygon_id = "id2")
#'
#' df <- data.frame(
#'   id1 = c(1,1,1,1,1,2,2,2,2,2)
#'   , id2 = c(1,1,1,1,1,1,1,1,1,1)
#'   , x = c(0,0,1,1,0,1,1,2,2,1)
#'   , y = c(0,1,1,0,0,1,2,2,1,1)
#' )
#'
#' sf_multipolygon( df, multipolygon_id = "id1", polygon_id = "id2" )
#' sf_multipolygon( df, polygon_id = "id1", linestring_id = "id2" )
#' sf_multipolygon( df, x = "x", y = "y", polygon_id = "id1")
#' sf_multipolygon( df, x = "x", y = "y", polygon_id = "id1", linestring_id = "id2")
#' sf_multipolygon( df, x = "x", y = "y", linestring_id = "id1")
#' sf_multipolygon( df, x = "x", y = "y", linestring_id = "id2")
#'
#' df <- data.frame(
#'   id1 = c('a','a','a','a','a','b','b','b','b','b')
#'   , id2 = c(1,1,1,1,1,1,1,1,1,1)
#'   , x = c(0,0,1,1,0,1,1,2,2,1)
#'   , y = c(0,1,1,0,0,1,2,2,1,1)
#' )
#'
#' sf_multipolygon( df, x = "x", y = "y", polygon_id = "id1")
#'
#' @export
sf_multipolygon <- function(
  obj = NULL,
  x = NULL,
  y = NULL,
  z = NULL,
  m = NULL,
  multipolygon_id = NULL,
  polygon_id = NULL,
  linestring_id = NULL,
  close = TRUE,
  keep = FALSE
  ) {
  geometry_columns <- c(x,y,z,m)
  res <- rcpp_sf_multipolygon(
    obj
    , index_correct( geometry_columns )
    , index_correct( multipolygon_id )
    , index_correct( polygon_id )
    , index_correct( linestring_id )
    , close
    , keep
    )
  return( replace_id( res, multipolygon_id ) )
}

replace_id <- function( x, id ) {
  if( is.character( id ) ) {
    names( x )[ names( x ) == "id" ] <- id
  }
  return( x )
}
