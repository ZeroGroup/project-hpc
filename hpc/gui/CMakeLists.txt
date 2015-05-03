# Component GUI
# GUI is CUDA/C-free

set(COMPONENT_NAME gui)
message("step into component: ${COMPONENT_NAME}")

#HACK!
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../sensors/src/include)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/include)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/cpp COMPONENT_CPP_SOURCES)

set(COMPONENT_LIBRARY_NAME gui)
add_library(${COMPONENT_LIBRARY_NAME} STATIC ${COMPONENT_CPP_SOURCES})

set(COMPONENT_EXECUTABLE_NAME hpc-gui)

add_executable(${COMPONENT_EXECUTABLE_NAME} src/main.cpp)
target_link_libraries(${COMPONENT_EXECUTABLE_NAME} ${COMPONENT_LIBRARY_NAME} sensors)

# component tests
add_executable(test_gui tests/test_gui.cpp)
target_link_libraries(test_gui ${COMPONENT_LIBRARY_NAME} sensors)

install(TARGETS ${COMPONENT_LIBRARY_NAME} ${COMPONENT_EXECUTABLE_NAME}
  EXPORT HpcTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR}" COMPONENT lib
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
)

install(DIRECTORY src/include/ DESTINATION "${INSTALL_INCLUDE_DIR}")
