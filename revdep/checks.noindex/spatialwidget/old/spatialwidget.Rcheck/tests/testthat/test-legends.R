context("legends")


test_that("legends are formatted", {

  ## Numeric
  df <- data.frame(lon = c(1,2,-5,0.3), lat = 1:4, col = 1:4)

  res <- spatialwidget::widget_point(
    data = df
    , lon = "lon"
    , lat = "lat"
    , fill_colour = "col"
  )

  expect_equal( as.character( res$legend ), '{"fill_colour":{"colour":["#440154FF","#31688EFF","#35B779FF","#FDE725FF"],"variable":["1.00","2.00","3.00","4.00"],"colourType":["fill_colour"],"type":["gradient"],"title":["col"],"css":[""]}}')

  ## factor
  df <- data.frame(lon = c(1,2,-5,0.3), lat = 1:4, col = letters[1:4], stringsAsFactors = TRUE)

  res <- spatialwidget::widget_point(
    data = df
    , lon = "lon"
    , lat = "lat"
    , fill_colour = "col"
  )

  expect_equal( as.character( res$legend ), '{"fill_colour":{"colour":["#440154FF","#31688EFF","#35B779FF","#FDE725FF"],"variable":["a","b","c","d"],"colourType":["fill_colour"],"type":["category"],"title":["col"],"css":[""]}}')

  ## character
  df <- data.frame(lon = c(1,2,-5,0.3), lat = 1:4, col = letters[1:4], stringsAsFactors = FALSE)

  res <- spatialwidget::widget_point(
    data = df
    , lon = "lon"
    , lat = "lat"
    , fill_colour = "col"
  )

  expect_equal( as.character( res$legend ), '{"fill_colour":{"colour":["#440154FF","#31688EFF","#35B779FF","#FDE725FF"],"variable":["a","b","c","d"],"colourType":["fill_colour"],"type":["category"],"title":["col"],"css":[""]}}')

  ## Logical
  df <- data.frame(lon = c(1,2,-5,0.3), lat = 1:4, col = c(T,F,T,T))

  res <- spatialwidget::widget_point(
    data = df
    , lon = "lon"
    , lat = "lat"
    , fill_colour = "col"
  )

  expect_equal( as.character( res$legend ), '{"fill_colour":{"colour":["#440154FF","#FDE725FF"],"variable":["FALSE","TRUE"],"colourType":["fill_colour"],"type":["category"],"title":["col"],"css":[""]}}')

  ## Date
  df <- data.frame(lon = c(1,2,-5,0.3), lat = 1:4, col = seq(as.Date("2018-01-01"), as.Date("2018-01-04"), length.out = 4))

  res <- spatialwidget::widget_point(
    data = df
    , lon = "lon"
    , lat = "lat"
    , fill_colour = "col"
  )

  expect_equal( as.character( res$legend ), '{"fill_colour":{"colour":["#440154FF","#31688EFF","#35B779FF","#FDE725FF"],"variable":["2018-01-01","2018-01-02","2018-01-03","2018-01-04"],"colourType":["fill_colour"],"type":["gradient"],"title":["col"],"css":[""]}}')

  ## POSIXct
  df <- data.frame(
    lon = c(1,2,-5,0.3)
    , lat = 1:4
    , col = seq(as.POSIXct("2018-01-01", tz= "UTC")
                , as.POSIXct("2018-01-04", tz="UTC")
                , length.out = 4)
    )

  res <- spatialwidget::widget_point(
    data = df
    , lon = "lon"
    , lat = "lat"
    , fill_colour = "col"
  )

  expect_equal( as.character( res$legend ), '{"fill_colour":{"colour":["#440154FF","#31688EFF","#35B779FF","#FDE725FF"],"variable":["2018-01-01T00:00:00","2018-01-02T00:00:00","2018-01-03T00:00:00","2018-01-04T00:00:00"],"colourType":["fill_colour"],"type":["gradient"],"title":["col"],"css":[""]}}')

  ## POSIXlt (as POSIXct because in data.frame)
  df <- data.frame(
    lon = c(1,2,-5,0.3)
    , lat = 1:4
    , col = seq(as.POSIXlt("2018-01-01", tz="UTC")
                , as.POSIXlt("2018-01-04", tz="UTC")
                , length.out = 4)
    )

  res <- spatialwidget::widget_point(
    data = df
    , lon = "lon"
    , lat = "lat"
    , fill_colour = "col"
  )

  expect_equal( as.character( res$legend ), '{"fill_colour":{"colour":["#440154FF","#31688EFF","#35B779FF","#FDE725FF"],"variable":["2018-01-01T00:00:00","2018-01-02T00:00:00","2018-01-03T00:00:00","2018-01-04T00:00:00"],"colourType":["fill_colour"],"type":["gradient"],"title":["col"],"css":[""]}}')

})

