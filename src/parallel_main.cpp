#include "Model.h"

#include <mpi.h>
#include <iostream>

int main(int argc, char **argv){

  int rank, size;


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

}
