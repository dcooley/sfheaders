context("colours")

test_that("colours returned as hex or rgb",{

  n <- 5
  params <- list(fill_colour = "col1")
  df <- data.frame(col1 = 1:n)
  lst_params <- spatialwidget:::rcpp_construct_params(df, params)
  data <- df
  data_rows <- nrow( df )
  lst_defaults <- list(fill_colour = rep(1,5))

  colour_name <- "fill_colour"
  opacity_name <- "fill_colour"
  lst_legend <- list("stroke_colour" = TRUE)
  include_legend <- FALSE

  colour_format = "hex"

  res <- spatialwidget:::rcpp_resolve_colour(
    lst_params,
    params,
    data,
    lst_defaults,
    colour_name,
    opacity_name,
    lst_legend,
    include_legend,
    colour_format
  )

  expect_equal(
    res$defaults$fill_colour, colourvalues::colour_values(1:5, alpha = 1:5)
  )


  n <- 5
  params <- list(fill_colour = "col1")
  df <- data.frame(col1 = 1:n)
  lst_params <- spatialwidget:::rcpp_construct_params(df, params)
  data <- df
  data_rows <- nrow( df )
  lst_defaults <- list(fill_colour = rep(1,5))

  colour_name <- "fill_colour"
  opacity_name <- "not_a_column_will_use_default"
  lst_legend <- list("stroke_colour" = TRUE)
  include_legend <- FALSE

  colour_format = "hex"

  res <- spatialwidget:::rcpp_resolve_colour(
    lst_params,
    params,
    data,
    lst_defaults,
    colour_name,
    opacity_name,
    lst_legend,
    include_legend,
    colour_format
  )

  expect_equal(
    res$defaults$fill_colour, colourvalues::colour_values(1:5)
  )


  n <- 5
  params <- list(fill_colour = "col1")
  df <- data.frame(col1 = 1:n)
  lst_params <- spatialwidget:::rcpp_construct_params(df, params)
  data <- df
  data_rows <- nrow( df )
  lst_defaults <- list(fill_colour = rep(1,5))

  colour_name <- "fill_colour"
  opacity_name <- "fill_colour"
  lst_legend <- list("stroke_colour" = TRUE)
  include_legend <- FALSE

  colour_format = "rgb"

  res <- spatialwidget:::rcpp_resolve_colour(
    lst_params,
    params,
    data,
    lst_defaults,
    colour_name,
    opacity_name,
    lst_legend,
    include_legend,
    colour_format
  )

  expect_equal(
    res$defaults$fill_colour, colourvalues::colour_values_rgb(1:5, alpha = 1:5)
  )

})
