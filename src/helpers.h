#include <exception>
#include <string>
#include <iostream>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

inline void CL_CALLBACK onOpenCLError(const char *errinfo,  const void *private_info,
                               size_t cb, void *user_data)
{
    std::cout << "Error while creating context or working in this context :"
              << errinfo << std::endl;
}

class ClException: public std::exception
{
public:

  ClException(unsigned int type) throw():
    type(type), message("OpenCL Driver Exception of type"+std::to_string(type))
  {
  }
  virtual const char* what() const throw()
  {
    return message.c_str();
  }

  virtual ~ClException() throw() {};

private:
  unsigned int type;
  std::string message;
};
