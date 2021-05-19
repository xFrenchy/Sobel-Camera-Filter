#include <iostream>

#include "functions.h"
#include "config.h"

using namespace cv;

Mat rainbowSobel(Mat frame) {
	Mat grad, grad_x, grad_y, abs_grad_x, abs_grad_y;
	int ddepth = CV_16S;

	//Sobel(input array without grayscale, output array, depth of output image, dx, dy, ksize, scale, delta, bordertype)
	Sobel(frame, grad_x, ddepth, 1, 0, 1, 1, 0, BORDER_DEFAULT);
	Sobel(frame, grad_y, ddepth, 0, 1, 1, 1, 0, BORDER_DEFAULT);

	// converting back to CV_8U
	convertScaleAbs(grad_x, abs_grad_x);
	convertScaleAbs(grad_y, abs_grad_y);
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

	return grad;
}

Mat ProperSobel(Mat frame) {
	Mat src, src_gray, grad, grad_x, grad_y, abs_grad_x, abs_grad_y;
	int ddepth = CV_16S;

	// Remove noise by blurring with a Gaussian filter ( kernel size = 3 )
	GaussianBlur(frame, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

	// Convert the image to grayscale
	cvtColor(src, src_gray, COLOR_BGR2GRAY);

	//Sobel(input array in grayscale, output array, depth of output image, dx, dy, ksize, scale, delta, bordertype)
	Sobel(src_gray, grad_x, ddepth, 1, 0, 1, 1, 0, BORDER_DEFAULT);
	Sobel(src_gray, grad_y, ddepth, 0, 1, 1, 1, 0, BORDER_DEFAULT);

	// converting back to CV_8U
	convertScaleAbs(grad_x, abs_grad_x);
	convertScaleAbs(grad_y, abs_grad_y);
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

	return grad;
}

Mat colorSobel(Mat frame, RGB color) {
	//Apply sobel to current frame
	frame = ProperSobel(frame);

	//Create a mask of all the pixel that should represent the sobel outline
	Mat mask;
	inRange(frame, Scalar(10, 10, 10), Scalar(255, 255, 255), mask);

	//Turn it back into RGB
	Mat Cimage;
	cvtColor(frame, Cimage, COLOR_GRAY2RGB);

	//Change sobel outline from white to a specific color
	Cimage.setTo(Scalar(color.b, color.g, color.r), mask);	//opencb uses BGR
	return Cimage;
}

Mat applySobel(Mat frame, EFilter_Sobel status) {
	Mat image;
	switch (status) {
		case EFilter_Sobel::rainbow:
			image = rainbowSobel(frame);
			break;
		case EFilter_Sobel::proper:
			image = ProperSobel(frame);
			break;
		case EFilter_Sobel::rotate_all_colors: {
			std::string colorKey = G_color_dict_key[G_color_rotation];
			image = colorSobel(frame, G_color_map[colorKey]);
			G_color_rotation = ++G_color_rotation % (sizeof(G_color_dict_key) / sizeof(G_color_dict_key[0]));
			break;
		}
		case EFilter_Sobel::color: {
			std::string colorKey = G_color_dict_key[G_color_rotation];
			image = colorSobel(frame, G_color_map[colorKey]);
			break;
		}
		case EFilter_Sobel::green:
			image = colorSobel(frame, G_color_map["green"]);
			break;
		case EFilter_Sobel::red:
			image = colorSobel(frame, G_color_map["red"]);
			break;
		case EFilter_Sobel::gold:
			image = colorSobel(frame, G_color_map["gold"]);
			break;
		case EFilter_Sobel::purple:
			image = colorSobel(frame, G_color_map["purple"]);
			break;
		default:
			std::cout << "### CURRENT STATUS NOT SUPPORTED ###\n";
	}

	return image;
}

EFilter_Sobel userInput()
{
	int keyInput = waitKey(1);
	EFilter_Sobel status;
	switch (keyInput) {
		case ESC_KEY:
			std::cout << "Esc key is pressed by user. Stoppig the video\n";
			exit(0);
			break;
		case ONE_KEY:
			std::cout << "Switching to rainbow sobel\n";
			status = EFilter_Sobel::rainbow;
			break;
		case TWO_KEY:
			std::cout << "Switching to proper sobel\n";
			status = EFilter_Sobel::proper;
			break;
		case THREE_KEY:
			std::cout << "Switching to a color sobel\n";
			status = EFilter_Sobel::color;
			incrementGlobalColorIndex();
			break;
		case FOUR_KEY:
			std::cout << "Switching to all color rotation sobel\n";
			status = EFilter_Sobel::rotate_all_colors;
			break;
		case FIVE_KEY:
			std::cout << "Switching to green sobel\n";
			status = EFilter_Sobel::green;
			break;
		case SIX_KEY:
			std::cout << "Switching to red sobel\n";
			status = EFilter_Sobel::red;
			break;
		case SEVEN_KEY:
			std::cout << "Switching to gold sobel\n";
			status = EFilter_Sobel::gold;
			break;
		case EIGHT_KEY:
			std::cout << "Switching to purple sobel\n";
			status = EFilter_Sobel::purple;
			break;
		case -1:
			status = EFilter_Sobel::no_change;
			break;
		default:
			status = EFilter_Sobel::no_change;
			std::cout << char(keyInput) << " is not a valid input\n";
			break;
	}
	
	return status;
}

void incrementGlobalColorIndex()
{
	G_color_rotation = ++G_color_rotation % (sizeof(G_color_dict_key) / sizeof(G_color_dict_key[0]));
	return;
}
