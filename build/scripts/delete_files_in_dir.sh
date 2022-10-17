#!/bin/bash

# Arugment $1 is the directory path
# Arugment $2 is the file type
# The shell will perform globbing if you pass a globbed extension (*.xml)
# Otherwise you can remove a single file.
# Because of -f, this will not fail if the files/directories do not exist.
# If the 3rd argument is supplied as `--recursive`, we'll enable recursive deletion.

if [ "$3" == '--recursive' ]; then
	find ${1} -name "${2}" -exec rm -f {} \;
else
	rm -f ${1}/${2}
fi


