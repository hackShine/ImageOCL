# CMakeList.txt : CMake project for OpenCL, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(OPENCL_STATIC_LIB ${CMAKE_CURRENT_LIST_DIR}/../libs/opencl/Debug/lib/x64)
set(OPENCL_INC_PATH ${CMAKE_CURRENT_LIST_DIR}/../libs/opencl/include)


# Add source to this project's executable.
add_executable (ImageOCL "OpenCL.cpp" "OpenCL.h")

target_include_directories(ImageOCL PRIVATE ${OPENCL_INC_PATH})
target_link_libraries(ImageOCL ${OPENCL_STATIC_LIB}/OpenCL.lib)

# TODO: Add tests and install targets if needed.
