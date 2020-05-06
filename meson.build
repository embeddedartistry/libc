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

# Options that are processed elsewhere
disable_unimplemented_apis = get_option('hide-unimplemented-libc-apis')
disable_builtins = get_option('disable-builtins')
disable_stack_protection = get_option('disable-stack-protection')
enable_gnu_src = get_option('enable-gnu-extensions')

# Pick up our common compiler variables + desired_*_flags variables
subdir('build/compiler')
subdir('build/compiler/c')
subdir('build/compiler/cpp')

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
subdir('build/compiler/check-and-apply-flags')

#################
# Build Modules #
#################

# Include reusable build modules here via subdir() calls
subdir('build/linker/linker-script-as-property')
subdir('build/linker/linker-map')
subdir('build/test/cmocka')
subdir('build/objcopy')

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

#######################
# Process Source Tree #
#######################

# Add files to this variable if you want them analyzed by clang-tidy
clangtidy_files = []

subdir('src')
subdir('test')

###################
# Tooling Modules #
###################

# Customization options
doxygen_description = 'C Standard Library Support for Bare-metal Systems'
lizard_paths = [
	meson.source_root() / 'arch',
	meson.source_root() / 'src',
	meson.source_root() / 'test'
]
cppcheck_args = [
	'-i', meson.source_root() / 'include',
	# Folders to analyze
	meson.source_root() / 'arch',
	meson.source_root() / 'src',
	meson.source_root() / 'test',
]
clangformat_args = [
	# Optional exclude directories (separated by commas)
	# '-e', 'src/external',
	# Directories to format files in
	meson.source_root() / 'src,' + meson.source_root() / 'test,' +
	meson.source_root() / 'include,' + meson.source_root() / 'arch',
	# File types to include in formatting (separated by commas)
	'*.c,*.h,*.cpp,*.hpp',
]

# Include modules
subdir('build/analysis/clang-tidy')
subdir('build/analysis/complexity')
subdir('build/analysis/cppcheck')
subdir('build/format')
subdir('build/docs/doxygen')

#############
# Packaging #
#############

# These macros allow you to simplify the declaration of includes for common
# include paths.
build_root_include = meson.build_root() + ':@0@'
src_include = meson.build_root() / 'src/:@0@'

host_pkg_files = [
	build_root_include.format('doc'),
	src_include.format('libc.a')
]

native_pkg_files = [
	build_root_include.format('doc'),
	src_include.format('libc_native.a')
]

# Invoke the package module
subdir('build/package')
