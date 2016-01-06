#include "opencv2\opencv.hpp"
#include <iostream>
#include <fstream>

#define START_IMG_NUM	0
#define END_IMG_NUM		2
#define IMAGE_FILE_PATH	"../../../data/Color Calibration/Set1"
#define WIN_SIZE		10

#define SHOW_DEBUG_IMAGES

using namespace cv;
using namespace std;

struct MouseParams{
	Mat img;
	vector<Point2f> cornerPoints;
	int imgNum;
	string windowName;
};

void mouse_callback(int event, int x, int y, int flags, void* param){

	//Check for the event Left mouse button press
	if (event != CV_EVENT_LBUTTONDOWN)	return;

	MouseParams* mp = (MouseParams*)param;
	Mat & colorFrame = mp->img;
	Mat frame;
	cvtColor(colorFrame, frame, CV_BGR2GRAY);

	vector<Point2f> corners(1, Point2f(x, y));
	cornerSubPix(frame, corners, Size(WIN_SIZE, WIN_SIZE), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
	printf("Refined Corner: %f %f\n", corners[0].x, corners[0].y);
	mp->cornerPoints.push_back(corners[0]);

	//Draw center point and ROI for viewing
	for (int i = 0; i < mp->cornerPoints.size(); i++){
		circle(colorFrame, mp->cornerPoints[i], 2, Scalar(0, 0, 255), -1);
	}

	imshow(mp->windowName, colorFrame);

	/*Point2f world;
	printf("Insert World Coordinates (x y):\n");
	cin >> world.x >> world.y;
	cout << world;*/

	//colorFrame.release();
	frame.release();
}



int main(){

	char szFilePath[256];

	Mat inputImg;

	for (int i = START_IMG_NUM; i <= END_IMG_NUM; i++){
	
		sprintf(szFilePath, "%s/IMG%04d.jpg", IMAGE_FILE_PATH, i);
		inputImg = imread(szFilePath, CV_LOAD_IMAGE_COLOR);

		if (!inputImg.data){
			printf("ERROR: Couldn't find the input image.\n");
			break;
		}

		// Find corner points of the chessboard using mouse click
		printf("\nDetecting Corner Points %d:\n", i);
		MouseParams imgParm;
		imgParm.img = inputImg.clone();
		imgParm.imgNum = i;
		sprintf(szFilePath, "Input Image %d", i);
		imgParm.windowName = szFilePath;
		namedWindow(imgParm.windowName, 1);
		imshow(imgParm.windowName, inputImg);
		setMouseCallback(imgParm.windowName, mouse_callback, (void*)&imgParm);

		char key = waitKey(0);
		if (key == 27) break;

		destroyWindow(imgParm.windowName);

		// Check all corners are detected
		if (imgParm.cornerPoints.size() != 4){
			printf("ERROR: Select four corners.\n");
			i--;
			continue;
		}


		waitKey(0);
	}


	







	/*vector<Point3i> rgbvalues;

	for (int i = 0; i < 10; i++){
		rgbvalues.push_back(Point3i(i, i*5, i*10));
	}

	FileStorage fs("test.yml", FileStorage::WRITE);

	fs << "Image1" << rgbvalues;

	fs.release();

	FileStorage fs2("test.yml", FileStorage::READ);

	vector<Point3i> rgbvalues2;

	fs2["Image1"] >> rgbvalues2;

	fs2.release();*/

	return 0;
}