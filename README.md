<!-- README.md is generated from README.Rmd. Please edit that file -->

# procmaps

<!-- badges: start -->

[![Lifecycle: experimental](https://img.shields.io/badge/lifecycle-experimental-orange.svg)](https://www.tidyverse.org/lifecycle/#experimental) [![CRAN status](https://www.r-pkg.org/badges/version/procmaps)](https://CRAN.R-project.org/package=procmaps)

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
<span class='c'>#&gt; 55cb535b6000-55cb535be000 r-xp 00000000 fd:01 2883652                    /bin/cat</span>
<span class='c'>#&gt; 55cb537bd000-55cb537be000 r--p 00007000 fd:01 2883652                    /bin/cat</span>
<span class='c'>#&gt; 55cb537be000-55cb537bf000 rw-p 00008000 fd:01 2883652                    /bin/cat</span>
<span class='c'>#&gt; 55cb540ba000-55cb540db000 rw-p 00000000 00:00 0                          [heap]</span>
<span class='c'>#&gt; 7fcc6e386000-7fcc6e7e5000 r--p 00000000 fd:01 29370411                   /usr/lib/locale/locale-archive</span>
<span class='c'>#&gt; 7fcc6e7e5000-7fcc6e9cc000 r-xp 00000000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so</span>
<span class='c'>#&gt; 7fcc6e9cc000-7fcc6ebcc000 ---p 001e7000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so</span>
<span class='c'>#&gt; 7fcc6ebcc000-7fcc6ebd0000 r--p 001e7000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so</span>
<span class='c'>#&gt; 7fcc6ebd0000-7fcc6ebd2000 rw-p 001eb000 fd:01 15731435                   /lib/x86_64-linux-gnu/libc-2.27.so</span>
<span class='c'>#&gt; 7fcc6ebd2000-7fcc6ebd6000 rw-p 00000000 00:00 0 </span>
<span class='c'>#&gt; 7fcc6ebd6000-7fcc6ebfd000 r-xp 00000000 fd:01 15731135                   /lib/x86_64-linux-gnu/ld-2.27.so</span>
<span class='c'>#&gt; 7fcc6edd0000-7fcc6edd2000 rw-p 00000000 00:00 0 </span>
<span class='c'>#&gt; 7fcc6eddb000-7fcc6edfd000 rw-p 00000000 00:00 0 </span>
<span class='c'>#&gt; 7fcc6edfd000-7fcc6edfe000 r--p 00027000 fd:01 15731135                   /lib/x86_64-linux-gnu/ld-2.27.so</span>
<span class='c'>#&gt; 7fcc6edfe000-7fcc6edff000 rw-p 00028000 fd:01 15731135                   /lib/x86_64-linux-gnu/ld-2.27.so</span>
<span class='c'>#&gt; 7fcc6edff000-7fcc6ee00000 rw-p 00000000 00:00 0 </span>
<span class='c'>#&gt; 7ffc8a683000-7ffc8a6a5000 rw-p 00000000 00:00 0                          [stack]</span>
<span class='c'>#&gt; 7ffc8a72e000-7ffc8a731000 r--p 00000000 00:00 0                          [vvar]</span>
<span class='c'>#&gt; 7ffc8a731000-7ffc8a733000 r-xp 00000000 00:00 0                          [vdso]</span>
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
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 1</span><span> 5601b89f… 5601b8a0… r-xp  000000… 00:00 </span><span style='color: #949494;'>"</span><span>293937… /usr/lib/R/bin/exec/R       </span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 2</span><span> 5601b8bf… 5601b8c0… r--p  000000… 00:00 </span><span style='color: #949494;'>"</span><span>293937… /usr/lib/R/bin/exec/R       </span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 3</span><span> 5601b8c0… 5601b8c0… rw-p  000010… 00:00 </span><span style='color: #949494;'>"</span><span>293937… /usr/lib/R/bin/exec/R       </span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 4</span><span> 5601ba8c… 5601bff8… rw-p  000000… 00:00 </span><span style='color: #949494;'>"</span><span>0     … [heap]                      </span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 5</span><span> 7f1201e0… 7f1201e1… r-xp  000000… 00:00 </span><span style='color: #949494;'>"</span><span>289787… /home/kirill/git/R/r-prof/p…</span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 6</span><span> 7f1201e1… 7f120201… ---p  000030… 00:00 </span><span style='color: #949494;'>"</span><span>289787… /home/kirill/git/R/r-prof/p…</span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 7</span><span> 7f120201… 7f120201… r--p  000030… 00:00 </span><span style='color: #949494;'>"</span><span>289787… /home/kirill/git/R/r-prof/p…</span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 8</span><span> 7f120201… 7f120201… rw-p  000040… 00:00 </span><span style='color: #949494;'>"</span><span>289787… /home/kirill/git/R/r-prof/p…</span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'> 9</span><span> 7f120201… 7f120201… r-xp  000000… 00:00 </span><span style='color: #949494;'>"</span><span>287226… /home/kirill/R-dev/glue/lib…</span></span>
<span class='c'>#&gt; <span style='color: #BCBCBC;'>10</span><span> 7f120201… 7f120221… ---p  000020… 00:00 </span><span style='color: #949494;'>"</span><span>287226… /home/kirill/R-dev/glue/lib…</span></span>
<span class='c'>#&gt; <span style='color: #949494;'># … with 364 more rows</span></span>

</pre>
