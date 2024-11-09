
cmake_minimum_required(VERSION 3.24)

project(gridlab)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(CTest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${gridlab_SOURCE_DIR}/bin)

include_directories(${gridlab_SOURCE_DIR}/include)

add_library(lib src/grid.cpp)

add_executable(test1 tests/test1.cpp)
target_link_libraries(test1 PUBLIC lib)

add_executable(test2 tests/test2.cpp)
target_link_libraries(test2 PUBLIC lib)

add_executable(test3 tests/test3.cpp)
target_link_libraries(test3 PUBLIC lib)

add_test(NAME Test2 COMMAND test2)
add_test(NAME Test3 COMMAND test3)

enable_testing()