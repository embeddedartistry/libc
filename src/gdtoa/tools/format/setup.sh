#!/bin/bash

if [ -z "$1" ]; then
	# if no argument is specified, use the default
	format_file="clang_format"
else
	format_file=$1
fi

fmt_dir=$(dirname "$0")

if [ "$fmt_dir" == "." ]; then
	fmt_dir=$PWD
else
	#change to that directory to start our search
	cd $fmt_dir
fi

repo=`basename \`git rev-parse --show-toplevel\``

if [ "$repo" != "format" ]; then
	echo "Please call this script from the format submodule"
	exit 1
fi

# Assume we are a submodule: move up at least one directory
# If it has a git directory, deploy clang-format there.
# We limit ourselves to three directories up

for i in `seq 1 3`;
do
	cd ../
	if [ -d ".git" ]; then
		echo "Parent git repository found $i levels up: deploying style $format_file."
		cp $fmt_dir/style/$format_file $PWD/.clang-format
		exit 0
	fi
done

# Didn't find one? Error out

echo "Couldn't find a parent directory within three levels that has a .git folder. Please deploy clang-format manually."

exit 1
