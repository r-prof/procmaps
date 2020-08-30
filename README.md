
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

This is what `/proc/self/maps` looks like (on Linux) when this document
is rendered:

``` bash
cat /proc/self/maps
#> 56224a7da000-56224a7e2000 r-xp 00000000 fd:01 2883652                    /bin/cat
#> 56224a9e1000-56224a9e2000 r--p 00007000 fd:01 2883652                    /bin/cat
#> 56224a9e2000-56224a9e3000 rw-p 00008000 fd:01 2883652                    /bin/cat
#> 56224aba9000-56224abca000 rw-p 00000000 00:00 0                          [heap]
#> 7fb8f1a69000-7fb8f1ec8000 r--p 00000000 fd:01 29370411                   /usr/lib/locale/locale-archive
#> 7fb8f1ec8000-7fb8f20af000 r-xp 00000000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so
#> 7fb8f20af000-7fb8f22af000 ---p 001e7000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so
#> 7fb8f22af000-7fb8f22b3000 r--p 001e7000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so
#> 7fb8f22b3000-7fb8f22b5000 rw-p 001eb000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so
#> 7fb8f22b5000-7fb8f22b9000 rw-p 00000000 00:00 0 
#> 7fb8f22b9000-7fb8f22e0000 r-xp 00000000 fd:01 15731135                   /lib/x86_64-linux-gnu/ld-2.27.so
#> 7fb8f24b3000-7fb8f24b5000 rw-p 00000000 00:00 0 
#> 7fb8f24be000-7fb8f24e0000 rw-p 00000000 00:00 0 
#> 7fb8f24e0000-7fb8f24e1000 r--p 00027000 fd:01 15731135                   /lib/x86_64-linux-gnu/ld-2.27.so
#> 7fb8f24e1000-7fb8f24e2000 rw-p 00028000 fd:01 15731135                   /lib/x86_64-linux-gnu/ld-2.27.so
#> 7fb8f24e2000-7fb8f24e3000 rw-p 00000000 00:00 0 
#> 7ffe12bbe000-7ffe12be0000 rw-p 00000000 00:00 0                          [stack]
#> 7ffe12bf0000-7ffe12bf3000 r--p 00000000 00:00 0                          [vvar]
#> 7ffe12bf3000-7ffe12bf5000 r-xp 00000000 00:00 0                          [vdso]
#> ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
```

Other operating systems make this information available in other form.
This package provides the equivalent as a data frame, regardless of
operating system:

``` r
library(procmaps)
procmap_get()
#> Converting to tibble, mute this message with `as_tibble = TRUE`.
#> # A tibble: 371 x 7
#>    from      to       perms offset  dev     inode pathname                      
#>    <chr>     <chr>    <chr> <chr>   <chr>   <dbl> <chr>                         
#>  1 557e12de… 557e12d… r-xp  000000… 00:00  2.94e7 "/usr/lib/R/bin/exec/R"       
#>  2 557e12fe… 557e12f… r--p  000000… 00:00  2.94e7 "/usr/lib/R/bin/exec/R"       
#>  3 557e12fe… 557e12f… rw-p  000010… 00:00  2.94e7 "/usr/lib/R/bin/exec/R"       
#>  4 557e14da… 557e19b… rw-p  000000… 00:00  0.     "[heap]"                      
#>  5 7f2a79d1… 7f2a79d… r-xp  000000… 00:00  2.90e7 "/home/kirill/git/R/r-prof/pr…
#>  6 7f2a79d1… 7f2a79f… ---p  000040… 00:00  2.90e7 "/home/kirill/git/R/r-prof/pr…
#>  7 7f2a79f1… 7f2a79f… r--p  000030… 00:00  2.90e7 "/home/kirill/git/R/r-prof/pr…
#>  8 7f2a79f1… 7f2a79f… rw-p  000040… 00:00  2.90e7 "/home/kirill/git/R/r-prof/pr…
#>  9 7f2a79f1… 7f2a79f… rw-p  000000… 00:00  0.     ""                            
#> 10 7f2a79f1… 7f2a79f… r-xp  000000… 00:00  2.87e7 "/home/kirill/R-dev/glue/libs…
#> # … with 361 more rows
```
