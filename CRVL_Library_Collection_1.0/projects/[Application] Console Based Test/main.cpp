#include "opencv2\opencv.hpp"

#include "crvlDisplayUtility.h"
#include "crvlRankTransformer.h"
#include "crvlVolumeCalculator.h"

using namespace cv;
using namespace std;

#define WINDOW_SIZE 7

//int main(){
//
//	/*Mat img = imread("../../../data/test1.ppm", CV_LOAD_IMAGE_COLOR);
//
//	if (!img.data){
//		printf("Input image not found..!!\n");
//		return 0;
//	}
//
//	CRVLDU::viewImage("Input Image", img);
//
//	Mat outPut;
//	crvlRankTransformer rankT;
//	if (rankT.doRankTransform(img, outPut, WINDOW_SIZE)){
//		Mat rankImg = rankT.getRankTransformImage(outPut, WINDOW_SIZE);
//		CRVLDU::viewAndSaveImage("Rank Image", rankImg, 0, "../../../data/rank.bmp");
//	}
//	
//	
//	waitKey(0);*/
//
//	crvlVolumeCalculator vm;
//
//	vector<Vec3f> vertices;
//	vertices.push_back(Vec3f(0.f, 0.f, 0.f));
//	vertices.push_back(Vec3f(10.f, 0.f, 2.f));
//	vertices.push_back(Vec3f(5.f, 20.f, 0.f));
//	vertices.push_back(Vec3f(0.f, 0.f, 50.f));
//	printf("Volume: %f\n", vm.calcTetrahedronVolume(vertices));
//
//	vector<Vec3f> prism;
//	prism.push_back(Vec3f(0.f, 0.f, 0.f));
//	prism.push_back(Vec3f(5.f, 0.f, 0.f));
//	prism.push_back(Vec3f(0.f, 5.f, 0.f));
//	prism.push_back(Vec3f(0.f, 0.f, 10.f));
//	prism.push_back(Vec3f(5.f, 0.f, 10.f));
//	prism.push_back(Vec3f(0.f, 5.f, 12.f));
//	printf("Prism Volume: %f\n", vm.calcPrismVolume(prism));
//
//
//
//	return 0;
//}

void findCenterPoints(Mat &image, vector<RotatedRect> &centerEllipses);

int main(){

	Mat image = imread("../../../data/test1.ppm", CV_LOAD_IMAGE_COLOR);

	if (!image.data)
	{
		printf("Image is not loaded\n");
		return -1;
	}

	imshow("Input image", image);
	waitKey(100);

	vector<RotatedRect> imageCenterEllipses;
	findCenterPoints(image, imageCenterEllipses);

	return 0;

}

void findCenterPoints(Mat &image, vector<RotatedRect> &centerEllipses){

	Mat grayImage;
	Mat thresholdImage, contourImage, goodContourImage;
	vector<vector<Point>> allContours, goodContours, refinedContours;
	vector<Vec4i> hierarchy, goodHierarchy;

	cvtColor(image, grayImage, CV_BGR2GRAY);
	threshold(grayImage, thresholdImage, 80, 255, CV_THRESH_BINARY);
	Mat threshCopy;
	thresholdImage.copyTo(threshCopy);

	findContours(threshCopy, allContours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);

	contourImage = Mat::zeros(thresholdImage.rows, thresholdImage.cols, thresholdImage.type());
	drawContours(contourImage, allContours, -1, Scalar(255));
	imshow("All contours image", contourImage);
	waitKey(0);

}