###############################################
# Automated Code Formatting with Clang-Format #
###############################################
# By including this module in your build, you will gain access to clang-format
# targets, which run clang-format on your project using the default settings
# which are expected to be in .clang-format file(s) in your source tree.
#
# By default, clang-format will run on all .c/.h/.cpp/.hpp files in the `src` and `test`
# directories in the source root of the project. If you need to override the default
# settings, you can do so by defining a variable called clangformat_args. This variable should
# be an array of strings, including options that will be passed to the `format.sh` script,
# as well as files and folders to be checked by clang-format.
#
# If you want to use the default settings and simply want to add subdirectories to exclude from
# formatting, you can define a variable called `clangformat_excludes`. This variable should be
# an array of directories and files to exclude. This module will convert them to the proper
# format expected by the script.
#	NOTE: Meson You need to exclude with the full path - make sure to add the source root!
#		You will also need to leave off the trailing slash.
# 	clangformat_excludes = [
#		meson.source_root() / 'src/utilities/type_safe',
#		meson.source_root() / 'src/utilities/debug_assert',
#	]
#
# A list of options can be found below. For more information, please see the documentation
# in format.sh

# [Optional] specify files and directories to exclude from the build
clangformat_excludes = get_variable('clangformat_excludes', [])

# This variable should be a string, which is a comma-separated list of directories
# to exclude from formatting. The -e argument is used to indicate excludes in the script.
if clangformat_excludes.length() > 0
	clangformat_excludes_processed = ''
	foreach entry : clangformat_excludes
		clangformat_excludes_processed += entry + ','
	endforeach
	clangformat_excludes_processed = ['-e', clangformat_excludes_processed]
else
	clangformat_excludes_processed = []
endif

# Target files and folders to include in clang-format analysis
clangformat_default_targets = [
	meson.source_root() / 'src',
	meson.source_root() / 'test',
]

# Override this variable to supply your own list of targets
clangformat_targets = get_variable('clangformat_targets', clangformat_default_targets)
# Define this variable to add new targets to the default list
clangformat_additional_targets = get_variable('clangformat_additional_targets', [])

# Convert into expected format for script: CSV
clangformat_targets_processed = ''
foreach entry : clangformat_targets + clangformat_additional_targets
	clangformat_targets_processed += entry + ','
endforeach

# File types to be included in cppcheck analysis
clangformat_default_file_types = [
	'*.c',
	'*.h',
	'*.cpp',
	'*.hpp'
]

# Override this variable to supply your own list of file types
clangformat_file_types = get_variable('clangformat_file_types', clangformat_default_file_types)
clangformat_additional_file_types = get_variable('clangformat_additional_file_types', [])

# Convert into expected format for script: CSV
clangformat_file_types_processed = ''
foreach entry : clangformat_file_types + clangformat_additional_file_types
	clangformat_file_types_processed += entry + ','
endforeach

## Default arguments used for clang format processing script
clangformat_default_args = [
	# Optional exclude directories (separated by commas)
	clangformat_excludes_processed,
	# Directories to format files in
	clangformat_targets_processed,
	# File types to include in formatting (separated by commas)
	clangformat_file_types_processed,
]

# Override this variable to supply your own raw arguments to the script
clangformat_args = get_variable('clangformat_args', clangformat_default_args)

# Clang-format run target will be unavailable if the program isn't found
clangformat = find_program('clang-format', required: false, disabler: true)

# If you want to implement a custom clang-format target, you can reference
# This files object to gain access to the script
clangformat_script = files('format.sh')

if clangformat.found()
	run_target('format',
		command: [
			clangformat_script,
			# Supply arguments
			clangformat_args
		]
	)

	run_target('format-patch',
		command: [
			clangformat_script,
			# Enable patch file,
			'-p',
			# Supply arguments
			clangformat_args
		]
	)
endif

cp = find_program('cp')

run_target('update-format-rules',
	command: [
		cp,
		meson.current_source_dir() + '/.clang-format',
		meson.source_root()
	]
)
