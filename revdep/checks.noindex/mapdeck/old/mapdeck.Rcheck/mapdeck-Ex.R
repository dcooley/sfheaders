pkgname <- "mapdeck"
source(file.path(R.home("share"), "R", "examples-header.R"))
options(warn = 1)
library('mapdeck')

base::assign(".oldSearch", base::search(), pos = 'CheckExEnv')
base::assign(".old_wd", base::getwd(), pos = 'CheckExEnv')
cleanEx()
nameEx("add_arc")
### * add_arc

flush(stderr()); flush(stdout())

### Name: add_arc
### Title: Add arc
### Aliases: add_arc

### ** Examples





cleanEx()
nameEx("add_bitmap")
### * add_bitmap

flush(stderr()); flush(stdout())

### Name: add_bitmap
### Title: Add bitmap
### Aliases: add_bitmap

### ** Examples





cleanEx()
nameEx("add_column")
### * add_column

flush(stderr()); flush(stdout())

### Name: add_column
### Title: Add column
### Aliases: add_column

### ** Examples

## Not run: 
##D 
##D ## You need a valid access token from Mapbox
##D key <- 'abc'
##D set_token( key )
##D 
##D 
##D df <- capitals
##D df$elev <- sample(50000:500000, size = nrow(df), replace = T)
##D 
##D mapdeck(style = mapdeck_style("dark"), pitch = 45) %>%
##D add_column(
##D   data = df
##D   , lat = "lat"
##D   , lon = "lon"
##D   , elevation = "elev"
##D   , fill_colour = "lon"
##D   , disk_resolution = 20
##D   , radius = 100000
##D   , tooltip = "capital"
##D )
##D 
##D library(sfheaders)
##D sf <- sfheaders::sf_point( df, x = "lon", y = "lat" )
##D 
##D sf$elev <- df$elev
##D 
##D mapdeck( style = mapdeck_style("dark"), pitch = 45 ) %>%
##D add_column(
##D   data = sf
##D   , layer_id = "col_layer"
##D   , elevation = "elev"
##D   , radius = 100000
##D   , fill_colour = "country"
##D )
##D 
##D 
## End(Not run)




cleanEx()
nameEx("add_dependencies")
### * add_dependencies

flush(stderr()); flush(stdout())

### Name: add_dependencies
### Title: Add Dependencies
### Aliases: add_dependencies

### ** Examples







cleanEx()
nameEx("add_geojson")
### * add_geojson

flush(stderr()); flush(stdout())

### Name: add_geojson
### Title: Add Geojson
### Aliases: add_geojson

### ** Examples






cleanEx()
nameEx("add_greatcircle")
### * add_greatcircle

flush(stderr()); flush(stdout())

### Name: add_greatcircle
### Title: Add greatcircle
### Aliases: add_greatcircle

### ** Examples





cleanEx()
nameEx("add_grid")
### * add_grid

flush(stderr()); flush(stdout())

### Name: add_grid
### Title: Add Grid
### Aliases: add_grid

### ** Examples





cleanEx()
nameEx("add_heatmap")
### * add_heatmap

flush(stderr()); flush(stdout())

### Name: add_heatmap
### Title: Add Heatmap
### Aliases: add_heatmap

### ** Examples





cleanEx()
nameEx("add_hexagon")
### * add_hexagon

flush(stderr()); flush(stdout())

### Name: add_hexagon
### Title: Add hexagon
### Aliases: add_hexagon

### ** Examples

## Not run: 
##D 
##D ## You need a valid access token from Mapbox
##D key <- 'abc'
##D set_token( key )
##D 
##D df <- read.csv(paste0(
##D 'https://raw.githubusercontent.com/uber-common/deck.gl-data/master/examples/'
##D , '3d-heatmap/heatmap-data.csv'
##D ))
##D 
##D df <- df[!is.na(df$lng), ]
##D 
##D mapdeck( style = mapdeck_style("dark"), pitch = 45) %>%
##D add_hexagon(
##D   data = df
##D   , lat = "lat"
##D   , lon = "lng"
##D   , layer_id = "hex_layer"
##D   , elevation_scale = 100
##D )
##D 
##D library(sfheaders)
##D sf <- sfheaders::sf_point( df, x = "lng", y = "lat" )
##D 
##D mapdeck( style = mapdeck_style("dark"), pitch = 45 ) %>%
##D add_hexagon(
##D   data = sf
##D   , layer_id = "hex_layer"
##D   , elevation_scale = 100
##D )
##D 
##D ## Using elevation and colour
##D df$colour <- rnorm(nrow(df))
##D df$elevation <- rnorm(nrow(df))
##D 
##D mapdeck( style = mapdeck_style("dark"), pitch = 45) %>%
##D add_hexagon(
##D   data = df
##D   , lat = "lat"
##D   , lon = "lng"
##D   , layer_id = "hex_layer"
##D   , elevation_scale = 100
##D   , elevation = "weight"
##D   , colour = "colour"
##D )
##D 
##D mapdeck( style = mapdeck_style("dark"), pitch = 45) %>%
##D add_hexagon(
##D   data = df
##D   , lat = "lat"
##D   , lon = "lng"
##D   , layer_id = "hex_layer"
##D   , elevation_scale = 100
##D   , elevation = "weight"
##D   , elevation_function = "mean"
##D   , colour = "colour"
##D   , colour_function = "mean"
##D )
##D 
##D ## with a legend
##D df$val <- sample(1:10, size = nrow(df), replace = T)
##D 
##D mapdeck( style = mapdeck_style("dark"), pitch = 45) %>%
##D add_hexagon(
##D 	data = df
##D 	, lat = "lat"
##D 	, lon = "lng"
##D 	, layer_id = "hex_layer"
##D 	, elevation_scale = 100
##D 	, legend = T
##D 	, legend_options = list( digits = 0 )
##D 	, colour_function = "mean"
##D 	, colour = "val"
##D )
##D 
## End(Not run)




