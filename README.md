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
<span class='c'>#&gt; 55f964020000-55f964028000 r-xp 00000000 fd:01 2883652                    /bin/cat</span>
<span class='c'>#&gt; 55f964227000-55f964228000 r--p 00007000 fd:01 2883652                    /bin/cat</span>
<span class='c'>#&gt; 55f964228000-55f964229000 rw-p 00008000 fd:01 2883652                    /bin/cat</span>
<span class='c'>#&gt; 55f9659a9000-55f9659ca000 rw-p 00000000 00:00 0                          [heap]</span>
<span class='c'>#&gt; 7f90e9615000-7f90e9a74000 r--p 00000000 fd:01 29370411                   /usr/lib/locale/locale-archive</span>
<span class='c'>#&gt; 7f90e9a74000-7f90e9c5b000 r-xp 00000000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so</span>
<span class='c'>#&gt; 7f90e9c5b000-7f90e9e5b000 ---p 001e7000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so</span>
<span class='c'>#&gt; 7f90e9e5b000-7f90e9e5f000 r--p 001e7000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so</span>
<span class='c'>#&gt; 7f90e9e5f000-7f90e9e61000 rw-p 001eb000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so</span>
<span class='c'>#&gt; 7f90e9e61000-7f90e9e65000 rw-p 00000000 00:00 0 </span>
<span class='c'>#&gt; 7f90e9e65000-7f90e9e8c000 r-xp 00000000 fd:01 15731135                   /lib/x86_64-linux-gnu/ld-2.27.so</span>
<span class='c'>#&gt; 7f90ea05f000-7f90ea061000 rw-p 00000000 00:00 0 </span>
<span class='c'>#&gt; 7f90ea06a000-7f90ea08c000 rw-p 00000000 00:00 0 </span>
<span class='c'>#&gt; 7f90ea08c000-7f90ea08d000 r--p 00027000 fd:01 15731135                   /lib/x86_64-linux-gnu/ld-2.27.so</span>
<span class='c'>#&gt; 7f90ea08d000-7f90ea08e000 rw-p 00028000 fd:01 15731135                   /lib/x86_64-linux-gnu/ld-2.27.so</span>
<span class='c'>#&gt; 7f90ea08e000-7f90ea08f000 rw-p 00000000 00:00 0 </span>
<span class='c'>#&gt; 7ffc05cfc000-7ffc05d1e000 rw-p 00000000 00:00 0                          [stack]</span>
<span class='c'>#&gt; 7ffc05dd5000-7ffc05dd8000 r--p 00000000 00:00 0                          [vvar]</span>
<span class='c'>#&gt; 7ffc05dd8000-7ffc05dda000 r-xp 00000000 00:00 0                          [vdso]</span>
<span class='c'>#&gt; ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]</span>
</pre>

Other operating systems make this information available in other form. This package provides the equivalent as a data frame, regardless of operating system:

<pre class='chroma'>
<span class='nf'><a href='https://rdrr.io/r/base/library.html'>library</a></span>(<span class='k'><a href='https://github.com/r-prof/procmaps'>procmaps</a></span>)
<span class='nf'><a href='https://rdrr.io/pkg/procmaps/man/procmap_get.html'>procmap_get</a></span>()
<span class='c'>#&gt; Converting to tibble, mute this message with `as_tibble = TRUE`.</span>
<span class='c'>#&gt; <span style='color: #949494;'># A tibble: 374 x 7</span></span>
<span class='c'>#&gt;    <span style='font-weight: bold;'>from</span><span>      </span><span style='font-weight: bold;'>to</span><span>        </span><span style='font-weight: bold;'>perms</span><span> </span><span style='font-weight: bold;'>offset</span><span>  </span><span style='font-weight: bold;'>dev</span><span>   </span><span style='font-weight: bold;'>inode</span><span>    </span><span style='font-weight: bold;'>pathname</span><span>                    </span></span>
<span class='c'>#&gt;    <span style='color: #949494;font-style: italic;'>&lt;chr&gt;</span><span>     </span><span style='color: #949494;font-style: italic;'>&lt;chr&gt;</span><span>     </span><span style='color: #949494;font-style: italic;'>&lt;chr&gt;</span><span> </span><span style='color: #949494;font-style: italic;'>&lt;chr&gt;</span><span>   </span><span style='color: #949494;font-style: italic;'>&lt;chr&gt;</span><span> </span><span style='color: #949494;font-style: italic;'>&lt;chr&gt;</span><span>    </span><span style='color: #949494;font-style: italic;'>&lt;chr&gt;</span><span>                       </span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 1</span><span> 564b1579… 564b1579… r-xp  000000… 00:00 </span><span style='color: #949494;'>"</span><span>293937… /usr/lib/R/bin/exec/R       </span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 2</span><span> 564b1599… 564b1599… r--p  000000… 00:00 </span><span style='color: #949494;'>"</span><span>293937… /usr/lib/R/bin/exec/R       </span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 3</span><span> 564b1599… 564b1599… rw-p  000010… 00:00 </span><span style='color: #949494;'>"</span><span>293937… /usr/lib/R/bin/exec/R       </span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 4</span><span> 564b16aa… 564b1c15… rw-p  000000… 00:00 </span><span style='color: #949494;'>"</span><span>0     … [heap]                      </span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 5</span><span> 7fbcdc9c… 7fbcdc9c… r-xp  000000… 00:00 </span><span style='color: #949494;'>"</span><span>289787… /home/kirill/git/R/r-prof/p…</span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 6</span><span> 7fbcdc9c… 7fbcdcbc… ---p  000030… 00:00 </span><span style='color: #949494;'>"</span><span>289787… /home/kirill/git/R/r-prof/p…</span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 7</span><span> 7fbcdcbc… 7fbcdcbc… r--p  000030… 00:00 </span><span style='color: #949494;'>"</span><span>289787… /home/kirill/git/R/r-prof/p…</span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 8</span><span> 7fbcdcbc… 7fbcdcbc… rw-p  000040… 00:00 </span><span style='color: #949494;'>"</span><span>289787… /home/kirill/git/R/r-prof/p…</span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 9</span><span> 7fbcdcbc… 7fbcdcbc… r-xp  000000… 00:00 </span><span style='color: #949494;'>"</span><span>287226… /home/kirill/R-dev/glue/lib…</span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'>10</span><span> 7fbcdcbc… 7fbcdcdc… ---p  000020… 00:00 </span><span style='color: #949494;'>"</span><span>287226… /home/kirill/R-dev/glue/lib…</span></span>
<span class='c'>#&gt; <span style='color: #949494;'># … with 364 more rows</span></span>
</pre>
