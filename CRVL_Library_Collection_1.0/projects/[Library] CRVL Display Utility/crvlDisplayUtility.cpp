#include "crvlDisplayUtility.h"

crvlDisplayUtility::crvlDisplayUtility(void){

}

crvlDisplayUtility::~crvlDisplayUtility(void){
	
}

void crvlDisplayUtility::combineTwoSimilarImages(Mat& first, Mat& second, Mat& combineImg){
	combineImg = Mat(Size(first.cols*2, first.rows), first.type(), Scalar(0));
	first.copyTo(combineImg(Rect(0,0,first.cols, first.rows)));
	second.copyTo(combineImg(Rect(first.cols, 0, second.cols, second.rows)));
}

void crvlDisplayUtility::viewImage(string windowName, Mat &image, int flag){
	namedWindow(windowName, flag);
	imshow(windowName, image);
}

void crvlDisplayUtility::viewAndSaveImage(string windowName, Mat &image, int flag/* =0 */, string savePath/* ="" */){
	namedWindow(windowName, flag);
	imshow(windowName, image);
	if(savePath==""){
		savePath = windowName+".jpg";
	}
	imwrite(savePath, image);
}