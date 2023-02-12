// Author: Anumod
// OpenCL.cpp : Defines the entry point for the application.
//

#include "ImageOCL.h"

using namespace std;
using namespace cl;

ImageOCL::ImageOCL() {

}

ImageOCL::~ImageOCL() {

}

vector<cl::Device> ImageOCL::getOCLDevice() {

    vector<Platform> platforms;
    Platform::get(&platforms);
    vector<cl::Device> devices;

    for (auto platform : platforms) {
        cout << "Using platform     :: " << platform.getInfo<CL_PLATFORM_NAME>() << endl;
        cout << "Platform vendor    :: " << platform.getInfo<CL_PLATFORM_VENDOR>() << endl;

        platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

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
    
    return devices;
}
