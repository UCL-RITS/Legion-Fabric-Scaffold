#include "Model.h"
#include <omp.h>
#include <iostream>

int main(int argc, char **argv){

  int thread_count=32;
  int result=0;
  int sum=0;

  #pragma omp parallel private(result), reduction(+:sum)
  {
     #pragma omp for
     for (int i = 0; i < thread_count; ++i)
     {
         Model model(i, thread_count);
         result = model.result();
         sum = sum+result;
     }

     # pragma omp critical
     {
       std::cout << "Final result on thread " <<
         omp_get_thread_num() << " is " << sum << std::endl;
     }
  }

  std::cout << "Final result is " << sum << std::endl;

}
