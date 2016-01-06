#include "crvlRankTransformer.h"

using namespace cv;

crvlRankTransformer::crvlRankTransformer()
{
}

crvlRankTransformer::~crvlRankTransformer()
{
}

bool crvlRankTransformer::doRankTransform(cv::Mat &input, cv::Mat &output, int winSize){

	if (!input.data){
		printf("Input data is empty..!!\n");
		return false;
	}

	if (winSize < 1 || winSize > 125){
		printf("Window size should be in between 1 and 125..!!\n");
		return false;
	}

	int rows = input.rows;
	int cols = input.cols;
	int numofchannels = input.channels();
	int fullWinSize = winSize * 2 + 1;

	Mat grayInput;
	output = Mat(input.size(), CV_16UC1, Scalar(0));

	if (numofchannels > 1){
		cvtColor(input, grayInput, CV_BGR2GRAY);
	} else{
		grayInput = input.clone();
	}

	int count = 0;
	for (int row = winSize; row < rows - winSize; row++){
		for (int col = winSize; col < cols - winSize; col++){

			unsigned short pixelCount = 0;
			int midPixVal = grayInput.at<uchar>(row, col);

			for (int i = -winSize; i <= winSize; i++){
				for(int j = -winSize; j <= winSize; j++){
					int currPixVal = grayInput.at<uchar>(row+i, col+j);
					if (currPixVal < midPixVal) pixelCount++;
					//printf("%d %d  ", row + i, col + j);
				}
			}

			output.at<ushort>(row, col) = pixelCount;
// 			printf("%d %d\n", row, col);
// 			if (row == 369 && col==444){
// 				printf("aaaaa");
// 			}
		}
	}

	return true;

}

cv::Mat crvlRankTransformer::getRankTransformImage(cv::Mat &rank, int windowSize){

	Mat rankImg;

	if (rank.type() != CV_16UC1){
		printf("Rank image should be CV_16UC1 type..!!");
		exit(0);
	}

	int scale = 1;
	if (windowSize < 5){
		scale = 5;
	}
	else if (windowSize > 15){
		scale = 1;
	}

	rank.convertTo(rankImg, CV_8UC1, scale);

	return rankImg;
}