# test_that("legend_digts used and formats legend", {
#
#   ## Numeric
#   df <- data.frame(lon = c(1,2,-5,0.3), lat = 1:4, col = c(1.23456789,2.34567891,3.45678912,4.56789123))
#
#   res <- spatialwidget::widget_point(
#     data = df
#     , lon = "lon"
#     , lat = "lat"
#     , fill_colour = "col"
#   )
#
#   expect_equal( as.character( res$legend ), '{"fill_colour":{"colour":["#440154FF","#31688EFF","#35B779FF","#FDE725FF"],"variable":["1.23","2.35","3.46","4.57"],"colourType":["fill_colour"],"type":["gradient"],"title":["col"],"css":[""]}}')
#
#   df <- data.frame(lon = c(1,2,-5,0.3), lat = 1:4, col = c(1.23456789,2.34567891,3.45678912,4.56789123))
#
#   res <- spatialwidget::widget_point(
#     data = df
#     , lon = "lon"
#     , lat = "lat"
#     , fill_colour = "col"
#     , legend_digits = 5
#   )
#
#   expect_equal( as.character( res$legend ), '{"fill_colour":{"colour":["#440154FF","#31688EFF","#35B779FF","#FDE725FF"],"variable":["1.23457","2.34568","3.45678","4.56789"],"colourType":["fill_colour"],"type":["gradient"],"title":["col"],"css":[""]}}')
#
#
#   x <- widget_roads[1:10, ]
#   x$var <- 0:9
#   l <- widget_line(x, stroke_colour = "var", legend = T, json_legend = FALSE, legend_digits = 5)
#   expect_true( all( nchar( l$legend$stroke_colour$variable ) == ( 5 + 1 + 1) ) ) # 5 digits + 1 before decimal, + 1 decimal
#
# })


test_that("rcpp legend list constructed",{

  df <- spatialwidget::widget_capitals
  l <- list(fill_colour = "country", stroke_colour = "capital", legend = T)
  p <- spatialwidget:::rcpp_construct_params( data = df, params = l)
  pn <- names( l )
  ll <- c("fill_colour","stroke_colour")

  res <- spatialwidget:::rcpp_construct_legend_list(
    lst_params = p
    , params = l
    , param_names = pn
    , legend_types = ll
    )

  expect_true( res$fill_colour == TRUE )
  expect_true( res$stroke_colour == TRUE )

  l <- list(fill_colour = "country", stroke_colour = "capital", legend = list(fill_colour = TRUE))
  p <- spatialwidget:::rcpp_construct_params( data = df, params = l)
  pn <- names( l )
  ll <- c("fill_colour","stroke_colour")

  res <- spatialwidget:::rcpp_construct_legend_list(
    lst_params = p
    , params = l
    , param_names = pn
    , legend_types = ll
  )

  expect_true( res$fill_colour == TRUE )
  expect_true( res$stroke_colour == FALSE )

})


test_that("legend options are set",{

  opts <- list(title = "hello")  ## user-supplied option
  value <- "foo"    ## the value to be replaced, like the column name
  colour_name <- "fill_colour"

  res <- spatialwidget:::rcpp_set_legend_option( opts, "title", value, colour_name );
  expect_equal( res, "hello")

})

