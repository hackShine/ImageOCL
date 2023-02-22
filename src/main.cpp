#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>
#include "ImageOCL.h"

using namespace std;
using namespace cv;

int main() {
	ImageOCL imageOCL;

	imageOCL.getOCLDevice();
	const int vecSize = 10000;
	std::vector<int> vec1(vecSize), vec2(vecSize), out(vecSize);
	std::iota(vec1.begin(), vec1.end(), 0);
	std::iota(vec2.begin(), vec2.end(), 100);

	
	cv::Mat im1 = imread("./im1.png");
	cv::Mat im2 = imread("./im2.png");
	resize(im2, im2, { im1.cols, im2.rows });
	cv::Mat imOut(im1.rows, im1.cols, CV_8UC3);

	auto startTime = chrono::high_resolution_clock::now();
	imageOCL.blendImage(im1, im2, imOut, 0.5f, 0.5f);
	auto endTime = chrono::high_resolution_clock::now();
	cout << "Execution time: " << chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << " ms" << endl;

	cv::imshow("Out", imOut);
	cv::waitKey(0);

	return 0;
}