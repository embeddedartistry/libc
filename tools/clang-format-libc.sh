#!/bin/bash

find . -type d \( -path ./test/cmocka -o -path ./src/gdtoa \) -prune \
	-o -iname *.h -o -iname *.c -o -iname *.cpp -o -iname *.hpp \
	| xargs clang-format -style=file -i -fallback-style=none

exit 0
