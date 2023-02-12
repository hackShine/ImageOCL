cmake_minimum_required (VERSION 3.8)

set(OPENCL_STATIC_LIB ${CMAKE_CURRENT_LIST_DIR}/../libs/opencl/Debug/lib/x64)
set(OPENCL_INC_PATH ${CMAKE_CURRENT_LIST_DIR}/../libs/opencl/include)

add_executable(ImageOCL 
                "ImageOCL.cpp" 
                "main.cpp")

target_include_directories(ImageOCL 
                            PRIVATE 
                            ${OPENCL_INC_PATH})

target_link_libraries(ImageOCL ${OPENCL_STATIC_LIB}/OpenCL.lib)
