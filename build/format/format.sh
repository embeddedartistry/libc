#!/bin/bash

# Script invocation:
#	format.sh [options] DIRS TYPES
#
# Argument 1 is a list of directories to search for files in, delimited by commas
#	e.g., src,include
#	This is required
# Argument 2 is a list of file types to search for, delimited by commas
#	e.g., *.c,*.h,*.cpp,*.hpp
#	This is required
#
# Optional arguments:
# -e specifies is a comma-separated list of directories to exclude, delimited by commas
#	e.g.: -e src/gdtoa,src/external
# -p generates a patch file using a `git`
#
## NOTE: Due to getopts limitations, optional arguments must precede positional arguments
#
## Processing strategy for separating CSVs is derived from:
## https://stackoverflow.com/questions/918886/how-do-i-split-a-string-on-a-delimiter-in-bash#tab-top

MESON_BUILD_ROOT=${MESON_BUILD_ROOT:-buildresults}
MESON_SOURCE_ROOT=${MESON_SOURCE_ROOT:-../../}
FILE_TYPES=
EXCLUDES_ARGS=
PATCH='0'

while getopts "e:p" opt; do
  case $opt in
    e) EXCLUDES_ARGS="$OPTARG"
    ;;
    p) PATCH='1'
    ;;
    \?) echo "Invalid option -$OPTARG" >&2
    ;;
  esac
done

# Shift off the getopts args, leaving us with positional args
shift $((OPTIND -1))

IFS=',' read -ra DIRS <<< "$1"

IFS=',' read -ra ENTRIES <<< "$2"
for entry in "${ENTRIES[@]}"; do
	FILE_TYPES="$FILE_TYPES -o -iname \"$entry\""
done

IFS=',' read -ra ENTRIES <<< "$EXCLUDES_ARGS"
for entry in "${ENTRIES[@]}"; do
	EXCLUDES="$EXCLUDES -o -path \"$entry\""
done

if [[ ! -z $EXCLUDES ]]; then
	# Remove the initial `-o` argument for a single/first directory
	EXCLUDES=${EXCLUDES:3:${#EXCLUDES}}

	# Create the final argument string
	EXCLUDES="-type d \( $EXCLUDES \) -prune"
else
	# Remove the initial `-o` argument for the first file type if there are no excludes,
	# otherwise the rules will not be properly parsed
	FILE_TYPES=${FILE_TYPES:3:${#FILE_TYPES}}
fi

cd ${MESON_SOURCE_ROOT}
eval find ${DIRS[@]} ${EXCLUDES} -type f ${FILE_TYPES} \
	| xargs clang-format -style=file -i -fallback-style=none

if [ "$PATCH" == '1' ]; then
	git diff > clang_format.patch

	# Delete if 0 size
	if [ ! -s clang_format.patch ]
	then
		rm clang_format.patch
	fi
fi
