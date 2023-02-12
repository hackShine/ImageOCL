#include <ImageOCL.h>
#include "gtest/gtest.h"

TEST(ImageOCL, TestMinOneDeviceAvailable) {
	ImageOCL iocl;
	ASSERT_TRUE(iocl.getOCLDevice().size() > 0);
}