#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>
#include "ImageOCL.h"

using namespace std;

int main() {
	ImageOCL imageOCL;

	imageOCL.getOCLDevice();
	const int vecSize = 10000;
	std::vector<int> vec1(vecSize), vec2(vecSize), out(vecSize);
	std::iota(vec1.begin(), vec1.end(), 0);
	std::iota(vec2.begin(), vec2.end(), 100);

	auto startTime = chrono::high_resolution_clock::now();
	int ret = imageOCL.add(vec1, vec2, out);
	auto endTime = chrono::high_resolution_clock::now();
	cout << "Execution time: " << chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << " ms" << endl;
	if (ret == 0) {
		for (auto val : out) {
			cout << val << ", " << endl;
		}
	}
	else {
		cout << "Error while running OpenCL compute" << endl;
	}

	return 0;
}