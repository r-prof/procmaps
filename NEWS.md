<!-- NEWS.md is maintained by https://cynkra.github.io/fledge, do not edit -->

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
