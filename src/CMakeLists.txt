cuda_add_executable(cuda_example cuda_main.cu )
cuda_add_library(modellib helpers.cu)
target_link_libraries(cuda_example modellib)
