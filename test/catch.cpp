// Next line tells CATCH we will use our own main function
#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include "Model.h"
#include <cmath>
#include <mpi.h>

int main(int argc, char * argv[]) {
    MPI_Init (&argc, &argv);
    int result = Catch::Session().run(argc, argv);
    MPI_Finalize();
    return result;
}




TEST_CASE( "Model can be instantiated and configured", "[Model]" ) {

    SECTION( "Model can be constructed" ) {
        Model model(0,1);
    }
}
