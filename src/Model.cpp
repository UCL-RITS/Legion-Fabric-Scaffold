#include <iostream>

#include "Model.h"

Model::Model(int rank, int size)
    :
    rank(rank),
    size(size)
{

}

int Model::result(){
  return rank*rank;
}
