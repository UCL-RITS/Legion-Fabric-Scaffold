add_executable (catch_cl catch.cpp)


configure_file(catch_cl.cl catch_cl.cl COPYONLY)
target_link_libraries(catch_cl cl_build ${OpenCL_LIBRARY})
