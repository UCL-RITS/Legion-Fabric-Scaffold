#include <iostream>

#include "Model.h"
#include <mpi.h>

Model::Model(
        int rank,
        int mpi_size)
    :
    rank(rank),
    mpi_size(mpi_size)
{

}

int Model::result(){
  return rank*rank;
}
