project('libc',
	['c', 'cpp'],
	default_options : ['c_std=c11','cpp_std=c++17'])

########################
# Identify Compiler(s) #
########################

native_compiler_id = meson.get_compiler('c', native : true).get_id()

if meson.is_cross_build()
	host_compiler_id = meson.get_compiler('c', native : false).get_id()
endif

##########################
# Determine Architecture #
##########################

subdir('build/architecture')
arch_include = include_directories('arch/' + architecture + '/include')

######################################
# Import compiler flags and warnings #
######################################

# Get compiler flags, and handle host vs cross builds
if meson.is_cross_build()
	if host_compiler_id == 'clang'
		subdir('build/compiler/clang')
	elif host_compiler_id == 'gcc'
		subdir('build/compiler/gcc')
	endif
else
	if native_compiler_id == 'clang'
		subdir('build/compiler/clang')
	elif native_compiler_id == 'gcc'
		subdir('build/compiler/gcc')
	endif
endif

# compiler_args is defined in build/compiler/<target>/meson.build
# We are the standard library, don't complain about __
add_project_arguments([compiler_args, '-Wno-reserved-id-macro'], language: ['c', 'cpp'])

subdir('build/ea-stdlib')

#########################
# Process Build Options #
#########################

if get_option('enable-werror') == true
	add_project_arguments('-Werror', language : ['c', 'cpp'])
endif

if get_option('enable-pedantic-error') == true
	add_project_arguments('-pedantic-error', language : ['c', 'cpp'])
endif

#######################
# Process source tree #
#######################

libc_includes = include_directories('include', 'src/gdtoa/include')
libc_system_includes = include_directories('include', 'src/gdtoa/include', is_system: true)

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
