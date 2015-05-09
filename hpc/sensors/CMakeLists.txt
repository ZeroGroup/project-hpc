#######################################################################
# Component SENSORS
# SENSORS component contains CUDA/C code
#
# target is static library `libsensors.a`
#######################################################################

cmake_minimum_required(VERSION 2.8.11)
project(hpc-sensors)

message("step into sub-project: ${PROJECT_NAME}")

set(HPC_SENSORS_MAJOR_VERSION 0)
set(HPC_SENSORS_MINOR_VERSION 1)
set(HPC_SENSORS_PATCH_VERSION 0)
set(HPC_SENSORS_VERSION_STRING
  ${HPC_SENSORS_MAJOR_VERSION}.${HPC_SENSORS_MINOR_VERSION}.${HPC_SENSORS_PATCH_VERSION})

configure_file(config.h.in "${PROJECT_BINARY_DIR}/config.h" @ONLY)


find_package(CUDA REQUIRED)
LIST(APPEND CUDA_NVCC_FLAGS -std=c++11 -gencode arch=compute_30,code=sm_30)
SET(CUDA_PROPAGATE_HOST_FLAGS OFF)

# Expose sensorss public includes to other
# subprojects through cache variable.
set(SENSORS_INCLUDE_DIR
  "${CMAKE_CURRENT_SOURCE_DIR}/src/include"
  CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE
)

set(SENSORS_LIBRARY_NAME
  "${PROJECT_NAME}"
  CACHE INTERNAL "${PROJECT_NAME}: Target Library name" FORCE
)

include_directories(${SENSORS_INCLUDE_DIR})
aux_source_directory(${PROJECT_SOURCE_DIR}/src/cpp CXX_SOURCES)
file(GLOB CU_SOURCES "${PROJECT_SOURCE_DIR}/src/cuda/*.cu")

# targets for nVidia CUDA compiler
cuda_add_library(${SENSORS_LIBRARY_NAME} STATIC ${CXX_SOURCES} ${CU_SOURCES})

set_target_properties(${SENSORS_LIBRARY_NAME}
  PROPERTIES POSITION_INDEPENDENT_CODE ON
)

# install library in lib directory
install(TARGETS ${SENSORS_LIBRARY_NAME}
  EXPORT HpcTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR}" COMPONENT lib
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
)

install(DIRECTORY src/include/ DESTINATION "${INSTALL_INCLUDE_DIR}" COMPONENT dev)

# component unit tests
include(gmock)

if(${GMOCK_FOUND})
  set(PROJECT_UT_DIR ${PROJECT_SOURCE_DIR}/tests/ut)

  include_directories(${PROJECT_UT_DIR}/include)
  aux_source_directory(${PROJECT_UT_DIR} UT_SOURCES)

  enable_testing(true)

  cuda_add_executable(run_ut ${UT_SOURCES})
  target_link_libraries(run_ut ${SENSORS_LIBRARY_NAME} ${CUDA_LIBRARIES} ${GMOCK_LIBRARY_MAIN})
  add_test(run_ut run_ut)
endif()

