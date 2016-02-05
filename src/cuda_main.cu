#include <stdio.h>
#include "helpers.h"

__global__ void map (int * results);
__global__ void reduce (int * array, int * result);


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
  reduce <<< 1, tpb >>> (results, device_total);

  handle_error(cudaMemcpy(&host_total,
      device_total, sizeof(int),cudaMemcpyDeviceToHost), "Retrieve result");

  printf("Final Result: %i\n", host_total);

}

__global__ void map (int * results){
    results[threadIdx.x] = threadIdx.x;
}

__global__ void reduce (int * array, int * result){

  // Here's how to do an O(ln N) reduce in pure
  // low-level CUDA.

	__shared__ int cache[thread_count];
	int thread_id=threadIdx.x;

	cache[thread_id]=array[thread_id];
	int reduction_index=thread_count/2;

  __syncthreads();

  while (reduction_index!=0){
		if (thread_id<reduction_index){
			cache[thread_id]+=cache[thread_id+reduction_index];
		}
		__syncthreads();
		reduction_index/=2;
	}

  if (thread_id==0) {
		*result=cache[0];
	}
}
