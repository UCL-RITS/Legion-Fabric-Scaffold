#include "Model.h"

__kernel void map(__global int* result){
  int local_result = model(get_global_id(0), get_global_size(0));
  result[get_global_id(0)]= local_result;
}
