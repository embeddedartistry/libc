#!/bin/bash

# This script should be supplied with two arguments:
# The first is the program to execute
# The second is an environment variable string to include

export $2
eval $1
