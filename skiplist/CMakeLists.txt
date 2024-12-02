
cmake_minimum_required(VERSION 3.24)

project(skiplistlab)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(CTest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${skiplistlab_SOURCE_DIR}/bin)

include_directories(${skiplistlab_SOURCE_DIR}/include)

enable_testing()