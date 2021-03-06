% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/sfc.R
\name{sfc_multipolygon}
\alias{sfc_multipolygon}
\title{sfc MULTIPOLYGON}
\usage{
sfc_multipolygon(
  obj = NULL,
  x = NULL,
  y = NULL,
  z = NULL,
  m = NULL,
  multipolygon_id = NULL,
  polygon_id = NULL,
  linestring_id = NULL,
  close = TRUE
)
}
\arguments{
\item{obj}{sorted matrix or data.frame}

\item{x}{x geometry column}

\item{y}{y geometry column}

\item{z}{z geometry column}

\item{m}{m geometry column}

\item{multipolygon_id}{column of ids for multipolygons}

\item{polygon_id}{column of ids for polygons}

\item{linestring_id}{column of ids for lines (within polygons)}

\item{close}{logical indicating whether polygons should be closed. If \code{TRUE},
all polygons will be checked and force closed if possible}
}
\value{
\code{sfc} object of MULTIPOLYGON geometries
}
\description{
constructs an sfc of MULTIPOLYGON objects
}
\section{notes}{

sfheaders functions do not perform any validity checks on the geometries.
Nor do they set Coordinate Reference Systems, EPSG, PROJ4 or precision attributes.

The data.frame and matrices you send into the sfheader functions must be ordered.
}

\examples{

m <- matrix(c(0,0,0,0,1,0,0,1,1,0,0,1,0,0,0), ncol = 3, byrow = TRUE )
sfc_multipolygon( m )

df <- data.frame(
  id = c(1,1,1,1,1)
  , x = c(0,0,1,1,0)
  , y = c(0,1,1,0,0)
)

sfc_multipolygon( df, x = "x", y = "y" )

df <- data.frame(
  id = c(1,1,1,1,1,2,2,2,2,2)
  , x = c(0,0,1,1,0,1,1,2,2,1)
  , y = c(0,1,1,0,0,1,2,2,1,1)
)

sfc_multipolygon( df, multipolygon_id = "id", polygon_id = "id", linestring_id = "id")

df <- data.frame(
  id1 = c(1,1,1,1,1,1,1,1,1,1)
  , id2 = c(1,1,1,1,1,2,2,2,2,2)
  , x = c(0,0,1,1,0,1,1,2,2,1)
  , y = c(0,1,1,0,0,1,2,2,1,1)
)

sfc_multipolygon( df, multipolygon_id = "id1", polygon_id = "id2")

df <- data.frame(
  id1 = c(1,1,1,1,1,1,1,1,1,1,2,2,2,2,2)
  , id2 = c(1,1,1,1,1,2,2,2,2,2,1,1,1,1,1)
  , x = c(0,0,1,1,0,1,1,2,2,1,3,3,4,4,3)
  , y = c(0,1,1,0,0,1,2,2,1,1,3,4,4,3,3)
)

sfc_multipolygon( df, multipolygon_id = "id1", polygon_id = "id2")

df <- data.frame(
  id1 = c(1,1,1,1,1,2,2,2,2,2)
  , id2 = c(1,1,1,1,1,1,1,1,1,1)
  , x = c(0,0,1,1,0,1,1,2,2,1)
  , y = c(0,1,1,0,0,1,2,2,1,1)
)

sfc_multipolygon( df, multipolygon_id = "id1", polygon_id = "id2" )
sfc_multipolygon( df, polygon_id = "id1", linestring_id = "id2" )
sfc_multipolygon( df, x = "x", y = "y", polygon_id = "id1")
sfc_multipolygon( df, x = "x", y = "y", polygon_id = "id1", linestring_id = "id2")
sfc_multipolygon( df, x = "x", y = "y", linestring_id = "id1")
sfc_multipolygon( df, x = "x", y = "y", linestring_id = "id2")

df <- data.frame(
  id1 = c('a','a','a','a','a','b','b','b','b','b')
  , id2 = c(1,1,1,1,1,1,1,1,1,1)
  , x = c(0,0,1,1,0,1,1,2,2,1)
  , y = c(0,1,1,0,0,1,2,2,1,1)
)

sfc_multipolygon( df, x = "x", y = "y", polygon_id = "id1")

}
