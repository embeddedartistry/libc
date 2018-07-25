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

groundwork:
	$(Q) mkdir -p $(BUILDRESULTS)
	$(Q) meson $(BUILDRESULTS)

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

.PHONY: analyze
analyze: groundwork
	$(Q) cd $(BUILDRESULTS); ninja scan-build

.PHONY: clean
clean:
	$(Q)echo Cleaning Build Output
	$(Q)rm -rf $(BUILDRESULTS)/

.PHONY: test
test: libc
	$(Q)cd $(BUILDRESULTS); ./test/libc_test

