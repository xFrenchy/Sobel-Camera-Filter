#include <iostream>

#include "functions.h"

Mat rainbowSobel(Mat frame) {
	Mat grad, grad_x, grad_y, abs_grad_x, abs_grad_y;
	int ddepth = CV_16S;

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

	Sobel(src_gray, grad_x, ddepth, 1, 0, 1, 1, 0, BORDER_DEFAULT);
	Sobel(src_gray, grad_y, ddepth, 0, 1, 1, 1, 0, BORDER_DEFAULT);

	// converting back to CV_8U
	convertScaleAbs(grad_x, abs_grad_x);
	convertScaleAbs(grad_y, abs_grad_y);
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

	return grad;
}

Mat colorSobel(Mat frame, EFilter_Sobel color) {
	frame = ProperSobel(frame);
	Mat mask;
	inRange(frame, Scalar(10, 10, 10), Scalar(255, 255, 255), mask);
	Mat Cimage;
	cvtColor(frame, Cimage, COLOR_GRAY2RGB);
	int maskColor[3];
	switch (color) {
		case EFilter_Sobel::green:
			maskColor[0] = 57;
			maskColor[1] = 255;
			maskColor[2] = 20;
			break;
		case EFilter_Sobel::red:
			maskColor[0] = 255;
			maskColor[1] = 51;
			maskColor[2] = 51;
			break;
		case EFilter_Sobel::gold:
			maskColor[0] = 255;
			maskColor[1] = 255;
			maskColor[2] = 51;
			break;
		case EFilter_Sobel::purple:
			maskColor[0] = 204;
			maskColor[1] = 153;
			maskColor[2] = 255;
			break;
	}

	//For debuggin of pixel values
	/*
	uint8_t* pixelPtr = (uint8_t*)frame.data;
	int cn = frame.channels();
	Scalar_<uint8_t> bgrPixel;

	for (int i = 0; i < frame.rows; i++)
	{
		for (int j = 0; j < frame.cols; j++)
		{
			bgrPixel.val[0] = pixelPtr[i * frame.cols * cn + j * cn + 0]; // B
			bgrPixel.val[1] = pixelPtr[i * frame.cols * cn + j * cn + 1]; // G
			bgrPixel.val[2] = pixelPtr[i * frame.cols * cn + j * cn + 2]; // R

			// do something with BGR values...
			std::cout << "[" << +bgrPixel.val[0] << ", " << +bgrPixel.val[1] << ", " << +bgrPixel.val[2] << "]\n";
		}
		std::cout << "End of column\n\n";
	}*/

	Cimage.setTo(Scalar(maskColor[2], maskColor[1], maskColor[0]), mask);	//opencb uses BGR
	return Cimage;
}