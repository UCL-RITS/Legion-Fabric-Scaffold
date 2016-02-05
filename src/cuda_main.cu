#include <stdio.h>
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/reduce.h>
#include "Model.h"

const int thread_count=32;

int main(int argc, char **argv){

  int host_total=0;

	thrust::device_vector<int> results(thread_count);

	thrust::generate(results.begin(), results.end(),
		[]__device__() {
			return Model(threadIdx.x, thread_count).calculate();
		} );

  thrust::device_vector<int> device_total(1);

  host_total = thrust::reduce(results.begin(), results.end(), 0,
		thrust::plus<int>()
	);

  printf("Final Result: %i\n", host_total);

}
