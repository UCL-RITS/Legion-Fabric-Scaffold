#ifndef ONCE_MODEL_H
#define ONCE_MODEL_H

class Model {
private:
    int rank;
    int mpi_size;
public:
    Model(int rank, int size);
    int result();
};

#endif // ONCE_MODEL_H
