#############################################################
# Module: Automatically Register Linker Script Dependencies #
#############################################################
# Redefine add_executable so that we specify a link-time dependency on the linker script
# The `LINKER_SCRIPT_DEPENDENCIES` variable should be defined in a toolchain
# file. It can contain a CMake list of all linker script dependencies.

function(add_executable target)
	# Forward all arguments to the CMake add_executable
	_add_executable(${target} ${ARGN})
	if(LINKER_SCRIPT_DEPENDENCIES)
		set_target_properties(${target} PROPERTIES
			LINK_DEPENDS "${LINKER_SCRIPT_DEPENDENCIES}")
	endif()
endfunction()
