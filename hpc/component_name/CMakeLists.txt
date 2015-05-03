#Component component_name

set(COMPONENT_NAME component_name)

message("step into component: ${COMPONENT_NAME}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/include)

#component is a library
cuda_add_library(component_name src/cuda/component_name.cu OPTIONS -arch sm_30)

#component unit tests
cuda_add_executable(test_component_name_1 tests/test_component_name_1.cpp)
target_link_libraries(test_component_name_1 component_name)

# install library in lib/ directory
install(TARGETS component_name DESTINATION lib)

# install test executable in bin/ directory
install(TARGETS test_component_name_1 DESTINATION bin/tests/component_name)
