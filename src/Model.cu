#include <iostream>

#include "Model.h"

__host__ __device__ Model::Model(
        int rank,
        int block_size)
    :
    rank(rank),
    block_size(block_size)
{
}

__host__ __device__ int Model::calculate(){
  return rank*rank;
}
