
<!-- README.md is generated from README.Rmd. Please edit that file -->

# procmaps

<!-- badges: start -->

[![Lifecycle:
experimental](https://img.shields.io/badge/lifecycle-experimental-orange.svg)](https://www.tidyverse.org/lifecycle/#experimental)
<!-- badges: end -->

The goal of procmaps is to help determine which library or other region
is mapped to a specific address of a process. It is the equivalent of
`/proc/self/maps` as a data frame, and is designed to work on all major
platforms.

## Installation

You can install the released version of procmaps from
[CRAN](https://CRAN.R-project.org) with:

``` r
install.packages("procmaps")
```

## Example

This is what `/proc/self/maps` looks like when this document is
rendered:

``` bash
cat /proc/self/maps
#> 55d7c0a61000-55d7c0a69000 r-xp 00000000 fd:01 2883652                    /bin/cat
#> 55d7c0c68000-55d7c0c69000 r--p 00007000 fd:01 2883652                    /bin/cat
#> 55d7c0c69000-55d7c0c6a000 rw-p 00008000 fd:01 2883652                    /bin/cat
#> 55d7c2396000-55d7c23b7000 rw-p 00000000 00:00 0                          [heap]
#> 7fe1cf912000-7fe1cfd71000 r--p 00000000 fd:01 29370411                   /usr/lib/locale/locale-archive
#> 7fe1cfd71000-7fe1cff58000 r-xp 00000000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so
#> 7fe1cff58000-7fe1d0158000 ---p 001e7000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so
#> 7fe1d0158000-7fe1d015c000 r--p 001e7000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so
#> 7fe1d015c000-7fe1d015e000 rw-p 001eb000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so
#> 7fe1d015e000-7fe1d0162000 rw-p 00000000 00:00 0 
#> 7fe1d0162000-7fe1d0189000 r-xp 00000000 fd:01 15731135                   /lib/x86_64-linux-gnu/ld-2.27.so
#> 7fe1d035c000-7fe1d035e000 rw-p 00000000 00:00 0 
#> 7fe1d0367000-7fe1d0389000 rw-p 00000000 00:00 0 
#> 7fe1d0389000-7fe1d038a000 r--p 00027000 fd:01 15731135                   /lib/x86_64-linux-gnu/ld-2.27.so
#> 7fe1d038a000-7fe1d038b000 rw-p 00028000 fd:01 15731135                   /lib/x86_64-linux-gnu/ld-2.27.so
#> 7fe1d038b000-7fe1d038c000 rw-p 00000000 00:00 0 
#> 7fff18b00000-7fff18b22000 rw-p 00000000 00:00 0                          [stack]
#> 7fff18b8e000-7fff18b91000 r--p 00000000 00:00 0                          [vvar]
#> 7fff18b91000-7fff18b93000 r-xp 00000000 00:00 0                          [vdso]
#> ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
```

This package provides the equivalent as a data frame:

``` r
library(procmaps)
procmap_get()
```
