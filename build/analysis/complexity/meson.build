##############################
# Complexity Analysis Module #
##############################
#
# This module adds complexity analysis using Lizard to the build, with multiple run targets.
#
# By default, lizard will run on all sourcefiles in the `src` and `test`
# directories in the source root of the project.
#
# This module provides multiple customization points:
#	- You can override the directories to analyze by setting a variable called lizard_paths.
#		This variable should be a string or an array of strings.
#	- You can add directories to the default list by setting a variable called lizard_additional_paths.
#		This variable should be a string or an array of strings.
#	- You can override the default value of specific parameters:
#		* lizard_length (integer) - the maximum length of a function
#		* lizard_ccn (integer) - the maximum CCN of a function
#		* lizard_arguments (integer) - the maximum arguments a function can contain
#	- You can insert lizard options other than --length, --CCN, --arguments by setting a variable
#		called lizard_insert_options. This variable should be a string or an array of strings.
#		This is most commonly used to exclude directories from the build.
#
# For maximum customization, you can also completely override all default arguments by defining
# lizard_args, which must be a string or array of strings. This will grant you full control
# over the settings used by the run targets.
#
# All variables must be defined before including this module.
#
# For a full list of available argument options, see the help output of the lizard program.

lizard_default_paths = [
	meson.source_root() / 'src',
	meson.source_root() / 'test',
]

lizard_paths = get_variable('lizard_paths', lizard_default_paths)
lizard_additional_paths = get_variable('lizard_additional_paths', [])

lizard_insert_options = get_variable('lizard_insert_options', [])

# Fail over this CCN
lizard_ccn = get_variable('lizard_ccn', 10).to_string()
# Fail when functions are longer than this
lizard_length = get_variable('lizard_length', 75).to_string()
# Fail at this arg count
lizard_arguments = get_variable('lizard_arguments', 10).to_string()

lizard_default_args = [
	# Custom options to insert
	lizard_insert_options,
	# Configuration
	'--length', lizard_length,
	'--CCN', lizard_ccn,
	'--arguments', lizard_arguments,
	# Counts switch/case with multiple args as 1
	'--modified',
	# Source Directories to audit
	lizard_paths,
	lizard_additional_paths,
]

lizard_args = get_variable('lizard_args', lizard_default_args)

# Lizard-based targets will be unavailable if the program isn't found
lizard = find_program('lizard', required: false, disabler: true)

# Only print violations
run_target('complexity',
	command: [lizard,
		lizard_args,
		'-w'
	]
)

# Print full output of lizard command
run_target('complexity-full',
	command: [lizard,
		lizard_args
	]
)

# Generate XML output
complexity_xml = custom_target('complexity.xml',
	output: 'complexity.xml',
	command: [
		lizard,
		lizard_args,
		'--xml'
	],
	capture: true,
	build_always_stale: true,
	build_by_default: false,
)

# Convenience target to generate the XML file via a command, instead of referencing the file
# directly (e.g., ninja -C buildresults/build/analysis/complexity/complexity.xml)
alias_target('complexity-xml', complexity_xml)
