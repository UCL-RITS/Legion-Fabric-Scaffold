cmake_minimum_required(VERSION 2.8)
project(MPI_Scaffold)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(CUDA)

list(APPEND CUDA_NVCC_FLAGS -arch sm_35;-std=c++11;--expt-extended-lambda)
include_directories(src)
include_directories(lib)

add_subdirectory(src)
add_subdirectory(test)
