project('Framework',
	'c',
	default_options : ['cpp_std=c11'])

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
arch_lib_path = '../arch/' + architecture + '/lib'

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
add_global_arguments([compiler_args, '-Wno-reserved-id-macro'], language: 'c')

subdir('build/ea-stdlib')

#########################
# Process Build Options #
#########################

if get_option('enable-werror') == true
	add_global_arguments('-Werror', language : 'c')
endif

if get_option('enable-pedantic-error') == true
	add_global_arguments('-pedantic-error', language : 'c')
endif

#######################
# Process source tree #
#######################

libc_includes = include_directories('include', 'src/gdtoa/include')

# Flags required by gdtoa
gdtoa_compiler_flags = [
	'-DNO_ERRNO',
	'-DIFNAN_CHECK',
	'-DGDTOA_NO_ASSERT',
	'-DNO_FENV_H'
]

ctype_files = [
	'src/ctype/isalnum.c',
	'src/ctype/isalpha.c',
	'src/ctype/isascii.c',
	'src/ctype/isblank.c',
	'src/ctype/iscntrl.c',
	'src/ctype/isdigit.c',
	'src/ctype/isgraph.c',
	'src/ctype/islower.c',
	'src/ctype/isprint.c',
	'src/ctype/ispunct.c',
	'src/ctype/isspace.c',
	'src/ctype/isupper.c',
	'src/ctype/isxdigit.c',
	'src/ctype/toascii.c',
	'src/ctype/tolower.c',
	'src/ctype/toupper.c'
]

gdtoa_files = [
	'src/gdtoa/src/dmisc.c',
	'src/gdtoa/src/dtoa.c',
	'src/gdtoa/src/g__fmt.c',
	'src/gdtoa/src/g_ddfmt.c',
	'src/gdtoa/src/g_dfmt.c',
	'src/gdtoa/src/g_ffmt.c',
	'src/gdtoa/src/g_Qfmt.c',
	'src/gdtoa/src/g_xfmt.c',
	'src/gdtoa/src/g_xLfmt.c',
	'src/gdtoa/src/gdtoa.c',
	'src/gdtoa/src/gethex.c',
	'src/gdtoa/src/gmisc.c',
	'src/gdtoa/src/hd_init.c',
	'src/gdtoa/src/hexnan.c',
	'src/gdtoa/src/misc.c',
	'src/gdtoa/src/smisc.c',
	'src/gdtoa/src/strtod.c',
	'src/gdtoa/src/strtodg.c',
	'src/gdtoa/src/strtodI.c',
	'src/gdtoa/src/strtodnrp.c',
	'src/gdtoa/src/strtof.c',
	'src/gdtoa/src/strtoId.c',
	'src/gdtoa/src/strtoIdd.c',
	'src/gdtoa/src/strtoIf.c',
	'src/gdtoa/src/strtoIg.c',
	'src/gdtoa/src/strtoIQ.c',
	'src/gdtoa/src/strtoIx.c',
	'src/gdtoa/src/strtoIxL.c',
	'src/gdtoa/src/strtopd.c',
	'src/gdtoa/src/strtopdd.c',
	'src/gdtoa/src/strtopf.c',
	'src/gdtoa/src/strtopQ.c',
	'src/gdtoa/src/strtopx.c',
	'src/gdtoa/src/strtopxL.c',
	'src/gdtoa/src/strtord.c',
	'src/gdtoa/src/strtordd.c',
	'src/gdtoa/src/strtorf.c',
	'src/gdtoa/src/strtorQ.c',
	'src/gdtoa/src/strtorx.c',
	'src/gdtoa/src/strtorxL.c',
	'src/gdtoa/src/sum.c',
	'src/gdtoa/src/ulp.c'
]

stdlib_files = [
	'src/stdlib/abs.c',
	'src/stdlib/atof.c',
	'src/stdlib/atoi.c',
	'src/stdlib/atol.c',
	'src/stdlib/atoll.c',
	'src/stdlib/bsearch.c',
	'src/stdlib/calloc.c',
	'src/stdlib/div.c',
	'src/stdlib/heapsort_r.c',
	'src/stdlib/heapsort.c',
	'src/stdlib/imaxabs.c',
	'src/stdlib/imaxdiv.c',
	'src/stdlib/labs.c',
	'src/stdlib/ldiv.c',
	'src/stdlib/llabs.c',
	'src/stdlib/lldiv.c',
	'src/stdlib/qsort_r.c',
	'src/stdlib/qsort.c',
	'src/stdlib/rand.c',
	'src/stdlib/realloc.c',
	'src/stdlib/strtol.c',
	'src/stdlib/strtoll.c',
	'src/stdlib/strtoull.c',
]

