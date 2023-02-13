// Author: Anumod
// OpenCL.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <vector>
#include <Cl/cl.hpp>

class ImageOCL {
public:
	ImageOCL();
	virtual ~ImageOCL();

	std::vector<cl::Device> getOCLDevice();

	int add(std::vector<int>& vec1, std::vector<int>& vec2, std::vector<int>& out);
};
