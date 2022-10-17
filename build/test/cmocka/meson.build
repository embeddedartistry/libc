#################
# CMocka Module #
#################
#
# This module provides common definitions and associated targets for
# programs using CMocka.
#
# This module will create a `clear-test-results` file which deletes
# all XML files in the build output's test subdirectory recursively.
# This is because CMocka will not overwrite existing XML files.
#
# The behavior of this target can be customized with three variables:
#	delete_test_results_root: a string for the top-level directory to run the script on
#	delete_test_results_rule: a string for the file name or file glob to delete
#	delete_test_results_recursive: a boolean, true = recursive delete, false = only delete in
#		the specified directory
#
# Variable overrides must be defined before invoking this module.
#
# Include this module *before* your unit tests folder or unit test declarations!

#####################
# CMocka Dependency #
#####################

# Searches for a library on the system, and falls back to a subproject otherwise
cmocka_native_dep = dependency('cmocka', native: true, fallback: ['cmocka', 'cmocka_native_dep'])

# Handle case where Linux fails to build because cmocka.h can't be found due to `-nostdinc`:
if cmocka_native_dep.type_name() != 'internal' and \
	false == native_c_compiler.has_header('cmocka.h',
		args: '-nostdinc',
		dependencies: cmocka_native_dep.partial_dependency(compile_args: true))

	# Header isn't found with `-nostdinc`, even though library is: revert to subproject
	cmocka_subproject = subproject('cmocka')
	cmocka_native_dep = cmocka_subproject.get_variable('cmocka_native_dep')
endif

#########################
# Convenience Variables #
#########################

# Tell CMocka where to place test files
# Note that this directory must exist prior to running the test program
cmocka_test_output_dir = 'CMOCKA_XML_FILE=' + meson.build_root() + '/test/%g.xml'

# This files variable can be used to invoke a CMocka program with an environment variable
# such as the one above
cmocka_with_env_script = files('../../scripts/exec_program_with_env.sh')

######################
# Associated Targets #
######################

# If you want to implement a deletion target, you can reference
# This files object to gain access to the script
delete_files_script = files('../../scripts/delete_files_in_dir.sh')

delete_test_results_root = get_variable('delete_test_results_root', meson.build_root() / 'test')
delete_test_results_rule = get_variable('delete_test_results_rule', '*.xml')
delete_test_results_recursive = get_variable('delete_test_results_recursive', true)

if delete_test_results_recursive
	delete_test_results_recursive_arg = '--recursive'
else
	delete_test_results_recursive_arg = []
endif

run_target('clear-test-results',
	command: [
		delete_files_script,
		# Directory to search for files
		delete_test_results_root,
		# File name or globbed extension to delete
		delete_test_results_rule,
		# Recursively searches all subdirs and removes the file name/type
		delete_test_results_recursive_arg
	]
)
