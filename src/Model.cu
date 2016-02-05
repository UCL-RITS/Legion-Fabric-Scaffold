#include <iostream>

#include "Model.h"

Model::Model(
        int rank,
        int block_size)
    :
    rank(rank),
    block_size(block_size)
{
}

__device__ int Model::calculate(){
  return rank*rank;
}
