pkgname <- "geojsonsf"
source(file.path(R.home("share"), "R", "examples-header.R"))
options(warn = 1)
library('geojsonsf')

base::assign(".oldSearch", base::search(), pos = 'CheckExEnv')
base::assign(".old_wd", base::getwd(), pos = 'CheckExEnv')
cleanEx()
nameEx("df_geojson")
### * df_geojson

flush(stderr()); flush(stdout())

### Name: df_geojson
### Title: df to GeoJSON
### Aliases: df_geojson

### ** Examples


df <- data.frame(lon = c(1:5, NA), lat = c(1:5, NA), id = 1:6, val = letters[1:6])
df_geojson( df, lon = "lon", lat = "lat")
df_geojson( df, lon = "lon", lat = "lat", atomise = TRUE)

df <- data.frame(lon = c(1:5, NA), lat = c(1:5, NA) )
df_geojson( df, lon = "lon", lat = "lat")
df_geojson( df, lon = "lon", lat = "lat", simplify = FALSE)

df <- data.frame(lon = c(1:5), lat = c(1:5), elevation = c(1:5) )
df_geojson( df, lon = "lon", lat = "lat", z = "elevation")
df_geojson( df, lon = "lon", lat = "lat", z = "elevation", simplify = FALSE)

df <- data.frame(lon = c(1:5), lat = c(1:5), elevation = c(1:5), id = 1:5 )
df_geojson( df, lon = "lon", lat = "lat", z = "elevation")
df_geojson( df, lon = "lon", lat = "lat", z = "elevation", atomise = TRUE)


## to sf objects
geo <- df_geojson( df, lon = "lon", lat = "lat", z = "elevation")
sf <- geojson_sf( geo )




cleanEx()
nameEx("geojson_sf")
### * geojson_sf

flush(stderr()); flush(stdout())

### Name: geojson_sf
### Title: Geojson to sf
### Aliases: geojson_sf

### ** Examples


## character string of GeoJSON

## load 'sf' for print methods
# library(sf)
geojson <- '{ "type" : "Point", "coordinates" : [0, 0] }'
geojson_sf(geojson)


## Not run: 
##D ## GeoJSON at a url
##D myurl <- "http://eric.clst.org/assets/wiki/uploads/Stuff/gz_2010_us_050_00_500k.json"
##D sf <- geojson_sf(myurl)
## End(Not run)




cleanEx()
nameEx("geojson_sfc")
### * geojson_sfc

flush(stderr()); flush(stdout())

### Name: geojson_sfc
### Title: Geojson to sfc
### Aliases: geojson_sfc

### ** Examples


## character string of GeoJSON

## load 'sf' for print methods
# library(sf)
geojson <- '{ "type":"Point","coordinates":[0,0] }'
geojson_sfc(geojson)

geojson <- '[
  { "type":"Point","coordinates":[0,0]},
  {"type":"LineString","coordinates":[[0,0],[1,1]]}
  ]'
geojson_sfc( geojson )

## Not run: 
##D ## GeoJSON at a url
##D myurl <- "http://eric.clst.org/assets/wiki/uploads/Stuff/gz_2010_us_050_00_500k.json"
##D sf <- geojson_sfc(myurl)
## End(Not run)




cleanEx()
nameEx("geojson_wkt")
### * geojson_wkt

flush(stderr()); flush(stdout())

### Name: geojson_wkt
### Title: Geojson to WKT
### Aliases: geojson_wkt

### ** Examples

geojson <- '{ "type" : "Point", "coordinates" : [0, 0] }'
geojson_wkt(geojson)




cleanEx()
nameEx("sf_geojson")
### * sf_geojson

flush(stderr()); flush(stdout())

### Name: sf_geojson
### Title: sf to GeoJSON
### Aliases: sf_geojson

### ** Examples

## Not run: 
##D library(sf)
##D sf <- sf::st_sf(geometry = sf::st_sfc(list(sf::st_point(c(0,0)), sf::st_point(c(1,1)))))
##D sf$id <- 1:2
##D sf_geojson(sf)
##D sf_geojson(sf, atomise = T)
##D 
##D ls <- st_linestring(rbind(c(0,0),c(1,1),c(2,1)))
##D mls <- st_multilinestring(list(rbind(c(2,2),c(1,3)), rbind(c(0,0),c(1,1),c(2,1))))
##D sfc <- st_sfc(ls,mls)
##D sf <- st_sf(sfc)
##D sf_geojson( sf )
##D sf_geojson( sf, simplify = FALSE )
##D 
## End(Not run)




cleanEx()
nameEx("sfc_geojson")
### * sfc_geojson

flush(stderr()); flush(stdout())

### Name: sfc_geojson
### Title: sfc to GeoJSON
### Aliases: sfc_geojson

### ** Examples

## Not run: 
##D library(sf)
##D sf <- sf::st_sfc(list(sf::st_point(c(0,0)), sf::st_point(c(1,1))))
##D sfc_geojson(sf)
## End(Not run)



### * <FOOTER>
###
cleanEx()
options(digits = 7L)
base::cat("Time elapsed: ", proc.time() - base::get("ptime", pos = 'CheckExEnv'),"\n")
grDevices::dev.off()
###
### Local variables: ***
### mode: outline-minor ***
### outline-regexp: "\\(> \\)?### [*]+" ***
### End: ***
quit('no')
