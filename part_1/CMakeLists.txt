cmake_minimum_required(VERSION 3.0.0)

project(hw3 VERSION 0.1.0 LANGUAGES CXX_STANDARD)

set(MTM_FLAGS_DEBUG "-std=c99 --pedantic-errors -Wall -Werror")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDEBUG")

set(CMAKE_C_FLAGS ${MTM_FLAGS_DEBUG})

add_subdirectory("${PROJECT_SOURCE_DIR}/date")
add_subdirectory("${PROJECT_SOURCE_DIR}/provided")

add_executable(my_executable main.cpp)