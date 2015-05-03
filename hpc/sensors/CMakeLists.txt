#Component sensors
configure_file(config.h.in "${CMAKE_CURRENT_BINARY_DIR}/config.h" @ONLY)

set(COMPONENT_NAME sensors)
message("step into component: ${COMPONENT_NAME}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/include)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/cpp COMPONENT_CPP_SOURCES)
file(GLOB COMPONENT_CUDA_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/cuda/*.cu")

# targets for nVidia CUDA compiler
cuda_add_library(${COMPONENT_NAME} STATIC ${COMPONENT_CPP_SOURCES} ${COMPONENT_CUDA_SOURCES})

# component tests
cuda_add_executable(test_sensors tests/test_sensors.cpp)
target_link_libraries(test_sensors ${COMPONENT_NAME} ${CUDA_LIBRARIES})

# set(${COMPONENT_NAME}_HEADERS_DIR src/include)
# file(GLOB_RECURSE ${COMPONENT_NAME}_HEADERS src/include/*)
# message("PUBLIC headers of ${COMPONENT_NAME}: ${${COMPONENT_NAME}_HEADERS}")
# set_target_properties(${COMPONENT_NAME} PROPERTIES
#  PUBLIC_HEADER "${${COMPONENT_NAME}_HEADERS}")

# install library in lib directory
install(TARGETS ${COMPONENT_NAME}
  EXPORT HpcTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR}" COMPONENT lib
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
#  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/hpc/${COMPONENT_NAME}" COMPONENT dev
  )

install(DIRECTORY src/include/ DESTINATION "${INSTALL_INCLUDE_DIR}")

