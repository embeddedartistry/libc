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
	meson_version: '>=0.58.0',
	version: '1.0'
)

################################
# Project Options and Settings #
################################\

# Options that are processed elsewhere
disable_unimplemented_apis = get_option('hide-unimplemented-libc-apis')
disable_builtins = get_option('disable-builtins')
disable_stack_protection = get_option('disable-stack-protection')
enable_gnu_src = get_option('enable-gnu-extensions')
stack_canary = get_option('stack-canary-value')
disable_stk_guard_runtime_config = get_option('disable-stk-guard-runtime-config')
enable_testing = get_option('enable-testing')

# Pick up our common compiler variables + desired_*_flags variables
subdir('meson/compiler')
subdir('meson/compiler/c')
subdir('meson/compiler/cpp')

# Add project-wide flags

desired_common_compile_flags += [
	'-Wno-nonnull',
	'-Wno-nonnull-compare'
]

if get_option('debug')
	add_project_arguments('-DDEBUG',
		language: ['c', 'cpp'])
	add_project_arguments('-DDEBUG',
		language: ['c', 'cpp'], native: true)
endif

if get_option('enable-pedantic')
	desired_common_compile_flags += '-pedantic'
else
	desired_common_compile_flags += '-Wno-pedantic'
endif

if get_option('enable-pedantic-error')
	desired_common_compile_flags += '-pedantic-error'
endif

compile_settings_list = [
	{'lang': 'c', 'compiler': host_c_compiler, 'flags': desired_c_compile_flags, 'isnative': false},
	{'lang': 'c', 'compiler': native_c_compiler, 'flags': desired_native_c_compile_flags, 'isnative': true},
]

link_settings_list = [
	{'lang': 'c', 'compiler': host_c_compiler, 'flags': [], 'isnative': false},
	{'lang': 'c', 'compiler': native_c_compiler, 'flags': [], 'isnative': true},
]

# Process the compilation flags
subdir('meson/compiler/check-and-apply-flags')

#################
# Build Modules #
#################

# Include reusable build modules here via subdir() calls
subdir('meson/linker/linker-script-as-property')
subdir('meson/linker/linker-map')

if enable_testing
	subdir('meson/test/cmocka')
	subdir('meson/objcopy')
endif

##########################
# Architecture Detection #
##########################

subdir('arch')

#############################
# Printf Dependency Targets #
#############################

libprintf_includes = [
	include_directories('printf/src/printf', is_system: true),
	include_directories('printf/src/', is_system: true)
]

printf_dep = declare_dependency(
	include_directories: libprintf_includes,
	sources: files('printf/src/printf/printf.c'),
	compile_args: [
		'-DPRINTF_ALIAS_STANDARD_FUNCTION_NAMES_HARD',
		'-DPRINTF_INCLUDE_CONFIG_H=0'
	]
)

printf_include_dep = declare_dependency(
	include_directories: libprintf_includes,
	compile_args: ['-DPRINTF_ALIAS_STANDARD_FUNCTION_NAMES_HARD']
)

if enable_testing
	printf_tests = executable('printf_tests',
		sources: files('printf/test/test_suite.cpp'),
		include_directories: [
			include_directories('printf/test'),
			include_directories('printf/src', is_system: true)
		],
		native: true,
		build_by_default: meson.is_subproject() == false,
	)

	if meson.is_subproject() == false
		test('printf_tests',
			printf_tests,
			args: ['-s', '-r', 'junit', '-o', meson.project_build_root() + '/test/printf_tests.xml']
		)
	endif

	run_target('printf-tests',
		command: printf_tests
	)

	run_target('printf-tests-xml',
		command: [printf_tests, '-s', '-r', 'junit', '-o', meson.project_build_root() + '/test/printf_tests.xml']
	)
endif

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

#######################
# Process Source Tree #
#######################

# Add files to this variable if you want them analyzed by clang-tidy
clangtidy_files = []

subdir('src')

if enable_testing
	subdir('test')
endif

###################
# Tooling Modules #
###################

# Module Customization options #
doxygen_description = 'C Standard Library Support for Bare-metal Systems'

doxygen_input_additional = [
	meson.project_source_root() / 'arch',
	meson.project_source_root() / 'include',
]

lizard_paths = [
	meson.project_source_root() / 'arch',
	meson.project_source_root() / 'src',
	meson.project_source_root() / 'test'
]

cppcheck_args = [
	'-i', meson.project_source_root() / 'include',
	# Folders to analyze
	meson.project_source_root() / 'arch',
	meson.project_source_root() / 'src',
	meson.project_source_root() / 'test',
]

clangformat_excludes = [
	meson.project_source_root() / 'src/gdtoa'
]

clangformat_additional_targets = [
	meson.project_source_root() / 'include',
	meson.project_source_root() / 'arch',
]

subdir('meson/analysis/clang-tidy')
subdir('meson/analysis/complexity')
subdir('meson/analysis/cppcheck')
subdir('meson/format')
subdir('meson/docs/doxygen')

#############
# Packaging #
#############

host_pkg_name = 'embeddedartistry_libc'
native_pkg_name = host_pkg_name + '_native'

# These macros allow you to simplify the declaration of includes for common
# include paths.
build_root_include = meson.project_build_root() + ':@0@'
src_include = meson.project_build_root() / 'src/:@0@'

host_pkg_files = [
	build_root_include.format('docs'),
	src_include.format('libc.a')
]

native_pkg_files = [
	build_root_include.format('docs'),
	src_include.format('libc_native.a')
]

# Invoke the package module
subdir('meson/package')
