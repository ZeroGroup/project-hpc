cmake_minimum_required(VERSION 2.8)

project(Hpc)

set(HPC_MAJOR_VERSION 0)
set(HPC_MINOR_VERSION 1)
set(HPC_PATCH_VERSION 0)
set(HPC_VERSION
  ${HPC_MAJOR_VERSION}.${HPC_MINOR_VERSION}.${HPC_PATCH_VERSION})

if(${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
  message(FATAL_ERROR "You should not call cmake in-source. See README.md for details")
endif()

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

find_package(CUDA REQUIRED)

LIST(APPEND CMAKE_CXX_FLAGS "--std=c++11 -Wall")
LIST(APPEND CUDA_NVCC_FLAGS -std=c++11 -gencode arch=compute_30,code=sm_30)
SET(CUDA_PROPAGATE_HOST_FLAGS OFF)

include_directories(
#  "${PROJECT_SOURCE_DIR}"   # to find hpc/foo.h
  "${PROJECT_BINARY_DIR}")      # to find hpc/<component>/config.h

#######################################
### COMPONENTS      LIST     BEGIN ####

add_subdirectory(sensors)
add_subdirectory(gui)

# testing component for illustration
#add_subdirectory(component_name)

### COMPONENTS       LIST      END ####
#######################################

# Add all targets to the build-tree export set
export(TARGETS sensors FILE "${PROJECT_BINARY_DIR}/HpcTargets.cmake")

# Export the package for use from the build-tree
export(PACKAGE Hpc)

# Create the HpcConfig.cmake and HpcConfigVersion.cmake files
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}" "${INSTALL_INCLUDE_DIR}")

message(" DUUUUUUUUUPA: " ${REL_INCLUDE_DIR})
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
