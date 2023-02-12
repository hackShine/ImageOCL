cmake_minimum_required(VERSION 3.8)

project("ImageOCL_test")

# dependency paths
# google test
set(GTEST_INC_PATH ${CMAKE_CURRENT_LIST_DIR}/dependencies/gtest/include)
set(GTEST_LIB_PATH ${CMAKE_CURRENT_LIST_DIR}/dependencies/gtest/lib)
# opencl
set(OPENCL_INC_PATH ${CMAKE_CURRENT_LIST_DIR}/../libs/opencl/include)
set(OPENCL_STATIC_LIB ${CMAKE_CURRENT_LIST_DIR}/../libs/opencl/Debug/lib/x64)

# ImageOCL files to test
set(IOCL_INC_PATH ${CMAKE_CURRENT_LIST_DIR}/../src)
set(IOCL_SRC_FILES 
					${CMAKE_CURRENT_LIST_DIR}/../src/ImageOCL.cpp)

add_executable(IOCL_test
				"test_main.cpp"
				"test_devices.cpp"
				${IOCL_SRC_FILES})


target_include_directories( IOCL_test
							PRIVATE
							${GTEST_INC_PATH}
							${IOCL_INC_PATH}
							${OPENCL_INC_PATH})

target_link_libraries(IOCL_test
					${GTEST_LIB_PATH}/Debug/gtest.lib
					${OPENCL_STATIC_LIB}/OpenCL.lib)