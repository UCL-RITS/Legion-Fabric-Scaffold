cuda_add_executable(catch catch.cu)
cuda_add_executable(catch_cuda catch_cuda.cu)
target_link_libraries(catch modellib)
target_link_libraries(catch_cuda modellib)
