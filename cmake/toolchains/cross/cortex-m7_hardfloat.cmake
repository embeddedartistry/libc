########################
# Cortex-M7 Hard-float #
########################

# CMake includes the toolchain file multiple times when configuring the build,
# which causes errors for some flags (e.g., --specs=nano.specs).
# We prevent this with an include guard.
if(ARM_CORTEX_M7_HARDFLOAT_TOOLCHAIN_INCLUDED)
	return()
endif()

set(ARM_CORTEX_M7_HARDFLOAT_TOOLCHAIN_INCLUDED true)

if(NOT CPU_NAME)
	set(CPU_NAME cortex-m7)
endif()
set(CPU_FLAGS "-mcpu=cortex-m7 -mthumb --specs=nosys.specs --specs=nano.specs ${CPU_FLAGS}")
set(VFP_FLAGS "-mfloat-abi=hard -mfpu=fpv4-sp-d16 ${VFP_FLAGS}")

include(${CMAKE_CURRENT_LIST_DIR}/arm-none-eabi-gcc.cmake)
