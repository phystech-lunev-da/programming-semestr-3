
cmake_minimum_required(VERSION 3.24)

project(probability)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${probability_SOURCE_DIR}/bin)

include_directories(${probability_SOURCE_DIR}/include)

add_library(prob_lib src/Dice.cpp src/ThreeDicePool.cpp src/BonusDice.cpp src/PenaltyDice.cpp src/DoubleDice.cpp)
add_executable(probability src/main.cpp)
target_link_libraries(probability prob_lib)