cleanEx()
nameEx("add_line")
### * add_line

flush(stderr()); flush(stdout())

### Name: add_line
### Title: Add line
### Aliases: add_line

### ** Examples





cleanEx()
nameEx("add_mesh")
### * add_mesh

flush(stderr()); flush(stdout())

### Name: add_mesh
### Title: Add Mesh
### Aliases: add_mesh

### ** Examples





cleanEx()
nameEx("add_path")
### * add_path

flush(stderr()); flush(stdout())

### Name: add_path
### Title: Add Path
### Aliases: add_path

### ** Examples





cleanEx()
nameEx("add_pointcloud")
### * add_pointcloud

flush(stderr()); flush(stdout())

### Name: add_pointcloud
### Title: Add Pointcloud
### Aliases: add_pointcloud

### ** Examples





cleanEx()
nameEx("add_polygon")
### * add_polygon

flush(stderr()); flush(stdout())

### Name: add_polygon
### Title: Add Polygon
### Aliases: add_polygon

### ** Examples





cleanEx()
nameEx("add_scatterplot")
### * add_scatterplot

flush(stderr()); flush(stdout())

### Name: add_scatterplot
### Title: Add Scatterplot
### Aliases: add_scatterplot

### ** Examples






cleanEx()
nameEx("add_screengrid")
### * add_screengrid

flush(stderr()); flush(stdout())

### Name: add_screengrid
### Title: Add Screengrid
### Aliases: add_screengrid

### ** Examples





cleanEx()
nameEx("add_text")
### * add_text

flush(stderr()); flush(stdout())

### Name: add_text
### Title: Add Text
### Aliases: add_text

### ** Examples






cleanEx()
nameEx("add_title")
### * add_title

flush(stderr()); flush(stdout())

### Name: add_title
### Title: Add Title
### Aliases: add_title

### ** Examples





cleanEx()
nameEx("add_trips")
### * add_trips

flush(stderr()); flush(stdout())

### Name: add_trips
### Title: Add Trips
### Aliases: add_trips

### ** Examples





cleanEx()
nameEx("legend_element")
### * legend_element

flush(stderr()); flush(stdout())

### Name: legend_element
### Title: Legend Element
### Aliases: legend_element

### ** Examples


l1 <- legend_element(
	variables = c("a","b")
	, colours = c("#00FF00","#FF0000")
	, colour_type = "fill"
	, variable_type = "category"
	, title = "my title"
)




cleanEx()
nameEx("light_settings")
### * light_settings

flush(stderr()); flush(stdout())

### Name: light_settings
### Title: Light Settings
### Aliases: light_settings

### ** Examples


light <- list(
  lightsPosition = c(-150, 75, 0)
  , numberOfLights = 1
  , ambientRatio = 0.2
)




cleanEx()
nameEx("mapdeck_legend")
### * mapdeck_legend

flush(stderr()); flush(stdout())

### Name: mapdeck_legend
### Title: Mapdeck Legend
### Aliases: mapdeck_legend

### ** Examples

l1 <- legend_element(
	variables = c("a","b")
	, colours = c("#00FF00","#FF0000")
	, colour_type = "fill"
	, variable_type = "category"
	, title = "my title"
)

mapdeck_legend(l1)




cleanEx()
nameEx("mapdeck_style")
### * mapdeck_style

flush(stderr()); flush(stdout())

### Name: mapdeck_style
### Title: Mapdeck Style
### Aliases: mapdeck_style

### ** Examples





cleanEx()
nameEx("pipe")
### * pipe

flush(stderr()); flush(stdout())

### Name: %>%
### Title: Pipe
### Aliases: %>%

### ** Examples




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
