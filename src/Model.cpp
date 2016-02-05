#include <iostream>

#include "Model.h"

Model::Model(int threads)
    :
    rank(rank),
    size(size)
{

}

int Model::result(){
  return rank*rank;
}
