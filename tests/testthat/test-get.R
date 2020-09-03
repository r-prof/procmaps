test_that("returns data frame or tibble if asked", {
  expect_s3_class(procmap_get(as_tibble = TRUE), "tbl_df")
  expect_s3_class(procmap_get(as_tibble = FALSE), "data.frame")
  expect_message(expect_s3_class(procmap_get(), "tbl_df"))
})
