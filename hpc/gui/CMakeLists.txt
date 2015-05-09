#######################################################################
# Component GUI - src directory CMakeLists.txt
# GUI code is CUDA/C-free
#
# target is executable: hpc-gui a.k.a ${GUI_EXECUTABLE_NAME}
#######################################################################

cmake_minimum_required(VERSION 2.8.11)

project(hpc-gui)
message("step into sub-project: ${PROJECT_NAME}")

set(GUI_EXECUTABLE_NAME ${PROJECT_NAME})

####
## CONFIGURE Qt5 LIBRARIES
####

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)

####
## ADD EXECUTABLE
####
aux_source_directory("${PROJECT_SOURCE_DIR}/src" CXX_SOURCES)
include_directories("${PROJECT_SOURCE_DIR}/src" ${SENSORS_INCLUDE_DIR})

add_executable(${GUI_EXECUTABLE_NAME} ${CXX_SOURCES})
target_link_libraries(${GUI_EXECUTABLE_NAME}
  ${SENSORS_LIBRARY_NAME}
  Qt5::Widgets
)

####
## INSTALLATION
####
install(TARGETS ${GUI_EXECUTABLE_NAME}
  EXPORT HpcTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR}" COMPONENT lib
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
)
