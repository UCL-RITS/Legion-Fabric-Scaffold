#!/usr/bin/env bash
mkdir -p build
cd build
cmake ..
make
test/catch
mpirun -n 2 test/catch_mpi
mpirun -n 4 src/mpi_example
