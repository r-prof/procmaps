#' Get the address space map of a process
#'
#' Returns the address space map of a process as a data frame.
#'
#' @examples
#' procmap_get()
#' @export
procmap_get <- function() {
  .Call(procmaps_c_procmap_get)
}
