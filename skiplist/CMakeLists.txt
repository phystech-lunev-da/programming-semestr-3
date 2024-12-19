
cmake_minimum_required(VERSION 3.24)

project(skiplistlab)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

enable_testing()

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include(CTest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${skiplistlab_SOURCE_DIR}/bin)

include_directories(${skiplistlab_SOURCE_DIR}/include)

add_executable(random_test src/random_test.cpp)

add_executable(skiplist_test src/skiplist_test.cpp)

add_executable(node_test src/node_test.cpp)

add_executable(iterator_test src/iterator_test.cpp)

# add_executable(test1 tests/test.cpp)
# target_link_libraries(test1 ${GTEST_LIBRARIES} gtest_main Threads::Threads)
