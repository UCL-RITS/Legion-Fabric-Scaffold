#include "build.h"

#include <cstring>
#include <vector>

Builder::Builder(cl_uint maxDevices,
                 cl_uint maxPlatforms,
                 cl_uint usedDevices):
  properties(0),
  platforms(maxPlatforms),
  deviceIDs(maxDevices)
{

  cl_int result;

  cl_command_queue_properties commandQueueProperties = CL_QUEUE_PROFILING_ENABLE;

  result = clGetPlatformIDs(maxPlatforms, &platforms[0], &numPlatforms);

  if(result != CL_SUCCESS) throw ClException(1) ;

  result = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_GPU, maxDevices,
    &deviceIDs[0], &numDevices);
  if(result != CL_SUCCESS) throw ClException(2);

  cl_context context = clCreateContext(properties, usedDevices, &deviceIDs[0],
    &onOpenCLError, NULL, &result);
  if(result != CL_SUCCESS) throw ClException(3);

  // build command queue
  cl_command_queue commands = clCreateCommandQueue(context, deviceIDs[0],
    commandQueueProperties, &result);
  if(result != CL_SUCCESS) throw ClException(4);

  DeviceDesc device_desc;
  device_desc.deviceId = deviceIDs[0];
  size_t actualSize;
  result = clGetDeviceInfo(deviceIDs[0], CL_DEVICE_TYPE, sizeof(cl_device_type),
    &device_desc.deviceType, &actualSize);


  switch(device_desc.deviceType)
  {
      case CL_DEVICE_TYPE_CPU:
          device_desc.deviceTypeString = "Processor";
          break;
      case CL_DEVICE_TYPE_GPU:
          device_desc.deviceTypeString = "Graphics card";
          break;
      case CL_DEVICE_TYPE_ACCELERATOR:
          device_desc.deviceTypeString = "Accelerator";
          break;
      default:
          device_desc.deviceTypeString = "NONE";
          break;
  }


  size_t deviceNameLength = 4096;
  char* tempDeviceName = (char*)malloc(4096);
  result |= clGetDeviceInfo(deviceIDs[0], CL_DEVICE_NAME, deviceNameLength,
    tempDeviceName, &actualSize);

  if(result == CL_SUCCESS){
      device_desc.deviceName = (char*)malloc(actualSize);
      std::memcpy(device_desc.deviceName, tempDeviceName, actualSize);
      free(tempDeviceName);
  }

  if(result != CL_SUCCESS)
  {
      printf("Error while getting device info\n");
      exit(0);
  }

  printf("%s: %s\n", device_desc.deviceTypeString,device_desc.deviceName);

}

int Builder::result(){
  return 0;
}
