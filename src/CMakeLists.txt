add_executable(omp_example parallel_main.cpp )
add_library(modellib Model.cpp)
target_link_libraries(omp_example modellib)
