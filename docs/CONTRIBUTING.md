# Contributing Guide

Welcome! We love receiving contributions from the community, so thanks for stopping by! There are many ways to contribute, including submitting bug reports, improving documentation, submitting feature requests, reviewing new submissions, or contributing code that can be incorporated into the project.

This document describes the Embedded Artistry development process. Following these guidelines shows that you respect the time and effort of the developers managing this project. In return, you will be shown respect in addressing your issue, reviewing your changes, and incorporating your contributions.

**Table of Contents:**

1. [Code of Conduct](#code-of-conduct)
2. [Important Resources](#important-resources)
3. [Questions](#questions)
7. [Contributing to the Project](#contributing-to-the-project)
	1. [Continual Need: Documentation](#continual-need-documentation)
	2. [Dependencies](#dependencies)
	3. [Development Process](#development-process)
	4. [Building the Project](#building-the-project)
	5. [Adding New Tests](#adding-new-tests)
9. [Community](#community)


## Code of Conduct

By participating in this project, you agree to abide by the Embedded Artistry [Code of Conduct](CODE_OF_CONDUCT.md). We expect all contributors to follow the [Code of Conduct](CODE_OF_CONDUCT.md) and to treat fellow humans with respect.

## Important Resources

This project is managed on GitHub:

* [GitHub Project Page](https://github.com/embeddedartistry/libc/)
* [GitHub Issue Tracker](https://github.com/embeddedartistry/libc/issues)

Questions can also be submitted [on the Embedded Artistry website](https://embeddedartistry.com/contact) and in the [Embedded Artistry Forum](https://embeddedartistry.com/community/embedded-artistry-oss/).

Useful Documentation:

* [Library Documentation](https://embeddedartistry.github.io/libc/index.html)
* [cppreference (API notes)](http://en.cppreference.com)
* [C Standard Library Header Files](http://en.cppreference.com/w/c/header)

Embedded Artistry blog posts related to this project:

* [Bringup Blog Category](https://embeddedartistry.com/blog?category=Bringup) - contains multiple articles about this project
* [memset, memcpy, memcmp, and memmove](https://embeddedartistry.com/blog/2017/3/7/implementing-memset-memcpy-and-memmove)
* [Libc bringup: String Functions](https://embeddedartistry.com/blog/2017/3/9/string-functions)
* [libc: Defining Standard Types for Your Platform](https://embeddedartistry.com/blog/2017/4/11/libc-defining-standard-types-for-your-platform)
* [libc: Useful Headers (memory, stdbool, endian, limits)](https://embeddedartistry.com/blog/2017/4/11/libc-some-important-headers)
* [libc: stdlib, pt. 1](https://embeddedartistry.com/blog/2017/4/10/libc-stdlib)
* [libc: stdlib, pt. 2](https://embeddedartistry.com/blog/2017/10/18/implementing-libc-stdlib-pt-2)

## Questions

Please submit your questions in the following ways:

* Filing a new [GitHub Issue](https://github.com/embeddedartistry/libc/issues)
* [Submitting a question on the Embedded Artistry website](https://embeddedartistry.com/contact)
* [Submitting a question on the Embedded Artistry forum](https://embeddedartistry.com/community/embedded-artistry-oss/)
* Asking a question [on Twitter: (mbeddedartistry)](https://twitter.com/mbeddedartistry/).

## New to Open Source?

If you've never worked with an open source project before, please check out our [Open Source Contribution Guide](https://embeddedartistry.com/fieldatlas/open-source-contribution-guide/), which contains information on:

* Resources for people new to open-source development
* How to find something to work on
* How to report issues
* Branching and PR guidelines for our projects
* Style guidelines for our projects

## Contributing to the Project

If you're interested in contributing = to this project, read on! Don't know where to start? Take a look at the [Open Source Contribution Guide](https://embeddedartistry.com/fieldatlas/open-source-contribution-guide/) section for information on finding beginner-friendly issues on our projects.

Please review the following guides to learn about our development process:

* [Open Source Contribution Guide](https://embeddedartistry.com/fieldatlas/open-source-contribution-guide/)
	* Resources for people new to open-source development
	- How to find something to work on
	- How to report issues
	- Branching and PR guidelines for our projects
	- Style guidelines for our projects
* [Embedded Artistry's GitHub Process](https://embeddedartistry.com/fieldatlas/embedded-artistrys-github-process/), which discusses how we handle PRs and integrate changes
* [Source Control Commit Guidelines](https://embeddedartistry.com/fieldatlas/source-control-commit-guidelines/), which describes our guidelines for commit messages

**If you have any questions about this process, please [ask us for help!](#questions)**

### Continual Need: Documentation

Should you have a suggestion for the documentation, you can open an issue and outline the problem or improvement you have - however, creating the doc fix yourself is much better! By creating a new issue (or commenting on a related existing one), you let others know what you're working on. If you're making a small change (typo, phrasing) don't worry about filing an issue first - just open a Pull Request.

I currently need the most help with improving the libc in-source Doxygen documentation and commenting. If you would like to help, please select a header in the `include/` folder and add Doxygen style comments to functions with no documentation.

For large fixes, please build and test the documentation before submitting the PR to be sure you haven't accidentally introduced any layout or formatting issues. To generate the Doxygen documentation, run:

```
make docs
```

You can find the resulting output in `buildresults/docs` folder.

### Dependencies

The dependencies for [Embedded Artistry's standardized Meson build system](https://embeddedartistry.com/fieldatlas/embedded-artistrys-standardized-meson-build-system/) are described [on our website](https://embeddedartistry.com/fieldatlas/embedded-artistrys-standardized-meson-build-system/).

In addition to those dependencies, you will need the following for this repository:

* [`git-lfs`](https://git-lfs.github.com) is used to store binary files

### Development Process

`master` contains the latest code for this project, and new versions are tagged nightly.

Please branch from `master` for any new changes. Once you are ready to merge changes, open a pull request. The build server will test and analyze the branch to ensure it can be safely merged.

### Building the Project

This project uses [Embedded Artistry's standardized Meson build system](https://embeddedartistry.com/fieldatlas/embedded-artistrys-standardized-meson-build-system/). Complete instructions can be found [on our website](https://embeddedartistry.com/fieldatlas/embedded-artistrys-standardized-meson-build-system/).

### Adding New Tests

If you add code you need to add tests! We’ve learned the hard way that code without tests is undependable. If your pull request reduces our test coverage because it lacks tests then it will be rejected.

This project uses CMocka as the testing framework.

Please follow these guidelines:

* New tests should be added to the [`test/`](../test/) directory tree
	* If you are adding a new function to an existing module, please add it in that module's tree
		* e.g. `string/`, `stdlib/`, `ctype/`
	* If you are adding a new module or a function in a new module, please create that directory and add the file there.
* Each function should have its own tests in its own C file.
* Each module should have a C file which coordinates the tests.
	* e.g. [`string/string_tests.c`](../test/string/string_tests.c)
* When adding a new test, add the following to the relevant test coordination file:
	* An `extern` function declaration: `extern int memcpy_tests(void);`
	* A call to this test function: `overall_result |= memcpy_tests();`
* When adding a new module:
	* Please copy the test coordinator style from an existing module
	* Add an `extern` function declaration in [main.c](../test/main.c): `extern int ctype_tests(void);`
	* Add a call to the test coordinator in [main.c](../test/main.c): `overall_result |= ctype_tests();`

## Community

Anyone interested in active conversation regarding this project should [join the Embedded Artistry community]https://embeddedartistry.com/community/embedded-artistry-oss/).

You can also [reach out on Twitter: mbeddedartistry](https://twitter.com/mbeddedartistry/).
