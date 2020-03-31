pkgname <- "eixport"
source(file.path(R.home("share"), "R", "examples-header.R"))
options(warn = 1)
library('eixport')

base::assign(".oldSearch", base::search(), pos = 'CheckExEnv')
base::assign(".old_wd", base::getwd(), pos = 'CheckExEnv')
cleanEx()
nameEx("Lights")
### * Lights

flush(stderr()); flush(stdout())

### Name: Lights
### Title: Spatial distribution example
### Aliases: Lights
### Keywords: datasets

### ** Examples

## Not run: 
##D 
##D dir.create(file.path(tempdir(), "EMISS"))
##D wrf_create(wrfinput_dir = system.file("extdata", package = "eixport"),
##D           wrfchemi_dir = file.path(tempdir(), "EMISS"),
##D           frames_per_auxinput5 = 24)
##D 
##D # get the name of created file
##D files <- list.files(path = file.path(tempdir(), "EMISS"),
##D                    pattern = "wrfchemi",
##D                    full.names = TRUE)
##D 
##D data(Lights)
##D 
##D perfil <- c(0.010760058, 0.005280596, 0.002883553, 0.002666932,
##D            0.005781312, 0.018412838, 0.051900411, 0.077834636,
##D            0.067919758, 0.060831614, 0.055852868, 0.052468599,
##D            0.050938043, 0.051921718, 0.052756244, 0.052820165,
##D            0.058388406, 0.072855890, 0.075267137, 0.063246412,
##D            0.042713523, 0.029108975, 0.022091855, 0.015298458)
##D 
##D plot(perfil, ty = "l", col= "purple", xlab = "Hour", main = "Time profile",
##D     ylab = "Weight", axes = FALSE, xlim = c(0, 24))
##D axis(2)
##D axis(1, at = c(0, 6, 12, 18, 24),
##D     labels = c("00:00","06:00","12:00","18:00","00:00"))
##D 
##D to_wrf(Lights, files[1], total = 1521983, profile = perfil, name = "E_CO")
## End(Not run)




cleanEx()
nameEx("emis_opt")
### * emis_opt

flush(stderr()); flush(stdout())

### Name: emis_opt
### Title: List of WRF emission species
### Aliases: emis_opt
### Keywords: datasets

### ** Examples

data(emis_opt)
names(emis_opt)
emis_opt[["eradm"]]




cleanEx()
nameEx("get_edgar")
### * get_edgar

flush(stderr()); flush(stdout())

### Name: get_edgar
### Title: Download datasets of EDGAR emissions
### Aliases: get_edgar

### ** Examples

## Not run: 
##D # Download all pollutants for sector TRO
##D get_edgar(dataset = "v432_AP", destpath = tempdir(),
##D sector = c("TOTALS"),
##D year = 2012)
##D # Download all sectors for pollutant CO
##D get_edgar(dataset = "v432_AP", destpath = tempdir(),
##D pol = c("CO"),
##D year = 2012)
## End(Not run)



cleanEx()
nameEx("sfx_explode")
### * sfx_explode

flush(stderr()); flush(stdout())

### Name: sfx_explode
### Title: splits line by vertex
### Aliases: sfx_explode

### ** Examples

{
# Do not run
data(emisco)
emisco <- emisco[1:100, "V8"]
dfco <- sfx_explode(emisco)
etm <- to_munich(sdf = dfco)
names(etm)
class(etm)
head(etm$Emissions)
head(etm$Street)
write.table(x = etm$Emissions, file = paste0(tempfile(), "_Emissions.txt"),
row.names = FALSE, sep = " ", quote = FALSE)
write.table(x = etm$Street, file = paste0(tempfile(), "_Street.txt"),
row.names = FALSE, sep = " ", quote = FALSE)
}



cleanEx()
nameEx("st_explode")
### * st_explode

flush(stderr()); flush(stdout())

### Name: st_explode
### Title: Split line by vertex (experimental)
### Aliases: st_explode

### ** Examples

## Not run: 
##D # do not run
##D library(vein)
##D data(net)
##D net2 <- st_explode(net)
##D dim(net)
##D dim(net2)
## End(Not run)



