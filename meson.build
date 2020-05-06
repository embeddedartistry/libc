project('Embedded Artistry libc',
	['c', 'cpp'],
	default_options : [
		'warning_level=3',
		'werror=false',
		# This project defaults to a release build
		'debug=false',
		'optimization=2',
		# `build.*` options affect `native: true targets`
		# plain options affect `native: false` targets.
		'c_std=c11', 'build.c_std=c11',
		'cpp_std=c++11', 'build.cpp_std=c++11',
	],
	license: 'MIT',
	meson_version: '>=0.54.0',
	version: '1.0'
)

################################
# Project Options and Settings #
################################

native_c_compiler = meson.get_compiler('c', native: true)
host_c_compiler = meson.get_compiler('c', native: false)
native_c_compiler_id = native_c_compiler.get_id()
host_c_compiler_id = host_c_compiler.get_id()

disable_unimplemented_apis = get_option('hide-unimplemented-libc-apis')
disable_builtins = get_option('disable-builtins')
disable_stack_protection = get_option('disable-stack-protection')
enable_gnu_src = get_option('enable-gnu-extensions')
debug = get_option('debug')

if debug
	debug_flags = ['-DDEBUG']
	add_project_arguments(debug_flags, language: ['c', 'cpp'])
	add_project_arguments(debug_flags, language: ['c', 'cpp'], native: true)
endif

project_arguments = [
	'-Wno-unknown-pragmas',
	'-Wno-nonnull',
	'-Wno-nonnull-compare'
]

add_project_arguments(
	host_c_compiler.get_supported_arguments(project_arguments),
	language: 'c'
)

add_project_arguments(
	native_c_compiler.get_supported_arguments(project_arguments),
	language: 'c',
	native: true
)

###############################################################
# Generate Linker Arguments and Dependencies for Linker Files #
###############################################################

linker_script_flags = []
linker_script_deps = []

foreach entry : meson.get_cross_property('linker_paths', [''])
	if entry != ''
		linker_script_flags += '-L' + meson.source_root() / entry
	endif
endforeach

foreach entry : meson.get_cross_property('linker_scripts', [''])
	if entry != ''
		linker_script_flags += '-T' + entry
	endif
endforeach

foreach entry : meson.get_cross_property('link_depends', [''])
	if entry != ''
		linker_script_deps += meson.source_root() / entry
	endif
endforeach

###################
# Build Templates #
###################

# This format string template can be used to declare a map file
# with an executable when using GCC, Clang, or MSVC
# Use it like:
#	link_args: host_map_file.format(meson.current_build_dir() + '/libc_test')

if native_c_compiler.has_link_argument('-Wl,-map,test.map')
	native_map_file = '-Wl,-map,@0@.map'
elif native_c_compiler.has_link_argument('-Wl,-Map,test.map')
	native_map_file = '-Wl,-Map,@0@.map'
else
	warning('Native toolchain does not support Map file generation')
	native_map_file = []
endif


if host_c_compiler.has_link_argument('-Wl,-Map,test.map')
	host_map_file = '-Wl,-Map,@0@.map'
elif host_c_compiler.has_link_argument('-Wl,-map,test.map')
	host_map_file = '-Wl,-map,@0@.map'
elif host_c_compiler.has_multi_link_arguments('--specs=nosys.specs', '-Wl,-Map,test.map')
	# arm-gcc will fail the check without --specs=nosys.specs
	host_map_file = '-Wl,-Map,@0@.map'
else
	warning('Host toolchain does not support Map file generation')
	host_map_file = []
endif


# The map_file variable is a simplified alias to host_map_file
map_file = host_map_file

##########################
# Architecture Detection #
##########################

subdir('arch')

#############################
# Printf Dependency Targets #
#############################

libprintf_files = files('printf/printf.c')
libprintf_includes = include_directories('printf', is_system: true)

printf_dep = declare_dependency(
	include_directories: libprintf_includes,
	sources: libprintf_files,
)

printf_tests = executable('printf_tests',
	sources: files('printf/test/test_suite.cpp'),
	include_directories: include_directories('printf/test'),
	native: true
)

test('printf_tests',
	printf_tests,
	args: ['-s', '-r', 'junit', '-o', meson.build_root() + '/test/printf_tests.xml']
)

run_target('printf-tests',
	command: printf_tests
)

run_target('printf-tests-xml',
	command: [printf_tests, '-s', '-r', 'junit', '-o', meson.build_root() + '/test/printf_tests.xml']
)

###############################
# Openlibm Dependency Targets #
###############################

openlibm_includes = include_directories(
	'openlibm/include',
	'openlibm/src',
	is_system: true
)

openlibm_dep = declare_dependency(
	include_directories: openlibm_includes,
)

#####################
# CMocka Dependency #
#####################

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

#######################
# Process Source Tree #
#######################

# Add files to this variable if you want them analyzed by clang-tidy
files_to_lint = []

subdir('src')
subdir('test')

##################
# Custom Targets #
##################

run_target('clear-test-results',
	command: meson.source_root() + '/tools/clear_test_xml.sh'
)

doxygen = find_program('doxygen', required: false, disabler: true)
run_target('docs',
	command: [doxygen, 'docs/Doxyfile'])

clangformat = find_program('clang-format', required: false, disabler: true)
if clangformat.found()
	run_target('format',
		command: 'tools/format.sh')

	run_target('format-patch',
		command: 'tools/format-patch.sh')
endif

cppcheck = find_program('cppcheck', required: false, disabler: true)
if cppcheck.found()
	run_target('cppcheck',
		command: 'tools/cppcheck.sh'
	)

	run_target('cppcheck-xml',
		command: [
			'tools/cppcheck.sh',
			'xml'
		],
	)
endif

clangtidy = find_program('clang-tidy', required: false, disabler: true)
if clangtidy.found()
	run_target('clang-tidy',
		command: [
			'tools/clang-tidy.sh',
			# Files,
			files_to_lint
		],
	)
endif

lizard_default_args = [
	# Exclude these Directories
	'-x', './buildresults/*',
	'-x', './subprojects/*',
	# Configuration
	'--length', '75', # Fail when functions are longer than this
	'--CCN', '10', # Fail over this CCN
	'--arguments', '10', # Fail at this arg count
]

lizard = find_program('lizard', required: false, disabler: true)
run_target('complexity',
	command: [lizard,
		lizard_default_args,
		'-w'
	]
)

run_target('complexity-full',
	command: [lizard,
		lizard_default_args
	]
)

complexity_xml = custom_target('complexity.xml',
	output: 'complexity.xml',
	command: [
		lizard,
		lizard_default_args,
		'--xml'
	],
	capture: true,
	build_always_stale: true,
	build_by_default: false,
)

alias_target('complexity-xml', complexity_xml)

#############
# Packaging #
#############

run_target('package',
	command: [
		'tools/package.sh',
		'-a', host_machine.cpu_family(),
		'-c', host_machine.cpu(),
		'-s', host_machine.system(),
		'-v', meson.project_version()
	]
)

run_target('package-native',
	command: [
		'tools/package.sh',
		'-a', build_machine.cpu_family(),
		'-c', build_machine.cpu(),
		'-s', build_machine.system(),
		'-v', meson.project_version(),
		'-n' # Use Native Files
	]
)

