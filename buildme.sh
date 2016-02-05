#!/bin/bash -l
module unload compilers
module unload mpi
module load compilers/gnu/4.9.2
module load mpi/openmpi/1.10.1/gnu-4.9.2
mkdir -p build
cd build
cmake ..
make
test/catch
mpirun -n 2 test/catch_mpi
mpirun -n 4 src/mpi_example