cleanEx()
nameEx("to_as4wrf")
### * to_as4wrf

flush(stderr()); flush(stdout())

### Name: to_as4wrf
### Title: Generates emissions dataframe to generate WRF-Chem inputs
### Aliases: to_as4wrf

### ** Examples

{
data(gCO)
df <- to_as4wrf(sdf = gCO, dmyhm = "29-04-2018 00:00",
               tz = "America/Sao_Paulo")
head(df)
df2 <- to_as4wrf(sdf = list(co = gCO, pm = gCO), dmyhm = "29-04-2018 00:00",
               tz = "America/Sao_Paulo")
head(df2)
}



cleanEx()
nameEx("to_brams_spm")
### * to_brams_spm

flush(stderr()); flush(stdout())

### Name: to_brams_spm
### Title: Inputs for BRAMS-SPM
### Aliases: to_brams_spm

### ** Examples

## Not run: 
##D data(gCO)
##D df1 <- to_brams_spm(sdf = gCO, epsg = 4326)
##D head(df1)
##D df2 <- to_brams_spm(sdf = list(co = gCO, pm = gCO), epsg = 4326)
##D lapply(df2, head)
## End(Not run)



cleanEx()
nameEx("to_munich")
### * to_munich

flush(stderr()); flush(stdout())

### Name: to_munich
### Title: Export emissions to Model of Urban Network of Intersecting
###   Canyons and Highways (MUNICH)
### Aliases: to_munich

### ** Examples

{
# Do not run
data(emisco)
dfco <- emisco[1:1000,"V8"]
etm <- to_munich(sdf = dfco)
names(etm)
class(etm)
head(etm$Emissions)
head(etm$Street)
write.table(x = etm$Emissions, file = paste0(tempfile(), "_Emissions.txt"),
row.names = FALSE, sep = " ", quote = FALSE)
write.table(x = etm$Street, file = paste0(tempfile(), "_Street.txt"),
row.names = FALSE, sep = " ", quote = FALSE)
}



cleanEx()
nameEx("to_rline")
### * to_rline

flush(stderr()); flush(stdout())

### Name: to_rline
### Title: Export emissions to other formats
### Aliases: to_rline

### ** Examples

## Not run: 
##D # Do not run
##D data(emisco)
##D Source <- to_rline(X_b = emisco$xmin,
##D                Y_b = emisco$ymin,
##D                Z_b =0,
##D                X_e = emisco$xmin,
##D                Y_e = emisco$ymin,
##D                Z_e =0,
##D                dCL = 0,
##D                Emis = emisco$V8,
##D                sigmaz0 = 2,
##D                lanes = emisco$lanes)
##D head(Source)
##D write.table(x = Source, file = paste0(tempdir(), "/Sources.txt"),
##D row.names = FALSE, sep = " ", quote = FALSE)
## End(Not run)



cleanEx()
nameEx("to_wrf")
### * to_wrf

flush(stderr()); flush(stdout())

### Name: to_wrf
### Title: Combine total/spatial/temporal/split and write emission to file
### Aliases: to_wrf

### ** Examples

## Not run: 
##D dir.create(file.path(tempdir(), "EMISS"))
##D wrf_create(wrfinput_dir = system.file("extdata", package = "eixport"),
##D           wrfchemi_dir = file.path(tempdir(), "EMISS"),
##D           frames_per_auxinput5 = 24)
##D 
##D # get the name of created file
##D files <- list.files(path = file.path(tempdir(), "EMISS"),
##D                    pattern = "wrfchemi",
##D                    full.names = TRUE)
##D 
##D data(Lights)
##D 
##D perfil <- c(0.010760058, 0.005280596, 0.002883553, 0.002666932,
##D             0.005781312, 0.018412838, 0.051900411, 0.077834636,
##D             0.067919758, 0.060831614, 0.055852868, 0.052468599,
##D             0.050938043, 0.051921718, 0.052756244, 0.052820165,
##D             0.058388406, 0.072855890, 0.075267137, 0.063246412,
##D             0.042713523, 0.029108975, 0.022091855, 0.015298458)
##D 
##D plot(perfil, ty = "l", col= "purple", xlab = "Hour", main = "Time profile",
##D     ylab = "Weight", axes = FALSE, xlim = c(0, 24))
##D axis(2)
##D axis(1, at = c(0, 6, 12, 18, 24),
##D     labels = c("00:00","06:00","12:00","18:00","00:00"))
##D 
##D to_wrf(Lights, files[1], total = 1521983, profile = perfil, name = "E_CO")
## End(Not run)



