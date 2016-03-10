#include "build.h"

#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>

void Builder::EnumerateDevices(){
  cl_uint numPlatforms;
  cl_uint numDevices;

  result = clGetPlatformIDs(0, NULL, &numPlatforms);
  platforms.resize(numPlatforms);
  result |= clGetPlatformIDs(numPlatforms, &platforms[0], NULL);

  std::cout << "Found " << numPlatforms << " platforms." << std::endl;

  if(result != CL_SUCCESS) throw ClException(1) ;

  result = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_ALL, 0, NULL, &numDevices);
  deviceIDs.resize(numDevices);
  result |= clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_ALL, numDevices,
    &deviceIDs[0], NULL);

  std::cout << "Found " << numDevices << " devices." << std::endl;

  if(result != CL_SUCCESS) throw ClException(2);

}

cl_device_type Builder::GetDeviceType(cl_uint selectedDevice){

  cl_device_type deviceType;

  result = clGetDeviceInfo(deviceIDs[selectedDevice],
    CL_DEVICE_TYPE, sizeof(cl_device_type),
    &deviceType, NULL);

  if(result != CL_SUCCESS)
  {
        throw ClException(5);
  }

  return deviceType;
}

cl_uint Builder::GetDeviceCores(cl_uint selectedDevice){
  cl_uint core_count;
  result = clGetDeviceInfo(deviceIDs[selectedDevice],
    CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint),
    &core_count, NULL);

  if(result != CL_SUCCESS)
  {
        throw ClException(5);
  }

  return core_count;
}

std::string Builder::GetDeviceName(cl_uint selectedDevice){
  size_t deviceNameLength;
  result |= clGetDeviceInfo(deviceIDs[selectedDevice], CL_DEVICE_NAME,
    0, NULL, &deviceNameLength
  );

  char * deviceNameBuffer = new char[deviceNameLength];

  result |= clGetDeviceInfo(deviceIDs[selectedDevice], CL_DEVICE_NAME,
    deviceNameLength, deviceNameBuffer, NULL);

  std::string deviceName(deviceNameBuffer);
  delete[] deviceNameBuffer;

  if(result != CL_SUCCESS)
  {
      throw ClException(5);
  }

  return deviceName; // RVO default move semantics
}

void Builder::DescribeDevice(){

  std::string deviceTypeString;

  cl_device_type deviceType = GetDeviceType(selected_device_index);

  switch(deviceType)
  {
      case CL_DEVICE_TYPE_CPU:
          deviceTypeString = "Processor";
          break;
      case CL_DEVICE_TYPE_GPU:
          deviceTypeString = "Graphics card";
          break;
      case CL_DEVICE_TYPE_ACCELERATOR:
          deviceTypeString = "Accelerator";
          break;
      default:
          deviceTypeString = "NONE";
          break;
  }

  std::cout << "Selected Device: "
            << GetDeviceName(selected_device_index)
            << " ( " << deviceTypeString << " with "
            << GetDeviceCores(selected_device_index) << " cores )"
            << std::endl;

}

void Builder::SelectDevice(cl_uint selectedDevice){

  selected_device_index = selectedDevice;
  selected_device_id = deviceIDs[selectedDevice];

  cl_command_queue_properties commandQueueProperties = CL_QUEUE_PROFILING_ENABLE;
  context = clCreateContext(properties, 1, &selected_device_id,
    &onOpenCLError, NULL, &result);

  if(result != CL_SUCCESS) throw ClException(3);

  // build command queue
  commands = clCreateCommandQueue(context,
    selected_device_id,
    commandQueueProperties, &result);
  if(result != CL_SUCCESS) throw ClException(4);

}

cl_kernel Builder::CompileKernel(const std::string &kernel_path,
                                 const std::string &kernel_name){
    // Slurp kernel file
    std::ifstream kernel_file(kernel_path);
    std::stringstream buffer;
    buffer << kernel_file.rdbuf();
    const char * buffer_contents = buffer.str().c_str();

    cl_program program = clCreateProgramWithSource(context, 1,
      &buffer_contents, NULL, &result);
    if(result != CL_SUCCESS) exit(5);

    result = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    if(result != CL_SUCCESS)
    {
      size_t log_length;

      clGetProgramBuildInfo(program, selected_device_id, CL_PROGRAM_BUILD_LOG,
        0, NULL, &log_length
      );

      char build_log[log_length];

      clGetProgramBuildInfo(program, selected_device_id, CL_PROGRAM_BUILD_LOG,
          log_length, build_log, NULL);

      std::cout << "Build log" << std::endl;
      std::cout << build_log << std::endl;
    }

    cl_kernel chol_gpu;

    chol_gpu = clCreateKernel(program, kernel_name.c_str(), &result);
    if(result != CL_SUCCESS) throw ClException(7);

    return chol_gpu;
}

void Builder::DispatchKernel(cl_kernel kernel, size_t work_count){

  cl_event  kernelExecEvent;

  result = clEnqueueNDRangeKernel(commands, kernel, 1, NULL, &work_count, NULL,
     0, NULL, &kernelExecEvent);

  clWaitForEvents(1, &kernelExecEvent);
  if(result != CL_SUCCESS) throw ClException(13);

  std::cout << "Kernel completed in " << Profile(kernelExecEvent)
            << " ms" << std::endl;
}

cl_double Builder::Profile(cl_event event){
  cl_ulong start = 0, end = 0;

  clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START,
    sizeof(cl_ulong), &start, NULL);
  clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END,
    sizeof(cl_ulong), &end, NULL);

  return (cl_double)(end - start)*(cl_double)(1e-09);
}

cl_mem Builder::AllocateDeviceMemory(cl_mem_flags flags, size_t count,
  void * source_data){
    cl_mem data = clCreateBuffer(context, flags, count, source_data, &result);
    if(result != CL_SUCCESS) throw ClException(8);
    return data;
}

void Builder::DeviceToHost(cl_mem device_mem, void* host_mem, size_t count){

  cl_event readResultsEvent;
  clEnqueueReadBuffer(commands, device_mem, CL_TRUE, 0,
    count, host_mem, 0, NULL, &readResultsEvent);

  clWaitForEvents(1, &readResultsEvent);

  if(result != CL_SUCCESS) throw ClException(14);
  std::cout << "Device to Host copy took " << Profile(readResultsEvent)
            << " ms" << std::endl;
}

Builder::Builder():
  properties(NULL),
  platforms(0),
  deviceIDs(0)
{
  EnumerateDevices();


}
