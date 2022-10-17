#!/bin/bash

# This script will iterate through your git repository and set the file timestamp
# For each file tot he last time it was changed in history.
#
# Why do this sort of thing, you ask?
# Well, mostly, to produce deterministic zip files. Different timestamps resulting from
# different clone times can produce different MD5 hashes for the same file contents.
# This is because timestamps get saved. So we overwrite them.
#
# Other archive formats may also benefit from a deterministic timestamp method.
#
# This particular approach is slower, this ensures consistency of archives of source files
# Even across commits.

cd ${MESON_SOURCE_ROOT}

rev=HEAD
if [[ "$OSTYPE" == "darwin"* ]]; then
	git ls-tree -r -t --full-name --name-only "$rev" | while read filename ; do
		touch -t $(git log --pretty=format:%cd --date=format:%Y%m%d%H%m.%S -1 "$rev" -- "$filename") "$filename";
	done
else
	git ls-tree -r -t --full-name --name-only "$rev" | while read filename ; do
		touch -d $(git log --pretty=format:%cI -1 "$rev" -- "$filename") "$filename";
	done
fi
