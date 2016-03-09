#include <iostream>
#include "build.h"

const int thread_count=32;

int main(int argc, char **argv){

  int host_total=0;

  Builder b;

  std::cout << "Final result " << b.result() << std::endl;

}
