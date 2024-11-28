<!-- NEWS.md is maintained by https://fledge.cynkra.com, contributors should not edit this file -->

# procmaps 0.0.5.9015 (2024-11-28)

## Continuous integration

- Ignore errors when removing pkg-config on macOS (#42).


# procmaps 0.0.5.9014 (2024-11-27)

## Continuous integration

- Explicit permissions (#41).


# procmaps 0.0.5.9013 (2024-11-26)

## Continuous integration

- Use styler from main branch (#40).


# procmaps 0.0.5.9012 (2024-11-25)

## Continuous integration

- Need to install R on Ubuntu 24.04 (#39).

- Use Ubuntu 24.04 and styler PR (#37).


# procmaps 0.0.5.9011 (2024-11-22)

## Continuous integration

  - Correctly detect branch protection (#36).


# procmaps 0.0.5.9010 (2024-11-18)

## Continuous integration

  - Use stable pak (#35).


# procmaps 0.0.5.9009 (2024-11-11)

## Continuous integration

  - Trigger run (#34).
    
      - ci: Trigger run
    
      - ci: Latest changes


# procmaps 0.0.5.9008 (2024-10-28)

## Continuous integration

  - Use pkgdown branch (#33).
    
      - ci: Use pkgdown branch
    
      - ci: Updates from duckdb
    
      - ci: Trigger run


# procmaps 0.0.5.9007 (2024-09-15)

## Continuous integration

  - Install via R CMD INSTALL ., not pak (#32).
    
      - ci: Install via R CMD INSTALL ., not pak
    
      - ci: Bump version of upload-artifact action


# procmaps 0.0.5.9006 (2024-08-31)

## Chore

  - Auto-update from GitHub Actions.
    
    Run: https://github.com/r-prof/procmaps/actions/runs/10425482568

  - Auto-update from GitHub Actions.
    
    Run: https://github.com/r-prof/procmaps/actions/runs/10200112202

  - Auto-update from GitHub Actions.
    
    Run: https://github.com/r-prof/procmaps/actions/runs/9728441193

  - Auto-update from GitHub Actions.
    
    Run: https://github.com/r-prof/procmaps/actions/runs/9691619452

## Continuous integration

  - Install local package for pkgdown builds.

  - Improve support for protected branches with fledge.

  - Improve support for protected branches, without fledge.

  - Sync with latest developments.

  - Use v2 instead of master.

  - Inline action.

  - Use dev roxygen2 and decor.

  - Fix on Windows, tweak lock workflow.

  - Avoid checking bashisms on Windows.

  - Better commit message.

  - Bump versions, better default, consume custom matrix.

  - Recent updates.


# procmaps 0.0.5.9005 (2024-04-03)

- Internal changes only.


# procmaps 0.0.5.9004 (2023-10-09)

- Internal changes only.


# procmaps 0.0.5.9003 (2023-03-24)

- Internal changes only.


# procmaps 0.0.5.9002 (2023-02-17)

- Internal changes only.


# procmaps 0.0.5.9001 (2023-01-22)

## Chore

- Fix Windows checks (#30).

## Uncategorized

- Merge branch 'docs'.


- Merged cran-0.0.5 into main.



# procmaps 0.0.5.9000 (2023-01-19)

## Chore

- Fix compiler warnings (@Antonov548, #29).

- Change maintainer e-mail address.


# procmaps 0.0.5 (2023-01-19)

## Chore

- Fix compiler warnings (@Antonov548, #29).

- Change maintainer e-mail address.


# procmaps 0.0.4 (2021-10-01)

- Fix failing test on macOS (#27).


# procmaps 0.0.3 (2020-09-21)

- Fix compilation on Solaris (#25).


# procmaps 0.0.2 (2020-09-20)

## Portability

- Fix test failures on Fedora (#21).
- `SystemRequirements` are no longer specified in `DESCRIPTION` (#22).
- Remove configuration and unnecessary code for better portability (#20).
- Hard-coding dylib extension because on the Mac it's `libR.dylib` but `<package>.so`.
- Fix tests on Solaris which seems to have statically linked `libR` (#14).

## Features

- Use `stringsAsFactors = FALSE` (#19).
- New `path_is_libr()` (#16).
- Addresses are returned as 16-digit hex numbers (#15).
- `procmap_get()` gets ellipsis argument for extensibility (#13).


# procmaps 0.0.1 (2020-09-03)

Initial release.

- `procmap_get()` returns a data frame with the address space map of the current process.
