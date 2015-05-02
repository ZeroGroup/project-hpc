cmake_minimum_required(VERSION 2.8)

if(${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
   message(FATAL_ERROR "You should not call cmake in-source. See README.md for details")
endif()

project(hpc)

SET(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR} )
message(${CMAKE_INSTALL_PREFIX})
message(${CMAKE_SOURCE_DIR})

find_package(CUDA REQUIRED)

LIST(APPEND CMAKE_CXX_FLAGS "--std=c++11 -Wall")
LIST(APPEND CUDA_NVCC_FLAGS -std=c++11 -gencode arch=compute_30,code=sm_30)
SET(CUDA_PROPAGATE_HOST_FLAGS OFF)

include_directories(${PROJECT_SOURCE_DIR}/src/include)

add_subdirectory(component_name)

#cuda_add_library(main_static STATIC src/main.cu OPTIONS -arch sm_30)

#install(TARGETS main_static DESTINATION lib)

#add_executable(main_exe src/main.cpp)
#target_link_libraries(main_exe main_static)

#target_link_libraries(main -lthrust)