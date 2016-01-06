#include "crvlVolumeCalculator.h"

using namespace cv;
using namespace std;

crvlVolumeCalculator::crvlVolumeCalculator(){
	m_vertices.resize(4, Vec3f(0.f, 0.f, 0.f));
	m_volume = calcTetrahedronVolume(m_vertices);
}

crvlVolumeCalculator::~crvlVolumeCalculator(){
}

float crvlVolumeCalculator::calcTetrahedronVolume(std::vector<cv::Vec3f> &vertices){

	if (vertices.size() != 4){
		printf("ERROR: Need four vertices to calculate volume.\n");
		return 0.f;
	}

	Vec3f tmp1 = vertices[0] - vertices[3];
	Vec3f tmp2 = vertices[1] - vertices[3];
	Vec3f tmp3 = vertices[2] - vertices[3];

	float volume = abs((tmp1.dot(tmp2.cross(tmp3))))/6.f;

	return volume;
}

float crvlVolumeCalculator::calcPrismVolume(std::vector<cv::Vec3f> &vertices){

	if (vertices.size() != 6){
		printf("ERROR: Need six vertices to calculate volume.\n");
		return 0.f;
	}

	vector<Vec3f> tetrahedron1, tetrahedron2, tetrahedron3;
	tetrahedron1.push_back(vertices[0]);
	tetrahedron1.push_back(vertices[1]);
	tetrahedron1.push_back(vertices[2]);
	tetrahedron1.push_back(vertices[3]);
		
	tetrahedron2.push_back(vertices[1]);
	tetrahedron2.push_back(vertices[2]);
	tetrahedron2.push_back(vertices[3]);
	tetrahedron2.push_back(vertices[4]);

	tetrahedron3.push_back(vertices[2]);
	tetrahedron3.push_back(vertices[3]);
	tetrahedron3.push_back(vertices[4]);
	tetrahedron3.push_back(vertices[5]);
	
	float totalVol = calcTetrahedronVolume(tetrahedron1) + calcTetrahedronVolume(tetrahedron2) + calcTetrahedronVolume(tetrahedron3);

	return totalVol;
}