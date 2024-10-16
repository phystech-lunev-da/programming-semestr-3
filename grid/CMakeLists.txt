
cmake_minimum_required(VERSION 3.24)

project(gridlab)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${grid_SOURCE_DIR}/bin)

include_directories(${grid_SOURCE_DIR}/include)

add_library(lib src/grid.cpp)
add_executable(gridlab src/main.cpp)
target_link_libraries(gridlab lib)