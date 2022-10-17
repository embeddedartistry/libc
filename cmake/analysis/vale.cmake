################################
# Vale Document Linting Module #
################################
# This module adds a vale document linting target to your build system.
#
# All variables used below can be overridden by the user. Simply define the variables
# with your own values before invoking this module.

find_program(VALE vale)

if(VALE)
 	# Code goes here

	if(NOT VALE_FILES)
		set(VALE_FILES
			docs/ README.md
			CACHE STRING "List of folders and files for vale to lint.")
	endif()

	if(VALE_ADDITIONAL_FILES)
		list(APPEND VALE_FILES ${VALE_ADDITIONAL_FILES})
	endif()

	if(NOT VALE_FILETYPES)
		set(VALE_FILETYPES "md,rst,txt"
			CACHE STRING "Comma-separated list of filetypes for vale to lint.")
	endif()

	if(VALE_ADDITIONAL_FILETYPES)
		list(APPEND VALE_FILETYPES ${VALE_ADDITIONAL_FILETYPES})
		string(REPLACE ";" "," VALE_FILETYPES ${VALE_FILETYPES})
	endif()

	# Supply a style file, which will use this file instead of the default .vale.ini
	if(NOT VALE_CONFIG_FILE)
		set(VALE_CONFIG_FILE
			${CMAKE_CURRENT_LIST_DIR}/vale-styleguide/config/documentation.vale.ini
			CACHE STRING "Configuration file to use instead of the default .vale.ini"
		)
	endif()

	if(NOT VALE_ARGS)
		set(VALE_ARGS
			--glob='*.{${VALE_FILETYPES}}'
			CACHE STRING "Arguments passed to Vale."
		)

		if(NOT "${VALE_CONFIG_FILE}" STREQUAL "")
			list(APPEND VALE_ARGS --config ${VALE_CONFIG_FILE})
		endif()
	endif()

	if(VALE_ADDITIONAL_ARGS)
		list(APPEND VALE_ARGS ${VALE_ADDITIONAL_ARGS})
	endif()

	################
	# Vale Targets #
	################
	add_custom_target(vale
		COMMAND ${VALE} ${VALE_ARGS} ${VALE_FILES}
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	)

endif()
