#include <iostream>
#include <fstream>

#include "opencv2\opencv.hpp"


using namespace cv;
using namespace std;

int main(){

	VideoCapture cap(0); // open the default camera
	if (!cap.isOpened()) // check if we succeeded
		return -1;

	while (true)
	{
		Mat frame;
		cap >> frame;
		imshow("webcam", frame);
		if (waitKey(30) >= 0) break;
	}

	return 0;
}