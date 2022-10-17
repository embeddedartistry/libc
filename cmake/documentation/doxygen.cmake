########################
# Doxygen Build Module #
########################

find_program(DOXYGEN doxygen)

if(DOXYGEN)
	## Set default values for variables
	if(NOT DOXYGEN_PROJECT_NAME)
		set(DOXYGEN_PROJECT_NAME ${PROJECT_NAME} CACHE STRING "Project name used for Doxygen documentation.")
	endif()

	if(NOT DOXYGEN_PROJECT_VERSION)
		set(DOXYGEN_PROJECT_VERSION ${CMAKE_PROJECT_VERSION} CACHE STRING "Project version reported in Doxygen documentation.")
	endif()

	if(NOT DOXYGEN_PROJECT_DESCRIPTION)
		set(DOXYGEN_PROJECT_DESCRIPTION ${CMAKE_PROJECT_DESCRIPTION} CACHE STRING "Short project description used for Doxygen documentation.")
	endif()

	if(NOT DOXYGEN_OUTPUT_DIR)
		set(DOXYGEN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/docs CACHE STRING "Output directory for Doxygen documentation.")
	endif()

	if(NOT DOXYGEN_INPUT_DIRS)
		set(DOXYGEN_INPUT_DIRS src docs README.md CACHE STRING "List of input files and folders used to generate Doxygen documentation.")
	endif()

	if(DOXYGEN_ADDITIONAL_INPUT_DIRS)
		list(APPEND DOXYGEN_INPUT_DIRS "${DOXYGEN_ADDITIONAL_INPUT_DIRS}")
	endif()

	# Convert to expected Doxygen output
	string(REPLACE ";" " " DOXYGEN_INPUT_DIRS "${DOXYGEN_INPUT_DIRS}")

	if(NOT DOXYGEN_EXCLUDE_PATTERNS)
		set(DOXYGEN_EXCLUDE_PATTERNS catch.hpp CACHE STRING "Project name used for Doxygen documentation.")
	endif()

	if(DOXYGEN_ADDITIONAL_EXCLUDE_PATTERNS)
		list(APPEND DOXYGEN_EXCLUDE_PATTERNS "${DOXYGEN_ADDITIONAL_EXCLUDE_PATTERNS}")
	endif()

	if(NOT DOXYGEN_MD_AS_MAINPAGE)
		set(DOXYGEN_MD_AS_MAINPAGE README.md CACHE STRING "Project name used for Doxygen documentation.")
	endif()

	## Process Doxyfile.in
	configure_file(${CMAKE_CURRENT_LIST_DIR}/Doxyfile.in ${DOXYGEN_OUTPUT_DIR}/Doxyfile @ONLY)

	## Build Target
	add_custom_target(docs
		COMMAND ${DOXYGEN} ${DOXYGEN_OUTPUT_DIR}/Doxyfile
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	)
	# This property will remove a directory, while add_custom_target BYPRODUCTS will not.
	set_target_properties(docs PROPERTIES ADDITIONAL_CLEAN_FILES ${DOXYGEN_OUTPUT_DIR})
else()
	message("[WARNING] Doxygen not installed. Documentation targets are disabled.")
endif()
