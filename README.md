
<!-- README.md is generated from README.Rmd. Please edit that file -->

# procmaps

<!-- badges: start -->

[![Lifecycle:
experimental](https://img.shields.io/badge/lifecycle-experimental-orange.svg)](https://www.tidyverse.org/lifecycle/#experimental)
[![CRAN
status](https://www.r-pkg.org/badges/version/procmaps)](https://CRAN.R-project.org/package=procmaps)
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
#> 5590aafac000-5590aafb4000 r-xp 00000000 fd:01 2883652                    /bin/cat
#> 5590ab1b3000-5590ab1b4000 r--p 00007000 fd:01 2883652                    /bin/cat
#> 5590ab1b4000-5590ab1b5000 rw-p 00008000 fd:01 2883652                    /bin/cat
#> 5590abca7000-5590abcc8000 rw-p 00000000 00:00 0                          [heap]
#> 7f12597a7000-7f1259c06000 r--p 00000000 fd:01 29370411                   /usr/lib/locale/locale-archive
#> 7f1259c06000-7f1259ded000 r-xp 00000000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so
#> 7f1259ded000-7f1259fed000 ---p 001e7000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so
#> 7f1259fed000-7f1259ff1000 r--p 001e7000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so
#> 7f1259ff1000-7f1259ff3000 rw-p 001eb000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so
#> 7f1259ff3000-7f1259ff7000 rw-p 00000000 00:00 0 
#> 7f1259ff7000-7f125a01e000 r-xp 00000000 fd:01 15731135                   /lib/x86_64-linux-gnu/ld-2.27.so
#> 7f125a1f1000-7f125a1f3000 rw-p 00000000 00:00 0 
#> 7f125a1fc000-7f125a21e000 rw-p 00000000 00:00 0 
#> 7f125a21e000-7f125a21f000 r--p 00027000 fd:01 15731135                   /lib/x86_64-linux-gnu/ld-2.27.so
#> 7f125a21f000-7f125a220000 rw-p 00028000 fd:01 15731135                   /lib/x86_64-linux-gnu/ld-2.27.so
#> 7f125a220000-7f125a221000 rw-p 00000000 00:00 0 
#> 7fffea873000-7fffea895000 rw-p 00000000 00:00 0                          [stack]
#> 7fffea9b3000-7fffea9b6000 r--p 00000000 00:00 0                          [vvar]
#> 7fffea9b6000-7fffea9b8000 r-xp 00000000 00:00 0                          [vdso]
#> ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
```

Other operating systems make this information available in other form.
This package provides the equivalent as a data frame, regardless of
operating system:

``` r
library(procmaps)
procmap_get()
#> Converting to tibble, mute this message with `as_tibble = TRUE`.
#> # A tibble: 370 x 7
#>    from      to        perms offset  dev   inode    pathname                    
#>    <chr>     <chr>     <chr> <chr>   <chr> <chr>    <chr>                       
#>  1 55b250f0… 55b250f0… r-xp  000000… 00:00 "293937… /usr/lib/R/bin/exec/R       
#>  2 55b25110… 55b25110… r--p  000000… 00:00 "293937… /usr/lib/R/bin/exec/R       
#>  3 55b25110… 55b25110… rw-p  000010… 00:00 "293937… /usr/lib/R/bin/exec/R       
#>  4 55b25147… 55b2562a… rw-p  000000… 00:00 "0     … [heap]                      
#>  5 7f42857a… 7f42857a… r-xp  000000… 00:00 "289787… /home/kirill/git/R/r-prof/p…
#>  6 7f42857a… 7f42859a… ---p  000030… 00:00 "289787… /home/kirill/git/R/r-prof/p…
#>  7 7f42859a… 7f42859a… r--p  000030… 00:00 "289787… /home/kirill/git/R/r-prof/p…
#>  8 7f42859a… 7f42859a… rw-p  000040… 00:00 "289787… /home/kirill/git/R/r-prof/p…
#>  9 7f42859a… 7f42859a… r-xp  000000… 00:00 "287226… /home/kirill/R-dev/glue/lib…
#> 10 7f42859a… 7f4285ba… ---p  000020… 00:00 "287226… /home/kirill/R-dev/glue/lib…
#> # … with 360 more rows
```
