/*
-Anthony Dupont
-5/17/2021
-Sobel filter applied to a camera feed
*/

#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>

#include "functions.h"

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

	double dWidth = cap.get(CAP_PROP_FRAME_WIDTH);
	double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT);

	string windowName = "Sobel Video Filter";
	namedWindow(windowName); // Create a window
	EFilter_Sobel status = EFilter_Sobel::rainbow;

	int colorRotation = 0;
	while (true) {
		//I want this switching to be better
		int keyInput = waitKey(1);
		switch (keyInput) {
			case ESC_KEY:
				cout << "Esc key is pressed by user. Stoppig the video" << endl;
				exit(0);
				break;
			case ONE_KEY:
				cout << "Switching to rainbow sobel\n";
				status = EFilter_Sobel::rainbow;
				break;
			case TWO_KEY:
				cout << "Switching to proper sobel\n";
				status = EFilter_Sobel::proper;
				break;
			case THREE_KEY:
				cout << "Switching to green sobel\n";
				status = EFilter_Sobel::green;
				break;
			case FOUR_KEY:
				cout << "Switching to red sobel\n";
				status = EFilter_Sobel::red;
				break;
			case FIVE_KEY:
				cout << "Switching to gold sobel\n";
				status = EFilter_Sobel::gold;
				break;
			case SIX_KEY:
				cout << "Switching to purple sobel\n";
				status = EFilter_Sobel::purple;
				break;
			case SEVEN_KEY:
				cout << "Switching to all color rotation sobel\n";
				status = EFilter_Sobel::rotate_all_colors;
				break;
			case -1:
				break;
			default:
				cout << char(keyInput) << " is not a valid input\n";
				break;
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

		Mat image;
		switch (status){
			case EFilter_Sobel::rainbow:
				image = rainbowSobel(frame);
				break;
			case EFilter_Sobel::proper:
				image = ProperSobel(frame);
				break;
			case EFilter_Sobel::green:
				image = colorSobel(frame, EFilter_Sobel::green);
				break;
			case EFilter_Sobel::red:
				image = colorSobel(frame, EFilter_Sobel::red);
				break;
			case EFilter_Sobel::gold:
				image = colorSobel(frame, EFilter_Sobel::gold);
				break;
			case EFilter_Sobel::purple:
				image = colorSobel(frame, EFilter_Sobel::purple);
				break;
			case EFilter_Sobel::rotate_all_colors: {
				EFilter_Sobel colors[] = { EFilter_Sobel::green, EFilter_Sobel::red, EFilter_Sobel::gold, EFilter_Sobel::purple };	//needs manual update, not good
				image = colorSobel(frame, colors[colorRotation]);
				colorRotation = ++colorRotation % (sizeof(colors) / sizeof(colors[0]));
				break;
			}
			default:
				cout << "### CURRENT STATUS NOT SUPPORTED ###\n";
		}
		
		imshow(windowName, image);

	}

	waitKey(0); // Wait for any keystroke in the window

	destroyWindow(windowName);

	return 0;
}