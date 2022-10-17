#!/bin/bash

# Script invocation:
#   cppcheck.sh [options] <dirs and files to process>
#
#   You can include any number of directories and files to pass to cppcheck. Files can be separated
#   by spaces: docs include buildresults/lib/libc.a
#
#	By default, `style` checks are enabled. You can override this setting with the -c flag.
#
### Example Invocation ###
# cppcheck.sh -e style,file -x src test
#
# Arguments
# `-c` takes a comma-separated list of styles that is directly passed to cppcheck.
#		If no -e option is specified, `style` is used.
# `-e` takes a comma-separated list of directories or files to exclude from checks
# `-i` takes a comma-separated list of include directory paths
# `-r` takes a comma-separated list of custom rule files
# `-x` will save the output in a file called `cppcheck.xml`
#
# Positional Arguments
#
# All positional arguments are directories or files to include in the checks.

MESON_CURRENT_SOURCE_DIR=${MESON_CURRENT_SOURCE_DIR:-./}
MESON_BUILD_ROOT=${MESON_BUILD_ROOT:-buildresults}

XML_ARGS=
XML_REDIRECT=
CHECKS=style
INCLUDES=
EXCLUDES=
RULES=

while getopts "c:e:i:r:x" opt; do
  case $opt in
    x) 	XML_ARGS='--xml --xml-version=2'
		XML_REDIRECT="2>${MESON_BUILD_ROOT}/cppcheck.xml"
    ;;
    c) CHECKS="$OPTARG"
	;;
	e)
		# Convert CSV files lists into spaces
		IFS=',' read -ra ENTRIES <<< "$OPTARG"
		for exclude in "${ENTRIES[@]}"; do
		    EXCLUDES="$EXCLUDES -i $exclude"
		done
	;;
	i)
		# Convert CSV files lists into spaces
		IFS=',' read -ra ENTRIES <<< "$OPTARG"
		for include in "${ENTRIES[@]}"; do
		    INCLUDES="$INCLUDES -I $include"
		done
	;;
	r)
		# Convert CSV files lists into spaces
		IFS=',' read -ra ENTRIES <<< "$OPTARG"
		for rules in "${ENTRIES[@]}"; do
		    RULES="$RULES --rule-file=$rules"
		done
	;;
    \?) echo "Invalid option -$OPTARG" >&2
    ;;
  esac
done

# Shift off the getopts args, leaving us with positional args
shift $((OPTIND -1))

eval cppcheck --quiet --enable=$CHECKS --inline-suppr --force ${XML_ARGS} \
	$INCLUDES $EXCLUDES $RULES $@ ${XML_REDIRECT}
