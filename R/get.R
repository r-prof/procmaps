#' Get the address space map of a process
#'
#' Returns the address space map of a process as a data frame.
#'
#' @param as_tibble When using in a package, set to `TRUE` to return a
#'   [tibble::tibble].
#'   This requires the tibble package to be installed.
#'   The default returns a tibble if the package is installed, otherwise a
#'   data frame.
#' @return A data frame or tibble, depending on the `as_tibble` argument.
#' @export
#' @examples
#' procmap_get()
procmap_get <- function(as_tibble = NULL) {
  lines <- .Call(procmaps_c_procmap_get)

  data <- utils::read.delim(text = lines, sep = "\x1f", header = FALSE)
  # https://stackoverflow.com/a/1401595/946850
  names(data) <- c("from", "to", "perms", "offset", "dev", "inode", "pathname")

  as_tibble_if(data, as_tibble)
}
