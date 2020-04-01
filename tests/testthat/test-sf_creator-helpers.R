context("sf_creator-helpers")

test_that("sf_mpoly works",{

  m <- matrix(c(0, 0, 1, 1, 0,
              0, 1, 1, 0, 0), ncol = 2, dimnames = list(NULL, c("x", "y")))
  mat <- cbind(m, multipolygon_id = 1, polygon_id = 1,
                  multilinestring_id = 1, linestring_id = 1,
                  multipoint_id = c(1, 1, 2, 2, 2), point_id = 1:5)
  res <- sf_mpoly(mat)
  ans <- sf_multipolygon(mat, x = "x", y = "y", multipolygon_id = "multipolygon_id", polygon_id = "polygon_id", linestring_id = "linestring_id")
  expect_equal(res,
               ans)
  expect_true( all( attr(res, "class") == c("sf", "data.frame") ) )


  ## z works
  expect_true(dim(sf_mpoly(cbind(mat, z = 1))[["geometry"]][[1L]][[1L]][[1L]])[2L] == 3L)
  ## m works
  expect_true(dim(sf_mpoly(cbind(mat, m = 0))[["geometry"]][[1L]][[1L]][[1L]])[2L] == 3L)
  ## zm works
  expect_true(dim(sf_mpoly(cbind(mat, z = 2, m = 0))[["geometry"]][[1L]][[1L]][[1L]])[2L] == 4L)
  ## keep works
  expect_equal(dim(sf_mpoly(cbind(mat, m = 0, cactus = 1:5, keepmetoo = 2))), c(1L, 2L))
  kept <- sf_mpoly(cbind(mat, m = 0, cactus = 1:5), keep = TRUE)
  expect_equal(dim(kept), c(1L, 6L))

  kept2 <- sf_mpoly(cbind(mat, m = 0, cactus = 1:5, keepmetoo = 2), keep = TRUE)
  expect_equal(dim(kept2), c(1L, 7L))

})

mm <- structure(list(multipolygon_id = c(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2),
                     polygon_id = c(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1),
                     linestring_id = c(1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1),
                     x = c(0, 0, 0.75, 1, 0.5, 0.8, 0.69, 0, 0.2, 0.5, 0.5, 0.3, 0.2, 0.2, 0.69, 0.8, 1.1, 1.23, 0.69),
                     y = c(0, 1, 1, 0.8, 0.7, 0.6, 0, 0, 0.2, 0.2, 0.4, 0.6, 0.4, 0.2, 0, 0.6, 0.63, 0.3, 0)),
                class = "data.frame", row.names = c(NA, 19L))
mm$multilinestring_id <- mm$multipoint_id <- mm$multipolygon_id

test_that("various helpers work", {
  expect_equal(sf_pt(mm), sf_point(mm, x = "x", y = "y"))
  expect_equal(sf_mpt(mm), sf_multipoint(mm, x = "x", y = "y", multipoint_id = "multipoint_id"))
  expect_equal(sf_mpt(mm, keep = TRUE), sf_multipoint(mm, x = "x", y = "y", multipoint_id = "multipoint_id", keep = TRUE))

  mm_line <- mm[order(mm$linestring_id), ]
  expect_equal(sf_line(mm_line), sf_linestring(mm_line, x = "x", y = "y", linestring_id = "linestring_id"))
  expect_equal(sf_line(mm_line, keep = TRUE), sf_linestring(mm_line, x = "x", y = "y", linestring_id = "linestring_id", keep = TRUE))

  expect_equal(sf_mline(mm), sf_multilinestring(mm, x = "x", y = "y",
                                                multilinestring_id = "multilinestring_id",
                                                linestring_id = "linestring_id"))
  expect_equal(sf_mline(mm, keep = TRUE), sf_multilinestring(mm, x = "x", y = "y",
                                                multilinestring_id = "multilinestring_id",
                                                linestring_id = "linestring_id",
                                                keep = TRUE))

  ## for polygon, the polygon id did not change so we have to copy down the feature (mpoly) iD
  mm_poly <- mm
  mm_poly$polygon_id <- mm_poly$multipolygon_id
 expect_equal(sf_poly(mm_poly),
              sf_polygon(mm_poly, x = "x", y = "y", linestring_id =  "linestring_id", polygon_id = "polygon_id"))
})


test_that("closing is the default, and succeeds", {
  mm1 <- mm
  mm1$polygon_id <- mm1$multipolygon_id
  mm1 <- head(mm1, -1)
  expect_equal(dim(sf_poly(mm1)$geometry[[2]][[1]]), c(5L, 2L))

  expect_equal(dim(sf_poly(mm1, close = TRUE)$geometry[[2]][[1]]), c(5L, 2L))

  expect_equal(dim(sf_poly(mm1, close = FALSE)$geometry[[2]][[1]]), c(4L, 2L))

})

test_that("list-columns kept",{

  df <- data.frame(
    x = 1:26
    , y = 1:26
    , val = letters
    , polygon_id = c(rep(1:2,each=12),3,3)
    , linestring_id = c(rep(1:5,each=5),6)
    , stringsAsFactors = FALSE
  )


  res1 <- sf_line(
    obj = df
    , list_columns = c("val")
  )

  res2 <- sf_linestring(
    obj = df
    , x = "x"
    , y = "y"
    , linestring_id = "linestring_id"
    , list_columns = "val"
  )

  expect_equal( res1, res2 )


  res1 <- sf_poly(
    obj = df
    , close = FALSE
    , list_columns = c("val")
  )

  res2 <- sf_polygon(
    obj = df
    , x = "x"
    , y = "y"
    , polygon_id = "polygon_id"
    , linestring_id = "linestring_id"
    , list_columns = "val"
    , close = FALSE
  )

  expect_equal( res1, res2 )

})
