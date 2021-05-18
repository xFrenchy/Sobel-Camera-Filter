/*
-Anthony Dupont
-5/17/2021
-Sobel filter applied to a camera feed
*/

#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>

#include "functions.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	VideoCapture cap(0);	//default video camera

	if (!cap.isOpened()) {
		cout << "Could not open the video camera\n";
		cin.get();	//wait for any key press
		return -1;
	}

	string windowName = "Sobel Video Filter";
	namedWindow(windowName); // Create a window
	EFilter_Sobel status = EFilter_Sobel::rainbow;

	while (true) {
		EFilter_Sobel newStatus = userInput();
		if (newStatus != EFilter_Sobel::no_change) {
			status = newStatus;
		}

		Mat frame;
		bool bSuccess = cap.read(frame); // read a new frame from video

		//Breaking the while loop if the frames cannot be captured
		if (!bSuccess)
		{
			cout << "Video camera is disconnected\n";
			cin.get();
			break;
		}

		Mat image = applySobel(frame, status);
		
		imshow(windowName, image);
	}

	waitKey(0); // Wait for any keystroke in the window

	destroyWindow(windowName);

	return 0;
}