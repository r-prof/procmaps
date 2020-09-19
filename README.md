<!-- README.md is generated from README.Rmd. Please edit that file -->

# procmaps

<!-- badges: start -->

[![Lifecycle: experimental](https://img.shields.io/badge/lifecycle-experimental-orange.svg)](https://www.tidyverse.org/lifecycle/#experimental) [![R build status](https://github.com/r-prof/procmaps/workflows/rcc/badge.svg)](https://github.com/r-prof/procmaps/actions) [![Codecov test coverage](https://codecov.io/gh/r-prof/procmaps/branch/master/graph/badge.svg)](https://codecov.io/gh/r-prof/procmaps?branch=master) [![CRAN status](https://www.r-pkg.org/badges/version/procmaps)](https://CRAN.R-project.org/package=procmaps)

<!-- badges: end -->

The goal of procmaps is to help determine which library or other region is mapped to a specific address of a process. It is the equivalent of `/proc/self/maps` as a data frame, and is designed to work on all major platforms.

## Installation

You can install the released version of procmaps from [CRAN](https://CRAN.R-project.org) with:

<pre class='chroma'>
<span class='nf'><a href='https://rdrr.io/r/utils/install.packages.html'>install.packages</a></span>(<span class='s'>"procmaps"</span>)
</pre>

## Example

This is what `/proc/self/maps` looks like (on Linux) when this document is rendered:

<pre class='chroma'>
<span class='k'>cat</span> <span class='o'>/</span><span class='k'>proc</span><span class='o'>/</span><span class='k'>self</span><span class='o'>/</span><span class='k'>maps</span>
<span class='c'>#&gt; 560233612000-56023361a000 r-xp 00000000 fd:01 2883652                    /bin/cat</span>
<span class='c'>#&gt; 560233819000-56023381a000 r--p 00007000 fd:01 2883652                    /bin/cat</span>
<span class='c'>#&gt; 56023381a000-56023381b000 rw-p 00008000 fd:01 2883652                    /bin/cat</span>
<span class='c'>#&gt; 560234853000-560234874000 rw-p 00000000 00:00 0                          [heap]</span>
<span class='c'>#&gt; 7fb275252000-7fb2756b1000 r--p 00000000 fd:01 29370411                   /usr/lib/locale/locale-archive</span>
<span class='c'>#&gt; 7fb2756b1000-7fb275898000 r-xp 00000000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so</span>
<span class='c'>#&gt; 7fb275898000-7fb275a98000 ---p 001e7000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so</span>
<span class='c'>#&gt; 7fb275a98000-7fb275a9c000 r--p 001e7000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so</span>
<span class='c'>#&gt; 7fb275a9c000-7fb275a9e000 rw-p 001eb000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so</span>
<span class='c'>#&gt; 7fb275a9e000-7fb275aa2000 rw-p 00000000 00:00 0 </span>
<span class='c'>#&gt; 7fb275aa2000-7fb275ac9000 r-xp 00000000 fd:01 15731135                   /lib/x86_64-linux-gnu/ld-2.27.so</span>
<span class='c'>#&gt; 7fb275c9c000-7fb275c9e000 rw-p 00000000 00:00 0 </span>
<span class='c'>#&gt; 7fb275ca7000-7fb275cc9000 rw-p 00000000 00:00 0 </span>
<span class='c'>#&gt; 7fb275cc9000-7fb275cca000 r--p 00027000 fd:01 15731135                   /lib/x86_64-linux-gnu/ld-2.27.so</span>
<span class='c'>#&gt; 7fb275cca000-7fb275ccb000 rw-p 00028000 fd:01 15731135                   /lib/x86_64-linux-gnu/ld-2.27.so</span>
<span class='c'>#&gt; 7fb275ccb000-7fb275ccc000 rw-p 00000000 00:00 0 </span>
<span class='c'>#&gt; 7ffd8659b000-7ffd865bd000 rw-p 00000000 00:00 0                          [stack]</span>
<span class='c'>#&gt; 7ffd865c8000-7ffd865cb000 r--p 00000000 00:00 0                          [vvar]</span>
<span class='c'>#&gt; 7ffd865cb000-7ffd865cd000 r-xp 00000000 00:00 0                          [vdso]</span>
<span class='c'>#&gt; ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]</span>
</pre>

Other operating systems make this information available in other form. This package provides the equivalent as a data frame, regardless of operating system:

<pre class='chroma'>
<span class='nf'><a href='https://rdrr.io/r/base/library.html'>library</a></span>(<span class='k'><a href='https://r-prof.github.io/procmaps/'>procmaps</a></span>)
<span class='nf'><a href='https://r-prof.github.io/procmaps/reference/procmap_get.html'>procmap_get</a></span>()
<span class='c'>#&gt; Converting to tibble, mute this message with `as_tibble = TRUE`.</span>
<span class='c'>#&gt; <span style='color: #949494;'># A tibble: 378 x 6</span></span>
<span class='c'>#&gt;    <span style='font-weight: bold;'>from</span><span>         </span><span style='font-weight: bold;'>to</span><span>          </span><span style='font-weight: bold;'>perms</span><span> </span><span style='font-weight: bold;'>offset</span><span>  </span><span style='font-weight: bold;'>inode</span><span>  </span><span style='font-weight: bold;'>pathname</span><span>                       </span></span>
<span class='c'>#&gt;    <span style='color: #949494;font-style: italic;'>&lt;chr&gt;</span><span>        </span><span style='color: #949494;font-style: italic;'>&lt;chr&gt;</span><span>       </span><span style='color: #949494;font-style: italic;'>&lt;chr&gt;</span><span> </span><span style='color: #949494;font-style: italic;'>&lt;chr&gt;</span><span>   </span><span style='color: #949494;font-style: italic;'>&lt;chr&gt;</span><span>  </span><span style='color: #949494;font-style: italic;'>&lt;chr&gt;</span><span>                          </span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 1</span><span> 000055ef44f… 000055ef44… r-xp  000000… 29393… /usr/lib/R/bin/exec/R          </span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 2</span><span> 000055ef451… 000055ef45… r--p  000000… 29393… /usr/lib/R/bin/exec/R          </span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 3</span><span> 000055ef451… 000055ef45… rw-p  000010… 29393… /usr/lib/R/bin/exec/R          </span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 4</span><span> 000055ef467… 000055ef4b… rw-p  000000… 0      [heap]                         </span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 5</span><span> 00007f5a460… 00007f5a46… r-xp  000000… 29024… /home/kirill/git/R/r-prof/proc…</span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 6</span><span> 00007f5a460… 00007f5a46… ---p  000030… 29024… /home/kirill/git/R/r-prof/proc…</span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 7</span><span> 00007f5a462… 00007f5a46… r--p  000020… 29024… /home/kirill/git/R/r-prof/proc…</span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 8</span><span> 00007f5a462… 00007f5a46… rw-p  000030… 29024… /home/kirill/git/R/r-prof/proc…</span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 9</span><span> 00007f5a462… 00007f5a46… r-xp  000000… 28722… /home/kirill/R-dev/glue/libs/g…</span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'>10</span><span> 00007f5a462… 00007f5a46… ---p  000020… 28722… /home/kirill/R-dev/glue/libs/g…</span></span>
<span class='c'>#&gt; <span style='color: #949494;'># … with 368 more rows</span></span>
</pre>

-----

## Code of Conduct

Please note that the procmaps project is released with a [Contributor Code of Conduct](https://contributor-covenant.org/version/2/0/CODE_OF_CONDUCT.html). By contributing to this project, you agree to abide by its terms.
