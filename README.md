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
<span class='c'>#&gt; 55646770b000-556467713000 r-xp 00000000 fd:01 2883652                    /bin/cat</span>
<span class='c'>#&gt; 556467912000-556467913000 r--p 00007000 fd:01 2883652                    /bin/cat</span>
<span class='c'>#&gt; 556467913000-556467914000 rw-p 00008000 fd:01 2883652                    /bin/cat</span>
<span class='c'>#&gt; 5564694da000-5564694fb000 rw-p 00000000 00:00 0                          [heap]</span>
<span class='c'>#&gt; 7f8eed2aa000-7f8eed709000 r--p 00000000 fd:01 29370411                   /usr/lib/locale/locale-archive</span>
<span class='c'>#&gt; 7f8eed709000-7f8eed8f0000 r-xp 00000000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so</span>
<span class='c'>#&gt; 7f8eed8f0000-7f8eedaf0000 ---p 001e7000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so</span>
<span class='c'>#&gt; 7f8eedaf0000-7f8eedaf4000 r--p 001e7000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so</span>
<span class='c'>#&gt; 7f8eedaf4000-7f8eedaf6000 rw-p 001eb000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so</span>
<span class='c'>#&gt; 7f8eedaf6000-7f8eedafa000 rw-p 00000000 00:00 0 </span>
<span class='c'>#&gt; 7f8eedafa000-7f8eedb21000 r-xp 00000000 fd:01 15731135                   /lib/x86_64-linux-gnu/ld-2.27.so</span>
<span class='c'>#&gt; 7f8eedcf4000-7f8eedcf6000 rw-p 00000000 00:00 0 </span>
<span class='c'>#&gt; 7f8eedcff000-7f8eedd21000 rw-p 00000000 00:00 0 </span>
<span class='c'>#&gt; 7f8eedd21000-7f8eedd22000 r--p 00027000 fd:01 15731135                   /lib/x86_64-linux-gnu/ld-2.27.so</span>
<span class='c'>#&gt; 7f8eedd22000-7f8eedd23000 rw-p 00028000 fd:01 15731135                   /lib/x86_64-linux-gnu/ld-2.27.so</span>
<span class='c'>#&gt; 7f8eedd23000-7f8eedd24000 rw-p 00000000 00:00 0 </span>
<span class='c'>#&gt; 7ffcffef8000-7ffcfff1a000 rw-p 00000000 00:00 0                          [stack]</span>
<span class='c'>#&gt; 7ffcffff1000-7ffcffff4000 r--p 00000000 00:00 0                          [vvar]</span>
<span class='c'>#&gt; 7ffcffff4000-7ffcffff6000 r-xp 00000000 00:00 0                          [vdso]</span>
<span class='c'>#&gt; ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]</span>
</pre>

Other operating systems make this information available in other form. This package provides the equivalent as a data frame, regardless of operating system:

<pre class='chroma'>
<span class='nf'><a href='https://rdrr.io/r/base/library.html'>library</a></span>(<span class='k'><a href='https://r-prof.github.io/procmaps/'>procmaps</a></span>)
<span class='nf'><a href='https://r-prof.github.io/procmaps/reference/procmap_get.html'>procmap_get</a></span>()
<span class='c'>#&gt; Converting to tibble, mute this message with `as_tibble = TRUE`.</span>
<span class='c'>#&gt; <span style='color: #949494;'># A tibble: 374 x 7</span></span>
<span class='c'>#&gt;    <span style='font-weight: bold;'>from</span><span>       </span><span style='font-weight: bold;'>to</span><span>         </span><span style='font-weight: bold;'>perms</span><span> </span><span style='font-weight: bold;'>offset</span><span>  </span><span style='font-weight: bold;'>dev</span><span>   </span><span style='font-weight: bold;'>inode</span><span>    </span><span style='font-weight: bold;'>pathname</span><span>                  </span></span>
<span class='c'>#&gt;    <span style='color: #949494;font-style: italic;'>&lt;chr&gt;</span><span>      </span><span style='color: #949494;font-style: italic;'>&lt;chr&gt;</span><span>      </span><span style='color: #949494;font-style: italic;'>&lt;chr&gt;</span><span> </span><span style='color: #949494;font-style: italic;'>&lt;chr&gt;</span><span>   </span><span style='color: #949494;font-style: italic;'>&lt;chr&gt;</span><span> </span><span style='color: #949494;font-style: italic;'>&lt;chr&gt;</span><span>    </span><span style='color: #949494;font-style: italic;'>&lt;chr&gt;</span><span>                     </span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 1</span><span> 000055628… 000055628… r-xp  000000… 00:00 </span><span style='color: #949494;'>"</span><span>293937… /usr/lib/R/bin/exec/R     </span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 2</span><span> 000055629… 000055629… r--p  000000… 00:00 </span><span style='color: #949494;'>"</span><span>293937… /usr/lib/R/bin/exec/R     </span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 3</span><span> 000055629… 000055629… rw-p  000010… 00:00 </span><span style='color: #949494;'>"</span><span>293937… /usr/lib/R/bin/exec/R     </span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 4</span><span> 000055629… 000055629… rw-p  000000… 00:00 </span><span style='color: #949494;'>"</span><span>0     … [heap]                    </span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 5</span><span> 00007f63e… 00007f63e… r-xp  000000… 00:00 </span><span style='color: #949494;'>"</span><span>289787… /home/kirill/git/R/r-prof…</span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 6</span><span> 00007f63e… 00007f63e… ---p  000030… 00:00 </span><span style='color: #949494;'>"</span><span>289787… /home/kirill/git/R/r-prof…</span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 7</span><span> 00007f63e… 00007f63e… r--p  000030… 00:00 </span><span style='color: #949494;'>"</span><span>289787… /home/kirill/git/R/r-prof…</span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 8</span><span> 00007f63e… 00007f63e… rw-p  000040… 00:00 </span><span style='color: #949494;'>"</span><span>289787… /home/kirill/git/R/r-prof…</span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 9</span><span> 00007f63e… 00007f63e… r-xp  000000… 00:00 </span><span style='color: #949494;'>"</span><span>287226… /home/kirill/R-dev/glue/l…</span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'>10</span><span> 00007f63e… 00007f63e… ---p  000020… 00:00 </span><span style='color: #949494;'>"</span><span>287226… /home/kirill/R-dev/glue/l…</span></span>
<span class='c'>#&gt; <span style='color: #949494;'># … with 364 more rows</span></span>
</pre>

-----

## Code of Conduct

Please note that the procmaps project is released with a [Contributor Code of Conduct](https://contributor-covenant.org/version/2/0/CODE_OF_CONDUCT.html). By contributing to this project, you agree to abide by its terms.
