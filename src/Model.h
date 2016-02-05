#ifndef ONCE_MODEL_H
#define ONCE_MODEL_H

class Model {
private:
    int rank;
    int block_size;
public:
    Model(int rank, int size);
    int getRank();
};

#endif // ONCE_MODEL_H
