#!/bin/bash -l
module unload compilers
module load compilers/gnu/4.9.2
mkdir -p build
cd build
cmake ..
make
test/catch
test/catch_omp
src/omp_example
