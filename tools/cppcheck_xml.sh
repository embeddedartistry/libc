#!/bin/bash

MESON_CURRENT_SOURCE_DIR=${MESON_CURRENT_SOURCE_DIR:-./}
MESON_BUILD_ROOT=${MESON_BUILD_ROOT:-buildresults}

cppcheck --quiet --enable=style --force --xml --xml-version=2 \
	-I ${MESON_CURRENT_SOURCE_DIR}/include \
	src test \
	2>${MESON_BUILD_ROOT}/cppcheck.xml
