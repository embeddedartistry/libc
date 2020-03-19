# Contributing Guide

Welcome! We love receiving contributions from the community, so thanks for stopping by! There are many ways to contribute, including submitting bug reports, improving documentation, submitting feature requests, reviewing new submissions, or contributing code that can be incorporated into the project.

This document describes the Embedded Artistry development process. Following these guidelines shows that you respect the time and effort of the developers managing this project. In return, you will be shown respect in addressing your issue, reviewing your changes, and incorporating your contributions.

**Table of Contents:**

1. [Code of Conduct](#code-of-conduct)
2. [Important Resources](#important-resources)
3. [Questions](#questions)
4. [Feature Requests](#feature-requests)
5. [Improving Documentation](#improving-documentation)
6. [Reporting Bugs](#reporting-bugs)
7. [Contributing Code](#contributing-code)
	1. [Getting Started](#getting-started)
	2. [Finding an Issue!](#finding-an-issue)
	3. [Development Process](#development-process)
	4. [Building the Project](#building-the-project)
	5. [Testing](#testing)
	6. [Style Guidelines](#style-guidelines)
	7. [Code Formatting Rules](#code-formatting)
	8. [Whitespace Cleanup](#whitespace-cleanup)
8. [Pull Request Guidelines](#pull-request-process)
	1. [Review Process](#review-process)
	2. [Addressing Feedback](#addressing-feedback)
9. [Community](#community)


## Code of Conduct

By participating in this project, you agree to abide by the Embedded Artistry [Code of Conduct][0]. We expect all contributors to follow the [Code of Conduct][0] and to treat fellow humans with respect.

## Important Resources

This project is managed on GitHub:

* [GitHub Project Page][8]
* [GitHub Issue Tracker][6]

Questions can also be submitted [on the Embedded Artistry website](https://embeddedartistry.com/contact) and in the [Embedded Artistry Forum](https://embeddedartistry.com/community/embedded-artistry-oss/).

Useful Documentation:

* [Library Documentation][9]
* [cppreference (API notes)](http://en.cppreference.com)
* [C Standard Library Header Files](http://en.cppreference.com/w/c/header)
* [Issue Template/Checklist](ISSUE_TEMPLATE.md)
* [Pull Request template/Checklist](PULL_REQUEST_TEMPLATE.md)

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

* Filing a new [GitHub Issue][6]
* [Submitting a question on the Embedded Artistry website](https://embeddedartistry.com/contact)
* [Submitting a question on the Embedded Artistry forum](https://embeddedartistry.com/community/embedded-artistry-oss/)
* Asking a question [on Twitter: (mbeddedartistry)](https://twitter.com/mbeddedartistry/).

## Feature Requests

We welcome feature requests!

For all requests, [please file a new GitHub issue][6]. Please provide the details about the feature/function you would like to see and why you need it. Please discuss your ideas and feedback before proceeding.

For new features or functions which have not been implemented, please label your request with the "Feature" label. If you are requesting an improvement on an existing function, please use the "Enhancement" label.

Small Changes can directly be crafted and submitted to the GitHub Repository as a Pull Request. See the section regarding [Pull Request Submission Guidelines](#pull-request-guidelines).

## Reporting Bugs

Before you submit your issue, please [search the issue archive][6] - maybe your question or issue has already been identified or addressed.

If you find a bug in the source code, you can help us by [submitting an issue to our GitHub issue tracker][6]. Even better, you can submit a Pull Request with a fix!

This project uses an [issue template](ISSUE_TEMPLATE.md), which GitHub will auto-populate when you create a new issue. Please make sure to follow the template and provide the necessary information. This will help us track down the bug as quickly as possible.

## Improving Documentation

Should you have a suggestion for the documentation, you can open an issue and outline the problem or improvement you have - however, creating the doc fix yourself is much better! By creating a new issue (or commenting on a related existing one), you let others know what you're working on. If you're making a small change (typo, phrasing) don't worry about filing an issue first - just open a Pull Request.

I currently need the most help with improving the libc in-source Doxygen documentation and commenting. If you would like to help, please select a header in the `include/` folder and add Doxygen style comments to functions with no documentation.

For large fixes, please build and test the documentation before submitting the PR to be sure you haven't accidentally introduced any layout or formatting issues. To generate the Doxygen documentation, run:

```
make doc
```

You can find the resulting output in `buildresults/doc` folder.

## Contributing Code

If you're interested in contributing code to this project, read on! Don't know where to start? Take a look at the [Finding an Issue](#finding-an-issue) section for help finding beginner-friendly issues.

If you are working on your first open source project or pull request, here are some helpful tutorials:

* [How to Contribute to an Open Source Project on GitHub][2]
* [Make a Pull Request][3]
* [First Timers Only][4]

### Getting Started

Install these dependencies:

* [Doxygen](http://www.stack.nl/~dimitri/doxygen/) must be installed to generate documentation
* [Meson](#meson-build-system) is the build system
* [`git-lfs`](https://git-lfs.github.com) is used to store binary files
* `make` is required to use Makefile shims
* A compiler should be installed in order to build the project (gcc + clang have been tested)

You will need to fork the main repository to work on your changes. Simply navigate to our GitHub page and click the "Fork" button at the top. Once you've forked the repository, you can clone your new repository and start making edits.

When using `git`, it is best to isolate each topic or feature into a “topic branch”. Branches are a great way to group commits related to one feature together, or to isolate different efforts when you might be working on multiple topics at the same time.

While it takes some experience to get the right feel about how to break up commits, a topic branch should be limited in scope to a single issue. If you are working on multiple issues, please create multiple branches and submit them for review separately.

```
# Checkout the master branch - you want your new branch to come from master
git checkout master

# Create a new branch named newfeature (give your branch its own simple informative name)
git branch newfeature

# Switch to your new branch
git checkout newfeature
```

For more information on the GitHub fork and pull-request processes, [please see this helpful guide][5].

#### git-lfs

This project stores some files using [`git-lfs`](https://git-lfs.github.com).

To install `git-lfs` on Linux or WSL:

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

To install on OS X:

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

### `adr-tools`

This repository uses [Architecture Decision Records](https://embeddedartistry.com/blog/2018/4/5/documenting-architectural-decisions-within-our-repositories). Please install [`adr-tools`](https://github.com/npryce/adr-tools) to contribute to architecture decisions.

If you are using OS X, you can install `adr-tools` through Homebrew:

```
brew install adr-tools
```

If you are using Windows or Linux, please install `adr-tools` via [GitHub](https://github.com/npryce/adr-tools).

### Finding an Issue

The list of outstanding feature requests and bugs can be found on our on our [GitHub issue tracker][6]. Pick an unassigned issue that you think you can accomplish and add a comment that you are attempting to do it.

* [`good first issue`](https://github.com/embeddedartistry/libc/issues?q=is%3Aissue+is%3Aopen+label%3A%22good+first+issue%22) labeled issues are deemed to be good low-hanging fruit for newcomers to the project
* [`help wanted`](https://github.com/embeddedartistry/libc/issues?q=is%3Aissue+is%3Aopen+label%3A%22help+wanted%22) labeled issues may be more difficult than `good first issue` and may include new feature development
* [`Documentation`](https://github.com/embeddedartistry/libc/issues?q=is%3Aissue+is%3Aopen+label%3ADocumentation_) labeled issues apply to new documents

### Development Process

`master` contains the latest code, and new versions are tagged nightly.

Please branch from `master` for any new changes. Once you are ready to merge changes, open a pull request. The build server will test and analyze the branch to ensure it can be safely merged.

### Building the Project

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

### Testing

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

### Style Guidelines

This project does not currently have an explicit style guideline, other than the formatting that is specified below.

When making changes to existing files, please keep the style consistent.

### Code Formatting

This repository enforces formatting using `clang-format`.

You can auto-format your code to match the style guidelines by issuing the following command:

```
make format
```

Formatting is enforced by the Jenkins build server which runs continuous integration for this project. Your Pull Request will not be accepted if the formatting check fails.

### Whitespace Cleanup

Don’t mix code changes with whitespace cleanup! If you are fixing whitespace, include those changes separately from your code changes. If your request is unreadable due to whitespace changes, it will be rejected.

Please submit any whitespace cleanups in a separate pull request.

### Git Commit Guidelines

The first line of the commit log must be treated as as an email subject line.  It must be strictly no greater than 50 characters long. The subject must stand on its own and not only make external references such as to relevant bug numbers.

The second line must be blank.

The third line begins the body of the commit message (one or more paragraphs) describing the details of the commit.  Paragraphs are each separated by a blank line. Manual line breaks are not required.

The last part of the commit log should contain all "external references", such as which issues were fixed.

For further notes about git commit messages, [please read this blog post][7].

## Pull Request Process

When you are ready to generate a pull request for preliminary review or merging into the project, you must first push your local topic branch back up to GitHub:

```
git push origin newfeature
```

Once you've committed and pushed all of your changes to GitHub:
	* Go to the page for your fork on GitHub
	* Select your development branch
	* Click the pull request button

If you need to make any adjustments to your pull request, just push the updates to your branch. Your pull request will automatically track the changes on your development branch and update.

Please follow the [Pull Request Template](PULL_REQUEST_TEMPLATE.md) for this project. GitHub will automatically populate the pull request description with this template.

### Review Process

Changes must build correctly on the Jenkins CI server, be free of formatting errors, and pass tests.

Once the changes pass the CI process, I will review the source code and provide feedback. I work on a variety of projects, so please expect some delay in getting back to you with a code review. I will notify you as soon as I have seen the PR and provide insight into the expected review timeline.

### Addressing Feedback

Once a PR has been submitted, your changes will be reviewed and constructive feedback may be provided. Feedback isn't meant as an attack, but to help make sure the highest-quality code makes it into our project. Changes will be approved once required feedback has been addressed.

If a maintainer asks you to "rebase" your PR, they're saying that a lot of code has changed, and that you need to update your fork so it's easier to merge.

To update your forked repository, follow these steps:

```
# Fetch upstream master and merge with your repo's master branch
git fetch upstream
git checkout master
git merge upstream/master

# If there were any new commits, rebase your development branch
git checkout newfeature
git rebase master
```

If too much code has changed for git to automatically apply your branches changes to the new `master`, you will need to manually resolve the merge conflicts yourself.

Once your new branch has no conflicts and works correctly, you can override your old branch using this command:

```
git push -f
```

Note that this will overwrite the old branch on the server, so make sure you are happy with your changes first!

**If you have any questions about this process, please ask for help!**

## Community

Anyone interested in active conversation regarding this project should [join the Embedded Artistry community]https://embeddedartistry.com/community/embedded-artistry-oss/).

You can also [reach out on Twitter: mbeddedartistry](https://twitter.com/mbeddedartistry/).

[0]: CODE_OF_CONDUCT.md
[1]: style_guidelines.md
[2]: https://egghead.io/series/how-to-contribute-to-an-open-source-project-on-github
[3]: http://makeapullrequest.com/
[4]: http://www.firsttimersonly.com
[5]: https://gist.github.com/Chaser324/ce0505fbed06b947d962
[6]: https://github.com/embeddedartistry/libc/issues
[7]: http://tbaggery.com/2008/04/19/a-note-about-git-commit-messages.html
[8]: https://github.com/embeddedartistry/libc/
[9]: https://embeddedartistry.github.io/libc/index.html
[10]: https:/embeddedartistry.com
