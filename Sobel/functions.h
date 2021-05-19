#pragma once
#ifndef FUNCTIONS_H

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
	color,
	rotate_all_colors,
	green,
	red,
	gold,
	purple,
	no_change,
};

struct RGB {
	int r, g, b;
	RGB() { r = 0; g = 0; b = 0; }
	RGB(int _r, int _g, int _b) { r = _r; g = _g; b = _b; }
};

cv::Mat rainbowSobel(cv::Mat);
cv::Mat ProperSobel(cv::Mat);
cv::Mat colorSobel(cv::Mat, RGB);
cv::Mat applySobel(cv::Mat, EFilter_Sobel);

EFilter_Sobel userInput();
void incrementGlobalColorIndex();

#endif // !FUNCTIONS_H