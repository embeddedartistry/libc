#!/bin/bash

if [ -z "$1" ]
then
	echo "Please supply a directory or path with this script."
	exit 1
fi

find $1 -iname *.h -o -iname *.c -o -iname *.cpp -o -iname *.hpp \
	| xargs clang-format -style=file -i -fallback-style=none

exit 0
