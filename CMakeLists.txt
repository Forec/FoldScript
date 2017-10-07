cmake_minimum_required(VERSION 3.8)
project(FoldScript)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_COMPILER "clang++")
add_compile_options(-std=c++14)

message(STATUS "Project: Fold Script")
message(STATUS "Project Directory: ${PROJECT_SOURCE_DIR}")

set(BUILD_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
set(LIBRARY_OUTPUT_PATH ${BUILD_OUTPUT_PATH}/lib)
set(EXECUTABLE_OUTPUT_PATH ${BUILD_OUTPUT_PATH}/bin)

add_subdirectory(src)
add_subdirectory(tests)
