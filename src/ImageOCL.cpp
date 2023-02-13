// Author: Anumod
// OpenCL.cpp : Defines the entry point for the application.
//

#include <stddef.h>
#include <assert.h>
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

#if 0
// Kernel code
const char* kernelAddVec = "                                                            \n" \
"#pragma OPENCL EXTENSION cl_khr_fp64 : enable                                          \n" \
"__kernel void vecAdd(__global double *v1, __global double *v2,                         \n" \
"                        __global double* out, unsigned int nElements)                  \n" \
"{                                                                                      \n" \
"   // Get global thread ID                                                             \n" \
"   int threadID = get_global_id(0);                                                    \n" \
"   if(threadID < nElements)                                                            \n" \
"       out[threadID] = v1[threadID] + v2[threadID];                                    \n" \
"}                                                                                      \n";
#else
const char* kernelAddVec = "\n" \
"__kernel void vecAdd(  __global int *a,                       \n" \
"                       __global int *b,                       \n" \
"                       __global int *c,                       \n" \
"                       const unsigned int n)                    \n" \
"{                                                               \n" \
"    //Get our global thread ID                                  \n" \
"    int id = get_global_id(0);                                  \n" \
"                                                                \n" \
"    //Make sure we do not go out of bounds                      \n" \
"    if (id < n)                                                 \n" \
"        c[id] = a[id] + b[id];                                  \n" \
"}                                                               \n" \
"\n";
#endif

int ImageOCL::add(vector<int>& vec1, vector<int>& vec2, std::vector<int>& outVec) {
    assert(vec1.size() == vec2.size());
    std::size_t nSamples = vec1.size();
    std::size_t samplesInBytes = nSamples * sizeof(int);

    // device I/O buffers
    cl_mem d_vec1;
    cl_mem d_vec2;
    cl_mem d_out;

    // host I/O
    int* h_vec1 = vec1.data();
    int* h_vec2 = vec2.data();
    int* h_out = outVec.data();

    // set OCL context, queue etc
    cl_platform_id oclPlatform;
    cl_device_id oclDeviceID;
    cl_context oclContext;
    cl_command_queue oclCmdQueue;
    cl_program oclProgram;
    cl_kernel oclKernel;

    // Number of work-groups
    std::size_t localSize = 64;
    // Number of work-items
    std::size_t globalSize = ceil(nSamples / (float)localSize) * localSize;

    // Get the platform ID
    cl_int err = clGetPlatformIDs(1, &oclPlatform, NULL);
    if (err != CL_SUCCESS) {
        cout << "Error while getting Platform ID" << endl;
        return -1;
    }

    // Get the device ID
    err = clGetDeviceIDs(oclPlatform, CL_DEVICE_TYPE_GPU, 1, &oclDeviceID, NULL);
        
    // Create a context
    oclContext = clCreateContext(NULL, 1, &oclDeviceID, NULL, NULL, &err);
    if (err != CL_SUCCESS) {
        cout << "Error while getting creating OCL context" << endl;
        return -1;
    }

    // Create command queue
    oclCmdQueue = clCreateCommandQueue(oclContext, oclDeviceID, NULL, &err);
    if (err != CL_SUCCESS) {
        cout << "Error while getting creating command queue" << endl;
        return -1;
    }

    // Create the program from source
    oclProgram = clCreateProgramWithSource(oclContext, 1, &kernelAddVec, NULL, &err);
    if (err != CL_SUCCESS) {
        cout << "Error while getting creating program" << endl;
        return -1;
    }

    // Build the source program
    clBuildProgram(oclProgram, 0, NULL, NULL, NULL, NULL);

    std::size_t len;
    clGetProgramBuildInfo(oclProgram, oclDeviceID, CL_PROGRAM_BUILD_LOG, 0, NULL, &len);

    std::vector<char> log(len);
    clGetProgramBuildInfo(oclProgram, oclDeviceID, CL_PROGRAM_BUILD_LOG, len, &log[0], NULL);

    cout << &log[0] << endl;

    // Create kernel
    oclKernel = clCreateKernel(oclProgram, "vecAdd", &err);
    if (err != CL_SUCCESS) {
        cout << "Error while creating kernel::: " << err << endl;
        return -1;
    }

    // Create device buffer for computation
    d_vec1 = clCreateBuffer(oclContext, CL_MEM_READ_ONLY, samplesInBytes, NULL, &err);
    if ((err == CL_SUCCESS) && (d_vec2 = clCreateBuffer(oclContext, CL_MEM_READ_ONLY, samplesInBytes, NULL, &err)));
    if ((err == CL_SUCCESS) && (d_out = clCreateBuffer(oclContext, CL_MEM_READ_WRITE, samplesInBytes, NULL, &err)));
    if (err != CL_SUCCESS) {
        cout << "Error while creating device buffer" << endl;
        return -1;
    }

    // Transfer input data to device
    err = clEnqueueWriteBuffer(oclCmdQueue, d_vec1, CL_TRUE, 0, samplesInBytes, h_vec1, 0, NULL, NULL);
    if (err != CL_SUCCESS) {
        cout << "Error while enqueue vec1" << endl;
        return -1;
    }

    err = clEnqueueWriteBuffer(oclCmdQueue, d_vec2, CL_TRUE, 0, samplesInBytes, h_vec2, 0, NULL, NULL);
    if (err != CL_SUCCESS) {
        cout << "Error while enqueue vec1" << endl;
        return -1;
    }

    // Set kernel arguements
    err = clSetKernelArg(oclKernel, 0, sizeof(cl_mem), &d_vec1);
    if (err != CL_SUCCESS) {
        cout << "Error while setting kernel arg for vec1" << endl;
        return -1;
    }

    err = clSetKernelArg(oclKernel, 1, sizeof(cl_mem), &d_vec2);
    if (err != CL_SUCCESS) {
        cout << "Error while setting kernel arg for vec2" << endl;
        return -1;
    }

    err = clSetKernelArg(oclKernel, 2, sizeof(cl_mem), &d_out);
    if (err != CL_SUCCESS) {
        cout << "Error while setting kernel arg for out" << endl;
        return -1;
    }

    err = clSetKernelArg(oclKernel, 3, sizeof(unsigned int), &nSamples);
    if (err != CL_SUCCESS) {
        cout << "Error while setting kernel arg for nSamples" << endl;
        return -1;
    }

    // Enqueue command to execute the kernel on device
    err = clEnqueueNDRangeKernel(oclCmdQueue, oclKernel, 1, NULL, &globalSize, &localSize, 0, NULL, NULL);
    if (err != CL_SUCCESS) {
        cout << "Error while enqueue execute command" << endl;
        return -1;
    }

    // Wait for completion of commands
    clFinish(oclCmdQueue);

    err = clEnqueueReadBuffer(oclCmdQueue, d_out, CL_TRUE, 0, samplesInBytes, h_out, 0, NULL, NULL);
    if (err != CL_SUCCESS) {
        cout << "Error while reading out buffer from device to host memory" << endl;
        return -1;
    }

    return 0;
}
