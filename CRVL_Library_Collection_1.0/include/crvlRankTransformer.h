#pragma once

#include <iostream>
#include "opencv2/opencv.hpp" 

class crvlRankTransformer
{
public:
	crvlRankTransformer();
	~crvlRankTransformer();

	bool doRankTransform(cv::Mat &input, cv::Mat &output, int winSize=5);
	cv::Mat getRankTransformImage(cv::Mat &rank, int windowSize);

private:

};

