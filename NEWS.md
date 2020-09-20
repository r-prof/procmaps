# procmaps 0.0.2.9000 (2020-09-20)

- Internal changes only.


# procmaps 0.0.2 (2020-09-20)

- Same as previous version.


# procmaps 0.0.1.9004 (2020-09-20)

- Fix test failures on Fedora (#21).
- `SystemRequirements` are no longer specified in `DESCRIPTION` (#22).
- Remove configuration and unnecessary code for better portability (#20).


# procmaps 0.0.1.9003 (2020-09-09)

- Use `stringsAsFactors = FALSE` (#19).


# procmaps 0.0.1.9002 (2020-09-07)

- Hard-coding dylib extension because on the Mac it's `libR.dylib` but `<package>.so`.
- Test upstream winch package (#17).


# procmaps 0.0.1.9001 (2020-09-04)

- New `path_is_libr()` (#16).
- Addresses are returned as 16-digit hex numbers (#15).
- Fix tests on Solaris which seems to have statically linked `libR` (#14).
- `procmap_get()` gets ellipsis argument for extensibility (#13).


# procmaps 0.0.1.9000 (2020-09-03)

- Internal changes only.


# procmaps 0.0.1 (2020-09-03)

Initial release.

- `procmap_get()` returns a data frame with the address space map of the current process.
