#ifndef ONCE_MODEL_H
#define ONCE_MODEL_H

class Model {
private:
    int rank;
    int block_size;
public:

    __host__ __device__ Model(int rank, int size);
    __host__ __device__ int calculate();
};

//Because linked-libraries for Cuda objects don't work
// for Compute Capability < 5.0
// (the latest Maxwell architecture launched this year)
// we need to directly include the model definition code as well as the header
#include "Model.cu"

#endif // ONCE_MODEL_H
