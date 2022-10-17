#################
# Catch2 Module #
#################
# This module simplifies the process of adding Catch2 testing support to your build.
#
# You can link against the `catch2_dep` library to access the dependency
#
# By default, XML output will be placed in ${CMAKE_BINARY_DIR}/test. You can change this
# by setting CATCH2_TEST_OUTPUT_DIR before you include this module.
#
# We provide a default main implementation for Catch2 test programs. If you wish to define your
# own main file, set CATCH2_MAIN_FILE with the path to your file.
#
# We disable many options in the Catch2 dependency, such as building tests and installing docs/helpers.
# You can pass your own settings to the dependency by setting the CATCH2_DEP_SETTINGS variable.
#
# Our default compile-time settings are provided in CATCH2_COMPILE_SETTINGS. You can override
# our settings completely by defining this variable. You can also provide additional settings
# using CATCH2_ADDITIONAL_COMPILE_SETTINGS.
#
# This module also provides a `register_catch2_test` function to simplify the registration of Catch2
# test programs. Call this function with the desired test name and the build target for the test
# program. This call can be used with multiple test programs.
#
# Example:
#   register_catch2_test(Printf.Test printf_tests)

include(${CMAKE_CURRENT_LIST_DIR}/../CPM.cmake)

## Set Default Options
if(NOT CATCH2_MAIN_FILE)
  set(CATCH2_MAIN_FILE ${CMAKE_CURRENT_LIST_DIR}/catch_main.cpp CACHE STRING "The file that contains the definiton of main for Catch2.")
endif()

if(NOT CATCH2_TEST_OUTPUT_DIR)
  set(CATCH2_TEST_OUTPUT_DIR ${CMAKE_BINARY_DIR}/test/ CACHE STRING "Location where Catch2 test results should live.")
endif()

if(NOT CATCH2_DEP_SETTINGS)
	set(CATCH2_DEP_SETTINGS
		"CATCH_BUILD_TESTING OFF"
		"CATCH_ENABLE_WERROR OFF"
		"CATCH_INSTALL_DOCS OFF"
		"CATCH_INSTALL_HELPERS OFF"
		CACHE STRING "Settings that control the Catch2 dependency build target.")
endif()

if(NOT CATCH2_COMPILE_SETTINGS)
	set(CATCH2_COMPILE_SETTINGS
		-DCATCH_CONFIG_FAST_COMPILE
		-DCATCH_CONFIG_NO_WCHAR
		-DCATCH_CONFIG_NO_POSIX_SIGNALS
		-DCATCH_CONFIG_DISABLE_MATCHERS
		-DMSE_DISABLE_IOSTREAM
		-DMSE_SCOPEPOINTER_DEBUG_RUNTIME_CHECKS_DISABLED
		-fexceptions
		-funwind-tables
	CACHE STRING "Settings that control Catch2 compilation.")
endif()

if(CATCH2_ADDITIONAL_COMPILE_SETTINGS)
	list(APPEND CATCH2_COMPILE_SETTINGS ${CATCH2_ADDITIONAL_COMPILE_SETTINGS})
endif()

######################
# Satisfy Dependency #
######################

# The library target is Catch2
CPMAddPackage(
  NAME Catch2
  GITHUB_REPOSITORY catchorg/Catch2
  VERSION 2.13.0
  OPTIONS
  	${CATCH2_DEP_SETTINGS}
)

# Define a build target that users can link against to build a Catch2 test program
add_library(catch2_dep INTERFACE)
target_link_libraries(catch2_dep INTERFACE Catch2)
target_sources(catch2_dep INTERFACE ${CATCH2_MAIN_FILE})
target_compile_options(catch2_dep INTERFACE ${CATCH2_COMPILE_SETTINGS})

################################
# Register Catch2 test targets #
################################

function(register_catch2_test test_name target)
	set(JUNIT_XML_NAME ${CATCH2_TEST_OUTPUT_DIR}/${target}.xml)
	set(CATCH_XML_NAME ${CATCH2_TEST_OUTPUT_DIR}/${target}_catchxml.xml)

	add_test(NAME ${test_name}
		COMMAND ${target}
	)

	# Add a command to run the tests with standard Catch output
	add_custom_target(test-${target}
		COMMAND ${target}
	)

	# Generate JUnit XML output
	add_custom_target(${target}-xml
		COMMAND ${target} -s -r junit -o ${JUNIT_XML_NAME}
	)
	set_target_properties(${target}-xml PROPERTIES ADDITIONAL_CLEAN_FILES ${JUNIT_XML_NAME})

	# Generate Catch2 XML output
	add_custom_target(${target}-catch-xml
		COMMAND ${target} -s -r xml -o ${CATCH_XML_NAME}
	)
	set_target_properties(${target}-catch-xml PROPERTIES ADDITIONAL_CLEAN_FILES ${CATCH_XML_NAME})
endfunction()
