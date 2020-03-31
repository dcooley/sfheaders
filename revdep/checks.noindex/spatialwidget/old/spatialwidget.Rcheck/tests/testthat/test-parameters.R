context("parameters")


test_that("parameters constructed",{

  df <- spatialwidget::widget_capitals
  l <- list(fill_colour = "country")
  res <- spatialwidget:::rcpp_construct_params(df, l)

  expect_true(res$parameter == "fill_colour")
  expect_true(res$parameter_type == 16)
  expect_true(res$data_column_index == 0 )

  l <- list(fill_colour = "country", stroke_colour = "capital")
  res <- spatialwidget:::rcpp_construct_params(df, l)

  expect_true(all( res$parameter == c( "fill_colour", "stroke_colour" ) ) )
  expect_true(all( res$parameter_type == c( 16, 16 ) ) )
  expect_true(all( res$data_column_index == c( 0, 1 ) ) )

  l <- list(fill_colour = "country", stroke_colour = "capital", stroke_weight = 10)
  res <- spatialwidget:::rcpp_construct_params(df, l)

  expect_true(all( res$parameter == c( "fill_colour", "stroke_colour", "stroke_weight" ) ) )
  expect_true(all( res$parameter_type == c( 16, 16, 14 ) ) )
  expect_true(all( res$data_column_index == c( 0, 1, -1 ) ) )

})


test_that("parameters converted to pseudo-geojson",{

  df <- spatialwidget::widget_capitals
  l <- list(fill_colour = "country", stroke_colour = "capital", legend = T)
  data_rows <- nrow( df )
  lst_defaults <- list(
    fill_colour = rep(1.0, data_rows)
    , stroke_colour = rep(1.0, data_rows)
  )

  layer_legend <- c("fill_colour","stroke_colour")
  parameter_exclusions <- c("legend","legend_options","palette","na_colour")

  res <- spatialwidget:::rcpp_params_to_data(
    df, l, lst_defaults, layer_legend, data_rows, parameter_exclusions,
    factors_as_string = TRUE
  )

  fill <- colourvalues::colour_values(df$country)
  stroke <- colourvalues::colour_values(df$capital)

  expect_true( all( res$data$fill_colour == fill ) )
  expect_true( all( res$data$stroke_colour == stroke ) )

  expect_true( res$legend$fill_colour$title == "country" )
  expect_true( res$legend$stroke_colour$title == "capital" )


})

