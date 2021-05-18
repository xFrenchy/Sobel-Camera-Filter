#pragma once

#include <opencv2/opencv.hpp>

#define ESC_KEY 27
#define ONE_KEY 49
#define TWO_KEY 50
#define THREE_KEY 51
#define FOUR_KEY 52
#define FIVE_KEY 53
#define SIX_KEY 54
#define SEVEN_KEY 55
#define EIGHT_KEY 56
#define NINE_KEY 57

enum class EFilter_Sobel
{
	rainbow,
	proper,
	green,
	red,
	gold,
	purple,
	rotate_all_colors,
	no_change,
};

using namespace cv;

Mat rainbowSobel(Mat);
Mat ProperSobel(Mat);
Mat colorSobel(Mat, EFilter_Sobel);
Mat applySobel(Mat, EFilter_Sobel);

EFilter_Sobel userInput();