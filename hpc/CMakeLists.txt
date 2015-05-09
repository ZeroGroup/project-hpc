cmake_minimum_required(VERSION 2.8.11)

project(Hpc CXX C)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)

# Get the current working branch
execute_process(
  COMMAND git rev-parse --abbrev-ref HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE HPC_GIT_BRANCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get the latest abbreviated commit hash of the working branch
execute_process(
  COMMAND git log -1 --format=%h
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE HPC_GIT_COMMIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get the latest full commit hash of the working branch
execute_process(
  COMMAND git log -1 --format=%H
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE HPC_GIT_COMMIT_HASH_FULL
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get the latest full commit hash of the working branch
execute_process(
  COMMAND date -u +"%Y-%m-%dT%H:%M:%SZ"
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE HPC_BUILD_TIME
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

message(STATUS "building branch ${HPC_GIT_BRANCH} rev.${HPC_GIT_COMMIT_HASH_FULL}")

set(HPC_MAJOR_VERSION 0)
set(HPC_MINOR_VERSION 1)
set(HPC_PATCH_VERSION 0)
set(HPC_VERSION_STRING
  ${HPC_MAJOR_VERSION}.${HPC_MINOR_VERSION}.${HPC_PATCH_VERSION}-rev${GIT_SHA1})

configure_file(config.h.in "${PROJECT_BINARY_DIR}/config.h" @ONLY)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Remove 'lib' prefix for shared libraries on Windows
if (WIN32)
  set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif ()

# install binaries in repository root,
# TODO: make it parametric
get_filename_component(CMAKE_INSTALL_PREFIX
  "${PROJECT_SOURCE_DIR}/.."
  REALPATH
)

# Offer the user the choice of overriding the installation directories
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")
set(INSTALL_DOCS_DIR docs CACHE PATH "Installation directory for documentation")

if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR CMake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/CMake/Hpc)
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")

# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

LIST(APPEND CMAKE_CXX_FLAGS "--std=c++11 -Wall -pedantic")

include_directories(
#  "${PROJECT_SOURCE_DIR}"   # to find hpc/foo.h
  "${PROJECT_BINARY_DIR}")      # to find hpc/<component>/config.h

#######################################
###  SETUP   GOOGLE    TEST   PATH  ###
set(GTEST_ROOT ${PROJECT_SOURCE_DIR}/libs/gtest-1.7.0)

#######################################
###     COMPONENTS       LIST      ####

add_subdirectory(sensors)
add_subdirectory(gui)

# testing component for illustration
#add_subdirectory(component_name)
#######################################

# Add all targets to the build-tree export set
export(TARGETS hpc-gui hpc-sensors FILE "${PROJECT_BINARY_DIR}/HpcTargets.cmake")

# Export the package for use from the build-tree
export(PACKAGE Hpc)

# Create the HpcConfig.cmake and HpcConfigVersion.cmake files
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}" "${INSTALL_INCLUDE_DIR}")

# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(HpcConfig.cmake.in "${PROJECT_BINARY_DIR}/HpcConfig.cmake" @ONLY)

# ... for the install tree
set(CONF_INCLUDE_DIRS "\${HPC_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(HpcConfig.cmake.in "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/HpcConfig.cmake" @ONLY)

# ... for both
configure_file(HpcConfigVersion.cmake.in "${PROJECT_BINARY_DIR}/HpcConfigVersion.cmake" @ONLY)

install(FILES
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/HpcConfig.cmake"
  "${PROJECT_BINARY_DIR}/HpcConfigVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)

# Install the export set for use with the install-tree
install(EXPORT HpcTargets DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)

# DOXYGEN!, becouse why not
find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(docs
        ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
    )

    #install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION "${INSTALL_DOCS_DIR}/api")
endif(DOXYGEN_FOUND)
