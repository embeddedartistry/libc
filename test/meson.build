# Test Build Definition

libc_test_files = files(
	'main.c',
	'crt/crt_init_array.c',
	'crt/crt_tests.c',
	'ctype/ctype_tests.c',
	'ctype/isalnum.c',
	'ctype/isalpha.c',
	'ctype/isascii.c',
	'ctype/isblank.c',
	'ctype/iscntrl.c',
	'ctype/isdigit.c',
	'ctype/isgraph.c',
	'ctype/islower.c',
	'ctype/isprint.c',
	'ctype/ispunct.c',
	'ctype/isspace.c',
	'ctype/isupper.c',
	'ctype/isxdigit.c',
	'ctype/toascii.c',
	'ctype/tolower.c',
	'ctype/toupper.c',
	'stdlib/abs.c',
	'stdlib/atof.c',
	'stdlib/atoi.c',
	'stdlib/atol.c',
	'stdlib/atoll.c',
	'stdlib/bsearch.c',
	'stdlib/calloc.c',
	'stdlib/div.c',
	'stdlib/heapsort.c',
	'stdlib/imaxabs.c',
	'stdlib/imaxdiv.c',
	'stdlib/labs.c',
	'stdlib/ldiv.c',
	'stdlib/llabs.c',
	'stdlib/lldiv.c',
	'stdlib/qsort_r.c',
	'stdlib/qsort.c',
	'stdlib/rand.c',
	'stdlib/realloc.c',
	'stdlib/stdlib_tests.c',
	'stdlib/strtod.c',
	'stdlib/strtof.c',
	'stdlib/strtol.c',
	'stdlib/strtoll.c',
	'stdlib/strtoul.c',
	'stdlib/strtoull.c',
	'string/memcmp.c',
	'string/memcpy.c',
	'string/memmem.c',
	'string/memmove.c',
	'string/memset.c',
	'string/strcat.c',
	'string/strchr.c',
	'string/strcmp.c',
	'string/strcpy.c',
	'string/strdup.c',
	'string/string_tests.c',
	'string/strlen.c',
	'string/strncat.c',
	'string/strncmp.c',
	'string/strncpy.c',
	'string/strndup.c',
	'string/strnlen.c',
	'string/strnstr.c',
	'string/strrchr.c',
	'string/strstr.c',
	'string/strtok.c',
	'test/rand.c'
)

clangtidy_files += libc_test_files

#######################
# Test Compiler Flags #
#######################

libc_test_flags = native_c_compiler.get_supported_arguments(
	'-Wno-unused-parameter',
	# We intentionally run the following scenarios in our tests
	'-Wno-stringop-truncation',
	'-Wno-stringop-overflow',
)

if disable_builtins == false
	libc_test_flags += '-DBUILTINS_ARE_ENABLED'
else
	warning('libc tests will not pass with builtins disabled - calloc() will hang infinitely.')
endif

#################################
# Enable CRT Testing if on OS X #
#################################

if build_machine.system() == 'darwin'
	crt_test_dep = declare_dependency(
		sources: crt_files_for_test,
		compile_args: '-DENABLE_CRT_TESTING'
	)
else
	crt_test_dep = []
endif

###############
# Test Target #
###############

libc_tests = executable('libc_test',
	libc_test_files,
	dependencies: [
		cmocka_native_dep,
		libc_hosted_native_dep,
		crt_test_dep,
	],
	link_args: [
		native_map_file.format(meson.current_build_dir() + '/libc_test'),
	],
	c_args: libc_test_flags,
	native: true,
	build_by_default: meson.is_subproject() == false,
)

stackprotect_test = executable('stackprotect_test',
	['app/stackcheck_main.c', stack_protection_file],
	c_args: ['-fstack-protector-all', libc_native_stack_protect_flags],
	link_args: native_map_file.format(meson.current_build_dir() + '/stackprotect_test'),
	dependencies: libc_hosted_native_dep,
	native: true,
	build_by_default: meson.is_subproject() == false
)

################################
# Cross Compilation "Test" App #
################################
# This application is used to confirm linking behavior, primarily for cross builds

if meson.is_cross_build() and meson.is_subproject() == false

	host_objcopy = find_program(meson.get_cross_property('objcopy'),
		required: false, disabler: true)

	if host_objcopy.found() == false
		message('Specified objcopy not found, .hex and .bin conversion is disabled.')
	endif

	sample_app = executable('sample_app',
		'app/main.c',
		dependencies: libc_dep,
		c_args: '-fstack-protector-all',
		link_args: [
			linker_script_flags,
			map_file.format(meson.current_build_dir()+'/sample_app'),
		],
		link_depends: linker_script_deps,
		native: false
	)

	sample_app_hex = custom_target('sample_app.hex',
		input: sample_app,
		output: 'sample_app.hex',
		command: [host_objcopy, '-O', 'ihex', '@INPUT@', '@OUTPUT@'],
		build_by_default: true
	)

	sample_app_bin = custom_target('sample_app.bin',
		input: sample_app,
		output: 'sample_app.bin',
		command: [host_objcopy, '-O', 'binary', '@INPUT@', '@OUTPUT@'],
		build_by_default: true
	)
endif

#############################
# Register Tests with Meson #
#############################

test_output_dir = 'CMOCKA_XML_FILE=' + meson.build_root() + '/test/%g.xml'

if meson.is_subproject() == false
	test('libc_tests',
		libc_tests,
		env: [test_output_dir])

	test('stackprotect_test',
		stackprotect_test,
		should_fail: true
	)

	run_target('libc-tests',
		command: [libc_tests]
	)

	run_target('libc-tests-xml',
		command: [
			meson.source_root() + '/tools/exec_program_with_env.sh',
			libc_tests,
			test_output_dir
		],
	)
endif
