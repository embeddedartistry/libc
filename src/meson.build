# libc src/ meson build

# Flags required by gdtoa
gdtoa_compiler_flags = [
	'-DNO_ERRNO',
	'-DIFNAN_CHECK',
	'-DGDTOA_NO_ASSERT',
	'-DNO_FENV_H'
]

assert_files = [
	'assert/assert.c',
]

exit_files = [
	'exit/_Exit.c',
	'exit/abort.c',
	'exit/at_quick_exit.c',
	#'exit/atexit.c',
	#'exit/exit.c',
	'exit/quick_exit.c'
]

ctype_files = [
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
	'ctype/toupper.c'
]

errno_files = [
	'errno/strerror.c',
]

gdtoa_files = [
	'gdtoa/src/dmisc.c',
	'gdtoa/src/dtoa.c',
	'gdtoa/src/g__fmt.c',
	'gdtoa/src/g_ddfmt.c',
	'gdtoa/src/g_dfmt.c',
	'gdtoa/src/g_ffmt.c',
	'gdtoa/src/g_Qfmt.c',
	'gdtoa/src/g_xfmt.c',
	'gdtoa/src/g_xLfmt.c',
	'gdtoa/src/gdtoa.c',
	'gdtoa/src/gethex.c',
	'gdtoa/src/gmisc.c',
	'gdtoa/src/hd_init.c',
	'gdtoa/src/hexnan.c',
	'gdtoa/src/misc.c',
	'gdtoa/src/smisc.c',
	'gdtoa/src/strtod.c',
	'gdtoa/src/strtodg.c',
	'gdtoa/src/strtodI.c',
	# Below is an alternative, we are not using it
	#'gdtoa/src/strtodnrp.c',
	'gdtoa/src/strtof.c',
	'gdtoa/src/strtoId.c',
	'gdtoa/src/strtoIdd.c',
	'gdtoa/src/strtoIf.c',
	'gdtoa/src/strtoIg.c',
	'gdtoa/src/strtoIQ.c',
	'gdtoa/src/strtoIx.c',
	'gdtoa/src/strtoIxL.c',
	'gdtoa/src/strtopd.c',
	'gdtoa/src/strtopdd.c',
	'gdtoa/src/strtopf.c',
	'gdtoa/src/strtopQ.c',
	'gdtoa/src/strtopx.c',
	'gdtoa/src/strtopxL.c',
	'gdtoa/src/strtord.c',
	'gdtoa/src/strtordd.c',
	'gdtoa/src/strtorf.c',
	'gdtoa/src/strtorQ.c',
	'gdtoa/src/strtorx.c',
	'gdtoa/src/strtorxL.c',
	'gdtoa/src/sum.c',
	'gdtoa/src/ulp.c'
]

math_files = [
	'math/fabs.c',
	'math/fabsf.c',
]

stdlib_files = [
	'stdlib/abs.c',
	'stdlib/atof.c',
	'stdlib/atoi.c',
	'stdlib/atol.c',
	'stdlib/atoll.c',
	'stdlib/bsearch.c',
	'stdlib/calloc.c',
	'stdlib/div.c',
	'stdlib/heapsort_r.c',
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
	'stdlib/strtol.c',
	'stdlib/strtold.c',
	'stdlib/strtoul.c',
	'stdlib/strtoll.c',
	'stdlib/strtoull.c',
]

stdio_files = [
	'stdio/putchar.c',
	'stdio/puts.c'
]

string_files = [
	'string/memcmp.c',
	'string/memcpy.c',
	'string/memmem.c',
	'string/memmove.c',
	'string/memrchr.c',
	'string/memset.c',
	'string/strcat.c',
	'string/strchr.c',
	'string/strchrnul.c',
	'string/strcmp.c',
	'string/strcoll.c',
	'string/strcpy.c',
	'string/strcspn.c',
	'string/strdup.c',
	'string/strlen.c',
	'string/strncat.c',
	'string/strncmp.c',
	'string/strncpy.c',
	'string/strndup.c',
	'string/strnlen.c',
	'string/strnstr.c',
	'string/strpbrk.c',
	'string/strrchr.c',
	'string/strspn.c',
	'string/strstr.c',
	'string/strtok.c',
	'string/strxfrm.c'
]

support_files = [
	'support/fls.c',
	'support/flsl.c',
	'support/flsll.c'
]

wchar_files = [
	'wchar/iswalnum.c',
	'wchar/iswalpha.c',
	'wchar/iswblank.c',
	'wchar/iswcntrl.c',
	'wchar/iswalnum.c',
	'wchar/iswalpha.c',
	'wchar/iswblank.c',
	'wchar/iswcntrl.c',
	'wchar/iswctype.c',
	'wchar/iswdigit.c',
	'wchar/iswgraph.c',
	'wchar/iswlower.c',
	'wchar/iswprint.c',
	'wchar/iswpunct.c',
	'wchar/iswspace.c',
	'wchar/iswupper.c',
	'wchar/iswxdigit.c',
	'wchar/towccase.c',
	'wchar/towctrans.c',
	'wchar/towlower.c',
	'wchar/towupper.c',
	'wchar/wcswidth.c',
	'wchar/wctrans.c',
	'wchar/wctype.c',
	'wchar/wcwidth.c',
]

libc_native_files = [
	files('stdio/putchar_native.c')
]

libc_common_files = [
	assert_files,
	ctype_files,
	gdtoa_files,
	errno_files,
	math_files,
	stdlib_files,
	string_files,
	support_files,
	wchar_files,
	printf_files,
]

libc_standalone_files = [exit_files, stdio_files]

libc_lint_files = files(
	assert_files,
	ctype_files,
	gdtoa_files,
	errno_files,
	math_files,
	stdlib_files,
	string_files,
	support_files,
	wchar_files,
	exit_files,
	stdio_files,
)

##
# For local builds, we use libc_includes to generate our own warnings
# For dependencies, we use libc_system_includes to add -isystem
##

libc = static_library(
	'c',
	libc_standalone_files + libc_common_files,
	c_args: [stdlib_compiler_flags, gdtoa_compiler_flags],
	include_directories: [libc_includes, libc_system_includes, arch_include]
)

# We don't build the stdio files for the native variant, as we rely on the
# System library to do the heavy lifting for missing symbols
libc_native = static_library(
		'c_native',
		[libc_common_files + libc_native_files],
		c_args: [stdlib_compiler_flags, gdtoa_compiler_flags],
		include_directories: [libc_includes, libc_system_includes, arch_include],
		native: true
)

libc_dep = declare_dependency(
	link_with: libc,
	include_directories: [libc_system_includes, arch_include],
	compile_args: stdlib_compiler_flags,
)

libc_native_dep = declare_dependency(
	link_with: libc_native,
	include_directories: [libc_system_includes, arch_include],
	compile_args: stdlib_compiler_flags,
)

libc_header_include = [libc_system_includes, arch_include]
