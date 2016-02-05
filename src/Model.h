#ifndef ONCE_MODEL_H
#define ONCE_MODEL_H

class Model {
private:
    int rank;
    int block_size;
public:
    Model(int rank, int size);
    __device__ int calculate();
};

#endif // ONCE_MODEL_H
