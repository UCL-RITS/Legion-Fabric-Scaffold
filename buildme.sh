#!/usr/bin/env bash
mkdir -p build
cd build
cmake ..
make
test/catch
test/catch_omp
src/omp_example
