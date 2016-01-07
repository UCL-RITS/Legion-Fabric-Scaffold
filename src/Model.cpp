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
  std::cout << "Rank " << rank << " of " << mpi_size << std::endl;

  std::cout << "Sum of all ranks: " << reduceRanks() << std::endl;
}

int Model::reduceRanks(){
  int result;
  MPI_Allreduce(
    &rank,
    &result,
    1,
    MPI_INTEGER,
    MPI_SUM,
    MPI_COMM_WORLD);
  return result;
}
