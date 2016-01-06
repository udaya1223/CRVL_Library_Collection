#include "opencv2\opencv.hpp"
#include <iostream>

#define IMAGE_FILE_PATH		"../../../data/FaceDatabase/"
#define START_IMG_NUM		1
#define END_IMG_NUM			5

#define NUM_OF_PCA			70

#define START_FOLDER		1
#define END_FOLDER			20

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

//////////////////////////////////////////////////////////////////////////
// Normalizes a given image into a value range between 0 and 255.
Mat norm_0_255(const Mat& src) {
	// Create and return normalized image:
	Mat dst;
	switch (src.channels()) {
	case 1:
		cv::normalize(src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
		break;
	case 3:
		cv::normalize(src, dst, 0, 255, NORM_MINMAX, CV_8UC3);
		break;
	default:
		src.copyTo(dst);
		break;
	}
	return dst;
}

//////////////////////////////////////////////////////////////////////////
//Prepare images as row matrices
static  Mat formatImagesForPCA(const vector<Mat> &data)
{
	Mat dst(static_cast<int>(data.size()), data[0].rows*data[0].cols, CV_32F);
	for (unsigned int i = 0; i < data.size(); i++)
	{
		Mat image_row = data[i].clone().reshape(1, 1);
		Mat row_i = dst.row(i);
		image_row.convertTo(row_i, CV_32F);
	}
	return dst;
}

static Mat toGrayscale(InputArray _src) {
	Mat src = _src.getMat();
	// only allow one channel
	if (src.channels() != 1) {
		CV_Error(Error::StsBadArg, "Only Matrices with one channel are supported");
	}
	// create and return normalized image
	Mat dst;
	cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
	return dst;
}

int main(){

	char szFilePath[256];
	string fileName;
	Mat faceImg;
	// Vector to keep all images
	vector<Mat> allFaceData;

	// Vector to hold all the Camera Coordinates of laser line
	vector<Point3f> intersectionsCamera;

	for (int x = START_FOLDER; x <= END_FOLDER; x++){
		for (int i = START_IMG_NUM; i <= END_IMG_NUM; i++){

			sprintf(szFilePath, "%s/s%d/%d.pgm", IMAGE_FILE_PATH, x, i);
			faceImg = imread(szFilePath, CV_LOAD_IMAGE_GRAYSCALE);

			if (!faceImg.data){
				printf("ERROR: Couldn't find the input image.\n");
				break;
			}


#ifdef SHOW_DEBUG_IMAGES
			imshow("Face Image", faceImg);
#endif // SHOW_DEBUG_IMAGES


			allFaceData.push_back(faceImg);
			waitKey(30);
		}
	}
	

	// Reshape and stack images into a rowMatrix and perform PCA
	Mat data = formatImagesForPCA(allFaceData);
	PCA pca(data, Mat(), CV_PCA_DATA_AS_ROW, NUM_OF_PCA);
	
	// And copy the PCA results:
	Mat mean = pca.mean.clone();
	Mat eigenvalues = pca.eigenvalues.clone();
	Mat eigenvectors = pca.eigenvectors.clone();

	for (int i = 0; i < NUM_OF_PCA; i++){
		Mat pc = norm_0_255(eigenvectors.row(i)).reshape(1, allFaceData[0].rows);
		Mat colorpc;
		applyColorMap(pc, colorpc, COLORMAP_BONE);

		sprintf(szFilePath, "Principal Component %d", i);
		//namedWindow(szFilePath, 0);
		//imshow(szFilePath, colorpc);

		fileName = format("%s/PC_%d.bmp", IMAGE_FILE_PATH, i);
		imwrite(fileName, colorpc);
	}

	Mat meanImg = norm_0_255(mean).reshape(1, allFaceData[0].rows);
	imshow("Mean", meanImg);
	fileName = format("%s/mean.bmp", IMAGE_FILE_PATH);
	imwrite(fileName, meanImg);

	////Take the first three eigenvectors to make PC images:
	////Display and save PCA results
	//Mat pca1 = norm_0_255(eigenvectors.row(0)).reshape(1, allFaceData[0].rows);
	//Mat colorpca1;
	//applyColorMap(pca1, colorpca1, COLORMAP_JET);
	//imshow("pc1", pca1);
	//fileName = format("%s/PCA 1.bmp", IMAGE_FILE_PATH);
	//imwrite(fileName, colorpca1);

	//if (NUM_OF_PCA > 1){
	//	Mat pca2 = norm_0_255(eigenvectors.row(1)).reshape(1, allFaceData[0].rows);
	//	Mat colorpca2;
	//	applyColorMap(pca2, colorpca2, COLORMAP_JET);
	//	imshow("pc2", colorpca2);
	//	fileName = format("%s/PCA 2.bmp", IMAGE_FILE_PATH);
	//	imwrite(fileName, colorpca2);
	//}

	//if (NUM_OF_PCA > 2){
	//	Mat pca3 = norm_0_255(eigenvectors.row(2)).reshape(1, allFaceData[0].rows);
	//	Mat colorpca3;
	//	applyColorMap(pca3, colorpca3, COLORMAP_JET);
	//	imshow("pc3", colorpca3);
	//	fileName = format("%s/PCA 3.bmp", IMAGE_FILE_PATH);
	//	imwrite(fileName, colorpca3);
	//}

	// Demonstration of the effect of retainedVariance on the first image
	sprintf(szFilePath, "%s/s1/%d.pgm", IMAGE_FILE_PATH, 5);
	Mat test = imread(szFilePath, CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Test Image", test);
	Mat image_row = test.clone().reshape(1, 1);
	Mat row_i;
	image_row.convertTo(row_i, CV_32F);

	Mat point = pca.project(row_i); // project into the eigenspace, thus the image becomes a "point"
	Mat reconstruction = pca.backProject(point); // re-create the image from the "point"
	reconstruction = reconstruction.reshape(allFaceData[0].channels(), allFaceData[0].rows); // reshape from a row vector into image shape
	reconstruction = toGrayscale(reconstruction); // re-scale for displaying purposes

	// display until user presses q
	imshow("Reconstruction", reconstruction);

	waitKey(0);
	return 0;
}


//// Demonstration of the effect of retainedVariance on the first image
//sprintf(szFilePath, "%s/%d.pgm", IMAGE_FILE_PATH, 10);
//Mat test = imread(szFilePath, CV_LOAD_IMAGE_GRAYSCALE);
//Mat image_row = test.clone().reshape(1, 1);
//Mat row_i;
//image_row.convertTo(row_i, CV_32F);