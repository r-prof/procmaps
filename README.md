
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
#> 55ac4e290000-55ac4e298000 r-xp 00000000 fd:01 2883652                    /bin/cat
#> 55ac4e497000-55ac4e498000 r--p 00007000 fd:01 2883652                    /bin/cat
#> 55ac4e498000-55ac4e499000 rw-p 00008000 fd:01 2883652                    /bin/cat
#> 55ac4ea08000-55ac4ea29000 rw-p 00000000 00:00 0                          [heap]
#> 7fa87aa60000-7fa87aebf000 r--p 00000000 fd:01 29370411                   /usr/lib/locale/locale-archive
#> 7fa87aebf000-7fa87b0a6000 r-xp 00000000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so
#> 7fa87b0a6000-7fa87b2a6000 ---p 001e7000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so
#> 7fa87b2a6000-7fa87b2aa000 r--p 001e7000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so
#> 7fa87b2aa000-7fa87b2ac000 rw-p 001eb000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so
#> 7fa87b2ac000-7fa87b2b0000 rw-p 00000000 00:00 0 
#> 7fa87b2b0000-7fa87b2d7000 r-xp 00000000 fd:01 15731135                   /lib/x86_64-linux-gnu/ld-2.27.so
#> 7fa87b4aa000-7fa87b4ac000 rw-p 00000000 00:00 0 
#> 7fa87b4b5000-7fa87b4d7000 rw-p 00000000 00:00 0 
#> 7fa87b4d7000-7fa87b4d8000 r--p 00027000 fd:01 15731135                   /lib/x86_64-linux-gnu/ld-2.27.so
#> 7fa87b4d8000-7fa87b4d9000 rw-p 00028000 fd:01 15731135                   /lib/x86_64-linux-gnu/ld-2.27.so
#> 7fa87b4d9000-7fa87b4da000 rw-p 00000000 00:00 0 
#> 7ffe08f77000-7ffe08f99000 rw-p 00000000 00:00 0                          [stack]
#> 7ffe08fa2000-7ffe08fa5000 r--p 00000000 00:00 0                          [vvar]
#> 7ffe08fa5000-7ffe08fa7000 r-xp 00000000 00:00 0                          [vdso]
#> ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
```

This package provides the equivalent as a data frame:

``` r
library(procmaps)
procmap_get()
#>            from           to perms   offset   dev    inode
#> 1  555805c51000 555805c52000  r-xp 00000000 00:00 29393780
#> 2  555805e51000 555805e52000  r--p 00000000 00:00 29393780
#> 3  555805e52000 555805e53000  rw-p 00001000 00:00 29393780
#> 4  555807755000 55580c50f000  rw-p 00000000 00:00        0
#> 5  7ff23a6a6000 7ff23a6aa000  r-xp 00000000 00:00 28978704
#> 6  7ff23a6aa000 7ff23a8a9000  ---p 00004000 00:00 28978704
#> 7  7ff23a8a9000 7ff23a8aa000  r--p 00003000 00:00 28978704
#> 8  7ff23a8aa000 7ff23a8ab000  rw-p 00004000 00:00 28978704
#> 9  7ff23a8ab000 7ff23a8af000  rw-p 00000000 00:00        0
#> 10 7ff23a8af000 7ff23a8b1000  r-xp 00000000 00:00 28722648
#> 11 7ff23a8b1000 7ff23aab0000  ---p 00002000 00:00 28722648
#> 12 7ff23aab0000 7ff23aab1000  r--p 00001000 00:00 28722648
#> 13 7ff23aab1000 7ff23aab2000  rw-p 00002000 00:00 28722648
#> 14 7ff23aab2000 7ff23aac6000  r-xp 00000000 00:00 28722678
#>                                              pathname
#> 1                               /usr/lib/R/bin/exec/R
#> 2                               /usr/lib/R/bin/exec/R
#> 3                               /usr/lib/R/bin/exec/R
#> 4                                              [heap]
#> 5  /home/kirill/git/R/r-prof/procmaps/src/procmaps.so
#> 6  /home/kirill/git/R/r-prof/procmaps/src/procmaps.so
#> 7  /home/kirill/git/R/r-prof/procmaps/src/procmaps.so
#> 8  /home/kirill/git/R/r-prof/procmaps/src/procmaps.so
#> 9                                                    
#> 10               /home/kirill/R-dev/glue/libs/glue.so
#> 11               /home/kirill/R-dev/glue/libs/glue.so
#> 12               /home/kirill/R-dev/glue/libs/glue.so
#> 13               /home/kirill/R-dev/glue/libs/glue.so
#> 14             /home/kirill/R-dev/fansi/libs/fansi.so
#>  [ reached 'max' / getOption("max.print") -- omitted 357 rows ]
```
