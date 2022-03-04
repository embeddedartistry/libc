#################
# GDTOA Library #
#################

add_library(gdtoa INTERFACE)
target_sources(gdtoa INTERFACE
	gdtoa/src/dmisc.c
	gdtoa/src/dtoa.c
	gdtoa/src/g__fmt.c
	gdtoa/src/g_ddfmt.c
	gdtoa/src/g_dfmt.c
	gdtoa/src/g_ffmt.c
	gdtoa/src/g_Qfmt.c
	gdtoa/src/g_xfmt.c
	gdtoa/src/g_xLfmt.c
	gdtoa/src/gdtoa.c
	gdtoa/src/gethex.c
	gdtoa/src/gmisc.c
	gdtoa/src/hd_init.c
	gdtoa/src/hexnan.c
	gdtoa/src/misc.c
	gdtoa/src/smisc.c
	gdtoa/src/strtod.c
	gdtoa/src/strtodg.c
	gdtoa/src/strtodI.c
	gdtoa/src/strtof.c
	gdtoa/src/strtoId.c
	gdtoa/src/strtoIdd.c
	gdtoa/src/strtoIf.c
	gdtoa/src/strtoIg.c
	gdtoa/src/strtoIQ.c
	gdtoa/src/strtoIx.c
	gdtoa/src/strtoIxL.c
	gdtoa/src/strtopd.c
	gdtoa/src/strtopdd.c
	gdtoa/src/strtopf.c
	gdtoa/src/strtopQ.c
	gdtoa/src/strtopx.c
	gdtoa/src/strtopxL.c
	gdtoa/src/strtord.c
	gdtoa/src/strtordd.c
	gdtoa/src/strtorf.c
	gdtoa/src/strtorQ.c
	gdtoa/src/strtorx.c
	gdtoa/src/strtorxL.c
	gdtoa/src/sum.c
	gdtoa/src/ulp.c
)
target_include_directories(gdtoa INTERFACE gdtoa/include)
target_compile_definitions(gdtoa INTERFACE
	NO_ERRNO
	IFNAN_CHECK
	GDTOA_NO_ASSERT
	NO_FENV_H
)

########
# Libc #
########

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION include)

# libc_core contains shared files and definitions that are used by libc and libc_hosted
add_library(c_core INTERFACE)
target_link_libraries(c_core INTERFACE printf openlibm gdtoa architecture_specific)
target_include_directories(c_core
	INTERFACE
		${PROJECT_SOURCE_DIR}/include
)

# libc is a standalone version of the library
add_library(c)
target_link_libraries(c PRIVATE c_core)
install(TARGETS c DESTINATION lib)

# libc_hosted is designed to be used with an operating system that provides a full implementation
# which can do the heavy lifting for missing pieces
add_library(c_hosted)
target_link_libraries(c_hosted PRIVATE c_core)
install(TARGETS c_hosted DESTINATION lib)

# Apply unconditional private flags here
list(APPEND libc_private_compile_flags
	"-Wno-nonnull-compare"
	"-Wno-unknown-pragmas"
)

# Apply unconditional public flags here
list(APPEND libc_public_compile_flags
	""
)

if(DISABLE_BUILTINS)
	list(APPEND libc_private_compile_flags -fno-builtin)
endif()

if(DISABLE_STACK_PROTECTION)
	list(APPEND libc_public_compile_flags -fno-stack-protector)
endif()

if(NOSTDINC_FOR_DEPENDENTS)
	list(APPEND libc_public_compile_flags -nostdinc)
else()
	list(APPEND libc_private_compile_flags -nostdinc)
endif()

# Apply common settings to C and C_hosted targets
foreach(target c c_hosted)
	target_include_directories(${target}
		INTERFACE
			$<TARGET_PROPERTY:openlibm,INTERFACE_INCLUDE_DIRECTORIES>
		INTERFACE SYSTEM
			${PROJECT_SOURCE_DIR}/include
			${PROJECT_SOURCE_DIR}/arch/${CMAKE_SYSTEM_PROCESSOR}/include
	)

	target_compile_definitions(${target}
		INTERFACE
			$<$<BOOL:${HIDE_UNIMPLEMENTED_C_APIS}>:DISABLE_UNIMPLEMENTED_LIBC_APIS>
		PUBLIC
			$<$<BOOL:${ENABLE_GNU_EXTENSIONS}>:_GNU_SOURCE>
		PRIVATE
			# Define a DEBUG symbol if we're using a Debug or Release with Debug Info buildtype
			$<$<OR:$<STREQUAL:${CMAKE_BUILD_TYPE},Debug>,$<STREQUAL:${CMAKE_BUILD_TYPE},RelWithDebInfo>>:DEBUG>
	)

	apply_supported_compiler_flags(C ${target} PRIVATE libc_private_compile_flags)
	apply_supported_compiler_flags(C ${target} PUBLIC libc_public_compile_flags)
