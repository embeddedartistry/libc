########################
# Code Coverage Module #
########################
# This module is a wrapper around CodeCoverage.cmake, simplifying its use and auto-creating
# code coverage build targets.
#
# This module defines a `ENABLE_COVERAGE_ANALYSIS` option, which defaults to OFF.
# 	This option is only available when creating a debug build.
#
# Include this module at the top of the build file, before you define any build targets.
# This will ensure that the proper compilation flags are added to the build.
#
# After your targets are defined, you can invoke the `enable_coverage_targets` function.
# Call this function and supply any targets which you want to register as dependencies
# for the coverage targets.
#
# Example:
#	enable_coverage_targets(libc_tests printf_tests)

include(CMakeDependentOption)

CMAKE_DEPENDENT_OPTION(ENABLE_COVERAGE_ANALYSIS
  "Enable code coverage analysis."
  OFF
  "\"${CMAKE_BUILD_TYPE}\" STREQUAL \"Debug\""
  OFF)

if(ENABLE_COVERAGE_ANALYSIS)
	include(${CMAKE_CURRENT_LIST_DIR}/CodeCoverage.cmake)
	append_coverage_compiler_flags()
endif()


# Call this function with dependencies that should be added to the coverage targets
function(enable_coverage_targets)
	if(ENABLE_COVERAGE_ANALYSIS)
	  setup_target_for_coverage_gcovr_xml(
	    NAME coverage-xml
	    EXECUTABLE ctest
	    DEPENDENCIES ${ARGN}
	  )

	  setup_target_for_coverage_gcovr_html(
	    NAME coverage-html
	    EXECUTABLE ctest
	    DEPENDENCIES ${ARGN}
	  )

	  add_custom_target(coverage
	    DEPENDS coverage-xml coverage-html)
	endif()
endfunction()