cleanEx()
nameEx("wrf_add")
### * wrf_add

flush(stderr()); flush(stdout())

### Name: wrf_add
### Title: Function to add values for variables on emission files
### Aliases: wrf_add

### ** Examples

{
# create the folder and emission file
dir.create(file.path(tempdir(), "EMISS"))
wrf_create(wrfinput_dir = system.file("extdata", package = "eixport"),
          wrfchemi_dir = file.path(tempdir(), "EMISS"))

# get the name of created file
files <- list.files(path = file.path(tempdir(), "EMISS"),
                    pattern = "wrfchemi",
                    full.names = TRUE)

# open, put some numbers and write
CO <- wrf_get(file = files[1], name = "E_CO")
CO[] = rnorm(length(CO),mean = 5,sd = 1)
wrf_put(file = files[1], name = "E_CO", POL = CO)
# open, put some different numbers and write
CO[] = rnorm(length(CO),mean = 10,sd = 1)
wrf_add(file = files[1], name = "E_CO", POL = CO)
}



cleanEx()
nameEx("wrf_create")
### * wrf_create

flush(stderr()); flush(stdout())

### Name: wrf_create
### Title: Create emission files for the WRF-Chem model
### Aliases: wrf_create

### ** Examples

## Not run: 
##D # Do not run
##D 
##D # emissions for a 1 day forecast for domains 1 and 2
##D 
##D dir.create(file.path(tempdir(), "EMISS"))
##D 
##D # emissions on date_hour style
##D wrf_create(wrfinput_dir         = system.file("extdata", package = "eixport"),
##D            wrfchemi_dir         = file.path(tempdir(), "EMISS"),
##D            domains              = 1:2,
##D            frames_per_auxinput5 = 25,
##D            auxinput5_interval_m = 60,
##D            verbose              = TRUE)
##D 
##D # emissions on 00z / 12z style, create the 00z
##D wrf_create(wrfinput_dir         = system.file("extdata", package = "eixport"),
##D            wrfchemi_dir         = file.path(tempdir(), "EMISS"),
##D            domains              = 1:2,
##D            io_style_emissions   = 1,
##D            day_offset           = 0,
##D            verbose              = TRUE,
##D            )
##D # emissions on 00z / 12z style, create the 12z
##D wrf_create(wrfinput_dir         = system.file("extdata", package = "eixport"),
##D            wrfchemi_dir         = file.path(tempdir(), "EMISS"),
##D            domains              = 1:2,
##D            io_style_emissions   = 1,
##D            day_offset           = 0.5,
##D            verbose              = TRUE)
## End(Not run)



cleanEx()
nameEx("wrf_get")
### * wrf_get

flush(stderr()); flush(stdout())

### Name: wrf_get
### Title: Function to read variables of emission files
### Aliases: wrf_get

### ** Examples

{

# create the folder and emission file
dir.create(file.path(tempdir(), "EMISS"))
wrf_create(wrfinput_dir = system.file("extdata", package = "eixport"),
         wrfchemi_dir = file.path(tempdir(), "EMISS"))

# get the name of created file
files <- list.files(path = file.path(tempdir(), "EMISS"),
                   pattern = "wrfchemi",
                   full.names = TRUE)

# open, put some numbers and write
CO <- wrf_get(file = files[1], name = "E_CO")
CO[] = rnorm(length(CO))
wrf_put(file = files[1], name = "E_CO", POL = CO)
COr <- wrf_get(file = files[1], name = "E_CO", as_raster = TRUE)

}



