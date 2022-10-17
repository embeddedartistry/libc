###############################
# Clang-tidy Analysis Support #
###############################
# By including this module in your build, you will gain access to a clang-tidy
# target, which runs clang-tidy on your project using the default settings
# which are expected to be in .clang-tidy file(s) in your source tree.
#
# You must provide a list of files to run `clang-tidy` on in a variable called
# clangtidy_files. The value should be an array of files objects. The variable must
# be declared before invoking this build module.
#
# If you want to provide manual options, you can specify them in a variable called
# clangtidy_options, which must be defined before including this module with subdir().
# The value of the variable must be a string or an array.

# Clang-tidy run target will be unavailable if the program isn't found
clangtidy = find_program('clang-tidy', required: false, disabler: true)

# If you want to implement a custom clang-tidy target, you can reference
# This files object to gain access to the script
clangtidy_script = files('clang-tidy.sh')

if clangtidy.found()
	if get_variable('clangtidy_files', []).length() == 0
		warning('clangtidy_files list not defined before including module, so the target is disabled.')
	else
		run_target('clang-tidy',
			command: [
				clangtidy_script,
				# Optional user overrides
				get_variable('clangtidy_options', ''),
				# Files,
				clangtidy_files
			],
		)
		run_target('clang-tidy-fix',
			command: [
				clangtidy_script,
				# Optional user overrides
				get_variable('clangtidy_options', ''),
				'--fix-errors', '--fix-notes',
				# Files,
				clangtidy_files
			],
		)
	endif
endif
