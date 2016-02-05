// Next line tells CATCH we will use our own main function
#define CATCH_CONFIG_RUNNER
#include <cmath>
#include "catch.hpp"
#include "Model.h"
#include <mpi.h>


int main(int argc, char * argv[]) {
    MPI_Init (&argc, &argv);
    int result = Catch::Session().run(argc, argv);
    MPI_Finalize();
    return result;
}


TEST_CASE ("MPI Tests"){
    int rank, size;
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    MPI_Comm_size (MPI_COMM_WORLD, &size);
    REQUIRE(size==2); // test designed for a two-process situation
    SECTION("Basic communication works"){
       Model model(rank,size);
       REQUIRE(model.result()==rank*rank);
    }
}
