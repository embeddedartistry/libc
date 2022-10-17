#!/bin/bash

# Script invocation:
#   package.sh [options] <Base Filename> <Dirs and Files to Include>
#
#   You can specify any number of directories and files to include in the archive. Files can be separated
#   by spaces: docs include buildresults/lib/libc.a
#
#   They can also be separated by commas: docs,include,buildresults/lib/libc.a
#
#   If you wish to change directories before adding files to the archive, add the directory
#   name (relative to the source root), followed by a colon, followed by a comma-separated list of files
#   to add from that directory: include,arch/x86_64/include buildresults:docs buildresults/lib:libc.a
#
### Example Invocation ###
# package.sh -a x86_64 -c x86_64 -s darwin -n -v 1.0.1 libc_native include,arch/x86_64/include buildresults:doc buildresults/libc_native.a
#
# Arguments
# * `-a` indicates the target architecture (`x86_64`, `arm`)
# * `-c` indicates the target chip (`Cortex-M3`, `STM32F103VBIx`)
# * `-s` indicates the target system (`darwin`, `none`)
# * `-v` indicates the version
#
# Positional Arguments
#
# The first postitional argument must be the base filename for the archive,
#   such as libc or libc_native
# Following that come lists of folders/files to include for processing, as defined above.

MESON_SOURCE_ROOT=${MESON_SOURCE_ROOT:-''}

if [[ "${MESON_SOURCE_ROOT}" == '' ]]; then
    MESON_SOURCE_ROOT=$(pwd)
fi

MESON_BUILD_ROOT=${MESON_BUILD_ROOT:-${MESON_SOURCE_ROOT}/buildresults}

ARCH='undef'
CHIP='undef'
SYSTEM='undef'

while getopts "a:c:s:v:" opt; do
  case $opt in
    a) ARCH="$OPTARG"
    ;;
    c) CHIP="$OPTARG"
    ;;
    s) SYSTEM="$OPTARG"
    ;;
    v) VERSION="$OPTARG"
	;;
    \?) echo "Invalid option -$OPTARG" >&2
    ;;
  esac
done

# Shift off the getopts args, leaving us with positional args
shift $((OPTIND -1))

######################
# Construct Filename #
######################

FILENAME=$1

if [ "$VERSION" != '' ]; then
    FILENAME+=_${VERSION}
fi

FILENAME+=_${ARCH}-${CHIP}-${SYSTEM}
FILENAME+=.tgz

#################
# Create Output #
#################

RELEASE_DIR=${MESON_BUILD_ROOT}/releases
mkdir -p "${RELEASE_DIR}"
# Create an empty arcive so we can update it in our processing loop below
tar -cf ${RELEASE_DIR}/${FILENAME} -T /dev/null

# Arg 1 = filename, so all remaining args are includes
for value in "${@:2}"; do
    if [[ "$value" == *':'* ]]; then
        DIR=${value%:*}
        FILES=${value#*:}
    else
        DIR=
        FILES=$value
    fi

    # Convert CSV files lists into spaces
    IFS=',' read -ra ENTRIES <<< "$FILES"
    FILES=
    for file in "${ENTRIES[@]}"; do
        FILES="$FILES $file"
    done

    # Change directory if necessary
    if [[ ! -z $DIR ]]; then
        cd $DIR
    fi

    ## Add the files to the directory
    tar -uf ${RELEASE_DIR}/${FILENAME} ${FILES}

    # Return to the last directory for next loop
    if [[ ! -z $DIR ]]; then
        cd -
    fi
done
