# libc
Embedded Artistry's `libc` is a C standard library implementation targeted for embedded systems.

In order to conserve precious memory resources, this library does not supply the complete C standard library functionality. Instead, a subset of functions which are useful on bare-metal embedded systems has been selected. If you have a bare metal system and want to use the standard set of C functions, this library is for you!

Unlike many other C libraries that I've come across, this library implements unit tests and has addressed flaws in various open-source implementations of the C standard library functions.

Note that `malloc` and `free` are not included in this library. If you need dynamic memory allocation support, you can couple this library with the [Embedded Artistry `libmemory`][1], which contains implementations of `malloc` and `free`.

If you are interested in contributing to this project, please read the [`CONTRIBUTING` guide][10].

## Table of Contents

1. [About the Project](#about-the-project)
2. [Project Status](#project-status)
3. [Getting Started](#getting-started)
	1. [Requirements](#requirements)
	2. [Building](#building)
	3. [Installation](#installation)
	4. [Usage](#usage)
4. [Release Process](#release-process)
	1. [Versioning](#versioning)

# About the Project

Embedded Artistry's `libc` is intended to provide a portable set of useful C standard library functions that allows quick bringup of new bare-metal embedded systems.

Additionally, we want to ensure a high-quality `libc` implementation by ensuring that each function has unit test coverage. Many C library function implementations are untested and contain errors. We are fighting poor implementations by adding test coverage.

In order to conserve precious memory resources, this library does not supply the complete C standard library functionality. Instead, a subset of functions which are useful on bare-metal embedded systems has been selected. This selection has primarily been driven by my own experience in bare-metal development. If you need additional features, please open a feature request!

The functional implementations in this library have been selected for portability and quick bringup of new systems. There may be more efficient implementations for these functions, but often they are architecture specific.

Note that `malloc` and `free` are not included in this library. Because memory allocation schemes vary greatly with embedded systems (some not even allowing dynamic memory), you will need to supply your own implementations based on your system's needs. You can also couple this library with the [Embedded Artistry `libmemory`][1], which contains implementations of `malloc` and `free`.

# Project Status

This library does not supply `errno` support at this time.

The following portions of the C library have been implemented:

* ctype
* string
* stdlib
	* atoX
	* abs, labs, llabs
	* bsearch
	* calloc
	* div, ldiv, lldiv
	* heapsort, heapsort_r
	* imaxabs, imaxdiv
	* qsort, qsort_r
	* rand family
	* realloc
	* strtoX functions (many via `gdtoa`)

The following architectures are currently supported:

* x86
* x86_64

Up next:

* `assert` (`assert.h`)
* Hooks for `exit` and `abort` (`stdlib`)
* ARM architecture support
* Cross-compilation for ARM
* math.h and some definitions (INFINITY, NaN)
* `stdio`

The following unit tests need to be added:

* `bsearch`
* `imaxdiv`
* `div`, `ldiv`
* `realloc`
* `rand` family
* `strnstr`
* `memmove`

Maybe in the future:

* `wchar` support
* `errno` support (enabled as a compile-time switch)
* `getopt` support

# Getting Started

## Requirements

* [Doxygen][0] must be installed to generate documentation
* [Premake][4] is used as the buildsystem
	* Binaries are included for Windows, Linux, and OSX
	* If yours is not natively supported please download a binary from the website or file a GitHub issue so I can help
* [`git-lfs`][7] is used to store binary files
* `make` and `gcc` should be installed in order to compile the files

## Getting the Source

This project uses `git-lfs`, so please install it before cloning. If you cloned prior to installing `git-lfs`, simply run `git lfs pull` after installation.

This project is [hosted on GitHub][8]. You can clone the project directly using this command:

```
git clone --recursive git@github.com:embeddedartistry/libc.git
```

## Building

The library can be built by issuing the following command:

```
make
```

This will build all targets for your current architecture.

You can clean builds using:

```
make clean
```

And you can completely eliminate the generated `Makefile`s and buildresults using:

```
make purify
```

### Cross-compiling

Output is currently limited to `x86_64`, but cross-compiling for ARM will be implemented in the near future.

## Installation

Currently the best method to use this project is to build it separately and copy the contents into your tree. I will improve this method to allow easier usage as a submodule.

Copy the `include/` directory contents into your source tree.

Build artifacts are stored in the `buildresults` folder. There is a sub-folder for the target architecture (e.g. `x86_64`). Inside of this architecture folder you will find a `libc` folder which contains the compiled static library: `libc.a`

Copy the desired library to your project and add the library to your link step.

Example linker flags:

```
-lc -Lpath/to/libc.a
```

## Testing

The tests for this library are written with [CMocka][3]. You can run the tests by issuing the following command:

```
make test
```

By default, test results are generated for use by the CI server and are formatted in JUnit XML. The test results XML files can be found in `buildresults/testresults/`.

If you would prefer to see the test result summary printed to `stdout` instead, simply use the following command:

```
CMOCKA_MESSAGE_OUTPUT=stdout make test
```

# Formatting

This repository enforces formatting using [`clang-format`][2].

You can auto-format your code to match the style guidelines by issuing the following command:

```
make format
```

Formatting is enforced by the Jenkins build server which runs continuous integration for this project. Your pull request will not be accepted if the formatting check fails.

# Documentation

[Documentation for the latest release can always be found here][9].

Documentation can be built locally by running the following command:

```
make doc
```

Documentation can be found in `buildresults/doc`, and the root page is `index.html`.

# Need help?

If you need further assistance or have any questions, please [file a GitHub Issue][6] or send us an email using the [Embedded Artistry Contact Form][5].

# Contributing

If you are intersted in contributing to this project, please read our [contributing guidelines](docs/CONTRIBUTING.md).

# Further Reading

* [`libc` Documentation][9]
* [`CONTRIBUTING` Guide][10]

# Authors

* **[Phillip Johnston](https://github.com/phillipjohnston)** - original library author - [Embedded Artistry](https://github.com/embeddedartistry)

# License

Copyright (c) 2017 Embedded Artistry LLC

This project is licensed under the MIT License - see [LICENSE](LICENSE) file for details.

musl libc is licensed under the MIT License - see [LICENSE](LICENSE) file for details.

# Acknowledgments

I'd like to thank the following individuals for their direct contributions on this project:

* @seekaddo (Documentation)

Many of the open-source function implementations used in this library have been pulled from two primary sources:

* [Apple Open Source libc](https://opensource.apple.com/source/Libc/)
	* abs, atof, bsearch, div family, heapsort/qsort family, abs family, imax family, strtol/ll/ull
	* fls, flsl, flsll
	* strstr, strtok. strnstr, strnlen, strndup, strncpy, strncat, strlen, strdup, strcpy, strcat
	* memmem, memcpy
* [musl libc](https://www.musl-libc.org)
	* All ctype member functions (locale support removed)
	* strrchr, strchrnul, strchr
	* memset, memrchr

I have also used and improved the open-source `gdtoa` library.

The initial groundwork of testing was implemented by referencing the [libc-test](http://nsz.repo.hu/git/?p=libc-test) project.

**[Back to top](#table-of-contents)**

[0]: http://www.stack.nl/~dimitri/doxygen/
[1]: https://github.com/embeddedartistry/libmemory
[2]: https://clang.llvm.org/docs/ClangFormat.html
[3]: https://cmocka.org
[4]: https://github.com/premake/premake-core/wiki
[5]: http://embeddedartistry.com/contact
[6]: https://github.com/embeddedartistry/libc/issues/new
[7]: https://git-lfs.github.com
[8]: https://github.com/embeddedartistry/libc
[9]: https://embeddedartistry.github.io/libc/index.html
[10]: docs/CONTRIBUTING.md
