cmake_minimum_required(VERSION 3.17)
project(EmbeddedArtistryLibc
	VERSION 1.0
	DESCRIPTION "A libc implementation for microcontroller-based embedded systems."
	LANGUAGES C CXX ASM)

set_property(GLOBAL PROPERTY C_STANDARD 11)

include(cmake/CPM.cmake)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR LIBC_BUILD_TESTING)
    include(CTest)
endif()

include(cmake/AddExecutableWithLinkerScriptDep.cmake)
include(cmake/CheckAndApplyFlags.cmake)
include(cmake/Conversions.cmake)

include(BuildOptions.cmake)
include(Packaging.cmake)

##################
# Compiler Flags #
##################

# If we're not a subproject, globally apply our warning flags
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  add_compile_options(-Wall -Wextra)
endif()

# This function can be used to generate a linker map file on an executable target
# in a compiler-agnostic way (currently supports GCC and Clang compiler families)
function(target_linker_map target)
  check_c_linker_flag("-Wl,-Map,test.map" _Map1)
  if("${_Map1}")
    set(GEN_MAP_FILE "-Wl,-Map,")
  else()
    check_c_linker_flag("-Wl,-map,test.map" _Map2)
    if("${_Map2}")
      set(GEN_MAP_FILE "-Wl,-map,")
    else()
      message("[WARNING] ${CMAKE_C_COMPILER_ID} does not have a defined linker map argument.")
      return()
    endif()
  endif()

  get_target_property(map_dir ${target} BINARY_DIR)
  target_link_options(${target} PRIVATE ${GEN_MAP_FILE}${map_dir}/${target}.map)
  set_target_properties(${target} PROPERTIES
    ADDITIONAL_CLEAN_FILES ${target}.map)
endfunction()

if(ENABLE_COVERAGE)
  include(cmake/CodeCoverage.cmake)
  append_coverage_compiler_flags()
endif()

#####################
# Printf Dependency #
#####################

CPMAddPackage(
  NAME printf
  GITHUB_REPOSITORY mpaland/printf
  VERSION 4.0.0
  DOWNLOAD_ONLY
)

add_library(printf INTERFACE)
target_sources(printf INTERFACE ${printf_SOURCE_DIR}/printf.c)
target_include_directories(printf SYSTEM INTERFACE ${printf_SOURCE_DIR})

if(LIBC_TESTING_IS_ENABLED)
  add_executable(printf_tests)
  target_sources(printf_tests PRIVATE ${printf_SOURCE_DIR}/test/test_suite.cpp)
  target_include_directories(printf_tests PRIVATE ${printf_SOURCE_DIR})
  install(FILES ${printf_SOURCE_DIR}/printf.h DESTINATION include)
  target_linker_map(printf_tests)
  set_target_properties(printf_tests PROPERTIES CXX_STANDARD 11)

  # Re-build + execute tests, printing test information to the console instead of the XML file
  add_custom_target(test-printf printf_tests)

  add_test(NAME Printf.Test
    COMMAND printf_tests -s -r junit -o ${CMAKE_BINARY_DIR}/printf_tests.xml
  )
endif()

#######################
# Openlibm Dependency #
#######################

CPMAddPackage(
  NAME openlibm
  GITHUB_REPOSITORY JuliaMath/openlibm
  VERSION 0.7.0
  DOWNLOAD_ONLY
)

add_library(openlibm INTERFACE)
target_include_directories(openlibm SYSTEM INTERFACE
	${openlibm_SOURCE_DIR}/src
	${openlibm_SOURCE_DIR}/include
)
install(DIRECTORY ${openlibm_SOURCE_DIR}/include/ DESTINATION include)
install(DIRECTORY ${openlibm_SOURCE_DIR}/src DESTINATION include FILES_MATCHING PATTERN "*.h")

#####################
# CMocka Dependency #
#####################

if(LIBC_TESTING_IS_ENABLED)
  find_package(cmocka QUIET)
  if(NOT cmocka_FOUND)
    CPMAddPackage(
      NAME cmocka
      GIT_REPOSITORY https://git.cryptomilk.org/projects/cmocka.git/
      VERSION 1.1.5
      GIT_TAG cmocka-1.1.5
      DOWNLOAD_ONLY YES
    )

    # Convenience variable to shorten our code below
    set(CMOCKA_STATIC_FILENAME
      ${CMAKE_STATIC_LIBRARY_PREFIX}cmocka-static${CMAKE_STATIC_LIBRARY_SUFFIX}
    )

    # We would normally use CPMAddPackage, but CMocka's build presents problems.
    # So we include it as an external project, which allows us to build the lib
    # separately and then link it in.
    include(ExternalProject)
    ExternalProject_Add(project_cmocka
      SOURCE_DIR ${cmocka_SOURCE_DIR}
      PREFIX ${CMAKE_CURRENT_BINARY_DIR}/cmocka
      BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/cmocka
      CMAKE_ARGS
        -DBUILD_STATIC_LIB=ON
        -DWITH_STATIC_LIB=ON # Without this, Cmocka will not install the static lib
        -DWITH_EXAMPLES=OFF
        -DCMAKE_BUILD_TYPE=Debug
        -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/cmocka
      # This is needed with Ninja generators to prevent it from failing due to
      # the library being missing before the build has been run
      BUILD_BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/cmocka/lib/${CMOCKA_STATIC_FILENAME}
    )

    # We need to get the CMocka installation directory to know where our
    # built libraries can be found
    ExternalProject_Get_Property(project_cmocka BINARY_DIR)

    # Now we define an IMPORTED library target and tell CMake where the library
    # files can be found. To ensure the build flows in the proper order,
    # we'll add a dependency on the ExternalProject target above, which will
    # ensure the library is built before we try to link it
    add_library(cmocka-static STATIC IMPORTED)
    set_target_properties(cmocka-static PROPERTIES
      IMPORTED_LOCATION ${BINARY_DIR}/lib/${CMOCKA_STATIC_FILENAME}
    )
    add_dependencies(cmocka-static project_cmocka)

    # Maintain build compatibility between find_package and CMakeLists.txt variants.
    set(CMOCKA_LIBRARIES cmocka-static)
    set(CMOCKA_INCLUDE_DIR ${BINARY_DIR}/include)
  endif()
