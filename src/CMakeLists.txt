cmake_minimum_required (VERSION 3.8)

set(OPENCL_STATIC_LIB ${CMAKE_CURRENT_LIST_DIR}/../libs/opencl/Debug/lib/x64)
set(OPENCL_INC_PATH ${CMAKE_CURRENT_LIST_DIR}/../libs/opencl/include)

set(OPENCV_INC_PATH ${CMAKE_CURRENT_LIST_DIR}/../thirdparty/opencv/include/)
set(OPENCV_LIB_PATH ${CMAKE_CURRENT_LIST_DIR}/../thirdparty/opencv/libs/debug/x64)

add_executable(ImageOCL 
                "ImageOCL.cpp" 
                "main.cpp")

target_include_directories(ImageOCL 
                            PRIVATE 
                            ${OPENCL_INC_PATH}
                            ${OPENCV_INC_PATH}
                            )

target_link_libraries(ImageOCL 
                        ${OPENCL_STATIC_LIB}/OpenCL.lib
                        ${OPENCV_LIB_PATH}/opencv_world470d.lib)
