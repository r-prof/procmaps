rx_libr <- paste0("(?:libR|R)", .Platform$dynlib.ext, "$")
rx_r <- "R$"
rx_libr_r <- paste0(rx_libr, "|", rx_r)

#' Does a path represent R's main library?
#'
#' For a vector of paths, checks if the [basename] matches `libR` or `R`.
#' This is useful to detect the addresses occupied by R itself.
#'
#' @param path A character vector of paths
#' @return A logical vector of the same length as `path`.
#' @export
#' @examples
#' map <- procmap_get()
#' path_is_libr(map$pathname)
path_is_libr <- function(path) {
  grepl(rx_libr_r, basename(path))
}
