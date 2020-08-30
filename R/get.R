#' Get the address space map of a process
#'
#' Returns the address space map of a process as a data frame.
#'
#' @examples
#' procmap_get()
#' @export
procmap_get <- function() {
  lines <- .Call(procmaps_c_procmap_get)

  data <- read.delim(text = lines, sep = "\x1f", header = FALSE)
  # https://stackoverflow.com/a/1401595/946850
  names(data) <- c("from", "to", "perms", "offset", "dev", "inode", "pathname")

  data
}
