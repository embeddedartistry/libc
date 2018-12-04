# you can set this to 1 to see all commands that are being run
export VERBOSE := 0

ifeq ($(VERBOSE),1)
export Q :=
export VERBOSE := 1
else
export Q := @
export VERBOSE := 0
endif

BUILDRESULTS?=buildresults

all: libc

.PHONY: groundwork
groundwork:
	$(Q)if [ -d "$(BUILDRESULTS)" ]; then mkdir -p $(BUILDRESULTS); fi
	$(Q)if [ ! -e "$(BUILDRESULTS)/build.ninja" ]; then meson --buildtype plain $(BUILDRESULTS); fi

.PHONY: libc
libc: groundwork
	$(Q)cd $(BUILDRESULTS); ninja

.PHONY: docs
docs: groundwork
	$(Q)cd $(BUILDRESULTS); ninja docs

.PHONY: format
format:
	$(Q)tools/clang-format-libc.sh

.PHONY : format-diff
format-diff :
	$(Q)tools/format/clang-format-git-diff.sh

.PHONY : format-check
format-check :
	$(Q)tools/clang-format-patch-libc.sh

.PHONY: list-targets
list-targets: groundwork
	$(Q) cd $(BUILDRESULTS); ninja -t targets

.PHONY: list-targets-all
list-targets-all: groundwork
	$(Q) cd $(BUILDRESULTS); ninja -t targets all

.PHONY: analyze
analyze: groundwork
	$(Q) cd $(BUILDRESULTS); ninja scan-build

.PHONY: clean
clean:
	$(Q)echo Cleaning build artifacts
	$(Q)if [ -d "$(BUILDRESULTS)" ]; then cd $(BUILDRESULTS); ninja -t clean; fi
	$(Q)if [ -d "buildresults-coverage" ]; then cd buildresults-coverage; ninja -t clean; fi

.PHONY: purify
purify:
	$(Q)echo Removing Build Output
	$(Q)rm -rf $(BUILDRESULTS)/
	$(Q)rm -rf buildresults-coverage

.PHONY: ccc
ccc: groundwork
	$(Q)cd $(BUILDRESULTS); ninja complexity

.PHONY: cppcheck
cppcheck: groundwork
	$(Q)cd $(BUILDRESULTS); ninja cppcheck

.PHONY: cppcheck-xml
cppcheck-xml: groundwork
	$(Q)cd $(BUILDRESULTS); ninja cppcheck-xml

.PHONY: test
test: groundwork
ifneq ("$(wildcard $(BUILDRESULTS)/test/)","")
	$(Q)rm -f $(BUILDRESULTS)/test/*.xml
endif
	$(Q) cd $(BUILDRESULTS); meson test

.PHONY: coverage
coverage:
	$(Q)if [ -d "buildresults-coverage" ]; then mkdir -p buildresults-coverage; fi
	$(Q)if [ ! -e "buildresults-coverage/build.ninja" ]; then meson --buildtype plain buildresults-coverage -Db_coverage=true; fi
	$(Q)cd buildresults-coverage; ninja; ninja test; ninja coverage-html; ninja coverage-xml

.PHONY: tidy
tidy: groundwork
	$(Q) cd $(BUILDRESULTS); ninja tidy

### Help Rule ###
.PHONY : help
help :
	@echo "usage: make [OPTIONS] <target>"
	@echo "  Options:"
	@echo "    > VERBOSE     Boolean. Default Off."
	@echo "    > BUILDRESULTS Directory for build results. Default buildresults."
	@echo "Targets:"
	@echo "  To list targets that ninja can compile:"
	@echo "    list-targets: list build targets for project"
	@echo "    list-targets-all: list all targets ninja knows about"
	@echo "  groundwork: runs meson and repares the BUILDRESULTS directory"
	@echo "  buildall: builds all targets that ninja knows about"
	@echo "  clean: cleans build artifacts"
	@echo "  purify: removes the BUILDRESULTS directory"
	@echo "  docs: Builds documentation"
	@echo "  test: Run unit tests"
	@echo "  Code Formating:"
	@echo "    format: runs clang-format on codebase"
	@echo "    format-diff: generates a diff file with formatting changes"
	@echo "    format-check: checks whether formatting needs to be applied"
	@echo "  Static Analysis:"
	@echo "    analyze: runs clang static analysis"
	@echo "	   ccc: runs complexity analysis with lizard"
	@echo "    cppcheck: runs cppcheck"
	@echo "    cppcheck-xml: runs cppcheck and generates an XML report (for build servers)"
	@echo "    coverage: runs code coverage analysis and generates an HTML report and XML report"
	@echo "    tidy: runs clang-tidy linter"
