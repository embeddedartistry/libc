#!/bin/bash
# Script invocation:
#	clang-tidy.sh [location of compile_commands.json] [directories] [file types]
#
# Argument 1 is the path to the compile_commands.json file for your build.
# Argument 2 is a comma-deliminted list of directories that will be included
# 	in the clang-tidy analysis
#	e.g., "src,arch,test"
# Argument 3 is a comma-deliminted list of file extensions or filenames to include
#	in the clang-tidy analysis
#	e.g., "*.c,*.cpp"

# Argument 1 is the path to the directory containing the compile_commands.json file
BUILD_OUTPUT_FOLDER=${1:-buildresults}

# Argument 2 is a list of directories to include in clang-tidy analysis
IFS=',' read -ra DIRS <<< "$2"

# Argument 3 is a list of file names/types to include in clang-tidy analysis
FILE_TYPES=
IFS=',' read -ra ENTRIES <<< "$3"
for entry in "${ENTRIES[@]}"; do
	FILE_TYPES="$FILE_TYPES -o -iname $entry"
done

# Remove the initial `-o` argument for the first file type
# otherwise the rules will not be properly parsed
FILE_TYPES=${FILE_TYPES:3:${#FILE_TYPES}}

find ${DIRS[@]} ${FILE_TYPES} \
	| xargs clang-tidy -p $BUILD_OUTPUT_FOLDER ${@:4}
