#!/bin/bash

# This script propagates all arguments to the clang-format command

clang-format -style=file -i -fallback-style=none $@

exit 0
