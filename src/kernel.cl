__kernel void map(global int* result){
  m = Model(get_global_id(0), get_global_size(0));
  return m.calculate();
}
