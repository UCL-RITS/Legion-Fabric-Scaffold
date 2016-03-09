// This file contains the "OpenCL Makefile" C code.
// We build and link an OpenCL library from our Model
// Then we link it to our main kernel.

#include "helpers.h"
#include <vector>

class Builder {
  public:
    Builder(cl_uint maxDevices =1,
            cl_uint maxPlatforms =1,
            cl_uint usedDevices = 1);
    int result();
  private:

    cl_uint             numPlatforms;
    cl_uint             numDevices;

    std::vector<cl_platform_id>    platforms;

        cl_context_properties*  properties ;


    std::vector<cl_device_id>       deviceIDs;




};
