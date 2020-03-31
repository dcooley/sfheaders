context("to_rline")

data(emisco)
emisco <- emisco[1 ,]
df2 <- data.frame(
  Group = format(1, width = 5))
df2$X_b = as.character(format(-46.74635, width = 10))
df2$Y_b = as.character(format(-23.60534, width = 10))
df2$Z_b = as.character(format(0, width = 5))
df2$X_e = as.character(format(-46.74635, width = 10))
df2$Y_e = as.character(format(-23.60534, width = 10))
df2$Z_e = as.character(format(0, width = 5))
df2$dCL = as.character(format(0, width = 5))
df2$sigma0 = as.character(format(2, width = 9))
df2$lanes = as.character(format(2, width = 7))
df2$Emis = as.character(format(13191.88, width = 6))
df2$Hw1 = as.character(format(0,width = 5))
df2$dw1 = as.character(format(0,width = 5))
df2$Hw2 = as.character(format(0,width = 5))
df2$dw2 = as.character(format(0, width = 5))
df2$Depth = as.character(format(0, width = 7))
df2$Wtop = as.character(format(0, width = 7))
df2$Wbottom = as.character(format(0, width = 9)
)

test_that("to_rline works", {
  expect_equal(to_rline(X_b = emisco$xmin,
                        Y_b = emisco$ymin,
                        Z_b =0,
                        X_e = emisco$xmin,
                        Y_e = emisco$ymin,
                        Z_e = 0,
                        dCL = 0,
                        Emis = as.numeric(emisco$V8),
                        sigmaz0 = 2,
                        lanes = emisco$lanes),
               df2
               )
})
test_that("to_rline works", {
  expect_equal(to_rline(X_b = emisco$xmin,
                        Y_b = emisco$ymin,
                        Z_b = 0,
                        X_e = emisco$xmin,
                        Y_e = emisco$ymin,
                        Z_e = 0,
                        dCL = 0,
                        sigmaz0 = 2,
                        lanes = emisco$lanes,
                        Emis = as.numeric(emisco$V8),
                        Hw1 = 0,
                        dw1 = 0,
                        Hw2 = 0,
                        dw2 = 0,
                        Depth = 0,
                        Wtop = 0,
                        Wbottom = 0,
                        experimental = TRUE),
               df2
  )
})
