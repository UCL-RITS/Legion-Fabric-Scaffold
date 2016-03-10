#include "Model.h"

int model(int rank, int size){
  return rank*rank;
}

/* No classes in OpenCL 1.2
Model::Model(int rank, int size):
  rank(rank), size(size){

  }

int Model::calculate(){
  return rank*rank;
}
*/
