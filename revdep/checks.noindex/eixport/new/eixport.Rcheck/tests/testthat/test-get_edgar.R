context("get_edgar")
# v432_AP
a <- get_edgar(dataset = "v432_AP", destpath = tempdir(),
               sector = c("TRO"),
               pol = "CO",
               year = 2012,
               copyright = T)
a <- get_edgar(dataset = "v432_AP", destpath = tempdir(),
               sector = c("TRO"),
               pol = "CO",
               year = 2012,
               copyright = F, txt = FALSE)
