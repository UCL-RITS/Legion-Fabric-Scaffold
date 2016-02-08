#!/bin/bash -l
module unload compilers
module load compilers/gnu/4.9.2
module load cuda/7.5.18/gnu-4.9.2
mkdir -p build
cd build
cmake ..
make
test/catch
cd ..
