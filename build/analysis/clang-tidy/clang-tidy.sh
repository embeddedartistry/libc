#!/bin/bash

# This script expects you to use a .clang-tidy file in your resposistory, rather than
# supplying checks through the command line.

MESON_BUILD_ROOT=${MESON_BUILD_ROOT:-./buildresults}

cd "${MESON_BUILD_ROOT}"
sed -i.bak 's/-pipe//g' compile_commands.json

clang-tidy -quiet -p ${MESON_BUILD_ROOT} $@

# Restore the old copy
mv compile_commands.json.bak compile_commands.json
