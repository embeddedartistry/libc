##################################################
# Standard Clang Toolchain On OSX (via Homebrew) #
##################################################
# This file is for using Mainline Clang on OS X
# This is expected to be installed by Homebrew.

set(CMAKE_C_COMPILER    /usr/local/opt/llvm/bin/clang)
set(CMAKE_CXX_COMPILER  /usr/local/opt/llvm/bin/clang++)
set(CMAKE_AR            /usr/local/opt/llvm/bin/llvm-ar)

if((${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin") AND (${CMAKE_HOST_SYSTEM_VERSION} VERSION_LESS "19"))
	# Resolve `-platform-version` error with macOS versions < Catalina and latest Clang
	set(CMAKE_EXE_LINKER_FLAGS_INIT
		"-mlinker-version=450"
		CACHE
		INTERNAL "Default linker flags.")
endif()

