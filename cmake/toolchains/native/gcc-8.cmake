###################
# GCC-8 Toolchain #
###################

set(CMAKE_C_COMPILER    gcc-8)
set(CMAKE_CXX_COMPILER  g++-8)
if(NOT (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin"))
	# gcc-ar-8 does not successfully find the linker plugin on Darwin
	set(CMAKE_AR        gcc-ar-7)
endif()

