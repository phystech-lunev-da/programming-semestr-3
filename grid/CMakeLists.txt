
cmake_minimum_required(VERSION 3.24)

project(gridlab)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

enable_testing()
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${gridlab_SOURCE_DIR}/bin)

include_directories(${gridlab_SOURCE_DIR}/include)

add_executable(test1 tests/test1.cpp)
target_link_libraries(test1 ${GTEST_LIBRARIES} gtest_main Threads::Threads)

add_executable(test2 tests/test2.cpp)
target_link_libraries(test2 ${GTEST_LIBRARIES} gtest_main Threads::Threads)

add_executable(test3 tests/test3.cpp)
target_link_libraries(test3 ${GTEST_LIBRARIES} gtest_main Threads::Threads)

add_executable(sampletest tests/test.cpp)
target_link_libraries(sampletest ${GTEST_LIBRARIES} gtest_main Threads::Threads)

add_test(
    NAME sampletest
    COMMAND sampletest
)