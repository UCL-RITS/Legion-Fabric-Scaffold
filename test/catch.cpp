// Next line tells CATCH we will use our own main function
#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include <cmath>
#include "build.h"

int main(int argc, char * argv[]) {
    int result = Catch::Session().run(argc, argv);
    return result;
}




TEST_CASE( "Basic OpenCL compilation and dispatch", "[Builder]" ) {


    Builder b;
    b.SelectDevice(0);
    b.Program("test/catch_cl.cl");
    cl_kernel trivial = b.CreateKernel("trivial");

    SECTION( "Kernel can be run"){

      cl_mem outputBuffer = b.AllocateDeviceMemory(CL_MEM_WRITE_ONLY, 1);
      int results[1];

      // Bind buffer to kernel argument
      cl_int result = clSetKernelArg(trivial, 0, sizeof(cl_mem), &outputBuffer);

      b.DispatchKernel(trivial, 1);

      b.DeviceToHost(outputBuffer, results, 1);
      REQUIRE(result == CL_SUCCESS);
      REQUIRE(results[0]==7);
    }

}
