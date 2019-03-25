project('libc',
	['c', 'cpp'],
	default_options : ['c_std=c11','cpp_std=c++17'])

########################
# Identify Compiler(s) #
########################

# Identify compilers & get flags
subdir('build/compiler')

native_compiler = meson.get_compiler('c', native: true)
host_compiler = meson.get_compiler('c')

libc_native_compile_args = []
libc_host_compile_args = []

if native_compiler.has_argument('-Wno-reserved-id-macro')
	# We are the standard library, don't complain about __ prefixes
	libc_native_compile_args += '-Wno-reserved-id-macro'
endif

if host_compiler.has_argument('-Wno-reserved-id-macro')
	# We are the standard library, don't complain about __ prefixes
	libc_host_compile_args += '-Wno-reserved-id-macro'
endif

subdir('build/ea-stdlib')

#######################
# Include Directories #
#######################

libc_includes = include_directories('include', 'src/gdtoa/include')
libc_system_includes = include_directories(
	'include',
	'openlibm/include',
	'openlibm/src',
	'src/gdtoa/include',
	'printf',
	is_system: true)

##########################
# Determine Architecture #
##########################

subdir('build/architecture')

target_arch_include = []
native_arch_include = []
target_arch_deps = []
native_arch_deps = []

subdir('arch/' + target_architecture)

if target_architecture != native_architecture
	subdir('arch/' + native_architecture)
endif

#########################
# Process Build Options #
#########################

if get_option('enable-werror') == true
	add_project_arguments('-Werror', language : ['c', 'cpp'])
endif

if get_option('enable-pedantic-error') == true
	add_project_arguments('-pedantic-error', language : ['c', 'cpp'])
endif

############################
# Process external modules #
############################

printf_files = files('printf/printf.c')

libc_printf_dep = declare_dependency(
	include_directories: include_directories('printf', is_system: true),
	sources: printf_files,
)

printf_tests = executable('printf_test',
	['printf/test/test_suite.cpp'],
	cpp_args: ['-Wno-format', '-Wno-format-invalid-specifier', '-Wno-old-style-cast', '-Wno-missing-prototypes'],
	include_directories: [include_directories('printf/test')],
	native: true
)

test('printf_tests',
	printf_tests,
	args: ['-s', '-r', 'junit', '-o', meson.build_root() + '/test/printf_tests.xml'])

run_target('printf-tests',
	command: [printf_tests])

run_target('printf-tests-xml',
	command: [printf_tests, '-s', '-r', 'junit', '-o', meson.build_root() + '/test/printf_tests.xml'])

#######################
# Process source tree #
#######################

# Library build definition
subdir('src/')

# Test build definition
subdir('test/')

############################
# Supporting Build Targets #
############################

run_target('docs',
	command: ['doxygen', 'docs/Doxyfile'])

run_target('complexity',
	command: ['tools/complexity_check.sh', '-w'])

run_target('complexity-list',
	command: ['tools/complexity_check.sh'])

cppcheck = find_program('cppcheck', required: false)

if cppcheck.found()
	run_target('cppcheck',
		command: ['cppcheck',
		# Options
		'--quiet', '--enable=style', '--force',
		# Include Directories
		'-I', meson.current_source_dir() + '/include',
		# Source Directories
		'src']
	)

	run_target('cppcheck-xml',
		command: ['tools/cppcheck_xml.sh']
	)
endif

clangtidy = find_program('clang-tidy', required: false)

if clangtidy.found()
    run_target(
        'tidy',
        command: [
            'build/tooling/clang-tidy/clang-tidy.sh',
            # Checks
            '-*,cppcoreguidelines-*,modernize-*,performance-*,portability-*,readability-*,' +
            '-readability-inconsistent-declaration-parameter-name,' +
            # Header Filter
            '.*',
            #Finish with files
        ] + libc_lint_files)
endif
