test_that("returns data frame or tibble if asked", {
  expect_s3_class(procmap_get(as_tibble = TRUE), "tbl_df")
  expect_s3_class(procmap_get(as_tibble = FALSE), "data.frame")
  expect_message(expect_s3_class(procmap_get(), "tbl_df"))
})

test_that("column data types", {
  map <- procmap_get(as_tibble = TRUE)
  classes <- unname(lapply(map, class))
  top_class <- vapply(classes, `[[`, 1, FUN.VALUE = character(1))
  expect_equal(top_class, rep("character", length(top_class)))
})
