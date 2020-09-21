test_that("error if ellipsis passed", {
  expect_error(procmap_get(TRUE))
  expect_error(procmap_get(bogus = TRUE))
})

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

  map <- procmap_get(as_tibble = FALSE)
  classes <- unname(lapply(map, class))
  top_class <- vapply(classes, `[[`, 1, FUN.VALUE = character(1))
  expect_equal(top_class, rep("character", length(top_class)))
})

test_that("files exist", {
  paths <- procmap_get(as_tibble = TRUE)$pathname
  paths <- paths[paths != ""]
  paths <- paths[!grepl("^[[]", paths)]
  expect_equal(file.exists(paths), rep(TRUE, length(paths)))

  skip_on_cran()
  lib_r <- path_is_libr(paths)
  expect_gt(sum(lib_r), 0)
})

test_that("addresses are 16 hex digits long", {
  map <- procmap_get(as_tibble = TRUE)
  expect_equal(grepl("[0-9a-f]{16}", map$from), rep(TRUE, nrow(map)))
  expect_equal(grepl("[0-9a-f]{16}", map$to), rep(TRUE, nrow(map)))
})
