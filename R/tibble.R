as_tibble_if <- function(data, as_tibble) {
  as_tibble <- check_as_tibble(as_tibble)

  if (isTRUE(as_tibble)) {
    tibble::as_tibble(data)
  } else {
    as.data.frame(data, stringsAsFactors = FALSE)
  }
}

make_check_as_tibble <- function() {
  checked <- FALSE
  tibble_available <- NA

  function(as_tibble) {
    if (!is.null(as_tibble) && is.na(as_tibble)) {
      checked <<- FALSE
      tibble_available <<- NA
      return(FALSE)
    }
    if (!is.null(as_tibble)) {
      return(as_tibble)
    }

    if (!checked) {
      tibble_available <<- requireNamespace("tibble", quietly = TRUE)
      if (tibble_available) {
        message("Converting to tibble, mute this message with `as_tibble = TRUE`.")
      } else {
        message("Install tibble to convert to tibble, mute this message with `as_tibble = FALSE`.")
      }
      checked <<- TRUE
    }
    tibble_available
  }
}

check_as_tibble <- make_check_as_tibble()
