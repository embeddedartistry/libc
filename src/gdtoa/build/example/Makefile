# This makefile is used to provide convenient access to the generated  makefile
# This makefile would go at your project root

# Specify the premake file to build. By default, we'll try to use the example.
PREMAKE_FILE ?= build/example/premake5.lua

# Export all args to act as a passthrough
export

all: build

.PHONY: build_gen
build_gen:
	@build/bin/premake5 --file=$(PREMAKE_FILE) gmake

.PHONY: build
build: build_gen
	@make -C build/gen/

.PHONY: help
help: build_gen
	@make -C build/gen/ help

.PHONY: clean
clean:
	@make -C build/gen/ clean
	@rm -rf buildresults

.PHONY: purify
purify: clean
	@rm -rf build/gen

.PHONY: regen
regen:
	@build/bin/premake5 --file=build/premake5.lua gmake


