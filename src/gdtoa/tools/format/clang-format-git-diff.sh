#!/bin/bash

clang-format -style=file -fallback-style=none -i `git ls-files -om "*.[ch]" "*.[hc]pp"`

exit 0
