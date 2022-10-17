#################
# CMocka Module #
#################
# This module simplifies the process of adding CMocka testing support to your build.
#
# You can link against the `cmocka_dep` library to access the dependency in an agnostic manner.
#
# This module also provides a `test-clear-results` target which can be used to clear existing
# XML files, since CMocka will not save XML data if the files already exist.
#
# By default, XML output will be placed in ${CMAKE_BINARY_DIR}/test. You can change this
# by setting CMOCKA_TEST_OUTPUT_DIR before you include this module.
#
# This module also provides a `register_cmocka_test` function to simplify the registration of CMocka
# test programs. Call this function with the desired test name and the build target for the test
# program. This call can be used with multiple test programs.
#
# Example:
#   register_cmocka_test(Libc.Test libc_tests)

include(${CMAKE_CURRENT_LIST_DIR}/../CPM.cmake)

## Set Default Options
if(NOT CMOCKA_TEST_OUTPUT_DIR)
  set(CMOCKA_TEST_OUTPUT_DIR ${CMAKE_BINARY_DIR}/test/ CACHE STRING "Location where CMocka test results should live.")
endif()

######################
# Satisfy Dependency #
######################

find_package(cmocka QUIET)

if(NOT cmocka_FOUND)
  CPMAddPackage(
    NAME cmocka
    GIT_REPOSITORY https://git.cryptomilk.org/projects/cmocka.git/
    VERSION 1.1.5
    GIT_TAG cmocka-1.1.5
    DOWNLOAD_ONLY YES
  )

  # We would normally use CPMAddPackage, but CMocka's build presents problems.
  # So we include it as an external project, which allows us to build the lib
  # separately and then link it in.
  include(ExternalProject)
  ExternalProject_Add(project_cmocka
    SOURCE_DIR ${cmocka_SOURCE_DIR}
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/cmocka
    CMAKE_ARGS -DBUILD_STATIC_LIB=ON -DWITH_EXAMPLES=OFF -DCMAKE_BUILD_TYPE=Debug
  )

  # We need to get the CMocka installation directory to know where our
  # built libraries can be found
  ExternalProject_Get_Property(project_cmocka INSTALL_DIR)
  # We need to get the include directory path from the project
  ExternalProject_Get_Property(project_cmocka CMOCKA_INCLUDE_DIR)

  # Now we define an IMPORTED library target and tell CMake where the library
  # files can be found. To ensure the build flows in the proper order,
  # we'll add a dependency on the ExternalProject target above, which will
  # ensure the library is built before we try to link it
  add_library(cmocka IMPORTED STATIC)
  set_target_properties(cmocka PROPERTIES IMPORTED_LOCATION ${INSTALL_DIR})
  add_dependencies(cmocka project_cmocka)

  # Maintain build compatibility between find_package and CMakeLists.txt variants.
  set(CMOCKA_LIBRARIES cmocka)
endif()

add_library(cmocka_dep INTERFACE)
target_include_directories(cmocka_dep INTERFACE ${CMOCKA_INCLUDE_DIR})
target_link_libraries(cmocka_dep INTERFACE ${CMOCKA_LIBRARIES})

##################
# Helper Targets #
##################

add_custom_target(test-clear-results
  COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMOCKA_TEST_OUTPUT_DIR}/*.xml
  COMMENT "Removing XML files in the test/ directory"
)

############################
# Register Test with CTest #
############################

add_test(NAME CMocka.ClearResults
  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test-clear-results
)

################################
# Register CMocka test targets #
################################
function(register_cmocka_test test_name target)
  add_custom_target(test-${target}
    COMMAND export CMOCKA_MESSAGE_OUTPUT=stdout
    COMMAND ${target}
  )

  add_test(NAME ${test_name}
    COMMAND ${target}
  )

  set_tests_properties(${test_name}
    PROPERTIES
      ENVIRONMENT CMOCKA_XML_FILE=${CMOCKA_TEST_OUTPUT_DIR}/%g.xml
      DEPENDS CMocka.ClearResults
  )
endfunction()
