#!/usr/bin/env bash
mkdir -p build
cd build
cmake ..
make
test/catch
test/catch_cuda
src/cuda_example
