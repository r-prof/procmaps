#' Get the address space map of a process
#'
#' Returns the address space map of a process as a data frame.
#'
#' @param ... Reserved for future extensions, must be empty.
#' @param as_tibble When using in a package, set to `TRUE` to return a
#'   [tibble::tibble].
#'   This requires the tibble package to be installed.
#'   The default returns a tibble if the package is installed, otherwise a
#'   data frame.
#' @return A data frame or tibble, depending on the `as_tibble` argument.
#' @export
#' @examples
#' procmap_get()
procmap_get <- function(..., as_tibble = NULL) {
  if (length(list(...)) > 0) {
    stop("... must be empty.", call. = FALSE)
  }

  data <- .Call(procmaps_c_procmap_get_df)
  names(data) <- c("from", "to", "perms", "offset", "inode", "pathname")

  as_tibble_if(data, as_tibble)
}
