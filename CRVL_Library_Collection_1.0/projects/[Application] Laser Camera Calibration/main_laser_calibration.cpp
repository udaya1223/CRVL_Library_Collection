#include "opencv2\opencv.hpp"
#include <iostream>

#define IMAGE_FILE_PATH		"../../../data/LaserCameraCalibration/2015.08.11"
#define START_IMG_NUM		0
#define END_IMG_NUM			6
#define WINDOW_SIZE			5
#define PATTERN_BOARD_X		4
#define PATTERN_BOARD_Y		7

#define SHOW_DEBUG_IMAGES


using namespace cv;
using namespace std;

struct MouseParams{
	Mat img;
	vector<Point2f> cornerPoints;
	int imgNum;
	string windowName;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
void _PrintMatrix(char *pMessage, cv::Mat &mat)
{
	printf("%s\n", pMessage);

	for (int r = 0; r < mat.rows; r++) {
		for (int c = 0; c < mat.cols; c++) {
			printf("%.8lf ", mat.at<float>(r, c));
		} printf("\n");
	} printf("\n");
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
bool _ParseCalibFile(char *pFilePath, Mat &rotation, Vec3f &translation){

	FILE *fp = fopen(pFilePath, "r+");

	if (!fp) {
		printf("Failed to open calibration file.\n");
		return false;
	}

	rotation = Mat::eye(3, 3, CV_32F);
	
	char szBuffer[512];

	while (!feof(fp)) {
		fscanf(fp, "%s", szBuffer);

		if (!strcmp("Tc_ext", szBuffer)) {
			fscanf(fp, "%s", szBuffer);
			fscanf(fp, "%s", szBuffer);

			// translation_x
			fscanf(fp, "%s", szBuffer);
			translation[0] = atof(szBuffer);

			// translation_y
			fscanf(fp, "%s", szBuffer);
			translation[1] = atof(szBuffer);

			// translation_z
			fscanf(fp, "%s", szBuffer);
			translation[2] = atof(szBuffer);

			continue;
		}
		else if (!strcmp("Rc_ext", szBuffer)) {
			fscanf(fp, "%s", szBuffer);
			fscanf(fp, "%s", szBuffer);

			// R_00
			fscanf(fp, "%s", szBuffer);
			rotation.at<float>(0, 0) = atof(szBuffer);

			// R_01
			fscanf(fp, "%s", szBuffer);
			rotation.at<float>(0, 1) = atof(szBuffer);

			// R_02
			fscanf(fp, "%s", szBuffer);
			rotation.at<float>(0, 2) = atof(szBuffer);

			// R_10
			fscanf(fp, "%s", szBuffer);
			rotation.at<float>(1, 0) = atof(szBuffer);

			// R_11
			fscanf(fp, "%s", szBuffer);
			rotation.at<float>(1, 1) = atof(szBuffer);

			// R_12
			fscanf(fp, "%s", szBuffer);
			rotation.at<float>(1, 2) = atof(szBuffer);

			// R_20
			fscanf(fp, "%s", szBuffer);
			rotation.at<float>(2, 0) = atof(szBuffer);

			// R_21
			fscanf(fp, "%s", szBuffer);
			rotation.at<float>(2, 1) = atof(szBuffer);

			// R_22
			fscanf(fp, "%s", szBuffer);
			rotation.at<float>(2, 2) = atof(szBuffer);

			continue;
		}

	}

	
	// 결과 출력해보기
	printf("\n\n");
	printf("_______________________________________________________________________________\n");

	printf("Extrinsic Camera Info. : \n");

	_PrintMatrix("Rotation", rotation);
	printf("Translation: [%f %f %f]\n", translation[0], translation[1], translation[2]);
	
	return true;
}

void laser_mouse_callback(int event, int x, int y, int flags, void* param){

	//Check for the event Left mouse button press
	if (event != CV_EVENT_LBUTTONDOWN)	return;

	MouseParams* mp = (MouseParams*)param;
	Mat & frame = mp->img;
	Mat colorFrame;
	cvtColor(frame, colorFrame, CV_GRAY2BGR);

	Size size;
	Point ofs;
	double maxVal = 0.0, totalVal = 0.0;
	Point maxLoc, pntLoc;

	vector<Point2f> corners(1, Point2f(x,y));
	cornerSubPix(frame, corners, Size(5, 5), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
	printf("Refined Corner: %f %f\n", corners[0].x, corners[0].y);
	mp->cornerPoints.push_back(corners[0]);

	//Draw center point and ROI for viewing
	for (int i = 0; i < mp->cornerPoints.size(); i++){
		circle(colorFrame, mp->cornerPoints[i], 2, Scalar(0, 0, 255), -1);
	}
	
	imshow(mp->windowName, colorFrame);
	colorFrame.release();
}

void vision_mouse_callback(int event, int x, int y, int flags, void* param){

	//Check for the event Left mouse button press
	if (event != CV_EVENT_LBUTTONDOWN)	return;

	MouseParams* mp = (MouseParams*)param;
	Mat & frame = mp->img;
	Mat colorFrame;
	cvtColor(frame, colorFrame, CV_GRAY2BGR);

	Size size;
	Point ofs;
	double maxVal = 0.0, totalVal = 0.0;
	Point maxLoc, pntLoc;

	vector<Point2f> corners(1, Point2f(x, y));
	cornerSubPix(frame, corners, Size(5, 5), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
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

	colorFrame.release();
}

double findCentroid(Mat &imgColumn, int roiStart, int roiEnd, int threshold){

	double y_hy = 0.0;
	double hy = 0.0;
	for (int row = roiStart; row < roiEnd; row++){
		//printf("%d\n", imgColumn.at<uchar>(row, 0));
		if (imgColumn.at<uchar>(row, 0)>(uchar)threshold){
			y_hy += row*(double)(imgColumn.at<uchar>(row, 0));
			hy += (double)(imgColumn.at<uchar>(row, 0));
		}
	}
	if (hy == 0){
		return 0.0;
	}
	else{
		return y_hy / hy;
	}
}

bool findLaserLine(Mat &laserImg, Vec4f &laserLine, vector<Point2f> &chessboardCorners, int threshold){

	// Define start and end of the scan
	int startCol, endCol, startRow, endRow;
	int corner0 = 0;
	int corner1 = chessboardCorners.size() - 1 - PATTERN_BOARD_X;
	int corner2 = chessboardCorners.size() - 1;
	int corner3 = PATTERN_BOARD_X;	

	// Take only the red channel of the RGB image
	vector<Mat> channels;
	split(laserImg, channels);
	Mat laserRedGray = channels[2];

	// Convert the red channel to a color image
	Mat laserRedColor;
	cvtColor(laserRedGray, laserRedColor, CV_GRAY2BGR);

	// Smooth red channel to remove the noise
	Mat laserRedSmooth;
	GaussianBlur(laserRedGray, laserRedSmooth, Size(5, 5), 2, 2);

	// Make a mask image using four corner information
	Mat mask(laserImg.size(), CV_8UC1, Scalar(0));
	vector<Point> corners;
	corners.push_back(Point((int)(chessboardCorners[corner0].x), (int)(chessboardCorners[corner0].y)));
	corners.push_back(Point((int)(chessboardCorners[corner1].x), (int)(chessboardCorners[corner1].y)));
	corners.push_back(Point((int)(chessboardCorners[corner2].x), (int)(chessboardCorners[corner2].y)));
	corners.push_back(Point((int)(chessboardCorners[corner3].x), (int)(chessboardCorners[corner3].y)));
	fillConvexPoly(mask, corners, Scalar(255), 8, 0);

	// Find start and end of the scanning
	if (corners[0].x > corners[3].x) startCol = corners[3].x;
	else startCol = corners[0].x;
	if (corners[1].x > corners[2].x) endCol = corners[1].x;
	else endCol = corners[2].x;
	if (corners[0].y > corners[1].y) startRow = corners[1].y;
	else startRow = corners[0].y;
	if (corners[3].y > corners[2].y) endRow = corners[3].y;
	else endRow = corners[2].y;

	// Crop the input image using the mask
	Mat croppedLaserRedSmooth;
	laserRedSmooth.copyTo(croppedLaserRedSmooth, mask);
		
	// Find the centroids by scanning every column
	vector<Point2f> laserLinePoints;
	for (int j = startCol; j < endCol; j++){
		Mat imgColumn = croppedLaserRedSmooth.col(j);
		double centroid = findCentroid(imgColumn, startRow, endRow, threshold);
		if (centroid > 0){
			//printf("Centroid: %f %f\n", (float)j, centroid);
			laserLinePoints.push_back(Point2f(j, (float)centroid));
		}
	}	

#ifdef SHOW_DEBUG_IMAGES
	imshow("Red Channel", laserRedGray);
	imshow("Gaussian Blur", laserRedSmooth);
	imshow("Cropped Image", croppedLaserRedSmooth);
	imwrite("Gaussian Blur.jpg", laserRedSmooth);
	// Draw centroid points on the image
	for (int j = 0; j < laserLinePoints.size(); j++){
		circle(laserRedColor, laserLinePoints[j], 1, Scalar(0, 0, 255), -1);
	}
	imshow("Laser Points", laserRedColor);
#endif // SHOW_DEBUG_IMAGES

	if (laserLinePoints.size() > 5){
		// Laser points to a line and find the line equation
		cv::fitLine(laserLinePoints, laserLine,
			CV_DIST_L2, // distance type
			0, // not used with L2 distance
			0.01, 0.01); // accuracy		
		return true;
	}
		
	else return false;	
}

void drawLaserLine(Mat & image, Vec4f & laserLine, Scalar color = Scalar(0,0,255), int scale = 200, int thickness = 1){
	// Draw laser line
	float x0 = laserLine[2] - scale * laserLine[0]; // a point on the line
	float y0 = laserLine[3] - scale * laserLine[1];
	float x1 = laserLine[2] + scale * laserLine[0]; // add a vector of length 200
	float y1 = laserLine[3] + scale * laserLine[1]; // using the unit vector
	line(image, cv::Point2f(x0, y0), cv::Point2f(x1, y1), color, thickness);
}

void setChessboardWorldCoordinates(int patternX, int patternY, float width, float height, vector<Point3f> &chessboardWorld){

	for (int Y = 0; Y <= patternY; Y++){
		for (int X = 0; X <= patternX; X++){
			chessboardWorld.push_back(Point3f(X*height, Y*width, 0.0));
		}
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Find the Intersection point of two lines
bool getIntersection(Point2f o1, Point2f p1, Point2f o2, Point2f p2, Point2f &r){
	Point2f x = o2 - o1;
	Point2f d1 = p1 - o1;
	Point2f d2 = p2 - o2;

	float cross = d1.x*d2.y - d1.y*d2.x;
	if (abs(cross) < 1e-8) return false;

	double t1 = (x.x * d2.y - x.y * d2.x) / cross;
	r = o1 + d1 * t1;
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Get two points on a line using line vector
void getTwoPointOnLine(Vec4f &line, Point2f &point1, Point2f &point2, int scale){

	point1.x = line[2] - scale * line[0]; // a point on the line
	point1.y = line[3] - scale * line[1];
	point2.x = line[2] + scale * line[0];
	point2.y = line[3] + scale * line[1];

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Find intersection points between laser line and chessboard edges
void findIntersections(Mat &srcImg, vector<Point2f> &chessboardImg, Vec4f &laserLine, vector<Point2f> &intersections, int chessboardX, int chessboardY){

	for (int i = 0; i < (chessboardY+1); i++){
		vector<Point2f> chessboardEdgePoints;
		chessboardEdgePoints.push_back(chessboardImg[i*(chessboardX + 1) + 0]);
		chessboardEdgePoints.push_back(chessboardImg[i*(chessboardX + 1) + 1]);
		chessboardEdgePoints.push_back(chessboardImg[i*(chessboardX + 1) + 2]);
		chessboardEdgePoints.push_back(chessboardImg[i*(chessboardX + 1) + 3]);
		chessboardEdgePoints.push_back(chessboardImg[i*(chessboardX + 1) + 4]);
		
		Vec4f chessboardEdgeLine;
		fitLine(chessboardEdgePoints, chessboardEdgeLine, CV_DIST_L2, 0, 0.01, 0.01);
		
		Point2f l1, l2, e1, e2, intersec;
		getTwoPointOnLine(laserLine, l1, l2, 200);
		getTwoPointOnLine(chessboardEdgeLine, e1, e2, 200);

		if (getIntersection(l1, l2, e1, e2, intersec)){
			intersections.push_back(intersec);
		}
		else {
			printf("ERROR: No intersection found. Try to change the scale.\n");
		}

#ifdef SHOW_DEBUG_IMAGES
		drawLaserLine(srcImg, chessboardEdgeLine, Scalar(0, 255, 0));
		circle(srcImg, intersec, 2, Scalar(255, 0, 255), -1);
		namedWindow("Chessboard Edges", 0);
		imshow("Chessboard Edges", srcImg);
#endif // SHOW_DEBUG_IMAGES

	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Find world coordinates of the crossing points using cross ratio
void findIntersectionWorldCoordinates(vector<Point2f> &intersecImg, vector<Point3f> &intersecWorld, vector<Point2f> &chessboardImg, vector<Point3f> &chessboardWorld, int chessboardX ){
	for (int i = 0; i < chessboardWorld.size(); i+=(chessboardX+1)){
	
		Point2f A, B, C, D, AC, BD, BC, AD;
		A = chessboardImg[i];
		B = chessboardImg[i + 1];
		C = intersecImg[i / (chessboardX + 1)];
		D = chessboardImg[i + chessboardX];
		AC = C - A;
		BD = D - B;
		BC = C - B;
		AD = D - A;
		
		float CR = (sqrt(AC.dot(AC)) * sqrt(BD.dot(BD))) / (sqrt(BC.dot(BC)) * sqrt(AD.dot(AD)));

		float X1, X2, X3, X4;
		X1 = chessboardWorld[i].x;
		X2 = chessboardWorld[i+1].x;
		X4 = chessboardWorld[i+chessboardX].x;
		
		X3 = (X1*(X4 - X2) - CR*X2*(X4 - X1)) / ((X4 - X2) - CR*(X4 - X1));

		Point3f intersec;
		intersec.x = X3;
		intersec.y = chessboardWorld[i].y;
		intersec.z = chessboardWorld[i].z;

		intersecWorld.push_back(intersec);
		
		///printf("Cross Ratio : %f", CR);

	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Convert World Coordinates to Camera Coordinates using Rotation and Translation
void findIntersectionCameraCoordinates(vector<Point3f> &world, vector<Point3f> &camera, Mat &rotation, Vec3f &translation){
	Mat Rt = Mat::zeros(3, 4, CV_32F);
	for (int row = 0; row < rotation.rows; row++){
		for (int col = 0; col < rotation.cols; col++){
			Rt.at<float>(row, col) = rotation.at<float>(row, col);
		}
	}

	Rt.at<float>(0, 3) = translation[0];
	Rt.at<float>(1, 3) = translation[1];
	Rt.at<float>(2, 3) = translation[2];

	_PrintMatrix("Rt", Rt);

	for (int i = 0; i < world.size(); i++){
		
		Mat W = Mat(4, 1, CV_32F);
		W.at<float>(0, 0) = world[i].x;
		W.at<float>(1, 0) = world[i].y;
		W.at<float>(2, 0) = world[i].z;
		W.at<float>(3, 0) = 1.0f;
		//_PrintMatrix("World", W);

		Mat cam = Rt * W;
		Point3f C;
		C.x = cam.at<float>(0, 0);
		C.y = cam.at<float>(1, 0);
		C.z = cam.at<float>(2, 0);
		camera.push_back(C);

		//_PrintMatrix("Camera Coordinates", cam);
	}
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void findPlaneEquations(vector<Point3f> &laserPoints3D, Vec4f &planeEquation){
	
	Vec3f cameraDir = Vec3f(0.f, 0.f, 1.f);
	Vec3f planeNormal;

	int nNumPoints = (int)laserPoints3D.size();

	if (nNumPoints < 4) {
		printf("ERROR: Number of 3D points are not enough to continue SVD. \n");
		planeEquation = Vec4f(0.f, 0.f, 0.f, 0.f);
		//system("pause");
	}
	else{
		Mat A(nNumPoints, 4, CV_32F, Scalar(0.)), W, U, Vt;
		for (int j = 0; j < nNumPoints; j++) {
			A.at<float>(j, 0) = laserPoints3D[j].x;
			A.at<float>(j, 1) = laserPoints3D[j].y;
			A.at<float>(j, 2) = laserPoints3D[j].z;
			A.at<float>(j, 3) = 1.;
		}

		// find SVD of A
		cv::SVD::compute(A, W, U, Vt);

		// Vt는 이미 정렬이 되어 있음!
		planeNormal[0] = Vt.at<float>(3, 0);
		planeNormal[1] = Vt.at<float>(3, 1);
		planeNormal[2] = Vt.at<float>(3, 2);

		float dLen = sqrt(planeNormal.dot(planeNormal));
		planeNormal /= dLen;

		// 카메라의 방향과 정반대라면.....
		if (cameraDir.dot(planeNormal) > 0.) {
			planeEquation = Vec4f(-Vt.at<float>(3, 0), -Vt.at<float>(3, 1), -Vt.at<float>(3, 2), -Vt.at<float>(3, 3));
		}
		else {
			planeEquation = Vec4f(Vt.at<float>(3, 0), Vt.at<float>(3, 1), Vt.at<float>(3, 2), Vt.at<float>(3, 3));
		}
	}

}

int main(){

	char szFilePath[256];
	
	Mat laserImg, visionImg, visionGrayImg, laserRedChannel;	

	// Vector to hold all the Camera Coordinates of laser line
	vector<Point3f> intersectionsCamera;

	for (int i = START_IMG_NUM; i <= END_IMG_NUM; i++){

		sprintf(szFilePath, "%s/Laser/Img_%03d.jpg", IMAGE_FILE_PATH, i);
		laserImg = imread(szFilePath, CV_LOAD_IMAGE_COLOR);
		sprintf(szFilePath, "%s/Vision/Img_%03d.jpg", IMAGE_FILE_PATH, i);		
		visionImg = imread(szFilePath, CV_LOAD_IMAGE_COLOR);

		if (!laserImg.data || !visionImg.data){
			printf("ERROR: Couldn't find the input image.\n");
			break;
		}

		cvtColor(visionImg, visionGrayImg, CV_BGR2GRAY);
		vector<Mat> channels;
		split(laserImg, channels);
		laserRedChannel = channels[2];

#ifdef SHOW_DEBUG_IMAGES
		imshow("Laser Image", laserImg);
		imshow("Vision Image", laserRedChannel);
#endif // SHOW_DEBUG_IMAGES
	
		// Find corner points of the chessboard using mouse click
		printf("\nDetecting Corner Points in Chessboard %d:\n", i);
		MouseParams visiomImgParm;
		visiomImgParm.img = visionGrayImg.clone();
		visiomImgParm.imgNum = i;
		visiomImgParm.windowName = "Chessboard Pattern";
		namedWindow(visiomImgParm.windowName, 0);
		imshow(visiomImgParm.windowName, visionGrayImg);
		setMouseCallback(visiomImgParm.windowName, vision_mouse_callback, (void*)&visiomImgParm);
		waitKey(0);
		destroyWindow(visiomImgParm.windowName);
	
		// Check all corners are detected
		if (visiomImgParm.cornerPoints.size() != ((PATTERN_BOARD_X + 1)*(PATTERN_BOARD_Y + 1))){
			printf("ERROR: All corners are not detected.\n");
			i--;
			continue;
		}

		// Chessboard image coordinates
		vector<Point2f> chessboardImage;
		chessboardImage = visiomImgParm.cornerPoints;

		// Find the laser line using line fitting
		Vec4f laserLine;
		findLaserLine(laserImg, laserLine, chessboardImage, 150);
		
		// Draw laser line
		drawLaserLine(laserImg, laserLine, Scalar(0,0,255));
		namedWindow("Laser Line", 0);
		imshow("Laser Line", laserImg);

		// Set chessboard world coordinates
		vector<Point3f> chessboardWorld;
		setChessboardWorldCoordinates(PATTERN_BOARD_X, PATTERN_BOARD_Y, 35, 35, chessboardWorld);

		// Find crossing points between laser line and chessboard edges
		vector<Point2f> intersectionsImage;
		findIntersections(laserImg, chessboardImage, laserLine, intersectionsImage, PATTERN_BOARD_X, PATTERN_BOARD_Y);
		
		// Find world coordinates of crossing points
		vector<Point3f> intersectionsWorld;
		findIntersectionWorldCoordinates(intersectionsImage, intersectionsWorld, chessboardImage, chessboardWorld, PATTERN_BOARD_X);

		// Find camera coordinates of crossing points using [R|t]
		Mat R; Vec3f t;		
		sprintf(szFilePath, "%s/Vision/Img_%03d.txt", IMAGE_FILE_PATH, i);
		_ParseCalibFile(szFilePath, R, t);
		findIntersectionCameraCoordinates(intersectionsWorld, intersectionsCamera, R, t);

		waitKey(0);
	}

	Vec4f planeEquation;
	findPlaneEquations(intersectionsCamera, planeEquation);

	printf("Plane Equation: \n");
	printf("A: %f\n", planeEquation[0]);
	printf("B: %f\n", planeEquation[1]);
	printf("C: %f\n", planeEquation[2]);
	printf("D: %f\n", planeEquation[3]);

	FILE * pFile;
	sprintf(szFilePath, "%s/Line Equation.txt", IMAGE_FILE_PATH);
	pFile = fopen(szFilePath, "w");
	if (!pFile) {
		printf("Failed to open Line Equation file.\n");
		return -1;
	}
	fprintf(pFile, "A: %f\n", planeEquation[0]);
	fprintf(pFile, "B: %f\n", planeEquation[1]);
	fprintf(pFile, "C: %f\n", planeEquation[2]);
	fprintf(pFile, "D: %f\n", planeEquation[3]);
	fclose(pFile);

	return 0;
}


/*vector<Point2f> corners;
Size patternsize(8, 5);
bool patternfound = findChessboardCorners(visionGrayImg, patternsize, corners, CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE + CALIB_CB_FAST_CHECK);
if (patternfound){
cornerSubPix(visionGrayImg, corners, Size(5, 5), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
drawChessboardCorners(visionImg, patternsize, Mat(corners), patternfound);
}*/