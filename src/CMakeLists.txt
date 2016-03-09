add_executable (cl_main cl_main.cpp)
add_library (cl_build build.cpp)

configure_file(kernel.cl kernel.cl COPYONLY)
configure_file(Model.cl Model.cl COPYONLY)
target_link_libraries(cl_main cl_build ${OpenCL_LIBRARY})
