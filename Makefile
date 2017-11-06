# This makefile is used to provide convenient access to the generated  makefile

# Export all args to act as a passthrough
export

ifeq ($(OS),Windows_NT)
    detected_OS := Windows
else
    detected_OS := $(shell sh -c 'uname -s 2>/dev/null || echo NotDetected')
endif

ifeq ($(detected_OS), "Windows")
	premake_BIN := premake5.exe
else
	premake_BIN := premake5
endif

all: build test

.PHONY: build_gen
build_gen:
	@echo "Detected OS: ${detected_OS}. Using Premake binary: build/bin/${detected_OS}/${premake_BIN}"
	@build/bin/${detected_OS}/${premake_BIN} --file=premake5.lua gmake

.PHONY: build
build: build_gen
	@make -C build/gen/

.PHONY: help
help: build_gen
	@make -C build/gen/ help

.PHONY: clean
clean:
ifeq ("$(wildcard build/gen/)","")
	@echo "No generated build files: skipping clean"
else
	@make -C build/gen/ clean
endif

.PHONY: purify
purify: clean
	@rm -rf build/gen

.PHONY: regen
regen:
	@build/bin/premake5 --file=premake5.lua gmake

.PHONY: format
format:
	@tools/clang-format-libc.sh

.PHONY : format-diff
format-diff :
	@tools/format/clang-format-git-diff.sh

.PHONY: format-check
format-check:
	@tools/clang-format-patch-libc.sh

.PHONY: test
test: build
ifeq ("$(wildcard buildresults/testresults/)","")
	@mkdir -p buildresults/testresults
else
	@rm -f buildresults/testresults/*
endif
	@CMOCKA_XML_FILE=buildresults/testresults/%g.xml buildresults/x86_64_debug/test/libc.bin

