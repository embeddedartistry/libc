#!/bin/bash

if [ -d "${MESON_BUILD_ROOT}/test" ]
then
	rm ${MESON_BUILD_ROOT}/test/*.xml
fi
