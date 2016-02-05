#include <iostream>

#include "Model.h"
#include <mpi.h>

Model::Model(
        int rank,
        int block_size)
    :
    rank(rank),
    block_size(block_size)
{
}

int Model::getRank(){
  return rank;
}
