# OpenLibm

[![Travis](https://travis-ci.org/JuliaMath/openlibm.svg?branch=master)](https://travis-ci.org/JuliaMath/openlibm)
[![AppVeyor](https://ci.appveyor.com/api/projects/status/sia04r4089rr19uc/branch/master?svg=true)](https://ci.appveyor.com/project/ararslan/openlibm-19152/branch/master)

[OpenLibm](https://openlibm.org/) is an effort to have a high quality, portable, standalone
C mathematical library ([`libm`](http://en.wikipedia.org/wiki/libm)).
It can be used standalone in applications and programming language
implementations.

The project was born out of a need to have a good `libm` for the
[Julia programming langage](http://www.julialang.org) that worked
consistently across compilers and operating systems, and in 32-bit and
64-bit environments.

## Platform support

OpenLibm builds on Linux, macOS, Windows, FreeBSD, OpenBSD, NetBSD, and
DragonFly BSD.  It builds with both GCC and clang. Although largely
tested and widely used on the x86 and x86-64 architectures, OpenLibm
also supports arm, aarch64, ppc64le, mips, wasm32, and s390(x).

## Build instructions

1. Use GNU Make to build OpenLibm. This is `make` on most systems, but `gmake` on BSDs.
2. Use `make USEGCC=1` to build with GCC. This is the default on
   Linux and Windows.
3. Use `make USECLANG=1` to build with clang. This is the default on OS X, FreeBSD,
   and OpenBSD.
4. Use `make ARCH=wasm32` to build the wasm32 library with clang. Requires clang-8.
5. Architectures are auto-detected. Use `make ARCH=i386` to force a
   build for i386. Other supported architectures are i486, i586, and
   i686. GCC 4.8 is the minimum requirement for correct codegen on
   older 32-bit architectures.

## Acknowledgements

PowerPC support for openlibm was graciously sponsored by IBM.
