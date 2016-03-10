// This file contains the "OpenCL Makefile" C code.
// We build and link an OpenCL library from our Model
// Then we link it to our main kernel.

#include "helpers.h"
#include <vector>

class Builder {
  public:
    Builder();
    void SelectDevice(cl_uint selectedDevice);
    void DescribeDevice();
    std::string GetDeviceName(cl_uint selectedDevice);
    cl_device_type GetDeviceType(cl_uint selectedDevice);
    cl_uint GetDeviceCores(cl_uint selectedDevice);
    cl_kernel CompileKernel(const std::string &kernel_path,
                            const std::string &kernel_name);
    cl_context GetContext(){ return context;}
    cl_command_queue GetQueue() {return commands;}
    void DispatchKernel(cl_kernel kernel, size_t work_count);
    cl_mem AllocateDeviceMemory(cl_mem_flags flags, size_t count,
      void * source_data = NULL);
    void DeviceToHost(cl_mem device_mem, void * host_mem, size_t count);
    cl_double Profile(cl_event event);
    
  private:

    void EnumerateDevices();



    cl_int result;

    cl_context_properties*  properties ;

    std::vector<cl_platform_id>    platforms;
    std::vector<cl_device_id>      deviceIDs;
    cl_command_queue commands;
    cl_context context;
    cl_device_id selected_device_id;
    cl_uint selected_device_index;
};
