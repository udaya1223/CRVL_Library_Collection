/********************************************************
		Computer & Robot Vision Lab, KNU
		Programmed by: UKW
		2013.11.04.
********************************************************/

#pragma once

#include "opencv2/opencv.hpp" 
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

namespace crvldu{

}
typedef class crvlDisplayUtility{

public:
	crvlDisplayUtility(void);
	~crvlDisplayUtility();

	static void combineTwoSimilarImages(Mat &first, Mat &second, Mat &combined);
	static void viewImage(string windowName, Mat &image, int flag=0);
	static void viewAndSaveImage(string windowName, Mat &image, int flag=0, string savePath="");

private:

} CRVLDU;