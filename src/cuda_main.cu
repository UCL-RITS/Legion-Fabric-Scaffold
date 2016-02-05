#include <stdio.h>
#include <thrust/device_vector.h>

#include "helpers.h"
#include "Model.h"


__global__ void map (int * results);

const int thread_count=32;

int main(int argc, char **argv){


	dim3 tpb(thread_count,1,1);

  int host_total=0;

  thrust::device_vector<int> results(thread_count);
  thrust::device_vector<int> device_total(1);

  map <<< 1, tpb >>> (thrust::raw_pointer_cast(&results[0]));

  reduce_add <<< 1, tpb, tpb.x >>> (
          thrust::raw_pointer_cast(&results[0]),
          thrust::raw_pointer_cast(&device_total[0]));

  host_total = device_total[0];

  printf("Final Result: %i\n", host_total);

}

__global__ void map (int * results){
    Model *m= new Model(threadIdx.x, blockDim.x);
    results[threadIdx.x] = m->calculate();
}
