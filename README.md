<!-- README.md is generated from README.Rmd. Please edit that file -->

# procmaps

<!-- badges: start -->

[![Lifecycle: experimental](https://img.shields.io/badge/lifecycle-experimental-orange.svg)](https://lifecycle.r-lib.org/articles/stages.html) [![R build status](https://github.com/r-prof/procmaps/workflows/rcc/badge.svg)](https://github.com/r-prof/procmaps/actions) [![Codecov test coverage](https://codecov.io/gh/r-prof/procmaps/branch/main/graph/badge.svg)](https://app.codecov.io/gh/r-prof/procmaps?branch=main) [![CRAN status](https://www.r-pkg.org/badges/version/procmaps)](https://CRAN.R-project.org/package=procmaps)

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
<span class='c'>#&gt; 56390592e000-563905936000 r-xp 00000000 fd:01 2883652                    /bin/cat</span>
<span class='c'>#&gt; 563905b35000-563905b36000 r--p 00007000 fd:01 2883652                    /bin/cat</span>
<span class='c'>#&gt; 563905b36000-563905b37000 rw-p 00008000 fd:01 2883652                    /bin/cat</span>
<span class='c'>#&gt; 563906bb9000-563906bda000 rw-p 00000000 00:00 0                          [heap]</span>
<span class='c'>#&gt; 7fb42c468000-7fb42c8c7000 r--p 00000000 fd:01 29370411                   /usr/lib/locale/locale-archive</span>
<span class='c'>#&gt; 7fb42c8c7000-7fb42caae000 r-xp 00000000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so</span>
<span class='c'>#&gt; 7fb42caae000-7fb42ccae000 ---p 001e7000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so</span>
<span class='c'>#&gt; 7fb42ccae000-7fb42ccb2000 r--p 001e7000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so</span>
<span class='c'>#&gt; 7fb42ccb2000-7fb42ccb4000 rw-p 001eb000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so</span>
<span class='c'>#&gt; 7fb42ccb4000-7fb42ccb8000 rw-p 00000000 00:00 0 </span>
<span class='c'>#&gt; 7fb42ccb8000-7fb42ccdf000 r-xp 00000000 fd:01 15731135                   /lib/x86_64-linux-gnu/ld-2.27.so</span>
<span class='c'>#&gt; 7fb42ceb2000-7fb42ceb4000 rw-p 00000000 00:00 0 </span>
<span class='c'>#&gt; 7fb42cebd000-7fb42cedf000 rw-p 00000000 00:00 0 </span>
<span class='c'>#&gt; 7fb42cedf000-7fb42cee0000 r--p 00027000 fd:01 15731135                   /lib/x86_64-linux-gnu/ld-2.27.so</span>
<span class='c'>#&gt; 7fb42cee0000-7fb42cee1000 rw-p 00028000 fd:01 15731135                   /lib/x86_64-linux-gnu/ld-2.27.so</span>
<span class='c'>#&gt; 7fb42cee1000-7fb42cee2000 rw-p 00000000 00:00 0 </span>
<span class='c'>#&gt; 7ffed6a9a000-7ffed6abc000 rw-p 00000000 00:00 0                          [stack]</span>
<span class='c'>#&gt; 7ffed6b08000-7ffed6b0b000 r--p 00000000 00:00 0                          [vvar]</span>
<span class='c'>#&gt; 7ffed6b0b000-7ffed6b0d000 r-xp 00000000 00:00 0                          [vdso]</span>
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
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 1</span><span> 000055cc2db… 000055cc2d… r-xp  000000… 29393… /usr/lib/R/bin/exec/R          </span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 2</span><span> 000055cc2dd… 000055cc2d… r--p  000000… 29393… /usr/lib/R/bin/exec/R          </span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 3</span><span> 000055cc2dd… 000055cc2d… rw-p  000010… 29393… /usr/lib/R/bin/exec/R          </span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 4</span><span> 000055cc2e4… 000055cc33… rw-p  000000… 0      [heap]                         </span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 5</span><span> 00007f9bac9… 00007f9bac… r-xp  000000… 28991… /home/kirill/git/R/r-prof/proc…</span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 6</span><span> 00007f9bac9… 00007f9bac… ---p  000040… 28991… /home/kirill/git/R/r-prof/proc…</span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 7</span><span> 00007f9bacb… 00007f9bac… r--p  000030… 28991… /home/kirill/git/R/r-prof/proc…</span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 8</span><span> 00007f9bacb… 00007f9bac… rw-p  000040… 28991… /home/kirill/git/R/r-prof/proc…</span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 9</span><span> 00007f9bacb… 00007f9bac… r-xp  000000… 28722… /home/kirill/R-dev/glue/libs/g…</span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'>10</span><span> 00007f9bacb… 00007f9bac… ---p  000020… 28722… /home/kirill/R-dev/glue/libs/g…</span></span>
<span class='c'>#&gt; <span style='color: #949494;'># … with 368 more rows</span></span>
</pre>

-----

## Code of Conduct

Please note that the procmaps project is released with a [Contributor Code of Conduct](https://contributor-covenant.org/version/2/0/CODE_OF_CONDUCT.html). By contributing to this project, you agree to abide by its terms.
