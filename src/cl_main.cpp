#include <iostream>
#include "build.h"

const int thread_count=32;

int main(int argc, char **argv){

  int host_total=0;

  Builder b;
  b.SelectDevice(0);
  b.DescribeDevice();

  b.Header("src/Model.h", "Model.h");

  b.Program("src/kernel.cl");
  b.Program("src/Model.cl");

  cl_kernel mykernel = b.CreateKernel("map");
  cl_int result;

  cl_uint work_count = b.GetDeviceCores(1);

  // Allocate output buffer on device

  cl_mem outputBuffer = b.AllocateDeviceMemory(CL_MEM_WRITE_ONLY, work_count);
  int results[work_count];

  // Bind buffer to kernel argument
  result = clSetKernelArg(mykernel, 0, sizeof(cl_mem), &outputBuffer);

  b.DispatchKernel(mykernel, work_count);

  b.DeviceToHost(outputBuffer, results, work_count);

  std::cout << "Final result " << results[10] << std::endl;

}