endif()

##########################
# Enable Static Analysis #
##########################

find_program(CPPCHECK cppcheck)

if(CPPCHECK)
  set(CPPCHECK_DEFAULT_ARGS
    ${CPPCHECK} --quiet --enable=style --force
      # Include directories
      -I ${CMAKE_CURRENT_LIST_DIR}/include
  )

  if(BUILD_WITH_STATIC_ANALYSIS)
    set(CMAKE_C_CPPCHECK ${CPPCHECK_DEFAULT_ARGS})
  endif()

  add_custom_target(cppcheck
    COMMAND ${CPPCHECK_DEFAULT_ARGS}
    # Source directories
    ${CMAKE_CURRENT_LIST_DIR}/src/ ${CMAKE_CURRENT_LIST_DIR}/target/
  )

  add_custom_target(cppcheck-xml
    COMMAND ${CPPCHECK_DEFAULT_ARGS}
    # enable XML output
    --xml --xml-version=2
    # Source directories
    ${CMAKE_CURRENT_LIST_DIR}/src/ ${CMAKE_CURRENT_LIST_DIR}/target/
    # Redirect to file
    2>${CMAKE_BINARY_DIR}/cppcheck.xml
  )
endif()

find_program(CLANG_TIDY clang-tidy)
if(CLANG_TIDY)
  if(BUILD_WITH_STATIC_ANALYSIS)
    set(CMAKE_C_CLANG_TIDY ${CLANG_TIDY})
  endif()

  add_custom_target(tidy
    COMMAND tools/clang-tidy.sh ${CMAKE_BINARY_DIR}
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
  )
endif()

#######################
# Process Source Tree #
#######################

add_subdirectory(arch/${CMAKE_SYSTEM_PROCESSOR})
add_subdirectory(src)

#####################
# Process Test Tree #
#####################

add_subdirectory(test)

###################
# Tooling Targets #
###################

find_program(DOXYGEN doxygen)
if(DOXYGEN)
  add_custom_target(docs
    COMMAND ${DOXYGEN} docs/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
  )
  # This property will remove a directory, while add_custom_target BYPRODUCTS will not.
  set_target_properties(docs PROPERTIES ADDITIONAL_CLEAN_FILES ${CMAKE_BINARY_DIR}/doc/)
endif()

find_program(CLANG_FORMAT clang-format)
if(CLANG_FORMAT)
  add_custom_target(format
    COMMAND tools/format.sh
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
  )

  add_custom_target(format-patch
    COMMAND tools/format-patch.sh
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
  )
endif()

find_program(LIZARD lizard)
if(LIZARD)
  set(LIZARD_BASE_ARGS
      ${LIZARD}
      --length 75 # fail when functions longer than this
      --CCN 10 # fail over this CCN
      --arguments 10 # fail this arg count
  )
  set(LIZARD_PATHS ${CMAKE_CURRENT_LIST_DIR}/src ${CMAKE_CURRENT_LIST_DIR}/tests)

  add_custom_target(complexity
    COMMAND
      ${LIZARD_BASE_ARGS}
      -w # Only show warnings
      ${LIZARD_PATHS}
  )

  add_custom_target(complexity-full
    COMMAND
      ${LIZARD_BASE_ARGS}
      ${LIZARD_PATHS}
  )

  add_custom_target(complexity-xml
    COMMAND
      ${LIZARD_BASE_ARGS}
      --xml # Generate XML output
      ${LIZARD_PATHS}
      # Redirect output to file
      > ${CMAKE_BINARY_DIR}/complexity.xml
    BYPRODUCTS
      ${CMAKE_BINARY_DIR}/complexity.xml
  )
endif()

if(ENABLE_COVERAGE)
  setup_target_for_coverage_gcovr_xml(
    NAME coverage-xml
    EXECUTABLE ctest
    DEPENDENCIES libc_tests printf_tests
  )

  setup_target_for_coverage_gcovr_html(
    NAME coverage-html
    EXECUTABLE ctest
    DEPENDENCIES libc_tests printf_tests
  )

  add_custom_target(coverage
    DEPENDS coverage-xml coverage-html)
endif()