string_files = [
	'src/string/memcmp.c',
	'src/string/memcpy.c',
	'src/string/memmem.c',
	'src/string/memmove.c',
	'src/string/memrchr.c',
	'src/string/memset.c',
	'src/string/strcat.c',
	'src/string/strchr.c',
	'src/string/strchrnul.c',
	'src/string/strcmp.c',
	'src/string/strcpy.c',
	'src/string/strdup.c',
	'src/string/strlen.c',
	'src/string/strncat.c',
	'src/string/strncmp.c',
	'src/string/strncpy.c',
	'src/string/strndup.c',
	'src/string/strnlen.c',
	'src/string/strnstr.c',
	'src/string/strrchr.c',
	'src/string/strstr.c',
	'src/string/strtok.c'
]

support_files = [
	'src/support/fls.c',
	'src/support/flsl.c',
	'src/support/flsll.c'
]

libc_test_files = [
	'test/main.c',
	'test/ctype/ctype_tests.c',
	'test/ctype/isalnum.c',
	'test/ctype/isalpha.c',
	'test/ctype/isascii.c',
	'test/ctype/isblank.c',
	'test/ctype/iscntrl.c',
	'test/ctype/isdigit.c',
	'test/ctype/isgraph.c',
	'test/ctype/islower.c',
	'test/ctype/isprint.c',
	'test/ctype/ispunct.c',
	'test/ctype/isspace.c',
	'test/ctype/isupper.c',
	'test/ctype/isxdigit.c',
	'test/ctype/toascii.c',
	'test/ctype/tolower.c',
	'test/ctype/toupper.c',
	'test/stdlib/abs.c',
	'test/stdlib/atof.c',
	'test/stdlib/atoi.c',
	'test/stdlib/atol.c',
	'test/stdlib/atoll.c',
	'test/stdlib/bsearch.c',
	'test/stdlib/calloc.c',
	'test/stdlib/div.c',
	'test/stdlib/heapsort_r.c',
	'test/stdlib/heapsort.c',
	'test/stdlib/imaxabs.c',
	'test/stdlib/imaxdiv.c',
	'test/stdlib/labs.c',
	'test/stdlib/ldiv.c',
	'test/stdlib/llabs.c',
	'test/stdlib/lldiv.c',
	'test/stdlib/qsort_r.c',
	'test/stdlib/qsort.c',
	'test/stdlib/rand.c',
	'test/stdlib/realloc.c',
	'test/stdlib/stdlib_tests.c',
	'test/stdlib/strtod.c',
	'test/stdlib/strtof.c',
	'test/stdlib/strtol.c',
	'test/stdlib/strtoll.c',
	'test/stdlib/strtoul.c',
	'test/stdlib/strtoull.c',
	'test/string/memcmp.c',
	'test/string/memcpy.c',
	'test/string/memmem.c',
	'test/string/memmove.c',
	'test/string/memset.c',
	'test/string/strcat.c',
	'test/string/strchr.c',
	'test/string/strcmp.c',
	'test/string/strcpy.c',
	'test/string/strdup.c',
	'test/string/string_tests.c',
	'test/string/strlen.c',
	'test/string/strncat.c',
	'test/string/strncmp.c',
	'test/string/strncpy.c',
	'test/string/strndup.c',
	'test/string/strnlen.c',
	'test/string/strnstr.c',
	'test/string/strrchr.c',
	'test/string/strstr.c',
	'test/string/strtok.c',
	'test/test/rand.c'
]

libc = static_library(
	'c',
	[ctype_files, gdtoa_files, stdlib_files, string_files, support_files],
	c_args: [stdlib_compiler_flags, gdtoa_compiler_flags],
	include_directories: [libc_includes, arch_include]
)

cmocka_include = include_directories('test/')

libc_tests = executable('libc_test',
	libc_test_files,
	c_args: [stdlib_compiler_flags, '-Wno-vla', '-Wno-unused-parameter'],
	link_args: [stdlib_link_flags, '-L' + arch_lib_path, '-lcmocka', '-lm'],
	include_directories: [libc_includes, arch_include, cmocka_include],
	link_with: libc
)
