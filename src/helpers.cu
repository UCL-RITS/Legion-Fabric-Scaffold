#include <stdio.h>

void handle_error( cudaError_t error, const char* message)
{
	if(error!=cudaSuccess) {
		fprintf(stderr,"ERROR: %s : %s\n",message,cudaGetErrorString(error));
		exit(-1);
	}
}

__global__ void reduce_add (int * array, int * result){

  // Here's how to do an O(ln N) reduce in pure
  // low-level CUDA.

	extern __shared__ int cache[];

	int thread_id=threadIdx.x;

	cache[thread_id]=array[thread_id];
	int reduction_index=blockDim.x/2;

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
