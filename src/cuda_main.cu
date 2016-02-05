#include <stdio.h>
#include "helpers.h"
#include "Model.h"


__global__ void map (int * results);

const int thread_count=32;

int main(int argc, char **argv){


	dim3 tpb(thread_count,1,1);

  int* results=0;
  int* device_total=0;
  int host_total=0;

  handle_error(cudaMalloc( &results,
      thread_count*sizeof( int ) ), "Allocate device samples");

  handle_error(cudaMalloc( &device_total,
      sizeof(int)), "Allocate result");

  map <<< 1, tpb >>> (results);
  reduce_add <<< 1, tpb, tpb.x >>> (results, device_total);

  handle_error(cudaMemcpy(&host_total,
      device_total, sizeof(int), cudaMemcpyDeviceToHost), "Retrieve result");

  printf("Final Result: %i\n", host_total);

}

__global__ void map (int * results){
    Model *m= new Model(threadIdx.x, blockDim.x);
    results[threadIdx.x] = m->calculate();
}
