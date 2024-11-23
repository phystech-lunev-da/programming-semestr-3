
cmake_minimum_required(VERSION 3.24)

project(gridlab)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(CTest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${gridlab_SOURCE_DIR}/bin)

include_directories(${gridlab_SOURCE_DIR}/include)

add_executable(test1 tests/test1.cpp)

add_executable(test2 tests/test2.cpp)

add_executable(test3 tests/test3.cpp)

add_test(NAME Test2 COMMAND test2)
add_test(NAME Test3 COMMAND test3)

enable_testing()