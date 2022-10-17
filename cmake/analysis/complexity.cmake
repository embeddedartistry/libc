##############################
# Complexity Analysis Module #
##############################
#
# This module provides complexity analysis targets to the build.
#
# You can control the behavior of lizard by setting the following variables
# before you include this module:
#   LIZARD_DIRS, which is a CMake list of directories to include in complexity analysis
#     By default, the src and test directories are included
#   LIZARD_EXCLUDES, which is a CMake list of directories/files to exclude from analysis
#     By default, this variable is not set
#   LIZARD_LENGTH_LIMIT, which specifies the maximum funtion length in lines
#   LIZARD_CCN_LIMIT, which specifies the maximum CCN limit
#   LIZARD_ARG_LIMIT, which specifies the maximum number of arguments
#
# You can completely override the default vaules by setting the variables above.
# You can also add to the defaults by defining these variables:
#   LIZARD_ADDITIONAL_DIRS, which is a CMake List of directories to include
#   LIZARD_ADDITIONAL_OPTIONS, which is a CMake list of additional flags and values to pass to Lizard

find_program(LIZARD lizard)
if(LIZARD)

  ## Set Default Arguments
  if(NOT LIZARD_DIRS)
    set(LIZARD_DIRS src test CACHE STRING "CMake list of directories to analyze with lizard.")
  endif()

  if(LIZARD_ADDITIONAL_DIRS)
    list(APPEND LIZARD_DIRS "${LIZARD_ADDITIONAL_DIRS}")
  endif()

  if(NOT LIZARD_LENGTH_LIMIT)
    set(LIZARD_LENGTH_LIMIT 60 CACHE STRING "The maximum length of a function (in lines) before a failure is triggered.")
  endif()

  if(NOT LIZARD_CCN_LIMIT)
    set(LIZARD_CCN_LIMIT 10 CACHE STRING "The maximum CCN of a function before a failure is triggered.")
  endif()

  if(NOT LIZARD_ARG_LIMIT)
    set(LIZARD_ARG_LIMIT 6 CACHE STRING "The maximum number of function arguments before a failure is triggered.")
  endif()

  if(LIZARD_EXCLUDES)
    foreach(exclude ${LIZARD_EXCLUDES})
      list(APPEND LIZARD_EXCLUDE_ARGS -x ${exclude})
    endforeach()
  endif()

  set(LIZARD_BASE_ARGS
      ${LIZARD}
      --length ${LIZARD_LENGTH_LIMIT} # fail when functions longer than this
      --CCN ${LIZARD_CCN_LIMIT} # fail over this CCN
      --arguments ${LIZARD_ARG_LIMIT} # fail this arg count
      ${LIZARD_EXCLUDE_ARGS}
      ${LIZARD_ADDITIONAL_OPTIONS}
  )

  ### Targets
  add_custom_target(complexity
    COMMAND
      ${LIZARD_BASE_ARGS}
      -w # Only show warnings
      ${LIZARD_DIRS}
    WORKING_DIRECTORY
      ${CMAKE_SOURCE_DIR}
  )

  add_custom_target(complexity-full
    COMMAND
      ${LIZARD_BASE_ARGS}
      ${LIZARD_DIRS}
    WORKING_DIRECTORY
      ${CMAKE_SOURCE_DIR}
  )

  add_custom_target(complexity-xml
    COMMAND
      ${LIZARD_BASE_ARGS}
      --xml # Generate XML output
      ${LIZARD_DIRS}
      # Redirect output to file
      > ${CMAKE_BINARY_DIR}/complexity.xml
    BYPRODUCTS
      ${CMAKE_BINARY_DIR}/complexity.xml
    WORKING_DIRECTORY
      ${CMAKE_SOURCE_DIR}
  )
else()
  message("[WARNING] Lizard is not installed. Complexity targets are disabled.")
endif()
