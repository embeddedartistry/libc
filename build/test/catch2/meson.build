#################
# Catch2 Module #
#################
#
# This module provides a standalone Catch2 test program, requiring the user only to supply
# the necessary files and include directories to use with Catch2.
#
# By default, a test application will be built and registered with the meson test runner.
# The test runner will output JUNIT XML.
# Run targets will be defined as convenience aliases, as well as to produce alternate output.
#
# Default run targets are:
#	catch2-tests (default output)
#	catch2-tests-xml (generates junit xml)
#	catch2-tests-catch-xml (generates Catch XML output)
#
# Test source files, dependencies, header include paths, and additional settings are to be
# passed to the test program with a dependency variable named `catch2_test_deps`. This variable
# must be fully populated before invoking this build module.
#
# To override default variable values defined below, redefine them before including this module
# with subdir().
#
# Default targets can be disabled altogether by setting `catch2_disable_builtin_targets` to true

catch2_subproject = subproject('catch2')
catch2_dep = catch2_subproject.get_variable('catch2_dep')

# The default test program name is the project name + _catch2_test
# You can override this variable to change the program name.
catch2_test_program_name = get_variable('catch2_test_program_name',
										meson.project_name() + '_catch2_test')

# Default main() declaration for catch2. You can override this variable with a files()
# variable if you need custom settings
catch2_main_file = get_variable('catch2_main_file', files('catch_main.cpp'))

# Default output location when XML reports are generated.
# Override this variable for an alternate location.
catch2_file_output_dir = get_variable('catch2_file_output_dir', meson.build_root() / 'test')

# Default settings for our catch2 test programs. You can override these settings
# by populating a variable called `catch2_compile_settings`.
default_catch2_settings = [
	'-DCATCH_CONFIG_FAST_COMPILE',
	'-DCATCH_CONFIG_NO_WCHAR',
	'-DCATCH_CONFIG_NO_POSIX_SIGNALS',
	'-DCATCH_CONFIG_DISABLE_MATCHERS',
	'-DMSE_DISABLE_IOSTREAM',
	'-DMSE_SCOPEPOINTER_DEBUG_RUNTIME_CHECKS_DISABLED',
	'-fexceptions',
	'-funwind-tables',
]

# Override this variable to supply your own settings instead of using the defaults.
catch2_compile_settings = get_variable('catch2_compile_settings', default_catch2_settings)

# Variable for user-specified dependencies that are used to build the test program.
catch2_tests_dep = get_variable('catch2_tests_dep', [])

# If set to `true`, the built-in targets will not be provided, allowing you to provide your own.
catch2_disable_builtin_targets = get_variable('catch2_disable_builtin_targets', false)

catch2_junit_args = ['-s', '-r', 'junit', '-o',
	catch2_file_output_dir / catch2_test_program_name + '.xml']
catch2_catchxml_args = ['-s', '-r', 'xml', '-o',
	catch2_file_output_dir / catch2_test_program_name / 'catchformat.xml']

if catch2_disable_builtin_targets == false
	catch2_tests = executable(catch2_test_program_name,
		catch2_main_file,
		cpp_args: catch2_compile_settings,
		dependencies: [
			catch2_dep,
			catch2_tests_dep
		],
		native: true,
		build_by_default: meson.is_subproject() == false
	)

	test(catch2_test_program_name,
		catch2_tests,
		args: catch2_junit_args
	)

	run_target('catch2-tests',
		command: catch2_tests
	)

	run_target('catch2-tests-xml',
		command: [catch2_tests, catch2_junit_args]
	)

	run_target('catch2-tests-catch-xml',
		command: [catch2_tests, catch2_catchxml_args,]
	)

endif
