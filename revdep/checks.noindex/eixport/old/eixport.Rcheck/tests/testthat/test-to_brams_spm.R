context("to_brams_spm")

data(gCO)
df1 <- to_brams_spm(sdf = gCO, epsg = 4326)[1, ]
test_that("to_brams_spm works", {
  expect_equal(to_brams_spm(sdf = gCO, epsg = 4326)[1, ],
               data.frame(
                 long = -46.8066,
                 lat = -23.62,
                 e24h = 8391.282 + 0.0004346044
               ))
})
df <- data.frame(
  co = 8391.282 + 0.0004346044,
  long = -46.8066,
  lat = -23.62
)
row.names(df) <- row.names(to_brams_spm(sdf = list(co = gCO,
                                                   pm = gCO),
                                        epsg = 4326)[[1]][1, ])
test_that("to_brams_spm works", {
  expect_equal(to_brams_spm(sdf = list(co = gCO,
                                       pm = gCO),
                            epsg = 4326)[[1]][1, ],
               df
               )
})
