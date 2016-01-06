#include <iostream>
#include <fstream>

#include "opencv2\opencv.hpp"
#include "crvlDisplayUtility.h"


using namespace cv;
using namespace std;


const int xRes = 639;
const int yRes = 479;
const int symbolSize = 1;
const int extendSize = 5;

ifstream inData;
ofstream outData;

void enlargePatternBnW(Mat &pattern, Mat &largepattern){
	for (int i = 0; i < pattern.rows; i++){
		for (int j = 0; j < pattern.cols; j++){
			if (pattern.at<uchar>(i, j) == 1){
				for (int x = i*symbolSize; x < (i*symbolSize + symbolSize); x++){
					for (int y = j*symbolSize; y < (j*symbolSize + symbolSize); y++){
						largepattern.row(x).col(y) = Scalar(255, 255, 255);
					}
				}
			}
		}
	}
}

void enlargePatternColor(Mat &pattern, Mat &largepattern){
	for (int i = 0; i < pattern.rows; i++){
		for (int j = 0; j < pattern.cols; j++){
			if (pattern.at<uchar>(i, j) == 0){
				for (int x = i*symbolSize; x < (i*symbolSize + symbolSize); x++){
					for (int y = j*symbolSize; y < (j*symbolSize + symbolSize); y++){
						largepattern.row(x).col(y) = Scalar(255, 0, 0);
					}
				}
			}
			else if (pattern.at<uchar>(i, j) == 1){
				for (int x = i*symbolSize; x < (i*symbolSize + symbolSize); x++){
					for (int y = j*symbolSize; y < (j*symbolSize + symbolSize); y++){
						largepattern.row(x).col(y) = Scalar(0, 255, 0);
					}
				}
			}
			else if (pattern.at<uchar>(i, j) == 2){
				for (int x = i*symbolSize; x < (i*symbolSize + symbolSize); x++){
					for (int y = j*symbolSize; y < (j*symbolSize + symbolSize); y++){
						largepattern.row(x).col(y) = Scalar(0, 255, 255);
					}
				}
			}
			else if (pattern.at<uchar>(i, j) == 3){
				for (int x = i*symbolSize; x < (i*symbolSize + symbolSize); x++){
					for (int y = j*symbolSize; y < (j*symbolSize + symbolSize); y++){
						largepattern.row(x).col(y) = Scalar(255, 255, 0);
					}
				}
			}
			else if (pattern.at<uchar>(i, j) == 4){
				for (int x = i*symbolSize; x < (i*symbolSize + symbolSize); x++){
					for (int y = j*symbolSize; y < (j*symbolSize + symbolSize); y++){
						largepattern.row(x).col(y) = Scalar(255, 0, 255);
					}
				}
			}
			else if (pattern.at<uchar>(i, j) == 5){
				for (int x = i*symbolSize; x < (i*symbolSize + symbolSize); x++){
					for (int y = j*symbolSize; y < (j*symbolSize + symbolSize); y++){
						largepattern.row(x).col(y) = Scalar(0, 0, 255);
					}
				}
			}
			else{
				for (int x = i*symbolSize; x < (i*symbolSize + symbolSize); x++){
					for (int y = j*symbolSize; y < (j*symbolSize + symbolSize); y++){
						largepattern.row(x).col(y) = Scalar(255, 255, 255);
					}
				}
			}
		}
	}
}

