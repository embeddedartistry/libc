# Embedded Artistry libc

Embedded Artistry's `libc` is a stripped-down C standard library implementation targeted for microcontroller-based embedded systems.

In order to conserve precious memory resources, this library does not supply the complete C standard library implementation. Instead, a subset of functions which are useful on bare-metal embedded systems has been selected. If you have a bare metal or RTOS-based embedded system, this library is for you!

Unlike many other C libraries that I've come across, this library implements unit tests and has addressed long-standing flaws in open-source implementations of the C standard library functions. We're continually adding tests and making additional improvements over the baseline implementations.

`malloc` and `free` are not included in this library. If you need dynamic memory allocation support, you will need to couple this library with something like [Embedded Artistry's `libmemory`][1], which contains implementations of `malloc` and `free`.

If you are interested in contributing to this project, please read the [`CONTRIBUTING` guide][10].

## Table of Contents

1. [About the Project](#about-the-project)
2. [Project Status](#project-status)
3. [Getting Started](#getting-started)
	1. [Requirements](#requirements)
		1. [Meson Build System](#meson-build-system)
	2. [Getting the Source](#getting-the-source)
	3. [Building](#building)
		1. [Cross-compiling](#cross-compiling)
		2. [Disabling Position Independent Code](#disabling-position-independent-code)
	4. [Installation](#installation)
	5. [Usage](#usage)
		1. [Aligned Malloc](#aligned-malloc)
	6. [Testing](#testing)
4. [Configuration Options](#configuration-options)
4. [Formatting](#formatting)
5. [Documentation](#documentation)
6. [Need Help?](#need-help)
7. [Contributing](#contributing)
8. [Futher Reading](#further-reading)
9. [Authors](#authors)
10. [License](#license)
11. [Acknowledgements](#acknowledgements)

## About the Project

Embedded Artistry's `libc` is intended to provide a portable set of useful C standard library functions that allows quick bring-up of new bare-metal and RTOS-based embedded systems.

Additionally, we want to provide a high-quality `libc` implementation by ensuring that each function has unit test coverage and addresses flaws exposed by the static analyzer. Many C library function implementations remain untested and contain errors. We are fighting back against poor implementations.

In order to conserve memory, this library does not supply the complete C standard library functionality. Instead, a subset of functions which are useful on bare-metal embedded systems has been selected. This selection has primarily been driven by my own experience in microcontroller-focused development. If you need additional features, please file an issue and make a feature request.

The functional implementations in this library have been selected for portability and quick bring-up of new systems. There may be more efficient implementations for these functions, but often they are architecture specific implementations. If you have suggestions for improving performance, we are always happy to hear them.

`malloc` and `free` are not included in this library. Because memory allocation schemes vary greatly with embedded systems (some not even allowing dynamic memory), you will need to supply your own implementations based on your system's needs. You can couple this library with the [Embedded Artistry `libmemory`][1], which contains implementations of `malloc` and `free`.

## Project Status

This library provides a complete-enough implementation to compile and link clang's `libc++` and `libc++abi` (see [Embedded Artistry's libcpp project](https://github.com/embeddedartistry/libcpp)). In order to achieve this, some functions are only defined in the headers but do not have an implementation. Unsupported-but-defined functions can be removed using a build option (`hide-unimplemented-libc-apis`).

The following portions of the C library have been implemented:

* `assert`
* Basic C runtime support (`crt.c`, `exit`, `atexit`, etc.)
* ctype
* math (via [openlibm](https://github.com/JuliaMath/openlibm))
* string functions
* stdlib
	* `atoX`
	* `abs`, `labs`, `llabs`
	* `bsearch`
	* `calloc`
	* `div`, `ldiv`, `lldiv`
	* `heapsort`, `heapsort_r`
	* `imaxabs`, `imaxdiv`
	* `qsort`, `qsort_r`
	* `rand` family
	* `realloc`
	* `strtoX` functions (many via [`gdtoa`](https://github.com/embeddedartistry/gdtoa))
* Basic stdio
	- `printf` family (most via [`mpaland/printf`](https://github.com/mpaland/printf))
	- `putchar`
	- `puts`
* `time` types and `asctime()`
* `wchar` type definitions and `wctype` functions

The following architectures are currently supported:

* x86
* x86_64
* ARM
* ARM64

The following unit tests need to be added:

* `bsearch`
* `imaxdiv`
* `div`, `ldiv`
* `realloc`
* `rand` family
* `strnstr`
* `memmove`

These are not implemented by may be added in the future:

* `wchar` functions
* `errno` support (enabled as a compile-time switch)
* `getopt` support
* `time` support
* `FILE` and additional stdio functions

We are currently not planning full support for:

* `locale`

## Getting Started

### Requirements

* [CMocka][3] must be installed on your system to compile and run unit tests
* [Doxygen][0] must be installed to generate documentation
* [Meson](#meson-build-system) is the build system
* [`git-lfs`][7] is used to store binary files in this repository
* `make` is needed if you want to use the Makefile shims
* You'll need some kind of compiler for your target system.
	- This repository has been tested with:
		- gcc
		- arm-none-eabi-gcc
		- Apple clang
		- Mainline clang


Contributors will also need:

* [`adr-tools`](https://github.com/npryce/adr-tools) for documenting major project decisions
* [`clang-format`][2] for code formatting

#### git-lfs

This project stores some files using [`git-lfs`](https://git-lfs.github.com).

To install `git-lfs` on Linux:

```
sudo apt install git-lfs
```

To install `git-lfs` on OS X:

```
brew install git-lfs
```

Additional installation instructions can be found on the [`git-lfs` website](https://git-lfs.github.com).

#### Meson Build System

The [Meson][meson] build system depends on `python3` and `ninja-build`.

To install on Linux:

```
sudo apt-get install python3 python3-pip ninja-build
```

To install on OSX:

```
brew install python3 ninja
```

Meson can be installed through `pip3`:

```
pip3 install meson
```

If you want to install Meson globally on Linux, use:

```
sudo -H pip3 install meson
```

#### `adr-tools`

This repository uses [Architecture Decision Records](https://embeddedartistry.com/blog/2018/4/5/documenting-architectural-decisions-within-our-repositories). Please install [`adr-tools`](https://github.com/npryce/adr-tools) to contribute to architecture decisions.

If you are using OSX, you can install `adr-tools` through Homebrew:

```
brew install adr-tools
```

If you are using Windows or Linux, please install `adr-tools` via [GitHub](https://github.com/npryce/adr-tools).

### Getting the Source

This project uses [`git-lfs`](https://git-lfs.github.com), so please install it before cloning. If you cloned prior to installing `git-lfs`, simply run `git lfs pull` after installation.

This project is [hosted on GitHub][8]. You can clone the project directly using this command:

```
git clone --recursive git@github.com:embeddedartistry/libc.git
```

If you don't clone recursively, be sure to run the following command in the repository or your build will fail:

```
git submodule update --init
```

### Building

The library can be built by issuing the following command:

```
make
```

This will build all targets for your current architecture.

You can clean builds using:

```
make clean
```

You can eliminate the generated `buildresults` folder using:

```
make purify
```

You can also use the `meson` method for compiling.

Create a build output folder:

```
meson buildresults
```

Then change into that folder and build targets by running:

```
ninja
```

At this point, `make` would still work.

#### Cross-compiling

Cross-compilation is handled using `meson` cross files. Example files are included in the [`build/cross`](build/cross/) folder. You can write your own cross files for your specific platform (or open an issue and we can help you).

Cross-compilation must be configured using the meson command when creating the build output folder. For example:

```
meson buildresults --cross-file build/cross/gcc/arm/gcc_arm_cortex-m4.txt
```

Following that, you can run `make` (at the project root) or `ninja` (within the build output directory) to build the project.

Tests will not be cross-compiled. They will be built for the native platform.

#### Disabling Position Independent Code

Position Independent Code (PIC) is enabled by default, but can be disabled during the Meson configuration stage by setting the built-in option `b_staticpic` to `false`:

```
meson buildresults -Db_staticpic=false
```

### Installation

If you don't use `meson` for your project, the best method to use this project is to build it separately and copy the headers and library contents into your source tree.

* Copy the `include/` directory contents into your source tree.
* Library artifacts are stored in the `buildresults/src` folder
* Copy the desired library to your project and add the library to your link step.

Example linker flags:

```
-Lpath/to/libc.a -lc 
```

If you're using `meson`, you can use `libc` as a subproject. Place it into your subproject directory of choice and add a `subproject` statement:

```
libc = subproject('libc')
```

You will need to promote the subproject dependencies to your project:

```
libc_dep = libc.get_variable('libc_dep')
libc_native_dep = libc.get_variable('libc_native_dep')
libc_hosted_dep = libc.get_variable('libc_hosted_dep')
libc_printf_dep = libc.get_variable('libc_printf_dep')
libc_header_include = libc.get_variable('libc_header_include')
libc_native_header_include = libc.get_variable('libc_native_header_include')
```

You can use the dependency for your target library configuration in your `executable` declarations(s) or other dependencies. For example:

```
fwdemo_sim_platform_dep = declare_dependency(
	include_directories: fwdemo_sim_platform_inc,
	dependencies: [
		fwdemo_simulator_hw_platform_dep,
		posix_os_dep,
		libmemory_native_dep,
		libc_native_dep, # <----- libc added here
		libcxxabi_native_dep,
		libcxx_full_native_dep,
		logging_subsystem_dep
	],
	sources: files('platform.cpp'),
)
```

### Testing

The tests for this library are written with [CMocka][3]. You can run the tests by issuing the following command:

```
make test
```

By default, test results are generated for use by the CI server and are formatted in JUnit XML. The test results XML files can be found in `buildresults/test/`.

## Configuration Options

The following meson project options can be set for this library when creating the build results directory with `meson`, or by using `meson configure`:

* `enable-werror`: Cause the build to fail if warnings are present
* `enable-pedantic-error`: Turn on `pedantic` warnings and errors
* `hide-unimplemented-libc-apis`: Hides the header definitions for functions which are not actually implemented

Options can be specified using `-D` and the option name:

```
meson buildresults -Denable-werror=true
```

The same style works with `meson configure`:

```
cd buildresults
meson configure -Denable-werror=true
```

## Formatting

This repository enforces formatting using [`clang-format`][2].

You can auto-format your code to match the style guidelines by issuing the following command:

```
make format
```

Formatting is enforced by the Jenkins build server which runs continuous integration for this project. Your pull request will not be accepted if the formatting check fails.

## Documentation

[Documentation for the latest release can always be found here][9].

Documentation can be built locally by running the following command:

```
make docs
```

Documentation can be found in `buildresults/doc`, and the root page is `index.html`.

## Need help?

If you need further assistance or have any questions, please [file a GitHub Issue][6] or send us an email using the [Embedded Artistry Contact Form][5].

You can also [reach out on Twitter: mbeddedartistry](https://twitter.com/mbeddedartistry/).

## Contributing

If you are interested in contributing to this project, please read our [contributing guidelines](docs/CONTRIBUTING.md).

## Further Reading

* [`libc` Documentation][9]
* [`CONTRIBUTING` Guide][10]

## Authors

* **[Phillip Johnston](https://github.com/phillipjohnston)** - original library author - [Embedded Artistry](https://github.com/embeddedartistry)

## License

Copyright © 2017 Embedded Artistry LLC

This project is licensed under the MIT License - see [LICENSE](LICENSE) file for details.

For other open-source licenses, please see the [Software Inventory](docs/software_inventory.xlsx).

## Acknowledgments

I'd like to thank the following individuals for their direct contributions on this project:

* [\@seekaddo](https://github.com/seekaddo) (Documentation)

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
[meson]: http://mesonbuild.com/index.html
[5]: http://embeddedartistry.com/contact
[6]: https://github.com/embeddedartistry/libc/issues/new
[7]: https://git-lfs.github.com
[8]: https://github.com/embeddedartistry/libc
[9]: https://embeddedartistry.github.io/libc/index.html
[10]: docs/CONTRIBUTING.md
