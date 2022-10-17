####################
# SLOCCount Module #
####################
#
# This module adds an sloccount target to your build system, which provides
# line of code analysis and cost/effort estimates for your project.
#
# All variables used below can be overridden by the user. Simply define the variables
# with your own values before invoking this module.
#
# The settings for this module default to "embedded" COCOMO mode:
# 	Embedded: The project must operate within tight (hard-to-meet) constraints,
#	and requirements and interface specifications are often non-negotiable.
#	The software will be embedded in a complex environment that the software must deal with as-is.
#
# Values for the models are:
#	Organic: effort factor = 2.4, exponent = 1.05; schedule factor = 2.5, exponent = 0.38
#	Semidetached: effort factor = 3.0, exponent = 1.12; schedule factor = 2.5, exponent = 0.35
#	Embedded: effort factor = 3.6, exponent = 1.20; schedule factor = 2.5, exponent = 0.32
#
# For information on tuning the model, see:
#	https://dwheeler.com/sloccount/sloccount.html#cocomo

find_program(SLOCCount sloccount)

if(SLOCCount)
	# Set defaults
	if(NOT SLOCCOUNT_DIRS)
		set(SLOCCOUNT_DIRS
			src
			test
			CACHE STRING "Directories to analyze with SLOCCount.")
	endif()

	if(SLOCCOUNT_ADDITIONAL_DIRS)
		lists(APPEND SLOCCOUNT_DIRS ${SLOCCOUNT_ADDITIONAL_DIRS})
	endif()

	# SLOCCOUNT_EFFORT is a pair of values [F, E], where F is the factor and E is the exponent.
	# this impacts calculated effort in person-months.
	if(NOT SLOCCOUNT_EFFORT)
		set(SLOCCOUNT_EFFORT 3.6;1.12
			CACHE STRING "A pair of values F;E where F is the factor and E is the exponent. This impacts calculated effort in person months.")
	endif()

	# SLOCCOUNT_SCHEDULE is a pair of values [F, E], where F is the factor and E is the exponent.
	# this impacts calculated effort in person-months.
	if(NOT SLOCCOUNT_SCHEDULE)
		set(SLOCCOUNT_SCHEDULE 2.5;0.32
			CACHE STRING "A pair of values F;E where F is the factor and E is the exponent. This impacts calculated effort in person months.")
	endif()

	# The average salary value to use in cost estimates
	if(NOT SLOCCOUNT_SALARY)
		set(SLOCCOUNT_SALARY 140000
			CACHE STRING "The average salary value to use in cost estimates.")
	endif()

	# The developer overhead value to use in cost estimates
	if(NOT SLOCCOUNT_OVERHEAD)
		set(SLOCCOUNT_OVERHEAD 2
			CACHE STRING "The developer overhead value to use in cost estimates.")
	endif()

	if(NOT SLOCCOUNT_DATA_DIR)
		set(SLOCCOUNT_DATA_DIR ${CMAKE_BINARY_DIR}/sloccount
			CACHE STRING "The location that sloccount will cache data.")
	endif()

	# Create the output directory
	file(MAKE_DIRECTORY ${SLOCCOUNT_DATA_DIR})

	# You can override the default set by defining this variable
	if(NOT SLOCCOUNT_ARGS)
		set(SLOCCOUNT_ARGS
			# Follow symbolic links
			--follow
			# Store data in the output directory
			--datadir ${SLOCCOUNT_DATA_DIR}
			# Effort factor/exponent
			--effort ${SLOCCOUNT_EFFORT}
			# Schedule factor/exponent
			--schedule ${SLOCCOUNT_SCHEDULE}
			# Annual Salary Setting
			--personcost ${SLOCCOUNT_SALARY}
			# Overhad value
			--overhead ${SLOCCOUNT_OVERHEAD}
			CACHE STRING "Default arguments supplied to SLOCCount"
		)
	endif()

	# Add arguments to the default set
	if(SLOCCOUNT_ADDITIONAL_ARGS)
		list(APPEND SLOCCOUNT_ARGS ${SLOCCOUNT_ADDITIONAL_ARGS})
	endif()

	##################
	# Custom Targets #
	##################
	add_custom_target(sloccount
		COMMAND ${SLOCCount} ${SLOCCOUNT_ARGS} ${SLOCCOUNT_DIRS}
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	)

	add_custom_target(sloccount-full
		COMMAND ${SLOCCount} ${SLOCCOUNT_ARGS}
			# Show details for every source code file
			--details
			${SLOCCOUNT_DIRS}
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	)

	add_custom_target(sloccount-report
		COMMAND ${SLOCCount} ${SLOCCOUNT_ARGS}
			# Show details for every source code file
			--details
			${SLOCCOUNT_DIRS}
			# Redirect output to file
	      	> ${CMAKE_BINARY_DIR}/sloccount.sc
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	)
	set_target_properties(sloccount-report
		PROPERTIES ADDITIONAL_CLEAN_FILES ${CMAKE_BINARY_DIR}/sloccount.sc)

	add_custom_target(sloccount-report-full
		COMMAND ${SLOCCount} ${SLOCCOUNT_ARGS}
			# Show details for every source code file
			--details
			${SLOCCOUNT_DIRS}
			# Redirect output to file
	      	> ${CMAKE_BINARY_DIR}/sloccount_detailed.sc
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	)
	set_target_properties(sloccount-report-full
		PROPERTIES ADDITIONAL_CLEAN_FILES ${CMAKE_BINARY_DIR}/sloccount_detailed.sc)

endif()
