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
};
