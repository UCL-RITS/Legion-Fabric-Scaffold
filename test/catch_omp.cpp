// Next line tells CATCH we will use our own main function
#define CATCH_CONFIG_RUNNER
#include <cmath>
#include "catch.hpp"
#include "Model.h"


int main(int argc, char * argv[]) {

    int result = Catch::Session().run(argc, argv);

    return result;
}


TEST_CASE ("MPI Tests"){
    int rank, size;

    REQUIRE(size==2); // test designed for a two-process situation
    SECTION("Basic communication works"){
       Model model(rank,size);
       REQUIRE(model.result()==rank*rank);
    }
}
