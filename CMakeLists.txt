cmake_minimum_required(VERSION 2.8)
project(MPI_Scaffold)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_FLAGS)

include_directories(src)
include_directories(lib)

add_subdirectory(src)
add_subdirectory(test)
