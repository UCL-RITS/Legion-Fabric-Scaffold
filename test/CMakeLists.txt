add_executable(catch catch.cpp)
add_executable(catch_omp catch_omp.cpp)
target_link_libraries(catch modellib)
target_link_libraries(catch_omp modellib)
