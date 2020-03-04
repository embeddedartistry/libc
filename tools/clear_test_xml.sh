#!/bin/bash

if [ -d "${MESON_BUILD_ROOT}/test" ]
then
	rm -f ${MESON_BUILD_ROOT}/test/*.xml
fi
