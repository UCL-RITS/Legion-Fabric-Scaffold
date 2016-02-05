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

    SECTION("Basic parallelism works"){

      int thread_count=32;
      int result;
      int sum;

      #pragma omp parallel private(result), reduction(+:sum)
      {
         #pragma omp for
         for (int i = 0; i < thread_count; ++i)
         {
             Model model(i, thread_count);
             result = model.result();
             sum = sum+result;
         }
      }
      REQUIRE (sum == 10416);
    }
}
