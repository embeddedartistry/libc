# you can set this to 1 to see all commands that are being run
VERBOSE ?= 0

ifeq ($(VERBOSE),1)
export Q :=
export VERBOSE := 1
else
export Q := @
export VERBOSE := 0
endif

# This skeleton is built for CMake's Ninja generator
export CMAKE_GENERATOR=Ninja

BUILDRESULTS ?= buildresults
CONFIGURED_BUILD_DEP = $(BUILDRESULTS)/build.ninja

OPTIONS ?=
INTERNAL_OPTIONS =

CPM_CACHE?=$(HOME)/CPM_Cache
ifneq ($(CPM_CACHE),)
	INTERNAL_OPTIONS += -DCPM_SOURCE_CACHE=$(CPM_CACHE)
endif

LTO ?= 0
ifeq ($(LTO),1)
	INTERNAL_OPTIONS += -DENABLE_LTO=ON
endif

CROSS ?=
ifneq ($(CROSS),)
	INTERNAL_OPTIONS += -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/cross/$(CROSS).cmake
endif

NATIVE ?=
ifneq ($(NATIVE),)
	INTERNAL_OPTIONS += -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/native/$(NATIVE).cmake
endif

BUILD_TYPE ?=
ifneq ($(BUILD_TYPE),)
	INTERNAL_OPTIONS += -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)
endif

SANITIZER ?=
ifneq ($(SANITIZER),)
	INTERNAL_OPTIONS += -DUSE_SANITIZER=$(SANITIZER)
endif

all: default

.PHONY: default
default: | $(CONFIGURED_BUILD_DEP)
	$(Q)ninja -C $(BUILDRESULTS)

.PHONY: test
test: default
	$(Q)cd $(BUILDRESULTS); ctest

.PHONY: docs
docs: | $(CONFIGURED_BUILD_DEP)
	$(Q)ninja -C $(BUILDRESULTS) docs

.PHONY: package
package: default
	$(Q)ninja -C $(BUILDRESULTS) package
	$(Q)ninja -C $(BUILDRESULTS) package_source

.PHONY: cppcheck
cppcheck: | $(CONFIGURED_BUILD_DEP)
	$(Q) ninja -C $(BUILDRESULTS) cppcheck

.PHONY: cppcheck-xml
cppcheck-xml: | $(CONFIGURED_BUILD_DEP)
	$(Q) ninja -C $(BUILDRESULTS) cppcheck-xml

.PHONY: complexity
complexity: | $(CONFIGURED_BUILD_DEP)
	$(Q) ninja -C $(BUILDRESULTS) complexity

.PHONY: complexity-xml
complexity-xml: | $(CONFIGURED_BUILD_DEP)
	$(Q) ninja -C $(BUILDRESULTS) complexity-xml

.PHONY: complexity-full
complexity-full: | $(CONFIGURED_BUILD_DEP)
	$(Q) ninja -C $(BUILDRESULTS) complexity-full

.PHONY: tidy
tidy: $(CONFIGURED_BUILD_DEP)
	$(Q) ninja -C $(BUILDRESULTS) tidy

.PHONY: format
format: $(CONFIGURED_BUILD_DEP)
	$(Q)ninja -C $(BUILDRESULTS) format

.PHONY : format-patch
format-patch: $(CONFIGURED_BUILD_DEP)
	$(Q)ninja -C $(BUILDRESULTS) format-patch

.PHONY: scan-build
scan-build:
	$(Q) scan-build cmake -B $(BUILDRESULTS)/scan-build $(OPTIONS) $(INTERNAL_OPTIONS)
	$(Q) ninja -C $(BUILDRESULTS)/scan-build

