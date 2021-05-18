#pragma once

#include <opencv2/opencv.hpp>

enum class EFilter_Sobel
{
	rainbow,
	proper,
	green,
	red,
	gold,
	purple,
	rotate_all_colors,
};

using namespace cv;

Mat rainbowSobel(Mat);
Mat ProperSobel(Mat);
Mat colorSobel(Mat, EFilter_Sobel);