void enlargePatternColorSpace(Mat &pattern, Mat &largepattern){
	int xCount = 0;
	int yCount = 0;
	for (int i = 0; i < pattern.rows; i++){
		for (int j = 0; j < pattern.cols; j++){
			if (pattern.at<uchar>(i, j) == 0){
				xCount = 0;
				yCount = 0;
				for (int x = i*symbolSize; x < (i*symbolSize + symbolSize); x++){
					yCount = 0;
					for (int y = j*symbolSize; y < (j*symbolSize + symbolSize); y++){
						if (yCount > 7 || xCount > 7){
							largepattern.row(x).col(y) = Scalar(0, 0, 0);
						}
						else{
							largepattern.row(x).col(y) = Scalar(255, 0, 0);
						}
						yCount++;
					}
					xCount++;
				}
			}
			else if (pattern.at<uchar>(i, j) == 1){
				xCount = 0;
				yCount = 0;
				for (int x = i*symbolSize; x < (i*symbolSize + symbolSize); x++){
					yCount = 0;
					for (int y = j*symbolSize; y < (j*symbolSize + symbolSize); y++){
						if (yCount > 7 || xCount > 7){
							largepattern.row(x).col(y) = Scalar(0, 0, 0);
						}
						else{
							largepattern.row(x).col(y) = Scalar(0, 255, 0);
						}
						yCount++;
					}
					xCount++;
				}
			}
			else if (pattern.at<uchar>(i, j) == 2){
				xCount = 0;
				yCount = 0;
				for (int x = i*symbolSize; x < (i*symbolSize + symbolSize); x++){
					yCount = 0;
					for (int y = j*symbolSize; y < (j*symbolSize + symbolSize); y++){
						if (yCount > 7 || xCount > 7){
							largepattern.row(x).col(y) = Scalar(0, 0, 0);
						}
						else{
							largepattern.row(x).col(y) = Scalar(0, 255, 255);
						}
						yCount++;
					}
					xCount++;
				}
			}
			else if (pattern.at<uchar>(i, j) == 3){
				xCount = 0;
				yCount = 0;
				for (int x = i*symbolSize; x < (i*symbolSize + symbolSize); x++){
					yCount = 0;
					for (int y = j*symbolSize; y < (j*symbolSize + symbolSize); y++){
						if (yCount > 7 || xCount > 7){
							largepattern.row(x).col(y) = Scalar(0, 0, 0);
						}
						else{
							largepattern.row(x).col(y) = Scalar(255, 255, 0);
						}
						yCount++;
					}
					xCount++;
				}
			}
			else if (pattern.at<uchar>(i, j) == 4){
				xCount = 0;
				yCount = 0;
				for (int x = i*symbolSize; x < (i*symbolSize + symbolSize); x++){
					yCount = 0;
					for (int y = j*symbolSize; y < (j*symbolSize + symbolSize); y++){
						if (yCount > 7 || xCount > 7){
							largepattern.row(x).col(y) = Scalar(0, 0, 0);
						}
						else{
							largepattern.row(x).col(y) = Scalar(255, 0, 255);
						}
						yCount++;
					}
					xCount++;
				}
			}
			else if (pattern.at<uchar>(i, j) == 5){
				xCount = 0;
				yCount = 0;
				for (int x = i*symbolSize; x < (i*symbolSize + symbolSize); x++){
					yCount = 0;
					for (int y = j*symbolSize; y < (j*symbolSize + symbolSize); y++){
						if (yCount > 7 || xCount > 7){
							largepattern.row(x).col(y) = Scalar(0, 0, 0);
						}
						else{
							largepattern.row(x).col(y) = Scalar(0, 0, 255);
						}
						yCount++;
					}
					xCount++;
				}
			}
			else{
				xCount = 0;
				yCount = 0;
				for (int x = i*symbolSize; x < (i*symbolSize + symbolSize); x++){
					yCount = 0;
					for (int y = j*symbolSize; y < (j*symbolSize + symbolSize); y++){
						if (yCount > 7 || xCount > 7){
							largepattern.row(x).col(y) = Scalar(0, 0, 0);
						}
						else{
							largepattern.row(x).col(y) = Scalar(255, 255, 255);
						}
						yCount++;
					}
					xCount++;
				}
			}
		}
	}
}

void enlargePatternRed(Mat &pattern, Mat &largepattern){
	for (int i = 0; i < pattern.rows; i++){
		for (int j = 0; j < pattern.cols; j++){
			if (pattern.at<uchar>(i, j) == 5){
				for (int x = i*symbolSize; x < (i*symbolSize + symbolSize); x++){
					for (int y = j*symbolSize; y < (j*symbolSize + symbolSize); y++){
						largepattern.row(x).col(y) = Scalar(0, 0, 255);
					}
				}
			}
			else{
				for (int x = i*symbolSize; x < (i*symbolSize + symbolSize); x++){
					for (int y = j*symbolSize; y < (j*symbolSize + symbolSize); y++){
						largepattern.row(x).col(y) = Scalar(255, 255, 255);
					}
				}
			}
		}
	}
}

void enlargePatternCircle(Mat &pattern, Mat &largepattern){
	for (int i = 0; i < pattern.rows; i++){
		for (int j = 0; j < pattern.cols; j++){
			if (pattern.at<uchar>(i, j) == 1){
				circle(largepattern, Point(j * 25 + 12, i * 25 + 12), 8, Scalar(255, 255, 255), -1);
			}
		}
	}
}

void addGrid(Mat &image, int gridinterval, int startRow, int startColumn){
	for (int i = startRow; i < image.rows; i += gridinterval){
		for (int j = 0; j < image.cols; j++){
			image.row(i).col(j) = Scalar(175, 175, 175);
		}
	}
	for (int i = startColumn; i < image.cols; i += gridinterval){
		for (int j = 0; j < image.rows; j++){
			image.row(j).col(i) = Scalar(175, 175, 175);
		}
	}

	Point2f start, end;
	start.x = 599;
	start.y = 0;
	end.x = 599;
	end.y = 449;
	line(image, start, end, Scalar(175, 175, 175), 1);
	start.x = 0;
	start.y = 449;
	end.x = 599;
	end.y = 449;
	line(image, start, end, Scalar(175, 175, 175), 1);

}