.PHONY: coverage
coverage:
	$(Q) cmake -B $(BUILDRESULTS)/coverage -DCMAKE_BUILD_TYPE=Debug -DENABLE_COVERAGE=ON $(OPTIONS) $(INTERNAL_OPTIONS)
	$(Q) ninja -C $(BUILDRESULTS)/coverage
	$(Q) cd $(BUILDRESULTS)/coverage; ctest
	$(Q) ninja -C $(BUILDRESULTS)/coverage coverage

# Runs whenever the build has not been configured successfully
$(CONFIGURED_BUILD_DEP):
	$(Q)cmake -B $(BUILDRESULTS) $(OPTIONS) $(INTERNAL_OPTIONS)

# Manually Reconfigure a target, esp. with new options
.PHONY: reconfig
reconfig:
	$(Q) cmake -B $(BUILDRESULTS) $(OPTIONS) $(INTERNAL_OPTIONS)

.PHONY: clean
clean:
	$(Q) if [ -d "$(BUILDRESULTS)" ]; then ninja -C $(BUILDRESULTS) clean; fi

.PHONY: distclean
distclean:
	$(Q) rm -rf $(BUILDRESULTS)

.PHONY : help
help :
	@echo "usage: make [OPTIONS] <target>"
	@echo "  Options:"
	@echo "    > VERBOSE Show verbose output for Make rules. Default 0. Enable with 1."
	@echo "    > BUILDRESULTS Directory for build results. Default buildresults."
	@echo "    > OPTIONS Configuration options to pass to a build. Default empty."
	@echo "    > LTO Enable LTO builds. Default 0. Enable with 1."
	@echo "    > CROSS Enable a Cross-compilation build. "
	@echo "			Pass the cross-compilation toolchain name without a path or extension."
	@echo "			Example: make CROSS=cortex-m3"
	@echo "			For supported toolchains, see cmake/toolchains/cross/"
	@echo "    > NATIVE Use an alternate toolchain on your build machine. "
	@echo "			Pass the toolchain name without a path or extension."
	@echo "			Example: make CROSS=gcc-9"
	@echo "			For supported toolchains, see cmake/toolchains/native/"
	@echo "    > CPM_CACHE Specify the path to the CPM source cache."
	@echo "			Set the variable to an empty value to disable the cache."
	@echo "    > BUILD_TYPE Specify the build type (default: RelWithDebInfo)"
	@echo "			Option are: Debug Release MinSizeRel RelWithDebInfo"
	@echo "    > SANITIZER Compile with support for a Clang/GCC Sanitizer."
	@echo "        Options are: none (default), address, thread, undefined, memory,"
	@echo "        leak, and 'address,undefined' as a combined option"
	@echo "Targets:"
	@echo "  default: Builds all default targets ninja knows about"
	@echo "  tests: Build and run unit test programs"
	@echo "  docs: Generate documentation"
	@echo "  package: Build the project, generates docs, and create a release package"
	@echo "  clean: cleans build artifacts, keeping build files in place"
	@echo "  distclean: removes the configured build output directory"
	@echo "  reconfig: Reconfigure an existing build output folder with new settings"
	@echo "Static Analysis:"
	@echo "    cppcheck: runs cppcheck"
	@echo "    cppcheck-xml: runs cppcheck and generates an XML report (for build servers)"
	@echo "  Code Formating:"
	@echo "    format: runs clang-format on codebase"
	@echo "    format-patch: generates a patch file with formatting changes"
	@echo "  Static Analysis:"
	@echo "    cppcheck: runs cppcheck"
	@echo "    cppcheck-xml: runs cppcheck and generates an XML report (for build servers)"
	@echo "    scan-build: runs clang static analysis"
	@echo "    complexity: runs complexity analysis with lizard, only prints violations"
	@echo "    complexity-full: runs complexity analysis with lizard, prints full report"
	@echo "    complexity-xml: runs complexity analysis with lizard, generates XML report"
	@echo "        (for build servers)"
	@echo "    coverage: runs code coverage analysis and generates an HTML & XML reports"
	@echo "    tidy: runs clang-tidy linter"