cleanEx()
nameEx("wrf_grid")
### * wrf_grid

flush(stderr()); flush(stdout())

### Name: wrf_grid
### Title: Creates grid from wrf file
### Aliases: wrf_grid

### ** Examples

{
# Do not run
wrf <- paste(system.file("extdata", package = "eixport"),
                         "/wrfinput_d02", sep="")
gwrf  <- wrf_grid(wrf)
plot(gwrf, axes = TRUE)
}



cleanEx()
nameEx("wrf_plot")
### * wrf_plot

flush(stderr()); flush(stdout())

### Name: wrf_plot
### Title: Simple plot from wrf emission file
### Aliases: wrf_plot

### ** Examples

{

dir.create(file.path(tempdir(), "EMISS"))
wrf_create(wrfinput_dir = system.file("extdata", package = "eixport"),
          wrfchemi_dir = file.path(tempdir(), "EMISS"))

# get the name of created file
files <- list.files(path = file.path(tempdir(), "EMISS"),
                   pattern = "wrfchemi",
                   full.names = TRUE)

# load end write some data in this emission file
data(Lights)
to_wrf(Lights, files[1], total = 1521983, name = "E_CO")

wrf_plot(files[1], "E_CO")
}



cleanEx()
nameEx("wrf_profile")
### * wrf_profile

flush(stderr()); flush(stdout())

### Name: wrf_profile
### Title: Create a spatial profile from a wrf emission file and a data
###   frame with
### Aliases: wrf_profile

### ** Examples

## Not run: 
##D # Do not run
##D 
##D # Profile based on Sao Paulo tunnel experiments
##D data(rawprofile)
##D rawprofile  <- matrix(rawprofile, nrow = 24, byrow = TRUE)
##D rawprofile <- as.data.frame(rawprofile)
##D names(rawprofile) <- c("Sunday","Monday","Tuesday","Wednesday","Thursday",
##D                        "Friday","Saturday")
##D row.names(rawprofile) <- c("00:00","01:00","02:00","03:00","04:00","05:00",
##D                            "06:00","07:00","08:00","09:00","10:00","11:00",
##D                            "12:00","13:00","14:00","15:00","16:00","17:00",
##D                            "18:00","19:00","20:00","21:00","22:00","23:00")
##D 
##D print(rawprofile)
##D 
##D # create the folder and emission file
##D dir.create(file.path(tempdir(), "EMISS"))
##D wrf_create(wrfinput_dir = system.file("extdata", package = "eixport"),
##D           wrfchemi_dir = file.path(tempdir(), "EMISS"),
##D           frames_per_auxinput5 = 24)
##D 
##D files <- list.files(path = file.path(tempdir(), "EMISS"),
##D                     pattern = "wrfchemi",
##D                     full.names = TRUE)
##D 
##D profile <- wrf_profile(rawprofile,files[1])
##D 
##D plot(profile, ty="l", lty = 2, axe = FALSE,
##D      main = "Traffic Intensity for Sao Paulo", xlab = "hour")
##D axis(2)
##D axis(1, at = 0.5 + c(0, 6, 12, 18, 24),
##D     labels = c("00:00","06:00","12:00","18:00", "00:00"))
## End(Not run)



cleanEx()
nameEx("wrf_put")
### * wrf_put

flush(stderr()); flush(stdout())

### Name: wrf_put
### Title: Function to write variables in emission files
### Aliases: wrf_put

### ** Examples

{
# create the folder and emission file
dir.create(file.path(tempdir(), "EMISS"))
wrf_create(wrfinput_dir = system.file("extdata", package = "eixport"),
          wrfchemi_dir = file.path(tempdir(), "EMISS"))

# get the name of created file
files <- list.files(path = file.path(tempdir(), "EMISS"),
                    pattern = "wrfchemi",
                    full.names = TRUE)

# open, put some numbers and write
CO <- wrf_get(file = files[1], name = "E_CO")
CO[] = rnorm(length(CO))
wrf_put(file = files[1], name = "E_CO", POL = CO)
}



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
