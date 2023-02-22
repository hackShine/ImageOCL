// Author: Anumod
// OpenCL.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <vector>
#include <Cl/cl.hpp>
#include <opencv2/opencv.hpp>

typedef unsigned char uchar_t;

class ImageOCL {
public:
	ImageOCL();
	virtual ~ImageOCL();

	std::vector<cl::Device> getOCLDevice();

	int add(std::vector<uchar_t>& vec1, std::vector<uchar_t>& vec2, std::vector<uchar_t>& out, float alpha1 = 1.f, float alpha2 = 1.f);
	cv::Mat blendImage(cv::Mat& img1, cv::Mat& img2, cv::Mat& out, float alpha1, float alpha2);
};
