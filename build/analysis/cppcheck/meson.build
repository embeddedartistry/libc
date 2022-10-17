#############################
# Cppcheck Analysis Support #
#############################
# By including this module in your build, you will gain access to cppcheck and
# cppcheck-xml targets.
#
# By default, cppcheck will be run with `--enable=style` on the `src` and `test`
# directories in the source root of the project. You can specify additional options like checks,
# exclude paths, include directories, and custom rule files by populating these variables
# before invoking this module. Configurable options are:
#	- cppcheck_paths
#	- cppcheck_additional_paths (use default, but add files/folders)
#	- cppcheck_includes
#	- cppcheck_excludes
#	- cppcheck_custom_rules
#	- cppcheck_checks
#
# In all cases, these variables should be defined as arrays of strings, even for n=1.
#
# If you need to override the default settings completely, you can do so by defining a variable
# called cppcheck_args. This variable should be an array of strings, formatted as expected
# by the cppcheck.sh script. You are responsible for formatting arguments in this case.

cppcheck_default_paths = [
	meson.source_root() / 'src',
	meson.source_root() / 'test',
]

cppcheck_default_custom_rules = [
	meson.current_source_dir() / 'cppcheck-rules/BitwiseOperatorInConditional/rule.xml',
	meson.current_source_dir() / 'cppcheck-rules/CollapsibleIfStatements/rule.xml',
	meson.current_source_dir() / 'cppcheck-rules/EmptyElseBlock/rule.xml',
	meson.current_source_dir() / 'cppcheck-rules/EmptyCatchStatement/rule.xml',
	meson.current_source_dir() / 'cppcheck-rules/EmptyDoWhileStatement/rule.xml',
	meson.current_source_dir() / 'cppcheck-rules/EmptyForStatement/rule.xml',
	meson.current_source_dir() / 'cppcheck-rules/EmptyIfStatement/rule.xml',
	meson.current_source_dir() / 'cppcheck-rules/EmptySwitchStatement/rule.xml',
	meson.current_source_dir() / 'cppcheck-rules/ForLoopShouldBeWhileLoop/rule.xml',
	meson.current_source_dir() / 'cppcheck-rules/InvertedLogic/rule.xml',
	meson.current_source_dir() / 'cppcheck-rules/MultipleUnaryOperator/rule.xml',
	meson.current_source_dir() / 'cppcheck-rules/RedundantConditionalOperator/rule.xml',
	meson.current_source_dir() / 'cppcheck-rules/RedundantIfStatement/rule.xml',
	meson.current_source_dir() / 'cppcheck-rules/UnnecessaryElseStatement/rule.xml',
	meson.current_source_dir() / 'cppcheck-rules/UseStlAlgorithm/rule.xml',
]

cppcheck_paths = get_variable('cppcheck_paths', cppcheck_default_paths)
cppcheck_additional_paths = get_variable('cppcheck_additional_paths', [])

# Include directory search paths for Cppcheck
cppcheck_includes = get_variable('cppcheck_includes', [])
if cppcheck_includes.length() > 0
	cppcheck_includes_processed = ''
	foreach entry : cppcheck_includes
		cppcheck_includes_processed += entry + ','
	endforeach
	# Convert to array with proper script argument
	cppcheck_includes_processed = ['-i', cppcheck_includes_processed]
else
	cppcheck_includes_processed = []
endif

# Files to exclude from analysis
cppcheck_excludes = get_variable('cppcheck_excludes', [])
if cppcheck_excludes.length() > 0
	cppcheck_excludes_processed = ''
	foreach entry : cppcheck_excludes
		cppcheck_excludes_processed += entry + ','
	endforeach
	# Convert to array with proper script argument
	cppcheck_excludes_processed = ['-e', cppcheck_excludes_processed]
else
	cppcheck_excludes_processed = []
endif

# Custom rules to use
cppcheck_custom_rules = get_variable('cppcheck_custom_rules', cppcheck_default_custom_rules)
# Add additional rules to the default list
cppcheck_custom_rules += get_variable('cppcheck_additional_custom_rules', [])
if cppcheck_custom_rules.length() > 0
	cppcheck_custom_rules_processed = ''
	foreach entry : cppcheck_custom_rules
		cppcheck_custom_rules_processed += entry + ','
	endforeach
	# Convert to array with proper script argument
	cppcheck_custom_rules_processed = ['-r', cppcheck_custom_rules_processed]
else
	cppcheck_custom_rules_processed = []
endif

# style checks to override
cppcheck_checks = get_variable('cppcheck_checks', [])
if cppcheck_checks.length() > 0
	cppcheck_checks_processed = ''
	foreach entry : cppcheck_checks
		cppcheck_checks_processed += entry + ','
	endforeach
	# Convert to array with proper script argument
	cppcheck_checks_processed = ['-c', cppcheck_checks_processed]
else
	cppcheck_checks_processed = []
endif

cppcheck_default_args = [
	# getopts arguments
	cppcheck_includes_processed,
	cppcheck_excludes_processed,
	cppcheck_custom_rules_processed,
	cppcheck_checks_processed,
	# Positional Arguments
	cppcheck_paths,
	cppcheck_additional_paths,
]

cppcheck_args = get_variable('cppcheck_args', cppcheck_default_args)

# Cppcheck run targets will be unavailable if the program isn't found
cppcheck = find_program('cppcheck', required: false, disabler: true)

# If you want to implement a custom cppcheck target, you can reference
# This files object to gain access to the script
cppcheck_script = files('cppcheck.sh')

if cppcheck.found()
	run_target('cppcheck',
		command: [
			cppcheck_script,
			# Supply Arguments
			cppcheck_args
		]
	)

	run_target('cppcheck-xml',
		command: [
			cppcheck_script,
			# Enable XML output
			'-x',
			# Supply Arguments
			cppcheck_args
		],
	)
endif

