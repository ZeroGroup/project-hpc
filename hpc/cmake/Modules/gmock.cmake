# module gmock
# required cmake/environment variable:
#  - GMOCK_SOURCE_DIR - path to unzipped gmock+gtest framework sources
# defines following variables:
#  - GMOCK_INCLUDE_DIR
#  - GTEST_INCLUDE_DIR
#  - GMOCK_LIBRARY
#  - GMOCK_LIBRARY_MAIN
#  - GTEST_LIBRARY
#  - GMOCK_FOUND

set(GMOCK_FOUND "False")

if(NOT GMOCK_SOURCE_DIR)
  message(STATUS "CMake variable GMOCK_SOURCE_DIR not set, checking environment...")
  if(DEFINED ENV{GMOCK_SOURCE_DIR})
    message(STATUS "Environment variable GMOCK_SOURCE_DIR found.")
    set(GMOCK_SOURCE_DIR "$ENV{GMOCK_SOURCE_DIR}" CACHE PATH "Installation prefix for Google Mock.")
  else()
    message(STATUS "Missing variable GMOCK_SOURCE_DIR.")
    return()
  endif()
endif()

add_subdirectory(${GMOCK_SOURCE_DIR} ${CMAKE_BINARY_DIR}/gmock)

set(GMOCK_FOUND "True")

set(GMOCK_INCLUDE_DIR "${GMOCK_SOURCE_DIR}/include")
set(GTEST_INCLUDE_DIR "${GMOCK_SOURCE_DIR}/gtest/include")

set(GMOCK_LIBRARY "gmock")
set(GMOCK_LIBRARY_MAIN "gmock_main")
set(GTEST_LIBRARY "gtest")

set_property(TARGET ${GTEST_LIBRARY} APPEND_STRING PROPERTY COMPILE_FLAGS " -w -Wno-unused-local-typedefs")

include_directories(${GMOCK_INCLUDE_DIR} ${GTEST_INCLUDE_DIR})


