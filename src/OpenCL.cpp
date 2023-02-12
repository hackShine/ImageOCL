// Author: Anumod
// OpenCL.cpp : Defines the entry point for the application.
//

#include<CL/cl.hpp>
#include "OpenCL.h"

using namespace std;
using namespace cl;

int detectOpenClPlatforms() {

    vector<Platform> platforms;
    Platform::get(&platforms);

    for (auto platform : platforms) {
        cout << "Using platform     :: " << platform.getInfo<CL_PLATFORM_NAME>() << endl;
        cout << "Platform vendor    :: " << platform.getInfo<CL_PLATFORM_VENDOR>() << endl;

        vector<cl::Device> devices;
        platform.getDevices(CL_DEVICE_TYPE_GPU | CL_DEVICE_TYPE_CPU, &devices);

        for (auto device : devices) {
            cout << "- Device name      :: " << device.getInfo<CL_DEVICE_NAME>() << endl;
            cout << "- Device vendor    :: " << device.getInfo<CL_DEVICE_VENDOR>() << endl;

            cout << "- Max comp units   :: " << device.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>() << endl;
            cout << "- Global Memory    :: " << device.getInfo<CL_DEVICE_GLOBAL_MEM_SIZE>() << endl;
            cout << "- Max Mem alloc    :: " << device.getInfo<CL_DEVICE_MAX_MEM_ALLOC_SIZE>() << endl;
            cout << "- Local memory     :: " << device.getInfo<CL_DEVICE_LOCAL_MEM_SIZE>() << endl;
            cout << "- Max Clk Freqz    :: " << device.getInfo<CL_DEVICE_MAX_CLOCK_FREQUENCY>() << endl;
            cout << "- Device available :: " << device.getInfo<CL_DEVICE_AVAILABLE>() << endl;
        }
    }
       
    
    return 0;
}

int main()
{
    cl_int err;
    cl_uint numPlatforms;

    detectOpenClPlatforms();

    err = clGetPlatformIDs(0, NULL, &numPlatforms);
    if (CL_SUCCESS == err)
        printf("\nDetected OpenCL platforms: %d", numPlatforms);
    else
        printf("\nError calling clGetPlatformIDs. Error code: %d", err);

    return 0;
}