void readPatternFromFile(Mat &patternImg){
	char c;
	inData.open(/*"FullPattern.txt"*/"B_S_Pattern_11_639_479.txt");

	for (int i = 0; i < yRes; i++){
		for (int j = 0; j < xRes; j++){

			if (inData >> c){

				if (c == '0'){
					patternImg.row(i).col(j) = 0;
				}
				else if (c == '1'){
					patternImg.row(i).col(j) = 1;
				}
				else if (c == '2'){
					patternImg.row(i).col(j) = 2;
				}
				else if (c == '3'){
					patternImg.row(i).col(j) = 3;
				}
				else if (c == '4'){
					patternImg.row(i).col(j) = 4;
				}
				else if (c == '5'){
					patternImg.row(i).col(j) = 5;
				}
				else if (c == '6'){
					patternImg.row(i).col(j) = 6;
				}

			}
			else{
				printf("Error in the input file format !\nThere's no enough input data in the file.\n\n");
				exit(0);
			}

		}
	}
	inData.close();
}

void extendPattern(Mat &pattern, Mat &largepattern){
	for (int i = 0; i < pattern.rows; i++){
		for (int j = 0; j < pattern.cols; j++){
			if (pattern.at<uchar>(i, j) == 1){
				int count = 0;
				for (int x = i*extendSize; x < (i*extendSize + extendSize); x++){
					for (int y = j*extendSize; y < (j*extendSize + extendSize); y++){
						if (count == (extendSize*extendSize) / 2){
							largepattern.row(x).col(y) = Scalar(1);
						}
						count++;
					}
				}
			}
		}
	}
}

void extendPattern2(Mat &pattern, Mat &largepattern){
	for (int i = 0; i < pattern.rows; i++){
		for (int j = 0; j < pattern.cols; j++){
			if (pattern.at<uchar>(i, j) == 1){
				int count = 0;
				for (int x = i*extendSize; x < (i*extendSize + extendSize); x++){
					for (int y = j*extendSize; y < (j*extendSize + extendSize); y++){
						if (count == 5 || count == 6 || count == 9 || count == 10 /*|| count == 12 || count == 13 || count == 16 || count == 17 || count == 18*/){
							largepattern.row(x).col(y) = Scalar(1);
						}
						count++;
					}
				}
			}
		}
	}
}

void savePatternTofile(Mat &matrix){
	int count = 0;
	cout << matrix.rows << endl;
	cout << matrix.cols << endl;
	outData.open("FullPattern.txt");
	for (int i = 0; i < matrix.rows; i++){
		for (int j = 0; j < matrix.cols; j++){
			if (matrix.at<uchar>(i, j) == 1){
				outData << '1';
				count++;
			}
			else if (matrix.at<uchar>(i, j) == 0)
				outData << '0';
		}
		outData << endl;
	}
	printf("Number of 1s in the pattern: %d\n", count);
	outData.close();
}

void savePatternTofileWithSpace(Mat &matrix){
	int count = 0;
	outData.open("FullPatternWithSpace.txt");
	for (int i = 0; i < matrix.rows; i++){
		for (int j = 0; j < matrix.cols; j++){
			if (matrix.at<uchar>(i, j) == 1){
				outData << "1 ";
				count++;
			}
			else if (matrix.at<uchar>(i, j) == 0)
				outData << "0 ";
		}
		outData << endl;
	}
	printf("Number of 1s in the pattern: %d\n", count);
	outData.close();
}

int main(){

	Mat pattern(yRes, xRes, CV_8UC1, Scalar(0));
	readPatternFromFile(pattern);

	imshow("Pattern", pattern);


	Mat patternImgLarge(yRes*symbolSize, xRes*symbolSize, CV_8UC3, Scalar(0, 0, 0));
	Mat patternImgExtend(yRes*extendSize, xRes*extendSize, CV_8UC1, Scalar(0));
	Mat patternImgLargeExtended(yRes*symbolSize*extendSize, xRes*symbolSize*extendSize, CV_8UC3, Scalar(0, 0, 0));

	//enlargePatternColorSpace(pattern, patternImgLarge);
	//enlargePatternRed(pattern, patternImgLarge);
	
	extendPattern(pattern, patternImgExtend);			//For IR Pattern
	enlargePatternBnW(patternImgExtend, patternImgLargeExtended);
	enlargePatternBnW(pattern, patternImgLarge);

	//savePatternTofile(patternImgExtend);
	savePatternTofileWithSpace(patternImgExtend);		//For IR pattern
	imshow("Extend Pattern", patternImgLarge);
	imwrite("Extend.bmp", patternImgLarge);
	//imwrite("Extend2.bmp", patternImgExtend);



	//imshow("Large Patter", patternImgLarge);

	//enlargePatternCircle(pattern, patternImgLarge);
	//imwrite("WithoutGrid.bmp", patternImgLarge); // For Color Patter
	//addGrid(patternImgLarge, symbolSize, 0, 0);
	//imshow("Large Patter", patternImgLarge);	// For Color Patter
	//imwrite("WithGrid.bmp", patternImgLarge);
	//imshow("Large Circle", patternImgLarge);

	waitKey(0);
	return 0;
}
