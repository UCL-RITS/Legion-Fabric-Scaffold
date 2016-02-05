// Next line tells CATCH we will use our own main function
#define CATCH_CONFIG_RUNNER
#include <cmath>
#include <thrust/device_vector.h>
#include "catch.hpp"
#include "Model.h"
#include "helpers.h"


int main(int argc, char * argv[]) {
    int result = Catch::Session().run(argc, argv);
    return result;
}

__global__ void threadnumber (int * results){
    results[threadIdx.x] = threadIdx.x;
}


TEST_CASE ("CUDA Tests"){

    SECTION("Basic cuda dispatch works"){


      const int thread_count=32;
      dim3 tpb(thread_count,1,1);

      int* device_results=0;
      int host_results[thread_count];

      handle_error(cudaMalloc( &device_results,
            thread_count*sizeof( int ) ), "Allocate device samples");

      threadnumber <<< 1, tpb >>> (device_results);

      handle_error(cudaMemcpy(&host_results,
          device_results, sizeof(int)*thread_count,
          cudaMemcpyDeviceToHost), "Retrieve result");

      for (unsigned int i=0; i<thread_count; i++) {
        REQUIRE(host_results[i]==i);
      }
    }

    SECTION("Thrust pointer cuda dispatch works"){


      const int thread_count=32;
      dim3 tpb(thread_count,1,1);

      thrust::device_vector<int> device_results(thread_count);
      thrust::host_vector<int> host_results(thread_count);

      threadnumber <<< 1, tpb >>> (thrust::raw_pointer_cast(&device_results[0]));

      host_results=device_results;

      for (unsigned int i=0; i<thread_count; i++) {
        REQUIRE(host_results[i]==i);
      }
    }

    SECTION("Thrust dispatch works"){

      const int thread_count=32;
      thrust::device_vector<int> device_results(thread_count);

    	thrust::generate(device_results.begin(), device_results.end(),
    		[]__device__() {
    			return threadIdx.x;
    		} );

      thrust::host_vector<int> host_results(thread_count);

      host_results=device_results;

      for (unsigned int i=0; i<thread_count; i++) {
        REQUIRE(host_results[i]==i);
      }
    }
}
