#include "Model.h"
#include <mpi.h>
#include <iostream>

int main(int argc, char **argv){
  MPI_Init (&argc, &argv);
  int rank, size;
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &size);

  Model model(rank, size);
  int local_result = model.result();
  int result;

  MPI_Allreduce(
    &local_result,
    &result,
    1,
    MPI_INTEGER,
    MPI_SUM,
    MPI_COMM_WORLD);

  std::cout << "Final result" << result << std::endl;

  MPI_Finalize();
}
