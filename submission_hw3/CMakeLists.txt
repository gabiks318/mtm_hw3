cmake_minimum_required(VERSION 3.0.0)

project(hw3 VERSION 0.1.0)

set(MTM_FLAGS_DEBUG "-std=c++11 --pedantic-errors -Wall -Werror -L.")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDEBUG")

set(CMAKE_CXX_FLAGS ${MTM_FLAGS_DEBUG})

add_subdirectory("${PROJECT_SOURCE_DIR}/partA")
add_subdirectory("${PROJECT_SOURCE_DIR}/partB")
add_subdirectory("${PROJECT_SOURCE_DIR}/partC")
add_subdirectory("${PROJECT_SOURCE_DIR}/provided")
add_subdirectory("${PROJECT_SOURCE_DIR}/tests")




add_executable(ex3 dry.cpp)
