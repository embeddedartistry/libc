#########################
# Code Sanitizer Module #
#########################
# This module provides a USE_SANITIZER option which can enable code sanitizers with GCC and Clang.
# Include this module before you define your targets to ensure the proper arguments are added
# to your targets.

set(USE_SANITIZER
    "" CACHE STRING
    "Compile with a sanitizer. Options are: Address, Memory, Leak, Undefined, Thread, 'Address;Undefined'"
)

if(USE_SANITIZER MATCHES "([Aa]ddress)")
  add_compile_options(-fsanitize=address)
  add_link_options(-fsanitize=address)
elseif(USE_SANITIZER MATCHES "([Tt]hread)")
  add_compile_options(-fsanitize=thread)
  add_link_options(-fsanitize=thread)
elseif(USE_SANITIZER MATCHES "([Uu]ndefined)")
  add_compile_options(-fsanitize=undefined)
  add_link_options(-fsanitize=undefined)
elseif(USE_SANITIZER MATCHES "([Ll]eak)")
  add_compile_options(-fsanitize=leak)
  add_link_options(-fsanitize=leak)
elseif(USE_SANITIZER MATCHES "([Mm]emory)")
  add_compile_options(-fsanitize=memory)
  add_link_options(-fsanitize=memory)
elseif(USE_SANITIZER MATCHES "([Aa]ddress),([Uu]ndefined)")
  add_compile_options(-fsanitize=address,undefined)
  add_link_options(-fsanitize=address,undefined)
elseif(NOT "${USE_SANITIZER}" STREQUAL "" AND NOT "${USE_SANITIZER}" STREQUAL "None")
  message(FATAL_ERROR "Unsupported value of USE_SANITIZER: ${USE_SANITIZER}")
endif()

# Set the possible values of build type for cmake-gui/ccmake
set_property(CACHE USE_SANITIZER
	PROPERTY STRINGS "None" "Address" "Thread" "Undefined" "Leak" "Memory" "Address,Undefined"
)
