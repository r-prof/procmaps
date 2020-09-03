
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
#> 5585ba6c4000-5585ba6cc000 r-xp 00000000 fd:01 2883652                    /bin/cat
#> 5585ba8cb000-5585ba8cc000 r--p 00007000 fd:01 2883652                    /bin/cat
#> 5585ba8cc000-5585ba8cd000 rw-p 00008000 fd:01 2883652                    /bin/cat
#> 5585bb092000-5585bb0b3000 rw-p 00000000 00:00 0                          [heap]
#> 7f70f7b21000-7f70f7f80000 r--p 00000000 fd:01 29370411                   /usr/lib/locale/locale-archive
#> 7f70f7f80000-7f70f8167000 r-xp 00000000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so
#> 7f70f8167000-7f70f8367000 ---p 001e7000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so
#> 7f70f8367000-7f70f836b000 r--p 001e7000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so
#> 7f70f836b000-7f70f836d000 rw-p 001eb000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so
#> 7f70f836d000-7f70f8371000 rw-p 00000000 00:00 0 
#> 7f70f8371000-7f70f8398000 r-xp 00000000 fd:01 15731135                   /lib/x86_64-linux-gnu/ld-2.27.so
#> 7f70f856b000-7f70f856d000 rw-p 00000000 00:00 0 
#> 7f70f8576000-7f70f8598000 rw-p 00000000 00:00 0 
#> 7f70f8598000-7f70f8599000 r--p 00027000 fd:01 15731135                   /lib/x86_64-linux-gnu/ld-2.27.so
#> 7f70f8599000-7f70f859a000 rw-p 00028000 fd:01 15731135                   /lib/x86_64-linux-gnu/ld-2.27.so
#> 7f70f859a000-7f70f859b000 rw-p 00000000 00:00 0 
#> 7fff62050000-7fff62072000 rw-p 00000000 00:00 0                          [stack]
#> 7fff621f0000-7fff621f3000 r--p 00000000 00:00 0                          [vvar]
#> 7fff621f3000-7fff621f5000 r-xp 00000000 00:00 0                          [vdso]
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
#>  1 55b1321f… 55b1321f… r-xp  000000… 00:00 "293937… /usr/lib/R/bin/exec/R       
#>  2 55b1323f… 55b1323f… r--p  000000… 00:00 "293937… /usr/lib/R/bin/exec/R       
#>  3 55b1323f… 55b1323f… rw-p  000010… 00:00 "293937… /usr/lib/R/bin/exec/R       
#>  4 55b1325d… 55b13740… rw-p  000000… 00:00 "0     … [heap]                      
#>  5 7f0b9722… 7f0b9722… r-xp  000000… 00:00 "289787… /home/kirill/git/R/r-prof/p…
#>  6 7f0b9722… 7f0b9742… ---p  000030… 00:00 "289787… /home/kirill/git/R/r-prof/p…
#>  7 7f0b9742… 7f0b9742… r--p  000030… 00:00 "289787… /home/kirill/git/R/r-prof/p…
#>  8 7f0b9742… 7f0b9742… rw-p  000040… 00:00 "289787… /home/kirill/git/R/r-prof/p…
#>  9 7f0b9742… 7f0b9742… r-xp  000000… 00:00 "287226… /home/kirill/R-dev/glue/lib…
#> 10 7f0b9742… 7f0b9762… ---p  000020… 00:00 "287226… /home/kirill/R-dev/glue/lib…
#> # … with 360 more rows
```