endforeach()

if(NOT ((${CMAKE_C_COMPILER_ID} STREQUAL "Clang") OR (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")))
	check_c_compiler_flag("-nolibc" _nolibc)
endif()

if("${_nolibc}")
	target_link_options(c INTERFACE "-nolibc")
else()
	check_c_compiler_flag("-nostdlib" _nostdlib)
	if(_nostdlib)
		target_link_options(c INTERFACE "-nostdlib")
	endif()
endif()

check_c_compiler_flag("-nostartfiles" _nostartfiles)
if("${_nostartfiles}")
		target_link_options(c INTERFACE "-nostartfiles")
endif()

# Assert Module
target_sources(c_core INTERFACE
	assert/assert.c
)

# CRT Module - Not needed for hosted targets
target_sources(c PRIVATE
	crt/_Exit.c
	crt/abort.c
	crt/at_exit.c
	crt/at_quick_exit.c
	crt/crt.c
	crt/cxa_atexit.c
	crt/exit.c
	crt/quick_exit.c
)

# CType Module
target_sources(c_core INTERFACE
	ctype/isalnum.c
	ctype/isalpha.c
	ctype/isascii.c
	ctype/isblank.c
	ctype/iscntrl.c
	ctype/isdigit.c
	ctype/isgraph.c
	ctype/islower.c
	ctype/isprint.c
	ctype/ispunct.c
	ctype/isspace.c
	ctype/isupper.c
	ctype/isxdigit.c
	ctype/toascii.c
	ctype/tolower.c
	ctype/toupper.c
)

# locale Module
target_sources(c_core INTERFACE
	locale/langinfo.c
)

# math Module
target_sources(c_core INTERFACE
	math/fabs.c
	math/fabsf.c
)

# stdio Module
target_sources(c_core INTERFACE
	stdio/asprintf.c
	stdio/putchar.c
	stdio/puts.c
	stdio/vasprintf.c
)

# stdio Hosted Module
target_sources(c_hosted PRIVATE
	stdio/putchar_native.c
)

# stdlib Module
target_sources(c_core INTERFACE
	stdlib/abs.c
	stdlib/atof.c
	stdlib/atoi.c
	stdlib/atol.c
	stdlib/atoll.c
	stdlib/bsearch.c
	stdlib/calloc.c
	stdlib/div.c
	stdlib/heapsort_r.c
	stdlib/heapsort.c
	stdlib/imaxabs.c
	stdlib/imaxdiv.c
	stdlib/labs.c
	stdlib/ldiv.c
	stdlib/llabs.c
	stdlib/lldiv.c
	stdlib/qsort_r.c
	stdlib/qsort.c
	stdlib/rand.c
	stdlib/realloc.c
	stdlib/strtol.c
	stdlib/strtold.c
	stdlib/strtoul.c
	stdlib/strtoll.c
	stdlib/strtoull.c
)

# string Module
target_sources(c_core INTERFACE
	string/memcmp.c
	string/memcpy.c
	string/memmem.c
	string/memmove.c
	string/memchr.c
	string/memrchr.c
	string/memset.c
	string/strcat.c
	string/strchr.c
	string/strchrnul.c
	string/strcmp.c
	string/strcoll.c
	string/strcpy.c
	string/strcspn.c
	string/strdup.c
	string/strerror.c
	string/strerror_r.c
	string/strlen.c
	string/strncat.c
	string/strncmp.c
	string/strncpy.c
	string/strndup.c
	string/strnlen.c
	string/strnstr.c
	string/strpbrk.c
	string/strrchr.c
	string/strspn.c
	string/strstr.c
	string/strtok.c
	string/strxfrm.c
)

# support Module
target_sources(c_core INTERFACE
	support/fls.c
	support/flsl.c
	support/flsll.c
)

# time Module
target_sources(c_core INTERFACE
	time/asctime.c
	time/asctime_r.c
)

# wchar Module
target_sources(c_core INTERFACE
	wchar/iswalnum.c
	wchar/iswalpha.c
	wchar/iswblank.c
	wchar/iswcntrl.c
	wchar/iswalnum.c
	wchar/iswalpha.c
	wchar/iswblank.c
	wchar/iswcntrl.c
	wchar/iswctype.c
	wchar/iswdigit.c
	wchar/iswgraph.c
	wchar/iswlower.c
	wchar/iswprint.c
	wchar/iswpunct.c
	wchar/iswspace.c
	wchar/iswupper.c
	wchar/iswxdigit.c
	wchar/towccase.c
	wchar/towctrans.c
	wchar/towlower.c
	wchar/towupper.c
	wchar/wcswidth.c
	wchar/wctrans.c
	wchar/wctype.c
	wchar/wcwidth.c
)
