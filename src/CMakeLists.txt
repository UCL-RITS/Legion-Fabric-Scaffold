add_executable(mpi_example parallel_main.cpp )
add_library(modellib Model.cpp)
target_link_libraries(mpi_example modellib  ${MPI_C_LIBRARIES} ${MPI_CXX_LIBRARIES})
