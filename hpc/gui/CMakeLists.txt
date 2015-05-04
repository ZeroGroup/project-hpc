#######################################################################
# Component GUI
# GUI code is CUDA/C-free
#
# targets are executable `hpc-gui` and static library `libgui.a`
#######################################################################

cmake_minimum_required(VERSION 2.8.11)

project(hpc-gui)
message("step into sub-project: ${PROJECT_NAME}")

set(GUI_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/include)

include_directories(${GUI_INCLUDE_DIR} ${SENSORS_INCLUDE_DIR})
aux_source_directory(${PROJECT_SOURCE_DIR}/src/cpp CXX_SOURCES)

set(GUI_LIBRARY_NAME ${PROJECT_NAME}-static)
add_library(${GUI_LIBRARY_NAME} STATIC ${CXX_SOURCES})

# Required on Unix OS family to be able to be linked into shared libraries.
set_target_properties(${GUI_LIBRARY_NAME}
  PROPERTIES POSITION_INDEPENDENT_CODE ON
)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)

set(GUI_EXECUTABLE_NAME ${PROJECT_NAME})

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${GUI_LIBRARY_NAME} ${SENSORS_LIBRARY_NAME} Qt5::Widgets)

# component tests
add_executable(test_gui tests/test_gui.cpp)
target_link_libraries(test_gui ${GUI_LIBRARY_NAME} ${SENSORS_LIBRARY_NAME})

install(TARGETS ${GUI_LIBRARY_NAME} ${GUI_EXECUTABLE_NAME}
  EXPORT HpcTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR}" COMPONENT lib
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
)

install(DIRECTORY src/include/ DESTINATION "${INSTALL_INCLUDE_DIR}")
