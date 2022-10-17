##############################
# sloccount Analysis Support #
##############################
#
# This module adds an sloccount target to your build system, which provides
# line of code analysis and cost/effort estimates for your project.
#
# All variables used below can be overridden by the user. Simply define the variables
# with your own values before invoking this module.
#
# The settings for this module default to "embedded" COCOMO mode:
# 	Embedded: The project must operate within tight (hard-to-meet) constraints,
#	and requirements and interface specifications are often non-negotiable.
#	The software will be embedded in a complex environment that the software must deal with as-is.
#
# Values for the models are:
#	Organic: effort factor = 2.4, exponent = 1.05; schedule factor = 2.5, exponent = 0.38
#	Semidetached: effort factor = 3.0, exponent = 1.12; schedule factor = 2.5, exponent = 0.35
#	Embedded: effort factor = 3.6, exponent = 1.20; schedule factor = 2.5, exponent = 0.32
#
# For information on tuning the model, see:
#	https://dwheeler.com/sloccount/sloccount.html#cocomo

sloccount_default_directories = [
	meson.source_root() / 'src',
	meson.source_root() / 'test',
]

sloccount_dirs = get_variable('sloccount_dirs', sloccount_default_directories)
sloccount_additional_dirs = get_variable('sloccount_additional_dirs', [])

# sloccount_effort is a pair of values [F, E], where F is the factor and E is the exponent.
# this impacts calculated effort in person-months.
sloccount_effort = get_variable('sloccount_effort', ['3.6', '1.12'])

# sloccount_schedule is a pair of values [F, E], where F is the factor and E is the exponent.
# this impacts calculated effort in person-months.
sloccount_schedule = get_variable('sloccount_schedule', ['2.5', '0.32'])

# The average salary value to use in cost estimates
sloccount_salary = get_variable('sloccount_salary', '140000')

# The developer overhead value to use in cost estimates
sloccount_overhead = get_variable('sloccount_overhead', '2')

sloccount_default_args = [
	# Follow symbolic links
	'--follow',
	# Store data in the output directory
	'--datadir', meson.current_build_dir(),
	# Effort factor/exponent
	'--effort', sloccount_effort,
	# Schedule factor/exponent
	'--schedule', sloccount_schedule,
	# Annual Salary Setting
	'--personcost', sloccount_salary,
	# Overhead value
	'--overhead', sloccount_overhead,
]

# Provides the ability to override the sloccount default arguments
sloccount_args = get_variable('sloccount_args', sloccount_default_args)

# You can use this variable to supply additional arguments
# without overriding the defaults
sloccount_additional_args = get_variable('sloccount_additional_args', [])

# sloccount targets will be disabled if the program isn't found
sloccount = find_program('sloccount', required: false, disabler: true)

sloccount_arg_set = [
	# Supply Arguments
	sloccount_args,
	sloccount_additional_args,
	# Directories to analyze
	sloccount_dirs,
	sloccount_additional_dirs,
]

run_target('sloccount',
	command: [
		sloccount,
		sloccount_arg_set
	]
)

run_target('sloccount-full',
	command: [
		sloccount,
		'--details',
		sloccount_arg_set
	]
)

sloccount_lines = custom_target('sloccount.sc',
	output: 'sloccount.sc',
	command: [
		sloccount,
		sloccount_arg_set,
	],
	capture: true,
	build_by_default: false,
	build_always_stale: true,
)

sloccount_files = custom_target('sloccount_detailed.sc',
	output: 'sloccount_detailed.sc',
	command: [
		sloccount,
		# Show details for every source code file
		'--details',
		sloccount_arg_set,
		sloccount_additional_args,
	],
	capture: true,
	build_by_default: false,
	build_always_stale: true,
)

alias_target('sloccount-report', sloccount_lines)
alias_target('sloccount-full-report', sloccount_files)

