#pragma once

#include <iostream>
#include "opencv2/opencv.hpp" 

class crvlVolumeCalculator
{
public:
	crvlVolumeCalculator();
	~crvlVolumeCalculator();

	float calcTetrahedronVolume(std::vector<cv::Vec3f> &vertices);
	float calcPrismVolume(std::vector<cv::Vec3f> &vertices);

private:

	std::vector<cv::Vec3f> m_vertices;
	float m_volume;

};
